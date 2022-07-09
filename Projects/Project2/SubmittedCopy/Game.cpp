/*****************************************
** File:    Game.cpp
** Project: CMSC 202 Project 2, Spring 2021
** Author:  Reagan Armstrong
** Date:    3/11/21
** Section: 10
** E-mail:  reagana1@gl.umbc.edu
**
** This file has the fuction definitions
** for the functions of the Game class
**
**
**
***********************************************/
#include "Game.h"
// Game
// default constructor for the Game class, loads materials
// into m_materials and m_myShip, and sets the name of the ship
Game::Game() {
  // prints title
  GameTitle();
  // loads materials
  LoadMaterials();
  cout << "What is the name of your Ship?" << endl;
  string shipName;
  // gets the name from the player
  getline(cin, shipName);
  cout << endl;
  m_myShip.SetName(shipName);
  // iterates through the material array and adds them to m_myShip
  for (int i = 0; i < PROJ2_SIZE; i++) {
    m_myShip.AddMaterial(m_materials[i]);
  }
}

// LoadMaterials
// gets material data from the materials file and puts that information
// into the m_materials array
void Game::LoadMaterials() {
  ifstream data(PROJ2_DATA);
  // checks if the file was successfully opened
  if (data.is_open()) {
    // keeps track of already modified m_materials indicies
    int matIndex = 0;
    string temp;
    // iterates for every line with a string followed by a comma
    while (getline(data, temp, ',')) {
      m_materials[matIndex].m_name = temp;
      getline(data, temp, ',');
      m_materials[matIndex].m_type = temp;
      getline(data, temp, ',');
      m_materials[matIndex].m_material1 = temp;
      // last string has a new line character instead of a comma after it
      // so that is set to be the delimiter (its the default one)
      getline(data, temp);
      m_materials[matIndex].m_material2 = temp;
      m_materials[matIndex].m_quantity = 0;
      // iterates matIndex
      matIndex++;
    }
  } else {
    cout << PROJ2_DATA + " failed to open" << endl;
  }
  data.close();
}

// StartGame
// Plays (facilitates) a game of No Man’s Alchemy
void Game::StartGame() {
  int status;
  // iterates once then continues to do so whenever 5 is not entered
  // by the player
  do {
    // status has the valid value entered by the user
    status = MainMenu();
    if (status == 1) {
      DisplayMaterials();
    } else if (status == 2) {
      SearchMaterials();
    } else if (status == 3) {
      CombineMaterials();
    } else if (status == 4) {
      CalcScore();
    }
  } while (status != 5);
  // ending text
  cout << "Thanks for playing No Man's Alchemy" << endl;
}

// DisplayMaterials
// prints all of the materials in m_myShip and their quantities
void Game::DisplayMaterials() {
  // iterates for PROJ2_SIZE
  for (int i = 0; i < PROJ2_SIZE; i++) {
    Material temp = m_myShip.GetMaterial(i);
    // i is the index so 1 must be added
    cout << i + 1 << "."
         << " " << temp.m_name << " " << temp.m_quantity << endl;
  }
}

// MainMenu
// Handles the printing of the main menu and getting valid inputs from the
// user
int Game::MainMenu() {
  // if they have reached S rank they won and main menu does not need
  // to prompt more inputs, soit sends an exit code
  if (m_myShip.GetRank() == 'S') {
    cout << "You ship has reached rank S, you win!" << endl;
    return 5;
  }
  // an array of options
  const string OPTIONS[] = {
      "1. Display your Ship's Materials", "2. Search for Raw Materials",
      "3. Attempt to Merge Materials", "4. See Score", "5. Quit"};
  const int NUM_OPTIONS = 5;
  int input;
  // iterates at least once and stops when the user's input is a
  // int between 1 and 5
  do {
    cout << "What would you like to do?" << endl;
    // prints all of the options
    for (int i = 0; i < NUM_OPTIONS; i++) {
      cout << OPTIONS[i] << endl;
    }
    cin >> input;
  } while (input < 1 || input > 5);
  return input;
}

// SearchMaterials
// Finds a random raw item from m_materials and
// increments it's quantity in m_myShip
void Game::SearchMaterials() {
  int index;
  bool found = false;
  // iterates until a raw material is found
  while (!found) {
    // index is some random number between 0 and PROJ2_SIZE-1
    index = rand() % PROJ2_SIZE;
    if (m_materials[index].m_type == "raw") {
      found = true;
    }
  }
  cout << m_materials[index].m_name << " found!" << endl;
  // increments the quantity of that raw material in m_myShip
  m_myShip.IncrementQuantity(m_materials[index]);
}

