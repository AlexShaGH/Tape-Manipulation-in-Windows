#pragma once
#include "ITapeDrive.h"
#include "SenseDecoder.h"

#define SCSI_MAX_SENSE_LEN   252

typedef struct _SKSI_FIELD_POINTER {
	
	BYTE BitPointer : 3;
	BYTE BPV : 1;
	BYTE Reserved : 2;
	BYTE CD : 1;
	BYTE SKSV : 1;

	WORD FieldPointer;

} SKSI_FIELD_POINTER, *PSKSI_FIELD_POINTER;

typedef struct _SKSI_ACTUAL_RETRY_CNT {

	BYTE Reserved : 7;
	BYTE SKSV : 1;

	WORD ActualRetryCount;

} SKSI_ACTUAL_RETRY_CNT, *PSKSI_ACTUAL_RETRY_CNT;

typedef struct _SKSI_PROGRESS_INDICATION {

	BYTE Reserved : 7;
	BYTE SKSV : 1;

	WORD ProgressIndication;

} SKSI_PROGRESS_INDICATION, *PSKSI_PROGRESS_INDICATION;

typedef struct _SKSI_SEGMENT_POINTER {

	BYTE BitPointer : 3;
	BYTE BPV : 1;
	BYTE Reserved1 : 1;
	BYTE SD : 1;
	BYTE Reserved2 : 1;
	BYTE SKSV : 1;

	WORD FieldPointer;

} SKSI_SEGMENT_POINTER, *PSKSI_SEGMENT_POINTER;

typedef struct _SKSI_UNIT_ATTN_Q_OVFL {

	BYTE Ovfl : 1;
	BYTE Reserved1 : 6;
	BYTE SKSV : 1;

	WORD Reserved2;

} SKSI_UNIT_ATTN_Q_OVFL, *PSKSI_UNIT_ATTN_Q_OVFL;

typedef struct _SKSI_GENERIC {

	BYTE Reserved1 : 7;
	BYTE SKSV : 1;

	WORD Reserved2;

} SKSI_GENERIC, *PSKSI_GENERIC;

typedef union _SKSI {
	SKSI_FIELD_POINTER FieldPointer;
	SKSI_ACTUAL_RETRY_CNT ActualRetryCnt;
	SKSI_PROGRESS_INDICATION ProgressIndication;
	SKSI_SEGMENT_POINTER SegmentPointer;
	SKSI_UNIT_ATTN_Q_OVFL UnitAttnQOvfl;
	SKSI_GENERIC GenericSKSI;
} SKSI, *PSKSI;

typedef struct _SENSE_DATA_FIXED {
	BYTE ResponseCode : 7;
	BYTE Valid : 1;

	BYTE ObsoleteByte;

	BYTE SNSKey : 4;
	BYTE SDatOvfl : 1;
	BYTE ILI : 1;
	BYTE EOM : 1;
	BYTE Filemark : 1;

	BYTE Info[4];// may need to be represented by other structure

	BYTE AddSNSLength;
	BYTE CmdSpecificInfo[4];// may need to be represented by other structure

	BYTE ASC;
	BYTE ASCQ;

	BYTE FieldReplacableUnitCode;

	SKSI SNSSpecificInfo;//see SPC-4 p. 4.5.2.4

	BYTE AddSNSBytes[234];	

} SENSE_DATA_FIXED, *PSENSE_DATA_FIXED;

typedef struct _SENSE_DATA_DESCRIPTOR {
	BYTE ResponseCode : 7;
	BYTE Reserved1 : 1;

	BYTE SNSKey : 4;
	BYTE Reserved2 : 1;

	BYTE ASC;
	BYTE ASCQ;

	BYTE Reserved3 : 7;
	BYTE SDAT_OVFL : 1;
		
	BYTE Reserved4[2];	

	BYTE AddSNSLength;

	BYTE SNSDataDescriptors[244];	

} SENSE_DATA_DESCRIPTOR, *PSENSE_DATA_DESCRIPTOR;

typedef union _SENSE_DATA {
	BYTE SNSData[SCSI_MAX_SENSE_LEN];
	SENSE_DATA_FIXED SNSDataFixed;
	SENSE_DATA_DESCRIPTOR SNSDataDescriptor;
} SENSE_DATA, *PSENSE_DATA;

