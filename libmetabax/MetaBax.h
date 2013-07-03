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


#ifndef PI
#define PI 3.141593
#endif

#ifndef PI_4
#define PI_4 (PI/4)
#endif

#ifndef PI_33_DEG
#define PI_33_DEG 0.57596
#endif


class MetaBax {

  public:

    // Function pointer to floating-point RGB row blitter (converts floating point
    // values decoded from the analog video signal into an integer surface format).
    typedef void (*fptr_frgb_row_to_img)(float*, char*, int, int);
    //                              |       |     |     \- stride of a pixel (in bytes)
    //                              |       |     \---- number of pixels in row
    //                              |       \---- generic pointer to surface data
    //                              \---- pointer floating point values RGBRGB-packed

    typedef void (*fptr_img_row_to_yiq)(char*, int, int, int, float*, float*, float*);
    //                                    img,   w, str, sig row len,  y,      i,      q


    MetaBax(int sig_line_len = 755, int sig_num_lines = 480);
    ~MetaBax();


    void Update();     // Updates signal with image including RX noise, etc.

    void LoadImage(int img_w, int img_h, char* img_ptr, int stride, int pitch,
                   fptr_img_row_to_yiq img_row_to_yiq);

    void GetImage(char* img_ptr, int img_w, int img_h, int stride, int pitch,
        fptr_frgb_row_to_img frgb_row_to_img_row);

    void DecodeRow(int sig_row, float *frgb_row, int img_w);


    void SetImage_Blank();
    void SetImage_TestCard();


    // Maybe put the below functions in a seperate file (not in the class,
    // but in a namespace) since they will vary with the surface/image type.
    static void ARGB32_row_to_yiq(char*  img_row_ptr, int    img_w,
                                  int    stride,      int    sig_line_len,
                                  float* y_row_ptr,   float* i_row_ptr,  float* q_row_ptr);

    static void FRGB_row_to_ARGB32(float* frgb_row, char* img_row,
                                   int    img_w,    int   stride);

    

    //
    // Decoder "TV" Controls:
    //
    // Colour Controls:
    float tint_phase;
    float level_y;
    float level_i;
    float level_q;

    // Frequency & Synchronization
    int   h_sync;       // [0, sig_line_len)  then wraps arounds
    int   v_sync;       // [0, sig_num_lines) then wraps around
    float h_freq_err;   // [0.0f, 1.0f] or [0.0f, Infty)?
    float v_freq_err;   // [0.0f, 1.0f]
    
    float rx_sig_level; // [0.0f, 1.0f]






    // Raw composite signal, updated from the y, i, and q buffers below.
    float *_composite;

    // We hold a buffer of the raw y, i, and q values obtained from sampling the
    // input image so they can be filtered later if needed, and so the composite
    // signal can be reconstructed quickly (without referencing the image).
    float *_y_buffer;   // These are equal to the signal length as well.
    float *_i_buffer;   // They can also be used to emulate other signals, like
    float *_q_buffer;   // S-Video or Component video (as opposed to composite).


  private:

    int   sig_num_lines;
    int   sig_line_len;
    int   sig_len;

};
