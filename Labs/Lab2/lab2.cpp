/*
 * lab2.cpp
 * This program practices C++ regarding input/output, loops, functions in C++
 */

#include <iostream>
using namespace std;

// FUNCTION PROTOYPES FOR sumOfInts() and greaterThanTen() GO HERE  *

int sumOfInts();
void greaterThanTen(int);

//*******main********
// The user should enter their desired amount of numbers, and the program should
// display the final value after the operations, as well as if the total is
// greater than ten or not. This logic must be implemented in one line. This
// means that the main() function can have ONE statement (and the return 0).
// Implement main here:

int main() {
  greaterThanTen(sumOfInts());
  return 0;
}

//******sumOfInts*****
// The user should be prompted to enter how many integers they would like to add
// together Afterwards, the user should enter values until the number of
// specified integers is reached Print and return the sum

// Precondition: None
// Postcondition: Returns the sum of the integers inputted by the user.
int sumOfInts() {
  int numInt = 0;
  int sumOfInts = 0;
  int nextInt = 0;
  cout << "How many integers would you like to add together? ";
  cin >> numInt;
  for (int i = numInt; i > 0; i--) {
    nextInt = 0;
    cout << "Enter an integer: ";
    cin >> nextInt;
    sumOfInts += nextInt;
  }
  cout << "Sum: " << sumOfInts << endl;
  return sumOfInts;
}

//******greaterThanTen*********
// 1 parameter, determine if the passed in number is greater than 10
// Print if the value is greater or not greater than ten

// Precondition: An integer x is given.
// Postcondition: Console text stating wether or not x is greater than 10.
void greaterThanTen(int x) {
  if (x > 10) {
    cout << x << " is greater than 10!";
  } else {
    cout << x << " is not greater than 10!";
  }
}