/**************
 * File: lab5.cpp
 * The user creates this file to demonstrate use of a course.
 *************/

#include <iostream>

#include "Book.h"
using namespace std;

int main() {
  //**Student Requirement**
  // Part 1: Create 2 books by instantiating them
  Book book1, book2;

  //**Student Requirement**
  // Part 2: Set their values for book name, cover type, and amount of
  // check-outs.
  book1.setBookName("Pride and Prejudice");
  book1.setCheckOuts(0);
  book1.setHardCover(false);
  book2.setBookName("Cat in the Hat");
  book2.setCheckOuts(6);
  book2.setHardCover(true);
  //**Student Requirement**
  // Part 3: Output their information:  Name, cover type, and amount of
  // check-outs
  cout << "Data of Book1:\n";
  cout << "Book Name: " << book1.getBookName() << endl;
  cout << "Number of Checkouts: " << book1.getCheckOuts() << endl;
  cout << "Hardcover/Paperback: " << book1.isHardCover() << endl;
  cout << "Data of Book2:\n";
  cout << "Book Name: " << book2.getBookName() << endl;
  cout << "Number of Checkouts: " << book2.getCheckOuts() << endl;
  cout << "Hardcover/Paperback: " << book2.isHardCover() << endl;

  //**Student Requirement**
  // Part 4: Call a custom function: Check if book is hard cover or not
  book1.checkHardcover();
  book2.checkHardcover();
  //**Student Requirement**
  // Part 5: Update data members with custom function: Add 1 check-out to the
  // amount of check-outs Display updated amount of check-outs
  if (book1.addCheckout()) {
    cout << "The book has been checked out!" << endl;
  } else {
    cout << "This book has been checked out too many times already!" << endl;
  }
  if (book2.addCheckout()) {
    cout << "The book has been checked out!" << endl;
  } else {
    cout << "This book has been checked out too many times already!" << endl;
  }
  cout << book1.getCheckOuts() << endl;
  cout << book2.getCheckOuts() << endl;

  return 0;
}
