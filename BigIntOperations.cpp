#include <bits/stdc++.h>
using namespace std;

class BigInt
{
public:
    string value;

    BigInt(string s = "0")
    {
        int i = 0;
        while (i + 1 < s.size() && s[i] == '0') i++;
        value = s.substr(i);
    }

    bool isLess(const BigInt& other) const
    {
        if (value.length() != other.value.length())
            return value.length() < other.value.length();
        return value < other.value;
    }

    BigInt operator+(const BigInt& other) const
    {
        string res = "";
        int i = value.length() - 1;
        int j = other.value.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry)
        {
            int v1 = (i >= 0) ? value[i--] - '0' : 0;
            int v2 = (j >= 0) ? other.value[j--] - '0' : 0;
            int sum = v1 + v2 + carry;
            res += char(sum % 10 + '0');
            carry = sum / 10;
        }

        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator-(const BigInt& other) const
    {
        string res = "";
        int i = value.length() - 1;
        int j = other.value.length() - 1;
        int borrow = 0;

        while (i >= 0)
        {
            int v1 = value[i--] - '0';
            int v2 = (j >= 0) ? other.value[j--] - '0' : 0;
            int sub = v1 - v2 - borrow;
            if (sub < 0)
            {
                sub += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            res += char(sub + '0');
        }

        while (res.size() > 1 && res.back() == '0')
            res.pop_back();

        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator*(const BigInt& other) const
    {
        int n = value.size();
        int m = other.value.size();
        vector<int> res(n + m, 0);

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                int mul = (value[i] - '0') * (other.value[j] - '0');
                int sum = mul + res[i + j + 1];
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }

        string s = "";
        for (int x : res)
        {
            if (!(s.empty() && x == 0))
                s += char(x + '0');
        }

        return s.empty() ? BigInt("0") : BigInt(s);
    }

    BigInt operator/(const BigInt& other) const
    {
        if (other.value == "0")
            return BigInt("Error");

        string res = "";
        string currentStr = "";

        for (char c : value)
        {
            currentStr += c;
            while (currentStr.size() > 1 && currentStr[0] == '0')
                currentStr.erase(0, 1);

            BigInt current(currentStr);
            int count = 0;

            while (!current.isLess(other))
            {
                current = current - other;
                currentStr = current.value;
                count++;
            }

            res += char(count + '0');
        }

        size_t pos = res.find_first_not_of('0');
        if (pos == string::npos)
            return BigInt("0");

        return BigInt(res.substr(pos));
    }
};

int main()
{
    BigInt a("123456789123456789");
    BigInt b("987654321");

    cout << (a + b).value << endl;
    cout << (a - b).value << endl;
    cout << (a * b).value << endl;
    cout << (a / b).value << endl;

    return 0;
}
