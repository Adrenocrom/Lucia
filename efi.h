#ifndef _EFI_H_
#define _EFI_H_

#include <stdint.h>

typedef void* EFI_HANDLE;
typedef void* EFI_EVENT;

typedef struct {
	uint16_t ScanCode;
	uint16_t UnicodeChar;
} EFI_INPUT_KEY;

typedef struct {
	uint64_t Signature;  
	uint32_t Revision;
	uint32_t HeaderSize;
	uint32_t CRC32;
	uint32_t Reserved;
} EFI_TABLE_HEADER;

typedef struct {
	void* Reset;
	void* ReadKeyStroke;
	EFI_EVENT WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct {
	void* Reset;
	void* OutputString;
	void* TestString;
	void* QueryMode;
	void* SetMode;
	void* SetAttribute;
	void* ClearScreen;
	void* SetCursorPosition;
	void* EnableCursor;
	void* Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
	EFI_TABLE_HEADER Hdr;
	void* RaiseTPL;
	void* RestoreTPL;
	void* AllocatePages;
	void* FreePages;
	void* GetMemoryMap;
	void* AllocatePool;
	void* FreePool;
	void* CreateEvent;
	void* SetTimer;
	void* WaitForEvent;
	void* SignalEvent;
	void* CloseEvent;
	void* CheckEvent;
	void* InstallProtocolInterface;
	void* ReinstallProtocolInterface;
	void* UninstallProtocolInterface;
	void* HandleProtocol;
	void* Reserved;
	void* RegisterProtocolNotify;
	void* LocateHandle;
	void* LocateDevicePath;
	void* InstallConfigurationTable;
	void* LoadImage;
	void* StartImage;
	void* Exit;
	void* UnloadImage;
	void* ExitBootServices;
	void* GetNextMonotonicCount;
	void* Stall;
	void* SetWatchdogTimer;
	void* ConnectController;
	void* DisconnectController;
	void* OpenProtocol;
	void* CloseProtocol;
	void* OpenProtocolInformation;
	void* ProtocolsPerHandle;
	void* LocateHandleBuffer;
	void* LocateProtocol;
	void* InstallMultipleProtocolInterfaces;
	void* UninstallMultipleProtocolInterfaces;
	void* CalculateCrc32;
	void* CopyMem;
	void* SetMem;
	void* CreateEventEx;
} EFI_BOOT_SERVICES;

typedef struct {
	EFI_TABLE_HEADER Hdr;
	void* GetTime;
	void* SetTime;
	void* GetWakeupTime;
	void* SetWakeupTime;
	void* SetVirtualAddressMap;
	void* ConvertPointer;
	void* GetVariable;
	void* GetNextVariableName;
	void* SetVariable;
	void* GetNextHighMonotonicCount;
	void* ResetSystem;
	void* UpdateCapsule;
	void* QueryCapsuleCapabilities;
	void* QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

typedef struct {
	EFI_TABLE_HEADER Hdr;
	void* FirmwareVendor;
	uint32_t FirmwareRevision;
	EFI_HANDLE ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;
	EFI_HANDLE ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
	EFI_HANDLE StandardErrorHandle;
	void* StdErr;
	EFI_RUNTIME_SERVICES* RuntimeServices;
	EFI_BOOT_SERVICES* BootServices;
	uint64_t NumberOfTableEntries;
	void* ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef void (*EFI_TEXT_OUTPUT_STRING) (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut, uint16_t* String);
typedef void (*EFI_WAIT_FOR_EVENT) (uint64_t NumberOfEvents, EFI_EVENT* Event, uint64_t* Index);
typedef void (*EFI_STALL) (uint64_t Microseconds);
typedef void (*EFI_INPUT_READ_KEY) (EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);

#endif
