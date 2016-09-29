/*
 * This is an evil implementation of the hangman game.
 * By Malcolm Vigren (malvi108) and Hannes Tuhklala (hantu447).
 *
 */


#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <array>
#include <map>
#include <stack>
#include <typeinfo>

using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

set<string> loadDictionary();
array<int, 2> findWordLengths(set<string>& dictionary);
void hangMan(set<string>& dictionary, int& wordLength, int& guesses, bool& debug);
set<string> narrowDownDictionary(set<string> &dictionary, stack<string> words);
set<string> narrowDictionaryBasedOnWordLength(set<string> &dictionary, int &wordLength);
void printPossibleWords(set<string> &possibleWords);
void printWordStatus(int& guessesLeft, string& currentWord, set<char> usedLetters);
void printGuessStatus(bool guessCorrect);
map<string, stack<string>> partitionWords(char& letter, set<string>& dictionary, string currentWord);
pair<string, stack<string>> getLargestPartition(map<string, stack<string>> partitions);
string createEmptyWord(int& length);
void inputLetter(char& letter, set<char>& guessedLetters);
string getPrintableUsedLetters(set<char> &usedLetters);
bool matches(string& word, string& wordComparison);
void printStack(stack<string> st);
bool allLettersGuessed(string word);
void inputInfo(int& length, int& guesses, bool& debug, array<int, 2> wordLengths);

int main() {
    set<string> dictionary = loadDictionary();
    cout << "Welcome to Hangman." << endl;

    int wordLength;
    int guesses;
    bool debug;

    array<int, 2> wordLengths = findWordLengths(dictionary);

    inputInfo(wordLength, guesses, debug, wordLengths);

    hangMan(dictionary, wordLength, guesses, debug);

    return 0;
}

void inputInfo(int& length, int& guesses, bool& debug, array<int, 2> wordLengths){
    bool validWordLength = false;
    do {
        if (validWordLength) {
            cout << "The word length has to be between " << wordLengths[0] << " and " << wordLengths[1] << "." << endl;
        }
        cout << "Word length? ";
        cin >> length;
        validWordLength = (!(length >= wordLengths.at(0) && length <= wordLengths.at(1)));
    } while (validWordLength);

    cout << "Number of guesses? ";

    while (cin >> guesses && guesses <= 0);

    cout << "Debug (y/n)? ";

    char ans;
    cin >> ans;
    debug = ans == 'y';
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
    string word = createEmptyWord(wordLength);
    dictionary = narrowDictionaryBasedOnWordLength(dictionary, wordLength);
    bool continueGame = true;
    set<char> usedLetters;
    while (continueGame){
        if (debug) printPossibleWords(dictionary);
        printWordStatus(guesses, word, usedLetters);
        cout << "Guess a letter: ";
        char letter;
        inputLetter(letter, usedLetters);
        usedLetters.insert(letter);
        map<string, stack<string>> partitions = partitionWords(letter, dictionary, word);
        pair<string, stack<string>> largestPartition = getLargestPartition(partitions);
        if (largestPartition.first == word){ //this means that the user guessed incorrectly
            printGuessStatus(false);
            guesses--;
        } else {
            printGuessStatus(true);
        }
        word = largestPartition.first;
        dictionary = narrowDownDictionary(dictionary, largestPartition.second);
        if (guesses == 1){
            cout << "Final guess!" << endl;
        }
        if (guesses == 0){
            cout << "HAHA! YOU LOST!" << endl;
            cout << "The word was in fact: " << largestPartition.second.top() << endl;
            continueGame = false;
        } else if (allLettersGuessed(word)){
            cout << "Wow... you actually won..." << endl
                << "The word was really \"" << word << "\"" << endl;

            continueGame = false;
        }
    }
}

bool allLettersGuessed(string word){
    for (char c : word){
        if (c == '-') return false;
    }
    return true;
}

pair<string, stack<string>> getLargestPartition(map<string, stack<string>> partitions){
    pair<string, stack<string>> largest;
    for (auto& currentPair : partitions) {
        if (currentPair.second.size() > largest.second.size()) {
            largest = currentPair;
        }
    }
    return largest;
}

map<string, stack<string>> partitionWords(char& letter, set<string>& dictionary, string currentWord){
    map<string, stack<string>> stackMap;
    for (string word : dictionary){
        stack<string> currentStack;
        string temp;
        for (unsigned int position = 0; position < word.length(); ++position) {
            if (word[position] == letter && (currentWord[position] == '-' || currentWord[position] == letter)) {
                temp += letter;
            } else if (currentWord[position] != letter){
                temp += currentWord[position];
            } else {
                temp += '-';
            }
        }
        //cout << temp << endl;
        if (stackMap.count(temp) == 0) {
            currentStack.push(word);
            stackMap.insert(pair<string, stack<string>>(temp, currentStack));
        } else {
            stackMap.at(temp).push(word);
        }
    }
    return stackMap;
}

void printStack(stack<string> st){
    while (!st.empty()){
        cout << st.top() << endl;
        st.pop();
    }
}

void inputLetter(char& letter, set<char>& usedLetters){
    bool incorrectInput = true;
    string temp;
    while (incorrectInput) {
        cin >> temp;
        if (temp.length() != 1 || alphabet.find(temp[0]) == -1){
            cout << "Invalid letter. Try again: ";
        } else if (usedLetters.count(temp[0]) == 1) {
            cout << "Letter already used. Try again: ";
        } else {
            incorrectInput = false;
            letter = temp[0];
        }
    }
}

string createEmptyWord(int& length){
    return string(length, '-');
}

void printGuessStatus(bool guessCorrect){
    if (guessCorrect){
        cout << "Guess correct!" << endl;
    } else {
        cout << "WRONG!" << endl;
    }
}

void printWordStatus(int& guessesLeft, string& currentWord, set<char> usedLetters){
    cout << "Guesses left: " << guessesLeft << endl
         << "Used letters: " << getPrintableUsedLetters(usedLetters) << endl
         << "Current word: " << currentWord << endl << endl;
}

string getPrintableUsedLetters(set<char>& usedLetters){
    if (usedLetters.empty()) return "None";
    string result = "";
    for (char letter : usedLetters){
        result += letter;
        result += ", ";
    }
    return result.substr(0, result.length() - 2);
}

set<string> narrowDictionaryBasedOnWordLength(set<string>& dictionary, int& wordLength){
    set<string> newDictionary;
    for (string word : dictionary) {
        if (word.length() == wordLength) {
            newDictionary.insert(word);
        }
    }
    return newDictionary;
}

set<string> narrowDownDictionary(set<string>& dictionary, stack<string> words) {
    set<string> newDictionary;
    while(!words.empty()){
        newDictionary.insert(words.top());
        words.pop();
    }
    return newDictionary;
}

bool matches(string& word, string& wordComparison){
    for (size_t i = 0; i < word.length(); ++i){
        if (word[i] != wordComparison[i] && wordComparison[i] != '-'){
            return false;
        }
    }
    return true;
}

void printPossibleWords(set<string>& possibleWords) {
    for (string word : possibleWords) {
        cout << word << endl;
    }
}
