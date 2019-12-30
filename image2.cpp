#include "image2.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<fstream>
using namespace std;
Image::Image ()
{
	pixels=NULL;
	rows=0;
	cols=0;
}
Image::~Image()
{
	if (pixels !=NULL)
		delete[] pixels;
	rows=0;
	cols=0;
}
int Image::resize(unsigned int width,unsigned height,uint8_t fillcolor)
{
	if (pixels !=NULL)
		delete[] pixels;
	pixels= new uint8_t[width*height];
	if (pixels != NULL)
	{
		int i=width*height;
		while (i>0)
		{
			pixels[i]=fillcolor;
			i--;
		}
		rows=height;
		cols=height;
		return 0;
	}
	return 1;
}
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
//image can't have a non zero dimension when the other dimension is zero
	if ((cols==0 && rows>0)||(rows==0 && cols>0))
	{
		f.close();
		return 1;
	}
//saves the pixels into the file
	for (int i=0;i<rows;i++)
	{
		for (int j=0;j<cols;j++)
		{
			f<<(int)pixels[i*cols+j]<<" ";
		}
		f<<endl;
	}
	f.close();
	return 0;
}
int Image::load(const char* filename){
	if (filename==NULL)
		return 1;
	fstream f2;
	f2.open(filename, ios::in);
	if (!f2.is_open())
		return 1;
	int in,i,n=0,line=0;
	char number_lines[3000];
//getline receives elements in each line I set size of char array to 3000 just to make sure it can contain the whole line
	while (!f2.eof()){
                f2.getline(number_lines,3000,'\n');
                line ++;
        }
        line--;
	f2.clear();
//have to move seekg to the beginning again inorder to find the numbere of lines
	f2.seekg (0, f2.beg);
//finds the total size and save it into n
	while (!f2.eof()){
                f2>> in;
                n++;
        }
        n--;
        f2.clear();
//if number of lines is zero then rows and cols should be zero too pixels sould be NULL
	if (line == 0){
		if(pixels != NULL)
                	delete[] pixels;
	        rows=0;
                cols=0;
		f2.close();
		return 0;
	}
//empties the file once more and moves the seekg to the beginning
	f2.clear();
        f2.seekg (0, f2.beg);
//total size=cols*lines if we devide the total size(n) by number of lines we get the number of columns
	cols = n/line;
	rows = line;
//pixels should be NULL when we're trying to store the image in it
	if(pixels != NULL)
		delete[] pixels;
	pixels = new uint8_t[cols*rows];
	for (i=0; i<n; i++){
		f2 >> in;
		pixels[i] = in;
	}
	f2.close();
	return 0;
 }
