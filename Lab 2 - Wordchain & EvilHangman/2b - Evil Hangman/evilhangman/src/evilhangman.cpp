#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <array>

using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

set<string> loadDictionary();
array<int, 2> findWordLengths(set<string>& dictionary);
void hangMan(set<string>& dictionary, int& wordLength, int& guesses, bool& debug);
set<string> getPossibleWords(set<string>& dictionary, int& wordLength);
void printWords(set<string> &possibleWords);
void printStatus(bool& debug, set<string>& possibleWords, int& guessesLeft, bool& guessCorrect, string currentWord);

int main() {
    set<string> dictionary = loadDictionary();
    cout << "Welcome to Hangman." << endl;

    int chosenWordLength;
    array<int, 2> wordLengths = findWordLengths(dictionary);

    cout << "Word length? ";

    do {
        cin >> chosenWordLength;
    } while (!(chosenWordLength >= wordLengths.at(0) && chosenWordLength <= wordLengths.at(1)));

    cout << "Number of guesses? ";

    int guesses;
    do {
        cin >> guesses;
    } while (guesses <= 0);

    cout << "Debug (true/false)? ";

    bool debug;
    cin >> debug;

    hangMan(dictionary, chosenWordLength, guesses, debug);

    return 0;
}

set<string> loadDictionary(){
    ifstream input;
    set<string> dictionary;
    input.open("dictionary.txt");
    string line;
    while(getline(input, line)) {
        dictionary.insert(line);
    }

    return dictionary;
}

array<int, 2> findWordLengths(set<string>& dictionary) {
    int longestWord;
    int shortestWord = longestWord = dictionary.begin()->length();
    for (string word : dictionary) {
        int wordLength = word.length();
        if (wordLength < shortestWord) {
            shortestWord = wordLength;
        } else if (wordLength > longestWord) {
            longestWord = wordLength;
        }
    }

    array<int, 2> wordLengths = {shortestWord, longestWord};
    return wordLengths;
}

void hangMan(set<string>& dictionary, int& wordLength, int& guesses, bool& debug) {
    set<string> possibleWords = getPossibleWords(dictionary, wordLength);
    bool continueGame = true;
    while (continueGame){
        cout << "Guess a letter: " << flush;
        string letter;
        do {
            cin >> letter;
        } while (letter.length() != 1 && alphabet.find(letter[0]) == -1);
    }
}

void printStatus(bool& debug, set<string>& possibleWords, int& guessesLeft, bool& guessCorrect, string currentWord){
    if (debug) {
        cout << "Possible words: ";
        for (string word : possibleWords){
            cout << word << endl;
        }
    }
    if (guessCorrect){
        cout << "Guess correct!" << endl;
    } else {
        cout << "WRONG!" << endl;
    }
    cout << "Letters guessed: " << currentWord << ". Guesses left: " << guessesLeft << "." << endl;
}

set<string> getPossibleWords(set<string>& dictionary, int& wordLength) {
    set<string> possibleWords;
    for (string word : dictionary) {
        if (word.length() == wordLength) {
            possibleWords.insert(word);
        }
    }

    return possibleWords;
}

void printWords(set<string>& possibleWords) {
    for (string word : possibleWords) {
        cout << word << endl;
    }
}
