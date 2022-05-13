#include "StdAfx.h"
#include "TapeFile.h"


TapeFile::TapeFile(void)
{
}

bool TapeFile::CreateNew( String^ fileName)
{
	_content = gcnew FileInfo(fileName);

	_fstream = _content->Create();

	if(_fstream = nullptr)
	{
		_tapeFileMap = nullptr;
		_content = nullptr;

		return false;
	}
	else 
	{
		_tapeFileMap = gcnew List<TapeFileMapRecord^>;

		return true;
	}
}

bool TapeFile::OpenExisting( String^ fileName, XmlNode^ xmlNode)
{
	_content = gcnew FileInfo(fileName);

	if(!_content->Exists)
	{
		_tapeFileMap = nullptr;
		_content = nullptr;

		return false;
	}
	
	_fstream = _content->Open(FileMode::Open,FileAccess::Read,FileShare::ReadWrite);

	if(_fstream = nullptr)
	{
		_tapeFileMap = nullptr;
		_content = nullptr;

		return false;
	}

	_tapeFileMap = gcnew List<TapeFileMapRecord^>;

	// populate _tapeFileMap with data
	XmlSerializer^ serializer = gcnew XmlSerializer(_tapeFileMap->GetType());
	XmlReader^ reader = gcnew XmlNodeReader(xmlNode);
	_tapeFileMap = dynamic_cast<List<TapeFileMapRecord^>^>(serializer->Deserialize( reader ));

	return true;
}

void TapeFile::Close()
{
	if(_fstream != nullptr)
	{
		_fstream->Flush();
		_fstream->Close();
		_fstream = nullptr;
	}

	_content = nullptr;

	_tapeFileMap = nullptr;
}
