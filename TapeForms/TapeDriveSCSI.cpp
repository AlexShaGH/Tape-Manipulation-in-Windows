#include "StdAfx.h"
#include "TapeDriveSCSI.h"


TapeDriveSCSI::TapeDriveSCSI(void)
{
}

bool TapeDriveSCSI::Open( String^ tapeDriveName, UInt32% returnCode )
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

bool TapeDriveSCSI::Close( UInt32% returnCode )
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

bool TapeDriveSCSI::Load( bool immediate, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	return LoadUnload(true,immediate,returnCode,snsInfo);
}

bool TapeDriveSCSI::Unload( bool immediate, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	return LoadUnload(false,immediate,returnCode,snsInfo);
}


bool TapeDriveSCSI::ExecuteCommand( SCSI_PASS_THROUGH_DIRECT_WITH_SENSE &sptdws, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo ) 
{
	bool returnResult = false;
	DWORD returnedBytes = 0;

	snsInfo = gcnew ERROR_SNS_INFO();
	
	BOOL devIOControlResult = DeviceIoControl(
		_tapeDriveHandle,
		IOCTL_SCSI_PASS_THROUGH_DIRECT,
		&sptdws,
		sizeof(sptdws),
		&sptdws,
		sizeof(sptdws),
		&returnedBytes,
		LPOVERLAPPED(NULL)
		);

	// check return value and process the result
	if (devIOControlResult)
	{// OK - still need to go through the SCSI specific mechanism of checking for status

		Byte scsiStatus = sptdws.SPTD.ScsiStatus;

		switch (scsiStatus)
		{
		case 0x00:// 0x00 = GOOD - no need to check for sense conditions
			returnCode = ERROR_SUCCESS;
			returnResult = true;
			break;
		case 0x02:// 0x02 = CHECK CONDITION - need to analyze sense data
			snsInfo = GetSense(sptdws);
			returnCode = ERROR_SUCCESS;
			returnResult = false;
			break;
		default:// anything else
			returnCode = ERROR_INTERNAL_ERROR; //fake it here for now
			returnResult = false;
			// pick up sense info too
			snsInfo = GetSense(sptdws);
			break;
		}
	}
	else
	{// NOT OK
		returnCode = GetLastError();
		returnResult = false;
		// pick up sense info too
		snsInfo = GetSense(sptdws);
	}

	return returnResult;
}


bool TapeDriveSCSI::LoadUnload( bool loadOp, bool immediate, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x1b; // LOAD/UNLOAD CMD
	if(immediate)
	{
		sptdws.SPTD.Cdb[1] = 1; // immediate
	}
	else 
	{
		sptdws.SPTD.Cdb[1] = 0; // not immediate
	}

	if(loadOp)
	{
		sptdws.SPTD.Cdb[4] = 1; // 1 = load 
	}
	else
	{
		sptdws.SPTD.Cdb[4] = 0; // 0 = unload
	}

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

ERROR_SNS_INFO^ TapeDriveSCSI::GetSNSInfoFromFixedData( PSENSE_DATA snsData )
{
	ERROR_SNS_INFO^ snsInfo = gcnew ERROR_SNS_INFO();

	snsInfo->SNSKey = snsData->SNSDataFixed.SNSKey;
	snsInfo->ASC = snsData->SNSDataFixed.ASC;
	snsInfo->ASCQ = snsData->SNSDataFixed.ASCQ;
	snsInfo->FRU = snsData->SNSDataFixed.FieldReplacableUnitCode;

	return snsInfo;
}

ERROR_SNS_INFO^ TapeDriveSCSI::GetSNSInfoFromDescriptorData(PSENSE_DATA snsData)
{
	ERROR_SNS_INFO^ snsInfo = gcnew ERROR_SNS_INFO();;

	snsInfo->SNSKey = snsData->SNSDataDescriptor.SNSKey;
	snsInfo->ASC = snsData->SNSDataDescriptor.ASC;
	snsInfo->ASCQ = snsData->SNSDataDescriptor.ASCQ;
	snsInfo->FRU = 00; // FAKE IT FOR NOW

	return snsInfo;
}

ERROR_SNS_INFO^ TapeDriveSCSI::GetSense(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE% sptdws)
{
	if(sptdws.SPTD.SenseInfoLength == 0) 
	{
		// what to do here?
		throw gcnew Exception("Check Condition is set but Sense Length is 0");
	}
	else
	{
		// retrieve all sense codes according to the format

		Byte responseCode = sptdws.SNSData.SNSData[0] & 0x7F;

		switch(responseCode)
		{
		case 0x70:// current info in fixed format
			return GetSNSInfoFromFixedData( &sptdws.SNSData );
		case 0x71:// deferred error in fixed format
			return GetSNSInfoFromFixedData( &sptdws.SNSData );
		case 0x72:// current info in descriptor format
			return GetSNSInfoFromDescriptorData( &sptdws.SNSData );
		case 0x73:// deferred error in descriptor format
			return GetSNSInfoFromDescriptorData( &sptdws.SNSData );
		case 0x7F:// vendor specific
			throw gcnew Exception("Unable to process vendor specific sense");
			break;
		default:
			throw gcnew Exception("Unrecognized sense info");
			break;
		}
	}

}


//************************************
// Method:    FormatTape
// FullName:  TapeDriveSCSI::FormatTape
// Access:    virtual public 
// Returns:   bool
// Qualifier:
// Parameter: Byte formatType
//		0h - Use default format - Ultrium 4 and later Data cartridge
//		1h - Partition medium - Ultrium 5 and later Data cartridge
//		2h - Default format then partition - Ultrium 5 and later Data cartridge
//		3h-7h - Reserved
//		8h-Fh - Vendor specific
// Parameter: bool immediate
// Parameter: bool verify
// Parameter: UInt32% returnCode
// Parameter: ERROR_SNS_INFO^ snsInfo
//************************************
bool TapeDriveSCSI::FormatTape( Byte formatType, bool immediate, bool verify, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x04; // FORMAT MEDIUM CMD

	sptdws.SPTD.Cdb[1] = 0;

	if(immediate)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x01 ; // immediate
	}

	if(verify)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x02 ; // verify
	}

	sptdws.SPTD.Cdb[2] = formatType & 0x0F;

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

