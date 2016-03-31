#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes


/* DEFINITIONS */

#pragma pack(push, 1)
// Contains general unit data. All special unit types derive from this class.
class BaseUnitData : public GameType
{
public: // Member variables (public for simplicity reasons...maybe put wrapper functions around them later?)
	int _VTable;
	char _type;
	char gap1[3];
	char *_name;
	short _languageDllNameId;
	short _languageDllCreationId;
	short _id1;
	short _id2;
	short _id3;
	short _class;
	int _standingGraphic1;
	int _standingGraphic2;
	int _dyingGraphic1;
	int _dyingGraphic2;
	char _deathMode;
	char gap2;
	short _hitPoints;
	float _lineOfSight;
	char _garrisonCapacity;
	char gap3[3];
	float _sizeRadius1;
	float _sizeRadius2;
	float _hpBarHeight1;
	int _selectionSound;
	int _trainSound1;
	int _dyingSound;
	int _trainSound2;
	short _deadUnitID;
	char _placementMode;
	char _airMode;
	short _iconID;
	char _hideInEditor;
	char gap4;
	short _unknownDatValue1;
	char _enabled;
	char _disabled;
	short _placementBypassTerrain1;
	short _placementBypassTerrain2;
	short _placementTerrain1;
	short _placementTerrain2;
	float _editorRadius1;
	float _editorRadius2;
	char _hillMode;
	char _visibleInFog;
	short _terrainRestriction;
	char _flyMode;
	char gap4b;
	short _resourceStorageTypes[3];
	float _resourceStorageAmounts[3];
	short _resourceCapacity;
	short gap5;
	float _resourceDecay;
	float _unknownDatValue3A;
	char _resourceStorageEnableds[3];
	char _blastType;
	char _unknownDatValue2;
	char _interactionMode;
	char _minimapMode;
	char _commandAttribute;
	char _minimapColor;
	char _attackMode;
	char _edibleMeat;
	char _damageGraphicCount;
	int  _damageGraphics;
	char _selectionMask;
	char _selectionShapeType;
	char _selectionShape;
	char gap7b;
	int _attribute_Civilization_Nothing;
	int _languageDLLHelp;
	int _languageDLLHotKeyText;
	int _hotKey;
	char _unselectable;
	char _unknownDatValue6;
	char _unknownSelectionMode;
	char _unknownDatValue8;
	char _selectionEffect;
	char _editorSelectionColor;
	char gap8[2];
	float _selectionRadius1;
	float _selectionRadius2;
	float _hpBarHeight2;

public:

};
#pragma pack(pop)

