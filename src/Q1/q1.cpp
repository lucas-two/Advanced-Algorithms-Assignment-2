/* Q1. Number list, with k-smallest list */
#include <iostream>
#include <vector>
using namespace std;

class FibonacciHeap
{
private:
    struct node
    {
        int value;
        bool looser = false;
        node *parent;
        vector<node *> children;
    };
    node *minNode = NULL;
    node *rootList = NULL;

    /* Create a new node */
    node *createNewNode(int value, node *parentNode)
    {
        node *newNode = new node();
        newNode->value = value;
        newNode->children = {};
        return newNode;
    }

    /* Cleanup nodes with same degree */
    void cleanup()
    {
        bool unionFound = true;
        while (unionFound)
        {
            unionFound = findUnion();
        }
    }

    /* Find and union the nodes with same degree */
    bool findUnion()
    {
        for (int i = 0; i < rootList->children.size(); i++)
        {
            for (int j = 0; j < rootList->children.size(); j++)
            {
                // Skip if we're looking at the same node
                if (rootList->children[i] == rootList->children[j])
                {
                    continue;
                }

                // Equal degrees
                if (rootList->children[i]->children.size() == rootList->children[j]->children.size())
                {
                    unionTrees(rootList->children[i], rootList->children[j]);
                    return true;
                }
            }
        }
        return false;
    }

    /* Union two trees together */
    void unionTrees(node *t1, node *t2)
    {
        if (t1->value < t2->value)
        {
            t2->parent = t1;
            t1->children.push_back(t2);
        }
        else
        {
            t1->parent = t2;
            t2->children.push_back(t1);
        }
    }

    /* Update the min node */
    void updateMinNode()
    {
        node *newMin = rootList->children[0];
        for (int i = 1; i < rootList->children.size(); i++)
        {
            if (rootList->children[i]->value < newMin->value)
            {
                newMin = rootList->children[i];
            }
        }
    }

    /* Move a node into the root list */
    void moveToRootList(node *n)
    {
        n->parent = NULL;
        n->looser = false;
        rootList->children.push_back(n);

        if (minNode == NULL || n->value < minNode->value)
        {
            minNode = n;
        }
    }

public:
    FibonacciHeap()
    {
        rootList = createNewNode(-1, NULL);
    }

    /* Display the root list */
    void printRootList()
    {
        cout << "Root List: ";
        for (int i = 0; i < rootList->children.size(); i++)
        {
            cout << rootList->children[i]->value << " ";
        }
        cout << endl;
    }

    /* Insert a value into the fib. heap */
    void insert(int value)
    {
        node *nodeToInsert = createNewNode(value, NULL);
        moveToRootList(nodeToInsert);
    }

    /* Return the min value in the fib. heap */
    void getMin()
    {
        if (minNode == NULL)
        {
            cout << "No min node" << endl;
        }
        else
        {
            cout << "Min node: " << minNode->value << endl;
        }
    }

    /* Remove a value from the fib. heap */
    void remove() {}
};

class KSmallest
{
private:
    int N;          //No. of elements
    int K;          //No. of smallest elements to track
    int upperLimit; // Highest number allowed for random generation

    vector<int> numbers;         // All numbers
    vector<int> smallestNumbers; // Subset of the K smallest numbers

    /* Generate a list of N random numbers */
    void generateRandomNumbers()
    {
        for (int i = 0; i < N; i++)
        {
            int number = rand() % upperLimit;
            numbers.push_back(number);
        }
    }

    /* Find and store the k-smallest numbers */
    void findKSmallest()
    {
    }

    /* Print out all numbers */
    void printNumbers()
    {
        for (int i = 0; i < N; i++)
        {
            cout << numbers[i] << endl;
        }
    }

    /* Print out the k-smalelst numbers */
    void printSmallestNumbers()
    {
        for (int i = 0; i < K; i++)
        {
            cout << smallestNumbers[i] << endl;
        }
    }

public:
    KSmallest(int noElements, int noKSmallestElements, int seed = 0, int maxValueLimit = 100)
    {
        N = noElements;
        K = noKSmallestElements;
        upperLimit = maxValueLimit;
        srand(seed);

        generateRandomNumbers();

        printNumbers();
    }
};

int main()
{
    // KSmallest ks(10, 3);

    FibonacciHeap fh;

    fh.insert(5);
    fh.insert(3);
    fh.insert(6);
    fh.printRootList();
    fh.getMin();

    return 0;
}