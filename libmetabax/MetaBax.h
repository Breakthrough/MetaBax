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


class MetaBax {
  public:

    // Function pointer to floating-point RGB row blitter (converts floating point
    // values decoded from the analog video signal into an integer surface format).
    typedef void (*fptr_blit_row)(float*, char*, int, int);
    //                              |       |     |
    //                              |       |     \---- number of pixels in row
    //                              |       \---- generic pointer to surface data
    //                              \---- pointer floating point values RGBRGB-packed

    typedef void (*fptr_img_row_to_yiq)(char*, int, int, int, float*, float*, float*);


    MetaBax(int sig_line_len = 755, int sig_num_lines = 480);

    void  Update();     // Updates signal with image including RX noise, etc.
    void LoadImage(int img_w, int img_h, char* img_ptr, int stride,
        fptr_img_row_to_yiq img_row_to_yiq);


    static void ARGB32_row_to_yiq(char*  img_row_ptr, int    img_w,
                                  int    stride,      int    sig_row,
                                  float* y_buffer,    float* i_buffer, float* q_buffer);

    static void FRGB_row_to_ARGB32(float* frgb_row, char* img_row,
                                   int    img_w,    int   stride);


    int   h_sync;       // [0, sig_row_len)  then wraps around
    int   v_sync;       // [0, sig_num_rows) then wraps around


    float h_freq_err;   // [0.0f, 1.0f] or [0.0f, Infty)?
    float v_freq_err;   // [0.0f, 1.0f]
    float rx_sig_level; // [0.0f, 1.0f]

    float *_composite;

    float *_y_buffer;   // len is equal to sig_row_len * sig_num_rows.......
    float *_i_buffer;   // Consumes as much memory as the composite signal.
    float *_q_buffer;



  private:
    int   sig_num_rows;
    int   sig_row_len;

};
