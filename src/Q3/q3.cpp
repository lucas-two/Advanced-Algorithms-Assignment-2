/* Q3. Red Black Tree vs. Van Emde Boas Tree*/
#include <iostream>
using namespace std;

class RedBlackTree
{
    /*
    Rules:
    1. Nodes are either red or black.
    2. The root and leaf (NILL) nodes are black.
    3. If a node is red, it's children are black.
    4. All paths from root -> NILL leafs have same number
       of black nodes.
    */
private:
    struct node
    {
        bool red = true; // Whether the node is red (true) or black (false)
        int value;       // Value of the node
        node *left;      // Pointer to the node's left child
        node *right;     // Pointer to the node's right child
    };

    node *rootPointer; // Root node

    /* Check if the tree is empty */
    bool treeIsEmpty()
    {
        return rootPointer == NULL;
    }

    /* Check if a node is not null */
    bool nodeExists(node *nodePointer)
    {
        return nodePointer != NULL;
    }

    /* Create a new node */
    node *createNewNode(int value)
    {
        node *newNode = new node(); // Allocate memory for the new node
        newNode->value = value;     // Set it's value to the input value
        newNode->left = NULL;       // Set left child as null
        newNode->right = NULL;      // Set right child as null
        return newNode;             // Return a pointer to the new node
    }

    node *insertRecursively(int value, node *nodePointer)
    {
        // ROOT: Tree is empty and this is our root node
        if (treeIsEmpty())
        {
            rootPointer = createNewNode(value);
            return rootPointer;
        }

        // LEFT: Value should be on the left of our node
        else if (value < nodePointer->value)
        {
            // If there's already a node there, traverse to it.
            if (nodeExists(nodePointer->left))
            {
                insertRecursively(value, nodePointer->left);
            }
            // Otherwise, create a new node there.
            else
            {
                nodePointer->left = createNewNode(value);
                return nodePointer->left;
            }
        }
        // RIGHT: Value should be on the right of our node
        else if (value > nodePointer->value)
        {
            // If there's already a node there, traverse to it.
            if (nodeExists(nodePointer->right))
            {
                insertRecursively(value, nodePointer->right);
            }
            // Otherwise, create a new node there.
            else
            {
                nodePointer->right = createNewNode(value);
                return nodePointer->right;
            }
        }
        // EQUAL: This is an error case. We don't want equal values.
        else
        {
            cout << "[!] DUPLICATE VALUE: Not accepting equal values." << endl;
            return NULL;
        }
        return NULL;
    }

    void printTreeRecursively(node *nodePointer)
    {
        if (!treeIsEmpty())
        {
            if (nodeExists(nodePointer->left))
            {
                printTreeRecursively(nodePointer->left);
            }
            cout << nodePointer->value << " " << (nodePointer->red ? "Red" : "Black") << endl;

            if (nodeExists(nodePointer->right))
            {
                printTreeRecursively(nodePointer->right);
            }
        }
        else
        {
            cout << "Tree is empty." << endl;
        }
    }

    void fixViolations(node *Z)
    {
        // Z is the root
        cout << Z->value << endl;

        // Z's uncle is red

        // Z's uncle is black (triangle)

        // Z's uncle is black (line)
    }

    void search()
    {
    }

    void remove()
    {
    }

public:
    RedBlackTree()
    {
        rootPointer = NULL; // Initialise tree as empty
    }

    void insert(int value)
    {
        node *insertedNodePointer = insertRecursively(value, rootPointer);
        fixViolations(insertedNodePointer);
    }

    void printTree()
    {
        printTreeRecursively(rootPointer);
        cout << endl;
    }
};

int main()
{
    RedBlackTree rbt;

    rbt.insert(2);
    rbt.printTree();
    return 0;
}