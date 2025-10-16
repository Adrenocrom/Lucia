#include "efi.h"

EFI_STATUS EFIAPI EfiMain(void* image, EFI_SYSTEM_TABLE* systemTable) {
	EFI_STALL Stall = (EFI_STALL)systemTable->BootServices->Stall;

	uint64_t index;
	EFI_INPUT_KEY key;

	for(int i = 0; i < 9; i++) {
		systemTable->ConOut->OutputString(systemTable->ConOut, u"hello\n\r");
		systemTable->BootServices->WaitForEvent(1, &systemTable->ConIn->WaitForKey, &index);
		systemTable->ConIn->ReadKeyStroke(systemTable->ConIn, &key);
	}

    return EFI_SUCCESS;
}
