#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

const char FILE_NAME[] = "words.txt";  // the name of the file
const int RAND_WORD_STEP =
    1;  // the space between every character for the randWord string
const int CORRECTLY_GUESSED_STEP =
    2;  // the space between every character for the correctlyGuessed string
const int UNOPENED = -1;  // the integer returned in case of an UNOPENED file
const int LOWER_CHAR_LIMIT = 96;   // integer equivalent of the char before a
const int UPPER_CHAR_LIMIT = 123;  // integer equivalent of the char after z
const int NUM_COL = 80;            // the number of columns in the 2d char array
// ----------------------------------------
// Name: playWordGuess
// Precondition: char[][NUM_COL] should have all of the words
//  from the file and it's rows should all have words.
//  int should be the num of rows in char[][NUM_COL], it
//  should not be zero.
// Postcondition: should play a complete game and
//  return a boolean indicating
//  wether or not the user wants to play again
// ----------------------------------------
bool playWordGuess(char[][NUM_COL], int);
// ----------------------------------------
// Name:countWords
// Precondition: N/A
// Postcondition: Prints and returns the number of words imported from
//                the file. Returns -1 if the file couldn't be opened.
// ----------------------------------------
int countWords();
// ----------------------------------------
// Name: fillWordsArray
// Precondition: char[][NUM_COL] must have rows equal to the
//                number of words in the file.
//                int should be the num of rows in char[][NUM_COL]
//                , it should not be zero.
// Postcondition:Puts all of the words in the file to the 2d char array.
// ----------------------------------------
void fillWordsArray(char[][NUM_COL], int);
// ----------------------------------------
// Name: inString
// Precondition: int must be an
//               int that correspongs to wether the word is the string
//               randWord or the string correctlyGuessed.
// Postcondition:Returns wether or not the char guess appears in the string
//               word.
// ----------------------------------------
bool inString(char[], char, int);
// ----------------------------------------
// Name: numToUpdate
// Precondition: N/A
// Postcondition:Returns the number of times guess appears in word.
// ----------------------------------------
int numToUpdate(char[], char);
// ----------------------------------------
// Name: createSpaces
// Precondition: int must be the length of the random word
// Postcondition: Modifies char[] by adding dashes, spaces
// and a null terminator
// ----------------------------------------
void createSpaces(char[], int);
// ----------------------------------------
// Name: updateSpaces
// Precondition: The first char[] is the random string chosen from the file.
//               the second char[] is the cstring of correctly Guessed
//               characters from the random word and dashes seperated by a
//               single spaces. The char is a lowercase alphabetic
//               character not already guessed and is in the random Word.
// Postcondition:Modifies the cstring of correctly guessed characters
//               and dashses with the newly guessed character
//               in the correct places
// ----------------------------------------
void updateSpaces(char[], char[], char);

int main() {
  // Introduces the game
  std::cout << "Welcome to UMBC Word Guess" << std::endl;
  const int numWords = countWords();
  if (numWords == 0) {
    std::cout << "Please add words to your file.";
  } else if (numWords != UNOPENED) {
    char words[numWords][NUM_COL];
    // fills the array with the words in the file
    fillWordsArray(words, numWords);
    std::srand(time(NULL));
    // plays the game once and asks the user for every replay thereafter
    bool replay = true;
    do {
      replay = playWordGuess(words, numWords);
    } while (replay == true);
  }
  return 0;
}

bool playWordGuess(char words[][NUM_COL], int numWords) {
  int randIndex = std::rand() % numWords;
  char randWord[NUM_COL];
  std::strcpy(randWord, words[randIndex]);
  const int wordLength = std::strlen(randWord);
  std::cout << "Ok. I am thinking of a word with " << wordLength << " letters."
            << std::endl;
  // Correct letters not guessed left
  int lettersLeft = wordLength;
  // Bad guesses left
  int badGuesses = 6;
  // This is the cstring that will show the progress of the player when printed.
  // It is initialized to have dashes for every letter in the randomly chosen
  // word.
  char correctlyGuessed[NUM_COL * 2];
  createSpaces(correctlyGuessed, wordLength);
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
          updateSpaces(randWord, correctlyGuessed, guess);
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
// updates correctlyGuessed
void updateSpaces(char randWord[], char correctlyGuessed[], char guess) {
  for (int i = 0, j = 0; i < int(std::strlen(randWord));
       i += RAND_WORD_STEP, j += CORRECTLY_GUESSED_STEP) {
    // If the guess char is at position i in randWord, then it should
    // be in position j in correctlyGuessed
    if (randWord[i] == guess) {
      correctlyGuessed[j] = guess;
    }
  }
}

// given a cstring word, a char guess, and an int step,
// returns a boolean indiacting if teh guess is in the
// string word
bool inString(char word[], char guess, int step) {
  // iterates through word, step prevents checking
  // unnecessary indicies
  for (int i = 0; i < int(std::strlen(word)); i += step) {
    if (word[i] == guess) {
      return true;
    }
  }
  return false;
}
// Given an int wordLength of the random word and a cstring
// with size wordLength*2 (spaces[]), updates spaces[]
void createSpaces(char spaces[], int wordLength) {
  int length = wordLength * 2;
  for (int i = 0; i < length; i++) {
    // handles formatting
    if (i == length - 1) {
      spaces[i] = '\0';
    } else if (i % 2) {
      spaces[i] = ' ';
    } else {
      spaces[i] = '_';
    }
  }
}
// Given a cstring word and a char guess, returns an int
// equal to how many instances of guess there are in word
int numToUpdate(char word[], char guess) {
  int numSpaces = 0;
  // iterates through word
  for (int i = 0; i < int(std::strlen(word)); i++) {
    if (word[i] == guess) {
      numSpaces++;
    }
  }
  return numSpaces;
}
// counts and returns the number of words in the file,
// (returns -1 if it was unable to open)
int countWords() {
  std::ifstream readWords(FILE_NAME);
  int numWords = 0;
  if (readWords.is_open()) {
    std::cout << "Your file was imported!" << std::endl;
    char first;
    char second;
    while (readWords.get(second)) {
      if (second == '\n') {
        numWords++;
      }
      first = second;
    }
    // adds to numWords if there was no enter after the last word
    if (first > LOWER_CHAR_LIMIT && first < UPPER_CHAR_LIMIT) {
      numWords++;
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
void fillWordsArray(char words[][NUM_COL], int numRows) {
  std::ifstream readWords(FILE_NAME);
  for (int i = 0; i < numRows; i++) {
    char temp;
    int j = 0;
    while (readWords.get(temp) && temp != '\n') {
      words[i][j] = temp;
      j++;
    }
    // adds the null terminator adter each word
    words[i][j] = '\0';
  }
  readWords.close();
}