typedef struct _SCSI_PASS_THROUGH_DIRECT_WITH_SENSE {
	SCSI_PASS_THROUGH_DIRECT SPTD;
	ULONG             Filler;      // realign buffer to double word boundary
	SENSE_DATA        SNSData;
} SCSI_PASS_THROUGH_DIRECT_WITH_SENSE, *PSCSI_PASS_THROUGH_DIRECT_WITH_SENSE;
/*
typedef struct _ERROR_SNS_INFO {
	BYTE SNSKey;
	BYTE ASC;
	BYTE ASCQ;
	BYTE FRU;
} ERROR_SNS_INFO, *PERROR_SNS_INFO;


typedef union _SENSE_INFO {
	DWORD SNSInfo;
	ERROR_SNS_INFO SNSErrorInfo;

} SENSE_INFO, *PSENSE_INFO;
*/

typedef struct _READ_POSITION_SHORT {
public: BYTE BPEW : 1;
		BYTE PERR : 1;
		BYTE LOLU : 1;
private:BYTE Rsvd1 : 1;
public:	BYTE BYCU : 1;
		BYTE LOCU : 1;
		BYTE EOP : 1;
		BYTE BOP : 1;

		BYTE PartitionNumber;

private:	WORD Rsvd2;

			BYTE FirstLogicalObjLocationBytes[4];

			BYTE LastLogicalObjLocationBytes[4];

			BYTE Rsvd3;

			BYTE NumOfLogicalObjInObjBufferBytes[3];

			BYTE NumOfBytesInObjBuffBytes[4];

public:
	DWORD FirstLogicalObjLocation() const { 
		DWORD val = 0;
		val = ((DWORD)(FirstLogicalObjLocationBytes[0])<<24) + ((DWORD)(FirstLogicalObjLocationBytes[1])<<16) + ((DWORD)(FirstLogicalObjLocationBytes[2])<<8) + (DWORD)FirstLogicalObjLocationBytes[3];
		return val; 
	}
	
	void FirstLogicalObjLocation(DWORD val) { 
		FirstLogicalObjLocationBytes[3] = (BYTE)(val & 0xff); 
		FirstLogicalObjLocationBytes[2] = (BYTE)((val>>8) & 0xff); 
		FirstLogicalObjLocationBytes[1] = (BYTE)((val>>16) & 0xff); 
		FirstLogicalObjLocationBytes[0] = (BYTE)((val>>24) & 0xff); 
	}

	DWORD LastLogicalObjLocation() const { 
		DWORD val = 0;
		val = ((DWORD)(LastLogicalObjLocationBytes[0])<<24) + ((DWORD)(LastLogicalObjLocationBytes[1])<<16) + ((DWORD)(LastLogicalObjLocationBytes[2])<<8) + (DWORD)LastLogicalObjLocationBytes[3];
		return val; 
	}
	
	void LastLogicalObjLocation(DWORD val) { 
		LastLogicalObjLocationBytes[3] = (BYTE)(val & 0xff); 
		LastLogicalObjLocationBytes[2] = (BYTE)((val>>8) & 0xff); 
		LastLogicalObjLocationBytes[1] = (BYTE)((val>>16) & 0xff); 
		LastLogicalObjLocationBytes[0] = (BYTE)((val>>24) & 0xff); 
	}

	DWORD NumOfLogicalObjInObjBuffer() const { 
		DWORD val = 0;
		val = ((DWORD)(NumOfLogicalObjInObjBufferBytes[0])<<16) + ((DWORD)(NumOfLogicalObjInObjBufferBytes[1])<<8) + (DWORD)NumOfLogicalObjInObjBufferBytes[2];
		return val; 
	}

	void NumOfLogicalObjInObjBuffer(DWORD val) { 
		NumOfLogicalObjInObjBufferBytes[2] = (BYTE)(val & 0xff); 
		NumOfLogicalObjInObjBufferBytes[1] = (BYTE)((val>>8) & 0xff); 
		NumOfLogicalObjInObjBufferBytes[0] = (BYTE)((val>>16) & 0xff); 
	}

	DWORD NumOfBytesInObjBuff() const { 
		DWORD val = 0;
		val = ((DWORD)(NumOfBytesInObjBuffBytes[0])<<24) + ((DWORD)(NumOfBytesInObjBuffBytes[1])<<16) + ((DWORD)(NumOfBytesInObjBuffBytes[2])<<8) + (DWORD)NumOfBytesInObjBuffBytes[3];
		return val; 
	}

	void NumOfBytesInObjBuff(DWORD val) { 
		NumOfBytesInObjBuffBytes[3] = (BYTE)(val & 0xff); 
		NumOfBytesInObjBuffBytes[2] = (BYTE)((val>>8) & 0xff); 
		NumOfBytesInObjBuffBytes[1] = (BYTE)((val>>16) & 0xff); 
		NumOfBytesInObjBuffBytes[0] = (BYTE)((val>>24) & 0xff); 
	}

} READ_POSITION_SHORT, *PREAD_POSITION_SHORT;

