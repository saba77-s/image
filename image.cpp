#include "image.hpp"
#include <stdio.h>
#include <stdint.h>
using namespace std;
Image :: Image()
{
	pixels=NULL;
	rows=0;
	cols=0;
}
Image ::~Image()
{
	if(pixels !=NULL)
		delete[] pixels;
}
/* Changes the size of an image, allocating memory as necessary, and
setting all pixels to fillcolor. Returns 0 on success, or a non-zero error*/
int Image::resize (unsigned int width, unsigned int height, uint8_t fillcolor){
	//frees the pixels
	delete[] pixels;
	uint8_t pixels[height*width];
	if (pixels == NULL)
	{
		return 1;
	}
	int i= height*width;
	while (i>0)
	{
		pixels[i] = fillcolor;
		i--;
	}
	return 0;
}
/* Sets the color of the pixel at (x,y) to color. Returns 0 on success, else a non-zero 
error code. If (x,y) is not a valid pixel, the call fails and the image does not change.*/
int Image::set_pixel(unsigned int x, unsigned int y, uint8_t color){
	if (y>=rows || x>=cols)
		return 1;
	pixels[y*cols+x] = color;
	return 0;
}
/* Gets the color of the pixel at (x,y) and stores at the address pointed to 
 by colorp. Returns 0 on success, else a non-zero error code. */
int Image::get_pixel (unsigned int x, unsigned int y,uint8_t* colorp)
{
	if (y>=rows || x>=cols)
		return 1;
	*colorp=pixels[y*cols+x];
	return 0;
} 
