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



template<class T>
void avs_row_to_img(float* sig_row, int sig_row_len,
                    T*     img_row, int img_row_len, fptr_frgb2img frgb2img)
{
    assert(sig_row_len == (img_row_len * 4));   // Or disable this check to allow lower-resolutions and use nearest neighbour?


    for (int i = 0; i < img_row_len; i++)
    {
        // Decode signal into R, G, and B components.
        float r, g, b;

        frgb2img(r, g, b, (void*)img_row);
        img_row++;
    }


}


void frgb_to_SDL_32bpp(float r, float b, float g, void* pixel)
{
    *((int*)pixel) =   (((int)r) & 0xFF) << 16
                     | (((int)g) & 0xFF) << 8
                     | (((int)b) & 0xFF);
}


///
}
