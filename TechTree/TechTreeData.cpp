/* INCLUDES */

// Class header
#define CLASS TechTreeData
#include "TechTreeData.h"

/* STATIC WRAPPER FUNCTIONS */

STATIC_WRAPPER(Destructor, void)

/* FUNCTIONS */

void TechTreeData::__Install()
{
	// First call base function
	base::__Install();

	// Patch a very ugly code region (tech tree construction when reading the DAT file, it's a complete mess of three different things randomly spread
	// between operator new and constructor call)
	DWORD constructorCallOffset = (PtrToUlong(&Constructor) - 0x004268D1) - 5;
	BYTE patch[] =
	{
		0x89, 0x9E, 0x58, 0x02, 0x00, 0x00, // mov [esi+0x258], ebx
		0x83, 0xC4, 0x0C, // add esp, 0x0C (stack cleanup for previous call)
		0xC7, 0x44, 0x24, 0x14, 0x01, 0x00, 0x00, 0x00, // mov [__$EHRec$.state], 1
		0x57, // push edi (datFileHandle parameter for constructor)
		0xE8, 0x00, 0x00, 0x00, 0x00, // TechTreeData::Constructor call (address will be inserted in the next step)
		0xEB, 0x14, // jmp short 0x004268EC
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // 8 dummy NOPs for easier debugging
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // 8 dummy NOPs for easier debugging
		0x90, 0x90, 0x90, 0x90 // 4 dummy NOPs for easier debugging
	};
	memcpy(patch + 19, &constructorCallOffset, sizeof(DWORD));
	CopyBytesToAddr(0x004268BF, patch, sizeof(patch));

	// Patch version number (no page protection change needed)
	*reinterpret_cast<char *>(0x0066B15A) = 'T';

	// Patch two original unknown TechTreeData calls that immediately crash the program if a game is started
	BYTE nopPatch1[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	CopyBytesToAddr(0x00454B23, nopPatch1, 15);
	BYTE nopPatch2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	CopyBytesToAddr(0x00454D25, nopPatch2, 6);

	// Install destructor
	INSTALL_WRAPPER_DIRECT(Destructor, 0x0042602E);
}

TechTreeData::TechTreeData(int datFileHandle)
{
	// The DAT read function.
	// Parameters:
	// -> fileHandle: The DAT file handle.
	// -> dataBuffer: A pointer to an buffer where the uncompressed data can be stored.
	// -> dataBufferSize: The size of the data buffer.
	int(__cdecl *ReadDataFromCompressedFile)(int fileHandle, char *dataBuffer, unsigned int dataBufferSize) = reinterpret_cast<int(__cdecl *)(int, char *, unsigned int)>(0x00542850);

	// Read root elements
	short rootElementCount;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&rootElementCount), 2);
	for(int i = 0; i < rootElementCount; ++i)
		_rootElements.push_back(new TechTreeElement(datFileHandle));
}

TechTreeData *TechTreeData::Constructor(int datFileHandle)
{
	// Return new object
	return new TechTreeData(datFileHandle);
}

void TechTreeData::Destructor()
{
	// Delete root elements, they delete their children recursively
	for(TechTreeElement *root : _rootElements)
		delete root;
}

void TechTreeData::UpdateRenderStates(char selectedCivId, int unknownGameAndPlayerData)
{
	// Update render state for all elements recursively
	for(auto &r : _rootElements)
		r->UpdateRenderState(selectedCivId, unknownGameAndPlayerData);
}

const std::vector<TechTreeElement *> &TechTreeData::GetRootElements()
{
	// Return root elements
	return _rootElements;
}