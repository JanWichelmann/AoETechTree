/* INCLUDES */

// Class header
#include "VanillaTechTreeRenderer.h"

// Other includes
#include <algorithm>
#include <functional>
#include "Game.h"
#include "DirectDrawHandler.h"


/* FUNCTIONS */

VanillaTechTreeRenderer::VanillaTechTreeRenderer(GameDataHandler *gameData, Size &windowSize, int unknownGameAndPlayerData)
	: TechTreeRenderer(gameData, unknownGameAndPlayerData)
{
	// Get design data
	_designData = _staticNewTechTreeDataObject->GetDesignData();

	// Load icon SLPs
	_researchIcons = new SlpFileElement("btntech.shp", 50729);
	_creatableIcons = new SlpFileElement("ico_unit.shp", 50730);
	_buildingIcons = new SlpFileElement("ico_bld2.shp", 50706);

	// Load node SLP
	_nodeGraphics = new SlpFileElement(_designData->_nodeSlpFileName, _designData->_nodeSlpId);

	// Load legend SLP
	_legendAndAgesSlp = new SlpFileElement(_designData->_legendAgesSlpFileName, _designData->_legendAgesSlpId);

	// Load tile SLP
	_tileSlp = new SlpFileElement(_designData->_tileSlpFileName, _designData->_tileSlpId);

	// Load legend "disable" SLP
	_legendDisableSlp = new SlpFileElement(_designData->_legendDisableSlpFileName, _designData->_legendDisableSlpId);

	// Set resolution specific position values
	_verticalDrawOffsets = new int[_ageCount * 2];
	_ageLabelRectangles = new Rect[_ageCount][2][2];
	_windowSize = windowSize;
	int resHeight = 0;
	{
		// Find resolution entry with nearest minimum height
		for(auto &rConf : _designData->_resolutionData)
			if(rConf.first > resHeight && rConf.first <= _windowSize.Y)
				resHeight = rConf.first;

		// Frame indices
		_legendFrameIndex = _designData->_resolutionData.at(resHeight)->_legendFrameIndex;
		_agesFrameIndex = _designData->_resolutionData.at(resHeight)->_ageFrameIndex;
		_tileFrameIndex = _designData->_resolutionData.at(resHeight)->_tileFrameIndex;

		// Control draw positions
		_legendDisableSlpDrawPosition = _designData->_resolutionData.at(resHeight)->_legendDisableSlpDrawPosition;
		_civBonusLabelRectangle = _designData->_resolutionData.at(resHeight)->_civBonusLabelRectangle;
		_civSelectionComboBoxRectangle = _designData->_resolutionData.at(resHeight)->_civSelectionComboBoxRectangle;
		_gameCivsLabelRectangle = _designData->_resolutionData.at(resHeight)->_civSelectionTitleLabelRectangle;

		// Legend labels
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotResearched)] = _designData->_resolutionData.at(resHeight)->_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotResearched)];
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researched)] = _designData->_resolutionData.at(resHeight)->_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researched)];
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Units)] = _designData->_resolutionData.at(resHeight)->_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Units)];
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Buildings)] = _designData->_resolutionData.at(resHeight)->_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Buildings)];
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researches)] = _designData->_resolutionData.at(resHeight)->_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researches)];
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotAvailable)] = _designData->_resolutionData.at(resHeight)->_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotAvailable)];

		// Age draw heights
		for(int i = 0; i < std::min(_ageCount * 2, static_cast<int>(_designData->_resolutionData.at(resHeight)->_verticalDrawOffsets.size())); ++i)
			_verticalDrawOffsets[i] = _designData->_resolutionData.at(resHeight)->_verticalDrawOffsets[i];

		// Age labels
		for(int i = 0; i < std::min(_ageCount * 2, static_cast<int>(_designData->_resolutionData.at(resHeight)->_ageLabelRectangles.size())); ++i)
			_ageLabelRectangles[i / 2][0][i % 2] = _designData->_resolutionData.at(resHeight)->_ageLabelRectangles[i];
	}

	// Calculate missing age draw offsets
	int definedDrawOffsetsCount = static_cast<int>(_designData->_resolutionData.at(resHeight)->_verticalDrawOffsets.size());
	if(definedDrawOffsetsCount % 2 == 1)
	{
		// Calculate second offset
		_verticalDrawOffsets[definedDrawOffsetsCount] = _verticalDrawOffsets[definedDrawOffsetsCount - 1] + (_verticalDrawOffsets[definedDrawOffsetsCount - 2] - _verticalDrawOffsets[definedDrawOffsetsCount - 3]);
		++definedDrawOffsetsCount;
	}
	for(int i = definedDrawOffsetsCount / 2; i < _ageCount; ++i)
	{
		// Use difference values from age #3
		_verticalDrawOffsets[2 * i] = _verticalDrawOffsets[2 * i - 1] + (_verticalDrawOffsets[definedDrawOffsetsCount - 2] - _verticalDrawOffsets[definedDrawOffsetsCount - 3]);
		_verticalDrawOffsets[2 * i + 1] = _verticalDrawOffsets[2 * i] + (_verticalDrawOffsets[definedDrawOffsetsCount - 1] - _verticalDrawOffsets[definedDrawOffsetsCount - 2]);
	}

	// Calculate missing age label rectangles
	int definedAgeLabelRectanglesCount = static_cast<int>(_designData->_resolutionData.at(resHeight)->_ageLabelRectangles.size());
	if(definedAgeLabelRectanglesCount % 2 == 1)
	{
		// Calculate second label rectangle
		_ageLabelRectangles[definedAgeLabelRectanglesCount / 2][0][1] = Rect(_ageLabelRectangles[definedAgeLabelRectanglesCount / 2 - 1][0][1].X, _ageLabelRectangles[definedAgeLabelRectanglesCount / 2][0][0].Y + (_ageLabelRectangles[definedAgeLabelRectanglesCount / 2 - 1][0][1].Y - _ageLabelRectangles[definedAgeLabelRectanglesCount / 2 - 1][0][0].Y), _ageLabelRectangles[definedAgeLabelRectanglesCount / 2 - 1][0][1].Width, _ageLabelRectangles[definedAgeLabelRectanglesCount / 2 - 1][0][1].Height);
		++definedAgeLabelRectanglesCount;
	}
	for(int i = definedAgeLabelRectanglesCount / 2; i < _ageCount; ++i)
	{
		// Calculate rectangles
		_ageLabelRectangles[i][0][0] = Rect(_ageLabelRectangles[i - 1][0][0].X, _ageLabelRectangles[i - 1][0][1].Y + (_ageLabelRectangles[i - 1][0][0].Y - _ageLabelRectangles[i - 2][0][1].Y), _ageLabelRectangles[i - 1][0][0].Width, _ageLabelRectangles[i - 1][0][0].Height);
		_ageLabelRectangles[i][0][1] = Rect(_ageLabelRectangles[i - 1][0][1].X, _ageLabelRectangles[i][0][0].Y + (_ageLabelRectangles[i - 1][0][1].Y - _ageLabelRectangles[i - 1][0][0].Y), _ageLabelRectangles[i - 1][0][1].Width, _ageLabelRectangles[i - 1][0][1].Height);
	}

	// Get some SLP frame sizes
	_legendAndAgesSlp->GetFrameSize(_agesFrameIndex, &_agesFrameWidth, &_agesFrameHeight);
	_tileSlp->GetFrameSize(_tileFrameIndex, &_tileFrameWidth, &_tileFrameHeight);
	_legendAndAgesSlp->GetFrameSize(_legendFrameIndex, &_legendFrameWidth, &_legendFrameHeight);

	// Load node caption font
	_nodeFont = (*_staticGameObjectPointer)->GetFontWithIndex(_designData->_nodeFontIndex);

	// Initialize tree computation variables
	_treeWidth = 0;
	_treeMatrixWidth = 0;
	_treeLayoutMatrix = new TechTreeElement**[_ageCount * 2](); // Filled later
}

