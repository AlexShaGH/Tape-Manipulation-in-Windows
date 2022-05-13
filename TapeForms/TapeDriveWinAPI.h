#pragma once
#include "ITapeDrive.h"

ref class TapeDriveWinAPI : ITapeDrive
{
public:
	TapeDriveWinAPI(void);

	virtual bool Open(String^ tapeDriveName, UInt32% returnCode);
	virtual bool Close( UInt32% returnCode );

	virtual bool Load(bool immediate, UInt32% returnCode);
	virtual bool Unload(bool immediate, UInt32% returnCode);
	
	virtual bool Lock(bool immediate, UInt32% returnCode);
	virtual bool Unlock(bool immediate, UInt32% returnCode);

    virtual bool FormatTape(bool immediate, UInt32% returnCode);
	virtual bool AdjustTension(bool immediate, UInt32% returnCode);

	virtual bool Rewind(bool immediate,UInt32% returnCode);
	virtual bool SeekToEOD(UInt32 partition, bool immediate,UInt32% returnCode);
	virtual bool SeekToAbsoluteBlock(UInt64 blockAddress, bool immediate, UInt32% returnCode);
	virtual bool SeekToLogicalBlock(UInt32 partition, UInt64 blockAddress, bool immediate, UInt32% returnCode);

	virtual bool SpaceFileMarks(Int64 spaceMarksCount, bool immediate, UInt32% returnCode);
	virtual bool SpaceBlocks(Int64 spaceBlocksCount, bool immediate, UInt32% returnCode);
	virtual bool SpaceSequentialFileMarks( Int64 spacSequentialMarksCount, bool immediate, UInt32% returnCode );//does not work on LTO
	virtual bool SpaceSequentialSetMarks( Int64 spacSequentialMarksCount, bool immediate, UInt32% returnCode );//does not work on LTO
	virtual bool SpaceSetMarks(Int64 spaceMarksCount, bool immediate, UInt32% returnCode);//does not work on LTO

	virtual bool GetTapeStatusOK(UInt32% returnCode);

	virtual bool GetTapePositionAbsolute(UInt32% partition, Int64% blockAddress, UInt32% returnCode);
	virtual bool GetTapePositionLogical(UInt32% partition, Int64% blockAddress, UInt32% returnCode);

	virtual bool GetMediaParameters(TAPE_GET_MEDIA_PARAMETERS* mediaInfo, UInt32% returnCode );
	virtual bool GetDriveParameters(TAPE_GET_DRIVE_PARAMETERS* driveInfo, UInt32% returnCode );

	virtual bool SetMediaBlockSize(UInt32 blockSize,UInt32% returnCode );

	virtual bool SetTapeDriveParams(TAPE_SET_DRIVE_PARAMETERS driveParams, UInt32% returnCode );

	virtual bool PartitionTape(UInt32 partitionMethod, UInt32 patitionCount, UInt32 partitionSizeInMB, UInt32% returnCode );
	virtual bool EraseTapeDo(UInt32 eraseType, bool immediate, UInt32% returnCode );

	virtual bool WriteTapemarkDo(UInt32 tapemarkType, UInt32 tapemarkCount, bool immediate, UInt32% returnCode );

    virtual bool ReadTape(array<byte>^ buffer, UInt32 bytesToRead, UInt32% bytesRead, UInt32% returnCode);
	virtual bool WriteTape(array<byte>^ buffer, UInt32 bytesToWrite, UInt32% bytesWritten, UInt32% returnCode);

private:
	HANDLE _tapeDriveHandle;
	String^ _tapeDriveName;

	bool PrepareTapeHelper(DWORD operationType, BOOL isImmediate, UInt32% returnCode);
	bool SetTapePositionHelper(DWORD positionMethod, DWORD partition, DWORD offsetLow, DWORD offsetHigh, BOOL isImmediate, UInt32% returnCode);

	bool GetTapePositionHelper(DWORD positionType, UInt32% partition, Int64% blockAddress, UInt32% returnCode);

	bool GetTapeParametersHelper(DWORD operationType, UInt32% bufferSize, LPVOID tapeInfo, UInt32% retrunCode);
	bool SetTapeParametersHelper(DWORD operationType, LPVOID tapeInfo, UInt32% returnCode );
};

