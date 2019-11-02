#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes
#include "SlpFile.h"
#include "SlpFrameHeader.h"
#include "DirectDrawBufferData.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an SLP file element.
class SlpFileElement : public GameType
{
protected: // Member variables
	int SlpDataArrayWasAllocated;
	int SlpDataSize;
	int UnknownValue3;
	SlpFile *SlpData;
	SlpFrameHeader *FirstFrameHeaderPointer;
	int MaybeSlpExists;
	int FrameCount;

public:
	// Constructor. Load the given SLP file.
	// Parameters:
	// -> slpName: The name of the SLP file (usually optional).
	// -> slpId: The resource ID of the SLP file.
	SlpFileElement(const char *slpName, int slpId);

	// Destructor.
	~SlpFileElement();

	// Gets the size of the frame with the given index.
	// Parameter:
	// -> frameId: The ID of the frame.
	// -> widthPointer: A pointer to a variable to put the frame width into.
	// -> heightPointer: A pointer to a variable to put the frame height into.
	int GetFrameSize(int frameId, int *widthPointer, int *heightPointer);

	// Draws the frame with the given ID into the specified DirectDrawBuffer.
	// Parameter:
	// -> directDrawBufferData: The target buffer.
	// -> anchorX: The buffer X position where the frame anchor point should be.
	// -> anchorY: The buffer Y position where the frame anchor point should be.
	// -> frameId: The ID of the frame.
	// -> unknown: Unknown.
	bool DrawFrameIntoDirectDrawBuffer(DirectDrawBufferData *directDrawBufferData, int anchorX, int anchorY, int frameId, int unknown);
};
#pragma pack(pop)
