/*****************************************
** File:    proj1.cpp
** Project: CMSC 202 Lab 1, Spring 2021
** Author:  Reagan Armstrong
** Date:    2/20/21
** Section: 10
** E-mail:  reagana1@gl.umbc.edu
**
** This program plays a game of word guess
**
**
**
**
***********************************************/

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
const std::string FILE_NAME = "words.txt";  // the name of the file
const int RAND_WORD_STEP =
    1;  // the space between every character for the randWord string
const int CORRECTLY_GUESSED_STEP =
    2;  // the space between every character for the correctlyGuessed string
const int UNOPENED = -1;  // the integer returned in case of an UNOPENED file
const int LOWER_CHAR_LIMIT = 96;   // integer equivalent of the char before a
const int UPPER_CHAR_LIMIT = 123;  // integer equivalent of the char after z

// ----------------------------------------
// Name: playWordGuess
// Precondition: words[] should have all of the words
//  from the file and it should be completely filled.
//  numWords should ne the size of words[] it,
//  should not be zero.
// Postcondition: should play a complete game and
//  return a boolean indicating
//  wether or not the user wants to play again
// ----------------------------------------
bool playWordGuess(std::string[], int);
// ----------------------------------------
// Name:countWords
// Precondition: N/A
// Postcondition: Prints and returns the number of words imported from
//                the file. Returns -1 if the file couldn't be opened.
// ----------------------------------------
int countWords();
// ----------------------------------------
// Name: fillWordsArray
// Precondition: The array of strings words must have size equal to the
//                number of words in the file.
// Postcondition:Puts all of the words in the file to the words array.
// ----------------------------------------
void fillWordsArray(std::string[]);
// ----------------------------------------
// Name: inString
// Precondition: word must be a string. guess much be a char. Step must be an
//               int that correspongs to wether the word is the string
//               randWord or the string correctlyGuessed.
// Postcondition:Returns wether or not the char guess appears in the string
//               word.
// ----------------------------------------
bool inString(std::string, char, int);
// ----------------------------------------
// Name: numToUpdate
// Precondition: word must be a string. guess much be a char.
// Postcondition:Returns the number of times guess appears in word.
// ----------------------------------------
int numToUpdate(std::string, char);
// ----------------------------------------
// Name: createSpaces
// Precondition: The length of the random word chosen from the words file
//                in integer form.
// Postcondition: Returns a string of length dashes with spaces in between
//                each one.
// ----------------------------------------
std::string createSpaces(int);
// ----------------------------------------
// Name: updateSpaces
// Precondition: randWord is the random string chosen from the file.
//               correctlyGuessed is the string of correctlyGuessed
//               characters from randWords and dashes seperated by a
//               single spaces. The guess is a lowercase alphabetic
//               character not already in correctlyGuessed and in randWord.
// Postcondition:Returns an updated correctlyGuessed string with the guess
//               char in the correct spaces.
// ----------------------------------------
std::string updateSpaces(std::string, std::string, char);

