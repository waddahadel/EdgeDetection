#include "convolution.h"

#include <stdlib.h>

#include "image.h"

void convolve(float *result, const float *img, int w, int h,
              const float *matrix, int w_m, int h_m)
{
    (void)result;
    (void)img;
    (void)w;
    (void)h;
    (void)matrix;
    (void)w_m;
    (void)h_m;

    // TODO: Implement me!
    // the middle coordinates of the kernel assuming this is always  odd x odd matrix =>
    int a = w_m / 2;
    int b = h_m / 2;

    // lot's of for loops, as long as the performance doesn't matter, I don't really care tbh..
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float matrix_mult_sum = 0;
            for (int j = 0; j < h_m; j++)
            {
                for (int i = 0; i < w_m; i++)
                {
                    matrix_mult_sum += (*(matrix + (j * w_m + i))) * get_pixel_value(img, w, h, x - a + i, y - b + j);
                }
            }
            *(result + (y * w + x)) = matrix_mult_sum;
        }
    }
}
