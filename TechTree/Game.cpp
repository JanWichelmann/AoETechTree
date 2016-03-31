/* INCLUDES */

// Class header
#include "Game.h"

/* FUNCTIONS */

// Set static Game object pointer
Game **_staticGameObjectPointer = reinterpret_cast<Game **>(0x007912A0);

GameDataHandler *Game::GetGameDataHandler()
{
	// Return handler
	return _gameDataHandler;
}

DirectDrawHandler *Game::GetDirectDrawHandler()
{
	// Return handler
	return _directDrawHandler;
}

FontData *Game::GetFontWithIndex(int fontIndex)
{
	// Return font
	return &_fontData[fontIndex];
}

void Game::GetStringFromLanguageDllsWithBuffer(int resourceId, char *buffer, int bufferLength)
{
	// Call virtual function
	_VTable->GetStringFromLanguageDllsWithBuffer(resourceId, buffer, bufferLength);
}

int Game::SetPauseMode(int unknown1, int unknown2)
{
	// Call original function
	return ((int(__thiscall *)(Game *, int, int))0x005E7450)(this, unknown1, unknown2);
}

void Game::GetIndexedDllString(int gameMode, int index, int unknown, char *buffer, int bufferLength)
{
	// Call virtual function
	_VTable->GetIndexedDllString(this, gameMode, index, unknown, buffer, bufferLength);
}