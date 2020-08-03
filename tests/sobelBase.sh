#!/bin/sh
###############################################################
# Automation of Sobel Filter Serial Execution Data Collection #
###############################################################

# Variable Definitions
outfile=sobelBase
imagein=LAGrande
imageout=edge

# Header for File
echo                                                      > $outfile.txt
echo "Sobel Filter Serial Baseline Data Acquisition Run" >> $outfile.txt
echo                                                     >> $outfile.txt

# Make Program
make clean                                               >> $outfile.txt
make                                                     >> $outfile.txt
echo                                                     >> $outfile.txt

# Initial Test Run - shows which values are which.
./sobelS $imagein.pgm 4$imageout.pgm 4                   >> $outfile.txt
echo                                                     >> $outfile.txt

# Job Start Time
echo -n "Job Start "                                     >> $outfile.txt
date                                                     >> $outfile.txt

# Automated Run Loop with Varying Core Utilization
iteration=0
final=1000
while [ $iteration -lt $final ]
do
  # Remove Previous Output Images
  rm $imageout.pgm

  # Collect Data
  s=$(./sobelS $imagein.pgm $imageout.pgm 0)             >> $outfile.txt
  echo "$iteration $s"                                   >> $outfile.txt

  # Indicate Status
  echo "Iteration $iteration $s"

  # Iterate Loop
  iteration=$((iteration+1))
done

# Job End Time
echo -n "Job Completion "                                >> $outfile.txt
date                                                     >> $outfile.txt
echo                                                     >> $outfile.txt

# Can now grab newline-delimited data from outfile.txt!



# End sobelBase.sh  - EWG SDG
