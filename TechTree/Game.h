#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"
#include "VTableType.h"

// Other includes
#include "DirectDrawHandler.h"
#include "DirectDrawArea.h"
#include "Shape.h"
#include "GameDataHandler.h"
#include "FontData.h"

/* DEFINITIONS */

// Prototype for virtual function table class
class GameVTable;

#pragma pack(push, 1)
// Represents the main game class.
class Game : public GameType
{
private:
	typedef GameType base;

protected: // Member variables
	GameVTable *_VTable;
	char _unknown1a1[28];
	int _playerInfoFile;
	int _scenarioInfoFile;
	int _mainGameData;
	HWND _mainWindowHWnd;
	int _unknown1b1a_maybeGameClassInitFlag;
	int _unknownDrawingRelated;
	HPALETTE _mainPalette;
	HANDLE _gameMutex;
	char _unknown1b2[24];
	int _screenSaverEnabled;
	int _lowPowerScreenSaverEnabled;
	int _unknown1b_val1;
	int _errorCode;
	int _unknown50SecondTimerHandle;
	DirectDrawHandler *_directDrawHandler;
	DirectDrawArea *_backBufferData;
	int _unknownValue2a1;
	int _useGameMouseCursors;
	short _specialSymbolCount;
	short _unknownValue2a;
	Shape **_specialSymbols;
	int _directSoundHandler;
	int _backgroundMusicHandler;
	int _interfaceSoundFileCount;
	int _interfaceSoundFiles;
	int _soundSamplesPerSecond;
	int _foregroundSoundHandler;
	char _unknown2a2[284];
	int _unknownValueGivenToGameDataHandler;
	char _unknown2a3[20];
	int _maybeLogger;
	char _unknown2b[8];
	int _registryHandles;
	int _maybeApplicationIsNotFocused;
	char _unknown3a1[12];
	int _customMouseCursorData;
	char _unknown3a2[4];
	int _mSyncCmdParam;
	int _mouseCursorVisible;
	int _useDefaultSystemMouseCursor;
	HCURSOR _currentCursor;
	int _mouseEnabled;
	HWND _inputDisabledWindowHWnd;
	int _fontCount;
	FontData *_fontData;
	char _baseDirectory[261];
	char _languageDllPath[261];
	char _unknown4a[2];
	GameDataHandler *_gameDataHandler;
	int _maybeUnknownWindowFlagsSet;
	char _unknown4b1[320];
	int _unknownValue4b1;
	char _unknown4b2[24];
	int _unknownValue4b2;
	char _unknown4b3[28];
	int _unknownValue4b3;
	char _unknown4b4[28];
	int _unknownValue4b4;
	char _unknown4b5[32];
	int _unknownValue4b5;
	char _unknown4b6[184];
	int _unknownValue4b6;
	char _unknown4b7[92];
	int _unknownValue4b7;
	char _unknown4b8[549];
	char _unknownString4b8[128];
	bool _singlePlayerMode;
	bool _multiPlayerMode;
	char _unknown4b10[33];
	float _gameSpeedMultiPlayer;
	char _unknown5a[376];
	int _rollOverText;
	int _unknownValue5;
	char _unknownSoundFilePaths[5][260];
	int _unknownSoundFilePathsSeekValues[5];
	char _unknown5b[20];
	float _gameSpeedSinglePlayer;
	int _difficulty;
	char _unknown6a1a;
	char _unknown6a1b[9];
	char _unknown6a1c;
	char _unknown6a1d;
	DirectDrawArea *_diamondMapSaveAreaBufferData;
	char _gameZoneCallCommand[255];
	char _httpShellCommand[257];
	int _unknown6a1e;
	char _unknownString[259];
	char _unknown6a2[147];
	char _populationLimitCmdParam;
	char _unknown6a_String[1];
	char _unknown6b[656];
	int _unknown6_1596;
	int _unknown6_1600;
	int _unknown6_1604;
	int _unknown6_1608;
	int _unknown6_1612;
	int _unknown6_1616;
	int _unknown6_1620;
	int _unknown6_1624;
	int _unknown6_1628;
	int _unknown6_1632;
	int _unknown6_1636;
	int _unknown6_1640;
	int _unknown6_1644;
	char _languageX1DllFileName[264];
	int _unknown7_0;
	int _unknown7_4;
	int _unknown7_8;
	int _unknown7_12;
	char _unknown7[1560];
	char _unknown7String[36];
	char _unknown8a[9];
	char _unknown8b[380];
	char _unknown8c[63];
	int _advancedButtonsSetting;
	int _oneClickGarrionSetting;
	char _unknown8d[4];

public:
	// Hide base class function.
	static void __Install();

	// Returns the game data handler.
	GameDataHandler *GetGameDataHandler();

