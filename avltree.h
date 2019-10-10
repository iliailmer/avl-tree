#include "node.h"
#include <cstddef>
#include <stdio.h>
#include <cmath>
#include <vector>
using namespace std;
/*TODO: 1) insertion-> add rebalancing  */
class AVLTree
{
public:
    Node *root;

    AVLTree(Node *root); // initialize a tree with a root
    AVLTree(vector<int> A, int start, int finish);
    ~AVLTree();

    void inorder_tree_walk(Node *node);
    void preorder_tree_walk(Node *node);
    void postorder_tree_walk(Node *node);
    void assign_parent(Node *root);
    void insert(Node *node);
    void _transplant(Node *u, Node *v);

    void get_height();

    int get_height(Node *root);
    int get_balance(Node *node);
    bool is_avl();
    Node *_delete(Node *root, int key);
    Node *rebalance(Node *node);
    Node *left_rotate(Node *node);
    Node *right_rotate(Node *node);
    Node *search(Node *x, int key);
    Node *tree_minimum(Node *x);
    Node *tree_maximum(Node *x);
    Node *tree_succsessor(Node *x);
    Node *root_from_array(vector<int> A, int start, int finish);
};

AVLTree::AVLTree(vector<int> A, int start, int finish)
{
    /*
    Constructor from a sorted array.
    */
    this->root = (this->root_from_array(A, start, finish));
    this->assign_parent(this->root);                   // this makes contruction of a tree nlogn
    this->root->height = this->get_height(this->root); // this makes construction of a tree nlogn
}

AVLTree::AVLTree(Node *root)
{
    /*
    Constructor from a single root
    */
    this->root = root;
}

AVLTree::~AVLTree()
{
    /* Destructor */
}

void AVLTree::inorder_tree_walk(Node *node)
{
    /* Inorder Traversal */
    if (node != NIL)
    {
        this->inorder_tree_walk(node->left);
        printf("%d ", node->get_val());
        this->inorder_tree_walk(node->right);
    }
}

void AVLTree::preorder_tree_walk(Node *node)
{
    /* Inorder Traversal */
    if (node != NIL)
    {
        this->preorder_tree_walk(node->left);
        this->preorder_tree_walk(node->right);
        printf("%d ", node->get_val());
    }
}

void AVLTree::postorder_tree_walk(Node *node)
{
    /* Inorder Traversal */
    if (node != NIL)
    {
        printf("%d ", node->get_val());
        this->postorder_tree_walk(node->left);
        this->postorder_tree_walk(node->right);
    }
}

void AVLTree::assign_parent(Node *root)
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

Node *AVLTree::search(Node *x, int key)
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

Node *AVLTree::tree_minimum(Node *x)
{
    while (x->left != NIL)
    {
        x = x->left;
    }
    return x;
}

Node *AVLTree::tree_maximum(Node *x)
{
    while (x->right != NIL)
    {
        x = x->right;
    }
    return x;
}

Node *AVLTree::tree_succsessor(Node *x)
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

int AVLTree::get_height(Node *root)
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

void AVLTree::get_height()
{
    int height = this->get_height(this->root);
}

Node *AVLTree::root_from_array(vector<int> A, int start, int finish)
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

void AVLTree::insert(Node *node)
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
        while (y != this->root)
        {
            y = this->rebalance(y);
            y = y->p;
        }
    }
    else
    {
        y->right = node;
        while (y != this->root)
        {
            y = this->rebalance(y);
            y = y->p;
        }
    }
}

int AVLTree::get_balance(Node *node)
{
    if (node == NIL)
    {
        return 0;
    }
    return this->get_height(node->left) - this->get_height(node->right);
}

bool AVLTree::is_avl()
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

void AVLTree::_transplant(Node *u, Node *v)
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

Node *AVLTree::left_rotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
    {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NIL)
    {
        this->root = y;
    }
    else if (x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
    return y;
}

Node *AVLTree::right_rotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NIL)
    {
        x->right->p = y;
    }
    x->p = y->p;
    if (y->p == NIL)
    {
        this->root = x;
    }
    else if (y == y->p->left)
    {
        y->p->left = x;
    }
    else
    {
        y->p->right = x;
    }
    x->right = y;
    y->p = x;

    return x;
}

Node *AVLTree::_delete(Node *root, int key)
{
    if (root == NIL)
    {
        return root;
    }
    Node *deleted = root;
    Node *y;
    // Classic BST Deletion
    if (key < root->get_val())
    {
        deleted = this->_delete(root->left, key);
    }
    else if (key > root->get_val())
    {
        deleted = this->_delete(root->right, key);
    }
    else
    {
        if (deleted->left == NIL)
            this->_transplant(deleted, deleted->right);

        else if (deleted->right == NIL)
        {
            this->_transplant(deleted, deleted->left);
        }
        else
        {
            y = this->tree_minimum(deleted->right);
            if (y->p != deleted)
            {
                this->_transplant(y, y->right);
                y->right = deleted->right;
                y->right->p = y;
            }
            this->_transplant(deleted, y);
            y->left = deleted->left;
            y->left->p = y;
        }
        this->get_height(); // possible bottleneck, recalculating heights
        // rebalancing the tree.
        int balance = this->get_balance(root);
        if (balance > 1 && this->get_balance(root->left) >= 0)
        {
            return this->right_rotate(root);
        }
        if (balance > 1 && this->get_balance(root->left) < 0)
        {
            this->left_rotate(root->left);
            return this->right_rotate(root);
        }
        if (balance < -1 && this->get_balance(root->right) <= 0)
        {
            return this->left_rotate(root);
        }
        if (balance < -1 && this->get_balance(root->right) <= 0)
        {
            this->right_rotate(root->right);
            return this->left_rotate(root);
        }
    }
    return NULL; // to avoid a warning
}

Node *AVLTree::rebalance(Node *node)
{
    int balance = this->get_balance(node);
    if (balance > 1 && this->get_balance(node->left) >= 0)
    {
        return this->right_rotate(node);
    }
    if (balance > 1 && this->get_balance(node->left) < 0)
    {
        this->left_rotate(node->left);
        return this->right_rotate(node);
    }
    if (balance < -1 && this->get_balance(node->right) <= 0)
    {
        return this->left_rotate(node);
    }
    if (balance < -1 && this->get_balance(node->right) <= 0)
    {
        this->right_rotate(node->right);
        return this->left_rotate(node);
    }
    return NULL; // to avoid a warning
}