VanillaTechTreeRenderer::~VanillaTechTreeRenderer()
{
	// Free SLPs
	delete _researchIcons;
	delete _creatableIcons;
	delete _buildingIcons;
	delete _nodeGraphics;
	delete _legendAndAgesSlp;
	delete _tileSlp;
	delete _legendDisableSlp;

	// Free tree layout matrix
	for(int i = 0; i < _ageCount * 2; ++i)
		if(_treeLayoutMatrix[i])
			delete[] _treeLayoutMatrix[i];
	delete[] _treeLayoutMatrix;

	// Free age label rectangle array
	delete[] _ageLabelRectangles;
}

void VanillaTechTreeRenderer::Draw(DirectDrawBufferData *drawBuffer, int offsetX, int offsetY)
{
	// Set player color palette offset (16 + x, where x is 0, 16, 32, 48, 64, 80, 96 or 112)
	// Default is blue (16)
	((void(__cdecl *)(int))0x00632860)(_unknownGameAndPlayerData != 0 ? reinterpret_cast<int **>(_unknownGameAndPlayerData)[88][4] : 16);

	// Lock surface of draw buffer
	drawBuffer->LockAssociatedSurface(1);

	// Draw background tiles (only for visible area)
	int treeWidthInPixels = _treeWidth * (64 + ELEMENT_SPACING);
	int tileCount = treeWidthInPixels / _tileFrameWidth;
	if(tileCount * _tileFrameWidth < treeWidthInPixels)
		++tileCount;
	int tileMin = (offsetX - _legendFrameWidth - _agesFrameWidth) / _tileFrameWidth;
	int tileMax = std::min(tileCount, tileMin + (_windowSize.X / _tileFrameWidth) + 1);
	for(int i = tileMin; i <= tileMax; ++i)
		_tileSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, -offsetX + _legendFrameWidth + _agesFrameWidth + i * _tileFrameWidth, -offsetY, _tileFrameIndex, 0);

	// Draw age bars
	if(offsetX <= _legendFrameWidth + _agesFrameWidth)
		_legendAndAgesSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, -offsetX + _legendFrameWidth, -offsetY, _agesFrameIndex, 0);
	if(offsetX >= _legendFrameWidth + tileCount * _tileFrameWidth - _windowSize.X)
		_legendAndAgesSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, -offsetX + _legendFrameWidth + _agesFrameWidth + tileCount * _tileFrameWidth, -offsetY, _agesFrameIndex, 0);

	// Draw legend
	if(offsetX <= _legendFrameWidth)
		_legendAndAgesSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, -offsetX, -offsetY, _legendFrameIndex, 0);

	// Draw legend "disable" symbol
	if(offsetX <= _legendFrameWidth)
		_legendDisableSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, _legendDisableSlpDrawPosition.X - offsetX, _legendDisableSlpDrawPosition.Y - offsetY, 0, 0);

	// Render elements recursively
	for(TechTreeElement *currRootElement : _staticNewTechTreeDataObject->GetRootElements())
		RenderSubTree(currRootElement, drawBuffer, offsetX - _legendFrameWidth - _agesFrameWidth, offsetY);

	// Unlock surface of draw buffer
	drawBuffer->UnlockAssociatedSurface();

	// Load element font for GDI
	HDC gdiContext = drawBuffer->CreateGdiContext();
	SetBkMode(gdiContext, TRANSPARENT);
	HGDIOBJ oldGdiObject = SelectObject(gdiContext, _nodeFont->GetFontHandle());
	SetTextColor(gdiContext, 0xFFFFFF);

	// Render element captions
	while(!_elementTextsForDrawRun.empty())
	{
		// Draw current entry
		auto currEntry = _elementTextsForDrawRun.top();
		_elementTextsForDrawRun.pop();
		TextOutA(gdiContext, std::get<0>(currEntry), std::get<1>(currEntry), std::get<2>(currEntry), std::get<3>(currEntry));
	}

	// Reset selected GDI object
	SelectObject(gdiContext, oldGdiObject);
	drawBuffer->DeleteGdiContext();
}

