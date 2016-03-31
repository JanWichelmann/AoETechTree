/* INCLUDES */

// Class header
#include "DirectDrawBufferData.h"

/* FUNCTIONS */

DirectDrawBufferData::DirectDrawBufferData(char *name, int unknown)
{
	// Call original function
	((DirectDrawBufferData *(__thiscall *)(DirectDrawBufferData*, char *, int))0x005A2250)(this, name, unknown);
}

DirectDrawBufferData::~DirectDrawBufferData()
{
	// Call original function
	((void(__thiscall *)(DirectDrawBufferData *))0x005A2390)(this);
}

char *DirectDrawBufferData::LockAssociatedSurface(int wait)
{
	// Call original function
	return ((char *(__thiscall *)(DirectDrawBufferData*, char *, int))0x005A2700)(this, nullptr, wait);
}

void DirectDrawBufferData::UnlockAssociatedSurface()
{
	// Call original function
	((void(__thiscall *)(DirectDrawBufferData*, char *))0x005A2780)(this, nullptr);
}

void DirectDrawBufferData::DrawFilledRectangle(int left, int top, int right, int bottom, unsigned char color)
{
	// Call original function
	((void(__thiscall *)(DirectDrawBufferData*, int, int, int, int, unsigned char))0x005A3DF0)(this, left, top, right, bottom, color);
}

bool DirectDrawBufferData::InsertIntoBufferListAndCreateSurfaceAndDoUnknownStuff(DirectDrawHandler *directDrawHandler, int clientWidth, int clientHeight, int unknown, int isPrimaryScreenBuffer)
{
	// Call original function
	return ((bool(__thiscall *)(DirectDrawBufferData*, DirectDrawHandler *, int, int, int, int))0x005A24D0)(this, directDrawHandler, clientWidth, clientHeight, unknown, isPrimaryScreenBuffer);
}

int DirectDrawBufferData::sub_5A30A0(int left, int right, int top, int bottom)
{
	// Call original function
	return ((int(__thiscall *)(DirectDrawBufferData*, int, int, int, int))0x005A30A0)(this, left, right, top, bottom);
}

DirectDrawHandler *DirectDrawBufferData::GetDirectDrawHandler()
{
	// Return handler
	return _directDrawHandler;
}

void DirectDrawBufferData::sub_5A31E0(DirectDrawBufferData *backBuffer, int xLeft, int yTop, RECT *childRect, int unknown)
{
	// Call original function
	((void(__thiscall *)(DirectDrawBufferData*, DirectDrawBufferData *, int, int, RECT *, int))0x005A31E0)(this, backBuffer, xLeft, yTop, childRect, unknown);
}

HDC DirectDrawBufferData::CreateGdiContext()
{
	// Call original function
	return ((HDC(__thiscall *)(DirectDrawBufferData *, char *))0x005A27C0)(this, nullptr);
}

HDC DirectDrawBufferData::GetGdiContext()
{
	// Return context
	return _gdiContext;
}

void DirectDrawBufferData::DeleteGdiContext()
{
	// Call original function
	((void(__thiscall *)(DirectDrawBufferData *, char *))0x005A2810)(this, nullptr);
}