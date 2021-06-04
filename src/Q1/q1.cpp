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
    node *maxNode = NULL;
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
        updateMaxNode();
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
        if (t1->value > t2->value)
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

    /* Update the max node */
    void updateMaxNode()
    {
        node *newMaxNode = rootList->children[0];

        for (int i = 1; i < rootList->children.size(); i++)
        {
            if (maxNode == NULL || rootList->children[i]->value > newMaxNode->value)
            {
                newMaxNode = rootList->children[i];
            }
        }
        maxNode = newMaxNode;
    }

    /* Move a node into the root list */
    void moveToRootList(node *n)
    {
        n->parent = rootList;
        n->looser = false;
        rootList->children.push_back(n);

        if (maxNode == NULL || n->value > maxNode->value)
        {
            maxNode = n;
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
                // don't search the branch if the value is less than
                // the one we're looking for.
                if (current->children[i]->value > valueToFind)
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

    /* Update to or deal with looser nodes */
    void updateLooser(node *n)
    {
        // If the node is a double looser
        if (n->looser)
        {
            updateLooser(n->parent);
            moveToRootList(n);
        }
        else
        {
            n->looser = true;
        }
    }

    /* Remove a node by its pointer from the fib. heap */
    void removeNode(node *n)
    {
        if (!inRootList(n))
        {
            updateLooser(n->parent);
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

    /* Priting children of a node */
    void printChildren(node *n)
    {
        for (int i = 0; i < n->children.size(); i++)
        {
            cout << n->children[i]->value << " " << n->value;
            if (!n->children[i]->children.empty())
            {
                printChildren(n->children[i]);
            }
        }
    }

    /* Display the root list */
    void printChildrenFromStructure(node *n)
    {
        for (int i = 0; i < n->children.size(); i++)
        {
            cout << n->children[i]->value << "(parent: " << n->value << ") ";

            if (!n->children[i]->children.empty())
            {
                cout << "[ ";
                printChildrenFromStructure(n->children[i]);
            }
        }
        cout << endl;
    }

public:
    FibonacciHeap()
    {
        rootList = createNewNode(-1, NULL);
    }

    /* Display structure of the heap */
    void printHeapStructure()
    {
        cout << "Heap structure:" << endl;
        printChildrenFromStructure(rootList);
    }

    /* Priting out the heap */
    void printHeap()
    {
        printChildren(rootList);
    }

    /* Insert a value into the fib. heap */
    void insert(int value)
    {
        node *nodeToInsert = createNewNode(value, NULL);
        moveToRootList(nodeToInsert);
    }

    /* Return the max value in the fib. heap */
    int getMax()
    {
        return maxNode->value;
    }

    /* Remove a node by its value from the fib. heap */
    void remove(int value)
    {
        node *n = find(value);
        removeNode(n);
    }

    /* Remove the max node */
    void removeMax()
    {
        removeNode(maxNode);
    }
};

class KSmallest
{
private:
    int N, K;
    int currentKNodes = 0;
    vector<int> numbers;
    FibonacciHeap kSmallestNumbers;

    /* Checks if a number is in the numbers list */
    bool numberInList(int num)
    {
        for (int i = 0; i < numbers.size(); i++)
        {
            if (num == numbers[i])
            {
                return true;
            }
        }
        return false;
    }

    /* Generate a list of N random numbers */
    void generateRandomNumbers()
    {
        for (int i = 0; i < N; i++)
        {
            bool uniqueNumberFound = false;
            while (!uniqueNumberFound)
            {
                int numberToInsert = rand() % (N * 10);
                if (!numberInList(numberToInsert))
                {
                    numbers.push_back(numberToInsert);

                    // Storing the k-smallest
                    if (currentKNodes < K)
                    {
                        kSmallestNumbers.insert(numberToInsert);
                        currentKNodes += 1;
                    }
                    else
                    {
                        if (numberToInsert < kSmallestNumbers.getMax())
                        {
                            kSmallestNumbers.removeMax();
                            kSmallestNumbers.insert(numberToInsert);
                        }
                    }
                    uniqueNumberFound = true;
                }
            }
        }
    }

    /* Print out all numbers */
    void printNumbers()
    {
        cout << "Numbers: ";
        for (int i = 0; i < numbers.size(); i++)
        {
            cout << numbers[i] << " ";
        }
        cout << endl;
    }

    void printKSmallestNumbers()
    {
        cout << "K-Smallest Numbers: ";
        kSmallestNumbers.printHeap();
        cout << endl;
    }

public:
    KSmallest(int noElements, int noKSmallestElements, int seed = 0)
    {
        N = noElements;
        K = noKSmallestElements;
        srand(seed);
        generateRandomNumbers();
        printNumbers();
        printKSmallestNumbers();
    }
};

int main()
{
    KSmallest ks(10, 3);

    // FibonacciHeap fh;
    // fh.insert(5);
    // fh.insert(3);
    // fh.insert(6);
    // fh.insert(7);
    // fh.insert(2);
    // fh.insert(8);
    // fh.insert(12);
    // fh.insert(14);
    // fh.insert(1);
    // fh.insert(23);
    // fh.insert(19);
    // fh.printHeap();
    // fh.getMax();
    // fh.remove(2);
    // fh.getMax();
    // fh.remove(3);
    // fh.printHeap();

    return 0;
}