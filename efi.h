#ifndef _EFI_H_
#define _EFI_H_

#include <stdint.h>

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
	void* WaitForKey;
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
	void* FirmwareVendor;
	uint32_t FirmwareRevision;
	void* ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;
	void* ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
	void* StandardErrorHandle;
	void* StdErr;
	void* RuntimeServices;
	void* BootServices;
	uint64_t NumberOfTableEntries;
	void* ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef void (*EFI_TEXT_OUTPUT_STRING) (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut, uint16_t* String);

#endif
