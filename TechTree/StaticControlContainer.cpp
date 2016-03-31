/* INCLUDES */

// Class header
#include "StaticControlContainer.h"

/* FUNCTIONS */

bool StaticControlContainer::SwitchToControl(char *controlTypeName, int unknown)
{
	// Call original function
	return ((bool(__thiscall *)(StaticControlContainer *, char *, int))0x00560320)(this, controlTypeName, unknown);
}

int StaticControlContainer::RemoveControlFromListWithDestructorCall(char *controlTypeName)
{
	// Call original function
	return ((int(__thiscall *)(StaticControlContainer *, char *))0x00560510)(this, controlTypeName);
}

StaticControlContainer *StaticControlContainer::GetStaticHandle()
{
	// Return original handle
	return reinterpret_cast<StaticControlContainer *>(0x007861B8);
}