bool TapeDriveSCSI::EraseTape( bool longErase, bool immediate, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x19; // ERASE CMD

	sptdws.SPTD.Cdb[1] = 0;

	if(immediate)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x02 ; // immediate
	}

	if(longErase)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x01 ; // verify
	}

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

bool TapeDriveSCSI::Rewind( bool immediate,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x01; // rewind

	sptdws.SPTD.Cdb[1] = 0;

	if(immediate)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x01 ; // immediate
	}

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

bool TapeDriveSCSI::ReadPositionShort( READ_POSITION_SHORT& positionInfo, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	return ReadPosition(&positionInfo, ShortForm, returnCode, snsInfo );
}

bool TapeDriveSCSI::ReadPositionLong( READ_POSITION_LONG& positionInfo, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	return ReadPosition(&positionInfo, LongForm, returnCode, snsInfo );
}

bool TapeDriveSCSI::ReadPositionExtended( READ_POSITION_EXTND& positionInfo, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	return ReadPosition(&positionInfo, ExtendedForm, returnCode, snsInfo );
}

bool TapeDriveSCSI::ReadPosition(PVOID pPositionInfo, ReadPositionServiceAction action, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 10;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_IN;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x34; // Read Position

	switch (action)
	{
		case ShortForm:
			sptdws.SPTD.DataTransferLength = sizeof(READ_POSITION_SHORT);
			// Service action
			sptdws.SPTD.Cdb[1] = ShortForm & 0x1F;
			//Allocation Length
			sptdws.SPTD.Cdb[7] = 0;
			sptdws.SPTD.Cdb[8] = 0;
			break;
		case LongForm:
			sptdws.SPTD.DataTransferLength = sizeof(READ_POSITION_LONG);
			// Service action
			sptdws.SPTD.Cdb[1] = LongForm & 0x1F;
			//Allocation Length
			sptdws.SPTD.Cdb[7] = 0;
			sptdws.SPTD.Cdb[8] = 0;
			break;
		case ExtendedForm:
			sptdws.SPTD.DataTransferLength = sizeof(READ_POSITION_EXTND);
			// Service action
			sptdws.SPTD.Cdb[1] = ExtendedForm & 0x1F;
			//Allocation Length
			sptdws.SPTD.Cdb[7] = 0;
			sptdws.SPTD.Cdb[8] = 0x1C;
			break;
		default:
			returnCode = ERROR_INTERNAL_ERROR; //fake it here for now
			returnResult = false;
			break;
	}

	sptdws.SPTD.DataBuffer = pPositionInfo;
	memset(pPositionInfo,0,sizeof(sptdws.SPTD.DataTransferLength));

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

bool TapeDriveSCSI::LocateCDB10( bool changePartition, bool immediate, BYTE partitionNumber, UInt32 logicalObjIdnf, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 10;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x2B; // locate - cdb 10

	sptdws.SPTD.Cdb[1] = 0;

	if(immediate)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x01 ; // immediate
	}

	if(changePartition)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x02 ; // change partition
	}

	// bit 3 must be set to 0 for now = BT (block type - not supported as of LTO-6)
	sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] & 0xFB ;

	// set Logical Object Idnf:
	sptdws.SPTD.Cdb[3] = (BYTE)((logicalObjIdnf>>24) & 0xFF);
	sptdws.SPTD.Cdb[4] = (BYTE)((logicalObjIdnf>>16) & 0xFF);
	sptdws.SPTD.Cdb[5] = (BYTE)((logicalObjIdnf>>8) & 0xFF);
	sptdws.SPTD.Cdb[6] = (BYTE)(logicalObjIdnf & 0xFF);

	sptdws.SPTD.Cdb[8] = partitionNumber;

	return ExecuteCommand(sptdws, returnCode, snsInfo);

}

