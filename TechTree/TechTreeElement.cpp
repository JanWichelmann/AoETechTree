/* INCLUDES */

// Class header
#include "TechTreeElement.h"

// Other includes
#include <algorithm>
#include "Game.h"
#include <mbstring.h>

/* DEFINITIONS */

// The DAT read function.
// Parameters:
// -> fileHandle: The DAT file handle.
// -> dataBuffer: A pointer to an buffer where the uncompressed data can be stored.
// -> dataBufferSize: The size of the data buffer.
int(__cdecl *ReadDataFromCompressedFile)(int fileHandle, char *dataBuffer, unsigned int dataBufferSize) = reinterpret_cast<int(__cdecl *)(int, char *, unsigned int)>(0x00542850);

/* FUNCTIONS */

TechTreeElement::TechTreeElement(int datFileHandle)
{
	// Read properties
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_elementType), 1);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_elementObjectID), 2);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_age), 1);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_renderMode), 1);

	// Read disabling civs
	char disableCivCount;
	ReadDataFromCompressedFile(datFileHandle, &disableCivCount, 1);
	for(int i = 0; i < disableCivCount; ++i)
	{
		// Read civ id
		char civId;
		ReadDataFromCompressedFile(datFileHandle, &civId, 1);
		_disableCivs.push_back(civId);
	}

	// Read children
	short childElementCount;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&childElementCount), 2);
	for(int i = 0; i < childElementCount; ++i)
		_children.push_back(new TechTreeElement(datFileHandle));

	// Read required elements
	short requiredCount;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&requiredCount), 2);
	for(int i = 0; i < requiredCount; ++i)
		_requiredElements.push_back(new RequiredElement(datFileHandle));

	// Initialize name variables
	_elementNameFirstLine[0] = '\0';
	_elementNameSecondLine[0] = '\0';
}

TechTreeElement::~TechTreeElement()
{
	// TODO: TechTreeElements aren't properly deleted

	// Free required elements
	for(RequiredElement *req : _requiredElements)
		delete req;
}

void TechTreeElement::UpdateRenderState(char selectedCivId)
{
	// Is the civ disabling this element?
	if(std::find(_disableCivs.begin(), _disableCivs.end(), selectedCivId) != _disableCivs.end())
	{
		// Civ disables. Hide or just gray out?
		if(_renderMode == ItemRenderMode::HideIfDisabled)
			_renderState = ItemRenderState::Hidden;
		else
			_renderState = ItemRenderState::Disabled;
	}
	else
	{
		// Enable element
		_renderState = ItemRenderState::Visible;
	}

	// Use the opportunity to load element caption
	// TODO: Do this always? Different civs can have different names for same units. Check for performance impact first...
	if(_elementNameFirstLine[0] == '\0' && _elementNameSecondLine[0] == '\0')
	{
		// Buffer
		char elementNameBuffer[256];

		// Calculate DLL index
		int dllIndex = -1;
		if(_elementType == TechTreeElement::ItemType::Building || _elementType == TechTreeElement::ItemType::Creatable)
			dllIndex = (*_staticGameObjectPointer)->GetGameDataHandler()->_civs[selectedCivId]->_units[_elementObjectID]->_languageDllNameId + 9000;
		else if(_elementType == TechTreeElement::ItemType::Research)
			dllIndex = (*_staticGameObjectPointer)->GetGameDataHandler()->_researches->_researches[_elementObjectID]._languageDLLName1 + 10000;

		// Get DLL string
		(*_staticGameObjectPointer)->GetStringFromLanguageDllsWithBuffer(dllIndex, elementNameBuffer, sizeof(elementNameBuffer));

		// Find position of line break
		// We deal with multibyte strings, so use _mbsinc to go to the next character
		char *elementNameBufferCurrPos = elementNameBuffer;
		int elementNameByteCount = strlen(elementNameBuffer);
		int firstLineByteCount = elementNameByteCount;
		while(elementNameBufferCurrPos < elementNameBuffer + elementNameByteCount)
		{
			// Line break found?
			if(*elementNameBufferCurrPos == '\n')
			{
				// Ignore line break
				elementNameBufferCurrPos = reinterpret_cast<char *>(_mbsinc(reinterpret_cast<unsigned char *>(elementNameBufferCurrPos)));

				// Set first line length for later copying
				int elementNameBufferCurrPosLength = strlen(elementNameBufferCurrPos);
				firstLineByteCount = elementNameByteCount - elementNameBufferCurrPosLength - 1;

				// Copy second line
				strcpy(_elementNameSecondLine, elementNameBufferCurrPos);

				// Done
				break;
			}
			else // Nope, next char
				elementNameBufferCurrPos = reinterpret_cast<char *>(_mbsinc(reinterpret_cast<unsigned char *>(elementNameBufferCurrPos)));
		}

		// Copy first line
		strncpy(_elementNameFirstLine, elementNameBuffer, firstLineByteCount);
		_elementNameFirstLine[firstLineByteCount] = '\0';
	}

	// Update display names for required elements
	for(RequiredElement *req : _requiredElements)
		req->UpdateDisplayName(selectedCivId);

	// Update render state for all children recursively
	for(auto &c : _children)
		c->UpdateRenderState(selectedCivId);
}

