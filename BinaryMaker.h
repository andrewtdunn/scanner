/*
 * BinaryMaker.h
 *
 *  Created on: Oct 10, 2011
 *      Author: andrewdunn
 */

#ifndef BINARYMAKER_H_
#define BINARYMAKER_H_

#include "libs.h"

#include "vision_utilities.h"

class BinaryMaker {
	int threshold;
	const char *outputFile;

public:
	Image * im;
	BinaryMaker();
	virtual ~BinaryMaker();
	void makeBinary (Image * im);
};

#endif /* BINARYMAKER_H_ */
