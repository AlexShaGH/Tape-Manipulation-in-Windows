#pragma once
#include "CommonDefinitions.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Globalization;

ref class ERROR_SNS_INFO { public:
	BYTE SNSKey;
	BYTE ASC;
	BYTE ASCQ;
	BYTE FRU;
	ERROR_SNS_INFO()
	{
		SNSKey = 0;
		ASC = 0;
		ASCQ = 0;
		FRU = 0;
	}
}; 

ref class SenseDecoder
{
private:
	SenseDecoder(void);
	//Dictionary<ERROR_SNS_INFO^, String^>^ _snsDictionary;// = 	gcnew Dictionary<String^, String^>();

public:
	static String^ DecodeSense(ERROR_SNS_INFO^ snsInfo);
};

