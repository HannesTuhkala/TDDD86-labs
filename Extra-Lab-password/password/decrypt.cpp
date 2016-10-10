#include <iostream>
#include <chrono>
#include "Key.h"
#include <vector>

#define SUBSET_SIZE 4

using namespace std;

struct HashTable {
	Key* elements;
	unsigned size;
};

HashTable* hashTableInit(unsigned size) {
	HashTable* t = new HashTable;
	t->elements = new Key[size];
	t->size = size;
	return t;
}

void hashTableDestroy(HashTable* t) {
	delete t->elements;
	delete t;
}

int hashFunction(char key, HashTable* t) {
	// TODO implement (modulo?)
}

void hashTableInsert(Key key, HashTable* t) {
	// TODO implement
}

bool hashTableContains(Key key, HashTable* t) {
	// TODO implement
}

int numberOfSubsets(unsigned tableSize, unsigned subsetSize) {

}

/*
 * Checks whether this is the last subset to check.
 * For example, with a subset size of 3, and N = 5, 
 * it returns true iff currentSubset = [2, 3, 4]
 */
bool isLastSubset(vector<unsigned> currentSubset) {
	for (unsigned i = 0; i < SUBSET_SIZE; ++i) {
		if (currentSubset[i] != N - SUBSET_SIZE + i) return false;
	}
	return true;
}

//bool incrementCurrentSubset(vector<unsigned> currentSubset) {
//	for (unsigned i = SUBSET_SIZE - 1; i >= 0; --i) {
//		if ()
//	}
//}

int main(int argc, char* argv[]) {
	unsigned char buffer[C+1];     // temporary string buffer
	Key candidate = {{0}};         // a password candidate
	Key encrypted;                 // the encrypted password
	Key candenc;                   // the encrypted password candidate
	Key zero = {{0}};              // the all zero key
	Key T[N];                      // the table T
	
	if (argc != 2) {
		cout << "Usage:" << endl << argv[0] << " password < rand8.txt" << endl;
		return 1;
	}
	
	encrypted = KEYinit((unsigned char *) argv[1]);

	// read in table T
	for (int i{0}; i < N; ++i) {
		scanf("%s", buffer);
		T[i] = KEYinit(buffer);
	}

	auto begin = chrono::high_resolution_clock::now();

	int subsets = numberOfSubsets(N, SUBSET_SIZE);
 
	// tells us which rows of the table
	// we are choosing for this subset
	vector<unsigned> currentSubset;

	for (unsigned i = 0; i < SUBSET_SIZE; ++i) {
		currentSubset.push_back(i);
	}

	bool found = false;

	// increment currentSubset
	do {

	
	} while (!found && !isLastSubset(currentSubset));
	
	auto end = chrono::high_resolution_clock::now();
	cout << "Decryption took "
	   << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
	   << " seconds." << endl;
	return 0;
}
