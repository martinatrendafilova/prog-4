#include <iostream>
#include <cstring>
using namespace std;

class GermanString {
private:
    char* content;
    int length;
    char* prefix;

public:
    GermanString() {
        content = nullptr;
        prefix = nullptr;
        length = 0;
    }

    GermanString(const char* str) {
        if (!str) {
            content = nullptr;
            prefix = nullptr;
            length = 0;
            return;
        }

        length = strlen(str);
        content = new char[length + 1];

        for (int i = 0; i < length; i++)
            content[i] = str[i];
        content[length] = '\0';

        if (length <= 12) {
            prefix = new char[5];
            for (int i = 0; i < min(4, length); i++)
                prefix[i] = str[i];
            prefix[min(4, length)] = '\0';
        } else {
            prefix = nullptr;
        }
    }

    GermanString(const GermanString& other) {
        length = other.length;
        content = new char[length + 1];
        for (int i = 0; i < length; i++)
            content[i] = other.content[i];
        content[length] = '\0';

        if (length <= 12 && other.prefix) {
            prefix = new char[5];
            for (int i = 0; i < min(4, length); i++)
                prefix[i] = other.prefix[i];
            prefix[min(4, length)] = '\0';
        } else {
            prefix = nullptr;
        }
    }

    GermanString& operator=(const GermanString& other) {
        if (this == &other) return *this;

        delete[] content;
        delete[] prefix;

        length = other.length;
        content = new char[length + 1];
        for (int i = 0; i < length; i++)
            content[i] = other.content[i];
        content[length] = '\0';

        if (length <= 12 && other.prefix) {
            prefix = new char[5];
            for (int i = 0; i < min(4, length); i++)
                prefix[i] = other.prefix[i];
            prefix[min(4, length)] = '\0';
        } else {
            prefix = nullptr;
        }

        return *this;
    }

    ~GermanString() {
        delete[] content;
        delete[] prefix;
    }

    int size_of() const {
        return length;
    }

    void print() const {
        for (int i = 0; i < length; i++)
            cout << content[i];
        cout << endl;
    }

    void empty() {
        delete[] content;
        content = nullptr;
        length = 0;
        delete[] prefix;
        prefix = nullptr;
    }

    char& operator[](int index) { return content[index]; }
    const char& operator[](int index) const { return content[index]; }

    int find(char c) const {
        for (int i = 0; i < length; i++)
            if (content[i] == c) return i;
        return -1;
    }
};

GermanString operator+(const GermanString& a, const GermanString& b) {
    int newLength = a.size_of() + b.size_of();
    char* buffer = new char[newLength + 1];

    for (int i = 0; i < a.size_of(); i++)
        buffer[i] = a[i];
    for (int i = 0; i < b.size_of(); i++)
        buffer[a.size_of() + i] = b[i];

    buffer[newLength] = '\0';

    GermanString result(buffer);
    delete[] buffer;
    return result;
}

int main() {
    GermanString x("alalalala");
    GermanString y("papapapap");
    cout << x[2] << endl;
    x[2] = 'x';
    cout << x[2] << endl;
    cout << x.size_of() << endl;
    x.print();

    cout << x.find('a') << endl;

    GermanString z = x + y;
    z.print();

    return 0;
}