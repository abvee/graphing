#!/bin/bash
# A shell script to test if everything is working.
RED="\033[1;31m"
CLEAR="\033[0m"

# +ve slopes
echo -e "${RED}+ve slope, -ve offset${CLEAR}"
echo "Slope: 1 Offset: -8"
./a.out 1 -8
echo "Slope: 2 Offset: -8"
./a.out 2 -8
echo "Slope: 2 Offset: -7"
./a.out 2 -7
echo "Slope: 5 Offset: -40"
./a.out 5 -40

echo -e "${RED}+ve slope, +ve offset${CLEAR}"
echo "Slope: 1 Offset: 8"
./a.out 1 8
echo "Slope: 2 Offset: 8"
./a.out 2 8
echo "Slope: 2 Offset: 7"
./a.out 2 7
echo "Slope: 5 Offset: 40"
./a.out 5 40
echo "Slope: 1 Offset: 0"
./a.out 1 0

echo -e "${RED}-ve slope, +ve offset${CLEAR}"
echo "Slope: -1 Offset: 8"
./a.out -1 8
echo "Slope: -2 Offset: 8"
./a.out -2 8
echo "Slope: -2 Offset: 7"
./a.out -2 7
echo "Slope: -5 Offset: 40"
./a.out -5 40
echo "Slope: -1 Offset: 0"
./a.out -1 0

echo -e "${RED}-ve slope, -ve offset${CLEAR}"
echo "Slope: -1 Offset: -8"
./a.out -1 -8
echo "Slope: -2 Offset: -8"
./a.out -2 -8
echo "Slope: -2 Offset: -7"
./a.out -2 -7
echo "Slope: -5 Offset: -40"
./a.out -5 -40
