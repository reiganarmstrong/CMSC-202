//File: lab6.cpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Candy.h"
using namespace std;

void fillVector(vector<Candy> &candyList){

}

void printVectorWithoutIterator(vector<Candy> &candyList){

}

void printVectorWithIterator(vector<Candy> &candyList){
  //We will be doing more with iterators during a later lab but if you are done with everything
  //else, please try to complete this function
}

int main(){

  vector<Candy> candyList;

  fillVector(candyList);
  printVectorWithoutIterator(candyList);
  cout << endl;
  //  printVectorWithIterator(candyList); //If done with other functions, complete this one

  return 0;
}
