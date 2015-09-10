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
set<string> loadDictionary(string file);
bool isValidWord(set<string> &dictionary, string word);
bool hasBeenUsed(vector<string>& usedWords, string word);

int main() {
    set<string> dictionary = loadDictionary("dictionary.txt");
    cout << "Welcome to TDDD86 Word Chain." << endl
         << "If you give me two English words, I will transform the" << endl
         << "first into the second by changing one letter at a time." << endl
         << endl;

    cout << "Please type two words: ";

    string firstWord, secondWord;
    cin >> firstWord >> secondWord;
    vector<string> usedWords;
    queue<stack<string>> myrko;
    stack<string> wordStack;

    wordStack.push(firstWord);
    myrko.push(wordStack);
    while (!myrko.empty()) {
        stack<string> st = myrko.front();
        myrko.pop();
        if (st.top() == secondWord){
            printContents(st);
        } else {
            string mumbojumbo = st.top();
            for (size_t i = 0; i < mumbojumbo.size(); ++i) {
                for (size_t letter = 0; letter < alphabet.size(); ++letter) {
                    mumbojumbo = mumbojumbo.substr(0, i) + alphabet[letter] + mumbojumbo.substr(i + 1, mumbojumbo.size() - 1);
                    if (isValidWord(dictionary, mumbojumbo) && !hasBeenUsed(usedWords, mumbojumbo)) {
                        stack<string> copy = st;
                        copy.push(mumbojumbo);
                        myrko.push(copy);
                        usedWords.push_back(mumbojumbo);
                    }
                }
            }
        }
    }

    return 0;
}

bool hasBeenUsed(vector<string>& usedWords, string word){
    for (auto index = usedWords.begin(); index != usedWords.end(); ++index) {
        if (*index == word) {
            return true;
        }
    }

    return false;
}

bool isValidWord(set<string>& dictionary, string word) {
    return dictionary.count(word) == 1;
}

set<string> loadDictionary(string file){
    ifstream input;
    set<string> dictionary;
    input.open(file);
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
}
