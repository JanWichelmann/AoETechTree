/* INCLUDES */

// Class header
#include "DirectDrawArea.h"

/* FUNCTIONS */

DirectDrawArea::DirectDrawArea(char *name, int unknown)
{
	// Call original function
	((DirectDrawArea *(__thiscall *)(DirectDrawArea*, char *, int))0x005A2250)(this, name, unknown);
}

DirectDrawArea::~DirectDrawArea()
{
	// Call original function
	((void(__thiscall *)(DirectDrawArea *))0x005A2390)(this);
}

char *DirectDrawArea::LockAssociatedSurface(int wait)
{
	// Call original function
	return ((char *(__thiscall *)(DirectDrawArea*, char *, int))0x005A2700)(this, nullptr, wait);
}

void DirectDrawArea::UnlockAssociatedSurface()
{
	// Call original function
	((void(__thiscall *)(DirectDrawArea*, char *))0x005A2780)(this, nullptr);
}

void DirectDrawArea::DrawFilledRectangle(int left, int top, int right, int bottom, unsigned char color)
{
	// Call original function
	((void(__thiscall *)(DirectDrawArea*, int, int, int, int, unsigned char))0x005A3DF0)(this, left, top, right, bottom, color);
}

bool DirectDrawArea::InsertIntoBufferListAndCreateSurfaceAndDoUnknownStuff(DirectDrawHandler *directDrawHandler, int clientWidth, int clientHeight, int unknown, int isPrimaryScreenBuffer)
{
	// Call original function
	return ((bool(__thiscall *)(DirectDrawArea*, DirectDrawHandler *, int, int, int, int))0x005A24D0)(this, directDrawHandler, clientWidth, clientHeight, unknown, isPrimaryScreenBuffer);
}

int DirectDrawArea::SetClipRect2(int left, int right, int top, int bottom)
{
	// Call original function
	return ((int(__thiscall *)(DirectDrawArea*, int, int, int, int))0x005A30A0)(this, left, right, top, bottom);
}

DirectDrawHandler *DirectDrawArea::GetDirectDrawHandler()
{
	// Return handler
	return _directDrawHandler;
}

void DirectDrawArea::Copy(DirectDrawArea *backBuffer, int xLeft, int yTop, RECT *childRect, int unknown)
{
	// Call original function
	((void(__thiscall *)(DirectDrawArea*, DirectDrawArea *, int, int, RECT *, int))0x005A31E0)(this, backBuffer, xLeft, yTop, childRect, unknown);
}

HDC DirectDrawArea::CreateGdiContext()
{
	// Call original function
	return ((HDC(__thiscall *)(DirectDrawArea *, char *))0x005A27C0)(this, nullptr);
}

HDC DirectDrawArea::GetGdiContext()
{
	// Return context
	return _gdiContext;
}

void DirectDrawArea::DeleteGdiContext()
{
	// Call original function
	((void(__thiscall *)(DirectDrawArea *, char *))0x005A2810)(this, nullptr);
}