#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1000000007; 
const long long BASE = 31;

void solve(const string& s, const string& dobri_losi, int k) {
    
    int n = s.size();

    unordered_set<long long> dobri;

    vector<long long> powers(n + 1);
    powers[0] = 1;
    for (int i = 1; i <= n; i++) {
        powers[i] = (powers[i - 1] * BASE) % MOD;
    }

    for (int i = 0; i < n; i++) {
        long long current_hash = 0;
        int losi = 0;

        for (int j = i; j < n; j++) {
            
            int index = s[j] - 'a';
            
            if (dobri_losi[index] == '0') {
                losi++;
            }

            if (losi > k) {
                break;
            }

            long long char_val = s[j] - 'a' + 1; 
            int length_of_substring = j - i; 

            current_hash = (current_hash + char_val * powers[length_of_substring]) % MOD;
            
            if (current_hash < 0) current_hash += MOD;

            dobri.insert(current_hash);
        }
    }

    cout << dobri.size() << endl;
}

int main() {
    string s;
    string dobri_losi;
    int k;
    
    cin >> s;
    cin >> dobri_losi;
    cin >> k;

    solve(s, dobri_losi, k);

    return 0;
}