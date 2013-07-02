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


#include "MetaBax.h"

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>


MetaBax::MetaBax(int sig_line_len, int sig_num_lines)
{
    int sig_len = sig_line_len * sig_num_lines;

    this->sig_len       = sig_len;
    this->sig_line_len  = sig_line_len;
    this->sig_num_lines = sig_num_lines;

    _composite = new float[sig_len];
    _y_buffer  = new float[sig_len];
    _i_buffer  = new float[sig_len];
    _q_buffer  = new float[sig_len];

    this->SetImage_Blank();

    //
    // TODO: Check above if anything can't be allocated.
    //
}

void MetaBax::SetImage_Blank()
{
    for (int i = 0; i < this->sig_len; i++)
        this->_composite[i] = this->_y_buffer[i] =
        this->_i_buffer[i]  = this->_q_buffer[i] = 0.0f;
}

void MetaBax::SetImage_TestCard()
{
    // TODO: Add code to fill in Y/I/Q values for testcard.

}


MetaBax::~MetaBax()
{
    delete[] _composite;
    delete[] _y_buffer;
    delete[] _i_buffer;
    delete[] _q_buffer;
}


void MetaBax::Update()     // Updates signal with image including RX noise, etc.
{
    // All this has to do is update the composite signal.

    float iq_multiplier[4];
    for (int i = 0; i < 4; i++)
    {
        iq_multiplier[i] = cos( ((i%4) * PI_4) + PI_33_DEG );
    }


    for (int i = 0; i < this->sig_len; i++)
    {
        // _composite[i] = ((float)rand()/RAND_MAX) * 255.0f;
        // _composite[i] = (_composite[i] * 0.08f) + (_y_buffer[i] * 0.92f);

        _composite[i] = (_y_buffer[i] * 2.0f)
            + ( _i_buffer[i] * 0.75f * iq_multiplier[(i+1) % 4] )
            + ( _q_buffer[i] * 0.75f * iq_multiplier[ (i)  % 4] );
    }
}


void MetaBax::GetImage(char* img_ptr, int img_w, int img_h, int stride, int pitch,
    fptr_frgb_row_to_img frgb_row_to_img_row)
{
    float *frgb_row = new float[3 * img_w];

    // Loop through image, and set image data based on decoded composite signal.
    for (int i = 0; i < img_h; i++)
    {
        //
        // Decode signal into FRGB row buffer.
        //
        int sig_row = (this->sig_num_lines * i) / img_h;
        // Decode one row at a time; right now, using noise
        // from testing data to set the colours.
        this->DecodeRow(sig_row, frgb_row, img_w);

        //
        // Update image with decoded row.
        //
        char* img_row_ptr = img_ptr + (i * pitch);  // pitch is in bytes already.
        frgb_row_to_img_row(frgb_row, img_row_ptr, img_w, stride);
    }
    
    delete[] frgb_row;
}


// Below, this *should* (testing mode now) decode 1 NTSC row into an FRGB buffer,
// the length of which is the image.
void MetaBax::DecodeRow(int sig_row, float *frgb_row, int img_w)
{
    float iq_multiplier[4];
    for (int i = 0; i < 4; i++)
        iq_multiplier[i] = cos(PI_4 * (i) + PI*(0.12f));


    float *composite_ptr = this->_composite + (sig_row * this->sig_line_len);
    for (int i = 0; i < img_w; i++)
    {
        int sig_offset         = (this->sig_line_len * i) / img_w;
        int aligned_sig_offset = sig_offset;

        if (aligned_sig_offset % 4 == 3)
            aligned_sig_offset++;
        while (aligned_sig_offset % 4 && aligned_sig_offset > 0)
            aligned_sig_offset--;

        if ((aligned_sig_offset+3) >= (sig_line_len-1))
            aligned_sig_offset -= 4;

        assert(aligned_sig_offset >= 0 && aligned_sig_offset < sig_line_len);

        float y_val = 0.0f,
              i_val = 0.0f,
              q_val = 0.0f;

        y_val = composite_ptr[sig_offset];

        for (int j = 0; j < 4; j++)
        {
            i_val += composite_ptr[sig_offset+j] * iq_multiplier[(i+1)%4];
            q_val += composite_ptr[sig_offset+j] * iq_multiplier[(i)];
        }

        float r = (y_val + ( 0.946882f*i_val) + ( 0.623557*q_val)) * 255.0f;;
        float g = (y_val + (-0.274788f*i_val) + (-0.635691*q_val)) * 255.0f;
        float b = (y_val + (-1.108545f*i_val) + ( 1.709007*q_val)) * 255.0f;
        if (r > 255.0f) r = 255.0f; else if (r < 0.0f) r = 0.0f;
        if (g > 255.0f) g = 255.0f; else if (g < 0.0f) g = 0.0f;
        if (b > 255.0f) b = 255.0f; else if (b < 0.0f) b = 0.0f;
        *(frgb_row++) = r;
        *(frgb_row++) = g;
        *(frgb_row++) = b;
         
    }
}


void MetaBax::LoadImage(int img_w, int img_h, char* img_ptr, int stride, int pitch,
    fptr_img_row_to_yiq img_row_to_yiq)
{
    for (int sig_line = 0; sig_line < sig_num_lines; sig_line++)
    {
        char* img_row_ptr = img_ptr;
        img_row_ptr += (((img_h * sig_line) / sig_num_lines) * pitch);

        int sig_offset = (sig_line * sig_line_len);

        // Convert image row to YIQ (stored in private class vars).
        img_row_to_yiq(img_row_ptr, img_w, stride, sig_line_len,
            this->_y_buffer + sig_offset, this->_i_buffer + sig_offset,
            this->_q_buffer + sig_offset);

        // Premultiply I/Q by sin/cos before further filters?
        // Maybe, maybe not - some DSP encoders do NOT.

        //
        // TODO: Investigate above.
        //
    }
}


void MetaBax::ARGB32_row_to_yiq(char* img_row_ptr, int img_w, int stride,
    int sig_line_len, float* y_row_ptr, float* i_row_ptr, float* q_row_ptr)
{
    // nearest neighbour for the row values.
    for (int i = 0; i < sig_line_len; i++)
    {
        unsigned char* pixel = (unsigned char*)img_row_ptr;
        pixel += (((img_w * i) / sig_line_len) * stride);

        // pixel[0] == alpha channel == unused
        y_row_ptr[i] = 
            0.2990f * pixel[1] + 0.5870f * pixel[2] + 0.1140f * pixel[3];
        i_row_ptr[i] = 
            0.5957f * pixel[1] - 0.2745f * pixel[2] - 0.3214f * pixel[3];
        q_row_ptr[i] = 
            0.2115f * pixel[1] - 0.5226f * pixel[2] + 0.3111f * pixel[3];

        //
        // TOOD: Add source for conversion matrix used above.
        //

    }
}


void MetaBax::FRGB_row_to_ARGB32(float *frgb_row, char* img_row, int img_w, int stride)
{
    int   i         = 0;
    float *frgb_val = frgb_row;     
    int   *img_val  = (int*)img_row;
    // Loop through and set each pixel value in the row (32bpp RGBA).
    while (i < img_w)
    { 
        int r = (int)*(frgb_val++);
        int g = (int)*(frgb_val++);
        int b = (int)*(frgb_val++);
        *(img_val++) =   (r << 16)
                       | (g << 8)
                       | (b);
        i++;
    }
}
