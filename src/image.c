#include "image.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apply_threshold(float *img, int w, int h, int T)
{
    (void)img;
    (void)w;
    (void)h;
    (void)T;

    // TODO: Implement me!
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (*(img + (i * w + j)) > T)
            {
                *(img + (i * w + j)) = 255;
            }
            else
            {
                *(img + (i * w + j)) = 0;
            }
        }
    }
}

void scale_image(float *result, const float *img, int w, int h)
{
    (void)result;
    (void)img;
    (void)w;
    (void)h;

    // TODO: Implement me!
    // first we get the minimum and maximum pixel values->

    float minE = 2147483647, maxE = (-2147483647 - 1);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (*(img + (i * w + j)) < minE)
            {
                minE = *(img + (i * w + j));
            }

            if (*(img + (i * w + j)) > maxE)
            {
                maxE = *(img + (i * w + j));
            }
        }
    }

    // get the difference between them
    float diff = maxE - minE;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (diff == 0)
            {
                // the edge case!
                *(result + (i * w + j)) = 0;
            }
            else
            {
                // do the calculations
                *(result + (i * w + j)) = (((*(img + (i * w + j))) - minE) / diff) * 255;
            }
        }
    }
}

float get_pixel_value(const float *img, int w, int h, int x, int y)
{
    (void)img;
    (void)w;
    (void)h;
    (void)x;
    (void)y;

    float pixel;

    // TODO: Implement me!

    // the intuition is quite straightforward,we have several cases, and I will just handle them one by one
    // we don't need any looping or so, we have some quick if else statements to do

    // first check if we have the x coordinate in range or not
    if (x >= 0 && x <= w - 1)
    {
        if (y >= 0 && y <= h - 1)
        {
            pixel = *(img + (y * w + x));
        }
        else if (y < 0)
        {
            y = abs(y) - 1;
            pixel = *(img + (y * w + x));
        }
        else if (y > h - 1)
        {
            int offset = y - (h - 1);
            y = h - offset;
            pixel = *(img + (y * w + x));
        }
    }

    else if (x < 0)
    {
        if (y >= 0 && y <= h - 1)
        {
            x = abs(x) - 1;
            pixel = *(img + (y * w + x));
        }
        else if (y < 0)
        {
            x = abs(x) - 1;
            y = abs(y) - 1;
            pixel = *(img + (y * w + x));
        }
        else if (y > h - 1)
        {
            int offset = y - (h - 1);
            y = h - offset;
            x = abs(x) - 1;
            pixel = *(img + (y * w + x));

            {
                /* code */
            }
        }

        else if (x > w - 1)
        {
            if (y >= 0 && y <= h - 1)
            {
                int offset = x - (w - 1);
                x = w - offset;
                pixel = *(img + (y * w + x));
            }
            else if (y < 0)
            {
                y = abs(y) - 1;
                int offset = x - (w - 1);
                x = w - offset;
                pixel = *(img + (y * w + x));
            }
            else if (y > h - 1)
            {
                int offset_x = x - (w - 1);
                x = w - offset_x;
                int offset = y - (h - 1);
                y = h - offset;
                pixel = *(img + (y * w + x));
            }
        }
    }
    return pixel;
}
float *array_init(int size)
{
    (void)size;

    // TODO: Implement me!
    float *array = (float *)malloc(size * sizeof(float));
    // NULL safety
    if (array == NULL)
    {
        return NULL;
    }
    return array;
}

void array_destroy(float *m)
{
    (void)m;

    // Null safety then free up.
    if (m != NULL)
    {
        free(m);
    }
}

float *read_image_from_file(const char *filename, int *w, int *h)
{
    (void)filename;
    (void)w;
    (void)h;

    // TODO: Implement me!

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL; // File does not exist, returning a null pointer
    }

    char line[100];
    if (fgets(line, sizeof(line), file) == NULL || strncmp(line, "P2", 2) != 0)
    {
        fclose(file);
        return NULL; // Invalid header data
    }

    // Read width and height
    if (fgets(line, sizeof(line), file) == NULL || sscanf(line, "%d %d", w, h) != 2 || *w <= 0 || *h <= 0)
    {
        fclose(file);
        return NULL; // Invalid width/height data
    }

    int max_gray_value;
    if (fgets(line, sizeof(line), file) == NULL || sscanf(line, "%d", &max_gray_value) != 1 || max_gray_value <= 0 || max_gray_value > 255)
    {
        fclose(file);
        return NULL; // Invalid max gray value
    }

    int size = (*w) * (*h);
    float *image = array_init(size);
    if (image == NULL)
    {
        fclose(file);
        return NULL; // Memory allocation failure
    }

    int pixel;
    for (int i = 0; i < size; i++)
    {
        if (fscanf(file, "%d", &pixel) != 1 || pixel < 0 || pixel > 255)
        {
            array_destroy(image);
            fclose(file);
            return NULL; // Invalid pixel value
        }
        image[i] = (float)pixel;
    }

    // Ensure there are no extra pixels
    if (fscanf(file, "%d", &pixel) != EOF)
    {
        array_destroy(image);
        fclose(file);
        return NULL; // Too many pixels
    }

    fclose(file);
    return image;
}

void write_image_to_file(const float *img, int w, int h, const char *filename)
{
    (void)img;
    (void)w;
    (void)h;
    (void)filename;

    // TODO: Implement me!
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return; // Failed to open file for writing
    }

    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", w, h);
    fprintf(file, "255\n");

    for (int i = 0; i < w * h; i++)
    {
        fprintf(file, "%d\n", (int)img[i]);
    }

    fclose(file);
}
