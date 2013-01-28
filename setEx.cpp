/*
 * setEx.cpp
 *
 *  Created on: Oct 8, 2011
 *      Author: andrewdunn
 */

//http://www.cplusplus.com/reference/stl/set/find/
// set::find
#include <iostream>
#include <set>
using namespace std;

int main ()
{
  set<int> myset;
  set<int>::iterator it;

  // set some initial values:
  for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

  it=myset.find(80);
  if (it != myset.end())myset.erase (it);
  myset.erase (myset.find(40));

  cout << "myset contains:";
  for (it=myset.begin(); it!=myset.end(); it++)
    cout << " " << *it;
  cout << endl;

  return 0;
}
