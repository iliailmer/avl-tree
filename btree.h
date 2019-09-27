#include "node.h"
#include <cstddef>
#include <stdio.h>

class BinaryTree
{
private:
public:
    Node *root;
    int height;

    BinaryTree(Node *root);
    ~BinaryTree();

    void inorder_tree_walk(Node *node);
    Node *search(Node *x, int key);
};

BinaryTree::BinaryTree(Node *root)
{
    /*
    Constructor
    */
    this->root = root;
    this->height = 1;
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

Node *BinaryTree::search(Node *x, int key)
{
    /* Search for a key */
    if (x == NIL || x->get_val() == key)
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
