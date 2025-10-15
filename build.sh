#!/bin/sh

nasm -f win64 -o boot.o boot.asm &&
lld-link /subsystem:EFI_APPLICATION /entry:_start /MACHINE:X64 /out:bootx64.efi boot.o &&

nasm -f elf64 -o fizzbuzz.o fizzbuzz.asm -O5 &&
ld fizzbuzz.o -o fizzbuzz
