/* Q5. Minimum Vertex Cover For Complement Graphs */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class MinimumVertexCover
{
private:
    struct edge
    {
        int from, to;
    };
    struct node
    {
        int id;
        vector<int> connections;
        int unseenConnections;
        bool visited = false;
        bool seen = false;
    };
    int noOfNodes, noOfEdges;
    int verticiesCovered = 0;
    int seenNodes = 0;
    vector<edge> edges;
    vector<node> nodes;

    /* Finds the minimum vertex cover */
    void findMinCover(node *startNode)
    {
        cout << "Calculating min cover..." << endl;
        vector<node *> priorityQueue;
        priorityQueue.push_back(startNode);

        while (seenNodes != noOfNodes && !priorityQueue.empty())
        {
            node *current = priorityQueue[0];
            priorityQueue.erase(priorityQueue.begin());

            if (!current->visited)
            {
                current->visited = true;
                verticiesCovered += 1;

                if (!current->connections.empty())
                {
                    for (int i = 1; i < current->connections.size(); i++)
                    {
                        node *childNode = findNode(current->connections[i]);

                        if (!childNode->seen)
                        {
                            childNode->seen = true;
                            seenNodes += 1;
                        }
                        // Insert the child at the front of the queue if it's larger than the current largest node
                        // Allows it to act as a priority queue
                        if (!priorityQueue.empty())
                        {
                            if (childNode->unseenConnections > priorityQueue[0]->unseenConnections)
                            {
                                priorityQueue.insert(priorityQueue.begin(), childNode);
                            }
                            else
                            {
                                priorityQueue.push_back(childNode);
                            }
                        }
                        else
                        {
                            priorityQueue.push_back(childNode);
                        }

                        updateAllWithSeenNode(childNode->id);
                    }
                }
            }
        }
    }

    /* Update all nodes where a specific node appears as their child */
    void updateAllWithSeenNode(int id)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            for (int j = 0; j < nodes[i].connections.size(); j++)
            {
                if (nodes[i].connections[j] == id)
                {
                    nodes[i].unseenConnections -= 1;
                }
            }
        }
    }

    /* Find the node with the most connections */
    node *getStartNode()
    {
        node *topNode = &nodes[0];
        for (int i = 0; i < nodes.size(); i++)
        {
            node *comparisonNode = &nodes[i];

            if (comparisonNode->unseenConnections > topNode->unseenConnections)
            {
                topNode = comparisonNode;
            }
        }
        return topNode;
    }

    /* Find a specific node from its ID */
    node *findNode(int id)
    {
        // Given the nature of the ids, we can just use id - 1 to find its location
        return &nodes[id - 1];
    }

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

    /* Extract the nodes from the edges */
    void extractNodes()
    {
        cout << "Extracting edges" << endl;

        for (int nodeId = 1; nodeId <= noOfNodes; nodeId++)
        {
            node n;
            n.id = nodeId;
            n.connections = {};
            for (int i = 0; i < noOfEdges; i++)
            {
                if (nodeId == edges[i].to)
                {
                    n.connections.push_back(edges[i].from);
                }
                else if (nodeId == edges[i].from)
                {
                    n.connections.push_back(edges[i].to);
                }
            }
            n.unseenConnections = n.connections.size();
            nodes.push_back(n);
        }
    }

public:
    MinimumVertexCover(string targetMinVertex)
    {
        // Input graph data
        ifstream inputFile(targetMinVertex);
        if (inputFile.fail())
        {
            cout << "[!] COULD NOT READ FILE" << endl;
        }
        else
        {
            string s;
            while (getline(inputFile, s))
            {
                // Extract edges
                if (s[0] == 'e')
                {
                    vector<string> graphEdgeInfo = tokenize(s, " ");
                    edge e = {e.from = stoi(graphEdgeInfo[1]), e.to = stoi(graphEdgeInfo[2])};
                    edges.push_back(e);
                }
                // Extract node and edge count
                else if (s[0] == 'p')
                {
                    vector<string> graphSizeInfo = tokenize(s, " ");
                    noOfNodes = stoi(graphSizeInfo[2]);
                    noOfEdges = stoi(graphSizeInfo[3]);
                }
            }
            inputFile.close();

            extractNodes();

            node *startNode = getStartNode();
            findMinCover(startNode);
            cout << "Verticies Covered: " << verticiesCovered << endl;
        }
    }

    // MinimumVertexCover()
    // {
    //     cout << "Create edges" << endl;
    //     edge e1 = {e1.from = 1, e1.to = 2};
    //     edge e2 = {e2.from = 2, e2.to = 3};
    //     edge e3 = {e3.from = 3, e3.to = 6};
    //     edge e4 = {e4.from = 6, e4.to = 9};
    //     edge e5 = {e5.from = 9, e5.to = 8};
    //     edge e6 = {e6.from = 8, e6.to = 7};
    //     edge e7 = {e7.from = 7, e7.to = 4};
    //     edge e8 = {e8.from = 4, e8.to = 1};
    //     edge e9 = {e9.from = 5, e9.to = 2};
    //     edge e10 = {e10.from = 5, e10.to = 4};
    //     edge e11 = {e11.from = 5, e11.to = 8};
    //     edge e12 = {e12.from = 5, e12.to = 6};

    //     edges.push_back(e1);
    //     edges.push_back(e2);
    //     edges.push_back(e3);
    //     edges.push_back(e4);
    //     edges.push_back(e5);
    //     edges.push_back(e6);
    //     edges.push_back(e7);
    //     edges.push_back(e8);
    //     edges.push_back(e9);
    //     edges.push_back(e10);
    //     edges.push_back(e11);
    //     edges.push_back(e12);

    //     noOfEdges = 12;
    //     noOfNodes = 9;

    //     extractNodes();

    //     node *startNode = getStartNode();
    //     findMinCover(startNode);
    //     cout << "Verticies Covered: " << verticiesCovered << endl;
    // }

    /* Print out the edges of the graph */
    void printEdges()
    {
        for (int i = 0; i < edges.size(); i++)
        {
            cout << edges[i].from << " -> " << edges[i].to << endl;
        }
    }

    /* Print out the nodes of the graph */
    void printNodes()
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << "[" << nodes[i].id << "]:";
            for (int j = 0; j < nodes[i].connections.size(); j++)
            {
                cout << " " << nodes[i].connections[j];
            }
            cout << endl;
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "[!] Error: Missing paremeter." << endl;
        return -1;
    }
    MinimumVertexCover mvc(argv[1]);
    return 0;
}