typedef struct _READ_POSITION_LONG {
public:	BYTE BPEW : 1;
private:BYTE Rsvd1 : 1;
public:	BYTE LONU : 1;
		BYTE MPU : 1;
private:BYTE Rsvd2 : 2;
public:	BYTE EOP : 1;
		BYTE BOP : 1;

private:BYTE Rsvd3[3];

		BYTE PartitionNumberBytes[4];

		BYTE LogicalObjNumberBytes[8];

		BYTE LogicalFileIdnfBytes[8];

		__int64 Obsolete1;

public:
	DWORD PartitionNumber() const { 
		DWORD val = 0;
		val = ((DWORD)(PartitionNumberBytes[0])<<24) + ((DWORD)(PartitionNumberBytes[1])<<16) + ((DWORD)(PartitionNumberBytes[2])<<8) + (DWORD)PartitionNumberBytes[3];
		return val;
	}

	void PartitionNumber(DWORD val) { 
		PartitionNumberBytes[3] = (BYTE)(val & 0xff); 
		PartitionNumberBytes[2] = (BYTE)((val>>8) & 0xff); 
		PartitionNumberBytes[1] = (BYTE)((val>>16) & 0xff); 
		PartitionNumberBytes[0] = (BYTE)((val>>24) & 0xff); 
	}

	__int64 LogicalObjNumber() const { 
		__int64 val = 0;
		val = ((__int64)(LogicalObjNumberBytes[0])<<56) + 
			((__int64)(LogicalObjNumberBytes[1])<<48) + 
			((__int64)(LogicalObjNumberBytes[2])<<40) + 
			((__int64)(LogicalObjNumberBytes[3])<<32) + 
			((__int64)(LogicalObjNumberBytes[4])<<24) + 
			((__int64)(LogicalObjNumberBytes[5])<<16) + 
			((__int64)(LogicalObjNumberBytes[6])<<8) + 
			(__int64)LogicalObjNumberBytes[7];
		return val;
	}

	void LogicalObjNumber(__int64 val) { 
		LogicalObjNumberBytes[7] = (BYTE)(val & 0xff); 
		LogicalObjNumberBytes[6] = (BYTE)((val>>8) & 0xff); 
		LogicalObjNumberBytes[5] = (BYTE)((val>>16) & 0xff); 
		LogicalObjNumberBytes[4] = (BYTE)((val>>24) & 0xff); 
		LogicalObjNumberBytes[3] = (BYTE)((val>>32) & 0xff);
		LogicalObjNumberBytes[2] = (BYTE)((val>>40) & 0xff);
		LogicalObjNumberBytes[1] = (BYTE)((val>>48) & 0xff);
		LogicalObjNumberBytes[0] = (BYTE)((val>>56) & 0xff);
	}

	__int64 LogicalFileIdnf() const { 
		__int64 val = 0;
		val = ((__int64)(LogicalFileIdnfBytes[0])<<56) + 
			((__int64)(LogicalFileIdnfBytes[1])<<48) + 
			((__int64)(LogicalFileIdnfBytes[2])<<40) + 
			((__int64)(LogicalFileIdnfBytes[3])<<32) + 
			((__int64)(LogicalFileIdnfBytes[4])<<24) + 
			((__int64)(LogicalFileIdnfBytes[5])<<16) + 
			((__int64)(LogicalFileIdnfBytes[6])<<8) + 
			(__int64)LogicalFileIdnfBytes[7];
		return val;
	}

	void LogicalFileIdnf(__int64 val) { 
		LogicalFileIdnfBytes[7] = (BYTE)(val & 0xff); 
		LogicalFileIdnfBytes[6] = (BYTE)((val>>8) & 0xff); 
		LogicalFileIdnfBytes[5] = (BYTE)((val>>16) & 0xff); 
		LogicalFileIdnfBytes[4] = (BYTE)((val>>24) & 0xff); 
		LogicalFileIdnfBytes[3] = (BYTE)((val>>32) & 0xff);
		LogicalFileIdnfBytes[2] = (BYTE)((val>>40) & 0xff);
		LogicalFileIdnfBytes[1] = (BYTE)((val>>48) & 0xff);
		LogicalFileIdnfBytes[0] = (BYTE)((val>>56) & 0xff);
	}

} READ_POSITION_LONG, *PREAD_POSITION_LONG;

