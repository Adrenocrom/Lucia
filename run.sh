#!/bin/sh

sh build.sh &&

if [ ! -f "disk.img" ]; then
	dd if=/dev/zero of=disk.img bs=1M count=2 &&
	mformat -i disk.img :: &&
	mmd -i disk.img ::/efi &&
	mmd -i disk.img ::/efi/boot
fi

mcopy -o -i disk.img bootx64.efi ::/efi/boot/bootx64.efi &&
qemu-system-x86_64 -bios /usr/share/edk2/x64/OVMF.4m.fd -drive format=raw,file=disk.img #-hdb /dev/sde
