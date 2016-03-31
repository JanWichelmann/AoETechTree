/* INCLUDES */

// Class header
#include "Window.h"

/* FUNCTIONS */

void Window::__Install()
{
	// First call base function
	base::__Install();
}

Window *Window::Constructor(char *windowName)
{
	// Call original function
	return ((Window *(__thiscall *)(Window *, char *))0x00548030)(this, windowName);
}

void Window::Destructor()
{
	// Call original function
	((void(__thiscall *)(Window *))0x00548050)(this);
}

bool Window::PrepareParentWindowAndLoadStyleData(DirectDrawBufferData *backBuffer, char *styleResourceName, int styleResourceId, int unk)
{
	// Call original function
	return ((bool(__thiscall *)(Panel*, DirectDrawBufferData *, char *, int, int))0x00548060)(this, backBuffer, styleResourceName, styleResourceId, unk);
}