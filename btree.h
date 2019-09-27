#include "node.h"
#include <cstddef>
#include <stdio.h>

class BinaryTree
{
private:
public:
    Node *root;
    BinaryTree(Node *root);
    void inorder_tree_walk(Node *node);
    
    int search(Node *start);
    ~BinaryTree();
};

BinaryTree::BinaryTree(Node *root)
{
}

BinaryTree::~BinaryTree()
{
}

void BinaryTree::inorder_tree_walk(Node *node)
{
    if (node != NIL)
    {
        this->inorder_tree_walk(node->left);
        printf("%d\n", node->get_val());
        this->inorder_tree_walk(node->right);
    }
}

int BinaryTree::search(Node *start)
{

}