// CombineMaterials
// Facilitates the combination of materials from the ship
void Game::CombineMaterials() {
  int choiceOneIndex;
  int choiceTwoIndex;
  int recipeIndex;
  // changes choiceOneIndex to be the index of the first valid material
  // chosen for combination
  RequestMaterial(choiceOneIndex);
  // changes choiceOneIndex to be the index of the second valid material
  // chosen for combination
  RequestMaterial(choiceTwoIndex);
  // checks if there is enough of each material to combine
  if (m_myShip.CheckQuantity(m_materials[choiceOneIndex],
                             m_materials[choiceTwoIndex])) {
    recipeIndex = SearchRecipes(m_materials[choiceOneIndex].m_name,
                                m_materials[choiceTwoIndex].m_name);
    // If they can be combined there will be a non -1 index of the end
    // product
    if (recipeIndex != -1) {
      // changes the quantity of the materials after combination
      m_myShip.DecrementQuantity(m_materials[choiceOneIndex]);
      // changes the quantity of the materials after combination
      m_myShip.DecrementQuantity(m_materials[choiceTwoIndex]);
      // changes the quantity of the materials after combination
      m_myShip.IncrementQuantity(m_materials[recipeIndex]);
      // prints after the materials are merged
      cout << m_materials[choiceOneIndex].m_name << " and "
           << m_materials[choiceTwoIndex].m_name << " merged to create "
           << m_materials[recipeIndex].m_name << "!" << endl;
    } else {
      // in case the materials can not be merged
      cout << m_materials[choiceOneIndex].m_name << " and "
           << m_materials[choiceTwoIndex].m_name << " can not be merged."
           << endl;
    }

  } else {
    // in case if there is not enough materials
    cout << "You don't have enough " << m_materials[choiceOneIndex].m_name
         << " or " << m_materials[choiceTwoIndex].m_name
         << " to attempt that merge." << endl;
  }
}

// RequestMaterial
// takes in an int passed by reference and changes it to be the index
// of the material chosen by the player
void Game::RequestMaterial(int &choice) {
  int input;
  // iterates at least once and until an input between 1 and PROJ2_SIZE
  // is inputted
  do {
    // if they want to see the materials
    if (input == -1) {
      DisplayMaterials();
    }
    cout << "Which materials would you like to merge?" << endl;
    cout << "To list known materials enter -1" << endl;
    cin >> input;
  } while (input < 1 || input > PROJ2_SIZE);
  // index of the material is one minus the input
  choice = input - 1;
}

// SearchRecipies
// given the names of the materials, it returns the index of a material
// they can be combined to make, or -1 if they can not be combined.
int Game::SearchRecipes(string mat1, string mat2) {
  const string UNIQUE = "unique";
  // iterates for the length of m_materials
  for (int i = 0; i < PROJ2_SIZE; i++) {
    // checks if the parameters(mat1 and mat2) satisfy both of the required
    // materials to make m_materials[i]
    if ((mat1 == m_materials[i].m_material1 &&
         mat2 == m_materials[i].m_material2) ||
        (mat2 == m_materials[i].m_material1 &&
         mat1 == m_materials[i].m_material2)) {
      if (m_materials[i].m_type == UNIQUE) {
        int uniqueIndex = m_myShip.CheckMaterial(m_materials[i]);
        // checks if the unique material has been crafted before
        if (m_myShip.GetMaterial(uniqueIndex).m_quantity == 0) {
          // checks that neither of the required materials are unique
          bool matOneIsUnique = false;
          bool matTwoIsUnique = false;
          // iterates through material array
          for (int j = 0; j < PROJ2_SIZE; j++) {
            // if the name matched and it has type unique
            if (m_materials[j].m_name == mat1 &&
                m_materials[j].m_type == UNIQUE) {
              matOneIsUnique = true;
            }
            // if the name matched and it has type unique
            if (m_materials[j].m_name == mat2 &&
                m_materials[j].m_type == UNIQUE) {
              matTwoIsUnique = true;
            }
          }
          // if neither are unique then increment the rank
          if (!matOneIsUnique && !matTwoIsUnique) {
            m_myShip.IncRank();
          }

          return i;
        }
      } else {
        return i;
      }
    }
  }
  return -1;
}

// CalcScore
// Displays the name and rank of the player's ship
void Game::CalcScore() {
  // header/seperator
  cout << "***The Ship***" << endl;
  cout << "The Great Ship " << m_myShip.GetName() << endl;
  cout << "Ship Rank: " << m_myShip.GetRank() << endl;
}
