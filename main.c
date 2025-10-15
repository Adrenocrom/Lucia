#include "efi.h"
#include <stdint.h>

int _start(void* image, EFI_SYSTEM_TABLE* systemTable) {
	EFI_TEXT_OUTPUT_STRING OutputString = (EFI_TEXT_OUTPUT_STRING)systemTable->ConOut->OutputString;
	EFI_WAIT_FOR_EVENT WaitForEvent = (EFI_WAIT_FOR_EVENT)systemTable->BootServices->WaitForEvent;
	EFI_STALL Stall = (EFI_STALL)systemTable->BootServices->Stall;
	EFI_INPUT_READ_KEY readKeyStroke = (EFI_INPUT_READ_KEY)systemTable->ConIn->ReadKeyStroke;

	uint16_t strHello[] = u"Hallo World\n\r\0";
	uint64_t index;
	EFI_INPUT_KEY key;

	for(int i = 0; i < 9; i++) {
		OutputString(systemTable->ConOut, strHello);
		WaitForEvent(1, &systemTable->ConIn->WaitForKey, &index);
		readKeyStroke(systemTable->ConIn, &key);
	}

    return 0;
}
