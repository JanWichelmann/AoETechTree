#pragma once

/* INCLUDES */

// Base class headers
#include "GameType.h"
#include "VTableType.h"

// Other includes
#include "ControlListElement.h"
#include "DirectDrawBufferData.h"
#include "AnotherControlRelatedClass.h"
#include "DrawUtilities.h"

/* DEFINITIONS */

// Prototype for virtual function table class
class ControlVTable;

#pragma pack(push, 1)
// Represents an abstract control.
// Research type name: WindowInformation.
class Control : public GameType
{
private:
	typedef GameType base;

public:
	// The different control type identifieres.
	enum class ControlType : char
	{
		Label = 1
	};

public:
	// Virtual function table.
	// Public for simplification of calls.
	ControlVTable *_VTable;

protected: // Member variables
	Control *_underlyingWindowInformation;
	Control *_unknownWindowInformation1;
	int _positionX2;
	int _positionY2;
	int _width1;
	int _height1;
	char *_controlTypeName;
	DirectDrawBufferData *_backBufferData;
	RECT _clientRectangle;
	int _maybeBiggerThanScreen;
	int _maybeStillNeedsToBeDrawn;
	Control *_currentSelectedSubElement;
	Control *_parentWindow;
	AnotherControlRelatedClass *_aWRS1;
	AnotherControlRelatedClass *_aWRS2;
	AnotherControlRelatedClass *_aWRS3;
	AnotherControlRelatedClass *_aWRS4;
	ControlListElement *_controlListElement;
	ControlListElement *_childControlListBegin;
	ControlListElement *_childControlListEnd;
	Control *_tabElementBefore;
	Control *_tabElementAfter;
	int _maybeHasUnderlyingControl;
	int _unknownValue6b;
	int _hasDrawRegion;
	int _allowsTab;
	int _selectionState;
	char _unknown5[16];
	HRGN _drawRegion;
	RECT _innerDrawArea;
	int _positionX;
	int _positionY;
	int _maybeMarginRight;
	int _maybeMarginBottom;
	int _width2;
	int _width3;
	int _height2;
	int _height3;
	char _unknown6a[28];
	int _initializationError;
	int _maybeSomeChildId;
	char _unknown6b[14];
	ControlType _controlTypeIdentifier;
	char _backgroundColor;
	char _fillBackground;
	char _unknown6c[2];
	bool _unknownFlagSetInGameClass;

public:
	// Hide base class install function.
	static void __Install();

	// Override delete operator to ensure correct destructor call.
	// Parameters:
	// -> obj: A pointer to the object being deleted.
	static void operator delete(void *obj);

	// Assigns an ID to the control and puts it into the ordered children list of the parent window.
	// Parameters:
	// -> idSelectionMode: The way the ID is calculated involving the existing IDs and/or the ID parameter.
	// -> id: The ID used if idSelectionMode is 0.
	void AssignIdToControlAndMoveInParentChildrenList(char idSelectionMode, short id);

	// Handles the given windows message.
	int HandleWindowsMessage(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam);

	// Handles an application internal event triggered by sub controls like buttons or labels (e.g. "clicked" or "text changed").
	// -> triggeringControl: The triggering sub control.
	// -> code: The ID of the triggered event.
	// -> data1: Custom event data.
	// -> data2: Custom event data.
	int HandleChildControlEvent(Control *triggeringControl, int code, int data1, int data2);

	// Updates the control.
	int DoUpdate();

	// Sets the selected sub control.
	// Parameters:
	// -> newSelectedControl: The control gaining focus.
	void UpdateSelectedSubControl(Control *newSelectedControl);

	// Returns the type name.
	char *GetControlTypeName();

	// Sets the position and the size.
	// Parameters:
	// -> posX: The X position.
	// -> posY: The Y position.
	// -> width: The width.
	// -> height: The height.
	void UpdatePositionAndSizeData(int posX, int posY, int width, int height);

	// Returns the control type id.
	ControlType GetTypeIdentifier();

	// Returns the position and size data of the control.
	Rect GetPositionAndSizeData();

	// Sets the background fill mode.
	// Parameters:
	// -> fill: The new fill mode.
	void SetFillBackground(char fill);

	// Returns the width of this control.
	int GetWidth();

	// Returns the height of this control.
	int GetHeight();
};
#pragma pack(pop)

