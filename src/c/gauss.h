
/*=======================================
    gauss.h
    Header for Gaussian Blur Operations
  =======================================*/


// Include Guard
#ifndef GAUSS_H
#define GAUSS_H


// Inclusions
#include <stdint.h>


// Function Prototypes
uint8_t gaussianBlurSerial( uint8_t *img, size_t width, size_t height );
uint8_t gaussianBlurOMP( uint8_t *img, size_t width, size_t height, uint8_t cores );
uint8_t gaussianBlurNEON( uint8_t *img, size_t width, size_t height, uint8_t cores );


// End Include Guard
#endif



// END gauss.h  - EWG SDG
