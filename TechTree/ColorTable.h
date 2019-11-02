#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an unknown class, probably palette related.
class ColorTable : public GameType
{
protected: // Member variables
	DWORD _VTable;
	int resource_id_;
	int type_;
	char* table_;
	int color_transform_base_;
	int unit_outline_color_;
	int selection_color_1_;
	int selection_color_2_;
	int minimap_color_1_;
	int minimap_color_2_;
	int minimap_color_3_;
	int text_color1_;
	int text_color2_;
	char text_color_r_;
	char text_color_g_;
	char text_color_b_;
	char reserved_;

public:
};
#pragma pack(pop)