void VanillaTechTreeRenderer::DrawPopupLabelBox(DirectDrawBufferData *drawBuffer, int x, int y)
{
	// Lock surface of draw buffer
	drawBuffer->LockAssociatedSurface(1);

	// Draw white background rectangle
	drawBuffer->DrawFilledRectangle(x + 0, y + 0, x + _popupLabelBoxSize.X, y + _popupLabelBoxSize.Y, 255);

	// Draw top bevels
	drawBuffer->DrawFilledRectangle(x + 1, y + 0, x + _popupLabelBoxSize.X - 0, y + 0, _designData->_popupBoxBevelColorIndices[0]);
	drawBuffer->DrawFilledRectangle(x + 2, y + 1, x + _popupLabelBoxSize.X - 1, y + 1, _designData->_popupBoxBevelColorIndices[1]);
	drawBuffer->DrawFilledRectangle(x + 3, y + 2, x + _popupLabelBoxSize.X - 2, y + 2, _designData->_popupBoxBevelColorIndices[2]);

	// Draw right bevels
	drawBuffer->DrawFilledRectangle(x + _popupLabelBoxSize.X - 0, y + 0, x + _popupLabelBoxSize.X - 0, y + _popupLabelBoxSize.Y - 0, _designData->_popupBoxBevelColorIndices[0]);
	drawBuffer->DrawFilledRectangle(x + _popupLabelBoxSize.X - 1, y + 1, x + _popupLabelBoxSize.X - 1, y + _popupLabelBoxSize.Y - 1, _designData->_popupBoxBevelColorIndices[1]);
	drawBuffer->DrawFilledRectangle(x + _popupLabelBoxSize.X - 2, y + 2, x + _popupLabelBoxSize.X - 2, y + _popupLabelBoxSize.Y - 2, _designData->_popupBoxBevelColorIndices[2]);

	// Draw left bevels
	drawBuffer->DrawFilledRectangle(x + 0, y + 0, x + 0, y + _popupLabelBoxSize.Y - 0, _designData->_popupBoxBevelColorIndices[3]);
	drawBuffer->DrawFilledRectangle(x + 1, y + 1, x + 1, y + _popupLabelBoxSize.Y - 1, _designData->_popupBoxBevelColorIndices[4]);
	drawBuffer->DrawFilledRectangle(x + 2, y + 2, x + 2, y + _popupLabelBoxSize.Y - 2, _designData->_popupBoxBevelColorIndices[5]);

	// Draw bottom bevels
	drawBuffer->DrawFilledRectangle(x + 0, y + _popupLabelBoxSize.Y - 0, x + _popupLabelBoxSize.X - 0, y + _popupLabelBoxSize.Y - 0, _designData->_popupBoxBevelColorIndices[3]);
	drawBuffer->DrawFilledRectangle(x + 1, y + _popupLabelBoxSize.Y - 1, x + _popupLabelBoxSize.X - 1, y + _popupLabelBoxSize.Y - 1, _designData->_popupBoxBevelColorIndices[4]);
	drawBuffer->DrawFilledRectangle(x + 2, y + _popupLabelBoxSize.Y - 2, x + _popupLabelBoxSize.X - 2, y + _popupLabelBoxSize.Y - 2, _designData->_popupBoxBevelColorIndices[5]);

	// Draw required elements
	int currX = x + 3 + _designData->_popupInnerPadding;
	int currY = y + _popupLabelBoxSize.Y - 64 - _designData->_popupInnerPadding - 3;
	for(TechTreeElement::RequiredElement *currReq : _selectedElement->_requiredElements)
	{
		// Get graphics
		int boxSlpFrameIndex = 0;
		SlpFileElement *iconSlp = nullptr;
		int iconId = -1;
		if(currReq->_elementType == TechTreeElement::ItemType::Building)
		{
			boxSlpFrameIndex = 0;
			iconSlp = _buildingIcons;
			iconId = _gameData->_civs[_selectedCivId]->_units[currReq->_elementObjectID]->_iconID;
		}
		else if(currReq->_elementType == TechTreeElement::ItemType::Creatable)
		{
			boxSlpFrameIndex = 2;
			iconSlp = _creatableIcons;
			iconId = _gameData->_civs[_selectedCivId]->_units[currReq->_elementObjectID]->_iconID;
		}
		else if(currReq->_elementType == TechTreeElement::ItemType::Research)
		{
			boxSlpFrameIndex = 4;
			iconSlp = _researchIcons;
			iconId = _gameData->_researches->_researches[currReq->_elementObjectID]._iconID;
		}

		// Draw element
		_nodeGraphics->DrawFrameIntoDirectDrawBuffer(drawBuffer, currX, currY, boxSlpFrameIndex, 0);
		if(iconId >= 0)
			iconSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, currX + 14, currY + 3, iconId, 0);

		// Next X
		currX += 64 + ELEMENT_SPACING;
	}

	// Unlock surface of draw buffer
	drawBuffer->UnlockAssociatedSurface();

	// Load element font for GDI
	HDC gdiContext = drawBuffer->CreateGdiContext();
	SetBkMode(gdiContext, TRANSPARENT);
	HGDIOBJ oldGdiObject = SelectObject(gdiContext, _nodeFont->GetFontHandle());
	SetTextColor(gdiContext, 0xFFFFFF);

	// Draw required element captions
	currX = x + 3 + _designData->_popupInnerPadding;
	for(TechTreeElement::RequiredElement *currReq : _selectedElement->_requiredElements)
	{
		// Draw text
		if(currReq->_elementNameFirstLine[0] != '\0')
			TextOutA(gdiContext, currX + 3, currY + 37, currReq->_elementNameFirstLine, strlen(currReq->_elementNameFirstLine));
		if(currReq->_elementNameSecondLine[0] != '\0')
			TextOutA(gdiContext, currX + 3, currY + 37 + _nodeFont->GetCharHeightWithRowSpace() - 6, currReq->_elementNameSecondLine, strlen(currReq->_elementNameSecondLine));

		// Next X
		currX += 64 + ELEMENT_SPACING;
	}

	// Reset selected GDI object
	SelectObject(gdiContext, oldGdiObject);
	drawBuffer->DeleteGdiContext();
}

