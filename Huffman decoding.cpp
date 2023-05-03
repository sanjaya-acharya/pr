#include <iostream>
#include <string>

using namespace std;

class Node { // Instance of this class represents a node of the huffman tree.
public:
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char value, int frequency) { // Constructor
        data = value; // if node is leaf there will be a character in attribute 'data' if node is not leaf 'data' will have '\0'.
        freq = frequency; // This is not actually necessary for decoding algorithm but in huffman tree we used to write frequency in non-leaf nodes.
        // frequency makes it easier to choose which nodes to merge while designing a huffman tree.
        left = NULL;
        right = NULL;
    }
};

string decodeMessage (string encodedMsg, string decodedMsg, Node* currNode, Node* rootNode) {
    if (currNode->left == NULL && currNode-> right == NULL) { // This represent the current node is a leaf node.
        decodedMsg += currNode->data; // saving the character in decoded message.
        return decodeMessage(encodedMsg, decodedMsg, rootNode, rootNode); // here we return rootNode as currentNode to restart iteration from root.
    }

    if (encodedMsg == "") { // At end of the encoded string, return decoded message.
        return decodedMsg;
    }

    char currBit = encodedMsg.front(); // Taking 1st bit from encoded string to test where to move.
    encodedMsg.erase(0, 1); // Removing the 1st bit from string to make recursion easier.

    if (currBit == '0') { // if current bit is 0, move towards left child.
        return decodeMessage(encodedMsg, decodedMsg, currNode->left, rootNode);
    } else { // if current bit is 1, move towards right child
        return decodeMessage(encodedMsg, decodedMsg, currNode->right, rootNode);
    }

}

int main () {
    Node* root = new Node('\0', 30);
    root->left = new Node('\0', 17);
    root->right = new Node('\0', 13);
    root->left->left = new Node('\0', 7);
    root->left->right = new Node('\0', 10);
    root->right->left = new Node('E', 6);
    root->right->right = new Node('D', 7);
    root->left->left->left = new Node('C', 3);
    root->left->left->right = new Node('F', 4);
    root->left->right->left = new Node('A', 5);
    root->left->right->right = new Node('B', 5);
    // This is a huffman tree for string "EDDDFFCEDBACFEDAEBAFDCBEBDABEA"

    string encMsg = "10111111001001000101101101000000110110101001101000111000011100111101001110010";

    string decMsg = decodeMessage(encMsg, "" , root, root);

    cout << "Decoded Message is : " << decMsg << endl;

    return 0;
}
