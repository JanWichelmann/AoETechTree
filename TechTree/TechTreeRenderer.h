#pragma once

/* INCLUDES */

// Other includes
#include "DirectDrawArea.h"
#include "GameDataHandler.h"
#include "TechTreeElement.h"
#include <vector>
#include "DrawUtilities.h"

/* DEFINITIONS */

// Represents an abstract tech tree renderer.
class TechTreeRenderer
{
protected: // Member variables
	// The game data.
	GameDataHandler *_gameData;

	// Pointer to a large chunk of game and player data, containing information about player colors, diplomacy, researched items etc.
	int _unknownGameAndPlayerData;

	// The ID of the currently selected civ.
	int _selectedCivId;

	// The age count of the rendered tree.
	int _ageCount;

public:
	// Creates a new tech tree renderer for the given tech tree.
	// Parameteres:
	// -> gameData: The game data.
	// -> unknownGameAndPlayerData: Data given ingame to highlight currently available units and researches.
	TechTreeRenderer(GameDataHandler *gameData, int unknownGameAndPlayerData);

	// Draws the tree with the given offset for the current civ.
	// Parameters:
	// -> drawBuffer: The buffer the tree should be rendered to.
	// -> offsetX: The X position of the left screen side (> 0 => scroll right).
	// -> offsetY: The Y position of the top screen side (> 0 => scroll down).
	virtual void Draw(DirectDrawArea *drawBuffer, int offsetX, int offsetY) = 0;

	// Draws the popup label box at the given pixel coordinates.
	// Parameters:
	// -> drawBuffer: The buffer the box should be rendered to.
	// -> x: The X position of the popup label box.
	// -> y: The Y position of the popup label box.
	virtual void DrawPopupLabelBox(DirectDrawArea *drawBuffer, int x, int y) = 0;

	// Sets the currently selected civ.
	virtual void SetCurrentCiv(int civId);

	// Returns the full width of the tree (including margins).
	virtual int GetFullWidth() = 0;

	// Returns the full height of the tree (including margins).
	virtual int GetFullHeight() = 0;

	// Returns the position and size of the civ bonus label.
	virtual const Rect* GetCivBonusLabelRectangle() = 0;

	// Returns the position and size of the civ selection combobox.
	virtual const Rect* GetCivSelectionComboBoxRectangle() = 0;

	// Returns the position and size of the "game civs" label above the civ selection combobox.
	virtual const Rect* GetGameCivsLabelRectangle() = 0;

	// Returns the position and size of the "Not Researched" legend label.
	virtual const Rect* GetLegendNotResearchedLabelRectangle() = 0;

	// Returns the position and size of the "Researched" legend label.
	virtual const Rect* GetLegendResearchedLabelRectangle() = 0;

	// Returns the count of the node type labels in the legend.
	virtual const int GetLegendNodeTypeCount() = 0;

	// Returns the position and size of the legend node type label with the given index.
	// Parameters:
	// -> labelIndex: The label index.
	virtual const Rect* GetLegendNodeTypeLabelRectangle(int labelIndex) = 0;

	// Returns the DLL string ID of the legend node type label with the given index.
	// Parameters:
	// -> labelIndex: The label index.
	virtual const int GetLegendNodeTypeLabelDllId(int labelIndex) = 0;

	// Returns the position and size of the "Disabled" legend label.
	virtual const Rect* GetLegendDisabledLabelRectangle() = 0;

	// Returns the position of the age label rectangle for the given age, line and side.
	// Parameters:
	// -> age: The age the label belongs to.
	// -> side: false for the left age bar, true for the right age bar.
	// -> line: false for the upper label line, true for the lower line.
	virtual const Rect* GetAgeLabelRectangle(int age, bool side, bool line) = 0;

	// Computes and returns the draw data of the box surrounding the popup label.
	// The position hereby is the relative offset of the label to the top left of the box, the size is the size of the box itself.
	// Parameters:
	// -> popupLabelSize: The size of the popup label.
	virtual Rect UpdateAndGetPopupLabelBoxDrawData(Size &popupLabelSize) = 0;

	// Returns the count of the rendered ages.
	virtual int GetAgeCount();

	// Returns the element at the given pixel position.
	// Parameters:
	// -> x: The x position where an element shall be searched.
	// -> y: The y position where an element shall be searched.
	virtual TechTreeElement* GetElementAtPosition(int x, int y) = 0;

	// Marks the given element as selected.
	// Parameters:
	// -> element: The element to be selected.
	virtual void SetSelectedElement(TechTreeElement *element) = 0;
};