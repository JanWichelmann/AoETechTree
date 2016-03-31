#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes
#include "TechTreeElement.h"
#include <vector>

/* DEFINITIONS */

// Loads and manages the tech tree data from the DAT file.
class TechTreeData : GameType
{
private:
	typedef GameType base;

protected: // Member variables
	// The root elements of the tech tree.
	std::vector<TechTreeElement *> _rootElements;

public:
	// Hide base class install function.
	static void __Install();

	// Constructor. Reads the tech tree data from the given DAT file handle.
	// Parameters:
	// -> datFileHandle: A handle to an uncompressed DAT file.
	TechTreeData(int datFileHandle);
	static TechTreeData * __stdcall Constructor(int datFileHandle);

	// Updates the render states for the selected civ.
	// Parameters:
	// -> selectedCivId: The ID of the selected civ.
	void UpdateRenderStates(char selectedCivId);

	// Returns the root elements of the tech tree.
	const std::vector<TechTreeElement *> &GetRootElements();
};