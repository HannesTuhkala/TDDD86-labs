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
	//Det som du förmodligen fastnade på (det gjorde jag också) var
	//att du gjorde en priority queue med pekare. Detta funkar inte 
	//eftersom den kommer då att sortera skiten efter minnesadresser.
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
		//cout << "Första noden: " << n1->character << ": " << n1->count << endl;
		//cout << "Andra noden: " << n2->character << ": " << n2->count << endl;
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

void preOrder(HuffmanNode* node, map<int, string>& encodingMap, std::string coding = std::string()) {
    if (!node->isLeaf() && node != nullptr) {
        cout << node->character << " " << node->count << endl;
        preOrder(node->zero, encodingMap, coding + "0");
        encodingMap.insert(make_pair(node->zero->character, coding + "0"));
        //string temp = coding + "1";
        preOrder(node->one, encodingMap, coding + "1");
        encodingMap.insert(make_pair(node->one->character, coding + "1"));
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

void compress(istream& input, obitstream& output) {
	map<int, int> freqTable = buildFrequencyTable(input);
	HuffmanNode* encodingTree = buildEncodingTree(freqTable);
	map<int, string> encodingMap = buildEncodingMap(encodingTree);
	
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