typedef struct _READ_POSITION_EXTND {
public:	BYTE BPEW : 1;
		BYTE PERR : 1;
		BYTE LOLU : 1;
private:BYTE Rsvd1 : 1;
public:	BYTE BYCU : 1;
		BYTE LOCU : 1;
		BYTE EOP : 1;
		BYTE BOP : 1;

		BYTE PartitionNumber;

private:BYTE AdditionalLengthBytes[2];

		BYTE Rsvd2;

		BYTE NumOfLogicalObjInObjBuffBytes[3];

		BYTE FirstLogicalObjLocationBytes[8];

		BYTE LastLogicalObjLocationBytes[8];

		BYTE NumOfBytesInObjBuffBytes[8];

public:
	WORD AdditionalLength() const { 
		WORD val = 0;
		val = (((WORD)(AdditionalLengthBytes[0]))<<8) +
			(WORD)AdditionalLengthBytes[1];
		return val;
	}

	void AdditionalLength(WORD val) { 
		AdditionalLengthBytes[1] = (BYTE)(val & 0xff); 
		AdditionalLengthBytes[0] = (BYTE)((val>>8) & 0xff); 
	}

	DWORD NumOfLogicalObjInObjBuff() const { 
		DWORD val = 0;
		val = ((DWORD)(NumOfLogicalObjInObjBuffBytes[0])<<16) + 
			((DWORD)(NumOfLogicalObjInObjBuffBytes[1])<<8) + 
			(DWORD)NumOfLogicalObjInObjBuffBytes[2];
		return val;

	}

	void NumOfLogicalObjInObjBuff(DWORD val) { 
		NumOfLogicalObjInObjBuffBytes[2] = (BYTE)(val & 0xff); 
		NumOfLogicalObjInObjBuffBytes[1] = (BYTE)((val>>8) & 0xff); 
		NumOfLogicalObjInObjBuffBytes[0] = (BYTE)((val>>16) & 0xff); 
	}

	__int64 FirstLogicalObjLocation() const { 
		__int64 val = 0;
		val = ((__int64)(FirstLogicalObjLocationBytes[0])<<56) + 
			((__int64)(FirstLogicalObjLocationBytes[1])<<48) + 
			((__int64)(FirstLogicalObjLocationBytes[2])<<40) + 
			((__int64)(FirstLogicalObjLocationBytes[3])<<32) + 
			((__int64)(FirstLogicalObjLocationBytes[4])<<24) + 
			((__int64)(FirstLogicalObjLocationBytes[5])<<16) + 
			((__int64)(FirstLogicalObjLocationBytes[6])<<8) + 
			(__int64)FirstLogicalObjLocationBytes[7];
		return val;
	}

	void FirstLogicalObjLocation(__int64 val) { 
		FirstLogicalObjLocationBytes[7] = (BYTE)(val & 0xff); 
		FirstLogicalObjLocationBytes[6] = (BYTE)((val>>8) & 0xff); 
		FirstLogicalObjLocationBytes[5] = (BYTE)((val>>16) & 0xff); 
		FirstLogicalObjLocationBytes[4] = (BYTE)((val>>24) & 0xff); 
		FirstLogicalObjLocationBytes[3] = (BYTE)((val>>32) & 0xff);
		FirstLogicalObjLocationBytes[2] = (BYTE)((val>>40) & 0xff);
		FirstLogicalObjLocationBytes[1] = (BYTE)((val>>48) & 0xff);
		FirstLogicalObjLocationBytes[0] = (BYTE)((val>>56) & 0xff);
	}

	__int64 LastLogicalObjLocation() const { 
		__int64 val = 0;
		val = ((__int64)(LastLogicalObjLocationBytes[0])<<56) + 
			((__int64)(LastLogicalObjLocationBytes[1])<<48) + 
			((__int64)(LastLogicalObjLocationBytes[2])<<40) + 
			((__int64)(LastLogicalObjLocationBytes[3])<<32) + 
			((__int64)(LastLogicalObjLocationBytes[4])<<24) + 
			((__int64)(LastLogicalObjLocationBytes[5])<<16) + 
			((__int64)(LastLogicalObjLocationBytes[6])<<8) + 
			(__int64)LastLogicalObjLocationBytes[7];
		return val;
	}
	void LastLogicalObjLocation(__int64 val) { 
		LastLogicalObjLocationBytes[7] = (BYTE)(val & 0xff); 
		LastLogicalObjLocationBytes[6] = (BYTE)((val>>8) & 0xff); 
		LastLogicalObjLocationBytes[5] = (BYTE)((val>>16) & 0xff); 
		LastLogicalObjLocationBytes[4] = (BYTE)((val>>24) & 0xff); 
		LastLogicalObjLocationBytes[3] = (BYTE)((val>>32) & 0xff);
		LastLogicalObjLocationBytes[2] = (BYTE)((val>>40) & 0xff);
		LastLogicalObjLocationBytes[1] = (BYTE)((val>>48) & 0xff);
		LastLogicalObjLocationBytes[0] = (BYTE)((val>>56) & 0xff);
	}

	__int64 NumOfBytesInObjBuff() const { 
		__int64 val = 0;
		val = ((__int64)(NumOfBytesInObjBuffBytes[0])<<56) + 
			((__int64)(NumOfBytesInObjBuffBytes[1])<<48) + 
			((__int64)(NumOfBytesInObjBuffBytes[2])<<40) + 
			((__int64)(NumOfBytesInObjBuffBytes[3])<<32) + 
			((__int64)(NumOfBytesInObjBuffBytes[4])<<24) + 
			((__int64)(NumOfBytesInObjBuffBytes[5])<<16) + 
			((__int64)(NumOfBytesInObjBuffBytes[6])<<8) + 
			(__int64)NumOfBytesInObjBuffBytes[7];
		return val;
	}

	void NumOfBytesInObjBuff(__int64 val) { 
		NumOfBytesInObjBuffBytes[7] = (BYTE)(val & 0xff); 
		NumOfBytesInObjBuffBytes[6] = (BYTE)((val>>8) & 0xff); 
		NumOfBytesInObjBuffBytes[5] = (BYTE)((val>>16) & 0xff); 
		NumOfBytesInObjBuffBytes[4] = (BYTE)((val>>24) & 0xff); 
		NumOfBytesInObjBuffBytes[3] = (BYTE)((val>>32) & 0xff);
		NumOfBytesInObjBuffBytes[2] = (BYTE)((val>>40) & 0xff);
		NumOfBytesInObjBuffBytes[1] = (BYTE)((val>>48) & 0xff);
		NumOfBytesInObjBuffBytes[0] = (BYTE)((val>>56) & 0xff);
	}

} READ_POSITION_EXTND, *PREAD_POSITION_EXTND;

