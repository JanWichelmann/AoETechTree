/* INCLUDES */

// Class header
#include "VanillaTechTreeRenderer.h"

// Other includes
#include <algorithm>
#include <stack>
#include <vector>
#include <functional>
#include "Game.h"
#include "DirectDrawHandler.h"

/* FUNCTIONS */

VanillaTechTreeRenderer::VanillaTechTreeRenderer(GameDataHandler *gameData, Size &windowSize)
	: TechTreeRenderer(gameData)
{
	// Load icon SLPs
	_researchIcons = new SlpFileElement("btntech.shp", 50729);
	_creatableIcons = new SlpFileElement("ico_unit.shp", 50730);
	_buildingIcons = new SlpFileElement("ico_bld2.shp", 50706);

	// Load node SLP
	_nodeGraphics = new SlpFileElement("technodex.slp", 53206);

	// Load legend SLP
	_legendAndAgesSlp = new SlpFileElement("techages.slp", 50342);

	// Load tile SLP
	_tileSlp = new SlpFileElement("techback.slp", 50341);

	// Load legend "disable" SLP
	_legendDisableSlp = new SlpFileElement("ttx.slp", 53211);

	// Set resolution specific position values
	_verticalDrawOffsets = new int[_ageCount * 2];
	_ageLabelRectangles = new Rect[_ageCount][2][2];
	if(windowSize.Y >= 1024)
	{
		// Frame indices
		_legendFrameIndex = 1;
		_agesFrameIndex = 8;
		_tileFrameIndex = 1;

		// Control draw positions
		_legendDisableSlpDrawPosition = Point(121, 926);
		_civBonusLabelRectangle = Rect(40, 125, 290, 660);
		_civSelectionComboBoxRectangle = Rect(70, 90, 230, 25);
		_gameCivsLabelRectangle = Rect(70, 70, 230, 25);

		// Legend labels
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotResearched)] = Rect(50, 814, 80, 40);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researched)] = Rect(50 + 100, 814, 80, 40);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Units)] = Rect(200, 855 + 0 * 23, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Buildings)] = Rect(200, 855 + 1 * 23, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researches)] = Rect(200, 855 + 2 * 23, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotAvailable)] = Rect(200 - 45, 855 + 3 * 23 + 15, 160, 25);

		// Age draw heights
		_verticalDrawOffsets[0] = 10;
		_verticalDrawOffsets[1] = 133;
		_verticalDrawOffsets[2] = 267;
		_verticalDrawOffsets[3] = 390;
		_verticalDrawOffsets[4] = 525;
		_verticalDrawOffsets[5] = 648;
		_verticalDrawOffsets[6] = 783;
		_verticalDrawOffsets[7] = 906;

		// Age labels
		// Calculate left side rectangles, right side follows later when the tree width is known
		// Bottom lines follow after resolution setting, they are always the same relative to the upper line labels
		_ageLabelRectangles[0][0][0] = Rect(450, 140, 150, 25);
		_ageLabelRectangles[1][0][0] = Rect(450, 420, 150, 25);
		_ageLabelRectangles[2][0][0] = Rect(450, 660, 150, 25);
		_ageLabelRectangles[3][0][0] = Rect(450, 920, 150, 25);
	}
	else if(windowSize.Y >= 768)
	{
		// Frame indices
		_legendFrameIndex = 0;
		_agesFrameIndex = 7;
		_tileFrameIndex = 0;

		// Control draw positions
		_legendDisableSlpDrawPosition = Point(113, 665);
		_civBonusLabelRectangle = Rect(40, 120, 280, 430);
		_civSelectionComboBoxRectangle = Rect(65, 85, 230, 25);
		_gameCivsLabelRectangle = Rect(65, 65, 230, 25);

		// Legend labels
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotResearched)] = Rect(45, 550, 80, 40);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researched)] = Rect(45 + 90, 550, 80, 40);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Units)] = Rect(188, 593 + 0 * 22, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Buildings)] = Rect(188, 593 + 1 * 22, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researches)] = Rect(188, 593 + 2 * 22, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotAvailable)] = Rect(188 - 40, 593 + 3 * 22 + 15, 160, 25);

		// Age draw heights
		_verticalDrawOffsets[0] = 7;
		_verticalDrawOffsets[1] = 99;
		_verticalDrawOffsets[2] = 200;
		_verticalDrawOffsets[3] = 292;
		_verticalDrawOffsets[4] = 393;
		_verticalDrawOffsets[5] = 485;
		_verticalDrawOffsets[6] = 586;
		_verticalDrawOffsets[7] = 678;

		// Age labels
		_ageLabelRectangles[0][0][0] = Rect(345, 131, 150, 25);
		_ageLabelRectangles[1][0][0] = Rect(345, 324, 150, 25);
		_ageLabelRectangles[2][0][0] = Rect(345, 517, 150, 25);
		_ageLabelRectangles[3][0][0] = Rect(345, 711, 150, 25);
	}
	else
	{
		// Frame indices
		_legendFrameIndex = 2;
		_agesFrameIndex = 17;
		_tileFrameIndex = 2;

		// Control draw positions
		_legendDisableSlpDrawPosition = Point(102, 528);
		_civBonusLabelRectangle = Rect(30, 115, 270, 300);
		_civSelectionComboBoxRectangle = Rect(55, 80, 230, 25);
		_gameCivsLabelRectangle = Rect(55, 60, 230, 25);

		// Legend labels
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotResearched)] = Rect(35, 430, 80, 40);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researched)] = Rect(35 + 80, 430, 80, 40);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Units)] = Rect(167, 470 + 0 * 22, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Buildings)] = Rect(167, 470 + 1 * 22, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::Researches)] = Rect(167, 470 + 2 * 22, 160, 25);
		_legendLabelRectangles[static_cast<int>(LegendLabelIndices::NotAvailable)] = Rect(167 - 30, 470 + 3 * 22 + 3, 160, 25);

		// Age draw heights
		_verticalDrawOffsets[0] = 6;
		_verticalDrawOffsets[1] = 78;
		_verticalDrawOffsets[2] = 157;
		_verticalDrawOffsets[3] = 229;
		_verticalDrawOffsets[4] = 308;
		_verticalDrawOffsets[5] = 380;
		_verticalDrawOffsets[6] = 459;
		_verticalDrawOffsets[7] = 531;

		// Age labels
		_ageLabelRectangles[0][0][0] = Rect(340, 110, 150, 25);
		_ageLabelRectangles[1][0][0] = Rect(340, 261, 150, 25);
		_ageLabelRectangles[2][0][0] = Rect(340, 412, 150, 25);
		_ageLabelRectangles[3][0][0] = Rect(340, 563, 150, 25);
	}

	// Set upper line position data according to difference of the last two age Y positions for all extra ages
	for(int i = 4; i < _ageCount; ++i)
		_ageLabelRectangles[i][0][0] = Rect(_ageLabelRectangles[3][0][0].X, _ageLabelRectangles[3][0][0].Y - _ageLabelRectangles[2][0][0].Y, _ageLabelRectangles[3][0][0].Width, _ageLabelRectangles[3][0][0].Height);

	// Set second line age label parameters (they directly depend on first line label parameters)
	for(int i = 0; i < _ageCount; ++i)
		_ageLabelRectangles[i][0][1] = Rect(_ageLabelRectangles[i][0][0].X, _ageLabelRectangles[i][0][0].Y + 17, _ageLabelRectangles[i][0][0].Width, _ageLabelRectangles[i][0][0].Height);

	// Get some SLP frame sizes
	_legendAndAgesSlp->GetFrameSize(_agesFrameIndex, &_agesFrameWidth, &_agesFrameHeight);
	_tileSlp->GetFrameSize(_tileFrameIndex, &_tileFrameWidth, &_tileFrameHeight);
	_legendAndAgesSlp->GetFrameSize(_legendFrameIndex, &_legendFrameWidth, &_legendFrameHeight);

	// Load node caption font
	_nodeFont = (*_staticGameObjectPointer)->GetFontWithIndex(12);

	// Initialize tree computation variables
	_treeWidth = 0;
	_treeLayoutMatrix = new TechTreeElement**[_ageCount * 2](); // Filled later

	// Set popup label box bevel colors
	HPALETTE palette = (*_staticGameObjectPointer)->GetDirectDrawHandler()->GetMainPalette();
	_popupLabelBoxBevelColors[0] = GetNearestPaletteIndex(palette, 0xCFCFCFu);
	_popupLabelBoxBevelColors[1] = GetNearestPaletteIndex(palette, 0xB9B9B9u);
	_popupLabelBoxBevelColors[2] = GetNearestPaletteIndex(palette, 0xA3A3A3u);
	_popupLabelBoxBevelColors[3] = GetNearestPaletteIndex(palette, 0x606060u);
	_popupLabelBoxBevelColors[4] = GetNearestPaletteIndex(palette, 0x767676u);
	_popupLabelBoxBevelColors[5] = GetNearestPaletteIndex(palette, 0x8C8C8Cu);
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
	// TODO: Hardcoded (red)
	((void(__cdecl *)(int))0x00632860)(32);

	// Lock surface of draw buffer
	drawBuffer->LockAssociatedSurface(1);

	// Draw background tiles
	int treeWidthInPixels = _treeWidth * (64 + ELEMENT_SPACING);
	int tileCount = treeWidthInPixels / _tileFrameWidth;
	if(tileCount * _tileFrameWidth < treeWidthInPixels)
		++tileCount;
	for(int i = 0; i < tileCount; ++i)
		_tileSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, -offsetX + _legendFrameWidth + _agesFrameWidth + i * _tileFrameWidth, -offsetY, _tileFrameIndex, 0);

	// Draw age bars
	_legendAndAgesSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, -offsetX + _legendFrameWidth, -offsetY, _agesFrameIndex, 0);
	_legendAndAgesSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, -offsetX + _legendFrameWidth + _agesFrameWidth + tileCount * _tileFrameWidth, -offsetY, _agesFrameIndex, 0);

	// Draw legend
	_legendAndAgesSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, -offsetX, -offsetY, _legendFrameIndex, 0);

	// Draw legend "disable" symbol
	_legendDisableSlp->DrawFrameIntoDirectDrawBuffer(drawBuffer, _legendDisableSlpDrawPosition.X - offsetX, _legendDisableSlpDrawPosition.Y - offsetY, 0, 0);

	// Debugging
	for(int i = 0; i < _ageCount * 2; ++i)
		for(int j = 0; j < _treeWidth * 2; ++j)
			drawBuffer->DrawFilledRectangle(1700 + 16 * j, 900 + 16 * i, 1716 + 16 * j, 916 + 16 * i, _treeLayoutMatrix[i][j] != nullptr ? 36 : 0);

	// Unlock surface of draw buffer
	drawBuffer->UnlockAssociatedSurface();

	// Render elements recursively
	for(TechTreeElement *currRootElement : _gameData->_techTree->GetRootElements())
		RenderSubTree(currRootElement, drawBuffer, offsetX - _legendFrameWidth - _agesFrameWidth, offsetY);
}

