#include <bits/stdc++.h>
using namespace std;

vector<int> rabin(const string &pat, const string &txt) {
    long long B = 31, M = 1000000009;
    int n = txt.size(), m = pat.size();

    long long pHash = 0, tHash = 0, power = 1;

    for (int i = 1; i < m; i++)
        power = (power * B) % M;

    for (int i = 0; i < m; i++) {
        pHash = (pHash * B + (pat[i] - 'a' + 1)) % M;
        tHash = (tHash * B + (txt[i] - 'a' + 1)) % M;
    }

    vector<int> ans;

    for (int i = 0; i <= n - m; i++) {
        if (pHash == tHash)
            ans.push_back(i);

        if (i + m < n) {
            tHash = (tHash - (txt[i] - 'a' + 1) * power) % M;
            tHash = (tHash + M) % M;
            tHash = (tHash * B + (txt[i + m] - 'a' + 1)) % M;
        }
    }

    return ans;
}

int main() {
    int x;
    cin >> x;

    while (x--) {
        string text, pat;
        cin >> text >> pat;

        vector<int> out = rabin(pat, text);

        if (out.empty()) {
            cout << "Not found\n";
        } else {
            cout << out.size() << "\n";
            for (int x : out) cout << x + 1 << " ";
            cout << "\n";
        }

        if (x) cout << "\n";
    }
}