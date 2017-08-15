/* INCLUDES */

// Class header
#include "TechTreeDesign.h"

// Other includes
#include <algorithm>
#include "Game.h"
#include <mbstring.h>
#include <string>

/* DEFINITIONS */

// The DAT read function. Defined in TechTreeElement.cpp.
extern int(__cdecl *ReadDataFromCompressedFile)(int fileHandle, char *dataBuffer, unsigned int dataBufferSize);

/* FUNCTIONS */

TechTreeDesign::TechTreeDesign(int datFileHandle)
{
	// Read and check version marker
	const unsigned char TECH_TREE_DESIGN_VERSION = 1;
	unsigned char techTreeDesignVersion;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&techTreeDesignVersion), 1);
	if(techTreeDesignVersion != TECH_TREE_DESIGN_VERSION)
	{
		// Malformed data file, exit process with error message and let the OS do the cleanup (the game would have crashed anyway...)
		std::string errorMessage = "Invalid tech tree design version (expected version " + std::to_string(TECH_TREE_DESIGN_VERSION) + "): version " + std::to_string(techTreeDesignVersion);
		MessageBoxA(NULL, errorMessage.c_str(), "Error reading DAT file", MB_OK | MB_ICONERROR);
		ExitProcess(1);
	}

	// Read SLPs
	int len;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	_nodeSlpFileName = new char[len + 1];
	ReadDataFromCompressedFile(datFileHandle, _nodeSlpFileName, len);
	_nodeSlpFileName[len] = '\0';
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_nodeSlpId), 4);

	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	_scrollSlpFileName = new char[len + 1];
	ReadDataFromCompressedFile(datFileHandle, _scrollSlpFileName, len);
	_scrollSlpFileName[len] = '\0';
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollSlpId), 4);

	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	_tileSlpFileName = new char[len + 1];
	ReadDataFromCompressedFile(datFileHandle, _tileSlpFileName, len);
	_tileSlpFileName[len] = '\0';
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_tileSlpId), 4);

	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	_legendAgesSlpFileName = new char[len + 1];
	ReadDataFromCompressedFile(datFileHandle, _legendAgesSlpFileName, len);
	_legendAgesSlpFileName[len] = '\0';
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendAgesSlpId), 4);

	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	_legendDisableSlpFileName = new char[len + 1];
	ReadDataFromCompressedFile(datFileHandle, _legendDisableSlpFileName, len);
	_legendDisableSlpFileName[len] = '\0';
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendDisableSlpId), 4);

	// Read scroll data
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_mouseScrollArea), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_mouseScrollDelay), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_mouseScrollOffset), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_keyScrollOffset), 4);

	// Read button rectangles
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_closeButtonRelativeRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_closeButtonRelativeRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_closeButtonRelativeRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_closeButtonRelativeRectangle.Height), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollLeftButtonRelativeRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollLeftButtonRelativeRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollLeftButtonRelativeRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollLeftButtonRelativeRectangle.Height), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollRightButtonRelativeRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollRightButtonRelativeRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollRightButtonRelativeRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_scrollRightButtonRelativeRectangle.Height), 4);
	
	// Read resolution data
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	for(int i = 0; i < len; ++i)
	{
		// Read minimum height
		int minHeight;
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&minHeight), 4);

		// Read data and store results in local map
		_resolutionData[minHeight] = new ResolutionConfiguration(datFileHandle);
	}

	// Read popup data
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_popupLabelDelay), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_popupLabelWidth), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_popupInnerPadding), 4);

	// Read popup bevel data
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(_popupBoxBevelColorIndices), 6);
	
	// Read node data
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_nodeFontIndex), 1);
	int nodeBackgroundCount;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&nodeBackgroundCount), 4);
	for(int i = 0; i < nodeBackgroundCount; i++)
		_nodeTypes.push_back(new NodeType(datFileHandle));
}

TechTreeDesign::~TechTreeDesign()
{
	// Delete strings
	delete[] _nodeSlpFileName;
	delete[] _scrollSlpFileName;
	delete[] _tileSlpFileName;
	delete[] _legendAgesSlpFileName;
	delete[] _legendDisableSlpFileName;

	// Delete resolution list
	for(auto &rc : _resolutionData)
		delete rc.second;

	// Delete node type list
	for(NodeType *nt : _nodeTypes)
		delete nt;
}

TechTreeDesign::ResolutionConfiguration::ResolutionConfiguration(int datFileHandle)
{
	// Read values
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendFrameIndex), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_ageFrameIndex), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_tileFrameIndex), 4);

	// Read point
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendDisableSlpDrawPosition.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendDisableSlpDrawPosition.Y), 4);

	// Read rectangles
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civBonusLabelRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civBonusLabelRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civBonusLabelRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civBonusLabelRectangle.Height), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civSelectionComboBoxRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civSelectionComboBoxRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civSelectionComboBoxRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civSelectionComboBoxRectangle.Height), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civSelectionTitleLabelRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civSelectionTitleLabelRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civSelectionTitleLabelRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_civSelectionTitleLabelRectangle.Height), 4);
	
	// Read rectangles
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendNotResearchedLabelRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendNotResearchedLabelRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendNotResearchedLabelRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendNotResearchedLabelRectangle.Height), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendResearchedLabelRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendResearchedLabelRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendResearchedLabelRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendResearchedLabelRectangle.Height), 4);

	// Read rectangles
	int len;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	for(int i = 0; i < len; ++i)
	{
		Rect lNTLR;
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&lNTLR.X), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&lNTLR.Y), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&lNTLR.Width), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&lNTLR.Height), 4);
		_legendNodeTypeLabelRectangles.push_back(lNTLR);
	}

	// Read rectangle
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendDisabledLabelRectangle.X), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendDisabledLabelRectangle.Y), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendDisabledLabelRectangle.Width), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendDisabledLabelRectangle.Height), 4);

	// Read rectangles
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	for(int i = 0; i < len; ++i)
	{
		Rect aLR;
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&aLR.X), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&aLR.Y), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&aLR.Width), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&aLR.Height), 4);
		_ageLabelRectangles.push_back(aLR);
	}

	// Read draw offsets
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	for(int i = 0; i < len; ++i)
	{
		int vDO;
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&vDO), 4);
		_verticalDrawOffsets.push_back(vDO);
	}
}

TechTreeDesign::ResolutionConfiguration::~ResolutionConfiguration()
{
	// Nothing to do here
}

TechTreeDesign::NodeType::NodeType(int datFileHandle)
{
	// Read and discard name
	int len;
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
	char *garbage = new char[len];
	ReadDataFromCompressedFile(datFileHandle, garbage, len);
	delete[] garbage;

	// Read values
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_frameIndex), 4);
	ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_dllId), 4);
}

TechTreeDesign::NodeType::~NodeType()
{
	// Nothing to do here
}