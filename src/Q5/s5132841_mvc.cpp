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
    int noOfNodes, noOfEdges;
    vector<edge> graph;

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
                    graph.push_back(e);
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
        }
    }

    /* Print out the edges of the graph */
    void printGraph()
    {
        for (int i = 0; i < graph.size(); i++)
        {
            cout << graph[i].from << " -> " << graph[i].to << endl;
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