#include "StdAfx.h"
#include "TapeDriveWinAPI.h"

TapeDriveWinAPI::TapeDriveWinAPI(void)
{
}

bool TapeDriveWinAPI::Open( String^ tapeDriveName, UInt32% returnCode )
{
	try
	{// try to open device	
		
		pin_ptr<const wchar_t> wName = PtrToStringChars(tapeDriveName);
	
		_tapeDriveHandle = CreateFile(
			wName,
			GENERIC_READ | GENERIC_WRITE,
			0, // do not share
			NULL, // default security descriptor
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL // no flags or attributes
		);
	}
	catch(Exception^)
	{
		_tapeDriveHandle = INVALID_HANDLE_VALUE;
	};

	if (_tapeDriveHandle == INVALID_HANDLE_VALUE)
	{
		returnCode = GetLastError();

		// clean up
		_tapeDriveName = nullptr;
		_tapeDriveHandle = nullptr;

		return false;
	}

	returnCode = ERROR_SUCCESS;

	// initialize private members
	_tapeDriveName = tapeDriveName;

	return true;
}

bool TapeDriveWinAPI::Close( UInt32% returnCode )
{
	bool returnValue = true;
	returnCode = ERROR_SUCCESS;

	// is it legit?
	if (_tapeDriveHandle != nullptr &&
		_tapeDriveHandle != INVALID_HANDLE_VALUE
		)
	{// it is! Proceed with closing

		if ( CloseHandle(_tapeDriveHandle) == FALSE )
		{
			returnValue = false;
			returnCode = GetLastError();
		}
	}

	_tapeDriveName = nullptr;
	_tapeDriveHandle = nullptr;

	return returnValue;
}

bool TapeDriveWinAPI::PrepareTapeHelper(DWORD operationType, BOOL isImmediate, UInt32% returnCode)
{
	try
	{
		returnCode = PrepareTape(
			_tapeDriveHandle,
			operationType,
			isImmediate
			);
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;
}

bool TapeDriveWinAPI::Load(bool immediate, UInt32% returnCode)
{
	return PrepareTapeHelper(TAPE_LOAD, immediate, returnCode);
}

bool TapeDriveWinAPI::Unload(bool immediate, UInt32% returnCode)
{
	return PrepareTapeHelper(TAPE_UNLOAD, immediate, returnCode);
}

bool TapeDriveWinAPI::Lock(bool immediate, UInt32% returnCode)
{
	return PrepareTapeHelper(TAPE_LOCK, immediate, returnCode);
}

bool TapeDriveWinAPI::Unlock(bool immediate, UInt32% returnCode)
{
	return PrepareTapeHelper(TAPE_UNLOCK, immediate, returnCode);
}

bool TapeDriveWinAPI::FormatTape(bool immediate, UInt32% returnCode)
{
	return PrepareTapeHelper(TAPE_FORMAT,  immediate, returnCode);
}

bool TapeDriveWinAPI::AdjustTension(bool immediate, UInt32% returnCode)
{
	return PrepareTapeHelper(TAPE_TENSION,  immediate, returnCode);
}

bool TapeDriveWinAPI::SetTapePositionHelper( DWORD positionMethod, DWORD partition, DWORD offsetLow, DWORD offsetHigh, BOOL isImmediate, UInt32% returnCode )
{
	try
	{
		returnCode = SetTapePosition(
			_tapeDriveHandle,
			positionMethod,
			partition,
			offsetLow,
			offsetHigh,
			isImmediate
			);
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;
}

bool TapeDriveWinAPI::Rewind( bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_REWIND, 0, 0, 0, immediate, returnCode);
}

bool TapeDriveWinAPI::SeekToEOD(UInt32 partition, bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_SPACE_END_OF_DATA, partition, 0, 0, immediate, returnCode);
}

bool TapeDriveWinAPI::SeekToAbsoluteBlock(UInt64 blockAddress, bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_ABSOLUTE_BLOCK, 0, (UInt32)blockAddress, (UInt32)(blockAddress>>32), immediate, returnCode);
}

