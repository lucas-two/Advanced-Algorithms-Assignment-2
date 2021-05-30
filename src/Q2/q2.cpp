/* Q2. Maze Generation */
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Maze
{
private:
    // Defines a position in the maze
    struct pos
    {
        int x, y;
    };

    int mazeWidth, mazeHeight;

    pos mazeStart, mazeEnd, furthestFromStart, furthestFromEnd;

    // Our maze
    // Legend: Start (2) | End (3) | Wall (1) | Path (0)
    vector<vector<int>> maze;

    // Copy of our maze, tracking visited paths
    // Legend: Visited (1) | Unvisited (0)
    vector<vector<int>> mazeVisited;

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

    /* Check if positions are equal */
    bool isGoal(pos a, pos b)
    {
        return a.y == b.y && a.x == b.x;
    }

    /* Check if a position is a wall */
    bool isWall(pos a)
    {
        return maze[a.y][a.x] == 1;
    }

    /* Turn a wall into a path */
    bool breakWall(pos a)
    {
        return maze[a.y][a.x] = 0;
    }

    /* Calculate Manhattan distance between two points */
    int calcManhattan(pos a, pos b)
    {
        return abs(a.y - b.y) + abs(a.x - b.x) - 1;
    }

    /* Check if there is a path between the start and end */
    bool isComplete()
    {
        // Run 2 BFSs: one from START -> END, and one from END -> START.
        // If either return true, we know we've reached our goal.
        return bfs(mazeStart, mazeEnd, &furthestFromStart) || bfs(mazeEnd, mazeStart, &furthestFromEnd);
    }

    /* Perform Breadth First Search */
    bool bfs(pos origin, pos goal, pos *furthestToGoal)
    {
        vector<pos> queue;
        queue.push_back(origin);

        // While the queue isn't empty
        while (!queue.empty())
        {
            // Pop from queue
            pos current = queue[0];
            queue.erase(queue.begin());

            // Check if we've reached the goal position
            if (isGoal(current, goal))
            {
                return true;
            }

            // Check if unvisited
            if (isUnvisited(current))
            {
                markAsVisited(current); // Mark as visited

                // Check if the current distance is greater than the best distance
                // Update the best distance if so.
                int bestDistance = calcManhattan(*furthestToGoal, origin);
                int currentDistance = calcManhattan(current, origin);
                if (currentDistance > bestDistance)
                {
                    *furthestToGoal = current;
                }

                // Check available positions:
                // North
                if (current.y != 0)
                {
                    // Add the north position to the queue if it's unvisited and able to be visited.
                    pos north = {origin.x = current.x, origin.y = current.y - 1};
                    if (isUnvisited(north) && canVisit(north))
                    {
                        queue.push_back(north);
                    }
                }
                // East
                if (current.x != mazeWidth - 1)
                {
                    // Add the east position to the queue if it's unvisited and able to be visited.
                    pos east = {origin.x = current.x + 1, origin.y = current.y};
                    if (isUnvisited(east) && canVisit(east))
                    {
                        queue.push_back(east);
                    }
                }
                // South
                if (current.y != mazeHeight - 1)
                {
                    // Add the south position to the queue if it's unvisited and able to be visited.
                    pos south = {origin.x = current.x, origin.y = current.y + 1};
                    if (isUnvisited(south) && canVisit(south))
                    {
                        queue.push_back(south);
                    }
                }
                // West
                if (current.x != 0)
                {
                    // Add the south position to the queue if it's unvisited and able to be visited.
                    pos west = {origin.x = current.x - 1, origin.y = current.y};
                    if (isUnvisited(west) && canVisit(west))
                    {
                        queue.push_back(west);
                    }
                }
            }
        }

        // We will reach here if the queue was exhaused and no end was found.
        mazeVisited = generatEmptyMaze(0); // Reset the visited maze
        return false;
    }

    /* Build the maze by randomly knocking down walls */
    void buildMaze()
    {
        while (!isComplete())
        {
            int noOfWallsToBreak = calcManhattan(furthestFromStart, furthestFromEnd);
            int wallsBroken = 0;
            while (wallsBroken <= noOfWallsToBreak)
            {
                // Choose a random position in the maze
                pos randomPos = {
                    randomPos.x = rand() % mazeWidth, // Range: 0 -> mazeWidth - 1
                    randomPos.y = rand() % mazeHeight // Range: 0 -> mazeHeight - 1
                };

                // If it's a wall, break it down
                if (isWall(randomPos))
                {
                    breakWall(randomPos);
                    wallsBroken += 1;
                }
            }
        }
    }

    /* Generates an empty maze and fills it with a specified value */
    vector<vector<int>> generatEmptyMaze(int fillValue)
    {
        vector<vector<int>> emptyMaze(mazeHeight, vector<int>(mazeWidth, fillValue));
        return emptyMaze;
    }

public:
    Maze(int width, int height, int seed = 0)
    {
        // Seed for random generation (default of 0)
        srand(seed);

        // Input the maze height/width
        mazeWidth = width;
        mazeHeight = height;

        // Generate empty maze for tracking if visited
        mazeVisited = generatEmptyMaze(0);

        // Generate empty maze filled with walls
        maze = generatEmptyMaze(1);

        // Adding in the start and end positions
        mazeStart = {mazeStart.x = 0, mazeStart.y = 0};
        mazeEnd = {mazeEnd.x = mazeWidth - 1, mazeEnd.y = mazeHeight - 1};
        maze[mazeStart.y][mazeStart.x] = 2;
        maze[mazeEnd.y][mazeEnd.x] = 3;

        // Initialise the pos furthest from start/end
        furthestFromStart = mazeStart;
        furthestFromEnd = mazeEnd;

        // Build the maze
        buildMaze();
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
        cout << endl;
    }
};

int main()
{
    Maze mz(50, 88);
    mz.printMaze();
    return 0;
}