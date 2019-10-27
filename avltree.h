#include "node.h"
#include <cstddef>
#include <stdio.h>
#include <cmath>
#include <vector>
using namespace std;
class AVLTree
{
public:
    Node *root;

    AVLTree(Node *root); // initialize a tree with a root
    AVLTree(vector<int> A, int start, int finish);
    ~AVLTree();
    int deletion_success;
    void inorder_tree_walk(Node *node);   // O(n)
    void preorder_tree_walk(Node *node);  // O(n)
    void postorder_tree_walk(Node *node); // O(n)
    void assign_parent(Node *root);
    void _transplant(Node *u, Node *v); // O(1)
    void get_height();
    int height(Node *root);                                      // O(1)
    int get_height(Node *root);                                  // O(1)
    int get_balance(Node *node);                                 // O(1)
    bool is_avl(Node *root);                                     // O(n log n)
    Node *insert(Node *root, int key);                           // O(log n) + O(log n)
    Node *_delete(Node *root, int key);                          // O(log n) + O(log n)
    Node *left_rotate(Node *node);                               // O(1)
    Node *right_rotate(Node *node);                              // O(1)
    Node *search(Node *x, int key);                              // O(log n)
    Node *tree_minimum(Node *x);                                 // O(log n)
    Node *tree_maximum(Node *x);                                 // O(log n)
    Node *tree_succsessor(Node *x);                              // O(log n)
    Node *root_from_array(vector<int> A, int start, int finish); // not using
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
    Node *temp = x;
    while (temp != NIL && key != temp->get_val())
    {
        if (key < temp->get_val())
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    return temp;
}

Node *AVLTree::tree_minimum(Node *x) // O(log n)
{
    Node *temp = x;
    while (temp->left != NIL)
    {
        temp = temp->left;
    }
    return temp;
}

Node *AVLTree::tree_maximum(Node *x) // O(log n)
{
    Node *temp = x;
    while (temp->right != NIL)
    {
        temp = temp->right;
    }
    return temp;
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

int AVLTree::height(Node *node)
{
    if (node == NIL)
    {
        return 0;
    }
    return node->height;
}

int AVLTree::get_height(Node *root)
{
    if (root == NIL)
    {
        return 0;
    }
    int leftHeight = height(root->left);

    int rightHeight = height(root->right);

    int max_height = max(leftHeight, rightHeight) + 1;
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

Node *AVLTree::insert(Node *node, int key)
{
    /*
    insert a node into an avl tree.
    */
    if (node == NIL)
    {
        return (newNode(key)); // O(1)
    }
    if (key < node->val)
    {
        node->left = this->insert(node->left, key); // T(n/2)
        node->left->p = node;
    }
    else if (key > node->val)
    {
        node->right = this->insert(node->right, key); // T(n/2)
        node->right->p = node;
    }
    else
    {
        return node;
    }
    node->height = 1 + max(height(node->left), height(node->right)); // O(1)
    int balance = this->get_balance(node);                           // O(1)
    if (balance > 1 && node->left != NIL && key < node->left->val)
    {
        return this->right_rotate(node); // O(1)
    }
    if (balance > 1 && node->left != NIL && key > node->left->val)
    {
        node->left = this->left_rotate(node->left);
        return this->right_rotate(node); // O(1)
    }
    if (balance < -1 && node->right != NIL && key > node->right->val)
    {
        return this->left_rotate(node); // O(1)
    }
    if (balance < -1 && node->right != NIL && key < node->right->val)
    {
        node->right = this->right_rotate(node->right);
        return this->left_rotate(node); // O(1)
    }
    return node;
}

int AVLTree::get_balance(Node *node)
{
    if (node == NIL)
    {
        return 0;
    }
    int left_height, right_height;
    left_height = height(node->left);
    right_height = height(node->right);
    return left_height - right_height;
}

bool AVLTree::is_avl(Node *root)
{
    if (root == NIL)
    {
        return true;
    }
    int balance = this->get_balance(root);
    if (abs(balance) <= 1 && this->is_avl(root->left) && this->is_avl(root->right))
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
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
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
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return x;
}

Node *AVLTree::_delete(Node *node, int key)
{

    if (node == NIL)
    {
        this->deletion_success = 0;
        return node;
    }
    //search for the required node
    if (key < node->val)
    {
        node->left = this->_delete(node->left, key);
    }
    else if (key > node->val)
    {
        node->right = this->_delete(node->right, key);
    }
    else
    {
        // found it
        // if it has one or no children
        if ((node->left == NIL) || (node->right == NIL))
        {
            Node *temp = node;

            if (node->left != NIL)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
            this->_transplant(temp, node);
            this->deletion_success = 1;
            free(temp);
        }
        else
        {
            // node with two children
            Node *temp = this->tree_minimum(node->right); // find successor
            node->val = temp->val;
            node->right = this->_delete(node->right, temp->val);
        }
    }
    if (node == NIL)
    {
        this->deletion_success = 1;
        return node;
    }
    node->height = this->get_height(node);
    int balance = this->get_balance(node);
    if (balance > 1 && this->get_balance(node->left) >= 0)
    {
        return this->right_rotate(node);
    }
    if (balance > 1 && this->get_balance(node->left) < 0)
    {
        node->left = this->left_rotate(node->left);
        return this->right_rotate(node);
    }
    if (balance < -1 && this->get_balance(node->right) <= 0)
    {
        return this->left_rotate(node);
    }
    if (balance < -1 && this->get_balance(node->right) > 0)
    {
        node->right = this->right_rotate(node->right);
        return this->left_rotate(node);
    }
    return node;
}