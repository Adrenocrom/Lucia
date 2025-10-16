#ifndef _EFI_H_
#define _EFI_H_

#include <stdint.h>

#define EFIAPI
#define EFI_SUCCESS 0L;
#define IN
#define OUT

typedef uint16_t CHAR16;
typedef uint64_t UINTN;
typedef uint64_t UINT64;
typedef uint32_t UINT32;
typedef uint16_t UINT16;

typedef UINTN EFI_STATUS;

typedef void* EFI_HANDLE;
typedef void* EFI_EVENT;

typedef struct {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef struct {
	uint64_t Signature;  
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	OUT EFI_INPUT_KEY *Key
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_STRING) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16 *String
);

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
	IN UINTN NumberOfEvents,
	IN EFI_EVENT *Event,
	OUT UINTN *Index
);

typedef
EFI_STATUS
(EFIAPI *EFI_STALL) (
	IN UINTN Microseconds
);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	void* Reset;
	EFI_INPUT_READ_KEY ReadKeyStroke;
	EFI_EVENT WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	void* Reset;
	EFI_TEXT_STRING OutputString;
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
	EFI_WAIT_FOR_EVENT WaitForEvent;
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
	UINT32 FirmwareRevision;
	EFI_HANDLE ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;
	EFI_HANDLE ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
	EFI_HANDLE StandardErrorHandle;
	void* StdErr;
	EFI_RUNTIME_SERVICES* RuntimeServices;
	EFI_BOOT_SERVICES* BootServices;
	UINTN NumberOfTableEntries;
	void* ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
