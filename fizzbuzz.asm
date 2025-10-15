global _start

section .data
    strSpace		db 0x9, 0xD
    strFizz			db "Fizz", 0xD
    strBuzz 		db "Buzz", 0xD
    strEndl 		db 0xA, 0xD
    buffer 			db 64 dup(0)

section .text

; print integer and add newline
; get integer from rcx
integerToAscii:
    push rbx
    push rsi
    
    mov rax, rcx
    xor rbx, rbx

.integerToAsciiDivide:
    inc rbx

    xor rdx, rdx
    mov rsi, 10
    idiv rsi
    
    add rdx, 0x30
    push rdx

    cmp rax, 0
    jnz .integerToAsciiDivide

	xor r8, r8
.integerToAsciiOutput:
    dec rbx

    pop rax
	mov [buffer + r8], al
	inc r8

    cmp rbx, 0
    jnz .integerToAsciiOutput

    mov     rax, 1
    mov     rdi, 1
    mov     rsi, buffer
	mov		rdx, r8
    syscall

    pop rsi
    pop rbx
    ret

; print fizzbuzz
; get integer from rcx
printFizzBuss:
    push rbx
    push rsi

	xor r8, r8
.printFizz:
	push rcx
	mov rax, rcx
    xor rdx, rdx
	mov rsi, 3
	idiv rsi

	cmp rdx, 0
	jne .printBuzz

	inc r8
    mov     rax, 1
    mov     rdi, 1
    lea     rsi, strFizz
	mov		rdx, 4
    syscall

.printBuzz:
	pop rax
    xor rdx, rdx
	mov rsi, 5
	idiv rsi

	cmp rdx, 0
	jne .printFizzBussEnd

	inc r8
    mov     rax, 1
    mov     rdi, 1
    lea     rsi, strBuzz
	mov		rdx, 4
    syscall
.printFizzBussEnd:
    mov     rax, 1
    mov     rdi, 1
    lea     rsi, strEndl
	mov		rdx, 1
    syscall
.printFizzBussReturn:
    pop rsi
    pop rbx
    ret

_start:
	xor rbx, rbx

.loop: inc rbx

	mov rcx, rbx
    call integerToAscii

    mov     rax, 1
    mov     rdi, 1
    mov     rsi, strSpace
	mov		rdx, 1
    syscall

	mov rcx, rbx
	call printFizzBuss
	
	cmp rbx, 1000000
	jne .loop

	mov rax, 60
	xor rdi, rdi
	syscall
