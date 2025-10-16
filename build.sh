#!/bin/sh

# nasm -f win64 -o boot.o boot.asm &&
# lld-link /subsystem:EFI_APPLICATION /entry:_start /MACHINE:X64 /out:bootx64.efi boot.o &&
# 
# nasm -f elf64 -o fizzbuzz.o fizzbuzz.asm -O5 &&
# ld fizzbuzz.o -o fizzbuzz

x86_64-w64-mingw32-gcc -c -S main.c &&
x86_64-w64-mingw32-gcc -c main.c &&
lld-link /subsystem:EFI_APPLICATION /entry:EfiMain /MACHINE:X64 /out:bootx64.efi main.o
