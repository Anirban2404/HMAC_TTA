#!/bin/bash
rm file.txt
dmesg -c
rmmod "$1"
insmod "$1"
dmesg>file.txt
echo "average" 
awk '{ T+= $NF} END {print T/NR}' file.txt
echo "MAX"
awk '{if ($NF>a) a=$NF; } END { print a}' file.txt
echo "MIN"
awk '{b=$NF; if ($NF<b) b=$NF; } END { print b}' file.txt
echo "Done."

