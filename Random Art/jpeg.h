/***************************************************************************
                          jpeg.h  -  description
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


#ifndef __jpeg_h_
#define __jpeg_h_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <math.h>

int createjpeg(unsigned char* buffer, int width, int height, char* filename);
void putpixel(unsigned char* buffer, int w, int h, int x, int y, unsigned char r, unsigned char g, unsigned char b);

#endif

