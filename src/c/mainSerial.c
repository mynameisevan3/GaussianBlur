
/*======================================
    mainSerial.c
    Serial Baseline Application Runner
  ======================================*/


// Inclusions
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"
#include "pgmTools.h"


// Definitions
#define NUM_ARGS 4


// Main
int main( int argc, char **argv ) {

  // Image
        unsigned char    *image        = NULL;  // Image Pointer - 8-bit Grayscale
  const          char    *in           = NULL;  // Input Filename
  const          char    *out          = NULL;  // Output Filename
                 size_t   width        = 0;     // Image Height
                 size_t   height       = 0;     // Image Width
  // Timing Components
                 double  jobStart      = 0.0;   // Job Clock Start Time
                 double  imageInStart  = 0.0;   // Image Input Start Time
                 double  imageInEnd    = 0.0;   // Image Input End Time
                 double  opStart       = 0.0;   // Operation Start Time
                 double  opEnd         = 0.0;   // Operation End Time
                 double  imageOutStart = 0.0;   // Image Output Start Time
                 double  imageOutEnd   = 0.0;   // Image Output End Time
                 double  jobEnd        = 0.0;   // Job Clock End Time
  // Final Time Values
                 double  imageInTime   = 0.0;   // Image Input and Preparation Time
                 double  opTime        = 0.0;   // Operation Execution Time
                 double  imageOutTime  = 0.0;   // Image Output Time
                 double  addOverhead   = 0.0;   // Additional Overhead Time
                 double  jobTime       = 0.0;   // Total Program Time
  // General
                 uint8_t display       = 0;     // Argument to Display Debug Text

  // Input Argument Check and Parsing
  if( argc != NUM_ARGS ) {
    fprintf( stderr, "\nUsage:    ./gaussS <input> <output> <display>\n" );
    fprintf( stderr, "  Input   - a .pgm image upon which to perform the sobel filter operation.\n" );
    fprintf( stderr, "  Output  - a .pgm image to output with the detected edges.\n" );
    fprintf( stderr, "  Display - 1 displays debug text, 0 just displays time values for raw data tables.\n" );
    fprintf( stderr, "Example:  ./gaussS input.pgm output.pgm 1\n\n" );
    return 1;
  }
  in      = argv[1];
  out     = argv[2];
  display = atoi( argv[3] );

  // Intro Message
  if( display ) {
    fprintf( stdout, "\n   = = =  Gaussian Blur  = = =   \n\n" );
  }

  // Job Start Timer
  jobStart     = omp_get_wtime( );

  // Image Initialization
  if( display ) {
    fprintf( stdout, "Initializing Image...\n" );
  }
  imageInStart = omp_get_wtime( );
  image = readPGM( in, &width, &height );
  if( !image ) {
    fprintf( stderr, "Failed to Read %s\n", in );
    return 1;
  }
  imageInEnd   = omp_get_wtime( );

  // Sobel Filter Operation
  if( display ) {
    fprintf( stdout, "Performing Gaussian Blur Operation...\n" );
  }
  opStart = omp_get_wtime( );
  gaussianBlurSerial( image, width, height );
  opEnd   = omp_get_wtime( );

  // Image Output
  if( display ) {
    fprintf( stdout, "Outputting Image...\n" );
  }
  imageOutStart = omp_get_wtime( );
  writePGM( out, image, width, height );
  imageOutEnd   = omp_get_wtime( );

  // Final Tasks
  free( image );
  if( display ) {
    fprintf( stdout, "Operation Complete!\n\n" );
  }

  // Final Timing Component
  jobEnd       = omp_get_wtime( );                               // End Full Program Clock
  imageInTime  = imageInEnd  - imageInStart;                     // Calculate Image Input and Preparation Time
  opTime       = opEnd       - opStart;                          // Calculate Operation Time
  imageOutTime = imageOutEnd - imageOutStart;                    // Calculate Image Output Time
  jobTime      = jobEnd      - jobStart;                         // Calculate Overall Time
  addOverhead  = jobTime - imageInTime - opTime - imageOutTime;  // Calculate Additional Overhead Time
  // Handle Displaying All Timing Data
  if( display ) {  // Messages only when display is 1.
    fprintf( stdout, "=== Timing Data ===\n  Image In:\t\t" );
    fprintf( stdout, "%0.9lf\n", imageInTime );                                                                                                                  fprintf( stdout, "  Operation:\t\t" );
  }
  fprintf( stdout, "%0.9lf ", opTime );
  if( display ) {
    fprintf( stdout, "\n  Image Out:\t\t" );
    fprintf( stdout, "%0.9lf\n", imageOutTime );
    fprintf( stdout, "  Overhead:\t\t" );
    fprintf( stdout, "%0.9lf\n", addOverhead );
    fprintf( stdout, "  Total Job Time:\t" );
    fprintf( stdout, "%0.9lf\n\n", jobTime );
  }

  return 0;

}



// END mainSerial.c  - EWG SDG