void VanillaTechTreeRenderer::RenderSubTree(TechTreeElement *element, DirectDrawBufferData *drawBuffer, int offsetX, int offsetY)
{
	// Element hidden?
	if(element->_renderState == TechTreeElement::ItemRenderState::Hidden)
		return;

	// Calculate element absolute draw position
	int drawX = -offsetX + (element->_renderPosition.X / 2) * (64 + ELEMENT_SPACING);
	if(element->_renderPosition.X % 2 == 1)
		drawX += (64 + ELEMENT_SPACING) / 2;
	int drawY = -offsetY + _verticalDrawOffsets[element->_renderPosition.Y];

	// Check whether element is visible (if not, omit drawing)
	bool elementIsVisible = (-64 <= drawX) || (drawX <= _windowSize.X);

	// Is the element part of a selection path? => Store flag for drawing
	// This flag is not set for the selected element itself.
	auto selectionPathIterator = std::find(_selectedElementPath.begin(), _selectedElementPath.end(), element);
	bool elementIsSelectionPathElement = element != _selectedElement && selectionPathIterator != _selectedElementPath.end();
	TechTreeElement *nextSelectionPathChild = nullptr;
	if(elementIsSelectionPathElement)
		nextSelectionPathChild = *(++selectionPathIterator);

	// Check whether the next selection path element is directly reachable (i.e., draw a line to it)
	bool nextSelectionPathElementDirectlyReachable = true;
	if(nextSelectionPathChild != nullptr)
		for(int y = nextSelectionPathChild->_renderPosition.Y - 1; y > element->_renderPosition.Y; --y)
		{
			// Check left
			if(nextSelectionPathChild->_renderPosition.X > 0)
				if(_treeLayoutMatrix[y][nextSelectionPathChild->_renderPosition.X - 1])
				{
					// Not reachable
					nextSelectionPathElementDirectlyReachable = false;
					break;
				}
			// Check middle
			if(_treeLayoutMatrix[y][nextSelectionPathChild->_renderPosition.X])
			{
				// Not reachable
				nextSelectionPathElementDirectlyReachable = false;
				break;
			}
			// Check right
			if(nextSelectionPathChild->_renderPosition.X < _treeMatrixWidth * 2 - 1)
				if(_treeLayoutMatrix[y][nextSelectionPathChild->_renderPosition.X + 1])
				{
					// Not reachable
					nextSelectionPathElementDirectlyReachable = false;
					break;
				}
		}

	// Select graphics
	int boxSlpFrameIndex = 0;
	SlpFileElement *iconSlp = nullptr;
	int iconId = -1;
	if(element->_elementType == TechTreeElement::ItemType::Building)
	{
		boxSlpFrameIndex = 0;
		iconSlp = _buildingIcons;
		iconId = _gameData->_civs[_selectedCivId]->_units[element->_elementObjectID]->_iconID;
	}
	else if(element->_elementType == TechTreeElement::ItemType::Creatable)
	{
		boxSlpFrameIndex = 2;
		iconSlp = _creatableIcons;
		iconId = _gameData->_civs[_selectedCivId]->_units[element->_elementObjectID]->_iconID;
	}
	else if(element->_elementType == TechTreeElement::ItemType::Research)
	{
		boxSlpFrameIndex = 4;
		iconSlp = _researchIcons;
		iconId = _gameData->_researches->_researches[element->_elementObjectID]._iconID;
	}

	// Item not researched or disabled? => Darker Box
	if(element->_renderState == TechTreeElement::ItemRenderState::NotResearched || element->_renderState == TechTreeElement::ItemRenderState::Disabled)
		++boxSlpFrameIndex;

	// Need to draw lines below?
	if(element->_children.size() > 0)
	{
		// Draw vertical line
		drawBuffer->DrawFilledRectangle(drawX + 31, drawY + 64, drawX + 32, drawY + 67, (elementIsSelectionPathElement && nextSelectionPathElementDirectlyReachable ? 255 : 0));

		// Draw vertical line for each child and store left most / right most child coordinates
		int leftMostChildDrawX = INT32_MIN;
		int rightMostChildDrawX = INT32_MIN;
		for(TechTreeElement *currChild : element->_children)
		{
			// Check whether child is visible
			if(currChild->_renderState == TechTreeElement::ItemRenderState::Hidden)
				continue;

			// Check whether the element is directly reachable from the root element (there are no elements on top of it)
			bool elementIsReachable = true;
			for(int y = currChild->_renderPosition.Y - 1; y > element->_renderPosition.Y; --y)
			{
				// Check left
				if(currChild->_renderPosition.X > 0)
					if(_treeLayoutMatrix[y][currChild->_renderPosition.X - 1])
					{
						// Not reachable
						elementIsReachable = false;
						break;
					}
				// Check middle
				if(_treeLayoutMatrix[y][currChild->_renderPosition.X])
				{
					// Not reachable
					elementIsReachable = false;
					break;
				}
				// Check right
				if(currChild->_renderPosition.X < _treeMatrixWidth * 2 - 1)
					if(_treeLayoutMatrix[y][currChild->_renderPosition.X + 1])
					{
						// Not reachable
						elementIsReachable = false;
						break;
					}
			}

			// If the element isn't reachable, it can be omitted
			if(!elementIsReachable)
				continue;

			// Calculate absolute child draw position
			int childDrawX = -offsetX + (currChild->_renderPosition.X / 2) * (64 + ELEMENT_SPACING);
			if(currChild->_renderPosition.X % 2 == 1)
				childDrawX += (64 + ELEMENT_SPACING) / 2;
			int childDrawY = -offsetY + _verticalDrawOffsets[currChild->_renderPosition.Y];

			// Update minimum/maximum if needed
			if(leftMostChildDrawX == INT32_MIN || childDrawX < leftMostChildDrawX)
				leftMostChildDrawX = childDrawX;
			if(rightMostChildDrawX == INT32_MIN || childDrawX > rightMostChildDrawX)
				rightMostChildDrawX = childDrawX;

			// Draw vertical line (white if the next element belongs to a selection path)
			if(elementIsSelectionPathElement && currChild == nextSelectionPathChild)
				drawBuffer->DrawFilledRectangle(childDrawX + 31, drawY + 68, childDrawX + 32, childDrawY, 255);
			else
				drawBuffer->DrawFilledRectangle(childDrawX + 31, drawY + 68, childDrawX + 32, childDrawY, 0);
		}

		// Draw horizontal connection from the left most child to the right most child
		if(leftMostChildDrawX != INT32_MIN && rightMostChildDrawX != INT32_MIN)
			drawBuffer->DrawFilledRectangle(leftMostChildDrawX + 31, drawY + 68, rightMostChildDrawX + 32, drawY + 69, 0);

		// If the element is part of a selection path, draw horizontal line along path
		if(elementIsSelectionPathElement && nextSelectionPathElementDirectlyReachable)
		{
			// Get child position
			int childDrawX = -offsetX + (nextSelectionPathChild->_renderPosition.X / 2) * (64 + ELEMENT_SPACING);
			if(nextSelectionPathChild->_renderPosition.X % 2 == 1)
				childDrawX += (64 + ELEMENT_SPACING) / 2;
			int childDrawY = -offsetY + _verticalDrawOffsets[nextSelectionPathChild->_renderPosition.Y];

			// Draw horizontal line
			int lineLeftElementX = (drawX < childDrawX ? drawX : childDrawX);
			int lineRightElementX = (drawX > childDrawX ? drawX : childDrawX);
			drawBuffer->DrawFilledRectangle(lineLeftElementX + 31, drawY + 68, lineRightElementX + 32, drawY + 69, 255);
		}
	}

	// If element is not visible, don't draw it
	if(elementIsVisible)
	{
		// Is the element selected or part of a selection path? => Draw white box as background
		if(elementIsSelectionPathElement || element == _selectedElement)
			drawBuffer->DrawFilledRectangle(drawX - 2, drawY - 2, drawX + 64 + 1, drawY + 64 + 1, 255);

		// Draw element
		_nodeGraphics->DrawFrameIntoDirectDrawBuffer(drawBuffer, drawX, drawY, boxSlpFrameIndex, 0);
		if(iconId >= 0)
			iconSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, drawX + 14, drawY + 3, iconId, 0);

		// If the element is disabled, draw disable graphic on top of it
		if(element->_renderState == TechTreeElement::ItemRenderState::Disabled)
		{
			// Draw node disable graphic (frame #6)
			// Per default this graphic consists only of one transparent pixel, so it could as well be omitted. Kept here for possible modding purposes.
			_nodeGraphics->DrawFrameIntoDirectDrawBuffer(drawBuffer, drawX, drawY, 6, 0);

			// Draw icon disable graphic (frame #117 in research icon SLP)
			_researchIcons->DrawFrameIntoDirectDrawBuffer(drawBuffer, drawX + 14, drawY + 3, 117, 0);
		}

		// Put caption onto the text stack for later drawing
		if(element->_elementNameFirstLine[0] != '\0')
			_elementTextsForDrawRun.push(std::make_tuple(drawX + 3, drawY + 37, element->_elementNameFirstLine, strlen(element->_elementNameFirstLine)));
		if(element->_elementNameSecondLine[0] != '\0')
			_elementTextsForDrawRun.push(std::make_tuple(drawX + 3, drawY + 37 + _nodeFont->GetCharHeightWithRowSpace() - 6, element->_elementNameSecondLine, strlen(element->_elementNameSecondLine)));
	}

	// Render sub elements
	for(TechTreeElement *currChild : element->_children)
		RenderSubTree(currChild, drawBuffer, offsetX, offsetY);
}

