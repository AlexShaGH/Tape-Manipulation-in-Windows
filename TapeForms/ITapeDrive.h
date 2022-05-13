#pragma once
#include "CommonDefinitions.h"

using namespace System;

interface class ITapeDrive
{
public:
	bool Open(String^ tapeDriveName, UInt32% returnCode);
	bool Close( UInt32% returnCode );

	bool Load(bool immediate, UInt32% returnCode);
	bool Unload(bool immediate, UInt32% returnCode);

	bool Rewind(bool immediate,UInt32% returnCode);
	bool SeekToEOD(UInt32 partition, bool immediate,UInt32% returnCode);

//	bool SpaceBlocks(long blocksToSpace, ref uint returnCode);
//	bool SpaceFileMarks(long filemarksToSpace, ref uint returnCode);
//	bool SeekToLogicalBlock(long blockAddress, ref uint returnCode);
//	bool SeekToAbsoluteBlock(long blockAddress, ref uint returnCode);

//	ITapeDrive(void);
};

