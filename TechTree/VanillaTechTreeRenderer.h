#pragma once

/* INCLUDES */

// Base class header
#include "TechTreeRenderer.h"

// Other includes
#include "SlpFileElement.h"
#include "FontData.h"


/* DEFINITIONS */

// Represents a renderer for the vanilla tech tree.
// This renderer assumes that there are at most two vertical elements per age!
class VanillaTechTreeRenderer : public TechTreeRenderer
{
private:
	typedef TechTreeRenderer base;

private:
	// The space between to tech tree elements.
	// WARNING: When you want to change this to an odd value, you have to use floating point division in the GetElementAtPosition function, else you'll get precision errors.
	static const int ELEMENT_SPACING = 4;

	// The inner padding of the popup label box.
	static const int POPUP_LABEL_BOX_PADDING = 8;

protected: // Member variables
	// The research icons.
	SlpFileElement *_researchIcons;

	// The creatable unit icons.
	SlpFileElement *_creatableIcons;

	// The building icons.
	SlpFileElement *_buildingIcons;

	// The element node graphics.
	SlpFileElement *_nodeGraphics;

	// The element node caption font.
	FontData *_nodeFont;

	// The SLP containing the legend and the ages bar.
	SlpFileElement *_legendAndAgesSlp;

	// The index of the legend frame for the current resolution.
	int _legendFrameIndex;

	// The width of the legend frame for the current resolution.
	int _legendFrameWidth;

	// The height of the legend frame for the current resolution.
	int _legendFrameHeight;

	// The index of the age bar frame for the current resolution.
	int _agesFrameIndex;

	// The width of the age bar frame for the current resolution.
	int _agesFrameWidth;

	// The height of the age bar frame for the current resolution.
	int _agesFrameHeight;

	// The SLP containing the background tiles.
	SlpFileElement *_tileSlp;

	// The index of the background tile frame for the current resolution.
	int _tileFrameIndex;

	// The width of the background tile frame for the current resolution.
	int _tileFrameWidth;

	// The height of the background tile frame for the current resolution.
	int _tileFrameHeight;

	// The SLP containing the "disable" symbol of the legend.
	SlpFileElement *_legendDisableSlp;

	// The draw position of the legend "disable" symbol for the current resolution.
	Point _legendDisableSlpDrawPosition;

	// The vertical draw positions for each tree level (depends on the size of the background tiling graphic).
	int *_verticalDrawOffsets;

	// The age label draw rectangles type.
	using AgeLabelRectanglesType = Rect(*)[2][2];

	// The age label draw rectangles: [age][side][line].
	AgeLabelRectanglesType _ageLabelRectangles;

	// The width of the rendered tree (not pixels, leaf count here).
	int _treeWidth;

	// A matrix for the element positioning.
	// Even column indices: Elements at integer positions.
	// Odd column indices: Elements at half positions.
	TechTreeElement ***_treeLayoutMatrix;

	// The size of the drawing window. Used for more efficient drawing.
	Size _windowSize;

	// The rectangle of the civ bonus label.
	Rect _civBonusLabelRectangle;

	// The rectangle of the civ selection combo box.
	Rect _civSelectionComboBoxRectangle;

	// The rectangle of the "game civs" label above the civ selection combo box.
	Rect _gameCivsLabelRectangle;

	// The legend label rectangles.
	Rect _legendLabelRectangles[6];

	// The popup label box size.
	Size _popupLabelBoxSize;

	// The currently selected (or hovered) element.
	TechTreeElement *_selectedElement;

	// The currently selected (or hovered) element's tree path (including the element itself).
	std::vector<TechTreeElement *> _selectedElementPath;

	// The bevel colors of the popup label box.
	unsigned char _popupLabelBoxBevelColors[6];

public:
	// Creates a new vanilla tech tree renderer for the given tech tree.
	// Parameteres:
	// -> gameData: The game data.
	// -> windowSize: The size of the render window.
	VanillaTechTreeRenderer(GameDataHandler *gameData, Size &windowSize);

	// Destructor.
	~VanillaTechTreeRenderer();

	// Draws the tree with the given offset for the current civ.
	// Parameters:
	// -> drawBuffer: The buffer the tree should be rendered to.
	// -> offsetX: The X position of the left screen side (> 0 => scroll right).
	// -> offsetY: The Y position of the top screen side (> 0 => scroll down).
	virtual void Draw(DirectDrawBufferData *drawBuffer, int offsetX, int offsetY);

	// Draws the popup label box at the given pixel coordinates.
	// Parameters:
	// -> drawBuffer: The buffer the box should be rendered to.
	// -> x: The X position of the popup label box.
	// -> y: The Y position of the popup label box.
	virtual void DrawPopupLabelBox(DirectDrawBufferData *drawBuffer, int x, int y);

	// Sets the currently selected civ.
	virtual void SetCurrentCiv(int civId);

	// Computes the sub tree of the given element and returns its width.
	// Parameters:
	// -> element: The current element which sub tree should be computed.
	// -> startColumnIndex: The matrix column index where the new sub tree can start. This should be even, if not, there was an error.
	// -> secondInAge: Specifies if the element is the first vertical element in the current age or the second one.
	int ComputeSubTree(TechTreeElement *element, int startColumnIndex, bool secondInAge);

	// Renders the given element an its sub tree.
	// Parameters:
	// -> element: The current element which should be rendered.
	// -> drawBuffer: The buffer the sub tree should be rendered to.
	// -> offsetX: The X position of the left screen side (> 0 => scroll right).
	// -> offsetY: The Y position of the top screen side (> 0 => scroll down).
	void RenderSubTree(TechTreeElement *element, DirectDrawBufferData *drawBuffer, int offsetX, int offsetY);

	// Returns the full width of the tree (including margins).
	virtual int GetFullWidth();

	// Returns the full height of the tree (including margins).
	virtual int GetFullHeight();

	// Returns the position and size of the civ bonus label.
	virtual const Rect* GetCivBonusLabelRectangle();

	// Returns the position and size of the civ selection combobox.
	virtual const Rect* GetCivSelectionComboBoxRectangle();

	// Returns the position and size of the "game civs" label above the civ selection combobox.
	virtual const Rect* GetGameCivsLabelRectangle();

	// Returns the position and size of the legend label with the given ID.
	// Parameters:
	// -> labelIndex: The label ID.
	virtual const Rect* GetLegendLabelRectangle(LegendLabelIndices labelIndex);

	// Returns the position of the age label rectangle for the given age, line and side.
	// Parameters:
	// -> age: The age the label belongs to.
	// -> side: false for the left age bar, true for the right age bar.
	// -> line: false for the upper label line, true for the lower line.
	virtual const Rect* GetAgeLabelRectangle(int age, bool side, bool line);

	// Computes and returns the draw data of the box surrounding the popup label.
	// The position hereby is the relative offset of the label to the top left of the box, the size is the size of the box itself.
	// Parameters:
	// -> popupLabelSize: The size of the popup label.
	virtual Rect& UpdateAndGetPopupLabelBoxDrawData(Size &popupLabelSize);

	// Returns the element at the given pixel position.
	// Parameters:
	// -> x: The x position where an element shall be searched.
	// -> y: The y position where an element shall be searched.
	virtual TechTreeElement* GetElementAtPosition(int x, int y);

	// Marks the given element as selected.
	// Parameters:
	// -> element: The element to be selected.
	virtual void SetSelectedElement(TechTreeElement *element);
};