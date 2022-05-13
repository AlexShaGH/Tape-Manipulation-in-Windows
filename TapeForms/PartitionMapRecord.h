#pragma once

#include "TapeImageModelDataTypes.h"
#include "TapeFile.h"

ref class PartitionMapRecord
{
public:
	PartitionMapRecord(void);

	System::Int64 StartBlockNumber;
	System::Int64 SizeInBlocks;

	TapeObjectType _type;
	TapeFile^ _linkedFile;

};