void VanillaTechTreeRenderer::DrawPopupLabelBox(DirectDrawBufferData *drawBuffer, int x, int y)
{
	// Lock surface of draw buffer
	drawBuffer->LockAssociatedSurface(1);

	// Draw white background rectangle
	drawBuffer->DrawFilledRectangle(x + 0, y + 0, x + _popupLabelBoxSize.X, y + _popupLabelBoxSize.Y, 255);

	// Draw top bevels
	drawBuffer->DrawFilledRectangle(x + 1, y + 0, x + _popupLabelBoxSize.X - 0, y + 0, _popupLabelBoxBevelColors[0]);
	drawBuffer->DrawFilledRectangle(x + 2, y + 1, x + _popupLabelBoxSize.X - 1, y + 1, _popupLabelBoxBevelColors[1]);
	drawBuffer->DrawFilledRectangle(x + 3, y + 2, x + _popupLabelBoxSize.X - 2, y + 2, _popupLabelBoxBevelColors[2]);

	// Draw right bevels
	drawBuffer->DrawFilledRectangle(x + _popupLabelBoxSize.X - 0, y + 0, x + _popupLabelBoxSize.X - 0, y + _popupLabelBoxSize.Y - 0, _popupLabelBoxBevelColors[0]);
	drawBuffer->DrawFilledRectangle(x + _popupLabelBoxSize.X - 1, y + 1, x + _popupLabelBoxSize.X - 1, y + _popupLabelBoxSize.Y - 1, _popupLabelBoxBevelColors[1]);
	drawBuffer->DrawFilledRectangle(x + _popupLabelBoxSize.X - 2, y + 2, x + _popupLabelBoxSize.X - 2, y + _popupLabelBoxSize.Y - 2, _popupLabelBoxBevelColors[2]);

	// Draw left bevels
	drawBuffer->DrawFilledRectangle(x + 0, y + 0, x + 0, y + _popupLabelBoxSize.Y - 0, _popupLabelBoxBevelColors[3]);
	drawBuffer->DrawFilledRectangle(x + 1, y + 1, x + 1, y + _popupLabelBoxSize.Y - 1, _popupLabelBoxBevelColors[4]);
	drawBuffer->DrawFilledRectangle(x + 2, y + 2, x + 2, y + _popupLabelBoxSize.Y - 2, _popupLabelBoxBevelColors[5]);

	// Draw bottom bevels
	drawBuffer->DrawFilledRectangle(x + 0, y + _popupLabelBoxSize.Y - 0, x + _popupLabelBoxSize.X - 0, y + _popupLabelBoxSize.Y - 0, _popupLabelBoxBevelColors[3]);
	drawBuffer->DrawFilledRectangle(x + 1, y + _popupLabelBoxSize.Y - 1, x + _popupLabelBoxSize.X - 1, y + _popupLabelBoxSize.Y - 1, _popupLabelBoxBevelColors[4]);
	drawBuffer->DrawFilledRectangle(x + 2, y + _popupLabelBoxSize.Y - 2, x + _popupLabelBoxSize.X - 2, y + _popupLabelBoxSize.Y - 2, _popupLabelBoxBevelColors[5]);

	// Draw required elements
	int currX = x + 3 + POPUP_LABEL_BOX_PADDING;
	int currY = y + _popupLabelBoxSize.Y - 64 - POPUP_LABEL_BOX_PADDING - 3;
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
	currX = x + 3 + POPUP_LABEL_BOX_PADDING;
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

	// Lock surface of draw buffer
	drawBuffer->LockAssociatedSurface(1);

	// Calculate element absolute draw position
	int drawX = -offsetX + (element->_renderPosition.X / 2) * (64 + ELEMENT_SPACING);
	if(element->_renderPosition.X % 2 == 1)
		drawX += (64 + ELEMENT_SPACING) / 2;
	int drawY = -offsetY + _verticalDrawOffsets[element->_renderPosition.Y];

	// Is the element part of a selection path? => Store flag for drawing
	// This flag is not set for the selected element itself.
	auto selectionPathIterator = std::find(_selectedElementPath.begin(), _selectedElementPath.end(), element);
	bool elementIsSelectionPathElement = element != _selectedElement && selectionPathIterator != _selectedElementPath.end();
	TechTreeElement *nextSelectionPathChild = nullptr;
	if(elementIsSelectionPathElement)
		nextSelectionPathChild = *(++selectionPathIterator);

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

	// Need to draw lines below?
	if(element->_children.size() > 0)
	{
		// Draw vertical line
		drawBuffer->DrawFilledRectangle(drawX + 31, drawY + 64, drawX + 32, drawY + 67, elementIsSelectionPathElement ? 255 : 0);

		// Draw vertical line for each child and store left most / right most child coordinates
		int leftMostChildDrawX = INT32_MIN;
		int rightMostChildDrawX = INT32_MIN;
		for(TechTreeElement *currChild : element->_children)
		{
			// Check whether the element is directly reachable from the root element (there are no elements on top of it)
			bool elementIsReachable = true;
			for(int y = currChild->_renderPosition.Y; y < element->_renderPosition.Y; --y)
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
				if(currChild->_renderPosition.X < _treeWidth * 2 - 1)
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
		if(elementIsSelectionPathElement)
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

	// Unlock surface of draw buffer
	drawBuffer->UnlockAssociatedSurface();

	// Load element font for GDI
	HDC gdiContext = drawBuffer->CreateGdiContext();
	SetBkMode(gdiContext, TRANSPARENT);
	HGDIOBJ oldGdiObject = SelectObject(gdiContext, _nodeFont->GetFontHandle());
	SetTextColor(gdiContext, 0xFFFFFF);

	// Draw element text
	if(element->_elementNameFirstLine[0] != '\0')
		TextOutA(gdiContext, drawX + 3, drawY + 37, element->_elementNameFirstLine, strlen(element->_elementNameFirstLine));
	if(element->_elementNameSecondLine[0] != '\0')
		TextOutA(gdiContext, drawX + 3, drawY + 37 + _nodeFont->GetCharHeightWithRowSpace() - 6, element->_elementNameSecondLine, strlen(element->_elementNameSecondLine));

	// Reset selected GDI object
	SelectObject(gdiContext, oldGdiObject);
	drawBuffer->DeleteGdiContext();

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
	for(TechTreeElement *currRootElement : _gameData->_techTree->GetRootElements())
		remainingElements.push(currRootElement);

	// Compute tree width (count of leaf elements)
	_treeWidth = 0;
	char elementNameBuffer[256];
	while(!remainingElements.empty())
	{
		// Pop top element
		TechTreeElement *currElement = remainingElements.top();
		remainingElements.pop();

		// If there are no children, increment tree width
		if(currElement->_children.size() == 0 && currElement->_renderState != TechTreeElement::ItemRenderState::Hidden)
			++_treeWidth;
		else // Iterate and push children
			for(TechTreeElement *currChild : currElement->_children)
				remainingElements.push(currChild);
	}

	// Free tree layout matrix rows if neccessary
	for(int i = 0; i < _ageCount * 2; ++i)
		if(_treeLayoutMatrix[i])
			delete[] _treeLayoutMatrix[i];

	// Create tree layout matrix rows (at maximum 2 vertical elements per age)
	for(int i = 0; i < _ageCount * 2; ++i)
		_treeLayoutMatrix[i] = new TechTreeElement*[_treeWidth * 2](); // Create and clear row

	// Compute sub trees for root elements
	int subTreeWidth = 0;
	for(TechTreeElement *currRootElement : _gameData->_techTree->GetRootElements())
	{
		// Compute sub tree and get its width
		if(currRootElement->_renderState != TechTreeElement::ItemRenderState::Hidden)
			subTreeWidth += ComputeSubTree(currRootElement, 2 * subTreeWidth, false);
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

int VanillaTechTreeRenderer::ComputeSubTree(TechTreeElement *element, int startColumnIndex, bool secondInAge)
{
	// Compute children sub trees
	int subTreeWidth = 0;
	for(TechTreeElement *currChild : element->_children)
		if(currChild->_renderState != TechTreeElement::ItemRenderState::Hidden)
			subTreeWidth += ComputeSubTree(currChild, startColumnIndex + 2 * subTreeWidth, currChild->_age == element->_age);

	// Get row index for this element
	int rowIndex = 2 * element->_age + (secondInAge ? 1 : 0);

	// If element has no children, the sub tree width is 1
	if(subTreeWidth == 0)
		subTreeWidth = 1;

	// Center element above subtree
	element->_renderPosition = Point(startColumnIndex + subTreeWidth - 1, rowIndex);
	_treeLayoutMatrix[element->_renderPosition.Y][element->_renderPosition.X] = element;
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

Rect& VanillaTechTreeRenderer::UpdateAndGetPopupLabelBoxDrawData(Size &popupLabelSize)
{
	// Calculate content width
	int contentWidth = std::max(popupLabelSize.X, static_cast<int>(_selectedElement->_requiredElements.size() * (64 + ELEMENT_SPACING)) - ELEMENT_SPACING);

	// The size is simply the sum of bevels, paddings and the content width
	_popupLabelBoxSize = Size(3 + POPUP_LABEL_BOX_PADDING + contentWidth + POPUP_LABEL_BOX_PADDING + 3, 3 + POPUP_LABEL_BOX_PADDING + popupLabelSize.Y + POPUP_LABEL_BOX_PADDING + 3);

	// If there are requirements, reserve space for them
	if(_selectedElement->_requiredElements.size() > 0)
		_popupLabelBoxSize.Y += 64;

	// Return size
	return Rect(3 + POPUP_LABEL_BOX_PADDING, 3 + POPUP_LABEL_BOX_PADDING, _popupLabelBoxSize.X, _popupLabelBoxSize.Y);
}

TechTreeElement* VanillaTechTreeRenderer::GetElementAtPosition(int x, int y)
{
	// Clean coordinate from other window fragments, this simplifies the calculations in the next step
	x = x - _legendFrameWidth - _agesFrameWidth;

	// Calculate tree X position
	int treeX = (x / ((64 + ELEMENT_SPACING) / 2));

	// Check for proper X values
	if(x < 0 || treeX >= 2 * _treeWidth)
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
	for(TechTreeElement *currRoot : _gameData->_techTree->GetRootElements())
		if(getElementPathRecursively(currRoot))
			break;
}