bool TapeDriveSCSI::LocateCDB16( bool changePartition, bool immediate, BYTE partitionNumber, LocateDestinationType destType, UInt64 logicalIdnf, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 16;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x92; // locate - cdb 10

	sptdws.SPTD.Cdb[1] = 0;

	if(immediate)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x01 ; // immediate
	}

	if(changePartition)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x02 ; // change partition
	}
	
	switch(destType)
	{
		case LogicalObject:
		case LogicalFile:
		case EOD:
			sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | (destType<<3) ; // set the type
			break;
		default:
			returnCode = ERROR_INTERNAL_ERROR; //fake it here for now
			returnResult = false;
			break;
	}

	sptdws.SPTD.Cdb[3] = partitionNumber;

	// set Logical Object Idnf:
	sptdws.SPTD.Cdb[4] = (BYTE)((logicalIdnf>>56) & 0xFF);
	sptdws.SPTD.Cdb[5] = (BYTE)((logicalIdnf>>48) & 0xFF);
	sptdws.SPTD.Cdb[6] = (BYTE)((logicalIdnf>>40) & 0xFF);
	sptdws.SPTD.Cdb[7] = (BYTE)((logicalIdnf>>32) & 0xFF);
	sptdws.SPTD.Cdb[8] = (BYTE)((logicalIdnf>>24) & 0xFF);
	sptdws.SPTD.Cdb[9] = (BYTE)((logicalIdnf>>16) & 0xFF);
	sptdws.SPTD.Cdb[10] = (BYTE)((logicalIdnf>>8) & 0xFF);
	sptdws.SPTD.Cdb[11] = (BYTE)(logicalIdnf & 0xFF);

	return ExecuteCommand(sptdws, returnCode, snsInfo);

}

bool TapeDriveSCSI::SeekToBOPCurrentPartition( bool immediate,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	return LocateCDB16(false,immediate,0,LogicalObject,0,returnCode,snsInfo);
}

bool TapeDriveSCSI::SeekToBOP(bool immediate, BYTE partitionNumber, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo)
{
	return LocateCDB16(true, immediate, partitionNumber, LogicalObject, 0, returnCode, snsInfo);
}

