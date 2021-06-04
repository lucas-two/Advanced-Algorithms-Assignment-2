/* Q3. Red Black Tree vs. Van Emde Boas Tree*/
#include <iostream>
#include <string>
using namespace std;

class VEB
{
    // We have a universe of keys
    // But we only have a subset of those keys
    // as actual keys.

    // Tree stores a set of keys from the universe
    // Keys must be integers

    // We have a big array of size U (universe)
    // And we mark 1 in the indicies that we have keys for
};

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

    /* Check if the node is a left child of it's parent */
    bool isLeftChild(node *nodePointer)
    {
        return nodePointer->parent->left == nodePointer;
    }

    void toggleColor(node *nodePointer)
    {
        nodePointer->red = !(nodePointer->red);
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
            fixViolations(rootPointer);
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
                cout << "Im about to fix..." << nodePointer->left->value << endl;
                fixViolations(nodePointer->left);
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
                fixViolations(nodePointer->right);
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
        cout << "You're now in the process of fixing..." << Z->value << endl;
        // CASE I: Z is the root node
        if (Z == rootPointer)
        {
            Z->red = false; // Set to black
        }

        // If Z's parent is the root, the tree should be fine
        else if (Z->parent->value == rootPointer->value)
        {
            cout << "Me: " << Z->value << endl;
            cout << "My parent: " << Z->parent->value << endl;
            cout << "Root: " << rootPointer->value << endl;
            return;
        }

        // If Z has no uncle, but

        // CASE II: Z's uncle is red
        // -> (Parent is left child)
        else if (isLeftChild(Z->parent) && Z->parent->parent->right->red)
        {
            toggleColor(Z->parent);                // Toggle Z's parent
            toggleColor(Z->parent->parent);        // Toggle Z's grandparent
            toggleColor(Z->parent->parent->right); // Toggle Z's uncle
        }
        // -> (Parent is right child)
        else if (!isLeftChild(Z->parent) && Z->parent->parent->left->red)
        {
            toggleColor(Z->parent);               // Toggle Z's parent
            toggleColor(Z->parent->parent);       // Toggle Z's grandparent
            toggleColor(Z->parent->parent->left); // Toggle Z's uncle
        }

        // CASE III: Z's uncle is black (Zig-Zag)
        // -> (Z is right child) & (Parent is left child)
        else if (!isLeftChild(Z) && isLeftChild(Z->parent) && !(Z->parent->parent->right->red))
        {
            leftRotate(Z->parent);
        }
        // -> (Z is left child) & (Parent is right child)
        else if (isLeftChild(Z) && !isLeftChild(Z->parent) && !(Z->parent->parent->right->red))
        {
            rightRotate(Z->parent);
        }

        // CASE IV: Z's uncle is black (Zig-Zig)
        // -> (Z is right child) & (Parent is right child)
        else if (!isLeftChild(Z) && !isLeftChild(Z->parent) && !(Z->parent->parent->right->red))
        {
            toggleColor(Z->parent);         // Toggle Z's parent
            toggleColor(Z->parent->parent); // Toggle Z's grandparent
            leftRotate(Z->parent->parent);
        }
        // -> (Z is left child) & (Parent is left child)
        else if (isLeftChild(Z) && isLeftChild(Z->parent) && !(Z->parent->parent->right->red))
        {
            toggleColor(Z->parent);         // Toggle Z's parent
            toggleColor(Z->parent->parent); // Toggle Z's grandparent
            rightRotate(Z->parent->parent);
        }
    }

    void leftRotate(node *nodePointer)
    {
        // Temp nodes
        node *X = nodePointer;
        node *Y = X->right;
        node *Z = Y->left;

        // Swap pointers
        X->right = Z;
        Y->left = X;

        // Update parents
        Y->left->right->parent = Y->left;
        Y->left->parent = Y;
        Y->parent = X->parent;

        // Update to the rotated branch
        nodePointer = Y;
    }

    void rightRotate(node *nodePointer)
    {
        // Temp nodes
        node *Y = nodePointer;
        node *X = Y->left;
        node *Z = X->right;

        // Swap pointers
        Y->left = Z;
        X->right = Y;

        // Update parents
        X->right->left->parent = X->right;
        X->right->parent = X;
        X->parent = Y->parent;

        // Update to the rotated branch
        nodePointer = X;
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