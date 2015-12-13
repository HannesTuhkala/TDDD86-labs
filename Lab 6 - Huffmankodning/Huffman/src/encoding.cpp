#include "encoding.h"
#include <queue>
// TODO: include any other headers you need

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
	int byte;
	byte = input.get();

	while (byte != -1) {
		if (freqTable.count(byte) == 0) {
			freqTable.insert(pair<int,int>(byte, 1));
		} else {
			freqTable.at(byte)++;
		}
		byte = input.get();
	}

	freqTable.insert(pair<int,int>(PSEUDO_EOF, 1));
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
	std::priority_queue<HuffmanNode> queue;
	//push all character-frequency pairs to the queue.
	for (auto character : freqTable) {
		queue.push(HuffmanNode(character.first, character.second));
	}
	//start building the tree.

	//create two temporary nodes.
	HuffmanNode n1;
	HuffmanNode n2;
	//as long as there are two or more nodes in the queue, it means that
	//not all are yet in the same tree, so keep building it.
	while (queue.size() >= 2) {
		//pop the two values at the top of the queue and store in n1, n2.
		n1 = queue.top();
		queue.pop();
		n2 = queue.top();
		queue.pop();

		//sum their frequencies
		int freqSum = n1.count + n2.count;
		//create the parent node with the sum of it's children's frequencies
		//with n1 as left child (since it has the lowest frequency, as it was 
		//at the top of the queue) and n2 as right child
		HuffmanNode parent = HuffmanNode(NOT_A_CHAR, freqSum, new HuffmanNode(n1), new HuffmanNode(n2));
		//push the parent to the queue
		queue.push(parent);
	}
	return new HuffmanNode(queue.top());
}

void preOrder(HuffmanNode* currentNode, map<int, string>& encodingMap, std::string coding = std::string()) {
    if (currentNode->isLeaf()) {
        encodingMap.insert(make_pair(currentNode->character, coding));
    } else {
        preOrder(currentNode->zero, encodingMap, coding + "0");
        preOrder(currentNode->one, encodingMap, coding + "1");
    }
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    preOrder(encodingTree, encodingMap);

    return encodingMap;
}

void writeCode(string& code, obitstream& output) {
	for (size_t i = 0; i < code.size(); ++i) {
		if (code[i] == '1') {
			output.writeBit(1);
		} else {
			output.writeBit(0);
		}
	}
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
	int byte = input.get();
	while (byte != -1) {
		string code = encodingMap.at(byte);
		writeCode(code, output);
		byte = input.get();
	}
	string eofCode = encodingMap.at(PSEUDO_EOF);
	writeCode(eofCode, output);
}

int getCharacter(ibitstream& input, HuffmanNode* tree) {
	if (tree->isLeaf()) return tree->character;
	int bit = input.readBit();
	if (bit == 1) return getCharacter(input, tree->one);
	else return getCharacter(input, tree->zero);
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
	while (true) {
		int character = getCharacter(input, encodingTree);
		if (character == PSEUDO_EOF) return;
		output.put(character);
	}
}

writeHeader(const map<int, int>& freqTable, obitstream& output) {
    output.put('{');
    for (map<int, int>::const_iterator it = freqTable.begin(); it != freqTable.end(); ++it) {
        if (it != freqTable.begin()) {
            output.put(',');
            output.put(' ');
        }

        string key = to_string(it->first);
        for (int i = 0; i < key.size(); ++i) {
            output.put(key[i]);
        }

        output.put(':');

        string freq = to_string(it->second);
        for (int i = 0; i < freq.size(); ++i) {
            output.put(freq[i]);
        }
    }

    output.put('}');
}

void compress(istream& input, obitstream& output) {
	map<int, int> freqTable = buildFrequencyTable(input);
	HuffmanNode* encodingTree = buildEncodingTree(freqTable);
	map<int, string> encodingMap = buildEncodingMap(encodingTree);

    writeHeader(freqTable, output);
    input.clear();
    input.seekg(0, ios::beg);

    encodeData(input, encodingMap, output);
    freeTree(encodingTree);
}

map<int, int> readHeader(istream& input) {
    map<int, int> freqTable;
    // Gets the '{'
    input.get();
    char byte;

    // While the header doesn't end do..
    while ((byte = input.get()) != '}') {
        string key;

        // get each byte until it finds a ':'
        while (byte != ':') {
            key += string(1, byte);
            byte = input.get();
        }

        string freq;

        // get each byte until it finds a ',' or a '}'
        while ((byte = input.get()) != ',' && byte != '}') {
            freq += string(1, byte);
        }

        freqTable.insert(make_pair(atoi(key.c_str()), atoi(freq.c_str())));

        // we have to check here, and it is only true if we are at the last element of the header.
        if (byte == '}') {
            break;
        }

        // gets a whitespace ' '
        input.get();
    }
}

void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable = readHeader(input);
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);
    freeTree(encodingTree);
}

void freeTree(HuffmanNode* node) {
    // en version
    /*if (node->zero->isLeaf()) {
        delete node->zero;
    } else {
        freeTree(node->zero);
    }

    if (node->one->isLeaf()) {
        delete node->one;
    } else {
        freeTree(node->one);
    } */

    // en annan version
    if (node == nullptr) {
        return;
    } else if (node->isLeaf()) {
        delete node;
    } else {
        freeTree(node->zero);
        freeTree(node->one);
    }

    cout << "HEJHEJ" << endl;
    delete node;
    cout << "HEJHEJ2" << endl;
}


