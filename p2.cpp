/*
 * p2.cpp
 *
 *  Created on: Sep 25, 2011
 *      Author: andrewdunn
 *
 *   implementation of sequential labeling algorithm
 *   given an input file out put an image file with each object
 *   labeled with a different shade of gray
 */


#include <iostream>
#include <vector>
#include <set>
#include "vision_utilities.h"

vector <vector <int> > grid;
vector <vector <int> > comparisonGrid;



using namespace std;

vector < vector<int> > equivs, storageVector;
vector<int> nonClashingLabels;

int currentLabel = 0;
int totalLabels;


int numRows, numCols;

void listEquivalencies()
{
	cout << "listEquivalencies() " << equivs.size()<< endl;
	int i,j;
	if (equivs.size() > 0)
	{

		for (i=0; i < equivs.size(); i ++)
		{
			cout << equivs[i][0] << "* ";
			for (j=0; j < equivs[i].size(); j++)
			{
				cout << equivs[i][j] << " ";
			}
			cout << endl;
		}
	}
}


// implements a disjoint set with two operations: merge and add
void addEquivalency(int aVal, int bVal)
{



	bool matchFound = false;
	int i;
	int homeKey = -1;
	for (i = 0; i < equivs.size(); i ++)
	{
		// if aVal is in the array but not bVal
		if (find(equivs[i].begin(), equivs[i].end(), aVal) != equivs[i].end()
		&&	find(equivs[i].begin(), equivs[i].end(), bVal) == equivs[i].end())
		{
			// if a match has already been found
			if (matchFound)
			{
			//	cout << "double match" << endl;
				// merge vectors
				equivs[homeKey].insert(equivs[homeKey].end(), equivs[i].begin(), equivs[i].end());
				equivs.erase(equivs.begin() + i);
				break;
			}

			// set matchFound to true and let this be the first finding
			// add to current vector
			matchFound = true;
			homeKey = i;
		//	cout << "match" << endl;
			equivs[i].push_back(bVal);
		}
		else
		// if bVal is found but not aVal
		if (find(equivs[i].begin(), equivs[i].end(), aVal) == equivs[i].end()
		&&	find(equivs[i].begin(), equivs[i].end(), bVal) != equivs[i].end())
		{
			// if a match has already been found
			if (matchFound)
			{
			//	cout << "double match" << endl;
				// merge vectors
				equivs[homeKey].insert(equivs[homeKey].end(), equivs[i].begin(), equivs[i].end());
				equivs.erase(equivs.begin() + i);
				break;
			}
			// set matchFound to true and let this be the first finding
			// add to current vector
			matchFound = true;
			homeKey = i;
		//	cout << "match" << endl;
			equivs[i].push_back(aVal);
		}
		else
		// if both aVal and bVal are found
		if (find(equivs[i].begin(), equivs[i].end(), aVal) != equivs[i].end()
		&&	find(equivs[i].begin(), equivs[i].end(), bVal) != equivs[i].end())
		{
			// if a match has already been found
			if (matchFound)
			{
			//	cout << "double match" << endl;
				// merge vectors
				equivs[homeKey].insert(equivs[homeKey].end(), equivs[i].begin(), equivs[i].end());
				equivs.erase(equivs.begin() + i);
				break;
			}
			// set matchFound to true and let this be the first finding
			// add to current vector
			matchFound = true;
			homeKey = i;
		//	cout << "match" << endl;
		}
		else
		// if neither aVal or bVal is found
		{
			// do nothing
		}
	}


	if (!matchFound){
		// create new vector
	//	cout << "no match" << endl;
		vector <int> newEquiv;
		newEquiv.push_back(aVal);
		newEquiv.push_back(bVal);
		equivs.push_back(newEquiv);
	}
//	listEquivalencies();
}



