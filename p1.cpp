/*
 * p1.cpp
 *
 *  Created on: Sep 21, 2011
 *      Author: andrewdunn
 *
 *  given a grayscale image, convert to binary
 */

#include <iostream>
#include "vision_utilities.h"

using namespace std;


int main(int argc, char *argv[])
{

	// put command line args into variables
	const char *inputFile = argv[1];
	const char *outputFile =argv[3];
	int threshold = atoi(argv[2]);

	cout << "input file: " << inputFile << endl;
	cout << "threshold: " << threshold << endl;
	cout << "output file: " << outputFile << endl;

	// use Image struct
	Image inImage;
	Image * im;
	im = &inImage;

	// read image, get # of cols and rows
	readImage(im, inputFile);
	int numCols =  getNCols(im);
	int numRows =  getNRows(im);
	int i, j;
	// iterate through pixels and reassign brightness based on the threshold value
	for (i=0; i < numRows; i++)
		for (j=0; j < numCols; j++)
		{
			int grayLevel = getPixel(im, i, j);
			int newGrayLevel = (grayLevel > threshold) ? 1: 0;
			setPixel(im, i, j, newGrayLevel);
		};


	setColors(im, 1);
	writeImage(im, outputFile);

	return 0;
}
