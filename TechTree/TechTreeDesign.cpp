/* INCLUDES */

// Class header
#include "TechTreeDesign.h"

// Other includes
#include <algorithm>
#include "Game.h"
#include <mbstring.h>

/* DEFINITIONS */

// The DAT read function. Defined in TechTreeElement.cpp.
extern int(__cdecl *ReadDataFromCompressedFile)(int fileHandle, char *dataBuffer, unsigned int dataBufferSize);

/* FUNCTIONS */

TechTreeDesign::TechTreeDesign(int datFileHandle)
{
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
	{
		// Read and discard name
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&len), 4);
		char *garbage = new char[len];
		ReadDataFromCompressedFile(datFileHandle, garbage, len);
		delete[] garbage;

		// Read and save frame index
		int frameIndex;
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&frameIndex), 4);
		_nodeBackgrounds.push_back(frameIndex);
	}
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
	for(int i = 0; i < 6; ++i)
	{
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendLabelRectangles[i].X), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendLabelRectangles[i].Y), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendLabelRectangles[i].Width), 4);
		ReadDataFromCompressedFile(datFileHandle, reinterpret_cast<char *>(&_legendLabelRectangles[i].Height), 4);
	}

	// Read rectangles
	int len;
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