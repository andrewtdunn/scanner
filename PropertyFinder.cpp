/*
 * PropertyFinder.cpp
 *
 *  Created on: Oct 10, 2011
 *      Author: andrewdunn
 */

#include "PropertyFinder.h"

#define MASS_THRESHOLD 550000
#define ROUND_THRESHOLD	0.05

PropertyFinder::PropertyFinder( vector < FoundObject > $soughtObjs) {
	// TODO Auto-generated constructor stub
	lineSize = 40;
	soughtObjs = $soughtObjs;
	threshold = 0;

}

PropertyFinder::~PropertyFinder() {
	// TODO Auto-generated destructor stub
}

float PropertyFinder::convertRadiansToDegrees(float radians)
{
	return radians * 180/PI;
}




/**
 * iterate through foughts objects and compare them against the EMin and
 * roundness of the sought objects. if they are outside of the
 * defined threshold - erase from found objects
 */
void PropertyFinder::compareAgainstDatabase(Image * im)
{
	int i, j, matchFound;

	int objFoundNum = 0;

	cout << "compare againstDatabase() objs elements: " << objs.size() << endl;
	for (i = 0; i < objs.size(); i++)
	{
		matchFound = 0;
		for (j=0; j < soughtObjs.size(); j++)
		{
			float roundnessDifference = 0.0;
			float massDiff = 0.0;
			// if not within the two thresholds, erase found object
			roundnessDifference = abs (soughtObjs[j].getRoundness() - objs[i].getRoundness());
			massDiff = abs (soughtObjs[j].getEMin() - objs[i].getEMin());
			if (roundnessDifference <= ROUND_THRESHOLD && massDiff <= MASS_THRESHOLD) cout << "* * * MATCH * * *" << endl;
			cout << "Found Object: " << i+1 << " Sought Object: " << j + 1 << endl;
			cout << " Roundness Difference: " << roundnessDifference << endl;
			cout << " Emin Diff " << massDiff << endl << endl;


			if (roundnessDifference <= ROUND_THRESHOLD && massDiff <= MASS_THRESHOLD)
			{


				setPixel(im, objs[i].getYPos(), 	objs[i].getXPos(), objs.size()+1);
				setPixel(im, objs[i].getYPos() +1, 	objs[i].getXPos(), objs.size()+1);
				setPixel(im, objs[i].getYPos() -1, 	objs[i].getXPos(), objs.size()+1);
				setPixel(im, objs[i].getYPos(), 	objs[i].getXPos() +1, objs.size()+1);
				setPixel(im, objs[i].getYPos(), 	objs[i].getXPos() -1, objs.size()+1);
				setPixel(im, objs[i].getYPos() +1, 	objs[i].getXPos() +1, objs.size()+1);
				setPixel(im, objs[i].getYPos() -1, 	objs[i].getXPos() +1, objs.size()+1);
				setPixel(im, objs[i].getYPos() +1, 	objs[i].getXPos() -1, objs.size()+1);
				setPixel(im, objs[i].getYPos() -1, 	objs[i].getXPos() -1, objs.size()+1);



				cout << "drawing .." << endl << endl;
				int x1, y1, objY, objX;

				x1 = y1 = objY = objX = 0;
				objX = objs[i].getXPos();
				objY = objs[i].getYPos();
				float rot = objs[i].getRotation();
				// draw;
				x1 = sin(rot) * lineSize;
				y1 = cos(rot) * lineSize;

				line(im, objY + y1, objX + x1, objY - y1, objX - x1, numObjs+1);



			}
		} // next sought object

		cout << endl << endl;
	} // next object

	cout << objs.size() << " objects found" << endl;

}


void PropertyFinder::findCenters(Image * im)
{
	numObjs = getColors(im);
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
	}
}

void PropertyFinder::findRotation(Image * im)
{
	for (int k=0; k < objs.size(); k ++)
	{

		int objX = objs[k].getXPos();
		int objY = objs[k].getYPos();
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
		objs[k].setRotation(rot);

	}
}