void VanillaTechTreeRenderer::SetCurrentCiv(int civId)
{
	// Call base function
	base::SetCurrentCiv(civId);

	// Start with root elements for width computation (order is not important)
	std::stack<TechTreeElement *> remainingElements;
	for(TechTreeElement *currRootElement : _staticNewTechTreeDataObject->GetRootElements())
		remainingElements.push(currRootElement);

	// Measure tree width (count of leaf elements)
	_treeMatrixWidth = 0;
	while(!remainingElements.empty())
	{
		// Pop top element
		TechTreeElement *currElement = remainingElements.top();
		remainingElements.pop();

		// Check if there are enabled children
		bool enabledChildExists = false;
		for(TechTreeElement *currChild : currElement->_children)
			if(currChild->_renderState != TechTreeElement::ItemRenderState::Hidden)
			{
				// Enabled child found, put onto the stack
				remainingElements.push(currChild);
				enabledChildExists = true;
			}

		// If there are no children, increment tree width
		if(!enabledChildExists && currElement->_renderState != TechTreeElement::ItemRenderState::Hidden)
			++_treeMatrixWidth;
	}

	// Free tree layout matrix rows if neccessary
	for(int i = 0; i < _ageCount * 2; ++i)
		if(_treeLayoutMatrix[i])
			delete[] _treeLayoutMatrix[i];

	// Create tree layout matrix rows (at maximum 2 vertical elements per age)
	for(int i = 0; i < _ageCount * 2; ++i)
		_treeLayoutMatrix[i] = new TechTreeElement*[_treeMatrixWidth * 2](); // Create and clear row

	// Compute sub trees for root elements
	_treeWidth = 0;
	for(TechTreeElement *currRootElement : _staticNewTechTreeDataObject->GetRootElements())
	{
		// Compute sub tree and get its width
		// Simulate a virtual root building to allow compactification
		int minimumStartColumnIndexDummy = -1;
		if(currRootElement->_renderState != TechTreeElement::ItemRenderState::Hidden)
			_treeWidth += ComputeSubTree(currRootElement, 2 * _treeWidth, false, &minimumStartColumnIndexDummy, TechTreeElement::ItemType::Building);
	}

	// Recalculate age label positions
	for(int i = 0; i < _ageCount; ++i)
	{
		// Calculate rectangles
		int fullTreeWidth = GetFullWidth();
		_ageLabelRectangles[i][1][0] = Rect(fullTreeWidth - _ageLabelRectangles[i][0][0].Width, _ageLabelRectangles[i][0][0].Y, _ageLabelRectangles[i][0][0].Width, _ageLabelRectangles[i][0][0].Height);
		_ageLabelRectangles[i][1][1] = Rect(fullTreeWidth - _ageLabelRectangles[i][0][1].Width, _ageLabelRectangles[i][0][1].Y, _ageLabelRectangles[i][0][1].Width, _ageLabelRectangles[i][0][1].Height);
	}
}

