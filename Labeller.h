/*
 * Labeller.h
 *
 *  Created on: Oct 10, 2011
 *      Author: andrewdunn
 */

#ifndef LABELLER_H_
#define LABELLER_H_
#include "vision_utilities.h"
#include "libs.h"


using namespace std;

class Labeller {
	int currentLabel;
	int totalLabels;
	int numRows, numCols;
	vector < vector <int> > equivs;

private:
	void addEquivalence(int aVal, int bVal);

public:
	Labeller();
	virtual ~Labeller();
	void scanImage(Image * im);
	void listEquivalences();
	void resolveEquivalences(Image * im);

};

#endif /* LABELLER_H_ */
