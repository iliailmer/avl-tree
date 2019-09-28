#include "node.h"
#include <cstddef>
#include <stdio.h>
#include <cmath>
#include <vector>
using namespace std;
/*TODO: 1) insertion, deletion, completion, rotations.
        2) Check specific AVL-Tree methods that I need*/
class BinaryTree
{
public:
    Node *root;

    BinaryTree(Node *root); // initialize a tree with a root
    BinaryTree(vector<int> A, int start, int finish);
    ~BinaryTree();

    void inorder_tree_walk(Node *node);
    void preorder_tree_walk(Node *node);
    void postorder_tree_walk(Node *node);
    void assign_parent(Node *root);
    int get_height(Node *root);

    Node *search(Node *x, int key);
    Node *root_from_array(vector<int> A, int start, int finish);
};

BinaryTree::BinaryTree(vector<int> A, int start, int finish)
{
    this->root = (this->root_from_array(A, start, finish));
    this->assign_parent(this->root);
}
BinaryTree::BinaryTree(Node *root)
{
    /*
    Constructor
    */
    this->root = root;
}

BinaryTree::~BinaryTree()
{
    /* Destructor */
}

void BinaryTree::inorder_tree_walk(Node *node)
{
    /* Inorder Traversal */
    if (node != NIL)
    {
        this->inorder_tree_walk(node->left);
        printf("%d\n", node->get_val());
        this->inorder_tree_walk(node->right);
    }
}

void BinaryTree::preorder_tree_walk(Node *node)
{
    /* Inorder Traversal */
    if (node != NIL)
    {
        this->preorder_tree_walk(node->left);
        this->preorder_tree_walk(node->right);
        printf("%d\n", node->get_val());
    }
}

void BinaryTree::postorder_tree_walk(Node *node)
{
    /* Inorder Traversal */
    if (node != NIL)
    {
        printf("%d ", node->get_val());
        this->postorder_tree_walk(node->left);
        this->postorder_tree_walk(node->right);
    }
}

void BinaryTree::assign_parent(Node *root)
{
    if (root != NIL)
    {
        if (root->left != NIL)
        {
            root->left->p = root;
            this->assign_parent(root->left);
        }
        if (root->right != NIL)
        {
            root->right->p = root;
            this->assign_parent(root->right);
        }
        }
}

Node *BinaryTree::search(Node *x, int key)
{
    /* Search for a key */
    if (x == NIL)
    {
        return nullptr;
    }
    if (x->get_val() == key)
    {
        return x;
    }
    if (key < x->get_val())
    {
        return this->search(x->left, key);
    }
    else
    {
        return this->search(x->right, key);
    }
}

int BinaryTree::get_height(Node *root)
{
    if (root == NIL)
    {
        return 0;
    }
    int leftHeight = this->get_height(root->left);
    int rightHeight = this->get_height(root->right);

    int max_height = fmax(leftHeight, rightHeight) + 1;

    return max_height;
}

Node *BinaryTree::root_from_array(vector<int> A, int start, int finish)
{
    if (start > finish)
    {
        return NIL;
    }
    int mid = (start + finish) / 2;
    Node *root = newNode(A[mid]);

    root->left = root_from_array(A, start, mid - 1);
    root->right = root_from_array(A, mid + 1, finish);

    return root;
}