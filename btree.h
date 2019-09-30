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
    void insert(Node *node);
    void _transplant(Node *u, Node *v);
    void _delete(int key);
    void left_rotate(Node *node);
    void right_rotate(Node *node);

    int get_height(Node *root);
    int get_balance(Node *node);
    bool is_avl();
    Node *search(Node *x, int key);
    Node *tree_minimum(Node *x);
    Node *tree_maximum(Node *x);
    Node *tree_succsessor(Node *x);
    Node *root_from_array(vector<int> A, int start, int finish);
};

BinaryTree::BinaryTree(vector<int> A, int start, int finish)
{
    /*
    Constructor from an array.
    */
    this->root = (this->root_from_array(A, start, finish));
    this->assign_parent(this->root);                   // this makes contruction of a tree nlogn
    this->root->height = this->get_height(this->root); // this makes construction of a tree nlogn
}

BinaryTree::BinaryTree(Node *root)
{
    /*
    Constructor from a single root
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
        printf("%d ", node->get_val());
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
        printf("%d ", node->get_val());
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
    while (x != NIL && key != x->get_val())
    {
        if (key < x->get_val())
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return x;
    /* if (x == NIL)
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
    } */
}

Node *BinaryTree::tree_minimum(Node *x)
{
    while (x->left != NIL)
    {
        x = x->left;
    }
    return x;
}

Node *BinaryTree::tree_maximum(Node *x)
{
    while (x->right != NIL)
    {
        x = x->right;
    }
    return x;
}

Node *BinaryTree::tree_succsessor(Node *x)
{
    if (x->right == NIL)
    {
        return this->tree_minimum(x);
    }
    Node *y = x->p;
    Node *tmp = x;
    while (y != NIL && tmp == y->right)
    {
        tmp = y;
        y = y->p;
    }
    free(tmp);
    return y;
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
    root->height = max_height;
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

void BinaryTree::insert(Node *node)
{
    /*
    insert a node into a binary tree.
    */
    Node *y = NIL;
    Node *x = this->root;
    while (x != NIL)
    {
        y = x;
        if (node->get_val() < x->get_val())
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    node->p = y;
    if (y == NIL)
    {
        this->root = node;
    }
    else if (node->get_val() < y->get_val())
    {
        y->left = node;
    }
    else
    {
        y->right = node;
    }
}

int BinaryTree::get_balance(Node *node)
{
    if (node == NIL)
    {
        return 0;
    }
    return this->get_height(node->left) - this->get_height(node->right);
}

bool BinaryTree::is_avl()
{
    int balance = this->get_balance(this->root);
    if (balance == 0 || balance == 1 || balance == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BinaryTree::_transplant(Node *u, Node *v)
{
    if (u->p == NIL)
    {
        this->root = v;
    }
    else if (u == u->p->left)
    {
        u->p->left = v;
    }
    else
    {
        u->p->right = v;
    }
    if (v != NIL)
    {
        v->p = u->p;
    }
}

void BinaryTree::_delete(int key)
{
    Node *x = this->root;
    while (x->val != key && x != NIL)
    {
        if (key > x->val)
        {
            x = x->right;
        }
        else
        {
            x = x->left;
        }
    }
    // x is the pointer to the node to be deleted

    if (x->left == NIL)
    {
        this->_transplant(x, x->right);
    }
    else if (x->right == NIL)
    {
        this->_transplant(x, x->left);
    }
    else
    {
        Node *y = this->tree_minimum(x->right);
        if (y->p != x)
        {
            this->_transplant(y, y->right);
            y->right = x->right;
            y->right->p = y;
        }
        this->_transplant(x, y);
        y->left = x->left;
        y->left->p = y;
    }
}