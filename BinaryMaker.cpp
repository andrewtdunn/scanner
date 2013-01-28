/*
 * BinaryMaker.cpp
 *
 *  Created on: Oct 10, 2011
 *      Author: andrewdunn
 */

#include "BinaryMaker.h"

BinaryMaker::BinaryMaker() {
	// TODO Auto-generated constructor stub
	threshold = 138;
}

BinaryMaker::~BinaryMaker() {
	// TODO Auto-generated destructor stub
}

void BinaryMaker::makeBinary (Image * im)
{
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
	writeImage(im, "test.pgm");
}
