#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes
#include "TechTreeData.h"
#include "CivData.h"
#include "ResearchData.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Contains all data readable from the empires2_x1_p1.dat.
class GameDataHandler : public GameType
{
public: // Member variables (public for simplicity reasons...maybe put wrapper functions around them later?)
	int _VTable;
	char _gap4[8];
	int _unknownValueFromGameX1;
	int _dword10;
	int _dword14;
	int _dword18;
	int _dword1C;
	int _dword20;
	int _gameSpeed;
	char _byte28;
	char _byte29;
	char _byte2A;
	char _gap_2B[1];
	int _dword2C;
	int _dword30;
	int _terrains;
	short *_soundCount;
	int _sounds;
	short _graphicCount;
	char _gap_42[2];
	int _graphics;
	short _unknown_ProbablyPlayerCount;
	char _gap_4A[2];
	int *_dword4C;
	short _civCount;
	char _gap_52[2];
	CivData **_civs;
	int _techageContainer;
	short _terrainRestrictionCount;
	short _terrainCount;
	int *_terrainRestrictionPointers1;
	int *_terrainRestrictionPointers2;
	int _unknownLargeObject_constructor426660;
	int _dword6C;
	int _dword70;
	int _dword74;
	short _playerColorCount;
	char _gap_7A[2];
	int _playerColors;
	int _maybeDatFileLoaded;
	int _dword84;
	char _gap88[4];
	char _byte8C;
	char _gap_8D[3];
	int _dword90;
	short _word94;
	char _gap96[14];
	int _directSoundHandler;
	int _dwordA8;
	int _dwordAC;
	int _dwordB0;
	int _dwordB4;
	int _dwordB8;
	int _dwordBC;
	int _dwordC0;
	char _gapC4[12];
	int _dwordD0;
	char _unknownString[36];
	int _UnknownObj1;
	int _UnknownObj2;
	int _UnknownObj3;
	int _UnknownObj4;
	int _UnknownObj5;
	int _UnknownObj6;
	int _UnknownObj7;
	int _dword114;
	int _dword118;
	int _dword11C;
	char _byte120;
	char _gap121[99];
	int _dword184;
	char _gap188[4];
	int _unitHeaders;
	int _UnitCount;
	int _dword194;
	int _dword198;
	char _gap19C[52];
	int _dword1D0;
	int _dword1D4;
	int _dword1D8;
	int _dword1DC;
	int _dword1E0;
	int _dword1E4;
	int _dword1E8;
	int _dword1EC;
	int _dword1F0;
	ResearchData *_researches;
	char _unknown1[32];
	float _unknownFloat1;
	float _unknownFloat2;
	float _unknownFloat3;
	float _unknownFloat4;
	float _unknownFloat5;
	float _unknownFloat6;
	float _unknownFloat7;
	float _unknownFloat8;
	char _unknown2[52];
	int _unknownDatValues[7];
	char _unknown3a[4];
	char _unknownByteArray[9];
	char _unknown3b[7];
	float _unknownFloat9_initial_5500;
	char _unknown3c[4];
	int _oldTechTree;
	int _unknownObj8;
	char _unknown4[4];

public:
};
#pragma pack(pop)
