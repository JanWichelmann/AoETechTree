#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes
#include "Control.h"
#include "ControlListElement.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an SLP file.
class StaticControlContainer : GameType
{
protected: // Member variables
	int _VTable;
	Control *UnknownControl1;
	Control *UnknownControl2;
	Control *UnknownControl3;
	Control *CurrentlyDisplayedControl;
	ControlListElement *ControlListBegin;
	int ListSize;
	Control *UnknownControl5;
	HPALETTE Palettes[10];
	char PaletteFileNames[2600];
	int PaletteReferenceCounters[10];
	int PaletteResourceIds[10];
	HIMC OldInputContext;
	int HasInputContext;
	int UnknownValue1;
	int Unknown_ImeVisibilityChecked;
	int ImeIsVisible;
	int MouseEnabled;
	int UnknownValue4;
	int ColorBackground;
	int ColorText;

public:
	// Switches to the control with the given type name.
	// Parameters:
	// -> controlTypeName: The type name of the control.
	// -> unknown: Unknown redrawing related parameter.
	bool SwitchToControl(char *controlTypeName, int unknown);

	// Deletes the control with the specified type name.
	// Parameters:
	// -> controlTypeName: The type name of the control.
	int RemoveControlFromListWithDestructorCall(char *controlTypeName);

	// Returns the static control container handle.
	static StaticControlContainer *GetStaticHandle();
};
#pragma pack(pop)