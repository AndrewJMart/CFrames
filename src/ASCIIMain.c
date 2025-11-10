#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "ASCIIImages.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../stb_image/stb_image_resize2.h"



int main(int argc, char **argv) {
	// Store Info
	int width, height, channels;

	// Load Image
	//unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);
	
	// Create Gray Image
	//unsigned char *gray_image = PNG_To_Grayscale(img, width, height, channels);

	// Free PNG Image
	//free(img);

	// Resize Gray Image
	//int *converted_height = malloc(sizeof(int));
	//int *converted_width = malloc(sizeof(int));

	//uint8_t *resized_gray_image = Resize_Gray_Image(gray_image, width, height, converted_width, converted_height);

	// Free Gray Image
	//free(gray_image);
		
	// Print Resized Image To ASCII
	//Gray_To_ASCII(resized_gray_image, *converted_width, *converted_height);

	// Free Resized Gray Image
	//free(resized_gray_image);

	// GIF Pipeline

	// Read GIF File
	FILE *gif_file;
	
	// Read In File
	gif_file = fopen (argv[1], "rb");
	
	// Seek To End Of File
	fseek(gif_file, 0, SEEK_END);
	
	// Find Size Of File
	int gif_size = ftell(gif_file);
	
	// Rewind Back To Start Of File
	rewind(gif_file);

	// Allocate Space For Buffer
	unsigned char *gif_buffer = malloc(gif_size);

	// Place File Into Buffer
	fread(gif_buffer, 1, gif_size, gif_file);

	// Create Variables To Read In GIF From Memory
	int x, y, frames, comp;
	int *delays = NULL;

	unsigned char *gif_pixels = stbi_load_gif_from_memory(gif_buffer, gif_size, &delays, &x, &y, &frames, &comp, 0);

	if (!gif_pixels) {
		printf("Failed To Load");
		
	}

    free(gif_buffer);
	
	// Walk Through Frames
	int png_channels = 3;
	unsigned char *gif_pixel_tracker = gif_pixels;

	// Store ASCII Frames
	char **ascii_frames = malloc((frames + 1) * sizeof(char*));

	for (int frame_count = 0; frame_count < frames; frame_count++) {
	      // Create 3 Channel Pointer For PNG To Grayscale
	      unsigned char *frame_pixels = malloc(x * y * 3);
	      
	      // Track Where You Are For Frame_Pixels
	      unsigned char *frame_pixel_tracker = frame_pixels;
	
	      // Calc End Of Frame
	      unsigned char *frame_end = gif_pixel_tracker + (x * y * comp);

	      // Loop Through Each Pixel In Frame
	      for (; gif_pixel_tracker < frame_end; gif_pixel_tracker += comp, frame_pixel_tracker += png_channels) {
		      
		      // Grab Pixel's RGB Values
		      uint8_t r_pixel = gif_pixel_tracker[0];
		      uint8_t g_pixel = gif_pixel_tracker[1];
		      uint8_t b_pixel = gif_pixel_tracker[2];

		      //printf("1: %p, 2: %p, 3: %p\n", &gif_pixel_tracker[0], &gif_pixel_tracker[1], &gif_pixel_tracker[2]);
		      //printf("R: %d, G: %d, B: %d\n", r_pixel, g_pixel, b_pixel);

		      // Copy Over Pixels
		      frame_pixel_tracker[0] = r_pixel;
		      frame_pixel_tracker[1] = g_pixel;
		      frame_pixel_tracker[2] = b_pixel;
	      }
	      
	      // Now Call PNG_To_Grayscale On Processed Frame
	      unsigned char *grayscale_frame = PNG_To_Grayscale(frame_pixels, x, y, 3);
	      // Free Frame Pixels
	      free(frame_pixels);

	      // Now Resize Grayscale image
	      int converted_width, converted_height; 
	      unsigned char *resized_grayscale_frame = Resize_Gray_Image(grayscale_frame, x, y, &converted_width, &converted_height); 
	      // Free Original Grayscale Frame
	      free(grayscale_frame);

	      // Convert Resized Grayscale Frame to ASCII
	      unsigned char *ascii_art = Gray_To_ASCII(resized_grayscale_frame, converted_width, converted_height);

	      ascii_frames[frame_count] = malloc(strlen(ascii_art));

	      strcpy(ascii_frames[frame_count], ascii_art);

	      //printf("%s\n", ascii_art);

	      //printf("Frame: %d\n", frame_count);

	      free(resized_grayscale_frame);
	      free(ascii_art);
	}

	while (1) {
    		for (int i = 0; i < frames; i++) {
        		// Clear the entire screen and move cursor to top-left
        		system("clear");

        		// Print the ASCII frame
        		printf("%s\n", ascii_frames[i]);
        		fflush(stdout);

        		// Wait for the frame delay (convert from 1/100ths of a second to microseconds)
        		usleep(delays[i] * 1000);
    		}
	}

	return 0;
}
