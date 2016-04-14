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
	void Constructor(int datFileHandle);

	// Destructor.
	~TechTreeData();
	void Destructor();

	// Updates the render states for the selected civ.
	// Parameters:
	// -> selectedCivId: The ID of the selected civ.
	// -> unknownGameAndPlayerData: Data given ingame to highlight currently available units and researches.
	void UpdateRenderStates(char selectedCivId, int unknownGameAndPlayerData);

	// Returns the root elements of the tech tree.
	const std::vector<TechTreeElement *> &GetRootElements();
};

// The data of the new tech tree. This variable is initialized when the game data is loaded, else its value is nullptr.
extern TechTreeData *_staticNewTechTreeDataObject;