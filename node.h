#include <cstddef>

#define NIL NULL

class Node
{
private:
public:
    int val;
    int height;
    Node *left;
    Node *right;
    Node *p;

    int get_val();
    int get_left();
    int get_right();
    int get_parent();
    void set_left(Node *left_child);
    void set_right(Node *right_child);

    Node(int value);
    Node();
    ~Node();
};

Node::Node()
{
}

Node::Node(int value)
{
    Node::val = value;
    Node::height = 1;
    Node::left = NIL;
    Node::right = NIL;
    Node::p = NIL;
}

Node::~Node()
{
}

int Node::get_val()
{
    return this->val;
}

int Node::get_left()
{
    return this->left->get_val();
}

int Node::get_right()
{
    return this->right->get_val();
}

int Node::get_parent()
{
    return this->p->get_val();
}

void Node::set_left(Node *left_child)
{
    this->left = left_child;
    this->left->p = this;
}

void Node::set_right(Node *right_child)
{
    this->right = right_child;
    this->right->p = this;
}

Node *newNode(int value)
{
    Node *node = new Node();
    node->val = value;
    node->left = NIL;
    node->right = NIL;
    node->p = NIL;
    node->height = 0;
    return node;
}

/*Node *build_from_array(vector<int> A, int start, int finish)
{
    if (start > finish)
    {
        return NIL;
    }
    int mid = (start + finish) / 2;
    Node root = Node(A[mid]);

    Node *onLeft = build_from_array(A, start, mid - 1);   //left subtree
    Node *onRight = build_from_array(A, mid + 1, finish); //right subtree

    root.set_left(onLeft);
    root.set_right(onRight);
    return &root;
}*/