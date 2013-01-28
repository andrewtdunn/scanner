/*
 * FoundObject.cpp
 *
 *  Created on: Sep 29, 2011
 *      Author: andrewdunn
 */

#include "FoundObject.h"

FoundObject::FoundObject() {
	// TODO Auto-generated constructor stub

}

FoundObject::~FoundObject() {
	// TODO Auto-generated destructor stub
}


void FoundObject::setXPos(int $xPos){
	xPos= $xPos;
}

int FoundObject::getXPos(){
	return xPos;
}

void FoundObject::setYPos(int $yPos){
	yPos= $yPos;
}

int FoundObject::getYPos(){
	return yPos;
}

void FoundObject::setLabel(int $label){
	label= $label;
}

int FoundObject::getLabel(){
	return label;
}

void FoundObject::setArea(int $area){
	area = $area;
}

int FoundObject::getArea(){
	return area;
}


void FoundObject::setEMin(float $eMin){
	eMin = $eMin;
}

float FoundObject::getEMin(){
	return eMin;
}
void FoundObject::setOrientation(float $orientation){
	orientation = $orientation;
}
float FoundObject::getOrientation(){
	return orientation;
}
void FoundObject::setRoundness(float $roundness){
	roundness = $roundness;
}
float FoundObject::getRoundness(){
	return roundness;
}

void FoundObject::setRotation(float $rotation){
	rotation = $rotation;
}
float FoundObject::getRotation(){
	return rotation;
}














