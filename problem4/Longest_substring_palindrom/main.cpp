#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int p = 31;
const int M = 1e9 + 9;

auto getHash(int i, int j, vector<long long> &pref, vector<long long> &p_pow, int n)
{
    if (i < 0 || j > n) return 0LL;
    long long hash_ = (pref[j] - pref[i] + M) % M;
    hash_ = (hash_ * p_pow[n-i-1]) % M;
    return hash_;
}

string findLongestPalindrome(const string &s)
{
    int n = s.length();
    if (n <= 1) return s;

    int max_length = 1;
    int start = 0;

    string t = s;
    reverse(t.begin(), t.end());

    vector<long long> p_pow(n);
    p_pow[0] = 1;
    for(int i = 1; i < n; i++)
    {
        p_pow[i] = (p_pow[i-1] * p) % M;
    }

    vector<long long> pref_s(n + 1, 0);
    vector<long long> pref_t(n + 1, 0);

    // Racunamo hash vrijednosti svih prefiksa stringa i njegovog ekvivalenta sa obrnutim redosljedom slova
    for(int i = 0; i < n; i++)
    {
        pref_s[i + 1] = (pref_s[i] + (s[i] - 'a' + 1) * p_pow[i]) % M;
        pref_t[i + 1] = (pref_t[i] + (t[i] - 'a' + 1) * p_pow[i]) % M;
    }

    // Za palindrome neparne duzine (centar ze biti jedan karakter)
    for(int i = 1; i < n; i++)
    {
        int left = 0;
        int right = min(i, n - i - 1);

        while(left <= right)
        {
            int mid = (left + right) / 2;
            long long hash_1 = getHash(i - mid, i + 1, pref_s, p_pow, n);
            long long hash_2 = getHash(n - (i + mid) - 1, n - i, pref_t, p_pow, n);

            if(hash_1 == hash_2)
            {
                if(2 * mid + 1 > max_length)
                {
                    start = i - mid;
                    max_length = 2 * mid + 1;
                }
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }

    // Za palindrome parne duzine (centar ce biti dva uzastopna identicna karaktera)
    for(int i = 1; i < n - 1; i++)
    {
        if(s[i] != s[i + 1]) continue;

        int left = 0;
        int right = min(i, n - i - 2);

        while(left <= right)
        {
            int mid = (left + right) / 2;
            long long hash_1 = getHash(i - mid, i + 1, pref_s, p_pow, n);
            long long hash_2 = getHash(n - (i + mid + 2), n - i - 1, pref_t, p_pow, n);

            if(hash_1 == hash_2)
            {
                if(2 * mid + 2 > max_length)
                {
                    start = i - mid;
                    max_length = 2 * mid + 2;
                }
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }

    return s.substr(start, max_length);
}

int main()
{
    string input;
    cout << "Unesite string: ";
    cin>> input;
    string result=findLongestPalindrome(input);
    cout << "Najduzi palindromski podstring je: " << result << endl;
    return 0;
}

