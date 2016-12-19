/*
 * This is our implementation of encoding files using Huffmancoding.
 * By Malcolm Vigren (malvi108) and Hannes Tuhkala (hantu447).
 *
 */

#include "encoding.h"
#include <queue>

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
	int byte;
	byte = input.get();

    // continue until input end of input, byte == -1
	while (byte != -1) {
        /* if new character, insert it into the freqtable, otherwise
           increment that characer already in the table*/
		if (freqTable.count(byte) == 0) {
            freqTable.insert(pair<int, int>(byte, 1));
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
    HuffmanNode tempNode1;
    HuffmanNode tempNode2;

    /* as long as there are two or more nodes in the queue, it means that
       not all are yet in the same tree, so keep building it. */
	while (queue.size() >= 2) {
		//pop the two values at the top of the queue and store in n1, n2.
        tempNode1 = queue.top();
		queue.pop();
        tempNode2 = queue.top();
		queue.pop();

		//sum their frequencies
        int freqSum = tempNode1.count + tempNode2.count;
        /* create the parent node with the sum of it's children's frequencies
           with n1 as left child (since it has the lowest frequency, as it was
           at the top of the queue) and n2 as the right child.*/
        HuffmanNode parent = HuffmanNode(NOT_A_CHAR, freqSum, new HuffmanNode(tempNode1), new HuffmanNode(tempNode2));

        //push the parent to the queue
		queue.push(parent);
	}

    return new HuffmanNode(queue.top());
}

void preOrder(HuffmanNode* currentNode, map<int, string>& encodingMap, std::string coding = std::string()) {
    // if leaf, insert the current coding along with the character into the encodingmap.
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
        (code[i] == '1') ? output.writeBit(1) : output.writeBit(0);
	}
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
	int byte = input.get();

    // continue until input end of input, byte == -1
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
    return (bit == 1) ? getCharacter(input, tree->one) : getCharacter(input, tree->zero);
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
	while (true) {
        int character = getCharacter(input, encodingTree);
        if (character == NOT_A_CHAR || input.tellg() == -1) return;

		output.put(character);
	}
}

HuffmanNode* decodeHeader(ibitstream& input) {
    if (input.readBit() == 1) {
        return new HuffmanNode(input.get(), 2, nullptr, nullptr);
    } else {
        HuffmanNode* zero = decodeHeader(input);
        HuffmanNode* one = decodeHeader(input);
        return new HuffmanNode(NOT_A_CHAR, 5, zero, one);
    }
}

HuffmanNode* readHeader(ibitstream& input) {
    return decodeHeader(input);
}

void encodeHeader(HuffmanNode* node, obitstream& output) {
    if (node->isLeaf()) {
        output.writeBit(1);
        output.put(node->character);
    } else {
        output.writeBit(0);
        encodeHeader(node->zero, output);
        encodeHeader(node->one, output);
    }
}

void writeHeader(HuffmanNode* encodingTree, obitstream& output) {
    encodeHeader(encodingTree, output);
}

void compress(istream& input, obitstream& output) {
	map<int, int> freqTable = buildFrequencyTable(input);
	HuffmanNode* encodingTree = buildEncodingTree(freqTable);
	map<int, string> encodingMap = buildEncodingMap(encodingTree);

    writeHeader(encodingTree, output);
    input.clear();
    input.seekg(0, ios::beg);

    encodeData(input, encodingMap, output);
    freeTree(encodingTree);
}

void decompress(ibitstream& input, ostream& output) {
    HuffmanNode* encodingTree = readHeader(input);
    decodeData(input, encodingTree, output);
    freeTree(encodingTree);
}

void freeTree(HuffmanNode* node) {
    if (node == nullptr) {
        return;
    } else {
        freeTree(node->zero);
        freeTree(node->one);
    }

    delete node;
}


