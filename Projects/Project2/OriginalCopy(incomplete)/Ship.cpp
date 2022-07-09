/*****************************************
** File:    Ship.cpp
** Project: CMSC 202 Project 2, Spring 2021
** Author:  Reagan Armstrong
** Date:    3/11/21
** Section: 10
** E-mail:  reagana1@gl.umbc.edu
**
** This file has the fuction definitions
** for the functions of the Ship class
**
**
**
***********************************************/
#include "Ship.h"

// Ship
// Default constructor for Ship, initializes
// m_shipRank and m_numMaterials
Ship::Ship() {
  m_shipRank = 'D';
  m_numMaterials = 0;
}

// Ship
// Overloaded constructor for Ship, takes in a string name and
// initializes m_shipRank, m_shipName, and m_numMaterials
Ship::Ship(string name) {
  m_shipName = name;
  m_shipRank = 'D';
  m_numMaterials = 0;
}

// GetName
// Getter function for m_shipName
string Ship::GetName() { return m_shipName; }

// SetName
// Setter function for m_shipName
void Ship::SetName(string name) { m_shipName = name; }

// CheckMaterial
// Takes in a material to check and returns its index in m_myMaterials
// if it exists there, if not then it returns -1
int Ship::CheckMaterial(Material toCheck) {
  string materialName = toCheck.m_name;
  string materialType = toCheck.m_type;
  // iterates through m_myMaterials
  for (int i = 0; i < m_numMaterials; i++) {
    // checks if the name and type are the same
    if ((m_myMaterials[i].m_name == materialName) &&
        (m_myMaterials[i].m_type == materialType)) {
      return i;
    }
  }
  // in case if the material is not in the m_myMaterials array
  return -1;
}

// AddMaterial
// Adds a given material to m_myMaterials
void Ship::AddMaterial(Material toAdd) {
  // copies over the properties of toAdd to the index of m_myMaterials
  // not yet modified (m_numMaterials)
  m_myMaterials[m_numMaterials].m_name = toAdd.m_name;
  m_myMaterials[m_numMaterials].m_type = toAdd.m_type;
  m_myMaterials[m_numMaterials].m_material1 = toAdd.m_material1;
  m_myMaterials[m_numMaterials].m_material2 = toAdd.m_material2;
  m_myMaterials[m_numMaterials].m_quantity = toAdd.m_quantity;
  // increases the m_numMaterials to prevent overwrites
  m_numMaterials++;
}

// IncrementQuantity
// Takes in a material and increments the quantity of that material in
// m_myMaterials
void Ship::IncrementQuantity(Material toInc) {
  // finds index
  int index = CheckMaterial(toInc);
  m_myMaterials[index].m_quantity++;
}

// DecrementQuantity
// Takes in a material and decrements the quantity of that material in
// m_myMaterials and return true if the material has over 0 quantity,
// returns false otherwise
bool Ship::DecrementQuantity(Material toDec) {
  // finds index
  int index = CheckMaterial(toDec);
  // checks if it is not possible to decrement
  if (m_myMaterials[index].m_quantity == 0) {
    return false;
  }
  // decrements quantity it it is possible
  m_myMaterials[index].m_quantity--;
  return true;
}

// CheckQuantity
// Given 2 materials, returns if there is enough of each in m_myMaterials
// for merging
bool Ship::CheckQuantity(Material matOne, Material matTwo) {
  // finds the indexes of the materials
  int matOneIndex = CheckMaterial(matOne);
  int matTwoIndex = CheckMaterial(matTwo);
  // checks if the indexes don't exists
  if (matOneIndex == -1 || matTwoIndex == -1) {
    return false;
    // handles the case in which the materials are the same
  } else if (matOneIndex == matTwoIndex &&
             m_myMaterials[matOneIndex].m_quantity < 2) {
    return false;
    // handles the case when the materials are not the same
  } else if (m_myMaterials[matOneIndex].m_quantity < 1 ||
             m_myMaterials[matTwoIndex].m_quantity < 1) {
    return false;
  }
  return true;
}

// GetMaterial
// getter function for the material at the given index
Material Ship::GetMaterial(int index) { return m_myMaterials[index]; }

// IncRank
// Increments the rank of the ship
void Ship::IncRank() {
  // if the character is between B and D
  if (m_shipRank > 65) {
    m_shipRank--;
    // if the character is A
  } else {
    m_shipRank = 'S';
  }
}

// GetRank
// Getter function for the ship's rank
char Ship::GetRank() { return m_shipRank; }
