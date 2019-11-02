/* INCLUDES */

// Class header
#include "Shape.h"

/* FUNCTIONS */

Shape::Shape(const char *slpName, int slpId)
{
	// Call original function
	((Shape *(__thiscall *)(Shape *, const char *, int))0x004DAE00)(this, slpName, slpId);
}

Shape::~Shape()
{
	// Call original function
	((void(__thiscall *)(Shape *))0x004DB110)(this);
}

int Shape::GetFrameSize(int frameId, int *widthPointer, int *heightPointer)
{
	// Call original function
	return ((int(__thiscall *)(Shape *, int, int *, int *))0x004DB290)(this, frameId, widthPointer, heightPointer);
}

bool Shape::DrawFrameIntoDirectDrawBuffer(DirectDrawArea *directDrawBufferData, int anchorX, int anchorY, int frameId, int unknown)
{
	// Call original function
	return ((bool(__thiscall *)(Shape *, DirectDrawArea *, int, int, int, int))0x004DB740)(this, directDrawBufferData, anchorX, anchorY, frameId, unknown);
}
