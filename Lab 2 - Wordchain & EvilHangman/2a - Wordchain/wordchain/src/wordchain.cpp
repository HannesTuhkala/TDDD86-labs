#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <vector>
using namespace std;

const string alphabet = "abcdefghijklmnopqrstuvwxyz";

bool isCorrectWord(const string& possibleWord, const string& correctWord);
void checkAllPossibleWords(set<string>& dictionary, queue<stack<string>>& queueStack, stack<string>& firstStack, set<string>& usedWords);
void greetUser();
void printContents(stack<string>& stck);
bool isValidWord(set<string>& dictionary, string& word);
bool hasBeenUsed(set<string>& usedWords, string& word);
void emptyQueue(queue<stack<string>>& queueStack);
set<string> loadDictionary();

int main() {
    set<string> dictionary = loadDictionary();
    greetUser();

    string firstWord, secondWord;
    cin >> firstWord >> secondWord;

    set<string> usedWords;
    queue<stack<string>> queueStack;
    stack<string> wordStack;

    wordStack.push(firstWord);
    queueStack.push(wordStack);
    while (!queueStack.empty()) {
        stack<string> firstStack = queueStack.front();
        queueStack.pop();
        if (isCorrectWord(firstStack.top(), secondWord)) {
            cout << "Chain from " << firstWord << " to " << secondWord << endl;
            printContents(firstStack);
            emptyQueue(queueStack);
        } else {
            checkAllPossibleWords(dictionary, queueStack, firstStack, usedWords);
        }
    }

    cout << "Have a nice day!" << endl;
    return 0;
}

/*
 * Checks if a possible word equals the last desired word.
 */
bool isCorrectWord(const string& possibleWord, const string& correctWord) {
    return possibleWord == correctWord;
}

/*
 * Checks all the possible words with the dictionary and then adds them to the copyStack if they are valid.
 */
void checkAllPossibleWords(set<string>& dictionary, queue<stack<string>>& queueStack, stack<string>& firstStack, set<string>& usedWords) {
    string tempWord = firstStack.top();
    string copyTemp = tempWord;
    for (size_t position = 0; position < tempWord.size(); ++position) {
        for (size_t letter = 0; letter < alphabet.size(); ++letter) {
            tempWord = copyTemp.substr(0, position) + alphabet[letter] + tempWord.substr(position + 1, tempWord.size() - 1);
            if (isValidWord(dictionary, tempWord) && !hasBeenUsed(usedWords, tempWord)) {
                stack<string> copyStack = firstStack;
                copyStack.push(tempWord);
                queueStack.push(copyStack);
                usedWords.insert(tempWord);
            }
        }
    }
}

/*
 * Greets the user
 */
void greetUser() {
    cout << "Welcome to TDDD86 Word Chain." << endl
         << "If you give me two English words, I will transform the" << endl
         << "first into the second by changing one letter at a time." << endl << endl
         << "Please type two words: ";
}

bool hasBeenUsed(set<string>& usedWords, string& word) {
    return usedWords.count(word) == 1;
}

/*
 * Checks whether the possible word is in the dictionary.
 */
bool isValidWord(set<string>& dictionary, string& word) {
    return dictionary.count(word) == 1;
}

/*
 * Loads the dictionary.
 */
set<string> loadDictionary() {
    ifstream input;
    set<string> dictionary;
    input.open("dictionary.txt");
    string line;
    while(getline(input, line)) {
        dictionary.insert(line);
    }

    return dictionary;
}

/*
 * Prints the content of the stack that shows the correct 'way' to get from word1 to word2.
 */
void printContents(stack<string>& stck) {
    while (!stck.empty()){
        cout << stck.top() << " ";
        stck.pop();
    }
    cout << endl;
}

/*
 * Empties the queue to free the memory making the program a bit faster.
 */
void emptyQueue(queue<stack<string>>& queueStack) {
    while (!queueStack.empty()) {
        queueStack.pop();
    }
}
