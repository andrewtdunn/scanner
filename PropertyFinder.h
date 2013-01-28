/*
 * PropertyFinder.h
 *
 *  Created on: Oct 10, 2011
 *      Author: andrewdunn
 */

#ifndef PROPERTYFINDER_H_
#define PROPERTYFINDER_H_

#include "libs.h"
#include "vision_utilities.h"
#include "FoundObject.h"

class PropertyFinder {
	int numCols, numRows, numObjs;
	int lineSize;
	vector < FoundObject > soughtObjs;
	vector < FoundObject > objs;
	int inputObjsSize;
	float threshold;

private:
	float convertRadiansToDegrees(float radians);


public:
	PropertyFinder( vector < FoundObject > $objs);
	virtual ~PropertyFinder();
	void findCenters(Image *);
	void findRotation(Image *);
	void compareAgainstDatabase(Image * im);


};

#endif /* PROPERTYFINDER_H_ */
