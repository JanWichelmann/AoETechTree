#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an unknown class type with a length of 1064 bytes. It is related to the DirectDrawArea class and widely used.

struct BITMAPINFO256 {
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD bmiColors[256];
};
#pragma pack(pop)
