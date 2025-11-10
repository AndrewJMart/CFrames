// ASCIIImages.h
#ifndef ASCIIImages
#define ASCIIImages

#include <stdint.h>
#include <stddef.h>

unsigned char *PNG_To_Grayscale(unsigned char *img, int width, int height, int channels);
uint8_t *Resize_Gray_Image(unsigned char *gray_image, int width, int height, int *converted_width, int *converted_height);
unsigned char *Gray_To_ASCII(uint8_t *resized_gray_image, int converted_width, int converted_height);

#endif
