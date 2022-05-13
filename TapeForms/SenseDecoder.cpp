#include "StdAfx.h"
#include "SenseDecoder.h"

using namespace System::IO;


SenseDecoder::SenseDecoder(void)
{
}


String^ SenseDecoder::DecodeSense(ERROR_SNS_INFO^ snsInfo)
{
	array<String^,3>^ senseData = gcnew array<String^,3>(16,256,256);
	int snsKey = 0;
	int snsASC = 0;
	int snsASCQ = 0;

	for (snsKey = 0; snsKey < 16; snsKey++)
	{
		for (snsASC = 0; snsASC < 256; snsASC++)
		{
			for (snsASCQ = 0; snsASCQ < 256; snsASCQ++)
			{
				senseData[snsKey,snsASC,snsASCQ] = String::Format("UNKNOWN SENSE CODE");
			}
		}
	}

	StreamReader^ reader = gcnew StreamReader("SenseCodes.txt");

	String^ dictionaryEntry;
	array<String^>^ dicEntrySplitArray;

	while (dictionaryEntry = reader->ReadLine())
	{
		dicEntrySplitArray = dictionaryEntry->Split(';');

		snsKey = Byte::Parse(dicEntrySplitArray[0],NumberStyles::HexNumber);
		snsASC = Byte::Parse(dicEntrySplitArray[1],NumberStyles::HexNumber);

		if (dicEntrySplitArray[2] == "XX")
		{
			for (snsASCQ = 0; snsASCQ < 256; snsASCQ++)
			{
				senseData[snsKey,snsASC,snsASCQ] = dicEntrySplitArray[3];
			}
		}
		else
		{
			snsASCQ = Byte::Parse(dicEntrySplitArray[2],NumberStyles::HexNumber);
			senseData[snsKey,snsASC,snsASCQ] = dicEntrySplitArray[3];
		}
	}

	return String::Format("Key: {0:X2}, ASC: {1:X2}, ACSQ: {2:X2}\n\r",snsInfo->SNSKey,snsInfo->ASC,snsInfo->ASCQ) + senseData[snsInfo->SNSKey,snsInfo->ASC,snsInfo->ASCQ];
}
