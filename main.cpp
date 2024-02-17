#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node {
    char data;
    unsigned freq;
    Node *left, *right;

    Node(char data, unsigned freq, Node* l = NULL, Node* r = NULL)
        : data(data), freq(freq), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

void print_codes(struct Node* root, string str) {
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    print_codes(root->left, str + "0");
    print_codes(root->right, str + "1");
}

void huffman_codes(map<char, int> freq_map) {
    struct Node *left, *right, *top;

    priority_queue<Node*, vector<Node*>, Compare> min_heap;

    for (auto i = freq_map.begin(); i != freq_map.end(); i++)
        min_heap.push(new Node(i->first, i->second));

    while (min_heap.size() != 1) {
        left = min_heap.top();
        min_heap.pop();

        right = min_heap.top();
        min_heap.pop();

        top = new Node('$', left->freq + right->freq, left, right);
        min_heap.push(top);
    }

    print_codes(min_heap.top(), "");
}

int main() {
    string s;
    cout << "Please enter your message: ";
    cin >> s;

    map<char, int> freq_map;
    for (char c : s)
        freq_map[c]++;

    huffman_codes(freq_map);
    return 0;
}