bool TapeDriveSCSI::SpaceCDB6( SpaceCode code, Int32 count, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x11; // space - cdb 6

	sptdws.SPTD.Cdb[1] = code & 0x7; // only 3 bits used

	// set count - 3 bytes only...
	sptdws.SPTD.Cdb[2] = (BYTE)((count>>16) & 0xFF);
	sptdws.SPTD.Cdb[3] = (BYTE)((count>>8) & 0xFF);
	sptdws.SPTD.Cdb[4] = (BYTE)(count & 0xFF);

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

bool TapeDriveSCSI::SpaceCDB16( SpaceCode code, Int64 count, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 16;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x91; // space - cdb 6

	sptdws.SPTD.Cdb[1] = code & 0xf; // only 4 bits used

	// set count - 8 bytes...
	sptdws.SPTD.Cdb[4] = (BYTE)((count>>56) & 0xFF);
	sptdws.SPTD.Cdb[5] = (BYTE)((count>>48) & 0xFF);
	sptdws.SPTD.Cdb[6] = (BYTE)((count>>40) & 0xFF);
	sptdws.SPTD.Cdb[7] = (BYTE)((count>>32) & 0xFF);
	sptdws.SPTD.Cdb[8] = (BYTE)((count>>24) & 0xFF);
	sptdws.SPTD.Cdb[9] = (BYTE)((count>>16) & 0xFF);
	sptdws.SPTD.Cdb[10] = (BYTE)((count>>8) & 0xFF);
	sptdws.SPTD.Cdb[11] = (BYTE)(count & 0xFF);

	// parameter length is all 00 according to SCSI spec
	sptdws.SPTD.Cdb[12] = 0;
	sptdws.SPTD.Cdb[13] = 0;

	return ExecuteCommand(sptdws, returnCode, snsInfo);

}

bool TapeDriveSCSI::SeekToEOD( UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	return SpaceCDB6(EndOfData,0,returnCode,snsInfo);

}

bool TapeDriveSCSI::SeekToEOD(bool immediate, BYTE partitionNumber, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo)
{
	return LocateCDB16(true, immediate, partitionNumber, LocateDestinationType::EOD, 0, returnCode, snsInfo);
}

bool TapeDriveSCSI::WriteFileMarks( UInt32 count,bool immediate,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x10; // Write FileMarks - cdb 6

	sptdws.SPTD.Cdb[1] = 0;

	if(immediate)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x01 ; // immediate
	}

	// set count - 3 bytes only...
	sptdws.SPTD.Cdb[2] = (BYTE)((count>>16) & 0xFF);
	sptdws.SPTD.Cdb[3] = (BYTE)((count>>8) & 0xFF);
	sptdws.SPTD.Cdb[4] = (BYTE)(count & 0xFF);

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

bool TapeDriveSCSI::ModeSelectExecuteCDB6( PVOID pModeData, bool isSCSI2Compatible, bool savePages, BYTE paramListLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_OUT;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);
	sptdws.SPTD.DataTransferLength = paramListLength;

	sptdws.SPTD.DataBuffer = pModeData;

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x15; // Mode Select - cdb 6

	sptdws.SPTD.Cdb[1] = 0;

	if(isSCSI2Compatible)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x10 ; // PF - SCSI-2 compatible
	}

	if(savePages)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x1 ; // SP - rarely allowed to be set to 1
	}

	// set param length
	sptdws.SPTD.Cdb[4] = paramListLength;

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

bool TapeDriveSCSI::ModeSelectExecuteCDB10( PVOID pModeData, bool isSCSI2Compatible, bool savePages, WORD paramListLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 10;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_OUT;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);
	sptdws.SPTD.DataTransferLength = paramListLength;

	sptdws.SPTD.DataBuffer = pModeData;

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x55; // Mode Select - cdb 10

	sptdws.SPTD.Cdb[1] = 0;

	if(isSCSI2Compatible)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x10 ; // PF - SCSI-2 compatible
	}

	if(savePages)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x1 ; // SP - rarely allowed to be set to 1
	}

	// set param length
	sptdws.SPTD.Cdb[7] = (BYTE)((paramListLength>>8) & 0xFF);
	sptdws.SPTD.Cdb[8] = (BYTE)(paramListLength & 0xFF);

	return ExecuteCommand(sptdws, returnCode, snsInfo);

}


bool TapeDriveSCSI::SetBlockSizeCDB6( UInt32 blockSize,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	MODE_DATA_6B modeData;
	memset(&modeData,0,sizeof(modeData));

	PVOID addr = &modeData;

	modeData.ParamHDR.BufferedMode = 1;
	modeData.ParamHDR.BlockDescriptorLength = 8;

	modeData.BlkDescriptor.DensityCode = 0;
	modeData.BlkDescriptor.NumberOfBlocks(0);
	modeData.BlkDescriptor.BlockLength(blockSize);

	return ModeSelectExecuteCDB6( &modeData, false, false, sizeof(modeData), returnCode, snsInfo );
}