	// Returns the DirectDraw handler.
	DirectDrawHandler *GetDirectDrawHandler();

	// Returns the font data with the specified index.
	// Parameter:
	// -> fontIndex: The index of the font.
	FontData *GetFontWithIndex(int fontIndex);

	// Copies the requested language DLL string into the given buffer.
	// Parameters:
	// -> resourceId: The ID of the requested DLL string.
	// -> buffer: The buffer where the returned string shall be stored.
	// -> bufferLength: The size of the specified buffer.
	void GetStringFromLanguageDllsWithBuffer(int resourceId, char *buffer, int bufferLength);

	// Sets the game pause mode.
	// Parameters:
	// -> unknown1: Unknown.
	// -> unknown2: Unknown.
	int SetPauseMode(int unknown1, int unknown2);

	// Copies the DLL string with the given special index.
	// Parameters:
	// -> gameMode: The current game mode.
	// -> index: The index of the requested string.
	// -> unknown: Unknown.
	// -> buffer: The destination buffer for the string.
	// -> bufferLength: The size of the destination buffer.
	void GetIndexedDllString(int gameMode, int index, int unknown, char *buffer, int bufferLength);
};
#pragma pack(pop)

#pragma pack(push, 1)
// Represents the virtual function table of the Game class.
class GameVTable : public VTableType
{
public: // Function pointers
	void(__thiscall *ScalarDeletingDestructor)(Game *, char);
	int(__thiscall *Run)(Game *);
	int(__thiscall *HandleWindowMessage)(Game *, HWND, UINT, WPARAM, LPARAM);
	void(__thiscall *SetMaybeApplicationIsNotFocused)(Game *, int);
	int functionPointers1b[3];
	int(__thiscall *GetErrorCode)(Game *);
	int functionPointers2[1];
	char *(__thiscall *GetStringFromLanguageDlls)(Game *, int);
	void(__stdcall *GetStringFromLanguageDllsWithBuffer)(int, char *, int);
	void(__thiscall *GetIndexedDllString)(Game *, int, int, int, char *, int);
	int functionPointers3aa[17];
	bool(__thiscall *CreateBackgroundMusicHandler)(Game *);
	int functionPointers3ab[14];
	bool(__thiscall *ParseCommandLine)(Game *);
	int(__thiscall *CreateAndRegisterWindowClass)(Game *);
	bool(__thiscall *CreateMainWindow)(Game *);
	bool(__thiscall *CreateAndInitializeDirectDrawHandles)(Game *);
	bool(__thiscall *Load50500Palette)(Game *);
	bool(__thiscall *LoadMouseCursors)(Game *);
	int functionPointers3b1a[2];
	bool(__thiscall *InitializeSound_TauntRelated)(Game *);
	int functionPointers3b1a2;
	bool(__thiscall *InitializeSound)(Game *);
	HDC(__thiscall *LoadFonts)(Game *);
	bool(__thiscall *LoadInterfaceSounds)(Game *);
	int(__thiscall *LoadSpecialSymbols)(Game *);
	bool(__thiscall *CreateBlankScreenWindow)(Game *);
	void(__thiscall *sub_5E6970)(Game *);
	int functionPointers3b2[4];
	GameDataHandler *(__thiscall *CreateGameDataHandler)(Game *);
	int functionPointers3b3a;
	void(__thiscall *DoUpdate)(Game *);
	int functionPointers3b3b[5];
	bool(__thiscall *EmptyMessageHandlerAlwaysTrue)(Game *, HWND, UINT, WPARAM, LPARAM);
	bool(__thiscall *HandlePaintEvent)(Game *, HWND, UINT, WPARAM, LPARAM);
	int functionPointers3c1[3];
	bool(__thiscall *sub_5E8960)(Game *, HWND, int, int, int);
	int functionPointers3c2[4];
	int(__stdcall *AlwaysOne1)();
	int functionPointers3d[4];
	int(__stdcall *AlwaysOne2)();
	int(__stdcall *AlwaysOne3)();
	int(__stdcall *AlwaysOne4)();
	int(__stdcall *AlwaysOne5)();
	int(__stdcall *AlwaysOne6)();
	int(__stdcall *AlwaysOne7)();
	int functionPointers3e[6];
	bool(__thiscall *CreateDiamondMapSaveAreaBuffer)(Game *);
	int functionPointers3f;
};
#pragma pack(pop)

// The static Game object neccessary to access various game resources, data files, ...
// As this object only exists at some point on runtime, it cannot be initialized at startup.
// Instead it is given as pointer-to-pointer, so to access the game object the pointer needs to be dereferenced once.
// Clearly this should only be done if the startup process has progressed enough for the object to exist.
extern Game **_staticGameObjectPointer;