#include "Book.h"

// Constructor -- Already Implemented
Book::Book() {
  cout << "Creating a book..." << endl;
  m_bookName = "book";
  m_isHardCover = false;
  m_numCheckOuts = 0;
}

// Here is an example for a getter and a setter

int Book::getCheckOuts() { return m_numCheckOuts; }

void Book::setCheckOuts(int numTimes) {
  // If number of check-outs is greater than 6, set to 6.
  if (numTimes > 6) {
    m_numCheckOuts = 6;
  } else {
    m_numCheckOuts = numTimes;
  }
}

//**Student Requirement**
// Implement getters and setters for bookName and isHardCover here
string Book::getBookName() { return m_bookName; }
void Book::setBookName(string name) { m_bookName = name; }
bool Book::isHardCover() { return m_isHardCover; }
void Book::setHardCover(bool state) { m_isHardCover = state; }

//**Student Requirement**
// Custom Functions -- Implement checkHardCover and addCheckOut
void Book::checkHardcover() {
  if (m_isHardCover) {
    cout << m_bookName << " is a hardcover book!" << endl;
  } else {
    cout << m_bookName << " is a paperback book!" << endl;
  }
}
bool Book::addCheckout() {
  if (m_numCheckOuts == 6) {
    return false;
  }
  m_numCheckOuts++;
  return true;
}
