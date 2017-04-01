/* INCLUDES */

// Class header
#define CLASS TechTreeData
#include "TechTreeData.h"

// C++ string class
#include <string>


/* STATIC WRAPPER FUNCTIONS */

STATIC_WRAPPER(Constructor, void, int)
STATIC_WRAPPER(Destructor, void)


/* FUNCTIONS */

// Set static data object
TechTreeData *_staticNewTechTreeDataObject = nullptr;

void TechTreeData::__Install()
{
	// First call base function
	base::__Install();

	// Patch tech tree object creation: Replace the null check of operator new by a call to TechTreeData::Constructor
	BYTE patch1[] =
	{
		0x53, // push ebx (0 here)
		0x57, // push edi (datFileHandle parameter)
		0x8B, 0xC8, // mov ecx, eax (handle to allocated memory)
		0xE8, 0xCA, 0xD2, 0xFD, 0xFF, // call constructor (of old tech tree data object)
		0x89, 0x86, 0xA4, 0x02, 0x00, 0x00, // mov [esi+2A4h], eax (store old tech tree data object pointer)
		0x57, // push edi (datFileHandle parameter)
		0xE8, 0x00, 0x00, 0x00, 0x00  // call TechTreeData::Constructor (address will be inserted in the next step)
	};
	CopyBytesToAddr(0x004268DD, patch1, sizeof(patch1));
	INSTALL_WRAPPER_DIRECT(Constructor, 0x004268ED);

	// Install destructor (overwrite VTable address assignment as that isn't neccessary)
	BYTE patch2[] =
	{
		0x90, // nop (alignment)
		0xE8, 0x00, 0x00, 0x00, 0x00  // call TechTreeData::Destructor (address will be inserted in the next step)
	};
	CopyBytesToAddr(0x00425F9F, patch2, sizeof(patch2));
	INSTALL_WRAPPER_DIRECT(Destructor, 0x00425FA0);
}

TechTreeData::TechTreeData(int datFileHandle)
{
	// The DAT read function.
	// Parameters:
	// -> fileHandle: The DAT file handle.
	// -> dataBuffer: A pointer to an buffer where the uncompressed data can be stored.
	// -> dataBufferSize: The size of the data buffer.
	int(__cdecl *ReadDataFromCompressedFile)(int fileHandle, char *dataBuffer, unsigned int dataBufferSize) = reinterpret_cast<int(__cdecl *)(int, char *, unsigned int)>(0x00542850);

	// Read marker
	const unsigned char TECH_TREE_VERSION = 1;
	char techTreeMarker[4];
	unsigned char techTreeVersion;
	ReadDataFromCompressedFile(datFileHandle, techTreeMarker, 3);
	techTreeMarker[3] = '\0';
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&techTreeVersion), 1);
	if(std::string("NTT").compare(techTreeMarker) != 0 || techTreeVersion != TECH_TREE_VERSION)
	{
		// Malformed data file, exit process with error message and let the OS do the cleanup (the game would have crashed anyway...)
		std::string errorMessage = "Invalid tech tree marker (expected NTT, version " + std::to_string(TECH_TREE_VERSION) + "): " + techTreeMarker + ", version " + std::to_string(techTreeVersion);
		MessageBoxA(NULL, errorMessage.c_str(), "Error reading DAT file", MB_OK | MB_ICONERROR);
		ExitProcess(1);
	}

	// Read root elements
	short rootElementCount;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&rootElementCount), 2);
	for(int i = 0; i < rootElementCount; ++i)
		_rootElements.push_back(new TechTreeElement(datFileHandle, nullptr));

	// Read design
	_design = new TechTreeDesign(datFileHandle);
}

void TechTreeData::Constructor(int datFileHandle)
{
	// Create new object
	if(_staticNewTechTreeDataObject == nullptr)
		_staticNewTechTreeDataObject = new TechTreeData(datFileHandle);
}

TechTreeData::~TechTreeData()
{
	// Delete root elements, they delete their children recursively
	for(TechTreeElement *root : _rootElements)
		delete root;
}

void TechTreeData::Destructor()
{
	// Delete and set value of static object pointer
	if(_staticNewTechTreeDataObject != nullptr)
		delete _staticNewTechTreeDataObject;
	_staticNewTechTreeDataObject = nullptr;
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

const TechTreeDesign *TechTreeData::GetDesignData()
{
	// Return design data
	return _design;
}