bool TapeDriveWinAPI::SeekToLogicalBlock( UInt32 partition, UInt64 blockAddress, bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_LOGICAL_BLOCK, partition, (UInt32)blockAddress, (UInt32)(blockAddress>>32), immediate, returnCode);
}

bool TapeDriveWinAPI::SpaceFileMarks( Int64 spaceMarksCount, bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_SPACE_FILEMARKS, 0, (UInt32)spaceMarksCount, (UInt32)(spaceMarksCount>>32), immediate, returnCode);
}

bool TapeDriveWinAPI::SpaceBlocks( Int64 spaceBlocksCount, bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_SPACE_RELATIVE_BLOCKS, 0, (UInt32)spaceBlocksCount, (UInt32)(spaceBlocksCount>>32), immediate, returnCode);
}

bool TapeDriveWinAPI::SpaceSequentialFileMarks( Int64 spacSequentialMarksCount, bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_SPACE_SEQUENTIAL_FMKS, 0, (UInt32)spacSequentialMarksCount, (UInt32)(spacSequentialMarksCount>>32), immediate, returnCode);
}

bool TapeDriveWinAPI::SpaceSequentialSetMarks( Int64 spacSequentialMarksCount, bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_SPACE_SEQUENTIAL_SMKS, 0, (UInt32)spacSequentialMarksCount, (UInt32)(spacSequentialMarksCount>>32), immediate, returnCode);
}

bool TapeDriveWinAPI::SpaceSetMarks( Int64 spaceMarksCount, bool immediate, UInt32% returnCode )
{
	return SetTapePositionHelper(TAPE_SPACE_SETMARKS, 0, (UInt32)spaceMarksCount, (UInt32)(spaceMarksCount>>32), immediate, returnCode);
}

