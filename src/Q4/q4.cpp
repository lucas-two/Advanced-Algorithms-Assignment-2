/* Q4. Kevin Bacon Problem */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class KevinBacon
{
private:
    struct movie
    {
        string title;         // Movie title
        bool visited = false; // Have we visited the movie in BFS
    };
    struct actor
    {
        string name;          // Actor name
        vector<movie> movies; // Movies actor appears in
        int popularity;       // No. of movies actor appears in
        bool visited = false; //Have we visited the actor in BFS
    };

    vector<actor> actors; // List of all actors

    /* Splitting the input */
    vector<string> tokenize(string text, string delimiter)
    {
        /* NOTE: I used a code example from GeeksForGeeks.org to create this.
        It is not my original work, and I only slightly tweaked it.
        (source: https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/) */

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

    /* Comparison for sorting by actor popularity */
    bool comparebyPopularity(const actor &a, const actor &b)
    {
        return a.popularity > b.popularity;
    }

    /* Find the index of the actor in the actors list */
    int findActorIndex(string actorName)
    {
        for (int i = 0; i < actors.size(); i++)
        {
            if (actors[i].name == actorName)
            {
                return i;
            }
        }

        // Actor not found
        cout << "[!] ERROR: Actor " << actorName << " not found." << endl;
        return -1;
    }

    void bfs(string startActor, string endActor)
    {
        int actorIndex = findActorIndex(startActor);

        cout << actorIndex;
        return;
    }

public:
    KevinBacon(string actorFrom, string actorTo)
    {
        // Input the data into a list (e.g. [[ActorName, MovieTitle]])
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

        // Convert list data into a suitable data structure.
        actor a = {a.name = list[0][0], a.movies = {}, a.popularity = 0}; // Initialise starting actor
        for (int i = 0; i < list.size(); i++)
        {
            // If the actor's name changes
            if (a.name != list[i][0])
            {
                a.popularity = a.movies.size();                             // Update the popularity of the actor
                actors.push_back(a);                                        // Add the actor to the list
                a = {a.name = list[i][0], a.movies = {}, a.popularity = 0}; // Update to the next actor + reset a
            }
            // Add movie to the actor's list
            movie m;
            m.title = list[i][1];
            a.movies.push_back(m);
        }

        // BUG: For some reason this part is freaking out.
        // Sort the actors by popularity
        // stable_sort(actors.begin(), actors.end(), comparebyPopularity);

        bfs(actorFrom, actorTo);
    }

    /* Display movies an actor is in*/
    void printActorMovies(actor a)
    {
        cout << "[" << a.popularity << "] " << a.name << endl;
        for (int i = 0; i < a.movies.size(); i++)
        {
            cout << "   - " << a.movies[i].title << endl;
        }
    }

    /* Display actors & the movies they appear in*/
    void printActors()
    {
        for (int i = 0; i < actors.size(); i++)
        {
            printActorMovies(actors[i]);
        }
    }
};

int main()
{
    KevinBacon kb("Kevin Bacon (I)", "Morgan Freeman (I)");
    // kb.printActors();
    return 0;
}