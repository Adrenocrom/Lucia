bits 64
default rel

global _start

section .text

%include "efi.asm"


; r8 = 64‑bit unsigned value
; rdi = pointer to a buffer that can hold up to 21 UTF‑16 chars (incl. null)
convert_uint_to_utf16:
    push    rbx rsi rdx                ; save callee‑saved registers
    xor     rdx, rdx                  ; high 64 bits = 0
    mov     rcx, 10
    mov     rsi, 0                     ; digit count
    mov     rbx, rdi                  ; store buffer base

    ; 1st pass – gather digits in reverse
convert_loop:
    cmp     r8, 0
    je      convert_end
    div     rcx                        ; rdx = r8 % 10
    mov     rsi, rdx
    mov     [rbx + rsi], dl            ; store digit
    inc     rsi
    mov     r8, rax
    jmp     convert_loop

convert_end:
    ; 2nd pass – write UTF‑16 buffer (reverse order)
    mov     rdx, rsi
    mov     rsi, rdi
    add     rsi, 20*2
reverse_loop:
    dec     rdx
    mov     cl, [rbx + rdx]
    mov     [rsi - 2], cx
    sub     rsi, 2
    test    rdx, rdx
    jnz     reverse_loop
    mov     word [rsi], 0              ; null‑terminate
    pop     rdx rsi rbx
    ret

_start:
    sub rsp, 32

    mov [systemTable], rdx

    mov rax, [rdx + EFI_SYSTEM_TABLE.ConOut]       ; SystemTable->ConOut (EFI_OUTPUT_PROTOCOL *)
    mov [conout], rax
    mov r8,  [rax + EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString]        ; ConOut->OutputString
    mov [outputString], r8

    mov rcx, [conout]          ; 1st arg: EFI_OUTPUT_PROTOCOL*
    lea rdx, [strMessage1]   ; 2nd arg: CHAR16*   (pointer to our string)
    call [outputString]        ; indirect call (or `call r8` works the same)

    mov rcx, [conout]          ; 1st arg: EFI_OUTPUT_PROTOCOL*
    lea rdx, [strMessage2]   ; 2nd arg: CHAR16*   (pointer to our string)
    call [outputString]        ; indirect call (or `call r8` works the same)

	mov rdx, [systemTable]
	mov rax, [rdx + EFI_SYSTEM_TABLE.BootServices]
	mov [bootServices], rax
	mov r8, [rax + EFI_BOOT_SERVICES.WaitForEvent]
	mov [waitForEvent], r8
	mov r8, [rax + EFI_BOOT_SERVICES.Stall]
	mov [stall], r8
	
    mov rcx, [conout]          ; 1st arg: EFI_OUTPUT_PROTOCOL*
    lea rdx, [strMessage1]   ; 2nd arg: CHAR16*   (pointer to our string)
    call [outputString]        ; indirect call (or `call r8` works the same)

	mov rdx, [systemTable]
    mov rax, [rdx + EFI_SYSTEM_TABLE.ConIn]
    mov [conin], rax
    mov r8,  [rax + EFI_SIMPLE_TEXT_INPUT_PROTOCOL.ReadKeyStroke]
    mov [readKeyStroke], r8
    mov r8,  [rax + EFI_SIMPLE_TEXT_INPUT_PROTOCOL.WaitForKey]
    mov [waitForKey], r8

    mov rcx, [conout]          ; 1st arg: EFI_OUTPUT_PROTOCOL*
    lea rdx, [strMessage2]   ; 2nd arg: CHAR16*   (pointer to our string)
    call [outputString]        ; indirect call (or `call r8` works the same)

	mov rbx, 0
.loop1:
	add rbx, 1
	mov rcx, 2000000
	call[stall]

    mov rcx, [conout]          ; 1st arg: EFI_OUTPUT_PROTOCOL*
    lea rdx, [strCount2]   ; 2nd arg: CHAR16*   (pointer to our string)
    call [outputString]        ; indirect call (or `call r8` works the same)

	mov rdi, [buffer]
	mov r8, rbx
	call [convert_uint_to_utf16]

    mov rcx, [conout]          ; 1st arg: EFI_OUTPUT_PROTOCOL*
    lea rdx, [strCount2]   ; 2nd arg: CHAR16*   (pointer to our string)
    call [outputString]        ; indirect call (or `call r8` works the same)

	cmp rbx, 10
	jne .loop1

	mov rcx, 0x1
	lea rdx, [waitForKey]
	lea r8, [index]
	call [waitForEvent]

	mov rcx, [conin]
	mov rdx, [keyData]
	call [readKeyStroke]

	; mov rcx, [conin]
    ; lea rdx, [index]           ; 1st arg: EFI_KEY_DATA*
    ; call [readKeyStroke]         ; blocks until key pressed

    mov rcx, [conout]          ; 1st arg: EFI_OUTPUT_PROTOCOL*
    lea rdx, [strMessage2]   ; 2nd arg: CHAR16*   (pointer to our string)
    call [outputString]        ; indirect call (or `call r8` works the same)

	mov rcx, 0x1
	lea rdx, [waitForKey]
	lea r8, [index]
	call [waitForEvent]

	; mov rcx, [conin]
    ; lea rdx, [index]           ; 1st arg: EFI_KEY_DATA*
    ; call [readKeyStroke]         ; blocks until key pressed

    ; shutdown here if possible

    add rsp, 32
    mov rax, 0                  ; EFI_STATUS – success
    ret

section .data
    strMessage1 db __utf16__ `Enter a Key to step foreward\r\n\0`
    strMessage2 db __utf16__ `You entered a new Part!\r\n\0`

    strCount1 db __utf16__ `Count 1\r\n\0`
    strCount2 db __utf16__ `Count 2\r\n\0`
    strCount3 db __utf16__ `Count 3\r\n\0`

	image           dq 0
	systemTable     dq 0
	conout 			dq 0
	conin 			dq 0
	waitForKey 		dq 0
	outputString    dq 0
	bootServices 	dq 0
	waitForEvent 	dq 0
	stall 			dq 0
	readKeyStroke  	dq 0
	index 			dq 0
	keyData 		dq 0
	buffer 			dq 0