int VanillaTechTreeRenderer::ComputeSubTree(TechTreeElement *element, int startColumnIndex, bool secondInAge, int *minimumStartColumnIndex, TechTreeElement::ItemType parentType)
{
	// Get row index for this element
	int rowIndex = 2 * element->_age + (secondInAge ? 1 : 0);

	// Calculate space to the left
	int elementMinimumStartColumnIndex = startColumnIndex;
	while(elementMinimumStartColumnIndex > 1)
	{
		// Check if there are other elements at the next position or below
		bool conflict = false;
		for(int y = rowIndex; y < 2 * _ageCount; ++y)
			if(_treeLayoutMatrix[y][elementMinimumStartColumnIndex - 2] != nullptr)
			{
				// Conflict found
				conflict = true;
				break;
			}

		// Check whether there are now collisions with subtrees of different buildings
		for(int y = rowIndex - 1; y >= 0; --y)
			if(_treeLayoutMatrix[y][elementMinimumStartColumnIndex - 2] != nullptr
				&& _treeLayoutMatrix[y][elementMinimumStartColumnIndex - 2]->_parentBuilding != element->_parentBuilding)
			{
				// Conflict found
				conflict = true;
				break;
			}

		// No conflict? => Next position
		if(conflict)
			break;
		--elementMinimumStartColumnIndex;
	}

	// Minimum Start Column Index 1 => there must be still space on the left
	if(elementMinimumStartColumnIndex == 1)
		elementMinimumStartColumnIndex = 0;

	// Compute children sub trees
	// If possible, center element above non-building subtree
	int subTreeWidth = 0;
	int firstNonBuildingChildPosX = -1;
	int nonBuildingChildSubTreeWidth = 0;
	for(TechTreeElement *currChild : element->_children)
		if(currChild->_renderState != TechTreeElement::ItemRenderState::Hidden)
		{
			// Compute child sub tree
			int currChildMinimumStartColumnIndex = -1;
			int currChildSubTreeWidth = ComputeSubTree(currChild, startColumnIndex + 2 * subTreeWidth, currChild->_age == element->_age, &currChildMinimumStartColumnIndex, element->_elementType);

			// Calculate shift to the left
			if(*minimumStartColumnIndex == -1)
				*minimumStartColumnIndex = std::max(elementMinimumStartColumnIndex, currChildMinimumStartColumnIndex);

			// Non-building child?
			if(currChild->_elementType != TechTreeElement::ItemType::Building)
			{
				// Is this the first non-building child?
				if(firstNonBuildingChildPosX < 0)
					firstNonBuildingChildPosX = startColumnIndex + 2 * subTreeWidth;

				// Add child sub tree width to non-building sub tree width
				nonBuildingChildSubTreeWidth += currChildSubTreeWidth;
			}

			// Add child sub tree width to whole subtree width
			subTreeWidth += currChildSubTreeWidth;
		}

	// If element has no children, the sub tree width is 1
	if(subTreeWidth == 0)
		subTreeWidth = 1;

	// Are there any non-building children?
	if(firstNonBuildingChildPosX < 0)
	{
		// Use all children for centering
		firstNonBuildingChildPosX = startColumnIndex;
		nonBuildingChildSubTreeWidth = subTreeWidth;
	}

	// Center element above non-building subtree
	element->_renderPosition = Point(firstNonBuildingChildPosX + nonBuildingChildSubTreeWidth - 1, rowIndex);
	_treeLayoutMatrix[element->_renderPosition.Y][element->_renderPosition.X] = element;

	// If minimum column index return value is not set, there were no children, so set it directly
	if(*minimumStartColumnIndex == -1)
		*minimumStartColumnIndex = std::max(elementMinimumStartColumnIndex, 0); // 0 if we already are on the very left

	// If parent element is building, perform compactification
	if(parentType == TechTreeElement::ItemType::Building && *minimumStartColumnIndex != startColumnIndex)
	{
		// Move whole subtree to the left
		MoveTreeLeft(element, startColumnIndex - *minimumStartColumnIndex);

		// Subtract shift amount from subtree width
		subTreeWidth -= ((startColumnIndex - *minimumStartColumnIndex) / 2);
		if(subTreeWidth < 0)
			subTreeWidth = 0;
	}

	// Finish, return width of whole subtree
	return subTreeWidth;
}

