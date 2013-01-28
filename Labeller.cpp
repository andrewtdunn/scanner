/*
 * Labeller.cpp
 *
 *  Created on: Oct 10, 2011
 *      Author: andrewdunn
 */

#include "Labeller.h"



Labeller::Labeller() {
	// TODO Auto-generated constructor stub
	currentLabel = 0;

}

Labeller::~Labeller() {
	// TODO Auto-generated destructor stub
}

void Labeller::listEquivalences()
{
	cout << "listEquivalences(): " << endl;
	cout << equivs.size() << " equivalences" << endl;
	int i,j;
	for (i=0; i<equivs.size(); i++)
	{
		cout << equivs[i][0] << "* ";
		for (j=1; j<equivs[i].size(); j++)
		{
			cout << equivs[i][j] << " ";
		}
		cout << endl;
	}
}

void Labeller::scanImage(Image * im)
{
	numCols =  getNCols(im);
	numRows =  getNRows(im);


	int i, j;
	// iterate through pixels left-right, top to bottom
	for (i=0; i < numRows; i++)
	{
		for (j=0; j < numCols; j++)
		{
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
						// label a with b
						setPixel(im,i,j,bLabel);
						// add Equivalence
						addEquivalence(bLabel, cLabel);
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

void Labeller::resolveEquivalences(Image * im)
{
	int i,j,k;
	for (i=0; i < numRows; i++)
	{
		for (j=0; j < numCols; j++)
		{
			int aLabel = getPixel(im, i, j);
			bool matchFound = false;
			// loop through arrays looking for a match
			for (k=0; k<equivs.size(); k++)
			{
				if (find(equivs[k].begin(),
						 equivs[k].end(),
						 aLabel) != equivs[k].end())
				{
					setPixel(im, i,j, k+1);
					matchFound = true;
				}
			}

		}
	}
	
	setColors(im, equivs.size());
	writeImage(im, "test2.pgm");
}

void Labeller::addEquivalence(int aVal, int bVal)
{
	bool matchFound = false;
	int i;
	int homeKey = -1;
	for (i=0; i< equivs.size(); i++)
	{
		// if aVal is in the array but not bVal
		if (find(equivs[i].begin(), equivs[i].end(), aVal) != equivs[i].end()
		 && find(equivs[i].begin(), equivs[i].end(), bVal) == equivs[i].end())
		{
			// if a match has already been found
			if (matchFound)
			{
				// merge vectors
				equivs[homeKey].insert(equivs[homeKey].end(), equivs[i].begin(), equivs[i].end());
				equivs.erase(equivs.begin() +i);
				// is this necessary?
				break;
			}
			else
			{
				homeKey = i;


			// set matchfound to true and let this be the first finding??
			matchFound = true;
			// should this be in an else block??

			equivs[i].push_back(bVal);
			}
		}
		// if bVal is found but not aVal
		else if (find(equivs[i].begin(), equivs[i].end(), aVal) == equivs[i].end()
			 &&	find(equivs[i].begin(), equivs[i].end(), bVal) != equivs[i].end())
		{
			// if a match has already been found
			if (matchFound)
			{
				// merge vectors
				equivs[homeKey].insert(equivs[homeKey].end(), equivs[i].begin(), equivs[i].end());
				equivs.erase(equivs.begin() +i);
				// is this necessary?
				break;
			}
			else
			{
				homeKey = i;

			// set matchfound to true and let this be the first finding??
			matchFound = true;
			// should this be in an else block??

			equivs[i].push_back(aVal);
			}
		}
		// if both aVal and bVal are found
		else if (find(equivs[i].begin(), equivs[i].end(), aVal) != equivs[i].end()
			&&	find(equivs[i].begin(), equivs[i].end(), bVal) != equivs[i].end())
		{
			// if a match has already been found
			if (matchFound)
			{
				// merge vectors
				equivs[homeKey].insert(equivs[homeKey].end(), equivs[i].begin(), equivs[i].end());
				equivs.erase(equivs.begin() +i);
				// is this necessary?
				break;
			}
			else
			{
				homeKey = i;


			// set matchfound to true and let this be the first finding??
			matchFound = true;
			// should this be in an else block??
			}
		}
		// if neither aVal or bVal is found
		else
		{
			// do nothing
		}
		cout << "size of vector " << i+1 << " " << equivs[i].size() << endl;
	}

	if (!matchFound)
	{
		vector <int> newEquiv;
		newEquiv.push_back(aVal);
		newEquiv.push_back(bVal);
		equivs.push_back(newEquiv);
	}
}