#pragma pack(push, 1)
// Represents the virtual function table of the Control class.
class ControlVTable : public VTableType
{
public: // Function pointers
	void(__thiscall *ScalarDeletingDestructor)(Control *, char mode);
	int(__thiscall *SetDrawDataAndCreateChildListElement)(Control *, DirectDrawBufferData *, Control *, int, int, int, int, int);
	void(__thiscall *AssignRectangleDataAndCreateDrawRegion)(Control *, int, int, int, int);
	void(__thiscall *AssignSizeDataAndCreateDrawRegion)(Control *, int, int, int, int);
	void(__thiscall *AssignBackgroundColorAndRedraw)(Control *, BYTE);
	void(__thiscall *InvalidateAndRedrawControl1)(Control *, int);
	void(__thiscall *UpdatePositionAndSizeAndOtherData)(Control*, int, int, int, int, int, int, int, int, int, int, int, int, int);
	void(__thiscall *UpdatePositionAndSizeData)(Control*, int, int, int, int);
	void(__thiscall *InvalidateAndRedrawControl2)(Control *, int);
	void(__thiscall *UnknownDrawingRelated)(Control *, Control *, Control *, int);
	void(__thiscall *BeginDrawRun)(Control *, int);
	void(__thiscall *EndDrawRun)(Control *);
	void(__thiscall *Draw)(Control *);
	DWORD gap1b[4];
	void(__thiscall *BlitBackBufferToScreenBuffer)(Control *);
	int(__thiscall *HandleWindowsMessage)(Control *, HWND, int, WPARAM, LPARAM);
	int(__thiscall *DoUpdate)(Control *);
	void(__thiscall *CalculateAndAssignRectangleData)(Control *, int, int);
	void(__thiscall *RecursiveDraw)(Control *);
	int(__thiscall *HandleKeyDown)(Control *, int, int, int, int, int);
	int(__thiscall *HandleCharMessage)(Control *, WPARAM, LPARAM);
	int(__thiscall *HandleCommandMessage)(Control *, WPARAM, LPARAM);
	int(__thiscall *HandleUserMessage)(Control *, WPARAM, LPARAM);
	int(__thiscall *HandleTimerMessage)(Control *, WPARAM, LPARAM);
	int(__thiscall *HandleScrollMessage)(Control *, int, int);
	int(__thiscall *HandleMouseButtonDown)(Control *, int, int, int, int, int);
	int(__thiscall *HandleMouseMove)(Control *, int, int, int, int);
	int(__thiscall *HandleMouseButtonUp)(Control *, int, int, int, int, int);
	int(__thiscall *HandleMouseDoubleClick)(Control *, int, int, int, int, int);
	int(__thiscall *HandleMouseWheel)(Control *, int, WPARAM, LPARAM);
	int(__thiscall *HandleMouseWheel2)(Control *, int, WPARAM, LPARAM);
	int(__thiscall *HandleMouseXButtonDownAndUp)(Control *, int, WPARAM, LPARAM);
	int(__thiscall *HandleMouseXButtonDownAndUp2)(Control *, int, WPARAM, LPARAM);
	DWORD gap2b1c;
	int(__thiscall *HandleLeftMouseButtonDown)(Control *, int, int, int, int);
	int(__thiscall *HandleLeftMouseButtonDownUpdate)(Control *, int, int, int, int);
	DWORD gap2b1d;
	int(__thiscall *HandleLeftMouseButtonUp)(Control *, int, int, int, int);
	int(__thiscall *HandleLeftMouseButtonDoubleClick)(Control *, int, int, int, int);
	int(__thiscall *HandleRightMouseButtonDown)(Control *, int, int, int, int);
	int(__thiscall *HandleRightMouseButtonDownUpdate)(Control *, int, int, int, int);
	DWORD gap2b1f;
	int(__thiscall *HandleRightMouseButtonUp)(Control *, int, int, int, int);
	int(__thiscall *HandleRightMouseButtonDoubleClick)(Control *, int, int, int, int);
	int(__thiscall *HandleKeyDown2)(Control *, int, int, int, int, int);
	int(__thiscall *HandleCharMessage2)(Control *, WPARAM, LPARAM);
	int(__thiscall *HandleChildControlEvent)(Control *, Control *, int, int, int);
	DWORD gap2b2;
	int(__thiscall *IsResponsibleForHandlingMouseEvent)(Control *, int, int);
	void(__thiscall *SetSelectionState)(Control *, int);
	DWORD SetTabInformation;
	DWORD AssignTabInformationToControlArray;
	DirectDrawBufferData *(__thiscall *GetBackBufferData)(Control *);
	DWORD _func3;
	DWORD _func4;
	int(__thiscall *UnknownRecursiveChildrenCheck)(Control *);
	DWORD _func6;
	DWORD _func7;
	DWORD _func8;
};
#pragma pack(pop)