typedef union _READ_POSITION {
	READ_POSITION_EXTND ReadPosition;
	BYTE RawData[32];

} READ_POSITION, *PREAD_POSITION;

enum ReadPositionServiceAction : BYTE {
	ShortForm = 0,
	LongForm = 6,
	ExtendedForm = 8
};

enum LocateDestinationType : BYTE {
	LogicalObject = 0x0,
	LogicalFile = 0x1,
	EOD = 0x3
};

enum SpaceCode : BYTE {
	Blocks = 0x0,
	FileMarks = 0x1,
	EndOfData = 0x3
};

typedef struct _MODE_PARAM_HDR_6B {
	BYTE ModeDataLength;
	BYTE MediumType;
	BYTE Speed : 4;
	BYTE BufferedMode : 3;
	BYTE WP : 1;
	BYTE BlockDescriptorLength;
} MODE_PARAM_HDR_6B, *PMODE_PARAM_HDR_6B;

typedef struct _MODE_PARAM_HDR_10B {
private:BYTE ModeDataLengthBytes[2];
public:	BYTE MediumType;
		BYTE Speed : 4;
		BYTE BufferedMode : 3;
		BYTE WP : 1;
private:BYTE ReservedBytes[2];
		BYTE BlockDescriptorLengthBytes[2];
public:
		WORD ModeDataLength() const { 
			WORD val = 0;
			val = (((WORD)(ModeDataLengthBytes[0]))<<8) +
				(WORD)ModeDataLengthBytes[1];
			return val;
		}

		void ModeDataLength(WORD val) { 
			ModeDataLengthBytes[1] = (BYTE)(val & 0xff); 
			ModeDataLengthBytes[0] = (BYTE)((val>>8) & 0xff); 
		}

		WORD BlockDescriptorLength() const { 
			WORD val = 0;
			val = (((WORD)(BlockDescriptorLengthBytes[0]))<<8) +
				(WORD)BlockDescriptorLengthBytes[1];
			return val;
		}

		void BlockDescriptorLength(WORD val) { 
			BlockDescriptorLengthBytes[1] = (BYTE)(val & 0xff); 
			BlockDescriptorLengthBytes[0] = (BYTE)((val>>8) & 0xff); 
		}

} MODE_PARAM_HDR_10B, *PMODE_PARAM_HDR_10B;


