
/*====================================
            P G M   T O O L S
    Loading and Changing .pgm Images
  ====================================*/


// Include Guard
#ifndef PGMTOOLS_H
#define PGMTOOLS_H


// Inclusions
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// Function Prototypes
void *readPGM( const char *p, size_t *w_, size_t *h_ );
int   writePGM( const char *p, void *buf, size_t width, size_t height );


// End Include Guard
#endif



// End pgmTools.h  - EWG SDG
