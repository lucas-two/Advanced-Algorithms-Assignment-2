/* Q4. Kevin Bacon Problem */
// https://medium.com/swlh/a-path-finding-algorithm-1dd35f49c164
// Going to use A* algorithm

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct record
{
    string actor;          // Actor's full name
    int popularity;        // Number of movies the actor appears in
    vector<string> movies; // A list of movies the actor appears in
};

vector<string> tokenize(string text, string delimiter);
bool comparebyPopularity(const record &a, const record &b);

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

    // Storing the data in a new record data structure
    vector<record> records;
    string currentActor = list[0][0];
    record rec;
    rec.actor = currentActor;
    rec.popularity = 0;
    for (int i = 0; i < list.size(); i++)
    {
        // While the current actor is still the same
        if (list[i][0] == currentActor)
        {
            // Add movies to their record
            rec.movies.push_back(list[i][1]);
            rec.popularity += 1;
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
            rec.popularity = 0;
            // Add this movie to their movie list
            rec.movies.push_back(list[i][1]);
            rec.popularity += 1;
        }
    }

    // Sort the records by popularity
    stable_sort(records.begin(), records.end(), comparebyPopularity);

    // Printing records from the new structure
    for (int i = 0; i < records.size(); i++)
    {
        cout << "[" << records[i].popularity << "] " << records[i].actor << endl;
        for (int j = 0; j < records[i].movies.size(); j++)
        {
            cout << "   - " << records[i].movies[j] << endl;
        }
    }

    return 0;
}

void bfs(vector<record> recs, string startActor, string endActor)
{
    vector<record> queue; // Want this to behave like a set.
    int startActorIndex;

    // Find the record for the start actor
    for (int i = 0; i < recs.size(); i++)
    {
        if (recs[i].actor == startActor)
        {
            startActorIndex = i;
            break;
        }
    }

    // For each of the actor's movies
    for (int i = 0; i < recs[startActorIndex].movies.size(); i++)
    {
        //
    }

    // Look through the actor's movies
    // Add the children of the movie to the queue. (no duplicates!)
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

bool comparebyPopularity(const record &a, const record &b)
{
    return a.popularity > b.popularity;
}
