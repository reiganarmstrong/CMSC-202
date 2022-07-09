//Lab 4 - Pass by Reference and Pointers
//CMSC 202

#include <iostream>
using namespace std;

//Constants here cash = 500, buy for $25.50, sell for $55




//Function Prototypes (Two functions - buyGold(reference) and sellGold(pointers))



int main() {
  double cash = START_CASH; //Your starting cash
  int gold = 0; //Your starting gold
  
  //Display initial message
  cout.precision(2); //Sets precision for currency
  cout << fixed; //Forces two decimals
  cout << "Your current cash amount is $" << cash << endl;
  cout << "You have " << gold << " pieces of gold." << endl;

  //Calls buyGold function by reference
  buyGold(cash, gold); //calls buyGold function by reference
  cout << "\nYou bought " << gold << " pieces of gold and your current cash is $" << cash << endl;

  //Calls sellGold function using pointers
  sellGold(&cash, &gold); //calls sellGold function by pointers
  
  //Display result
  cout << "\nYou sold " << gold << " pieces of gold." << endl;
  cout << "Current Cash: $" << cash << endl;
  cout << "Current Gold: " << gold << endl;
  
  return 0;
}

//Implement buyGold here using pass-by-reference
//Buy gold should ask the user how many gold pieces they would like to buy
//Loop checks to make sure that the user has enough cash
//Then it decreases cash and increases gold





//Implement sellGold here using pointers
//Buy gold should ask the user how much gold to sell
//Loop checks to make sure that the user has enough gold
//Then it increases cash and decreases gold
