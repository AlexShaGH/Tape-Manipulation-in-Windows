#pragma once

#include "PartitionMapRecord.h"

ref class TapePartition
{
public:
	TapePartition(void);

	List<PartitionMapRecord^>^ _partitionMap;
};