bool TapeDriveSCSI::SetBlockSizeCDB10( UInt32 blockSize,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	MODE_DATA_10B modeData;
	memset(&modeData,0,sizeof(modeData));

	PVOID addr = &modeData;

	modeData.ParamHDR.ModeDataLength(0);
	modeData.ParamHDR.MediumType = 0;
	modeData.ParamHDR.Speed = 0;
	modeData.ParamHDR.BufferedMode = 1;
	modeData.ParamHDR.BlockDescriptorLength(8);

	modeData.BlkDescriptor.DensityCode = 0;
	modeData.BlkDescriptor.NumberOfBlocks(0);
	modeData.BlkDescriptor.BlockLength(blockSize);

	return ModeSelectExecuteCDB10( &modeData, false, false, sizeof(modeData), returnCode, snsInfo );
}

bool TapeDriveSCSI::TestUnitReady( UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x0; // test unit ready - cdb 6

	return ExecuteCommand(sptdws, returnCode, snsInfo);

}

// snsInfor here DOES NOT represent Sense for the previous command
bool TapeDriveSCSI::RequestSense( PSENSE_DATA pSnsData, BYTE snsDataType, UInt32% snsInfoLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;
	bool isDescriptorFormat = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_IN;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);
	sptdws.SPTD.DataTransferLength = SCSI_MAX_SENSE_LEN;

	sptdws.SPTD.DataBuffer = pSnsData;

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x3; // request sense - cdb 6

	snsDataType = snsDataType & 1;
	sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | snsDataType;

	sptdws.SPTD.Cdb[4] = SCSI_MAX_SENSE_LEN;

	returnResult = ExecuteCommand(sptdws, returnCode, snsInfo);
	snsInfoLength = sptdws.SPTD.DataTransferLength;

	return returnResult;

}

bool TapeDriveSCSI::ModeSenseCDB6( PVOID pModeData, bool disableBlkDscr, BYTE pageCntrl, BYTE pageCode, BYTE subPageCode, BYTE allocationLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_IN;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);
	sptdws.SPTD.DataTransferLength = allocationLength;

	sptdws.SPTD.DataBuffer = pModeData;

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x1A; // Mode Sense - cdb 6

	sptdws.SPTD.Cdb[1] = 0;

	if(disableBlkDscr)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x8 ; // disable block descriptor transfer
	}

	sptdws.SPTD.Cdb[2] = ((pageCntrl & 0x3)<<6) + (pageCode & 0x3f);
	sptdws.SPTD.Cdb[3] = subPageCode;
	sptdws.SPTD.Cdb[4] = allocationLength;

	return ExecuteCommand(sptdws, returnCode, snsInfo);

}

bool TapeDriveSCSI::ModeSenseCDB10( PVOID pModeData, bool disableBlkDscr, BYTE pageCntrl, BYTE pageCode, BYTE subPageCode, WORD allocationLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_IN;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);
	sptdws.SPTD.DataTransferLength = allocationLength;

	sptdws.SPTD.DataBuffer = pModeData;

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x5A; // Mode Sense - cdb 10

	sptdws.SPTD.Cdb[1] = 0;

	if(disableBlkDscr)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x8 ; // disable block descriptor transfer
	}

	sptdws.SPTD.Cdb[2] = ((pageCntrl & 0x3)<<6) + (pageCode & 0x3f);
	sptdws.SPTD.Cdb[3] = subPageCode;

	sptdws.SPTD.Cdb[7] = (BYTE)((allocationLength>>8) & 0xFF);
	sptdws.SPTD.Cdb[8] = (BYTE)(allocationLength & 0xFF);

	return ExecuteCommand(sptdws, returnCode, snsInfo);
}

bool TapeDriveSCSI::GetMediaBlockSize( UInt32% blockSize,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;
	MODE_DATA_6B modeData;
	BYTE allocationLength = sizeof(modeData);
	memset(&modeData,0,allocationLength);

	returnResult = ModeSenseCDB6( &modeData, false, 0/*report current*/, 0/*descriptor only*/, 0, allocationLength, returnCode, snsInfo );

	if (returnResult)
	{
		blockSize = modeData.BlkDescriptor.BlockLength();
	}

	return returnResult;

}

