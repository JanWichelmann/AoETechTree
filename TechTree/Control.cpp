/* INCLUDES */

// Class header
#include "Control.h"

/* FUNCTIONS */

void Control::__Install()
{
	// First call base function
	base::__Install();
}

void Control::operator delete(void *obj)
{
	// Call virtual destructor function
	static_cast<Control *>(obj)->_VTable->ScalarDeletingDestructor(static_cast<Control *>(obj), 1);
}

void Control::AssignIdToControlAndMoveInParentChildrenList(char idSelectionMode, short id)
{
	// Call original function
	((void(__thiscall *)(Control *, char, short))0x005629E0)(this, idSelectionMode, id);
}

int Control::HandleWindowsMessage(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam)
{
	// Call original function
	return ((int(__thiscall *)(Control *, HWND, int, WPARAM, LPARAM))0x00561880)(this, hWnd, msg, wParam, lParam);
}

int Control::HandleChildControlEvent(Control *triggeringControl, int code, int data1, int data2)
{
	// Call original function
	return ((int(__thiscall *)(Control *, Control *, int, int, int))0x00562760)(this, triggeringControl, code, data1, data2);
}

int Control::DoUpdate()
{
	// Call original function
	return ((int(__thiscall *)(Control *))0x00561D10)(this);
}

void Control::UpdateSelectedSubControl(Control *newSelectedControl)
{
	// Call original function
	((void(__thiscall *)(Control *, Control *))0x00562950)(this, newSelectedControl);
}

char *Control::GetControlTypeName()
{
	// Return type name
	return _controlTypeName;
}

void Control::UpdatePositionAndSizeData(int posX, int posY, int width, int height)
{
	// Call virtual function
	_VTable->UpdatePositionAndSizeData(this, posX, posY, width, height);
}

Control::ControlType Control::GetTypeIdentifier()
{
	// Return type
	return _controlTypeIdentifier;
}

Rect& Control::GetPositionAndSizeData()
{
	// Create and return rect
	return Rect(_positionX2, _positionY2, _width1, _height1);
}

void Control::SetFillBackground(char fill)
{
	// Set mode
	_fillBackground = fill;
}

int Control::GetWidth()
{
	// Return width
	return _width1;
}

int Control::GetHeight()
{
	// Return height
	return _height1;
}