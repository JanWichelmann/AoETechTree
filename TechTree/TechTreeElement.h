#pragma once

/* INCLUDES */

// Other includes
#include <vector>
#include "DrawUtilities.h"

/* DEFINITIONS */

// Represents a single tech tree element.
class TechTreeElement
{
	// Allow tech tree and renderers to access the element for efficiency and readability purposes
	friend class TechTreeWindow;
	friend class TechTreeRenderer;
	friend class VanillaTechTreeRenderer;

public:
	// The different types a tech tree element can have.
	enum class ItemType : char
	{
		Research = 0,
		Creatable = 1,
		Building = 2
	};

	// The possible tech tree element render modes.
	enum class ItemRenderMode : char
	{
		// Standard mode. If the element is disabled, it is grayed out.
		Standard = 0,

		// If the element is disabled, it is completely omitted on drawing (including positioning).
		HideIfDisabled = 1
	};

	// The current tech tree element render states.
	enum class ItemRenderState : char
	{
		Visible = 0,
		Disabled = 1,
		Hidden = 2
	};

private:
	// Defines an entry of the requirement list.
	class RequiredElement
	{
	public:
		// The element type.
		ItemType _elementType;

		// The ID of the corresponding object.
		short _elementObjectID;

		// The element name (white text on each element of the vanilla tech tree). Automatically set when updating the current civ.
		char _elementNameFirstLine[256];

		// Optional. The second line of the element name.
		char _elementNameSecondLine[256];

	public:
		// Constructor. Reads the element data from the given DAT file handle.
		// Parameters:
		// -> datFileHandle: A handle to an uncompressed DAT file.
		RequiredElement(int datFileHandle);

		// Destructor.
		~RequiredElement();

		// Updates the display name for the selected civ.
		// Parameters:
		// -> selectedCivId: The ID of the selected civ.
		void UpdateDisplayName(char selectedCivId);
	};

protected: // Member variables
	// The element type.
	ItemType _elementType;

	// The ID of the corresponding object.
	short _elementObjectID;

	// The age of the element.
	char _age;

	// The element render mode.
	ItemRenderMode _renderMode;

	// The element render state (used for more efficient rendering).
	ItemRenderState _renderState;

	// The child elements.
	std::vector<TechTreeElement *> _children;

	// The IDs of the civs disabling this element.
	std::vector<char> _disableCivs;

	// The types and IDs of required elements. These don't need to be real tree elements.
	std::vector<RequiredElement *> _requiredElements;

	// The element render position (precomputed for performance reasons).
	// It doesn't need to be a absolute pixel position; this depends on the renderer.
	Point _renderPosition;

	// The element name (white text on each element of the vanilla tech tree). Automatically set when updating the render state.
	char _elementNameFirstLine[256];

	// Optional. The second line of the element name.
	char _elementNameSecondLine[256];

public:
	// Constructor. Reads the tech tree element data from the given DAT file handle.
	// Parameters:
	// -> datFileHandle: A handle to an uncompressed DAT file.
	TechTreeElement(int datFileHandle);

	// Destructor.
	~TechTreeElement();

	// Updates the render state for the selected civ.
	// Parameters:
	// -> selectedCivId: The ID of the selected civ.
	void UpdateRenderState(char selectedCivId);
};