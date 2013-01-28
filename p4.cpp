/*
 * p4.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: andrewdunn
 *
 * 	compare labeled images against items in a database
 */


#include "libs.h"

#include "FoundObject.h"
#include "PropertyFinder.h"

using namespace std;

// objects read from data file
vector < FoundObject > soughtObjects;

int main(int argc, char *argv[])
{

	// put command line args into variables
	const char *inputImage = argv[1];
	const char *databaseName = argv[2];
	const char *outputImage =argv[3];

	cout << "input labeled image: " << inputImage << endl;
	cout << "input database name: " << databaseName << endl;
	cout << "output image: " << outputImage << endl << endl << endl;
	
	
	
	
	// read database file
	string line;
	ifstream inputFile (databaseName);
	char * pch;
	if (inputFile.is_open())
	{
		while (inputFile.good())
		{
			
			
			
			
			
			
			getline(inputFile,line);
		//	string s("Somewhere down the road");
		    istringstream iss(line);
			int i = 0;
		    do
		    {
				
		        	string sub;
		        	iss >> sub;
					string sub2;
					iss >> sub2;
					string sub3;
		        	iss >> sub3;
					string sub4;
					iss >> sub4;
					string sub5;
		        	iss >> sub5;
					string sub6;
		        	iss >> sub6;
				
				if (atof(sub.c_str()) != 0)
		        {
					FoundObject fob;
				//	cout << "EMin: " << atof(sub4.c_str()) << endl;
				//	cout << "roundness: " << atof(sub6.c_str()) << endl << endl;
					fob.setEMin(atof(sub4.c_str()) );
					fob.setRoundness(atof(sub6.c_str()) );
					soughtObjects.push_back(fob);
				}
		    } while (iss);
		
		
		}
		inputFile.close();
	}
	else cout << "Unable to open file";
	
	cout << "Looking for objects: " << endl;
	
	// should techinically be done with an interator
	for (int i = 0; i < soughtObjects.size(); i++)
	{
		cout << i + 1 << " with EMin " << soughtObjects[i].getEMin() << " and roundness " << soughtObjects[i].getRoundness() << endl;
	}
	
	
	// use Image struct
	Image newImage;
	Image * im;
	im = &newImage;
	
	readImage(im, inputImage);
	

	PropertyFinder proper(soughtObjects);
	proper.findCenters(im);
	proper.findRotation(im);
	proper.compareAgainstDatabase(im);
	
	writeImage(im, outputImage);



	return 0;
}


