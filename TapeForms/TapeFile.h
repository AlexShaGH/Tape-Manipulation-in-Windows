#pragma once
#include "TapeImageModelDataTypes.h"
#include "CommonDefinitions.h"
using namespace System::Collections::Generic;
using namespace System;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Xml::Serialization;


ref class TapeFile
{
public:
	TapeFile(void);
	//virtual ~TapeFile();
	
	virtual bool OpenExisting(String^ fileName, XmlNode^ xmlNode);
	virtual bool CreateNew(String^ fileName);
	virtual void Close();

	List<TapeFileMapRecord^>^ TapeFileMap() { return _tapeFileMap; }

	//virtual bool WriteVarBlock(array<byte>^ buffer, UINT32% bytesTransferred);
	//virtual bool ReadVarBlock(array<byte>^ buffer, UINT32% bytesTransferred);

	//virtual bool ReadFixedBlocks(array<byte>^ buffer,UInt32 blockSize, UInt32 blocksToRead, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	//virtual bool ReadVarBlock(array<byte>^ buffer, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);

	//virtual bool WriteFixedBlocks(array<byte>^ buffer,UInt32 blockSize, UInt32 blocksToWrite, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	//virtual bool WriteVarBlock(array<byte>^ buffer, UINT32% bytesTransferred, UInt32% returnCode, ERROR_SNS_INFO^% snsInfo);
	
private: 
	List<TapeFileMapRecord^>^ _tapeFileMap;
	
	//List<TapeFileMapRecord^>^ TapeFileMap() { return _tapeFileMap; }
	//void TapeFileMap(List<TapeFileMapRecord^>^ val) { _tapeFileMap = val; }

	System::IO::FileInfo^ _content;
	System::IO::FileStream^ _fstream;

};