typedef struct _MODE_BLOCK_DESCRIPTOR {
public:	BYTE DensityCode;
private:BYTE NumberOfBlocksBytes[3];
		BYTE Reserved;
		BYTE BlockLengthBytes[3];
public:
	DWORD NumberOfBlocks() const { 
		DWORD val = 0;
		val = (((DWORD)(NumberOfBlocksBytes[0]))<<16) +
			(((DWORD)(NumberOfBlocksBytes[1]))<<8) +
			(DWORD)NumberOfBlocksBytes[2];
		return val;
	}

	void NumberOfBlocks(DWORD val) { 
		NumberOfBlocksBytes[2] = (BYTE)(val & 0xff); 
		NumberOfBlocksBytes[1] = (BYTE)((val>>8) & 0xff); 
		NumberOfBlocksBytes[0] = (BYTE)((val>>16) & 0xff); 
	}

	DWORD BlockLength() const { 
		DWORD val = 0;
		val = (((DWORD)(BlockLengthBytes[0]))<<16) +
			(((DWORD)(BlockLengthBytes[1]))<<8) +
			(DWORD)BlockLengthBytes[2];
		return val;
	}

	void BlockLength(DWORD val) { 
		BlockLengthBytes[2] = (BYTE)(val & 0xff); 
		BlockLengthBytes[1] = (BYTE)((val>>8) & 0xff); 
		BlockLengthBytes[0] = (BYTE)((val>>16) & 0xff); 
	}

} MODE_BLOCK_DESCRIPTOR, *PMODE_BLOCK_DESCRIPTOR;


typedef struct _MODE_DATA_6B {
	MODE_PARAM_HDR_6B ParamHDR;
	MODE_BLOCK_DESCRIPTOR BlkDescriptor;
} MODE_DATA_6B, *PMODE_DATA_6B;

typedef struct _MODE_DATA_10B {
	MODE_PARAM_HDR_10B ParamHDR;
	MODE_BLOCK_DESCRIPTOR BlkDescriptor;
} MODE_DATA_10B, *PMODE_DATA_10B;

//DEBUG
/*typedef union _MODE_DATA_6B_tst {
	MODE_DATA_6B mD;
	BYTE rawData[12];
} MODE_DATA_6B_tst, *PMODE_DATA_6B_tst;*/