bool TapeDriveSCSI::Read( PVOID pData, UInt32 allocDataBytes, UInt32 transferLength, bool isSILI, bool isFixed, UInt32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_IN;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);
	sptdws.SPTD.DataTransferLength = allocDataBytes;

	sptdws.SPTD.DataBuffer = pData;

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x08; // Read - cdb 6

	sptdws.SPTD.Cdb[1] = 0;

	if(isFixed)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x1 ; // sets fixed block size mode
														// transferLength indicates number of blocks
														// otherwise transferLength indicates block size 
	}

	if (isSILI)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x2 ; // device will not return CHECK CONDITION if
														// the only error is TransferLength != BlockLenght
	}
	
	// Transfer Length:
	sptdws.SPTD.Cdb[2] = (BYTE)((transferLength>>16) & 0xFF);
	sptdws.SPTD.Cdb[3] = (BYTE)((transferLength>>8) & 0xFF);
	sptdws.SPTD.Cdb[4] = (BYTE)(transferLength & 0xFF);

	returnResult = ExecuteCommand(sptdws, returnCode, snsInfo);

	// will this make sense if the returnResult == False?
	bytesTransferred = sptdws.SPTD.DataTransferLength;

	return returnResult;
}

bool TapeDriveSCSI::ReadFixedBlocks( array<byte>^ buffer, UInt32 blockSize, UInt32 blocksToRead, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	UInt32 allocDataBytes = buffer->Length;
	UInt32 transferLength = blocksToRead;
	bool isSILI = false;
	bool isFixed = true;

	pin_ptr<byte> pData = &buffer[0];

	return Read(pData, allocDataBytes, transferLength, isSILI, isFixed, bytesTransferred, returnCode, snsInfo);
}

bool TapeDriveSCSI::ReadVarBlock( array<byte>^ buffer, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	UInt32 allocDataBytes = buffer->Length;
	UInt32 transferLength = allocDataBytes;
	bool isSILI = true;
	bool isFixed = false;

	pin_ptr<byte> pData = &buffer[0];

	return Read(pData, allocDataBytes, transferLength, isSILI, isFixed, bytesTransferred, returnCode, snsInfo);
}

bool TapeDriveSCSI::Write( PVOID pData, UInt32 allocDataBytes, UInt32 transferLength, bool isFixed, UInt32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	bool returnResult = false;

	// use SPTD with sense buffer
	SCSI_PASS_THROUGH_DIRECT_WITH_SENSE sptdws;

	// initialize structure with all zeros
	memset(&sptdws,0,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE));

	// setup structure members
	sptdws.SPTD.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdws.SPTD.CdbLength = 6;
	sptdws.SPTD.SenseInfoLength = SCSI_MAX_SENSE_LEN;
	sptdws.SPTD.DataIn = SCSI_IOCTL_DATA_OUT;
	sptdws.SPTD.TimeOutValue = 60;
	sptdws.SPTD.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE,SNSData);
	sptdws.SPTD.DataTransferLength = allocDataBytes;

	sptdws.SPTD.DataBuffer = pData;

	// setup CDB
	sptdws.SPTD.Cdb[0] = 0x0a; // write - cdb 6

	sptdws.SPTD.Cdb[1] = 0;

	if(isFixed)
	{
		sptdws.SPTD.Cdb[1] = sptdws.SPTD.Cdb[1] | 0x1 ; // sets fixed block size mode
		// transferLength indicates number of blocks
		// otherwise transferLength indicates block size
	}


	// Transfer Length:
	sptdws.SPTD.Cdb[2] = (BYTE)((transferLength>>16) & 0xFF);
	sptdws.SPTD.Cdb[3] = (BYTE)((transferLength>>8) & 0xFF);
	sptdws.SPTD.Cdb[4] = (BYTE)(transferLength & 0xFF);

	returnResult = ExecuteCommand(sptdws, returnCode, snsInfo);

	bytesTransferred = sptdws.SPTD.DataTransferLength;

	return returnResult;

}

bool TapeDriveSCSI::WriteFixedBlocks( array<byte>^ buffer,UInt32 blockSize, UInt32 blocksToWrite, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	UInt32 allocDataBytes = buffer->Length;
	UInt32 transferLength = blocksToWrite;
	bool isFixed = true;

	pin_ptr<byte> pData = &buffer[0];

	return Write(pData, allocDataBytes, transferLength, isFixed, bytesTransferred, returnCode, snsInfo);

}

bool TapeDriveSCSI::WriteVarBlock( array<byte>^ buffer, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo )
{
	UInt32 allocDataBytes = buffer->Length;
	UInt32 transferLength = allocDataBytes;
	bool isFixed = false;

	pin_ptr<byte> pData = &buffer[0];

	return Write(pData, allocDataBytes, transferLength, isFixed, bytesTransferred, returnCode, snsInfo);
}
