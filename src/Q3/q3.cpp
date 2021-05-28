/* Q3. Red Black Tree vs. Van Emde Boas Tree*/
#include <iostream>
#include <string>
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
        node *parent;    // Pointer to the node's parent
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
    node *createNewNode(int value, node *parentNode)
    {
        node *newNode = new node();   // Allocate memory for the new node
        newNode->value = value;       // Set it's value to the input value
        newNode->parent = parentNode; // Set the node's parent to the parent node
        newNode->left = NULL;         // Set left child as null
        newNode->right = NULL;        // Set right child as null
        return newNode;               // Return a pointer to the new node
    }

    void insertRecursively(int value, node *nodePointer)
    {
        // ROOT: Tree is empty and this is our root node
        if (treeIsEmpty())
        {
            rootPointer = createNewNode(value, nodePointer);
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
                nodePointer->left = createNewNode(value, nodePointer);
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
                nodePointer->right = createNewNode(value, nodePointer);
            }
        }
        // EQUAL: This is an error case. We don't want equal values.
        else
        {
            cout << "[!] DUPLICATE VALUE: Not accepting equal values." << endl;
        }
    }

    void printTreeRecursively(node *nodePointer)
    {
        if (!treeIsEmpty())
        {
            if (nodeExists(nodePointer->left))
            {
                printTreeRecursively(nodePointer->left);
            }

            cout << nodePointer->value << " " << (nodePointer->red ? "(Red)" : "(Black)") << " Parent: " << (nodePointer->parent == NULL ? "None" : to_string(nodePointer->parent->value)) << endl;

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

        // -> Toggle it black
        cout << Z->value << endl;

        // Z's uncle is red
        // -> Toggle Z's parent, grandparent, uncle

        // Z's uncle is black (triangle)
        // (Z is left child, Z's parent is right child)
        // OR
        // (Z is right child, Z's parent is left child)

        // Z's uncle is black (line)
    }

    void leftRotate()
    {
    }

    void rightRotate()
    {
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
        insertRecursively(value, rootPointer);
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

    rbt.insert(5);
    rbt.insert(4);
    rbt.insert(1);
    rbt.insert(10);
    rbt.insert(11);
    // rbt.insert(4);
    // rbt.insert(6);
    rbt.printTree();
    return 0;
}