#pragma once

/* INCLUDES */

// Base class header
#include "Panel.h"

// Other includes


/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an abstract game window.
// Research type name: FullscreenWindow.
class Window : public Panel
{
private:
	typedef Panel base;

protected: // Member variables
	

public:
	// Hide base class install function.
	static void __Install();

	// Constructor.
	// Parameters:
	// -> windowName: The window type description (e.g "game setup screen").
	Window *Constructor(char *windowName);

	// Destructor.
	void Destructor();

	// Loads the specified window style file and assigns its properties.
	// Parameters:
	// -> backBuffer: The window's own back buffer.
	// -> styleResourceName: The resource file name (may be empty if ID is given).
	// -> styleResourceId: The resource file id.
	// -> unk: Unknown.
	bool PrepareParentWindowAndLoadStyleData(DirectDrawBufferData *backBuffer, char *styleResourceName, int styleResourceId, int unk);

	// Returns a reference to the back buffer of this window.
	DirectDrawBufferData *GetBackBufferData();
};
#pragma pack(pop)