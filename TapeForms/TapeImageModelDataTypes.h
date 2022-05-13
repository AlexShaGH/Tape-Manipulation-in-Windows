#pragma once

public enum TapeObjectType
{
	DataBlock,
	FileMark,
	EODMark,
	EOTMark
};

public ref struct TapeFileMapRecord
{
public:
	System::Int64 StartBlockNumber;
	System::Int32 BlockSize;
	System::Int64 SizeInBlocks;
};

