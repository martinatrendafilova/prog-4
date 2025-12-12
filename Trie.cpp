#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    bool isWord;
    TrieNode* children[26];

    TrieNode() {
        isWord = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++)
            delete children[i];
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        TrieNode* node = root;

        for (char ch : word) {
            if (!isalpha(ch)) continue;
            ch = tolower(ch);
            int index = ch - 'a';

            if (node->children[index] == nullptr)
                node->children[index] = new TrieNode();

            node = node->children[index];
        }

        node->isWord = true;
    }

    bool search(const string& word) const {
        TrieNode* node = root;

        for (char ch : word) {
            if (!isalpha(ch)) continue;
            ch = tolower(ch);
            int index = ch - 'a';

            if (node->children[index] == nullptr)
                return false;

            node = node->children[index];
        }

        return node->isWord;
    }
};

int main() {
    Trie trie;
    ifstream file("words.txt");

    if (!file.is_open()) {
        cout << "Could not open!" << endl;
        return 1;
    }

    string word;
    int count = 0;

    while (getline(file, word)) {
        trie.insert(word);
        count++;
    }

    file.close();

    cout << "Number of words inserted: " << count << endl;

    cout << "music: " << trie.search("music") << endl;
    cout << "math: " << trie.search("math") << endl;
    cout << "laalala: " << trie.search("laalala") << endl;
    return 0;
}

