#!/bin/bash
echo "average" 
awk '{ T+= $NF} END {print T/NR}' "$1"
echo "MAX"
awk '{if ($NF>a) a=$NF; } END { print a}' "$1"
echo "MIN"
awk '{b=$NF; if ($NF<b) b=$NF; } END { print b}' "$1"
echo "Done."