// sequential labeling algorithm
void scanImage()
{
	
	int i, j;
	// iterate through pixels and reassign brightness based on the threshold value
	for (i=0; i < numRows; i++)
	{
		for (j=0; j < numCols; j++)
		{

			int aLabel = storageVector[i][j];
			//1 aLabel = 0 (bkgd)
			// .. if A is black
			if (aLabel == 0)
			{
				// do nothing
			}
			else
			{

			//	cout << "object detected" << endl;

				// x and y  are reversed!! it
				// is row i and column j
				// so column is j = x
				// and row is i = y
				//int dLabel = getPixel(im, i-1, j-1);
				int dLabel = storageVector[i-1][j-1];

				//2 if D has been labeled
				if (dLabel != 0)
				{
					// copy that label and move on

					//setPixel(im, i, j, dLabel);
					storageVector[i][j]=dLabel;
					//labels[i][j] = dVal;
				}

				else
				{
					// y-1 , x
					int bLabel = storageVector[i-1][j];// getPixel(im, i-1, j);
					int cLabel = storageVector[i][j-1];
					//3 if b has been labeled but not c
					if (bLabel != 0 && cLabel == 0)
					{
						//setPixel(im,i,j,bLabel);
						storageVector[i][j]=bLabel;
						//labels[i][j] = bVal;
					}
					//4 if neither b nor c is labeled
					else if (bLabel == 0 && cLabel == 0 )
					{
						// make a new label for a
						currentLabel ++;
						storageVector[i][j]=currentLabel;
					}

					//5 if c has been labeled but not b
					else if (cLabel != 0 && bLabel == 0 )
					{
						// set a label to c
						storageVector[i][j]=cLabel;
					}
					//6 if b and c has been labeled and are equal
					else if ((bLabel !=0 && cLabel != 0) && bLabel == cLabel)
					{
						// label a with b
						storageVector[i][j]=dLabel;
					}
					// 7
					// remaining possibility is that b and c
					// are both labeled but not equal
					// (and d is not labelled)
					else if ((bLabel !=0 && cLabel != 0) && bLabel != cLabel )
					{
						// label a with b
						storageVector[i][j]=bLabel;
						addEquivalency(bLabel, cLabel);

					}
				}

			}
		}
	}

}






// second pass. resolve equivalencies and adjust total labels
void resolveEquivalencies(Image * im)
{
	cout << "resolveEquivalencies() ";
	int i,j,k;
	for (i=0; i < numRows; i++)
	{
		for (j=0; j < numCols; j++)
		{
			int aLabel = storageVector[i][j];
			{
				// loop through arrays - look for match

				for (k=0; k<equivs.size(); k++)
				{
					if (find(equivs[k].begin(), equivs[k].end(), aLabel) != equivs[k].end())
					{
						storageVector[i][j] = k+1;
					}
				}

			}
		}
	}
	cout << "resolved equivalent labels: " << equivs.size()-2 << endl;
}


void loadImage(Image * im)
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j=0; j < numCols; j++)
		{
			setPixel(im, i, j, storageVector[i][j]);
		}
	}
}










int main(int argc, char *argv[])
{

	// put command line args into variables
	const char *inputFile = argv[1];
	const char *outputFile =argv[2];

	cout << endl << "input file: " << inputFile << endl;
	cout << "output file: " << outputFile << endl << endl;

	// use Image struct
	Image newImage;
	Image * im;
	im = &newImage;



	// read image, get # of columns and rows
	readImage(im, inputFile);
	numCols =  getNCols(im);
	numRows =  getNRows(im);


	cout << "initializing" << endl;

	// initialize labels vector


	for (int vSizeY = 0; vSizeY < numRows; vSizeY ++)
	{
		vector < int > newVector;
		for (int vSizeX = 0; vSizeX < numCols; vSizeX++)
		{
			newVector.push_back(getPixel(im, vSizeY, vSizeX));
		}
		storageVector.push_back(newVector);
	}
	cout << "initialized" << endl;




	// sequential labeling algorithm

	scanImage();

//	listEquivalencies();
	resolveEquivalencies(im);
 //	listEquivalencies();
	cout << endl  << endl << "There are " << equivs.size() << " objects" << endl;
	loadImage(im);
	setColors(im, equivs.size());
	writeImage(im, outputFile);

	return 0;
}







