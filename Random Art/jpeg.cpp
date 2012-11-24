/***************************************************************************
                          jpeg.cpp  -  description
                             -------------------
    begin                : Mon Oct 28 2002
    copyright            : (C) 2002 by Jason Fieldman
    email                : jmfieldman@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "jpeg.h"

int createjpeg(unsigned char* buffer, int w, int h, char* filename)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	FILE * outfile;

	if ((outfile = fopen(filename, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return 1;
	}
	
	jpeg_stdio_dest(&cinfo, outfile);

	
	cinfo.image_width = w;      /* image width and height, in pixels */
	cinfo.image_height = h;
	cinfo.input_components = 3;     /* # of color components per pixel */
	cinfo.in_color_space = JCS_RGB; /* colorspace of input image */

	jpeg_set_defaults(&cinfo);

	jpeg_start_compress(&cinfo, TRUE);

	// draw scanlines
	
	JSAMPROW row_pointer[1];        /* pointer to a single row */
	int row_stride;                 /* physical row width in buffer */

	row_stride = w * 3;   /* JSAMPLEs per row in image_buffer */

	while (cinfo.next_scanline < cinfo.image_height) {
		row_pointer[0] = & buffer[cinfo.next_scanline * row_stride];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	
	//close
	
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	
	fclose(outfile);
	
	return 0;
}

void putpixel(unsigned char* buffer, int w, int h, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	int pos = (x + (y*w)) * 3;
	buffer[pos] = r;
	buffer[pos+1] = g;
	buffer[pos+2] = b;
}