ref class TapeDriveSCSI //: ITapeDrive
{
public:
	TapeDriveSCSI(void);

	virtual bool Open(String^ tapeDriveName, UInt32% returnCode);
	virtual bool Close( UInt32% returnCode );

	virtual bool Load(bool immediate, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );
	virtual bool Unload(bool immediate, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );


	//virtual bool Lock(bool immediate, UInt32% returnCode, ERROR_SNS_INFO^ snsInfo);
	//virtual bool Unlock(bool immediate, UInt32% returnCode);

	virtual bool FormatTape(Byte formatType, bool immediate, bool verify, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo); // does not work???

	virtual bool EraseTape( bool longErase, bool immediate, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

	//virtual bool AdjustTension(bool immediate, UInt32% returnCode);

	virtual bool Rewind(bool immediate,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	virtual bool ReadPositionShort(READ_POSITION_SHORT& positionInfo, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool ReadPositionLong(READ_POSITION_LONG& positionInfo, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool ReadPositionExtended(READ_POSITION_EXTND& positionInfo, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool ReadPosition(PVOID pPositionInfo, ReadPositionServiceAction action, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	virtual bool LocateCDB10(bool changePartition, bool immediate, BYTE partitionNumber, UInt32 logicalObjIdnf, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool LocateCDB16(bool changePartition, bool immediate, BYTE partitionNumber, LocateDestinationType destType, UInt64 logicalIdnf, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	virtual bool SeekToBOPCurrentPartition(bool immediate,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool SeekToBOP(bool immediate, BYTE partitionNumber, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	virtual bool SpaceCDB6(SpaceCode code, Int32 count, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );
	virtual bool SpaceCDB16(SpaceCode code, Int64 count, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

	virtual bool SeekToEOD(UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool SeekToEOD(bool immediate, BYTE partitionNumber, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	virtual bool WriteFileMarks(UInt32 count,bool immediate,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	virtual bool SetBlockSizeCDB6(UInt32 blockSize,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );
	virtual bool SetBlockSizeCDB10(UInt32 blockSize,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

	virtual bool TestUnitReady(UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool RequestSense(PSENSE_DATA pSnsData, BYTE snsDataType, UInt32% snsInfoLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

	virtual bool ModeSenseCDB6( PVOID pModeData, bool disableBlkDscr, BYTE pageCntrl, BYTE pageCode, BYTE subPageCode, BYTE allocationLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );
	virtual bool ModeSenseCDB10( PVOID pModeData, bool disableBlkDscr, BYTE pageCntrl, BYTE pageCode, BYTE subPageCode, WORD allocationLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

	virtual bool GetMediaBlockSize(UInt32% blockSize,UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

	virtual bool ReadFixedBlocks(array<byte>^ buffer,UInt32 blockSize, UInt32 blocksToRead, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool ReadVarBlock(array<byte>^ buffer, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	virtual bool WriteFixedBlocks(array<byte>^ buffer,UInt32 blockSize, UInt32 blocksToWrite, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	virtual bool WriteVarBlock(array<byte>^ buffer, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	//virtual bool ReadTape(array<byte>^ buffer, UInt32 bytesToRead, UInt32% bytesRead, UInt32% returnCode);

	//virtual bool GetMediaParameters(TAPE_GET_MEDIA_PARAMETERS* mediaInfo, UInt32% returnCode );
	//virtual bool GetDriveParameters(TAPE_GET_DRIVE_PARAMETERS* driveInfo, UInt32% returnCode );
	
/*	virtual bool SeekToAbsoluteBlock(UInt64 blockAddress, bool immediate, UInt32% returnCode);
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

	virtual bool WriteTapemarkDo(UInt32 tapemarkType, UInt32 tapemarkCount, bool immediate, UInt32% returnCode );


	virtual bool WriteTape(array<byte>^ buffer, UInt32 bytesToWrite, UInt32% bytesWritten, UInt32% returnCode);
	*/
	ERROR_SNS_INFO^ GetSNSInfoFromFixedData(PSENSE_DATA snsData);
	ERROR_SNS_INFO^ GetSNSInfoFromDescriptorData(PSENSE_DATA snsData);
	ERROR_SNS_INFO^ GetSense(SCSI_PASS_THROUGH_DIRECT_WITH_SENSE% sptdws);

private:
	HANDLE _tapeDriveHandle;
	String^ _tapeDriveName;



	bool LoadUnload( bool loadOp, bool immediate, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

	bool ExecuteCommand( SCSI_PASS_THROUGH_DIRECT_WITH_SENSE &sptdws, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

	bool ModeSelectExecuteCDB6(PVOID pModeData, bool isSCSI2Compatible, bool savePages, BYTE paramListLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	bool ModeSelectExecuteCDB10(PVOID pModeData, bool isSCSI2Compatible, bool savePages, WORD paramListLength, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	bool Read( PVOID pData, UInt32 allocDataBytes, UInt32 transferLength, bool isSILI, bool isFixed, UInt32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );
	bool Write( PVOID pData, UInt32 allocDataBytes, UInt32 transferLength, bool isFixed, UInt32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo );

};

