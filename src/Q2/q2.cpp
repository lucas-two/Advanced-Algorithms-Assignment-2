/* Q2. Maze Generation */
#include <iostream>
#include <vector>
using namespace std;

class Maze
{
private:
    // Defines a position in the maze
    struct pos
    {
        int x, y;
    };

    int mazeWidth = 10; // Width of maze
    int mazeHeight = 7; // Height of maze

    vector<vector<int>> newMaze;

    // Our maze
    // Legend: Start (2) | End (3) | Wall (1) | Path (0)
    vector<vector<int>> maze = {
        {2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 1, 1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
        {0, 1, 1, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0, 3},
    };

    // Copy of our maze, tracking visited paths
    // Legend: Visited (1) | Unvisited (0)
    vector<vector<int>> mazeVisited = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    /* Check if a position has not been visited */
    bool isUnvisited(pos a)
    {
        return mazeVisited[a.y][a.x] == 0;
    }

    /* Mark position as visited */
    void markAsVisited(pos a)
    {
        mazeVisited[a.y][a.x] = 1;
    }

    /* Check if a position can be visited (e.g. isn't 1) */
    bool canVisit(pos a)
    {
        return maze[a.y][a.x] != 1;
    }

    /* Check if the end is reached */
    bool isEnd(pos a)
    {
        return maze[a.y][a.x] == 3;
    }

public:
    Maze(int width, int height)
    {
        // Input the maze height/width
        mazeWidth = width;
        mazeHeight = height;

        // Generate empty maze
        vector<vector<int>> emptyMaze(mazeHeight, vector<int>(mazeWidth, 0));
        newMaze = emptyMaze;
    }

    /* Check if there is a path from start to end */
    bool isComplete()
    {
        vector<pos> queue;                      // Queue storing valid positions
        pos start = {start.x = 0, start.y = 0}; // Maze starting position
        queue.push_back(start);                 // Insert starting position into the queue

        // While the queue isn't empty
        while (!queue.empty())
        {
            // Pop from queue
            pos current = queue[0];
            queue.erase(queue.begin());

            // Check if we've reached the end position
            if (isEnd(current))
            {
                return true;
            }

            // Check if unvisited
            if (isUnvisited(current))
            {
                markAsVisited(current); // Mark as visited
            }

            // Check available positions:
            // North
            if (current.y != 0)
            {
                // Add the north position to the queue if it's unvisited and able to be visited.
                pos north = {start.x = current.x, start.y = current.y - 1};
                if (isUnvisited(north) && canVisit(north))
                {
                    queue.push_back(north);
                }
            }
            // East
            if (current.x != mazeWidth - 1)
            {
                // Add the east position to the queue if it's unvisited and able to be visited.
                pos east = {start.x = current.x + 1, start.y = current.y};
                if (isUnvisited(east) && canVisit(east))
                {
                    queue.push_back(east);
                }
            }
            // South
            if (current.y != mazeHeight - 1)
            {
                // Add the south position to the queue if it's unvisited and able to be visited.
                pos south = {start.x = current.x, start.y = current.y + 1};
                if (isUnvisited(south) && canVisit(south))
                {
                    queue.push_back(south);
                }
            }
            // West
            if (current.x != 0)
            {
                // Add the south position to the queue if it's unvisited and able to be visited.
                pos west = {start.x = current.x - 1, start.y = current.y};
                if (isUnvisited(west) && canVisit(west))
                {
                    queue.push_back(west);
                }
            }
        }

        // We will reach here if the queue was exhaused and no end was found.
        return false;
    }

    /* Print out the maze*/
    void printMaze()
    {
        for (int i = 0; i < maze.size(); i++)
        {
            for (int j = 0; j < maze[i].size(); j++)
            {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
    }

    /* Print out the maze*/
    void printNewMaze()
    {
        for (int i = 0; i < newMaze.size(); i++)
        {
            for (int j = 0; j < newMaze[i].size(); j++)
            {
                cout << newMaze[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Maze mz(10, 7);
    mz.printMaze();
    mz.printNewMaze();
    cout << "Is complete: " << mz.isComplete() << endl;
    return 0;
}