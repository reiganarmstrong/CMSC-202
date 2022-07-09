/*****************************************
** File:    lab1.cpp
** Project: CMSC 202 Lab 1, Spring 2021
** Author:  Reagan Armstrong
** Date:    2/7/21
** Section: 10
** E-mail:  reagana1@gl.umbc.edu
**
** This program asks the user for the name and age of their cat.
** It then asks them to preform 3 actions.
**
**
**
***********************************************/

#include <iostream>
#include <string>
using namespace std;

int main() {
  char name[80];
  int age = 0;
  // constants I will use for asking questions and giving options
  const string petKitty = "1. Pet Kitty";
  const string feedKitty = "2. Feed Kitty";
  const string chaseKitty = "3. Chase Kitty";
  const string askAge =
      "Please enter your cat's age, it should be an integer between 0 "
      "and 22";
  const string actions = "What would you like to do?";
  const string askAction = "Enter your choice (1-3):";
  // The variable I will use to store their chosen action
  int chosenAction = 0;
  cout << "What is your cat's name?" << endl;
  cin.getline(name, 80);
  cout << askAge << endl;
  cin >> age;
  // checks if the age was an integer and between 0 and 22
  while (cin.fail() || (age < 0 || age > 22)) {
    cout << askAge << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> age;
  }
  // display's the information now stored about the cat
  cout << "Cat's Name = " << name << endl;
  cout << "Cat's Age = " << age << endl << endl;
  // This for loop runs three times where a valid input is given
  for (int i = 0; i < 3; i++) {
    cout << actions << endl;
    cout << petKitty << endl;
    cout << feedKitty << endl;
    cout << chaseKitty << endl;
    cout << askAction << endl;
    cin >> chosenAction;
    // checks if an integer between 1 and 3 was given, if not it repromts
    // the user
    while (cin.fail() || (chosenAction < 1 || chosenAction > 3)) {
      cout << actions << endl;
      cout << petKitty << endl;
      cout << feedKitty << endl;
      cout << chaseKitty << endl;
      cout << askAction << endl;
      cin.clear();
      cin.ignore(256, '\n');
      cin >> chosenAction;
    }
    // This switch links the chosen action in the form of an integer to the
    // correct cout message.
    switch (chosenAction) {
      case 1:
        cout << "You pet Kitty and they purr." << endl;
        break;
      case 2:
        cout << "Kitty meows gently as you feed them." << endl;
        break;
      case 3:
        cout << "You chase after Kitty and they hiss and try to bite." << endl;
        break;
      default:
        cout << "A problem has occured in the mainframe." << endl;
        break;
    }
  }
  // Ending message
  cout << "That is enough for today. Good-bye";
  return 0;
}