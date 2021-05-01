/* Q4. Kevin Bacon Problem */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> tokenize(string text, string delimiter);

int main()
{
    // Input the data
    vector<string> data;
    vector<vector<string>> list;
    ifstream inputFile("data.txt");
    if (inputFile.fail())
    {
        cout << "[!] COULD NOT READ FILE" << endl;
    }
    else
    {
        string s;
        while (getline(inputFile, s))
        {
            list.push_back(tokenize(s, "|"));
        }
        inputFile.close();
    }

    cout << list[0][0] << " -> " << list[0][1] << endl;
    return 0;
}

/* Splitting the input */
// NOTE: I used a code example from GeeksForGeeks to create this.
// It is not my original work, and I only slightly tweaked it.
// (source: https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/)
vector<string> tokenize(string text, string delimiter)
{
    int start = 0;
    int end = text.find(delimiter);
    vector<string> words;
    while (end != -1)
    {
        words.push_back(text.substr(start, end - start));
        start = end + delimiter.size();
        end = text.find(delimiter, start);
    }
    words.push_back(text.substr(start, end - start));

    return words;
}