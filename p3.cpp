/*
 * p3.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: andrewdunn
 *
 *   input labeled images output database of properties
 */


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "vision_utilities.h"
#include "FoundObject.h"



using namespace std;


vector<FoundObject> objs;

int numCols, numRows, numObjs;
int lineSize = 40;


void getCenter(Image * im)
{
	cout << "describe objects() " << endl;
	numCols =  getNCols(im);
	numRows =  getNRows(im);
	int xPos, yPos;
	int  xSum, ySum, area, a, b, c;

	// label 0 is the background
	for (int k=1; k <= numObjs; k++)
	{
		// why do i have to do this
		xPos = yPos = xSum = ySum = area = a = b= c= 0;

		cout << endl << "matching label " << k << endl << endl;

		FoundObject obj;
		// find x,y pos

		// first label is for zero
		int label = k;
		obj.setLabel(label);

		// find xSum ,ySum, area, a, b, c
		int i,j;
		for (i = 0; i < numRows; i++)
		{
			for (j=0; j < numCols; j++)
			{
				int pixLabel = getPixel(im, i, j);
				if (pixLabel == label)
				{

					// b(x,y) always equal to 1

					// xsum += column num
					xSum += j ;
					// ysum += row num
					ySum += i ;
					area ++;
				}


			}
		}
		cout << "object: " << k << endl;
		cout << "area: " << area<< endl;
		cout << "xSum: " << xSum << endl;
		cout << "ySum: " << ySum << endl;
		xPos = xSum/area;
		yPos = ySum/area;
		cout << "x: " << xPos << endl;
		cout << "y: " << yPos << endl;
		obj.setXPos(xPos);
		obj.setYPos(yPos);
		obj.setArea(area);

		objs.push_back(obj);
	}


}

float convertRadiansToDegrees(float radians)
{
	return radians * 180/PI;
}

void getRotation(Image * im)
{
	float a, b, c;
	for (int k=0; k < objs.size(); k ++)
	{

		int objX = objs[k].getXPos();
		int objY = objs[k].getYPos();
		int ctrX = objX + 10;
		int ctrY = objY + 10;
		int a = 0;
		int b = 0;
		int c = 0;
		int label = k+1;


		//construct axis
//		line(im, ctrY-10, ctrX, ctrY+10, ctrX, numObjs+1);
//		line(im, ctrY, ctrX - 10, ctrY, ctrX+10, numObjs+1);

		// find a,b,c
		// find xSum ,ySum, area, a, b, c
		int i,j;
		for (i = 0; i < numRows; i++)
		{

			for (j=0; j < numCols; j++)
			{
				int pixLabel = getPixel(im, i, j);
				if (pixLabel == label)
				{
					a += (j - objX) * (j - objX);
					b += 2 * (j - objX) * (i - objY);
					c += (i - objY) * (i - objY);
				}
			}

		}

		cout << endl << "Object "<< k +1  << " Rotation:" << endl;
		cout << " a: " << a << endl;
		cout << " b: " << b << endl;
		cout << " c: " << c << endl;


		float rot, rot2;
		
		rot  = rot2 = 0;
		float orientation;
		orientation = 0;
		int x1,y1,x2,y2;
		x1 = y1 = x2 = y2 = 0;
		rot = (atan2(b, a-c))/2;
		rot2  = rot + (PI/2);
		orientation = PI/2 - rot;

		x1 = sin(rot) * lineSize;
		y1 = cos(rot) * lineSize;
		
		cout << "x1: " << x1 << endl;
		cout << "71: " << y1 << endl << endl;
		line(im, objY + y1, objX + x1, objY - y1, objX - x1, numObjs+1);
		
		cout << "The rotation is " <<  convertRadiansToDegrees(rot) << " degrees." <<endl;
		
		float eMin, eMax; // max and min moment of inertia
		float roundness = 0; 
		eMin = eMax = 0;
		eMin =  a * sin(rot) * sin(rot) - b * sin(rot) * cos(rot) + c * cos (rot) * cos (rot);
		eMax =  a * sin(rot2) * sin(rot2) - b * sin(rot2) * cos(rot2) + c * cos (rot2) * cos (rot2);
		roundness = eMin/eMax;
		
		cout << "Emin: " << eMin << endl;
		cout << "Emax: " << eMax << endl;
		cout << "Roundness: " << roundness << endl; 
		
		objs[k].setOrientation(orientation);
		objs[k].setRoundness(roundness);
		objs[k].setEMin(eMin);
	}
}






