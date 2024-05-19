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
       const *blury_image = (float *)malloc(width * height * sizeof(float));
       if (blury_image == NULL)
       {
              fprintf(stderr, "Failed to allocate memory for blurred image\n");
              array_destroy(image); // free the memory allocated for the input image
              return 1;
       }
       convolve(blury_image, image, width, height, gaussian_k, gaussian_w, gaussian_h);

       // write blurred image to file
       char *blur_file = "out_blur.pgm";
       write_image_to_file(blury_image, width, height, blur_file);

       /**
        * Compute the derivation of the blurred image computed above in both x and
        * y direction.
        *
        * Afterwards, rescale both results and write them to the files out_d_x.pgm
        * and out_d_y.pgm respectively.
        */
       // TODO: Implement me!

       // two pointers, point at two arrays for our two results, then regular stuff.
       /**/
       float *derivative_x = (float *)malloc(width * height * sizeof(float));
       if (derivative_x == NULL)
       {
              fprintf(stderr, "Failed to allocate memory for derivative in x direction\n");
              free(blury_image);    // free the memory allocated for the blurred image
              array_destroy(image); // free the memory allocated for the input image
              return 1;
       }

       derivation_y_direction(derivative_x, blury_image, width, height);

       // Write derivative in x direction to file
       char *d_x_file = "out_d_x.pgm";
       write_image_to_file(derivative_x, width, height, d_x_file);

       // Free dynamically allocated memory for the derivative in x direction
       free(derivative_x);

       // Compute the derivative in y direction using the blurred image
       float *derivative_y = (float *)malloc(width * height * sizeof(float));
       if (derivative_y == NULL)
       {
              fprintf(stderr, "Failed to allocate memory for derivative in y direction\n");
              free(blury_image);    // Free the memory allocated for the blurred image
              array_destroy(image); // Free the memory allocated for the input image
              return 1;
       }

       derivation_y_direction(derivative_y, blury_image, width, height);

       // Write derivative in y direction to file
       char *d_y_file = "out_d_y.pgm";
       write_image_to_file(derivative_y, width, height, d_y_file);

       // Free dynamically allocated memory for the derivative in y direction
       free(derivative_y);

       // Free dynamically allocated memory for the blurred image
       free(blury_image);

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
