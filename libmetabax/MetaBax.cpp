 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                       libmetabax - Main Source File                       *
 *                                                                           *
 * This file contains the implementations for many of the analog encoding    *
 * and decoding functionality provided by libmetabax.  Note that some state  *
 * variables should be kept in the target application should one want to     *
 * manipulate or tune these parameters while the application is running.     *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2013, Brandon "Breakthrough" Castellano.                    *
 *                                                                           *
 * libmetabax is licensed under the BSD 2-Clause License; see the included   *
 * COPYRIGHT file, or visit http://github.com/Breakthrough/MetaBax.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>

namespace MetaBax
{
///


void avs_row_to_img(float* sig_row, int sig_row_len,
                    void*  img_row, int img_row_len, fptr_frgb2img frgb_row_to_img_row)
{
    // sig_row_len = samples/row
    // img_row_len = pixels/row

    float *frgb_row = new float[3 * img_row_len];
    float *frgb_val = frgb_row;

    for (int i = 0; i < img_row_len; i++)
    {
        // Decode signal into R, G, and B components.
        float r, g, b;

        //...

        *(frgb_val++) = r;
        *(frgb_val++) = g;
        *(frgb_val++) = b;
    }

    frgb_row_to_img_row(frgb_row, img_row, img_row_len);
        

    delete[] frgb_row;
}


void frgb_row_conv_32bppARGB(float *frgb_row, void* img_row, int img_row_len)
{
    int   i         = 0;
    float *frgb_val = frgb_row;     
    int   *img_val  = (int*)img_row;
    // Pre-decrement pointers since they are pre-incremented in the loop below.
    frgb_row--;
    img_row--;
    // Loop through and set each pixel value in the row (32bpp RGBA).
    while (i < img_row_len)
    {
        *(++img_val) =   (int)(*(++frgb_val)) << 16
                       | (int)(*(++frgb_val)) << 8
                       | (int)(*(++frgb_val));
        i++;
    }
}


///
}
