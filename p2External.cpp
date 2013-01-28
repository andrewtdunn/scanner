/*
 * p2.cpp
 *
 *  Created on: Oct 10, 2011
 *      Author: andrewdunn
 *
 *      Implementation of sequential labeling algorithm -
 *      Given an input file output an image with each object
 *      labeled by a different shade of gray.
 */

#include <iostream>
#include <vector>
#include "vision_utilities.h"
#include "DisjointSets.h"

using namespace std;


int currentLabel = 0;




int numRows, numCols;


/**
 * returns a vector of Labels in a disjoint set
 *
 */
vector <int> getLabels(DisjointSets * s)
{
	vector <int> currElements;
	for (int i = 0; i < s->NumElements(); ++i)
	{
		if (find (currElements.begin(), currElements.end(), s->FindSet(i))
				== currElements.end())
		{
			currElements.push_back(s->FindSet(i));
		}
	}
	return currElements;
}


/*
 * set cannot handle over 255 elements. if this occurs, find elements
 * in current set, copy into a vector. push elements in the vector
 * into a new disjoint set, reassign pointer.
 *
 */
void expandSet(DisjointSets** s)
{
	DisjointSets * newPointer = NULL;
	vector <int> currElements = getLabels(*s);
	cout << "expandSet()" << currElements.size() << endl;
	newPointer = new DisjointSets(1);
	for (vector<int>::iterator it = currElements.begin(); it!=currElements.end(); ++it)
	{
	    cout << distance(currElements.begin(), it) << " "<< *it << endl;
	    newPointer->AddElements(*it);
	}



	s = &newPointer;
}



void printElementSets(DisjointSets * s)
{

	for (int i = 0; i < s->NumElements(); ++i)
		cout << s->FindSet(i) << "  ";
	cout << endl;
}

// sequential labeling algorithm
void scanImage(Image * im, DisjointSets * s)
{

	bool doubled = false;
	cout << "scanImage()" << endl;
	int i, j;
	// iterate through pixels left-right, top to bottom
	for (i=0; i < numRows; i++)
	{
		for (j=0; j < numCols; j++)
		{

			if (s->NumElements() ==  255 && !doubled)
			{

				expandSet(&s);
				doubled = true;

				//printElementSets(s);
				cout << "elements: " << s->NumElements() <<endl;
				cout << "size: " << s->NumSets() << endl <<endl;

				cout << s->NumElements() << endl;

			}

			int aLabel = getPixel(im,i,j);
			// case 1 aLabel = 0 (background)
			if (aLabel == 0)
			{
				// do nothing
			}
			else
			{
				// x and y reversed!!
				// row i and column j
				// so column is j = x
				// and row is i=y
				int dLabel = getPixel(im, i-1,j-1);

				// case 2 if d has been labeled
				if (dLabel != 0)
				{
					// copy that label and move on
					setPixel(im, i, j, dLabel);
				}
				else
				{
					// y-1 , x
					int bLabel = getPixel(im, i-1, j);
					// y, x-1
					int cLabel = getPixel(im, i, j-1);

					// case 3
					// b has been labeled but not c
					if (bLabel != 0 && cLabel == 0)
					{
						// setLabel to b
						setPixel(im, i, j, bLabel);
					}
					// case 4
					// if neither b nor c is labeled
					else if (bLabel == 0 && cLabel == 0)
					{

						// make a new label for a
						currentLabel ++;
						setPixel(im, i, j, currentLabel);

						if (currentLabel >= 1) {s->AddElements(1);}
						/*
						printElementSets(s);
						cout << "elements: " << s->NumElements() <<endl;
						cout << "size: " << s->NumSets() << endl <<endl;
						*/
					}
					// case 5
					// if c has been labeled but not b
					else if (bLabel==0 && cLabel!=0)
					{
						// set aLabel to c
						setPixel(im, i,j, cLabel);
					}
					// case 6
					// if b and c has been labeled and are equal
					else if ((bLabel != 0 && cLabel != 0) &&
							bLabel == cLabel)
					{
						// label a with b
						// (could be c, it doesn't matter)
						setPixel(im, i, j, bLabel);
					}
					// case 7
					// remaining possibility is that b and c
					// are both labeled but not equal
					else if ((bLabel != 0 && cLabel != 0 )
						   && bLabel != cLabel)
					{
						//cout << "clash " << bLabel<<" " << cLabel << endl;
						// label a with b
						setPixel(im,i,j,bLabel);
						// add Equivalence
						s->Union(s->FindSet(bLabel),s->FindSet(cLabel));

						cout << "equivalence: " << bLabel << " " << cLabel << endl;
						printElementSets(s);
						cout << "elements: " << s->NumElements() <<endl;
						cout << "size: " << s->NumSets() << endl <<endl;

					}
					else
					{
						cout << " >>> THIS SHOULD NEVER OCCUR!! <<<" << endl;
					}
				}

			}
		}
	}
}

// second pass resolve equivalences
void resolveEquivalences(Image * im, DisjointSets * s)
{
	/*
	cout << "resolveEquivalences()" << endl;
	int i,j,k;
	for (i=0; i < numRows; i++)
	{
		for (j=0; j < numCols; j++)
		{
			int aLabel = getPixel(im, i, j);
			if (aLabel != 0)
				setPixel(im, i, j, s->FindSet(aLabel));
		}
	}
	*/

}




int main(int argc, char *argv[])
{
	// put command line args into variables
	const char *inputFile = argv[1];
	const char *outputFile = argv[2];

	cout << endl << "input file: " << inputFile << endl;
	cout << "output file: " << outputFile << endl;

	// use Image struct
	Image newImage;
	Image * im;
	im = &newImage;


	DisjointSets * setPointer = NULL;
	setPointer = new DisjointSets(1);

	// read image, get # of columns and rows
	readImage(im, inputFile);
	numCols = getNCols(im);
	numRows = getNRows(im);

	scanImage(im, setPointer);
	resolveEquivalences(im, setPointer);
	setColors(im, setPointer->NumSets());
	writeImage(im, outputFile);

	return 0;
}

