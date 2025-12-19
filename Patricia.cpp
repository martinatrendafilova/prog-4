#include <bits/stdc++.h>
using namespace std;

string sanitize_word(const string& input) {
    string result;
    for (char ch : input) {
        if (isalpha(ch)) result += tolower(ch);
    }
    return result;
}

struct Node {
    string value;
    bool isEnd;
    vector<Node*> branches;

    Node(const string& val = "") : value(val), isEnd(false), branches(26, nullptr) {}

    ~Node() {
        for (Node* branch : branches) delete branch;
    }
};

class Patricia {
private:
    Node* rootNode;

    int char_to_idx(char ch) const { return ch - 'a'; }

    int shared_prefix(const string& a, const string& b) const {
        int i = 0;
        while (i < a.size() && i < b.size() && a[i] == b[i]) i++;
        return i;
    }

public:
    Patricia() { rootNode = new Node(); }
    ~Patricia() { delete rootNode; }

    void insert(const string& word) {
        string w = sanitize_word(word);
        if (w.empty()) return;

        Node* current = rootNode;
        string remainder = w;

        while (!remainder.empty()) {
            int idx = char_to_idx(remainder[0]);
            Node* child = current->branches[idx];

            if (!child) {
                current->branches[idx] = new Node(remainder);
                current->branches[idx]->isEnd = true;
                return;
            }

            int prefix_len = shared_prefix(remainder, child->value);

            if (prefix_len == child->value.size()) {
                remainder = remainder.substr(prefix_len);
                current = child;
            } else {
                string common = child->value.substr(0, prefix_len);
                Node* splitNode = new Node(common);

                string oldSuffix = child->value.substr(prefix_len);
                int oldIdx = char_to_idx(oldSuffix[0]);
                child->value = oldSuffix;
                splitNode->branches[oldIdx] = child;

                string newSuffix = remainder.substr(prefix_len);
                if (newSuffix.empty()) splitNode->isEnd = true;
                else {
                    int newIdx = char_to_idx(newSuffix[0]);
                    Node* newNode = new Node(newSuffix);
                    newNode->isEnd = true;
                    splitNode->branches[newIdx] = newNode;
                }

                current->branches[idx] = splitNode;
                return;
            }
        }

        current->isEnd = true;
    }

    bool search(const string& word) const {
        string w = sanitize_word(word);
        if (w.empty()) return false;

        Node* current = rootNode;
        string remainder = w;

        while (!remainder.empty()) {
            int idx = char_to_idx(remainder[0]);
            Node* child = current->branches[idx];
            if (!child) return false;

            int prefix_len = shared_prefix(remainder, child->value);

            if (prefix_len < remainder.size() && prefix_len < child->value.size()) return false;

            if (prefix_len == child->value.size()) {
                remainder = remainder.substr(prefix_len);
                current = child;
            } else if (prefix_len == remainder.size()) {
                return true;
            } else return false;
        }

        return current->isEnd;
    }
};

int main() {
    Patricia trie;
    ifstream file("words_eng.txt");
    int totalWords = 0;

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
    } else {
        string line;
        while (getline(file, line)) {
            trie.insert(line);
            totalWords++;
        }
        file.close();
    }

    cout << totalWords << endl;
    cout << trie.search("apple") << endl;
    cout << trie.search("banana") << endl;
    cout << trie.search("orange") << endl;
    cout << trie.search("aaa") << endl;
    cout << trie.search("berry") << endl;
    cout << trie.search("tomato") << endl;

    return 0;
}
