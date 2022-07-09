/**********
 * File: Book.h
 * Intended for Lab 5: Classes
 **********/

#ifndef BOOK_H  // Header or Include Guards
#define BOOK_H  // Header or Include Guards

#include <iostream>
#include <string>
using namespace std;

class Book {
 public:
  // Default constructor, already implemented.
  Book();

  //**Student Requirement**
  // Do the prototype for each of the functions described in the lab document

  // Returns name of the book
  string getBookName();
  // Sets name of the book
  void setBookName(string name);

  // Returns if book is hard cover or not
  bool isHardCover();
  // Sets hard cover boolean
  void setHardCover(bool state);

  // Returns the number of check-outs
  int getCheckOuts();

  // Sets the number of check-outs
  void setCheckOuts(int numTimes);

  // Outputs whether the book is hard cover or not
  void checkHardcover();

  // Adds one check-out to number of check-outs
  bool addCheckout();

 private:
  //**Student Requirement**
  // Create the member variables below as described in the lab document
  // name of book
  string m_bookName;
  // hard cover or not
  bool m_isHardCover;
  // number of check-outs
  int m_numCheckOuts;
};

#endif  // End of Header Guard
