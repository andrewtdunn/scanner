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

#define ARRAY_SIZE 500
#define NUM_ROWS 531
#define NUM_COLS 681


using namespace std;

int  equivsArray[ARRAY_SIZE][ARRAY_SIZE];
vector < vector<int> > equivs;
vector<int> nonClashingLabels;

int currentLabel = 0;
int totalLabels;


int numRows, numCols;






void printSet(int setA[], int setName)
{
	cout << setName << ": ";

	if (setA[0] == 0)
	{
		cout << "empty set" << endl;
	}
	else
	{
		int index = 0;
		while (setA[index] != 0)
		{
			cout << setA[index] << " ";
			index ++;
		}
	}
	cout << endl;
}


void printSets()
{
	cout << "All Sets: " << endl;
	int i=0;
	while (equivsArray[i][0] != 0)
	{
		printSet(equivsArray[i],i);
		i++;
	}
	cout << endl << endl;
}


void newSet(int a, int b)
{
	int mainIndex = 0;
	while (equivsArray[mainIndex][0] != 0){mainIndex++;}
	equivsArray[mainIndex][0] = a;
	equivsArray[mainIndex][1] = b;
	printSets();
}



void mergeSets(int keepSet[], int discardSet[])
{
	// merge sets
	cout << "merging.. " << endl;
	printSet(keepSet, 1);
	printSet(discardSet, 2);
	int keepIndex=0;
	while (keepSet[keepIndex]!=0){keepIndex++;}
	int discardIndex = 0;
	while (discardSet[discardIndex]!= 0 )
	{
	//	cout << "keepIndex: " << keepIndex << endl;
	//	cout << "replacing " << keepSet[keepIndex] << " with " << discardSet[discardIndex] << endl;
		keepSet[keepIndex] = discardSet[discardIndex];
		keepIndex ++;
		discardIndex ++;
	}
	cout << "deleting old set" << endl;
	// fill old set with zeroes
	for (int index=0; index < 12; index++)
	{
		discardSet[index] = 0;
	}
	//printSet(discardSet, 2);


}



void addEquivalency(int aVal, int bVal)
{

//	cout <<  "addEquiv: " << aVal << " " << bVal<< endl;
	// use a set
	// http://www.cplusplus.com/reference/stl/set/find/

	bool matchFound = false;
	int homeKey = -1;

	bool aValFound = false;
	bool bValFound = false;
	for (int outerIndex=0; outerIndex < ARRAY_SIZE; outerIndex ++)
	{
        //cout << outerIndex << endl;
		// iterate through sub arrays
		aValFound = bValFound = false;
		for (int innerIndex=0; innerIndex < ARRAY_SIZE; innerIndex ++)
		{
			if (equivsArray[outerIndex][innerIndex] == aVal)
				{aValFound = true; }
			if (equivsArray[outerIndex][innerIndex] == bVal )
				{bValFound = true; }
		} // end inner iteration

		// if a match has been found in a previous set
		if (matchFound && (aValFound || bValFound))
		{
			mergeSets(equivsArray[homeKey], equivsArray[outerIndex]);
		}
		else
		{
			// if aVal is in the array but not bVal
			if(aValFound && !bValFound)
			{
				// add bVal to this array
				int addedIndex = 0;
				while (equivsArray[outerIndex][addedIndex] != 0) {addedIndex++; if (addedIndex==ARRAY_SIZE){break;}}
				equivsArray[outerIndex][addedIndex] =bVal;

				matchFound = true;
				homeKey = outerIndex;
			}
			// if bVal is found but not aVal
			else if (bValFound && !aValFound)
			{

				// add bVal to this array
				int addedIndex = 0;
				while (equivsArray[outerIndex][addedIndex] != 0) {addedIndex++; if (addedIndex==ARRAY_SIZE){break;}}
				equivsArray[outerIndex][addedIndex] =aVal;

				matchFound = true;
				homeKey = outerIndex;

			}
			// if both bVal and aVal are found
			else if (bValFound && aValFound)
			{
			//	cout << ("both found") << endl;
				matchFound = true;
				homeKey = outerIndex;

				// nothing to add;
			}

		}

	} // end outer iteration


	if (!matchFound)
	{
	//	cout << "no match, new equivalence set" << endl;
		newSet(aVal, bVal);
	}


	//printSets();
}



