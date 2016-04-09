#pragma once

/* INCLUDES */

// Other includes
#include "DirectDrawBufferData.h"
#include "GameDataHandler.h"
#include "TechTreeElement.h"
#include <vector>
#include "DrawUtilities.h"

/* DEFINITIONS */

// Represents an abstract tech tree renderer.
class TechTreeRenderer
{
public:
	// Defines the different legend label IDs.
	// This enum is only for readability, DO NOT CHANGE IT! These IDs may be used to access rectangle arrays.
	enum class LegendLabelIndices : int
	{
		NotResearched = 0,
		Researched = 1,
		Units = 2,
		Buildings = 3,
		Researches = 4,
		NotAvailable = 5
	};

protected: // Member variables
	// The game data.
	GameDataHandler *_gameData;

	// The ID of the currently selected civ.
	int _selectedCivId;

	// The age count of the rendered tree.
	int _ageCount;

public:
	// Creates a new tech tree renderer for the given tech tree.
	// Parameteres:
	// -> gameData: The game data.
	TechTreeRenderer(GameDataHandler *gameData);

	// Draws the tree with the given offset for the current civ.
	// Parameters:
	// -> drawBuffer: The buffer the tree should be rendered to.
	// -> offsetX: The X position of the left screen side (> 0 => scroll right).
	// -> offsetY: The Y position of the top screen side (> 0 => scroll down).
	virtual void Draw(DirectDrawBufferData *drawBuffer, int offsetX, int offsetY) = 0;

	// Draws the popup label box at the given pixel coordinates.
	// Parameters:
	// -> drawBuffer: The buffer the box should be rendered to.
	// -> x: The X position of the popup label box.
	// -> y: The Y position of the popup label box.
	virtual void DrawPopupLabelBox(DirectDrawBufferData *drawBuffer, int x, int y) = 0;

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

	// Returns the position and size of the legend label with the given ID.
	// Parameters:
	// -> labelIndex: The label ID.
	virtual const Rect* GetLegendLabelRectangle(LegendLabelIndices labelIndex) = 0;

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