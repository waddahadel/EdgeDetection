# Edge Detection Project

## Overview
Welcome to my Edge Detection Project! This project involves creating a powerful C program capable of detecting edges in images. Edge detection is crucial for various applications such as object detection, artistic image filters, and image compression.

## Project Steps
Here's a quick rundown of what I did:

### 1. Read the Original Image
First, I loaded the image into the program. This involves reading the image file and storing its pixel values in a suitable data structure.

### 2. Blur the Image
To reduce noise, I applied a Gaussian blur. The Gaussian kernel I used is defined as:
```math
 G(x, y) = \frac{1}{2\pi\sigma^2} e^{-\frac{x^2 + y^2}{2\sigma^2}} 
```
where $` \sigma `$ is the standard deviation. This kernel is applied to the image using convolution.

### 3. Compute Discrete Derivatives
Next, I used Sobel operators to find changes in pixel intensity. The Sobel kernels for the x and y directions are:
```math
 K_x = \begin{bmatrix} -1 & 0 & 1 \\ -2 & 0 & 2 \\ -1 & 0 & 1 \end{bmatrix} 
 K_y = \begin{bmatrix} -1 & -2 & -1 \\ 0 & 0 & 0 \\ 1 & 2 & 1 \end{bmatrix} 
```
Applying these kernels to the image gives the gradients \( G_x \) and \( G_y \).

### 4. Calculate Gradient Magnitude
To determine the strength of edges, I computed the gradient magnitude at each pixel using:
```math
 G = \sqrt{G_x^2 + G_y^2} 
```
### 5. Thresholding
To highlight significant edges, I compared pixel values to a threshold. Pixels with gradient magnitudes above the threshold are considered edges.

### 6. Output the Edge Image
Finally, I generated a black-and-white image showing the detected edges.

## Assignments

### 1. Threshold
I implemented a function to recolor pixels based on a threshold value.

### 2. Gradient Magnitude
I computed the magnitude of the gradient vector using the derivatives obtained from the Sobel operators.

### 3. Scale Gray-Scale Values
I scaled the computed gradient magnitudes back to the 0-255 range for proper image representation.

### 4. Convolution
I applied convolution with the Gaussian kernel to blur the image and with the Sobel kernels to compute the derivatives.

### 5. Reading and Writing Images
I implemented functions to read from and write images to files in the PGM format, ensuring proper handling of image data.

### 6. Main Function
I combined all previous steps into the main function to create the complete edge detection pipeline.

## How to Run

1. **Compile the Project**: Run `make` to build the project.
2. **Run Edge Detection**: Use the command `./bin/edgedetection -T <threshold> <image file>` to execute the program with your chosen threshold and image file.

## Testing

Run `make tests` to execute public tests and ensure your implementation is correct. You can also run specific tests using the command `python3 test/run-tests.py -f <test_name>`.


 For more details on the Sobel operator, check out [this link](https://en.wikipedia.org/wiki/Sobel_operator). 
