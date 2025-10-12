#!/bin/sh

# dd if=/dev/zero of=disk.img bs=1M count=2 &&
# mformat -i disk.img :: &&

mcopy -i disk.img bootx64.efi ::/efi/boot/bootx64.efi &&
qemu-system-x86_64 -bios /usr/share/edk2/x64/OVMF.4m.fd -drive format=raw,file=disk.img #-hdb /dev/sde
