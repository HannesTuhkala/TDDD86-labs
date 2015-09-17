#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <vector>
using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

void printContents(stack<string>& st);
set<string> loadDictionary();
bool isValidWord(set<string>& dictionary, string& word);
bool hasBeenUsed(set<string>& usedWords, string& word);
void emptyQueue(queue<stack<string>>& queueStack);
void wordChain(set<string>& dictionary, string& word1, string& word2);

int main() {
    set<string> dictionary = loadDictionary();
    cout << "Welcome to TDDD86 Word Chain." << endl
         << "If you give me two English words, I will transform the" << endl
         << "first into the second by changing one letter at a time." << endl
         << endl;

    cout << "Please type two words: ";

    string firstWord, secondWord;
    cin >> firstWord >> secondWord;

    wordChain(dictionary, firstWord, secondWord);

    cout << "Have a nice day!" << endl;
    return 0;
}

void wordChain(set<string>& dictionary, string& firstWord, string& secondWord) {
    set<string> usedWords;
    queue<stack<string>> queueStack;
    stack<string> wordStack;

    wordStack.push(firstWord);
    queueStack.push(wordStack);
    while (!queueStack.empty()) {
        stack<string> firstStack = queueStack.front();
        queueStack.pop();
        if (firstStack.top() == secondWord){
            printContents(firstStack);
            emptyQueue(queueStack);
        } else {
            string temp = firstStack.top();
            string copyTemp = temp;
            for (size_t position = 0; position < temp.size(); ++position) {
                for (size_t letter = 0; letter < alphabet.size(); ++letter) {
                    temp = copyTemp.substr(0, position) + alphabet[letter] + temp.substr(position + 1, temp.size() - 1);
                    if (isValidWord(dictionary, temp) && !hasBeenUsed(usedWords, temp)) {
                        stack<string> copyStack = firstStack;
                        copyStack.push(temp);
                        queueStack.push(copyStack);
                        usedWords.insert(temp);
                    }
                }
            }
        }
    }
}

bool hasBeenUsed(set<string>& usedWords, string& word){
    return usedWords.count(word) == 1;
}

bool isValidWord(set<string>& dictionary, string& word) {
    return dictionary.count(word) == 1;
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

void printContents(stack<string>& st){
    while (!st.empty()){
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

void emptyQueue(queue<stack<string>>& queueStack) {
    while (!queueStack.empty()) {
        queueStack.pop();
    }
}
