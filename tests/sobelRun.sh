#!/bin/sh
#################################################################
# Automation of Sobel Filter Parallel Execution Data Collection #
#################################################################

# Variable Definitions
outfile=sobelOut
imagein=LAGrande
imageout=edge

# Header for File
echo                                            > $outfile.txt
echo "Sobel Filter Data Acquisition Run"       >> $outfile.txt
echo                                           >> $outfile.txt

# Make Program
make clean                                     >> $outfile.txt
make                                           >> $outfile.txt
echo                                           >> $outfile.txt

# Initial Test Run - shows which values are which.
./sobel $imagein.pgm 4$imageout.pgm 4 1        >> $outfile.txt
echo                                           >> $outfile.txt

# Job Start Time
echo -n "Job Start "                           >> $outfile.txt
date                                           >> $outfile.txt

# Automated Run Loop with Varying Core Utilization
iteration=0
final=1000
while [ $iteration -lt $final ]
do
  # Remove Previous Output Images
  rm *$imageout.pgm

  # Collect Data
  a=$(./sobel $imagein.pgm 1$imageout.pgm 1 0) >> $outfile.txt
  b=$(./sobel $imagein.pgm 2$imageout.pgm 2 0) >> $outfile.txt
  c=$(./sobel $imagein.pgm 3$imageout.pgm 3 0) >> $outfile.txt
  d=$(./sobel $imagein.pgm 4$imageout.pgm 4 0) >> $outfile.txt
  echo "$iteration $a $b $c $d"                >> $outfile.txt

  # Indicate Status
  echo "Iteration $iteration $a $b $c $d"

  # Iterate Loop
  iteration=$((iteration+1))
done

# Job End Time
echo -n "Job Completion "                      >> $outfile.txt
date                                           >> $outfile.txt
echo                                           >> $outfile.txt

# Can now grab newline-delimited data from outfile.txt!



# End sobelRun.sh  - EWG SDG
