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
    };
    int noOfNodes, noOfEdges;
    vector<edge> edges;
    vector<node> nodes;

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
        }
    }

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
    mvc.printNodes();
    return 0;
}