bool TapeDriveWinAPI::GetTapeStatusOK( UInt32% returnCode )
{
	try
	{
		returnCode =  GetTapeStatus(_tapeDriveHandle);
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;
}

bool TapeDriveWinAPI::GetTapePositionHelper( DWORD positionType, UInt32% partition, Int64% blockAddress, UInt32% returnCode )
{
	try
	{
		DWORD offsetLow = 0;
		DWORD offsetHigh = 0;
		pin_ptr<UInt32> part = &partition;

		returnCode = GetTapePosition(
			_tapeDriveHandle,
			positionType,
			(LPDWORD)part,
			&offsetLow,
			&offsetHigh
			);

		blockAddress = (((Int64)offsetHigh)<<32) + (Int64)offsetLow;
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;

}

bool TapeDriveWinAPI::GetTapePositionAbsolute( UInt32% partition, Int64% blockAddress, UInt32% returnCode )
{
	return GetTapePositionHelper(TAPE_ABSOLUTE_POSITION, partition, blockAddress, returnCode);
}

bool TapeDriveWinAPI::GetTapePositionLogical( UInt32% partition, Int64% blockAddress, UInt32% returnCode )
{
	return GetTapePositionHelper(TAPE_LOGICAL_POSITION, partition, blockAddress, returnCode);
}

bool TapeDriveWinAPI::GetTapeParametersHelper(DWORD operationType, UInt32% bufferSize, LPVOID tapeInfo, UInt32% returnCode )
{
	
	try
	{
		pin_ptr<UInt32> bufSize = &bufferSize;

		returnCode = GetTapeParameters(
			_tapeDriveHandle,
			operationType,
			(LPDWORD)bufSize,
			tapeInfo
			);

	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;	
}

bool TapeDriveWinAPI::GetMediaParameters(TAPE_GET_MEDIA_PARAMETERS* mediaInfo, UInt32% returnCode )
{
	UInt32 bufferSize = sizeof(TAPE_GET_MEDIA_PARAMETERS);
	memset(mediaInfo,0,bufferSize);

	return GetTapeParametersHelper(GET_TAPE_MEDIA_INFORMATION, bufferSize, mediaInfo, returnCode );
}

bool TapeDriveWinAPI::GetDriveParameters( TAPE_GET_DRIVE_PARAMETERS* driveInfo, UInt32% returnCode )
{
	UInt32 bufferSize = sizeof(TAPE_GET_DRIVE_PARAMETERS);
	memset(driveInfo,0,bufferSize);

	return GetTapeParametersHelper(GET_TAPE_DRIVE_INFORMATION, bufferSize, driveInfo, returnCode );
}


bool TapeDriveWinAPI::SetTapeParametersHelper(DWORD operationType, LPVOID tapeParams, UInt32% returnCode )
{
	try
	{
		returnCode = SetTapeParameters(
			_tapeDriveHandle,
			operationType,
			tapeParams
			);
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;

}

bool TapeDriveWinAPI::SetMediaBlockSize( UInt32 blockSize,UInt32% returnCode )
{
	TAPE_SET_MEDIA_PARAMETERS  mediaParam;

	mediaParam.BlockSize = blockSize;
	
	return SetTapeParametersHelper(SET_TAPE_MEDIA_INFORMATION, &mediaParam, returnCode);
}

bool TapeDriveWinAPI::SetTapeDriveParams(TAPE_SET_DRIVE_PARAMETERS driveParams, UInt32% returnCode )
{
	return SetTapeParametersHelper(SET_TAPE_DRIVE_INFORMATION, &driveParams, returnCode);
}

bool TapeDriveWinAPI::PartitionTape( UInt32 partitionMethod, UInt32 patitionCount, UInt32 partitionSizeInMB, UInt32% returnCode )
{
	try
	{
		returnCode = CreateTapePartition(
			_tapeDriveHandle,
			partitionMethod,
			patitionCount,
			partitionSizeInMB
			);
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;

}

bool TapeDriveWinAPI::EraseTapeDo( UInt32 eraseType, bool immediate, UInt32% returnCode )
{
	try
	{
		returnCode = EraseTape(
			_tapeDriveHandle,
			eraseType,
			immediate
			);
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;
}

bool TapeDriveWinAPI::WriteTapemarkDo( UInt32 tapemarkType, UInt32 tapemarkCount, bool immediate, UInt32% returnCode )
{
	try
	{
		returnCode = WriteTapemark(
			_tapeDriveHandle,
			tapemarkType,
			tapemarkCount,
			immediate
			);
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		return false;
	}

	if (returnCode == NO_ERROR) return true;

	return false;
}

bool TapeDriveWinAPI::ReadTape( array<byte>^ buffer, UInt32 bytesToRead, UInt32% bytesRead, UInt32% returnCode )
{
	BOOL returnValue = FALSE;

	try
	{

		pin_ptr<UInt32> pBytesRead = &bytesRead;
		pin_ptr<byte> pBuffer = &buffer[0];

		returnValue = ReadFile(
			_tapeDriveHandle,
			pBuffer,
			bytesToRead,
			(LPDWORD)pBytesRead,
			NULL
			);

		if (returnValue == FALSE)
		{
			returnCode = GetLastError();
		}
		else
		{ 
			returnCode = NO_ERROR;
		}
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		returnValue = FALSE;
	}

	return (returnValue == TRUE);
}

bool TapeDriveWinAPI::WriteTape( array<byte>^ buffer, UInt32 bytesToWrite, UInt32% bytesWritten, UInt32% returnCode )
{
	BOOL returnValue = FALSE;

	try
	{
		pin_ptr<UInt32> pBytesWritten = &bytesWritten;
		pin_ptr<byte> pBuffer = &buffer[0];

		returnValue = WriteFile(
			_tapeDriveHandle,
			pBuffer,
			bytesToWrite,
			(LPDWORD)pBytesWritten,
			NULL
			);

		if (returnValue == FALSE)
		{
			returnCode = GetLastError();
		}
		else
		{ 
			returnCode = NO_ERROR;
		}
	}
	catch(Exception^)
	{
		returnCode = GetLastError();
		returnValue = FALSE;
	}

	return (returnValue == TRUE);
}









