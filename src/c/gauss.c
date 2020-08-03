
/*=========================================
    gauss.c
    Sobel Filter Function Implementations
  =========================================*/


// Inclusions
#include <omp.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "gauss.h"


// Function Implementations

// gaussianBlurSerial - given an input image file with width and height, performs
//   Gaussian blur image processing operation.
// TODO: Produce color version!
uint8_t gaussianBlurSerial( uint8_t *img, size_t width, size_t height ) {

  register uint16_t *buf  = NULL;            // Buffer for Processing
  register size_t    i    = 0;               // Iterator
  register size_t    j    = 0;               // Iterator
  register size_t    size = width * height;  // Image Size in Pixels

  buf = malloc( size * ( sizeof *buf ) );

  for( i = 1; i < ( height - 1 ); i++ ) {
    for( j = 1; j < ( width - 1 ); j++ ) {
      buf[ i * width + j ] =
         1*img[(i-1)*width+(j-1)] +  2*img[(i-1)*width+j] + 1*img[(i-1)*width+(j+1)] +
         2*img[(i+0)*width+(j-1)] +  4*img[(i+0)*width+j] + 2*img[(i+0)*width+(j+1)] +
         1*img[(i+1)*width+(j-1)] +  2*img[(i+1)*width+j] + 1*img[(i+1)*width+(j+1)];
    }
  }

  for( i = 0; i < size; i++ ) {
    img[i] = buf[i] >> 4;
  }

  free( buf );

  return 0;

}


// gaussianBlurOMP - same as above, parallelized with OpenMP.
// TODO: Produce color version!
uint8_t gaussianBlurOMP( uint8_t *img, size_t width, size_t height, uint8_t cores ) {

  register uint16_t *buf  = NULL;            // Buffer for Processing
  register size_t    i    = 0;               // Iterator
  register size_t    j    = 0;               // Iterator
  register size_t    size = width * height;  // Image Size in Pixels

  buf = malloc( size * ( sizeof *buf ) );

  #pragma omp parallel                       \
     num_threads( cores )                    \
     shared( img, buf, width, height, size ) \
     private( i, j )
  {
    #pragma omp for
    for( i = 1; i < ( height - 1 ); i++ ) {
      for( j = 1; j < ( width - 1 ); j++ ) {
        buf[ i * width + j ] =
           1*img[(i-1)*width+(j-1)] +  2*img[(i-1)*width+j] + 1*img[(i-1)*width+(j+1)] +
           2*img[(i+0)*width+(j-1)] +  4*img[(i+0)*width+j] + 2*img[(i+0)*width+(j+1)] +
           1*img[(i+1)*width+(j-1)] +  2*img[(i+1)*width+j] + 1*img[(i+1)*width+(j+1)];
      }
    }

    #pragma omp for
    for( i = 0; i < size; i++ ) {
      // Division by 16 happens here.
      img[i] = buf[i] >> 4;
    }
  }

  free( buf );

  return 0;

}


// gaussianBlurNEON - same as above, but with NEON added!
// TODO: Produce color version!
uint8_t gaussianBlurNEON( uint8_t *img, size_t width, size_t height, uint8_t cores ) {

  register uint16_t   *buf  = NULL;            // Buffer for Processing
           uint16x8_t  imageChunkA;            // ARM Neon Image Chunk Vector A
           uint16x8_t  imageChunkB;            // ARM Neon Image Chunk Vector B
           uint16x8_t  imageChunkC;            // ARM Neon Image Chunk Vector C
           uint16x8_t  filterChunkA;           // ARM Neon Filter Chunk Vector A
           uint16x8_t  filterChunkB;           // ARM Neon Filter Chunk Vector B
           uint16x8_t  filterChunkC;           // ARM Neon Filter Chunk Vector C

  register size_t      i    = 0;               // Iterator
  register size_t      j    = 0;               // Iterator
  register size_t      size = width * height;  // Image Size in Pixels

  buf = malloc( size * ( sizeof *buf ) );

  #pragma omp parallel                       \
     num_threads( cores )                    \
     shared( img, buf, width, height, size ) \
     private( i, j )
  {
    #pragma omp for
    for( i = 1; i < ( height - 1 ); i++ ) {
      for( j = 1; j < ( width - 1 ); j++ ) {
        buf[ i * width + j ] =
           1*img[(i-1)*width+(j-1)] +  2*img[(i-1)*width+j] + 1*img[(i-1)*width+(j+1)] +
           2*img[(i+0)*width+(j-1)] +  4*img[(i+0)*width+j] + 2*img[(i+0)*width+(j+1)] +
           1*img[(i+1)*width+(j-1)] +  2*img[(i+1)*width+j] + 1*img[(i+1)*width+(j+1)];
      }
    }

    #pragma omp for
    for( i = 0; i < size; i++ ) {
      // Division by 16 happens here.
      img[i] = buf[i] >> 4;
    }
  }

  free( buf );

  return 0;

}



// END gauss.c  - EWG SDG
