
/*====================================
            P G M   T O O L S
    Loading and Changing .pgm Images
  ====================================*/


// Inclusions
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "pgmTools.h"


// Definitions
#define MAXCOLOR8 255


// Function Implementations

// readPGM - read a .ppm image file named filename and output a pointer to
//   that image.
void *readPGM( const char *p, size_t *w_, size_t *h_ ) {
  FILE *file = fopen( p, "r" );
  if( !file )
    return 0;
  if( fscanf( file, "P5\n%zu %zu\n255\n", w_, h_ ) < 2 )
    goto err;
  void *buf = 0;
  size_t w = *w_, h = *h_;
  if( !w || !h || w > SIZE_MAX/h )
    goto err;
  if( !( buf = malloc( h * w ) ) )
    goto err;
  if( fread( buf, 1, ( h * w ), file ) != ( h * w ) )
    goto err;
  fclose( file );
  return buf;
err:
  free( buf );
  fclose( file );
  return 0;
}


// writePGM - write out the image given by the output pointer to the
//   filename specified.
int writePGM( const char *p, void *buf, size_t width, size_t height ) {
  FILE *file = fopen( p, "wb" );
  if( !file )
    return -1;
  fprintf( file, "P5\n%zu %zu\n255\n", width, height );
  fwrite( buf, 1, ( height * width ), file );
  fclose( file );
  return 0;
}



// End pgmTools.c  - EWG SDG
