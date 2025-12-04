#include <bits/stdc++.h>
using namespace std;

class Result {
public:
    const long long BASE = 29;
    const long long mod = 1000000007;

    vector<long long> power;
    vector<long long> hashPrefix;
    int length;

    long long hashRange(int start, int end) {
        long long h = (hashPrefix[end] - hashPrefix[start] + mod) % mod;
        h = (h * power[length - start - 1]) % mod;
        return h;
    }

    int hasDuplicate(int subLen) {
        unordered_set<long long> seenHashes;
        for (int i = 0; i + subLen <= length; i++) {
            long long h = hashRange(i, i + subLen);
            if (seenHashes.count(h)) return i;
            seenHashes.insert(h);
        }
        return -1;
    }

    string findLongestDuplicate(const string& str) {
        length = str.size();
        power.assign(length + 1, 1);
        hashPrefix.assign(length + 1, 0);

        for (int i = 1; i <= length; i++)
            power[i] = (power[i - 1] * BASE) % mod;

        for (int i = 0; i < length; i++)
            hashPrefix[i + 1] = (hashPrefix[i] + (str[i] - 'a' + 1) * power[i]) % mod;

        int low = 1, high = length;
        int bestLength = 0, bestIndex = -1;

        while (low <= high) {
            int mid = (low + high) / 2;
            int pos = hasDuplicate(mid);

            if (pos != -1) {
                bestLength = mid;
                bestIndex = pos;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (bestIndex == -1) return "";
        return str.substr(bestIndex, bestLength);
    }
};

int main() {
    string s;
    cin >> s;

    Result res;
    string answer = res.findLongestDuplicate(s);

    if (answer.empty())
        cout << "Nema";
    else
        cout << answer << endl;

    return 0;
}

