// Libraries
#include <iostream>
#include <fstream>

// Namespace std
using namespace std;

// Files as redirections for streams of standard input / output
const char * stream_in  = "./data/tbdw.in";
const char * stream_out = "./data/tbdw.out";

// Tree Node Structure
struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};

// Functions declarations
Node *insertNode(Node *node, int arg);
Node *deleteNode(Node *node, int arg);
Node *searchNode(Node *node, int arg);
Node *findMinNode(Node *node);
Node *findMaxNode(Node *node);
Node *findNextNode(Node *node, int arg);
Node *findPrevNode(Node *node, int arg);
void inorderTraversal(Node *node);
void preorderTraversal(Node *node);
void postorderTraversal(Node *node);

// --------------------------------------------------------

// Operations Functions

// -- Add new Node
Node *insertNode(Node *node, int arg)
{
    // create new node
    if (node == NULL) {
        node = new Node();
        node->val = arg;
        node->left = NULL;
        node->right = NULL;
    } 
    // search for new node's place
    else 
    {
        // check left subtree
        if (arg < node->val)
            node->left = insertNode(node->left, arg);
        
        // check right subtree
        else if (arg > node->val)
            node->right = insertNode(node->right, arg);
        
        // if there is already existed node with 'arg' value:
        //   do nothing
    }
    return node;
}

// -- Delete node
Node *deleteNode(Node *node, int arg)
{
    // base case
    if (node == NULL)
        return node;
    
    // check left subtree
    if (arg < node->val)
        node->left = deleteNode(node->left, arg);

    // check right subtree
    else if (arg > node->val)
        node->right = deleteNode(node->right, arg);
    
    // if node's value is equal to 'arg',
    // then that is the node to be deleted
    else 
    {
        // node is a leaf - has no children
        if (node->left == NULL && node->right == NULL)
            return NULL;

        // node with two children
        if (node->left != NULL && node->right != NULL)
        {
            Node *rightChild = node->right;
            node = node->left;
            node->right = rightChild;
        }

        // node with one child
        //  - left
        else if (node->left != NULL)
        {
            node = node->left;
        }

        // node with one child
        //  - right
        else
        {
            node = node->right;
        }
    }
    return node;
}

// -- Check if node with 'arg' value exists
Node *searchNode(Node *node, int arg)
{
    // base case
    if (node == NULL)
        return node;

    // auxillary node pointer
    Node * tmp = NULL;

    // check left subtree
    if (arg < node->val)
        tmp = searchNode(node->left, arg);

    // check right subtree
    else if (arg > node->val)
        tmp = searchNode(node->right, arg);
    
    // if node's value is equal to 'arg',
    // then that is the node you are looking for
    else
        return node;

    return tmp;
}

// -- Find minimum value in subtree with root in 'node'
Node *findMinNode(Node *node)
{
    Node * current = node;

    // find left extreme leaf
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// -- Find maximum value in subtree with root in 'node'
Node *findMaxNode(Node *node)
{
    Node *current = node;

    // find right extreme leaf
    while (current && current->right != NULL)
        current = current->right;
    return current;
}

// -- Find right child of 'node' with 'arg' value
Node *findNextNode(Node *node, int arg)
{
    // search for 'node' with 'arg' value
    Node *tmp = searchNode(node, arg);

    // if searched node does not exists
    if (tmp == NULL)
        return tmp;

    // if searched node exists 
    //  - return his right child
    else 
    {
        return tmp->right;
    }
}

// -- Find left child of 'node' with 'arg' value
Node *findPrevNode(Node *node, int arg)
{
    // search for 'node' with 'arg' value
    Node *tmp = searchNode(node, arg);

    // if searched node does not exists
    if (tmp == NULL)
        return tmp;

    // if searched node exists
    //  - return his left child
    else
    {
        return tmp->left;
    }
}

// LVR - Left, Visited, Right
void inorderTraversal(Node *node)
{
    // Check left subtree
    if (node->left != NULL) 
        inorderTraversal(node->left);

    cout << node->val << " ";

    // Check right subtree
    if (node->right != NULL)
        inorderTraversal(node->right);
}

// VLR - Visited, Left, Right
void preorderTraversal(Node *node)
{
    cout << node->val << " ";

    // Check left subtree
    if (node->left != NULL)
        inorderTraversal(node->left);

    // Check right subtree
    if (node->right != NULL)
        inorderTraversal(node->right);
}

// LRV - Left, Right, Visited
void postorderTraversal(Node *node)
{
    // Check left subtree
    if (node->left != NULL)
        inorderTraversal(node->left);

    // Check right subtree
    if (node->right != NULL)
        inorderTraversal(node->right);

    cout << node->val << " ";
}


// -- Interpret and execute operation
Node *execute(Node *root, char opt, int arg)
{
    // auxillary node pointer
    Node *node = NULL;

    switch(opt)
    {
        case 'I':
            root = insertNode(root, arg);
            break;
        case 'D':
            root = deleteNode(root, arg);
            break;
        case 'S':
            node = searchNode(root, arg);
            if (node != NULL)
                cout << node->val << endl;
            else
                cout << "-" << endl;
            break;
        case 'X':
            if (arg == 0)
                node = findMinNode(root);
            else if (arg == 1)
                node = findMaxNode(root);
            
            if (node != NULL)
                cout << node->val << endl;
            break;
        case 'N':
            node = findNextNode(root, arg);
            if (node != NULL)
                cout << node->val << endl;
            else
                cout << "-" << endl;
            break;
        case 'P':
            node = findPrevNode(root, arg);
            if (node != NULL)
                cout << node->val << endl;
            else
                cout << "-" << endl;
            break;
        case 'R':
            if (arg == 0){
                inorderTraversal(root);
            }
            else if (arg == 1){
                preorderTraversal(root);
            }
            else if (arg == 2){
                postorderTraversal(root);
            }
            cout << endl;
            break;
    }
    
    return root;
}

// -- Test Solver
void solveTest(int testInd)
{
    cout << "test " << testInd << endl;

    // -- tree's root
    Node * root = NULL;

    // -- operations count
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        // -- get operation type and its argument
        char opt = '\0';
        int arg = 0;
        cin >> opt >> arg;

        // -- execute operation
        root = execute(root, opt, arg);
    }
}

// -- DRIVER --
int main()
{ 
    // Change I/O streams source/destination
    // -- new input source
    ifstream in(stream_in);

    // -- new output destination
    ofstream out(stream_out);

    // -- optional performance optimizations
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // -- redirect I/O streams
    cin.rdbuf(in.rdbuf());
    cout.rdbuf(out.rdbuf());

    // Main program
    // -- tests count
    int t = 0;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        solveTest(i+1);
    }

    return 0;
}