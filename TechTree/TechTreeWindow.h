#pragma once

/* INCLUDES */

// Base class header
#include "Window.h"

// Other includes
#include "ButtonControl.h"
#include "LabelControl.h"
#include "StaticControlContainer.h"
#include "DirectDrawBufferData.h"
#include "TechTreeRenderer.h"
#include "ComboBoxControl.h"
#include "TechTreeElement.h"
#include "FontData.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents the new tech tree screen.
class TechTreeWindow : public Window
{
private:
	typedef Window base;

private:
	// The area at the window borders where the mouse cursor triggers scrolling.
	static const int SCROLL_AREA = 15;

	// The time in milliseconds that has to elapse before the popup window is shown (when hovering an element).
	static const int ELEMENT_POPUP_DELAY = 500;

protected: // Member variables
	// The underlying window (that called the tech tree screen).
	Window *_underlyingWindow;

	// Horizontal scroll offset (relative position of left screen bound,  > 0 => scroll right).
	int _horizontalScrollOffset;

	// Vertical scroll offset (relative position of top screen bound,  > 0 => scroll down).
	int _verticalScrollOffset;

	// The tech tree renderer used.
	TechTreeRenderer *_renderer;

	// Close button and its buffer.
	ButtonControl *_closeButton;
	DirectDrawBufferData *_closeButtonDrawBuffer;

	// Left scroll button and its buffer.
	ButtonControl *_scrollLeftButton;
	DirectDrawBufferData *_scrollLeftButtonDrawBuffer;

	// Left scroll button and its buffer.
	ButtonControl *_scrollRightButton;
	DirectDrawBufferData *_scrollRightButtonDrawBuffer;

	// The arrow SLP for the scroll buttons.
	SlpFileElement *_arrowSlp;

	// The label where the civ information and bonuses are shown.
	LabelControl *_civBonusLabel;

	// The civ selection combo box.
	ComboBoxControl *_civSelectionComboBox;

	// The "game civs" label above the civ selection combo box.
	LabelControl *_gameCivsLabel;

	// The legend labels.
	LabelControl *_legendLabels[6];

	// The age count.
	int _ageCount;

	// Type of the age labels array.
	using AgeLabelsArrayType = LabelControl*(*)[2][2];

	// The age labels: [age][side][line].
	AgeLabelsArrayType _ageLabels;

	// The currently selected civ.
	int _currentCivId;

	// The currently selected (or hovered) element.
	TechTreeElement *_selectedElement;

	// The time when the selected element changed.
	int _selectedElementChangedTime;

	// The time when the last scroll action was performed.
	int _lastScrollActionTime;

	// The current mouse cursor position.
	Point _mouseCursorPosition;

	// The popup label containing element descriptions.
	LabelControl *_popupLabel;

	// The relative draw position of the popup label relative to the top left corner of the popup label box.
	Point _popupLabelRelativeDrawPosition;

	// The popup label base font.
	FontData *_popupLabelBaseFont;

	// The position of the popup label box.
	Point _popupLabelBoxPosition;

	// The size of the popup label box.
	Size _popupLabelBoxSize;

	// States if the popup label box should be drawn.
	bool _drawPopupLabelBox;

public:
	// Hide base class install function.
	static void __Install();

	// Constructor. Creates a new tech tree screen.
	// Parameters:
	// -> underlyingWindow: The calling window.
	// -> someData: Data given ingame to highlight currently available units and researches.
	// -> selectedCivId: The id of the initially selected civ.
	TechTreeWindow(Window *underlyingWindow, int someData, int selectedCivId) { Constructor(underlyingWindow, someData, selectedCivId); }
	TechTreeWindow *Constructor(Window *underlyingWindow, int someData, int selectedCivId);

	// Destructor.
	void Destructor();
	~TechTreeWindow() { Destructor(); }
	void ScalarDeletingDestructor(char mode) { if(mode & 1) delete this; else Destructor(); }
	static void operator delete(void *obj) { ::operator delete(obj); }

	// Draws the tech tree and its sub controls.
	void Draw();

	// Handles the given windows message.
	// Parameters:
	// -> hWnd: The handle to the responsible system window.
	// -> msg: The message code.
	// -> wParam: The wParam of the message.
	// -> lParam: The lParam of the message.
	int HandleWindowsMessage(HWND hWnd, signed int msg, WPARAM wParam, LPARAM lParam);

	// Performs an update (called periodically).
	int DoUpdate();

	// Handles the given custom message.
	// Parameters:
	// -> wParam: The wParam of the custom message.
	// -> lParam: The lParam of the custom message.
	int HandleUserMessage(WPARAM wParam, LPARAM lParam);

	// Handles a mouse button down event.
	// Parameters:
	// -> buttonId: The triggering mouse button (1: left, 2: right).
	// -> cursorPosX: The X position of the mouse cursor.
	// -> cursorPosY: The Y position of the mouse cursor.
	// -> controlKeyPressed: The state of the control key (1: pressed).
	// -> shiftKeyPressed: The state of the shift key (1: pressed).
	int HandleMouseButtonDown(int buttonId, int cursorPosX, int cursorPosY, int controlKeyPressed, int shiftKeyPressed);

	// Handles a mouse move event.
	// Parameters:
	// -> cursorPosX: The X position of the mouse cursor.
	// -> cursorPosY: The Y position of the mouse cursor.
	// -> controlKeyPressed: The state of the control key (1: pressed).
	// -> shiftKeyPressed: The state of the shift key (1: pressed).
	int HandleMouseMove(int cursorPosX, int cursorPosY, int controlKeyPressed, int shiftKeyPressed);

	// Handles a key down event in a second pass (first it is passed to all child controls).
	// Parameters:
	// -> keyDown: The virtual key code of the pressed key (VK_###).
	// -> lParam: The lParam of the key down message.
	// -> menuKeyDown: The state of the menu key (1: pressed).
	// -> controlKeyDown: The state of the control key (1: pressed).
	// -> shiftKeyDown: The state of the shift key (1: pressed).
	int HandleKeyDown2(int keyDown, int lParam, int menuKeyDown, int controlKeyDown, int shiftKeyDown);

	// Handles an application internal event triggered by sub controls like buttons or labels (e.g. "clicked" or "text changed").
	// -> triggeringControl: The triggering sub control.
	// -> code: The ID of the triggered event.
	// -> data1: Custom event data.
	// -> data2: Custom event data.
	int HandleChildControlEvent(Control *triggeringControl, int code, int data1, int data2);

	// Applies the given scroll offset.
	// Parameters:
	// -> horizontalScrollOffset: The horizontal scroll offset (> 0 -> scroll right).
	// -> verticalScrollOffset: The vertical scroll offset (> 0 -> scroll down).
	void ApplyScrollOffset(int horizontalScrollOffset, int verticalScrollOffset);

	// Sets the currently selected civ. 
	// Parameters:
	// -> civId: The civ to be selected.
	void SetCurrentCiv(int civId);

	// Updates the visibility of the popup label box (selection change).
	void UpdatePopupBoxVisibility();

	// Applies the element selection and issues a redraw.
	void ApplySelectedElementAndRedraw();

	// Updates the size and position data of the popup label.
	void UpdatePopupLabelDrawData();
};
#pragma pack(pop)