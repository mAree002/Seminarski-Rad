#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

const long long M = 1e9 + 9;
const int p = 31;

long long compute_hash(const string &s)
{
    long long hash_ = 0;
    for (char c : s)
    {
        hash_ = (hash_ * p + (c - 'A' + 1)) % M;
    }
    return hash_;
}

long long compute_hash_rotated(long long prev_hash, char first_char, long long pow)
{
    return ((prev_hash - (first_char - 'A' + 1) * pow  + M) % M * p + (first_char - 'A' + 1)) % M;
}

int findMaxCyclicOccurrenses(const string &s, int m)
{
    int n = s.length();
    if (m > n) return 0;

    map<long long, pair<int, long long>> hashMap;

    long long pow = 1;
    for (int i = 0; i < m - 1; i++)
    {
        pow = (pow * p) % M;
    }

    string current_string = s.substr(0, m);
    long long current_hash = compute_hash(current_string);
    hashMap[current_hash].first++;
    hashMap[current_hash].second = compute_hash_rotated(current_hash, current_string[0], pow);

    for (int i = 1; i <= n - m; i++)
    {
        current_hash = ((current_hash - ((s[i - 1] - 'A' + 1) * pow % M) + M) % M * p + (s[i + m - 1] - 'A' + 1)) % M;
        hashMap[current_hash].first++;
        hashMap[current_hash].second = compute_hash_rotated(current_hash, s[i], pow);
    }
    int maxOccurrences = 0;
    for (const auto &entry : hashMap)
    {
        long long startHash = entry.first;
        long long currentHash = startHash;
        int totalOccurrences = 0;
        unordered_map<long long, bool> visited;

        while (!visited[currentHash] && hashMap.count(currentHash))
        {
            visited[currentHash] = true;
            totalOccurrences += hashMap[currentHash].first;

            currentHash = hashMap[currentHash].second;

            if (currentHash == startHash)
            {
                maxOccurrences = max(maxOccurrences, totalOccurrences);
                break;
            }
        }
    }

    return maxOccurrences;
}

int main()
{
    string s1 = "BABABBAAB";
    int m1 = 3;
    cout << "Test 1: " << findMaxCyclicOccurrenses(s1, m1) << endl;

    string s2 = "ABAABAABAABAAAAA";
    int m2 = 5;
    cout << "Test 2: " << findMaxCyclicOccurrenses(s2, m2) << endl;

    return 0;
}
