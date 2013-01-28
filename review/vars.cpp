/*
 * vars.cpp
 *
 *  Created on: Sep 22, 2011
 *      Author: andrewdunn
 */

#include <iostream>
using namespace std;

#define PI 3.14149
#define cir


int main()
{
	// declaring variables
	int a, b;
	int result;

	// process:
	a=5;
	b=2;
	a = a+ 1;
	result = a - b;

	// print out the result
	cout << result;

	string mystring;
	mystring = "\nThis is the initial string content.";
	cout << mystring << endl;

	// terminate the program:
	return 0;

}
