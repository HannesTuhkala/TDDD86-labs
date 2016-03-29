#include <iostream>
#include <chrono>
#include "Key.h"

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
	// TODO hur många delmängder av storlek subsetSize kan man 
	// bilda ur en tabell med storlek tableSize???
}

int main(int argc, char* argv[]) {
	// TODO Vi kan nog behöva ändra de här
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

	//HashTable* t = hashTableInit();
	// TODO här kommer allt sökande
	
	auto end = chrono::high_resolution_clock::now();
	cout << "Decryption took "
	   << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
	   << " seconds." << endl;
	return 0;
}
