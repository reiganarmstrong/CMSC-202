/*****************************************
** File:    proj1.cpp
** Project: CMSC 202 Project 1, Spring 2022
** Author:  Vrinda Thapliyal
** Date:    02/26/2022
** Section: 31
** E-mail:  vrindat1@umbc.edu
**
** Wordle with no color. Project 1.
**
**
**
**
***********************************************/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
const string correct = "&", wrongLocation = "!", incorrect = "_",
             fileName = "proj1_data.txt", notGuessed = "-----", checked = "/",
             winningStatus = "&&&&&";
const int numWords = 2315, numGuesses = 6, wordLength = 5;

// handles replays
// precondition: none
// postconsition: returns true/false depending on user input
bool playAgain();
// handles loading the file
// precondition: an empty words array of size equal to the number of words in
// the file
// postcondition: adds all of the words in the file to the words array
bool loadFile(string words[]);
// checks if the word is in the list
// precondition: takes in an array of strings words and a string word
// postconditon: checks if word is in words array
bool wordInList(string words[], string word);
// undates the records with a new guess
//  precondition: an array of guesses, an array of statuses, the current guess,
//  the correct word, and the iteration of the current guess
// postcondition: updates the values in gueses[] and statuses[]
void updateRecords(string gueses[], string statuses[], string guess,
                   string correctWord, int iteration);
// handles playing the game once
// precondition: a complete array of words from the file
// postcondition: play a game of wordle
void playWordle(string words[]);

int main() {
    string words[numWords];
    // loads the file, if loaded plays the game, if not exits
    if (loadFile(words)) {
        // stes the seed
        srand(time(NULL));
        cout << "Welcome to UMBC Wordle" << endl;
        cout << "2315 words imported." << endl;
        // plays wordle as long as the user says play again
        do {
            playWordle(words);
        } while (playAgain());
    }
    return 0;
}

// prompts the user for another game, returns true if the want to do so
bool playAgain() {
    string input;
    do {
        cout << "Another game? y/n" << endl;
        // gets their input
        getline(cin, input);
    } while (input != "y" && input != "n");
    if (input == "y") {
        return true;
    }
    return false;
}

// loads all of the words in the data file into the words array
bool loadFile(string words[]) {
    // creats an ifstream and opens the file
    ifstream wordFile(fileName);
    // checks if the file is open, if not return false
    if (wordFile.is_open()) {
        cout << "Your file was imported!" << endl;
    } else {
        cout << "Error importing file" << endl;
        return false;
    }
    int i = 0;
    string word;
    // adds all if the words into the words arr, i<numWords is there to prevent
    // error when checking words[words.length()]
    while (i < numWords && getline(wordFile, words[i])) {
        i++;
    }
    // closes file and indicates the file was loaded
    wordFile.close();
    return true;
}

// checks if word is in array words
bool wordInList(string words[], string word) {
    // makes sure the word is 5 characters
    if (word.length() != wordLength) {
        return false;
    }
    // loops through the array and checks if its there
    for (int i = 0; i < numWords; i++) {
        if (word == words[i]) {
            return true;
        }
    }
    return false;
}

// updates the user values of the recorded guesses and their corresponding
// statuses
void updateRecords(string gueses[], string statuses[], string guess,
                   string correctWord, int iteration) {
    gueses[iteration] = guess;
    // initializes the status to string of dashes
    statuses[iteration] = "-----";
    // adds the correct character to spaces and marks them as checked in
    // correct word and & in statuses
    for (int i = 0; i < wordLength; i++) {
        // adds a & if the characters match
        if (correctWord.at(i) == guess.at(i)) {
            statuses[iteration].replace(i, 1, correct);
            correctWord.replace(i, 1, checked);
            // adds a ! if the character exists elsewhere
        }
    }
    // identifies the rest of the characters of the word that are not correct
    for (int i = 0; i < wordLength; i++) {
        // makes sure its not a character thats already accounted for
        if (statuses[iteration].at(i) == '-') {
            // if the character exists elsewhere
            if (int(correctWord.find(guess.at(i))) != -1) {
                statuses[iteration].replace(i, 1, wrongLocation);
                correctWord.replace(int(correctWord.find(guess.at(i))), 1,
                                    checked);
                // adds a _ if the character is not in the word
            } else {
                statuses[iteration].replace(i, 1, incorrect);
            }
        }
    }
}

// displays the statuses and gueses recorded
void displayRecords(string gueses[], string statuses[], int numGuessed) {
    // this indicates how many notGuessed lines to add
    int guessesLeft = numGuesses - numGuessed;
    // displays the guesses and statuses
    for (int i = 0; i < numGuessed; i++) {
        cout << gueses[i] << endl << statuses[i] << endl;
    }
    // adds lines for the rest of the guesses
    for (int i = 0; i < guessesLeft; i++) {
        cout << notGuessed << endl;
    }
}

// plays 1 instance of wordle
void playWordle(string words[]) {
    // records the guesses
    string gueses[numGuesses];
    // records how correct a guess was
    string statuses[numGuesses];
    bool gameWon = false;
    // gets a random word
    string correctWord = words[rand() % numWords];
    cout << "Ok. I am thinking of a word with five letters." << endl;
    // iterates until the game is won or all guesses are used up
    for (int guessIndex = 0; !gameWon && guessIndex < numGuesses;
         guessIndex++) {
        string input;
        // checks the entered word is valid
        cout << "What word would you like to guess?" << endl;
        getline(cin, input);
        while (!wordInList(words, input)) {
            cout << "That word is not in the word list" << endl;
            cout << "What word would you like to guess?" << endl;
            getline(cin, input);
        }
        // updates the values in gueses and statuses and displaty them
        updateRecords(gueses, statuses, input, correctWord, guessIndex);
        displayRecords(gueses, statuses, guessIndex + 1);
        // checks if the user guessed the word
        if (statuses[guessIndex] == winningStatus) {
            gameWon = true;
        }
    }
    if (gameWon) {
        cout << "Congrats you won!" << endl;
    } else {
        cout << "Sorry, you lost" << endl;
    }
    cout << "The correct word was: " << correctWord << endl;
}