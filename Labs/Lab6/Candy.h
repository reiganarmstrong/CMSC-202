//File: Candy.h

#ifndef CANDY_H
#define CANDY_H

#include <iostream>
#include <string>
using namespace std;

class Candy
{
 public:
  //Default Constructor for Candy
  Candy();
  //Overloaded Constructor for Candy
  Candy(string c_name, double c_price, int c_quantity);
  //Name: setName
  //Sets the name of the variable
  void setName(string toSetName);
  //Name: setPrice
  //Sets the price of the candy
  void setPrice(double toSetPrice);
  //Name: setQuantity
  //Sets the quantity of the candy to be purchased
  void setQuantity(int toSetQuant);
  //Name: getName
  //Returns the candy's name
  string getName();
  //Name: getPrice
  //Returns the price of the candy
  double getPrice();
  //Name: getQuant
  //Returns the quantity of the candy
  int getQuantity();

 private:
  string name;
  double price;
  int quantity;
};
#endif
