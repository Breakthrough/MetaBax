/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                     libmetabax - Main Library Header                      *
 *                                                                           *
 * This file contains mainly type and function definitions for interfacing   *
 * the libmetabax library, including all required functions to reconstruct   *
 * an analog signal from an image (assuming the appropriate pixel conversion *
 * functions are available).                                                 *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2013, Brandon "Breakthrough" Castellano.                    *
 *                                                                           *
 * libmetabax is licensed under the BSD 2-Clause License; see the included   *
 * COPYRIGHT file, or visit http://github.com/Breakthrough/MetaBax.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

namespace MetaBax
{
///

typedef void (*fptr_frgb2img)(float, float, float, void*);

// Signal Encoding:

// Signal Decoding:
template<class T>
void avs_row_to_img(float* sig_row, int sig_row_len,
                    T*     img_row, int img_row_len, fptr_frgb2img frgb2img);

// Pixel Conversion Formats (may be moved to separate file):
void frgb_to_SDL_32bpp(float r, float b, float g, void* pixel);


///
}

// namespace MB = MetaBax;