void writeDatabase(const char *outputFile)
{
	cout << endl << "writing database" << endl;

	ofstream database;
	database.open (outputFile);
	/*
	database << " * * OBJECTS DATABASE * * " << endl;
	database << " There are " << numObjs << " objects." << endl << endl;
	database << "Label\t" << "x pos\t" << "y pos\t" << "eMin\t\t" << "orientation\t" << "roundness" << endl << endl; 
	*/
	for (int i = 0; i < numObjs; i++)
	{
		FoundObject obj = objs[i];
		/*
		//prettier version
		database << obj.getLabel() <<  "\t"
				 << obj.getXPos() << "\t"
				 << obj.getYPos() << "\t"
				 <<fixed << showpoint << setprecision(2) << obj.getEMin() << "\t"
				 << fixed << showpoint << setprecision(2) << obj.getOrientation() << "\t\t"
				 << fixed << showpoint << setprecision(2) << obj.getRoundness() <<
				 endl;
		*/
		database << obj.getLabel() <<  " "
				 << obj.getXPos() << " "
				 << obj.getYPos() << " "
				 <<fixed << showpoint << setprecision(2) << obj.getEMin() << " "
				 << fixed << showpoint << setprecision(2) << obj.getOrientation() << " "
				 << fixed << showpoint << setprecision(2) << obj.getRoundness() <<
				 endl;
	}

	database.close();
}

void writeImageFile(Image * im,const char * outputImage)
{

	for (int i = 0; i < objs.size(); i ++)
	{
		// add center dot
		setPixel(im, objs[i].getYPos(), 	objs[i].getXPos(), objs.size()+1);
		setPixel(im, objs[i].getYPos() +1, 	objs[i].getXPos(), objs.size()+1);
		setPixel(im, objs[i].getYPos() -1, 	objs[i].getXPos(), objs.size()+1);
		setPixel(im, objs[i].getYPos(), 	objs[i].getXPos() +1, objs.size()+1);
		setPixel(im, objs[i].getYPos(), 	objs[i].getXPos() -1, objs.size()+1);
		setPixel(im, objs[i].getYPos() +1, 	objs[i].getXPos() +1, objs.size()+1);
		setPixel(im, objs[i].getYPos() -1, 	objs[i].getXPos() +1, objs.size()+1);
		setPixel(im, objs[i].getYPos() +1, 	objs[i].getXPos() -1, objs.size()+1);
		setPixel(im, objs[i].getYPos() -1, 	objs[i].getXPos() -1, objs.size()+1);


		// draw line segment for orientation
	}
	// +1 for lines
	setColors(im, objs.size() + 1);

	cout << "writing " << outputImage << endl;
	writeImage(im, outputImage);


}







int main(int argc, char *argv[])
{

	// put command line args into variables
	const char *inputImage = argv[1];
	const char *databaseName = argv[2];
	const char *outputImage =argv[3];

	cout << endl;
	cout << "input image: " << inputImage << endl;
	cout << "database name: " << databaseName << endl;
	cout << "output image: " << outputImage << endl;
	cout << endl;

	// use Image struct
	Image newImage;
	Image * im;
	im = &newImage;

	// read image, get # of columns and rows
	readImage(im, inputImage);
	numObjs = getColors(im);
	cout << endl << "Main:: there are " << numObjs << " objects." << endl << endl;

	getCenter(im);
	getRotation(im);
	writeDatabase(databaseName);
	writeImageFile(im, outputImage);


	return 0;
}







