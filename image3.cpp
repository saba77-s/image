#include "image3.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include<stdint.h>
using namespace std;
//everything is pretty much the same as task 2 except that we're reimplimenting the image class using a 2d array
Image :: Image()
{
	pixels=NULL;
	rows=0;
	cols=0;
}
Image ::~Image()
{
	if ( pixels !=NULL){
                for (int i=0;i<rows;i++)
                        delete[] pixels[i];
                delete [] pixels;
        }
}
/* Changes the size of an image, allocating memory as necessary, and
setting all pixels to fillcolor. Returns 0 on success, or a non-zero error*/
int Image::resize (unsigned int width, unsigned int height, uint8_t fillcolor){
	//frees the pixels
	if ( pixels !=NULL){
		for (int i=0;i<rows;i++)
			delete[] pixels[i];
		delete [] pixels;
	}
	rows=height;
	cols=width;
	pixels = new uint8_t* [rows];
        for (int i=0;i<rows;i++)
                pixels[i]=new uint8_t[cols];
	if (pixels == NULL)
		return 1;
	for (int i=0;i<rows;i++){
		for (int j=0;j<cols;j++)
			pixels[i][j]=fillcolor;
	}
	return 0;
}
/* Sets the color of the pixel at (x,y) to color. Returns 0 on success, else a non-zero 
error code. If (x,y) is not a valid pixel, the call fails and the image does not change.*/
int Image::set_pixel(unsigned int x, unsigned int y, uint8_t color){
	if (y>=rows || x>=cols)
		return 1;
	pixels[y][x] = color;
	return 0;
}
/* Gets the color of the pixel at (x,y) and stores at the address pointed to 
 by colorp. Returns 0 on success, else a non-zero error code. */
int Image::get_pixel (unsigned int x, unsigned int y,uint8_t* colorp)
{
	if (y>=rows || x>=cols || pixels==NULL || colorp==NULL)
		return 1;
	*colorp=pixels[y][x];
	return 0;
}
int Image::save (const char*  filename)
{
	if (filename ==NULL)
		return 1;
	fstream f;
	f.open(filename,fstream::out);
	if (!f.is_open())
		return 1;
	if (cols==0 && rows==0)
	{
		f.close();
		return 0;
	}
	if ((cols==0 && rows>0)||(rows==0 && cols>0))
	{
		f.close();
		return 1;
	}
	for (int i=0;i<rows;i++)
	{
		for (int j=0;j<cols;j++)
		{
			f<<(int) pixels[i][j]<<" ";
		}
		f<<endl;
	}
	f.close();
	return 0;
}
 

int Image::load(const char* filename ){
	if (filename==NULL)
		return 1;
	fstream f2;
	f2.open(filename, ios::in);
	if (!f2.is_open())
		return 1;
	int in,n=0,line=0;
	char number_lines[3000];
	while (!f2.eof()){
                f2.getline(number_lines,3000,'\n');
                line ++;
        }
        line --;
	f2.clear();
	f2.seekg(0,f2.beg);
	while (!f2.eof()){
		f2>> in;
		n++;
	}
	n--;
	f2.clear();
	if (n==0){
		if(pixels != NULL){
                        for(int i=0;i<rows;i++)
                                delete[] pixels[i];
                        delete [] pixels;
                        pixels=NULL;
                }
                rows=0;
                cols=0;
                f2.close();
                return 0;
	}
	if (line == 0){
		if (pixels !=NULL){
			for (int i=0;i<rows;i++)
                        	delete[] pixels[i];
                	delete [] pixels;
			pixels=NULL;
		}
		rows=0;
		cols=0;
		f2.close();
		return 0;
	}
	cols = n/line;
	rows = line;
	f2.clear();
        f2.seekg (0, f2.beg);
	if(pixels != NULL){
		for (int i=0;i<rows;i++)
			delete[] pixels[i];
		delete [] pixels;
		pixels=NULL;
	}
	pixels = new uint8_t* [rows];
	for (int i=0;i<rows;i++)
		pixels[i]=new uint8_t[cols];
	for (int i=0;i<rows;i++){
		for (int j=0;j<cols;j++){
			f2>>in;
			pixels[i][j] = in;
		}
	}
	f2.close();
	return 0;
 }

