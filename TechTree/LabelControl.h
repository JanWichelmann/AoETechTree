#pragma once

/* INCLUDES */

// Base class header
#include "Control.h"

// Other includes
#include "SlpFileElement.h"
#include "LabelLineData.h"
#include "ScrollBarControl.h"

/* DEFINITIONS */

// Prototype for virtual function table class
class LabelControlVTable;

#pragma pack(push, 1)
// Represents a label.
class LabelControl : public Control
{
protected: // Member variables
	LabelLineData *_firstLineData;
	short _lineCount;
	short _unknownValue100_2;
	short _unknownValue100_3;
	short _unknownValue100_4;
	short _lastSearchedLineIndex;
	short _unknownValue100_6;
	HFONT _fontHandles[4];
	int _maximumCharWidth;
	int _maximumCharHeight;
	int _verticalTextAlignment_3Top_012Center_4Bottom;
	int _horizontalTextAlignment_1Left_0Center_2Right;
	int _unknown100b_1;
	int _maybe_HasMaximumWidth_OR_HasDifferentFormats;
	int _unknown_StyleTextColor2AndShadowRelated1;
	int _unknown_StyleTextColor2AndShadowRelated2;
	int _styleText2Color1_BGR;
	int _styleText2Color2_BGR;
	int _styleFocusColor1_BGR;
	int _styleFocusColor2_BGR;
	ScrollBarControl *_scrollBar;
	int _maybeAutoSize_ProbablyWrong;
	short _maxLineLength;
	char _unknown100c[10];
	SlpFileElement *_unknownSlpFile;
	short _firstFrameWidth;
	short _firstFrameHeight;
	char _unknown100d[24];
	int _sortLines;
	char _unknown100e[8];
	int _scrollBarWidth;
	char _unknown100f[4];
	int _unknownBevelColorRelated;
	char _bevelColors[6];
	char _unknown100g[22];

public:
	// Constructor. Creates a new label.
	LabelControl() { Constructor(); }
	LabelControl* Constructor();

	// Sets an unknown flag and issues a redraw.
	// Parameters:
	// -> unknown: Unknown.
	int sub_545D50(int unknown);

	// Sets an unknown text color and issues a redraw.
	// Parameters:
	// -> unknown: Unknown.
	int sub_545D70(int unknown);

	// Sets text colors.
	// Parameters:
	// -> styleTextColor1_BGR: The first text color in BGR format.
	// -> styleTextColor2_BGR: The second text color in BGR format.
	int SetStyleText2Colors(int styleTextColor1_BGR, int styleTextColor2_BGR);

	// Draws the label.
	void ForceDraw();

	// Interpretes tags like <b> and applies word wrap.
	// Parameters:
	// -> unformattedText: The plain text.
	// -> id: The id to be assigned to the text.
	// -> isResearch: Neccessary to decide if e.g. the <cost> tag applies to a unit or a research.
	void InterpreteTextFormatCodesAndComputeWordWrap(char *unformattedText, int id, int isResearch);

	// Does unknown things, but seems to be text color related.
	// Parameters:
	// -> unknown1: Unknown.
	// -> unknown2: Unknown.
	int sub_545DF0(int unknown1, char unknown2);

	// Sets the tiled background image.
	// Parameters:
	// -> slpFileName: The name of the background SLP.
	// -> slpResId: The ID of the background SLP.
	void SetBackgroundSlp(char *slpFileName, int slpResId);

	// Does some initialization and many unknown things.
	// Parameters:
	// -> parentControlBackBuffer: The back buffer of the parent control.
	// -> parentControl: The parent control.
	// -> posX: The initial X position of the label.
	// -> posY: The initial Y position of the label.
	// -> width: The initial width of the label.
	// -> height: The initial height of the label.
	// -> fonts: Exactly 4 fonts to be used.
	// -> maximumCharWidth: Some char width.
	// -> maximumCharHeight: Some char height.
	// -> slpFileName: Some SLP file name.
	// -> unknown1: Unknown.
	// -> unknown2: Unknown.
	// -> unknown3: Unknown.
	// -> unknown4: Unknown.
	// -> maxLineLength: The maximum allowed line length (else force word wrap).
	// -> text: Initial text.
	int sub_5444B0(DirectDrawBufferData *parentControlBackBuffer, Control *parentControl, int posX, int posY, int width, int height, HFONT *fonts, int maximumCharWidth, int maximumCharHeight, char *slpFileName, int unknown1, char unknown2, int unknown3, char unknown4, short maxLineLength, char *text);

	// Sets the text alignment.
	// Parameters:
	// -> horizontalAlignment: The horizontal text alignment.
	// -> verticalAlignment: The vertical text alignment.
	void SetTextAlignment(int horizontalAlignment, int verticalAlignment);

	// Returns the count of wrapped lines.
	int GetLineCount();
};
#pragma pack(pop)

#pragma pack(push, 1)
// Represents the virtual function table of the LabelControl class.
class LabelControlVTable : public ControlVTable
{
public: // Function pointers
	int unknown1;
	void(__thiscall *AssignTextFromLanguageDlls)(LabelControl *, int);
	void(__thiscall *ComputeWordWrap)(LabelControl *, char *, TextFormatData *);
	int unknown2[2];
	void(__thiscall *InterpreteTextFormatCodesAndComputeWordWrap)(LabelControl *, char *, int, int);
	int(__thiscall *SetBevelColors)(LabelControl *, int, char, char, char, char, char, char);
	int unknown3[2];
	bool(__thiscall *AddLineToLineList)(LabelControl *, int, char *, char *, int, TextFormatData *);
	char *(__thiscall *GetLineWithIndex)(LabelControl *, int);
	void(__thiscall *DeleteAllLines)(LabelControl *);
};
#pragma pack(pop)