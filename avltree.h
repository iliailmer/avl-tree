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
    int deletion_success;
    void inorder_tree_walk(Node *node);
    void preorder_tree_walk(Node *node);
    void postorder_tree_walk(Node *node);
    void assign_parent(Node *root);

    void _transplant(Node *u, Node *v);

    void get_height();

    int get_height(Node *root);
    int get_balance(Node *node);
    bool is_avl(Node *root);
    Node *insert(Node *root, int key);
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

Node *AVLTree::insert(Node *root, int key)
{
    /*
    insert a node into a binary tree.
    */
    if (root == NIL)
    {
        return (newNode(key)); // O(1)
    }
    if (key < root->val)
    {
        root->left = this->insert(root->left, key); // T(n/2)
        root->left->p = root;
    }
    else if (key > root->val)
    {
        root->right = this->insert(root->right, key); // T(n/2)
        root->right->p = root;
    }
    else // Equal keys are not allowed in BST
    {
        return root;
    }
    root->height = this->get_height(root); // O(hlog(h))
    int balance = this->get_balance(root); // O(1)
    if (balance > 1 && key < root->left->val)
    {
        return this->right_rotate(root); // O(1)
    }
    if (balance > 1 && key > root->left->val)
    {
        this->left_rotate(root->left);
        return this->right_rotate(root); // O(1)
    }
    if (balance < -1 && key > root->right->val)
    {
        return this->left_rotate(root); // O(1)
    }
    if (balance < -1 && key < root->right->val)
    {
        this->right_rotate(root->right);
        return this->left_rotate(root); // O(1)
    }
    return root;
}

int AVLTree::get_balance(Node *node)
{
    if (node == NIL)
    {
        return 0;
    }
    int left_height, right_height;
    if (node->left == NIL)
    {
        left_height = 0;
    }
    else
    {
        left_height = node->left->height;
    }
    if (node->right == NIL)
    {
        right_height = 0;
    }
    else
    {
        right_height = node->right->height;
    }

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
            Node *temp = NIL;

            if (node->left != NIL)
            {
                temp = node->left;
            }
            else
            {
                temp = node->right;
            }
            if (temp == NIL) // no children
            {
                temp = node;
                node = NIL;
            }
            else
            {
                this->_transplant(node, temp);
            }
            this->deletion_success = 1;
            free(temp);
        }
        else
        {
            // node with two children
            Node *temp = this->tree_minimum(node->right);
            node->val = temp->val;
            node->right = this->_delete(node->right, temp->val);
            this->deletion_success = 1;
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

/* 
if (root == NIL)
    {
        return root;
    }
    Node *y;
    // Classic BST Deletion
    if (key < root->get_val())
    {
        root->left = this->_delete(root->left, key);
    }
    else if (key > root->get_val())
    {
        root->right = this->_delete(root->right, key);
    }
    else
    { // root is the node we are deleting
        if (root->left == NIL)
        {
            this->_transplant(root, root->right);
            root = root->right;
        }
        else if (root->right == NIL)
        {
            this->_transplant(root, root->left);
            root = root->left;
        }
        else
        {
            y = this->tree_minimum(root->right);
            if (y->p != root)
            {
                this->_transplant(y, y->right);
                y->right = root->right;
                y->right->p = y;
            }
            this->_transplant(root, y);
            y->left = root->left;
            y->left->p = y;
            y->height = this->get_height(y);
            root = y;
        }
    }
    // deletion is done, now onto rebalancing
    root->height = this->get_height(root); // get the new heights
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
    return root; // to avoid a warning 

*/

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
    return node; // no rebalancing required
}