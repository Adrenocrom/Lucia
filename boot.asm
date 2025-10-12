bits 64
default rel                 ; use RIP‑relative addressing

global _start               ; the UEFI firmware will call this function

section .text
_start:
    sub rsp, 32                ; 4 registers × 8 bytes = 32 bytes

    mov [systemTable], rdx      ; rdx = &EFI_SYSTEM_TABLE

    mov rax, [rdx + 0x40]       ; SystemTable->ConOut (EFI_OUTPUT_PROTOCOL *)
    mov [conout], rax

    mov r8,  [rax + 0x8]        ; ConOut->OutputString
    mov [outputString], r8

    mov rcx, [conout]          ; 1st arg: EFI_OUTPUT_PROTOCOL*
    lea rdx, [strHelloWorld]   ; 2nd arg: CHAR16*   (pointer to our string)

    call [outputString]        ; indirect call (or `call r8` works the same)
	
    mov rax, [rdx + 0x48]        ; SystemTable->ConIn
    mov [conin], rax

    mov r8,  [rax + 0x10]        ; ConIn->ReadKeyStroke
    mov [readKeyStroke], r8

    ; 3. Wait for a key – the call blocks until a key arrives
    lea rcx, [keyData]           ; 1st arg: EFI_KEY_DATA*
    call [readKeyStroke]         ; blocks until key pressed

    ; (Optional)  you can inspect keyData.EscapedChar or
    ; keyData.Key.UnicodeChar etc. here.


    add rsp, 32
    mov rax, 0                  ; EFI_STATUS – success
    ret

section .data
    strHelloWorld db __utf16__ `hello, world!\r\n\0`

	image           dq 0
	systemTable     dq 0
	conout 			dq 0
	conin 			dq 0
	outputString    dq 0
	readKeyStroke 	dq 0
	keyData 		dq 0
