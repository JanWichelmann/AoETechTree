/* INCLUDES */

// Class header
#include "SlpFileElement.h"

/* FUNCTIONS */

SlpFileElement::SlpFileElement(char *slpName, int slpId)
{
	// Call original function
	((SlpFileElement *(__thiscall *)(SlpFileElement *, char *, int))0x004DAE00)(this, slpName, slpId);
}

SlpFileElement::~SlpFileElement()
{
	// Call original function
	((void(__thiscall *)(SlpFileElement *))0x004DB110)(this);
}

int SlpFileElement::GetFrameSize(int frameId, int *widthPointer, int *heightPointer)
{
	// Call original function
	return ((int(__thiscall *)(SlpFileElement *, int, int *, int *))0x004DB290)(this, frameId, widthPointer, heightPointer);
}

bool SlpFileElement::DrawFrameIntoDirectDrawBuffer(DirectDrawBufferData *directDrawBufferData, int anchorX, int anchorY, int frameId, int unknown)
{
	// Call original function
	return ((bool(__thiscall *)(SlpFileElement *, DirectDrawBufferData *, int, int, int, int))0x004DB740)(this, directDrawBufferData, anchorX, anchorY, frameId, unknown);
}