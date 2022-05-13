#include <WINDOWS.h> // ntddscsi.h , etc.

#include <ntddscsi.h> // BlockDeviceNativeSpecific.h , BlockDeviceWinSAT.cpp , BlockDeviceWinSAT.cpp

#include <SETUPAPI.h> // DeviceEnum.cpp

#include <TCHAR.h> // DeviceEnum.cpp ( _tcsdup )

#include <vcclr.h> // BlockDeviceWinDisk.h ( PtrToStringChars )

#include <memory.h> // IoDataBuffer, BinaryBlocksCache

#include <BaseTsd.h> // for INT_PTR

#include <Cfgmgr32.h> // for device enumeration