int main() {
  // Introduces the game
  std::cout << "Welcome to UMBC Word Guess" << std::endl;
  const int numWords = countWords();
  if (numWords == 0) {
    std::cout << "Please add words to your file.";
  } else if (numWords != UNOPENED) {
    std::string words[numWords];
    // fills the array with the words in the file
    fillWordsArray(words);
    std::srand(time(NULL));
    // plays the game once and asks the user for every replay thereafter
    bool replay = true;
    do {
      replay = playWordGuess(words, numWords);
    } while (replay == true);
  }
  return 0;
}
// Given the array of words and it's size, plays the game once.
bool playWordGuess(std::string words[], int numWords) {
  int randIndex = std::rand() % numWords;
  std::string randWord = words[randIndex];
  const int wordLength = randWord.length();
  std::cout << "Ok. I am thinking of a word with " << wordLength << " letters."
            << std::endl;
  // Correct letters not guessed left
  int lettersLeft = wordLength;
  // Bad guesses left
  int badGuesses = 6;
  // This is the string printed that will show the progress of the player.
  // It is initialized to have dashes for every letter in the randomly chosen
  // word.
  std::string correctlyGuessed = createSpaces(wordLength);
  // Should handle all of the guesses from the user until they either win
  // or loose.
  while (lettersLeft > 0 && badGuesses > 0) {
    char guess;
    bool validGuess = false;
    std::cout << lettersLeft << " letters remain." << std::endl;
    std::cout << correctlyGuessed << std::endl;
    while (!validGuess) {
      // Checks if the inputted character is a lowercase letter.
      // Reprompts the user if it is not.
      std::cout << "What letter would you like to guess?" << std::endl;
      std::cin >> guess;
      // If the character if between 'a' and 'z' validGuess will equal true
      // otherwise false.
      validGuess =
          (guess > LOWER_CHAR_LIMIT && guess < UPPER_CHAR_LIMIT) ? true : false;
    }
    // If the character is in the randomly chosen word
    if (inString(randWord, guess, RAND_WORD_STEP)) {
      // If the character is not an already guessed character
      if (!inString(correctlyGuessed, guess, CORRECTLY_GUESSED_STEP)) {
        lettersLeft -= numToUpdate(randWord, guess);
        if (lettersLeft > 0) {
          // If the while loop will iterate again correctlyGuessed is updated
          correctlyGuessed = updateSpaces(randWord, correctlyGuessed, guess);
        }
      } else {
        // Subtract a bad guess and tells the user it is because they already
        // guessed the character .
        badGuesses--;
        std::cout << "That letter was already guessed" << std::endl;
        std::cout << "You have " << badGuesses << " bad guesses left."
                  << std::endl;
      }
    } else {
      // Subtracts a bad guess and tells the user its because the character is
      // not in the puzzle.
      badGuesses--;
      std::cout << "There are no " << guess << " in the puzzle" << std::endl;
      std::cout << "You have " << badGuesses << " bad guesses left."
                << std::endl;
    }
  }
  if (lettersLeft == 0) {
    // Win text
    std::cout << "Congrats you won!" << std::endl;
    std::cout << "The correct word was: " << randWord << std::endl;
  } else {
    // Losing text
    std::cout << "Sorry, you lost" << std::endl;
    std::cout << "The correct word was: " << randWord << std::endl;
  }
  char replayOption;
  // handles replays
  do {
    // input validation
    std::cout << "Another game? y/n" << std::endl;
    std::cin >> replayOption;
  } while (replayOption != 'y' && replayOption != 'n');
  if (replayOption == 'y') {
    return true;
  } else {
    return false;
  }
}
// given randWord, correctlyGuessed and guess,
// returns an updated correctlyGuessed
std::string updateSpaces(std::string randWord, std::string correctlyGuessed,
                         char guess) {
  for (int i = 0, j = 0; i < int(randWord.length());
       i += RAND_WORD_STEP, j += CORRECTLY_GUESSED_STEP) {
    // If the guess char is at position i in randWord, then it should
    // be in position j in correctlyGuessed
    if (randWord[i] == guess) {
      correctlyGuessed[j] = guess;
    }
  }
  return correctlyGuessed;
}
// Given a string word and a char guess, returns an int
// equal to how many instances of guess there are in word
int numToUpdate(std::string word, char guess) {
  int numSpaces = 0;
  // iterates through word
  for (int i = 0; i < int(word.length()); i++) {
    if (word[i] == guess) {
      numSpaces++;
    }
  }
  return numSpaces;
}
// given a string word, a char guess, and an int step,
// returns a boolean indiacting if teh guess is in the
// string word
bool inString(std::string word, char guess, int step) {
  // iterates through word, step prevents checking
  // unnecessary indicies
  for (int i = 0; i < int(word.length()); i += step) {
    if (word[i] == guess) {
      return true;
    }
  }
  return false;
}
// Given an int length of the random word, returns
// a string with spaces and dashes for the user to see.
std::string createSpaces(int length) {
  std::string spaces = "";
  for (int i = 0; i < length; i++) {
    // handles formatting
    (i < length - 1) ? spaces.append("_ ") : spaces.append("_");
  }
  return spaces;
}
// counts and returns the number of words in the file,
// (returns -1 if it was unable to open)
int countWords() {
  std::string word;
  std::ifstream readWords(FILE_NAME);
  int numWords = 0;
  if (readWords.is_open()) {
    std::cout << "Your file was imported!" << std::endl;
    if (readWords >> word) {
      // increase numWord by 1 for every word
      do {
        numWords++;
      } while (readWords >> word);
    }
    std::cout << numWords << " words imported." << std::endl;
  } else {
    std::cout << "Your file was not imported!" << std::endl;
    numWords = UNOPENED;
  }
  readWords.close();
  return numWords;
}
// updates a given array with all of the words in the file
void fillWordsArray(std::string words[]) {
  std::ifstream readWords(FILE_NAME);
  std::string word;
  // iterates through all words[]
  for (int i = 0; readWords >> word; i++) {
    words[i] = word;
  }
  readWords.close();
}
