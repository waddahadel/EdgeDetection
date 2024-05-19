#include <stdio.h>
#include <stdlib.h>

#include "argparser.h"
#include "convolution.h"
#include "derivation.h"
#include "gaussian_kernel.h"
#include "image.h"

int main(int const argc, char **const argv)
{
       /**
        * Parse arguments. The parsed image file name and threshold are available
        * in the image_file_name and threshold global variables (see argparser.h).
        */
       parse_arguments(argc, argv);
       printf("Computing edges for image file %s with threshold %i\n",
              image_file_name, threshold);

       /**
        * Read Image from given file.
        *
        * If the input file is broken terminate with return value 1.
        *
        * Hint: The width and height of the image have to be accessible in the
        * scope of this function.
        */
       // TODO: Implement me!
       // Read Image from given file
       int width, height;
       float *image = read_image_from_file(image_file_name, &width, &height);
       if (image == NULL)
       {
              fprintf(stderr, "Failed to read image from file %s\n", image_file_name);
              return 1;
       }
       /**
        * Blur the image by using convolve with the given Gaussian kernel matrix
        * gaussian_k (defined in gaussian_kernel.h). The width of the matrix is
        * gaussian_w, the height is gaussian_h.
        *
        * Afterwards, write the resulting blurred image to the file out_blur.pgm.
        */
       // TODO: Implement me!
       float *blury_image;

       // create a result array and make the values start at 0.0

       float result[width * height];

       for (int i = 0; i < width * height; i++)
       {
              result[i] = 0.0;
       }
       blury_image = result;
       char *blur_file; // pointer to the file out_blur.pgm
       blur_file = "out_blur.pgm";
       convolve(blury_image, image, width, height, gaussian_k, gaussian_w, gaussian_h);
       write_image_to_file(blury_image, width, height, blur_file);

       /**
        * Compute the derivation of the blurred image computed above in both x and
        * y direction.
        *
        * Afterwards, rescale both results and write them to the files out_d_x.pgm
        * and out_d_y.pgm respectively.
        */
       // TODO: Implement me!

       /**
        * Compute the gradient magnitude of the blurred image by using the
        * (unscaled!) derivations in x- and y-direction computed earlier.
        *
        * Afterwards, rescale the result and write it to out_gm.pgm.
        */
       // TODO: Implement me!

       /**
        * Apply the threshold to the gradient magnitude.
        * Then write the result to the file out_edges.pgm.
        */
       // TODO: Implement me!

       /**
        * Remember to free dynamically allocated memory when it is no longer used!
        */
}
