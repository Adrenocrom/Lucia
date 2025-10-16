#include "efi.h"

#define PRINT(x) systemTable->ConOut->OutputString(systemTable->ConOut, (x));

EFI_STATUS EFIAPI EfiMain(void* image, EFI_SYSTEM_TABLE* systemTable) {
	uint64_t index;
	EFI_INPUT_KEY key;

	//systemTable->ConOut->OutputString(systemTable->ConOut, u"hello\n\r");
	systemTable->ConOut->ClearScreen(systemTable->ConOut);
	PRINT(u"hello\n\r");
	PRINT(u"press a key to continue\n\r");

	systemTable->BootServices->WaitForEvent(1, &systemTable->ConIn->WaitForKey, &index);
	systemTable->ConIn->ReadKeyStroke(systemTable->ConIn, &key);
	PRINT(u"will the graphics work?\n\r");
	EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = 0L;
	EFI_GUID guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	systemTable->BootServices->LocateProtocol(&guid, 0L, (void **)&gop);
	if (gop) {
		PRINT(u"Its works your protocol has been found!\n\r");
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL* buffer;
		UINT32 width = gop->Mode->Info->HorizontalResolution;
		UINT32 height = gop->Mode->Info->VerticalResolution;
		if(width == 0 || height == 0) {
			width = 640;
			height = 480;
		}
		UINT32 size = width * height;
		systemTable->BootServices->AllocatePool(EfiBootServicesData, sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * size, (void **)&buffer);

		for(UINT32 x = 0; x < size; x++) {
			EFI_GRAPHICS_OUTPUT_BLT_PIXEL* pixel = &buffer[x];
			pixel->Red = 0;
			pixel->Green = 0;
			pixel->Blue = 20;
		}
		gop->Blt(gop, buffer, EfiBltBufferToVideo, 0, 0, 0, 0, width, height, 0);

		for(UINT32 x = 0; x < size; x++) {
			EFI_GRAPHICS_OUTPUT_BLT_PIXEL* pixel = &buffer[x];
			pixel->Red = 255;
			pixel->Green = 0;
			pixel->Blue = 0;
			gop->Blt(gop, buffer, EfiBltBufferToVideo, 0, 0, 0, 0, width, height, 0);
			systemTable->BootServices->Stall(10000);
		}

		if(buffer) {
			systemTable->BootServices->FreePool(buffer);
		}
	}
	else {
		PRINT(u":(");
	}

	systemTable->BootServices->WaitForEvent(1, &systemTable->ConIn->WaitForKey, &index);
	systemTable->ConIn->ReadKeyStroke(systemTable->ConIn, &key);
    return EFI_SUCCESS;
}
