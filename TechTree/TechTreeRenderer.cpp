/* INCLUDES */

// Class header
#include "TechTreeRenderer.h"

// Other includes
#include <stack>

/* FUNCTIONS */

TechTreeRenderer::TechTreeRenderer(GameDataHandler *gameData)
{
	// Remember parameters
	_gameData = gameData;

	// Initialize selected civ member
	_selectedCivId = 0;

	// Get age count by determining the maximum specified age.
	_ageCount = 1;
	std::stack<TechTreeElement *> remainingElements;
	for(TechTreeElement *currRootElement : _gameData->_techTree->GetRootElements())
		remainingElements.push(currRootElement);
	while(!remainingElements.empty())
	{
		// Pop top element
		TechTreeElement *currElement = remainingElements.top();
		remainingElements.pop();

		// New maximum age?
		if(_ageCount < currElement->_age + 1)
			_ageCount = currElement->_age + 1;

		// Iterate and push children
		for(TechTreeElement *currChild : currElement->_children)
			remainingElements.push(currChild);
	}
}

void TechTreeRenderer::SetCurrentCiv(int civId)
{
	// Remember civ ID
	_selectedCivId = civId;

	// Update render states
	_gameData->_techTree->UpdateRenderStates(civId);
}

int TechTreeRenderer::GetAgeCount()
{
	// Return age count
	return _ageCount;
}