#pragma once

#include "TapeCartridgeMemory.h"
#include "TapePartition.h"

ref class TapeImage
{
public:
	TapeImage(void);

	TapeCartridgeMemory^ _cm;
	List<TapePartition^>^ _partitions;

};

