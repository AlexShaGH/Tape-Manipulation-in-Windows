#pragma once
public ref struct RangeRecord {

	System::Int64 StartBlockNumber;
	System::Int32 BlockSize;
	System::Int64 SizeInBlocks;
};

/*structure RangeRecord
{
public:
	RangeRecord(void);

	System::Int64 _startBlckNumber;
	System::Int64 StartBlckNumber() { return _startBlckNumber; }
	void StartBlckNumber(System::Int64 val) { _startBlckNumber = val; }

	System::Int32 _blckSize;
	System::Int32 BlckSize() { return _blckSize; }
	void BlckSize(System::Int32 val) { _blckSize = val; }

	System::Int64 _sizeInBlks;
	System::Int64 SizeInBlks() { return _sizeInBlks; }
	void SizeInBlks(System::Int64 val) { _sizeInBlks = val; }
};*/

