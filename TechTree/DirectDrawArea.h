#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Standard includes
#include <ddraw.h>

// Other includes
#include "DirectDrawAreaNode.h"
#include "BitmapInfo.h"

/* DEFINITIONS */

// Class prototype to avoid include loops
class DirectDrawHandler;

#pragma pack(push, 1)
// Represents an DirectDraw buffer handler.
class DirectDrawArea : public GameType
{
protected: // Member variables
	DirectDrawHandler *_directDrawHandler;
	HWND _mainWindowHWnd;
	char *_lockedSurfaceMemoryAddress;
	BITMAPINFO256 *_bitmapInfo;
	HGDIOBJ _unknownGdiObject2;
	HGDIOBJ _unknownGdiObject1;
	int _width;
	int _height;
	DWORD _bytesPerLine;
	int _originPointAtBottom_NegateYAxis;
	RECT _maybeDrawArea;
	HDC _gdiContext;
	IDirectDrawSurface *_associatedDirectDrawSurface;
	DDSURFACEDESC _associatedDirectDrawSurfaceDesc;
	DirectDrawAreaNode *_listElement;
	char *_name;
	DWORD _dwordB4;
	BYTE _gapB8[4];
	DWORD _arrayWithHeightTimes4Elements1;
	DWORD _arrayWithHeightTimes4Elements2;
	DWORD _dwordC4;
	BYTE _gapC8[12];
	DWORD _dwordD4;
	DWORD _dwordD8;
	DWORD _heightTimes4;
	DWORD _dwordE0;
	DWORD _dwordE4;
	DWORD _primarySurfaceIsInVideoMemory;
	DWORD _dwordEC;
	DWORD _isPrimaryScreenBuffer;
	DWORD _dwordF4;
	DWORD _unknown_Add10ToHeight;
	BYTE _byteFC;
	BYTE _gapFD[3];
	DWORD _dword100;
	BYTE _byte104;

public:
	// Constructor. Creates a buffer data object.
	// Parameters:
	// -> name: The buffer name.
	// -> unknown: Unknown.
	DirectDrawArea(char *name, int unknown);

	// Destructor.
	~DirectDrawArea();

	// Locks the DirectDraw surface memory for drawing operations.
	// Parameters:
	// -> wait: Specifies if the function should block until the locking process is complete.
	char *LockAssociatedSurface(int wait);

	// Unlocks the previously locked DirectDraw surface memory.
	void UnlockAssociatedSurface();

	// Draws a filled rectangle with the given coordinates in the specified color.
	// Parameters:
	// -> left: Left bounding of the rectangle.
	// -> top: Top bounding of the rectangle.
	// -> right: Right bounding of the rectangle.
	// -> bottom: Bottom bounding of the rectangle.
	// -> color: The palette index of the color the rectnalge should be filled with.
	void DrawFilledRectangle(int left, int top, int right, int bottom, unsigned char color);

	// Inserts the buffer into the global buffer list, creates a surface and does some additional stuff.
	// Parameters:
	// -> directDrawHandler: The DirectDraw handler struct this buffer should be associated to.
	// -> clientWidth: The width of the buffer.
	// -> clientHeight: The height of the buffer.
	// -> unknown: Unknown.
	// -> isPrimaryScreenBuffer: Only true for the primary buffer which is directly sent to screen.
	bool InsertIntoBufferListAndCreateSurfaceAndDoUnknownStuff(DirectDrawHandler *directDrawHandler, int clientWidth, int clientHeight, int unknown, int isPrimaryScreenBuffer);

	// A function not yet understood.
	// Parameters:
	// -> left: Left coordinate of a rectangle.
	// -> right: Right coordinate of a rectangle.
	// -> top: Top coordinate of a rectangle.
	// -> bottom: Bottom coordinate of a rectangle.
	int sub_5A30A0(int left, int right, int top, int bottom);

	// Returns the direct draw handler associated with this object.
	DirectDrawHandler *GetDirectDrawHandler();

	// A function not yet understood. It seemingly copies the internal buffer to the specified back buffer.
	// Parameters:
	// -> backBuffer: The DirectDraw buffer the internal buffer should be rendered into.
	// -> xLeft: Unknown.
	// -> yTop: Unknown.
	// -> childRect: Unknown.
	// -> unknown: Unknown.
	void sub_5A31E0(DirectDrawArea *backBuffer, int xLeft, int yTop, RECT *childRect, int unknown);

	// Gets the associated GDI context.
	HDC CreateGdiContext();

	// Returns the created associated GDI context.
	HDC GetGdiContext();

	// Frees the associated GDI context.
	void DeleteGdiContext();
};
#pragma pack(pop)
