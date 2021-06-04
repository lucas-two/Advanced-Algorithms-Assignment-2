/* Q1. Number list, with k-smallest list */
#include <iostream>
#include <vector>
#include <string>
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
    vector<node *> map;

    /* Create a new node */
    node *createNewNode(int value, node *parentNode)
    {
        node *newNode = new node();
        newNode->value = value;
        newNode->children = {};
        return newNode;
    }

    /* Clean up nodes with same degree */
    void cleanup()
    {
        bool unionFound = true;
        while (unionFound)
        {
            unionFound = findUnion();
        }
        updateMinNode();
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
            removeFromParentsChildren(t2);
            t2->parent = t1;
            t1->children.push_back(t2);
        }
        else
        {
            removeFromParentsChildren(t1);
            t1->parent = t2;
            t2->children.push_back(t1);
        }
    }

    /* Update the min node */
    void updateMinNode()
    {
        node *newMinNode = rootList->children[0];

        for (int i = 1; i < rootList->children.size(); i++)
        {
            if (minNode == NULL || rootList->children[i]->value < newMinNode->value)
            {
                newMinNode = rootList->children[i];
            }
        }
        minNode = newMinNode;
    }

    /* Move a node into the root list */
    void moveToRootList(node *n)
    {
        n->parent = rootList;
        n->looser = false;
        rootList->children.push_back(n);

        if (minNode == NULL || n->value < minNode->value)
        {
            minNode = n;
        }
    }

    /* Return if a node is in the root list */
    bool inRootList(node *n)
    {
        return n->parent == NULL;
    }

    /* 
    Find the pointer to a node by it's value

    NOTE: This will give us a find of O(K). An alternative would
    be to use a hashmap, but since space efficency must be O(K + N)
    I decided against doing that. 
    */
    node *find(int valueToFind)
    {
        vector<node *> queue;
        queue.push_back(rootList);

        while (!queue.empty())
        {
            node *current = queue[0];
            queue.erase(queue.begin());

            for (int i = 0; i < current->children.size(); i++)
            {
                if (current->children[i]->value == valueToFind)
                {
                    return current->children[i];
                }
                // don't search the branch if the value is bigger than
                // the one we're looking for.
                if (current->children[i]->value < valueToFind)
                {
                    queue.push_back(current->children[i]);
                }
            }
        }
        cout << "[!] Could not find the value (" << valueToFind << ") in the heap." << endl;
        exit(1);
        return NULL;
    }

    /* Removes a node from its parent's children */
    void removeFromParentsChildren(node *n)
    {
        for (int i = 0; i < n->parent->children.size(); i++)
        {
            if (n == n->parent->children[i])
            {
                n->parent->children.erase(n->parent->children.begin() + i);
            }
        }
    }

    /* Remove a node by its pointer from the fib. heap */
    void removeNode(node *n)
    {
        if (!inRootList(n))
        {
            // If the node's parent is already a looser
            if (n->parent->looser)
            {
                removeNode(n->parent);
            }
            else
            {
                n->parent->looser = true;
            }
            removeFromParentsChildren(n);
            moveToRootList(n);
        }
        removeFromParentsChildren(n);
        for (int i = 0; i < n->children.size(); i++)
        {
            moveToRootList(n->children[i]);
        }
        n = NULL;
        cleanup();
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
        cout << "Min Node: " << (minNode == NULL ? "N/A" : to_string(minNode->value)) << endl;
    }

    /* Remove a node by its value from the fib. heap */
    void remove(int value)
    {
        node *n = find(value);
        removeNode(n);
    }
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
    fh.insert(7);
    fh.insert(2);
    fh.insert(8);
    fh.insert(12);
    fh.printRootList();
    fh.getMin();
    fh.remove(2);
    fh.getMin();
    fh.printRootList();

    return 0;
}