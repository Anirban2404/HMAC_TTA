#!/bin/bash

echo "HMAC Script Started..."
dmesg -c

echo "Removing and deleting old $1 module..."
rmmod "$1"
rm "$1".ko

echo "Copying new $1 module..."
mount /dev/sdb1 /mnt/cf
cp /mnt/cf/"$1".ko /home/demo

umount /mnt/cf/

dmesg -c

echo "Inserting new $1 module in kernel..."
insmod "$1".ko

echo "Done."
