#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string digits;

    BigInt(string s = "0") { digits = s; }

    bool operator<(const BigInt &other) const {
        if (digits.size() != other.digits.size()) return digits.size() < other.digits.size();
        return digits < other.digits;
    }

    bool operator==(const BigInt &other) const { return digits == other.digits; }

    BigInt operator+(const BigInt &other) const {
        string sumStr;
        int carry = 0, i = digits.size() - 1, j = other.digits.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            int temp = carry;
            if (i >= 0) temp += digits[i--] - '0';
            if (j >= 0) temp += other.digits[j--] - '0';
            carry = temp / 10;
            sumStr.push_back(temp % 10 + '0');
        }
        reverse(sumStr.begin(), sumStr.end());
        return BigInt(sumStr);
    }

    BigInt operator-(const BigInt &other) const {
        string resStr;
        int borrow = 0, i = digits.size() - 1, j = other.digits.size() - 1;
        while (i >= 0) {
            int temp = digits[i--] - '0' - borrow - (j >= 0 ? other.digits[j--] - '0' : 0);
            if (temp < 0) { temp += 10; borrow = 1; } else borrow = 0;
            resStr.push_back(temp + '0');
        }
        while (resStr.size() > 1 && resStr.back() == '0') resStr.pop_back();
        reverse(resStr.begin(), resStr.end());
        return BigInt(resStr);
    }

    BigInt operator*(const BigInt &other) const {
        int n = digits.size(), m = other.digits.size();
        vector<int> product(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                product[i + j + 1] += (digits[i] - '0') * (other.digits[j] - '0');
            }
        }
        for (int k = n + m - 1; k > 0; k--) {
            product[k - 1] += product[k] / 10;
            product[k] %= 10;
        }
        string resStr;
        for (int x : product) if (!(resStr.empty() && x == 0)) resStr.push_back(x + '0');
        return BigInt(resStr.empty() ? "0" : resStr);
    }

    pair<BigInt, BigInt> divmod(const BigInt &other) const {
        if (other == BigInt("0")) return {BigInt("Error"), BigInt("Error")};
        string quotientStr, remainderStr;
        for (char ch : digits) {
            remainderStr.push_back(ch);
            while (remainderStr.size() > 1 && remainderStr[0] == '0') remainderStr.erase(0, 1);
            BigInt remainder(remainderStr);
            int cnt = 0;
            while (!(remainder < other)) {
                remainder = remainder - other;
                remainderStr = remainder == BigInt("0") ? "" : remainder.digits;
                cnt++;
            }
            quotientStr.push_back(cnt + '0');
        }
        size_t first = quotientStr.find_first_not_of('0');
        if (first != string::npos) quotientStr = quotientStr.substr(first);
        else quotientStr = "0";
        return {BigInt(quotientStr), BigInt(remainderStr.empty() ? "0" : remainderStr)};
    }

    BigInt operator/(const BigInt &other) const { return divmod(other).first; }
    BigInt operator%(const BigInt &other) const { return divmod(other).second; }
};

BigInt modPow(BigInt base, BigInt exponent, BigInt mod) {
    BigInt result("1");
    base = base % mod;
    while (!(exponent == BigInt("0"))) {
        if (!(exponent % BigInt("2") == BigInt("0"))) result = (result * base) % mod;
        base = (base * base) % mod;
        exponent = exponent / BigInt("2");
    }
    return result;
}

int main() {
    BigInt base("8");
    BigInt exp("17");
    BigInt mod("90");

    BigInt res = modPow(base, exp, mod);

    cout << res.digits << endl;

    return 0;
}
