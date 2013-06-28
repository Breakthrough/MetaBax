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
#include "MetaBax.h"


MetaBax::MetaBax(int sig_line_len, int sig_num_lines);
{
    _composite = new float[height * width * 4];

}


void  MetaBax::Update();     // Updates signal with image including RX noise, etc.
{
    // All this has to do is update the composite signal.
}


void MetaBax::avs_row_to_img(float* sig_row, int sig_row_len,
    void*  img_row, int img_w, fptr_frgb2img frgb_row_to_img_row)
{
    // sig_row_len = samples/row
    // img_w = pixels/row

    float *frgb_row = new float[3 * img_w];
    float *frgb_val = frgb_row;

    for (int i = 0; i < img_w; i++)
    {
        // Decode signal into R, G, and B components.
        float r = 0.0f,
              g = 0.0f,
              b = 0.0f;

        //
        // TODO: Actually decode signal values above.
        //

        *(frgb_val++) = r;
        *(frgb_val++) = g;
        *(frgb_val++) = b;
    }

    frgb_row_to_img_row(frgb_row, img_row, img_w);
        

    delete[] frgb_row;
}


void MetaBax::LoadImage(int img_w, int img_h, char* img_ptr, int stride,
    fptr_img_row_to_yiq img_row_to_yiq)
{
    for (int sig_row = 0; sig_row < sig_num_rows; sig_row++)
    {
        char* img_row_ptr = img_ptr;
        
        img_row_ptr += (((img_h * sig_row) / sig_num_rows) * img_w * stride);

        // Convert image row to YIQ (stored in private class vars).
        img_row_to_yiq(img_row_ptr, img_w, stride, sig_row);

        // Premultiply I/Q by sin/cos before further filters?
        // Maybe, maybe not - some DSP encoders do NOT.

        //
        // TODO: Investigate above.
        //
    }
}


static void MetaBax::ARGB32_row_to_yiq(char* img_row_ptr, int img_w,
    int stride, int sig_row, float* y_buffer, float* i_buffer, float* q_buffer)
{
    // nearest neighbour for the row values.
    int yiq_offset = sig_row * sig_row_len;
    for (int i = 0; i < sig_row_len; i++)
    {
        char* pixel = img_row_ptr;
        pixel += (((img_w * i) / sig_row_len) * stride);

        // pixel[0] == alpha channel == unused
        y_buffer[yiq_offset + i] = 
            0.2990f * pixel[1] + 0.5870f * pixel[2] + 0.1140f * pixel[3];
        i_buffer[yiq_offset + i] = 
            0.5957f * pixel[1] - 0.2745f * pixel[2] - 0.3214f * pixel[3];
        q_buffer[yiq_offset + i] = 
            0.2115f * pixel[1] - 0.5226f * pixel[2] + 0.3111f * pixel[3];

        //
        // TOOD: Add source for conversion matrix used above.
        //

    }
}


static void MetaBax::FRGB_row_to_ARGB32(float *frgb_row, char* img_row,
    int img_w, int stride)
{
    int   i         = 0;
    float *frgb_val = frgb_row;     
    int   *img_val  = (int*)img_row;
    // Pre-decrement pointers since they are pre-incremented in the loop below.
    frgb_row--;
    img_row--;
    // Loop through and set each pixel value in the row (32bpp RGBA).
    while (i < img_w)
    {
        *(++img_val) =   (int)(*(++frgb_val)) << 16
                       | (int)(*(++frgb_val)) << 8
                       | (int)(*(++frgb_val));
        i++;
    }
}
