/* Q4. Kevin Bacon Problem */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
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

    struct production
    {
        movie productionMovie; // Movie
        vector<actor> cast;    // Cast of the movie
    };

    vector<vector<string>> data; // List of all the data

    vector<movie> movies;           // List of all movies
    vector<actor> actors;           // List of all actors
    vector<production> productions; // List of all movie productions

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

    /* Find a paticular actor from the actor's list */
    actor *getActor(string actorName)
    {
        for (int i = 0; i < actors.size(); i++)
        {
            if (actors[i].name == actorName)
            {
                return &actors[i];
            }
        }
        // Actor not found
        cout << "[!] ERROR: Actor '" << actorName << "' not found." << endl;
        return NULL;
    }

    /* Find a movie cast from the productions list */
    vector<actor> *getCast(string movieTitle)
    {
        for (int i = 0; i < productions.size(); i++)
        {
            if (productions[i].productionMovie.title == movieTitle)
            {
                return &productions[i].cast;
            }
        }
        // Movie not found
        cout << "[!] ERROR: Movie '" << movieTitle << "' not found." << endl;
        return NULL;
    }

    int bfs(string startActor, string endActor)
    {
        vector<actor> queue;
        // Add starting actor to the queue
        actor a = *getActor(startActor);
        queue.push_back(a);

        // Level -> 0

        // While the queue isn't empty
        while (!queue.empty())
        {
            // Pop from queue
            actor current = queue[0];
            queue.erase(queue.begin());

            // Check if we've reached the end actor
            if (current.name == endActor)
            {
                return 1;
            }

            // Check if unvisited
            if (!current.visited)
            {
                current.visited = true; // Mark as visited

                // For each of the actor's movies...
                for (int i = 0; i < current.movies.size(); i++)
                {
                    // Find the movie's cast
                    vector<actor> cast = *getCast(current.movies[i].title);

                    // For each actor in the cast...
                    for (int j = 0; j < cast.size(); j++)
                    {
                        queue.push_back(cast[j]); // Add the actor to the queue
                    }
                }
            }
        }

        return 1;
    }

    /* Keep the movies list as a set */
    // NOTE: I tried using sets but this gave me a bug
    // that I wasn't able to solve.
    bool isMovieInList(movie m)
    {
        for (int i = 0; i < movies.size(); i++)
        {
            if (m.title == movies[i].title)
            {
                return true;
            }
        }
        return false;
    }

    /* Extract actors and movies from the data */
    void gatherActors()
    {
        // Initialise starting actor
        actor a = {a.name = data[0][0], a.movies = {}, a.popularity = 0};

        // For each record in the data...
        for (int i = 0; i < data.size(); i++)
        {
            movie m;
            m.title = data[i][1];
            // Add movie to the movies list
            if (!isMovieInList(m))
            {
                movies.push_back(m);
            }

            // If we've reached the end of our data
            if (i == data.size() - 1)
            {
                a.movies.push_back(m);          // Add the movie to the actor's list
                a.popularity = a.movies.size(); // Update actor's popularity
                actors.push_back(a);            // Add actor to the actors list
            }

            // If the actor's name changes
            else if (a.name != data[i][0])
            {
                a.popularity = a.movies.size(); // Update actor's popularity
                actors.push_back(a);
                // Reset the current actor
                a = {a.name = data[i][0], a.movies = {}, a.popularity = 0};
                a.movies.push_back(m); // Add movie to the actor's list
            }
            else
            {
                a.movies.push_back(m); // Add movie to the actor's list
            }
        }
    }

    /* Compile actors and movies into productions */
    void compileProductions()
    {
        // For each movie...
        for (int i = 0; i < movies.size(); i++)
        {
            movie m;
            m.title = movies[i].title;
            production p;
            p.productionMovie = m;
            p.cast = {};

            // For each actor...
            for (int j = 0; j < actors.size(); j++)
            {
                // For each of the actor's movies...
                for (int k = 0; k < actors[j].movies.size(); k++)
                {
                    // If the production movie is the same as the actor's movie
                    if (p.productionMovie.title == actors[j].movies[k].title)
                    {
                        // Add the actor to the production cast
                        p.cast.push_back(actors[j]);
                    }
                }
            }
            productions.push_back(p); // Add the production to the productions list
        }
    }

public:
    KevinBacon(string actorFrom, string actorTo)
    {
        // Input the data into a list (e.g. [[ActorName, MovieTitle]])
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
                data.push_back(tokenize(s, "|"));
            }
            inputFile.close();
        }

        // Collecting all movies
        gatherActors();
        compileProductions();

        // BUG: For some reason this part is freaking out.
        // Sort the actors by popularity
        // stable_sort(actors.begin(), actors.end(), comparebyPopularity);

        bfs(actorFrom, actorTo);
    }

    /* Display the cast members of a production */
    void printProductionCast(production p)
    {
        cout << p.productionMovie.title << endl;
        for (int i = 0; i < p.cast.size(); i++)
        {
            cout << "   - " << p.cast[i].name << endl;
        }
    }

    /* Displays all productions */
    void printProductions()
    {
        for (int i = 0; i < productions.size(); i++)
        {
            printProductionCast(productions[i]);
        }
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

    /* Display all movies */
    void printMovies()
    {
        for (int i = 0; i < movies.size(); i++)
        {
            cout << movies[i].title << endl;
        }
    }
};

int main()
{
    KevinBacon kb("Kevin Bacon (I)", "Morgan Freeman (I)");
    // kb.printActors();
    // kb.printMovies();
    kb.printProductions();
    return 0;
}