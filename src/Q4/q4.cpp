/* Q4. Kevin Bacon Problem */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> tokenize(string text, string delimiter);

struct record
{
    string actor;
    vector<string> movies;
};
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

    // Move data into a more useful data structure
    vector<record> records;

    string currentActor = list[0][0];
    record rec;
    rec.actor = currentActor;
    for (int i = 0; i < list.size(); i++)
    {
        // While the current actor is still the same
        if (list[i][0] == currentActor)
        {
            // Add movies to their record
            rec.movies.push_back(list[i][1]);
        }
        // If it changes
        else
        {
            // Submit the previous record
            records.push_back(rec);

            // Update new current actor
            currentActor = list[i][0];
            rec.actor = currentActor;
            rec.movies = {};
            // Add this movie to their movie list
            rec.movies.push_back(list[i][1]);
        }
    }

    for (int i = 0; i < records.size(); i++)
    {
        cout << records[i].actor << endl;
        for (int j = 0; j < records[i].movies.size(); j++)
        {
            cout << "   - " << records[i].movies[j] << endl;
        }
    }
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