TechTreeElement::RequiredElement::RequiredElement(int datFileHandle)
{
	// Read properties
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_elementType), 1);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_elementObjectID), 2);

	// Initialize name variables
	_elementNameFirstLine[0] = '\0';
	_elementNameSecondLine[0] = '\0';
}

// Destructor.
TechTreeElement::RequiredElement::~RequiredElement()
{
	// Nothing to do here
}

void TechTreeElement::RequiredElement::UpdateDisplayName(char selectedCivId)
{
	// Load element caption
	// TODO: Do this always? Different civs can have different names for same units. Check for performance impact first...
	if(_elementNameFirstLine[0] == '\0' && _elementNameSecondLine[0] == '\0')
	{
		// Buffer
		char elementNameBuffer[256];

		// Calculate DLL index
		int dllIndex = -1;
		if(_elementType == TechTreeElement::ItemType::Building || _elementType == TechTreeElement::ItemType::Creatable)
			dllIndex = (*_staticGameObjectPointer)->GetGameDataHandler()->_civs[selectedCivId]->_units[_elementObjectID]->_languageDllNameId + 9000;
		else if(_elementType == TechTreeElement::ItemType::Research)
			dllIndex = (*_staticGameObjectPointer)->GetGameDataHandler()->_researches->_researches[_elementObjectID]._languageDLLName1 + 10000;

		// Get DLL string
		(*_staticGameObjectPointer)->GetStringFromLanguageDllsWithBuffer(dllIndex, elementNameBuffer, sizeof(elementNameBuffer));

		// Find position of line break
		// We deal with multibyte strings, so use _mbsinc to go to the next character
		char *elementNameBufferCurrPos = elementNameBuffer;
		int elementNameByteCount = strlen(elementNameBuffer);
		int firstLineByteCount = elementNameByteCount;
		while(elementNameBufferCurrPos < elementNameBuffer + elementNameByteCount)
		{
			// Line break found?
			if(*elementNameBufferCurrPos == '\n')
			{
				// Ignore line break
				elementNameBufferCurrPos = reinterpret_cast<char *>(_mbsinc(reinterpret_cast<unsigned char *>(elementNameBufferCurrPos)));

				// Set first line length for later copying
				int elementNameBufferCurrPosLength = strlen(elementNameBufferCurrPos);
				firstLineByteCount = elementNameByteCount - elementNameBufferCurrPosLength - 1;

				// Copy second line
				strcpy(_elementNameSecondLine, elementNameBufferCurrPos);

				// Done
				break;
			}
			else // Nope, next char
				elementNameBufferCurrPos = reinterpret_cast<char *>(_mbsinc(reinterpret_cast<unsigned char *>(elementNameBufferCurrPos)));
		}

		// Copy first line
		strncpy(_elementNameFirstLine, elementNameBuffer, firstLineByteCount);
		_elementNameFirstLine[firstLineByteCount] = '\0';
	}
}