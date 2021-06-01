/* Q4. Kevin Bacon Problem */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class KevinBacon
{
private:
    struct actor
    {
        string name;           // Actor name
        vector<string> movies; // Movie titles actor appears in
        int popularity;        // No. of movies actor appears in
        bool visited = false;  //Have we visited the actor in BFS
    };

    struct production
    {
        string title;         // Movie title
        vector<actor> cast;   // Cast of the movie
        bool visited = false; //Have we visited the production in BFS
    };

    vector<vector<string>> data;    // List of all the data
    vector<string> movies;          // List of all movies
    vector<actor> actors;           // List of all actors
    vector<production> productions; // List of all movie productions

    vector<actor> visitedActors;

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
        cout << "[!] ERROR: Actor '" << actorName << "' not found." << endl;
        exit(1);
        return NULL;
    }

    /* Get a specific production */
    production *getProduction(string movieTitle)
    {
        for (int i = 0; i < productions.size(); i++)
        {
            if (productions[i].title == movieTitle)
            {
                return &productions[i];
            }
        }
        cout << "[!] ERROR: Movie '" << movieTitle << "' not found." << endl;
        exit(1);
        return NULL;
    }

    /* Reset the visited state of actors and productions */
    void resetVisited()
    {
        for (int i = 0; i < actors.size(); i++)
        {
            actors[i].visited = false;
        }

        for (int i = 0; i < actors.size(); i++)
        {
            productions[i].visited = false;
        }
    }

    /* Perform Breadth First Search to find no. of links between actors */
    int bfs(string startActor, string endActor)
    {
        vector<actor *> queue;
        // Add starting actor to the queue
        actor *a = getActor(startActor);
        queue.push_back(a);

        // Tracking level
        int baconScore = 0; // Number of actors jumped
        int toExploreCurrent = 1;
        int toExploreNext = 0;

        // While the queue isn't empty
        while (!queue.empty())
        {
            // Pop from queue
            actor *current = queue[0];
            queue.erase(queue.begin());

            if (!current->visited)
            {
                current->visited = true; // Mark as visited

                // For each of the actor's movies...
                for (int i = 0; i < current->movies.size(); i++)
                {
                    production *p = getProduction(current->movies[i]);

                    // If the movie is unvisited...
                    if (!p->visited)
                    {
                        p->visited = true; // Mark as visited

                        // For each actor in the cast...
                        for (int j = 0; j < p->cast.size(); j++)
                        {
                            // NOTE: It's important that the actor comes from the
                            // [actors] list instead of the [productions[x].cast] list.
                            // This is because actors from the cast do not have an accurate
                            // (visited) state.
                            actor *a = getActor(p->cast[j].name);

                            // If the actor is unvisited...
                            if (!a->visited)
                            {
                                // If we found the end actor, return our bacon score
                                if (a->name == endActor)
                                {
                                    resetVisited();
                                    return baconScore + 1;
                                }
                                // Otherwise, add the actor to the queue
                                else
                                {
                                    toExploreNext += 1;
                                    queue.push_back(a); // Add the actor to the queue
                                }
                            }
                        }
                    }
                }
                // Actor child has been explored
                toExploreCurrent -= 1;
                // If we've processed all the actors on this level
                if (toExploreCurrent == 0)
                {
                    baconScore += 1;                  // Increase the bacon score
                    toExploreCurrent = toExploreNext; // Update the 'current to explore' with the found 'next to explore'
                    toExploreNext = 0;                // Reset the to 'next to explore'
                }
            }
        }
        resetVisited();
        return -1;
    }

    /* Keep the movies list as a set */
    // NOTE: I tried using sets but this gave me a bug
    // that I wasn't able to solve.
    bool isMovieInList(string m)
    {
        for (int i = 0; i < movies.size(); i++)
        {
            if (m == movies[i])
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
        actor a;
        a.name = data[0][0];

        // For each record in the data...
        for (int i = 0; i < data.size(); i++)
        {
            string m = data[i][1];

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
                a.name = data[i][0];
                a.movies = {};
                a.popularity = 0;
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
            production p;
            p.title = movies[i];
            p.cast = {};

            // For each actor...
            for (int j = 0; j < actors.size(); j++)
            {
                // For each of the actor's movies...
                for (int k = 0; k < actors[j].movies.size(); k++)
                {
                    // If the production movie is the same as the actor's movie
                    if (p.title == actors[j].movies[k])
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
    KevinBacon()
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

        // Convert data to more usable data structure
        gatherActors();
        compileProductions();
    }

    /* Display the cast members of a production */
    void printProductionCast(production p)
    {
        cout << p.title << endl;
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
        cout << "[" << a.popularity << "] " << a.name << " --> visited: " << (a.visited ? "yes" : "no") << endl;
        for (int i = 0; i < a.movies.size(); i++)
        {
            cout << "   - " << a.movies[i] << endl;
        }
    }

    /* Display movies an actor is in*/
    void printActorsNoMovies()
    {
        for (int i = 0; i < actors.size(); i++)
        {
            cout << actors[i].name << " --> visited: " << (actors[i].visited ? "yes" : "no") << endl;
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
            cout << movies[i] << endl;
        }
    }

    /* Calculate links between two actors */
    void findMinLinks(string actorFrom, string actorTo)
    {
        int score = bfs(actorFrom, actorTo);

        if (score == -1)
        {
            cout << actorFrom << " ---/ No link /---> " << actorTo << endl;
        }
        else
        {
            cout << actorFrom << " ---( " << score << " links )---> " << actorTo << endl;
        }
    }

    /* Calculate links between an actor and Kevin Bacon */
    void findBaconNumber(string actorTo)
    {
        findMinLinks(actorTo, "Kevin Bacon (I)");
    }

    /* Find actor with the highest Bacon number. */
    void findHighestBacon()
    {
        string actorToBest;
        int topScore;
        for (int i = 0; i < actors.size(); i++)
        {
            string actorTo = actors[i].name;
            int score = bfs("Kevin Bacon (I)", actorTo);
            if (score > topScore)
            {
                topScore = score;
                actorToBest = actorTo;
            }
        }
        cout << actorToBest << " ---( " << topScore << " links )---> "
             << "Kevin Bacon (I)" << endl;
    }
};

int main()
{
    KevinBacon kb;

    kb.findBaconNumber("Steven Brill (I)");
    kb.findBaconNumber("Carrie Fisher");
    kb.findBaconNumber("Jorn Benzon");
    kb.findBaconNumber("Billy Crystal");

    kb.findMinLinks("Denise Dabrowski", "Roy C. Johnson");
    kb.findMinLinks("Roman Bohnen", "Alan Rickman");
    kb.findMinLinks("Albert Brooks (I)", "Steve Buscemi");
    kb.findMinLinks("Gino Corrado", "Tim Condren");

    kb.findHighestBacon();
    return 0;
}