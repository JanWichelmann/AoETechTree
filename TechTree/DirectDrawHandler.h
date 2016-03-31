#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Standard includes
#include <ddraw.h>

// Other includes
#include "DirectDrawBufferData.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an handler for the main DirectDraw instance.
// Research type name: WindowInformation.
class DirectDrawHandler : public GameType
{
protected: // Member variables
	HINSTANCE _applicationInstance;
	HWND _mainWindowHWnd;
	HPALETTE _mainPalette;
	DirectDrawBufferData *_backBufferBufferData;
	DirectDrawBufferData *_primarySurfaceBufferData;
	DirectDrawBufferDataListElement *_firstBufferDataListElement;
	IDirectDraw *_directDrawObject;
	IDirectDrawSurface *_primaryDirectDrawSurface;
	IDirectDrawClipper *_directDrawClipper;
	IDirectDrawPalette *_directDrawMainPalette;
	int _systemMemoryCmdParamSet;
	int _mainWindowClientWidth;
	int _mainWindowClientHeight;
	int _bitsPerPixel;
	int _initializationStatus;
	char _atLeast8BitPerPixelPlus1;
	char _fullScreenModePlus1;
	char _unknownValue1b;
	char _unknownValue1c;
	int _unknownFullScreenRelated;
	int _displayIsBankSwitched;
	int _transparentColorKeyBlittingForSourceEnabled;
	char _unknown2a[8];
	int _has_8Bit_640x480_Surface;
	int _has_8Bit_800x600_Surface;
	int _has_8Bit_1024x768_Surface;
	int _has_8Bit_1280x1024_Surface;
	int _has_8Bit_1600x1200_Surface;
	int _has_8Bit_320x200_Surface;
	int _has_8Bit_320x240_Surface;
	int _has_16Bit_320x200_Surface;
	int _has_16Bit_320x240_Surface;
	int _has_16Bit_640x480_Surface;
	int _has_16Bit_800x600_Surface;
	int _has_16Bit_1024x768_Surface;
	int _has_16Bit_1600x1200_Surface;
	int _has_24Bit_320x200_Surface;
	int _has_24Bit_320x240_Surface;
	int _has_24Bit_640x480_Surface;
	int _has_24Bit_800x600_Surface;
	int _has_24Bit_1024x768_Surface;
	int _has_24Bit_1600x1200_Surface;
	int _has_32Bit_320x200_Surface;
	int _has_32Bit_320x240_Surface;
	int _has_32Bit_640x480_Surface;
	int _has_32Bit_800x600_Surface;
	int _has_32Bit_1024x768_Surface;
	int _has_32Bit_1600x1200_Surface;
	PALETTEENTRY _mainPaletteData[256];

public:
	// Returns the main palette handle.
	HPALETTE GetMainPalette();
};
#pragma pack(pop)

