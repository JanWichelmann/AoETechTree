#pragma once

/* INCLUDES */

// Base class header
#include "Control.h"

// Other includes
#include "SlpFileElement.h"
#include "UnknownPaletteRelatedClass.h"
#include "LabelControl.h"
#include "ButtonControl.h"
#include "TextBoxControl.h"
#include "ComboBoxControl.h"

/* DEFINITIONS */

// Prototype for virtual function table class
class PanelVTable;

#pragma pack(push, 1)
// Represents an abstract panel.
// Research type name: ProxyWindowInformation.
class Panel : public Control
{
private:
	typedef Control base;

protected: // Member variables
	int _minimumWindowWidth;
	int _minimumWindowHeight;
	char _styleResourceName[260];
	int _styleResourceId;
	SlpFileElement *_backgroundSlpFileElement1;
	SlpFileElement *_backgroundSlpFileElement2;
	HPALETTE _palette;
	char _cursorsFileName[260];
	int _cursorsFileResourceId;
	int _styleBackgroundPosition;
	int _useBevelColors;
	int _unknownFlag2;
	unsigned char _bevelColor1;
	unsigned char _bevelColor2;
	unsigned char _bevelColor3;
	unsigned char _bevelColor4;
	unsigned char _bevelColor5;
	unsigned char _bevelColor6;
	char _unknownByte7ab1;
	char _unknownByte7ab2;
	int _styleText1Color1_BGR;
	int _styleText1Color2_BGR;
	int _styleFocusColor1_BGR;
	int _styleFocusColor2_BGR;
	int _styleStateColor1_BGR;
	int _styleStateColor2_BGR;
	int _styleText2Color1_BGR;
	int _styleText2Color2_BGR;
	int _unknownValue7ab3;
	char _popupDialogStyleResourceName[260];
	int _popupDialogStyleResourceId;
	SlpFileElement *_styleButtonSlp;
	UnknownPaletteRelatedClass *_unknownPaletteThings;
	int _shadeAmountPercentage;
	char _styleBackgroundColor1;
	char _styleBackgroundColor2;
	char _unknown7b[10];
	int _unknownBGValue1;
	HGDIOBJ _blackBrush;
	int _unknownBGValue2;
	DirectDrawBufferData *_windowDirectDrawBuffer;
	char _unknown7c1[12];
	LabelControl *_maybeHelpTextLabel;
	int _helpTextCount;
	Panel *_helpTextControls[70];
	int _helpTextDllIds[70];
	int _maybeHelpTextFontIndices[70];
	char _unknown7c2[8];

public:
	// Hide base class install function.
	static void __Install();

	// Draws the background.
	void Draw();

	// TODO: To be deleted, unused....
	// Creates a button with a string read from the language DLLs and a single font.
	// Parameters:
	// -> parentWindow: The parent window of the calling control.
	// -> destinationButtonPointer: A reference to a button pointer, where the reference to the created button shall be stored.
	// -> labelString0: The ID of the first string (initially shown).
	// -> labelString1: The ID of the second string (optional).
	// -> buttonPositionX: The X position of the new button.
	// -> buttonPositionY: The Y position of the new button.
	// -> buttonWidth: The width of the new button.
	// -> buttonHeight: The height of the new button.
	// -> fontIndex: The index of the font to be used.
	// -> interfaceSoundIndex: The index of the sound to be played when the button is pressed.
	// -> unknown: Unknown.
	bool CreateButtonWithOneFontWithTextFromDll(Panel *parentWindow, ButtonControl **destinationButtonPointer, int labelString0, int labelString1, int buttonPositionX, int buttonPositionY, int buttonWidth, int buttonHeight, int fontIndex, int interfaceSoundIndex, int unknown);

	// Handles a mouse move event.
	// Parameters:
	// -> cursorPosX: The X position of the mouse cursor.
	// -> cursorPosY: The Y position of the mouse cursor.
	// -> controlKeyPressed: The state of the control key (1: pressed).
	// -> shiftKeyPressed: The state of the shift key (1: pressed).
	int HandleMouseMove(int cursorPosX, int cursorPosY, int controlKeyPressed, int shiftKeyPressed);

	// Handles a mouse button down event.
	// Parameters:
	// -> buttonId: The triggering mouse button (1: left, 2: right).
	// -> cursorPosX: The X position of the mouse cursor.
	// -> cursorPosY: The Y position of the mouse cursor.
	// -> controlKeyPressed: The state of the control key (1: pressed).
	// -> shiftKeyPressed: The state of the shift key (1: pressed).
	int HandleMouseButtonDown(int buttonId, int cursorPosX, int cursorPosY, int controlKeyPressed, int shiftKeyPressed);
};
#pragma pack(pop)

#pragma pack(push, 1)
// Represents the virtual function table of the Panel class.
class PanelVTable : public ControlVTable
{
public: // Function pointers
	int Unknown100[2];
	void(__thiscall* UnknownDrawBackgroundAndBevels)(Panel *, int);
	void(__thiscall* SetMinimumWindowSize)(Panel *, int, int);
	bool(__thiscall* CreateButtonWithOneFontWithTextFromDll)(Panel *, Panel *, ButtonControl **, int, int, int, int, int, int, int, int, int);
	bool(__thiscall* CreateButton)(Panel *, Panel *, ButtonControl **, char *, char *, int, int, int, int, int, int, int);
	int Unknown101[4];
	bool(__thiscall* CreateLabel)(Panel *, Panel *, LabelControl **, char *, int, int, int, int, int *, int, int, int, int, int);
	bool(__thiscall* CreateLabelWithOneFontWithTextFromDll)(Panel *, Panel *, LabelControl **, int, int, int, int, int, int, int, int, int);
	int Unknown102;
	bool(__thiscall* CreateLabelWithOneFont)(Panel *, Panel *, LabelControl **, char *, int, int, int, int, int, int, int, int);
	int Unknown103;
	bool(__thiscall* CreateTextBox)(Panel *, Panel *, TextBoxControl **, char *, int, int, int, int, int, int, int, int, int, int);
	bool(__thiscall* CreateComboBox)(Panel *, Panel *, ComboBoxControl **, int, int, int, int, int, int, int);
	int Unknown104;
	bool(__thiscall* CreateScrollBarForLabelAtPosition)(Panel *, Panel *, ScrollBarControl * *, LabelControl *, int, int, int, int, int);
	bool(__thiscall* CreateScrollBarForLabel)(Panel *, Panel *, ScrollBarControl * *, LabelControl *, int);
	int Unknown105[6];
};
#pragma pack(pop)