int VanillaTechTreeRenderer::GetFullWidth()
{
	// First calculate number of background tiles
	int treeWidthInPixels = _treeWidth * (64 + ELEMENT_SPACING);
	int tileCount = treeWidthInPixels / _tileFrameWidth;
	if(tileCount * _tileFrameWidth < treeWidthInPixels)
		++tileCount;

	// Calculate tree width
	return _legendFrameWidth + _agesFrameWidth + tileCount * _tileFrameWidth + _agesFrameWidth;
}

int VanillaTechTreeRenderer::GetFullHeight()
{
	// TODO
	return _legendFrameHeight;
}

const Rect* VanillaTechTreeRenderer::GetCivBonusLabelRectangle()
{
	// Return rectangle
	return &_civBonusLabelRectangle;
}

const Rect* VanillaTechTreeRenderer::GetCivSelectionComboBoxRectangle()
{
	// Return rectangle
	return &_civSelectionComboBoxRectangle;
}

const Rect* VanillaTechTreeRenderer::GetGameCivsLabelRectangle()
{
	// Return rectangle
	return &_gameCivsLabelRectangle;
}

const Rect* VanillaTechTreeRenderer::GetLegendLabelRectangle(LegendLabelIndices labelIndex)
{
	// Return rectangle
	return &_legendLabelRectangles[static_cast<int>(labelIndex)];
}

