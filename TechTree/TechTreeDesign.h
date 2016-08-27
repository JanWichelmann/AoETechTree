#pragma once

/* INCLUDES */

// Other includes
#include "DrawUtilities.h"
#include <map>
#include <vector>

/* DEFINITIONS */

// Represents a single tech tree element.
class TechTreeDesign
{
	// Allow tech tree and renderers to access the data for efficiency and readability purposes
	friend class TechTreeWindow;
	friend class TechTreeRenderer;
	friend class VanillaTechTreeRenderer;

private:
	// Defines the configuration for a specific resolution.
	class ResolutionConfiguration
	{
	public:
		// The frame index of the legend background for this resolution.
		int _legendFrameIndex;

		// The frame index of the age bar for this resolution.
		int _ageFrameIndex;

		// The frame index of the tile graphic for this resolution.
		int _tileFrameIndex;

		// The draw position of the legend "disabled" icon.
		Point _legendDisableSlpDrawPosition;

		// The rectangle of the civ description and bonuses label.
		Rect _civBonusLabelRectangle;

		// The rectangle of the civ selection box.
		Rect _civSelectionComboBoxRectangle;

		// The rectangle of the civ selection label.
		Rect _civSelectionTitleLabelRectangle;

		// The rectangles of various legend labels.
		Rect _legendLabelRectangles[6];

		// The rectangles of the age name labels on the left side. There are always two per age: First the upper line, then the lower line.
		// Must have at least three entries.
		std::vector<Rect> _ageLabelRectangles;

		// The vertical node Y draw positions relative to the upper screen edge. There are always two per age: First the upper line, then the lower line.
		// Must have at least three entries.
		std::vector<int> _verticalDrawOffsets;

	public:
		// Constructor. Reads the resolution configuration data from the given DAT file handle.
		// Parameters:
		// -> datFileHandle: A handle to an uncompressed DAT file.
		ResolutionConfiguration(int datFileHandle);

		// Destructor.
		~ResolutionConfiguration();
	};

protected: // Member variables
	// The file name of the node background SLP (optional).
	char *_nodeSlpFileName;

	// The ID of the node background SLP.
	int _nodeSlpId;

	// The file name of scroll button SLP (optional).
	char *_scrollSlpFileName;

	// The ID of the scroll button SLP.
	int _scrollSlpId;

	// The file name of the tile SLP (optional).
	char *_tileSlpFileName;

	// The ID of the tile SLP.
	int _tileSlpId;

	// The file name of the legend and age bar SLP (optional).
	char *_legendAgesSlpFileName;

	// The ID of the legend and age bar SLP.
	int _legendAgesSlpId;

	// The file name of the legend disable icon SLP (optional).
	char *_legendDisableSlpFileName;

	// The ID of the legend disable icon SLP.
	int _legendDisableSlpId;

	// The mouse scroll margin at the screen border.
	int _mouseScrollArea;

	// The mosue scroll delay.
	int _mouseScrollDelay;

	// The mouse scroll step amount.
	int _mouseScrollOffset;

	// The key scroll step amount.
	int _keyScrollOffset;

	// The rectangle of the close button.
	Rect _closeButtonRelativeRectangle;

	// The rectangle of the scroll left button.
	Rect _scrollLeftButtonRelativeRectangle;

	// The rectangle of the scroll right button.
	Rect _scrollRightButtonRelativeRectangle;

	// The resolution specific data, indexed by minimum height.
	std::map<int, ResolutionConfiguration *> _resolutionData;

	// The popup box display delay.
	int _popupLabelDelay;

	// The width of the popup box label.
	int _popupLabelWidth;

	// The inner padding of the popup box.
	int _popupInnerPadding;

	// The bevel (border) colors of the popup box.
	unsigned char _popupBoxBevelColorIndices[6];

	// The Index
	unsigned char _nodeFontIndex;

public:
	// Constructor. Reads the tech tree element data from the given DAT file handle.
	// Parameters:
	// -> datFileHandle: A handle to an uncompressed DAT file.
	TechTreeDesign(int datFileHandle);

	// Destructor.
	~TechTreeDesign();
};