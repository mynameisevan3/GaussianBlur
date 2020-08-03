#!/bin/sh
#######################################################
# Automation of Sobel Filter Power Measure Collection #
#######################################################

# Variable Definitions
outfile=sobelPowerOut
imagein=LAGrande
imageout=edge
coreStart=1
coreEnd=4

# Header
echo "Sobel Filter Power Measure Run"
# No File Generation Here - Just for Power Measures

# Make Program
make clean
make
echo

# Initial Test Run - shows which values are which.
./sobel $imagein.pgm 4$imageout.pgm 4 1

# Automated Run Loop with Varying Core Utilization
for cores in `seq $coreStart $coreEnd`
do
  echo " "
  echo "Running with $cores Cores..."
  iteration=0
  final=100
  while [ $iteration -lt $final ]
  do
    # Remove Previous Output Images
    rm *$imageout.pgm

    # Run Application
    p=$(./sobel $imagein.pgm $cores$imageout.pgm $cores 0)

    # Indicate Status
    echo "Iteration $iteration $p"

    # Iterate Loop
    iteration=$((iteration+1))
  done
done



# End sobelPower.sh  - EWG SDG
