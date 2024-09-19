#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string readFile(const string &fileName)
{
    string filePath = "inputs/" + fileName;
    ifstream file(filePath);
    if (!file.is_open())
    {
        throw runtime_error("Could not open the file - '" + filePath + "'");
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

bool findMaliciousCode(const string &transmission, const string &maliciousCode, size_t &position)
{
    position = transmission.find(maliciousCode);
    return (position != string::npos);
}

void longestPalindrome(const string &transmission)
{
    int n = transmission.length();
    int maxLength = 1;
    int start = 0;

    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i)
        dp[i][i] = true;

    for (int i = 0; i < n - 1; ++i)
    {
        if (transmission[i] == transmission[i + 1])
        {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    for (int length = 3; length <= n; ++length)
    {
        for (int i = 0; i < n - length + 1; ++i)
        {
            int j = i + length - 1;

            if (dp[i + 1][j - 1] && transmission[i] == transmission[j])
            {
                dp[i][j] = true;

                if (length > maxLength)
                {
                    start = i;
                    maxLength = length;
                }
            }
        }
    }

    cout << start + 1 << " " << start + maxLength << endl;
}

void longestCommonSubstring(const string &transmission1, const string &transmission2)
{
    int n1 = transmission1.length();
    int n2 = transmission2.length();
    int maxLength = 0;
    int endPos = 0;

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            if (transmission1[i - 1] == transmission2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;

                if (dp[i][j] > maxLength)
                {
                    maxLength = dp[i][j];
                    endPos = i;
                }
            }
        }
    }

    int startPos = endPos - maxLength + 1;

    cout << startPos << " " << endPos << endl;
}

int main()
{
    vector<string> transmissionFiles = {"transmission1.txt", "transmission2.txt"};
    vector<string> maliciousCodeFiles = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};

    vector<string> transmissions;
    for (const string &transmissionFile : transmissionFiles)
    {
        transmissions.push_back(readFile(transmissionFile));
    }

    vector<string> maliciousCodes;
    for (const string &maliciousCodeFile : maliciousCodeFiles)
    {
        maliciousCodes.push_back(readFile(maliciousCodeFile));
    }

    // Complejidad de tiempo
    // O(n * m) donde n es el tamaño de transmissions y m es el tamaño de maliciousCodes
    for (size_t i = 0; i < transmissions.size(); ++i)
    {
        const string &transmission = transmissions[i];
        for (size_t j = 0; j < maliciousCodes.size(); ++j)
        {
            const string &maliciousCode = maliciousCodes[j];
            size_t position;
            if (findMaliciousCode(transmission, maliciousCode, position))
                cout << "true " << position + 1 << endl;
            else
                cout << "false" << endl;
        }
    }

    cout << endl;

    // Complejidad de tiempo
    // O(n*m) donde n es el tamaño de la primera transmisión y m es el tamaño de la segunda transmisión
    for (const string &transmission : transmissions)
    {
        longestPalindrome(transmission);
    }

    cout << endl;

    // Complejidad de tiempo
    // O(n*m) donde n es el tamaño de la primera transmisión y m es el tamaño
    longestCommonSubstring(transmissions[0], transmissions[1]);

    return 0;
}
