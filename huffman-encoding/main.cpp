#include "iostream"
#include "vector"
#include "unordered_map"
#include <algorithm>
#include "queue"

using namespace std;

struct Node {
    char value;
    int freq;
    Node *left;
    Node *right;

    Node() {
        this->value = '\0';
        this->freq = 0;
        left = nullptr;
        right = nullptr;
    }

    Node(char c, int f) {
        this->value = c;
        this->freq = f;
        left = nullptr;
        right = nullptr;
    }

    Node(int f, Node* l, Node *r) {
        this->value = '\0';
        this->freq = f;
        this->left = l;
        this->right = r;
    }
};

struct comp {
    bool operator()(Node *l, Node *r) {
        return l->freq > r->freq;
    }
};

/**
 * We defined 1 for go right and 0 for go left.
 */
class HuffmanCoding {
private:
    Node *huffmanTree;
    unordered_map<char, string> huffmanCode;

    void makeHuffmanTree(const string &s) {
        /* Find frequency of all character in string. */
        unordered_map<char, int> characterCount;
        for (char c : s) characterCount[c]++;

        /* Create Node for each character and push it in priority queue. */
        priority_queue<Node*, vector<Node*>, comp> queue;
        for (pair<char, int> pair : characterCount)
            queue.emplace(new Node(pair.first, pair.second));

        while (queue.size() > 1) {
            Node *l = queue.top(); queue.pop();
            Node *r = queue.top(); queue.pop();
            queue.emplace(new Node(l->freq + r->freq, l, r));
        }

        huffmanTree = queue.top();
    }

    void genHuffmanCode(Node *root, string s) {
        if (!root) return;

        if (!root->left && !root->right) {
            huffmanCode[root->value] = s;
        }

        genHuffmanCode(root->left, s + "0");
        genHuffmanCode(root->right, s + "1");
    }



public:
    HuffmanCoding() {
        huffmanTree = new Node;
    }

    string encode(const string &s) {
        this->makeHuffmanTree(s);
        this->genHuffmanCode(huffmanTree, "");

        string encodedBits;
        for (auto c : s) encodedBits += huffmanCode[c];
        return encodedBits;
    }

    string decode(const string &encodedBits) {
        if (!this->huffmanTree) return "";

        string decodedStr;
        Node *rootHold = this->huffmanTree;

        for (char c : encodedBits) {
            if (c == '0') rootHold = rootHold->left;
            if (c == '1') rootHold = rootHold->right;

            if (!rootHold->left && !rootHold->right) {
                decodedStr += rootHold->value;
                rootHold = this->huffmanTree;
            }
        }

        return decodedStr;
    }
};

int main() {
    auto *huffmanCoding = new HuffmanCoding;
    const string text = "Duong Hoang Dung";

    // Encode string with huffman encoding.
    string encodedBits = huffmanCoding->encode(text);
    string decodedStr = huffmanCoding->decode(encodedBits);

    cout << "Input: " << text << endl;
    cout << "Encoded bits: " << encodedBits << endl;
    cout << "Decoded text: " << decodedStr << endl;

    return 0;
}