#pragma once

/* INCLUDES */

// Base class header
#include "Control.h"

// Other includes
#include "SlpFileElement.h"
#include "UnknownPaletteRelatedClass.h"
#include "LabelControl.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents a button.
class ButtonControl : public Control
{
private:
	typedef Control base;

protected: // Member variables
	int _unknown_MaybeLabelStringsIdList[9];
	int _unknown_MaybeLabelStringsIdList_Related[9];
	char _unknown100a1[12];
	int _displayMode;
	char _unknown100a2[4];
	int _sound;
	SlpFileElement *_backgroundSlps[9];
	__int16 _backgroundSlpFrameIndices[9];
	char _unknown100b1[2];
	int _unknownValue100bBackgroundSlpRelated1;
	int _unknownValue100bBackgroundSlpRelated2;
	int _unknownValue100bBackgroundSlpRelated3;
	int _unknownValue100bBackgroundSlpRelated4;
	char _unknown100b[4];
	char *_labelStringsFirstLine[6];
	char _unknown101[12];
	char *_labelStringsSecondLine[6];
	char _unknown102a[20];
	HFONT _fontHandle;
	int _fontAverageCharWidth;
	int _fontHeightWithRowSpace;
	char _unknown102b[16];
	int _keyDownTimeStamp;
	int _styleTextColors1_BGR[9];
	int _styleTextColors2_BGR[9];
	int _styleFocusColors1_BGR[9];
	int _styleFocusColors2_BGR[9];
	char _unknown102c[4];
	int _hotKey;
	int _shiftKeyModifierNeeded;
	int _controlKeyModifierNeeded;
	int _menuKeyModifierNeeded;
	int _unknownBevelColorRelated;
	char _bevelColor1;
	char _bevelColor2;
	char _bevelColor3;
	char _bevelColor4;
	char _bevelColor5;
	char _bevelColor6;
	char _unknown102d[2];
	int _keyDown;
	char _unknown102e[4];
	int _soundIndex;
	bool _unknownFlagUsedByGameSetupWindowAtPlayerAndTeamNumber;
	char _unknown102f[3];

public:
	// Returns the client rectangle.
	RECT GetClientRectangle();

	// Draws the button without considering its parent window.
	void DrawSingle();

	// Sets the hotkey and its modifiers.
	// Parameters:
	// -> hotKey: The key to trigger the button (VK_###).
	// -> shiftKeyModifierNeeded: Specifies if the shift key has to be pressed.
	// -> controlKeyModifierNeeded: Specifies if the control key has to be pressed.
	// -> menuKeyModifierNeeded: Specifies if the menu key has to be pressed.
	void SetHotKey(int hotKey, int shiftKeyModifierNeeded, int controlKeyModifierNeeded, int menuKeyModifierNeeded);

	// Sets a SLP frame as background.
	// Parameters:
	// -> backgroundIndex: The background display index.
	// -> backgroundSlp: The corresponding SLP.
	// -> frameId: The ID of the frame to be used as background.
	void SetBackgroundSlpAtIndex(short backgroundIndex, SlpFileElement *backgroundSlp, short frameId);

	// Sets some display mode. This controls the draw behaviour when clicked, hovered etc.
	// Parameters:
	// -> mode: The display mode.
	void SetDisplayMode(int mode);

	// Sets the label string. The exact behaviour isn't fully understood yet.
	// Parameters:
	// -> index: The label ID.
	// -> labelString: The label string.
	void AssignLabelString(short index, char *labelString);
};
#pragma pack(pop)