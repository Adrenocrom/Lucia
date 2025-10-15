#include "efi.h"

int _start(void* image, EFI_SYSTEM_TABLE* systemTable) {
	EFI_TEXT_OUTPUT_STRING OutputString = (EFI_TEXT_OUTPUT_STRING)systemTable->ConOut->OutputString;
	uint16_t strHello[] = u"\rHallo World";
	OutputString(systemTable->ConOut, strHello);
	for(;;) {
		OutputString(systemTable->ConOut, strHello);
	}
    return 0;
}
