#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string value;

    BigInt(string s = "0") : value(s) {}

    bool isLess(BigInt other) {
        if (value.length() != other.value.length())
            return value.length() < other.value.length();
        return value < other.value;
    }

    BigInt operator+(BigInt other) {
        string result = "";
        int i = value.size() - 1, j = other.value.size() - 1, carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? value[i--] - '0' : 0;
            int digit2 = (j >= 0) ? other.value[j--] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            result += (char)(sum % 10 + '0');
            carry = sum / 10;
        }
        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    BigInt operator*(BigInt other) {
        int n = value.size(), m = other.value.size();
        vector<int> res(n + m, 0);

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (value[i] - '0') * (other.value[j] - '0');
                int sum = mul + res[i + j + 1];
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }

        string s = "";
        for (int x : res) if (!(s.empty() && x == 0)) s += (char)(x + '0');
        return s.empty() ? BigInt("0") : BigInt(s);
    }
};

struct Compare {
    bool operator()(pair<BigInt, BigInt> a, pair<BigInt, BigInt> b) {
        return b.first.isLess(a.first);
    }
};

void generatePrimes(int n) {
    priority_queue<pair<BigInt, BigInt>, vector<pair<BigInt, BigInt>>, Compare> pq;

    cout << "2 ";
    pq.push({BigInt("4"), BigInt("2")});

    for (int i = 3; i <= n; i++) {
        BigInt current(to_string(i));

        if (current.isLess(pq.top().first)) {
            cout << i << " ";
            pq.push({current * current, current});
        } else {
            while (!current.isLess(pq.top().first)) {
                pair<BigInt, BigInt> top = pq.top();
                pq.pop();
                BigInt nextMultiple = top.first;
                BigInt prime = top.second;
                pq.push({nextMultiple + prime, prime});
            }
        }
    }
    cout << endl;
}

int main() {
    int n;
    cin>>n;
    generatePrimes(n);
    return 0;
}