// sequential labeling algorithm
void scanImage(int storageArray[NUM_ROWS][NUM_COLS])
{
	cout << "scanning image... " << endl;
	cout << "rows: " << numRows << endl;
	cout << "cols: " << numCols << endl;
	
	int i, j;
	// iterate through pixels and reassign brightness based on the threshold value
	for (i=0; i < numRows; i++)
	{
		for (j=0; j < numCols; j++)
		{

			int aLabel = storageArray[i][j];
			//1 aLabel = 0 (bkgd)
			// .. if A is black
			if (aLabel == 0)
			{
				// do nothing
			}
			else
			{


				// x and y  are reversed!! it
				// is row i and column j
				// so column is j = x
				// and row is i = y
				int dLabel = storageArray[i-1][ j-1];

				//2 if D has been labeled
				if (dLabel != 0)
				{
					//setPixel(im, i, j, dLabel);
					storageArray[i][j] = dLabel;
				}

				else
				{
					// y-1 , x
					int bLabel = storageArray[i-1][j];
					int cLabel = storageArray[i][j-1];
					//3 if b has been labeled but not c
					if (bLabel != 0 && cLabel == 0)
					{
						storageArray[i][j] = bLabel;
					}
					//4 if neither b nor c is labeled
					else if (bLabel == 0 && cLabel == 0 )
					{
						// make a new label for a
						currentLabel ++;
					//	cout<< "new Label: " << currentLabel<< endl;
						storageArray[i][j] = currentLabel;
					}

					//5 if c has been labeled but not b
					else if (cLabel != 0 && bLabel == 0 )
					{
						// set a label to c
						storageArray[i][j] = cLabel;
					}
					//6 if b and c has been labeled and are equal
					else if ((bLabel !=0 && cLabel != 0) && bLabel == cLabel)
					{
						// label a with b
						storageArray[i][j] = bLabel;
					}
					// 7
					// remaining possibility is that b and c
					// are both labeled but not equal
					// (and d is not labelled)
					else if ((bLabel !=0 && cLabel != 0) && bLabel != cLabel )
					{
						// label a with b
						storageArray[i][j] = bLabel;
						addEquivalency(bLabel, cLabel);

					}
				}

			}
		}
	}

}



// second pass. resolve equivalencies and adjust total labels
void resolveEquivalencies(int storageArray[NUM_ROWS][NUM_COLS], Image * im)
{
	cout << "resolving .. " << endl;
	int i,j;
	i=j=0;
	for (i=0; i < numRows; i++)
	{
		for (j=0; j < numCols; j++)
		{
			int aLabel = storageArray[i][j];
			{

				for (int outerIndex = 0; outerIndex < ARRAY_SIZE; outerIndex ++)
				{
					for (int innerIndex = 0; innerIndex < ARRAY_SIZE; innerIndex ++)
					{
						if ( equivsArray[outerIndex][innerIndex] == 0 ){break;}
						//cout << i << " "<< j << " " <<outerIndex << " " << innerIndex << endl;
						if ( equivsArray[outerIndex][innerIndex] == aLabel)
						{
							setPixel(im,i,j, outerIndex + 1);

						}
					}
				}

			}
		}
	}

	printSets();
	cout << "resolution over. " << endl;
}




void getTotalLabels()
{
	int total = 0;
	while(equivsArray[total][0]!=0)
	{
		total++;
		if (total == ARRAY_SIZE){break;}
	}
	totalLabels = total;
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


	int storageArray[NUM_ROWS][NUM_COLS];

	// initialize storage array with pixel values
	for (int storeI=0; storeI<numRows; storeI ++)
	{
		for (int storeJ=0; storeJ<numCols; storeJ++)
		{
			storageArray[storeI][storeJ] = getPixel(im, storeI, storeJ);
		}
	}


	// initialize equivalence vector
	for (int outerI = 0; outerI < ARRAY_SIZE; outerI ++)
	{
		for (int innerI = 0; innerI < ARRAY_SIZE; innerI++)
			{equivsArray[outerI][innerI] = 0;}
	}



	/*
	// to test
	cout << "merging arrays" << endl;
	int coolArray[12] = {1,2,3,4, 0, 0, 0, 0, 0, 0, 0, 0};
	int dudeArray[12]= {5,6,7,8, 0, 0, 0, 0, 0, 0 , 0 ,0};
	cout << "print" << endl;
	printSet(coolArray, 1);
	printSet(dudeArray, 2);
	cout << "merge" << endl;
	mergeSets(coolArray, dudeArray);
	printSet(coolArray, 1);
	printSet(dudeArray, 2);
	*/


	// sequential labeling algorithm

	scanImage(storageArray);
	resolveEquivalencies(storageArray, im);
	getTotalLabels();
	cout << endl  << endl << "There are " << totalLabels << " objects" << endl;
	setColors(im, totalLabels);
	writeImage(im, outputFile);


	return 0;
}







