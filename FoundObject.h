/*
 * FoundObject.h
 *
 *  Created on: Sep 29, 2011
 *      Author: andrewdunn
 *
 *      value object for holding image properties
 */

#ifndef FOUNDOBJECT_H_
#define FOUNDOBJECT_H_

class FoundObject
{
	int xPos,yPos,label,area;
	float eMin, orientation, roundness, rotation;


public:
	FoundObject();
	virtual ~FoundObject();
	void setXPos(int $xPos);
	int getXPos();
	void setYPos(int $yPos);
	int getYPos();
	void setLabel(int $label);
	int getLabel();
	void setArea(int $area);
	int getArea();
	void setEMin(float $eMin);
	float getEMin();
	void setOrientation(float $orientation);
	float getOrientation();
	void setRoundness(float $roundness);
	float getRoundness();
	void setRotation(float $rotation);
	float getRotation();
};

#endif /* FOUNDOBJECT_H_ */
