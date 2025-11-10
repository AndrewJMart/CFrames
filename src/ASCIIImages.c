#include "ASCIIImages.h"

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

unsigned char *PNG_To_Grayscale(unsigned char *img, int width, int height, int channels) {
	// Initialize Pointers For Output & Walking Through PNG
	unsigned char *gray_image = malloc(width * height);

	unsigned char *png_pointer = img, *gray_pointer = gray_image;

	for (; png_pointer != (img + (height*width*channels)); png_pointer += channels, gray_pointer += 1) {
		uint8_t r_pixel = *png_pointer;
		uint8_t g_pixel = *(png_pointer + 1);
		uint8_t b_pixel = *(png_pointer + 2);
		uint8_t gray_pixel = (uint8_t)floor((0.299 * r_pixel) + (0.587 * g_pixel) + (0.114 * b_pixel));
		*gray_pointer = gray_pixel;
	}

	return gray_image;
}

uint8_t *Resize_Gray_Image(unsigned char *gray_image, int width, int height, int *converted_width, int *converted_height) {
	int num_channels = 1;

	// Calcuate Aspect Ratio & Conversions
	if (height > 300 || width > 300) {
		float aspect_ratio = (float)width / height;
		*converted_height = 300;
		*converted_width = (int)(*converted_height * aspect_ratio);
	}
	else{ 
		*converted_height = height;
		*converted_width = width;
	}

	// Allocate Space For New Image
	uint8_t *resized_gray_image = malloc(*converted_height * *converted_width);
	
	// Resize Image
	stbir_resize_uint8_linear(gray_image, width, height, width * num_channels, resized_gray_image, *converted_width, *converted_height, *converted_width * num_channels, num_channels);
	
	return resized_gray_image;
}

unsigned char *Gray_To_ASCII(uint8_t *resized_gray_image, int converted_width, int converted_height) {
    // ASCII Ramp
    char map[27] = "@#W$9876543210?!abc;:+=-,._";
    
    // Allocate: width * height + newlines + null terminator
    unsigned char *ascii_output = malloc((converted_width + 1) * converted_height + 1);
    unsigned char *ascii_output_tracker = ascii_output;
    
    // Loop Through Row By Row
    int img_pos = 0;
    for (int row_pos = 0; row_pos < converted_height; row_pos++) {
        // Loop Through Column By Column
        for (int col_pos = 0; col_pos < converted_width; col_pos++) {
            uint8_t gray_pixel = resized_gray_image[img_pos];
            *ascii_output_tracker = map[((255 - gray_pixel) * 27) / 256];
            ascii_output_tracker++;
            img_pos++;
        }
        // Add newline after each row
        *ascii_output_tracker = '\n';
        ascii_output_tracker++;
    }
    
    // Null terminate
    *ascii_output_tracker = '\0';
    
    return ascii_output;
}
