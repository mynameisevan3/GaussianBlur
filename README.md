
# Gaussian Blur

This repository contains a simple Gaussian blur image processing application parallelized with OpenMP.


## Build

This application can be built by simply running the ```make``` command from within this directory.


## Usage

The Gaussian blur image processing kernel can be run using the following command.

```./gauss <input> <output> <cores> <display>```

The parameters that follow apply.

+ Input   - a .pgm image upon which to perform the sobel filter operation.
+ Output  - a .pgm image to output with the detected edges.
+ Cores   - the number of cores to utilize for this parallel operation.
+ Display - 1 displays debug text, 0 just displays time values for raw data tables.

Example:  ```./gauss input.pgm output.pgm 4 0```

The serial baseline can be run in the same manner as gaussS without the cores parameter, like so:

```./gaussS input.pgm output.pgm 0```


## Conversion

One may convert to and from .pgm images using the Unix terminal command:

```convert <filenameIn>.<extensionIn> <filenameOut>.<extensionOut>```


## Automated Data Acquisition

Scripts designed to automate the process of acquiring execution time and power data on the facsimiles are included.  Both scripts default to one thousand runs and parallelize to four cores.