const Rect* VanillaTechTreeRenderer::GetAgeLabelRectangle(int age, bool side, bool line)
{
	// Return rectangle
	return &_ageLabelRectangles[age][side ? 1 : 0][line ? 1 : 0];
}

Rect VanillaTechTreeRenderer::UpdateAndGetPopupLabelBoxDrawData(Size &popupLabelSize)
{
	// Calculate content width
	int contentWidth = std::max(popupLabelSize.X, static_cast<int>(_selectedElement->_requiredElements.size() * (64 + ELEMENT_SPACING)) - ELEMENT_SPACING);

	// The size is simply the sum of bevels, paddings and the content width
	_popupLabelBoxSize = Size(3 + _designData->_popupInnerPadding + contentWidth + _designData->_popupInnerPadding + 3, 3 + _designData->_popupInnerPadding + popupLabelSize.Y + _designData->_popupInnerPadding + 3);

	// If there are requirements, reserve space for them
	if(_selectedElement->_requiredElements.size() > 0)
		_popupLabelBoxSize.Y += 64;

	// Return size
	return Rect(3 + _designData->_popupInnerPadding, 3 + _designData->_popupInnerPadding, _popupLabelBoxSize.X, _popupLabelBoxSize.Y);
}

TechTreeElement* VanillaTechTreeRenderer::GetElementAtPosition(int x, int y)
{
	// Clean coordinate from other window fragments, this simplifies the calculations in the next step
	x = x - _legendFrameWidth - _agesFrameWidth;

	// Calculate tree X position
	int treeX = (x / ((64 + ELEMENT_SPACING) / 2));

	// Check for proper X values
	if(x < 0 || treeX >= 2 * _treeMatrixWidth)
		return nullptr;

	// Calculate tree Y position: Check whether element is on one of the draw offsets
	int treeY = -1;
	for(int i = 0; i < _ageCount * 2; ++i)
		if(_verticalDrawOffsets[i] <= y && y < _verticalDrawOffsets[i] + 64)
		{
			// Found
			treeY = i;
			break;
		}

	// Valid position found?
	if(treeY < 0)
		return nullptr;

	// Check whether there is an element at the calculated position
	TechTreeElement *element = _treeLayoutMatrix[treeY][treeX];
	if(element != nullptr || treeX == 0)
		return element;
	else
	{
		// Check whether there is a element on the left of the calculated X
		int elementX = ((treeX - 1) / 2) * (64 + ELEMENT_SPACING);
		if((treeX - 1) % 2 == 1)
			elementX += (64 + ELEMENT_SPACING) / 2;
		if(elementX <= x && x < elementX + 64)
			return _treeLayoutMatrix[treeY][treeX - 1];
		else
			return nullptr;
	}
}

void VanillaTechTreeRenderer::SetSelectedElement(TechTreeElement *element)
{
	// Changes?
	if(_selectedElement == element)
		return;

	// Save element
	_selectedElement = element;
	_selectedElementPath.clear();

	// No selection?
	if(element == nullptr)
		return;

	// Compute parent elements of selected element to draw the selection path
	std::function<bool(TechTreeElement *)> getElementPathRecursively;
	getElementPathRecursively = [this, element, &getElementPathRecursively](TechTreeElement *currElement)
	{
		// Push onto the path stack
		_selectedElementPath.push_back(currElement);

		// Element found?
		if(currElement == element)
			return true;

		// Try to find child with this element
		for(TechTreeElement *currChild : currElement->_children)
			if(getElementPathRecursively(currChild))
				return true;

		// Not found, pop and return
		_selectedElementPath.pop_back();
		return false;
	};
	for(TechTreeElement *currRoot : _staticNewTechTreeDataObject->GetRootElements())
		if(getElementPathRecursively(currRoot))
			break;
}

void VanillaTechTreeRenderer::MoveTreeLeft(TechTreeElement *element, int amount)
{
	// Move recursively
	for(TechTreeElement *currChild : element->_children)
		MoveTreeLeft(currChild, amount);

	// Calculate now column index
	int newDrawX = element->_renderPosition.X - amount;

	// Update tree layout matrix
	_treeLayoutMatrix[element->_renderPosition.Y][element->_renderPosition.X] = nullptr;
	_treeLayoutMatrix[element->_renderPosition.Y][newDrawX] = element;

	// Update position variable
	element->_renderPosition.X = newDrawX;
}