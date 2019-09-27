#include <cstddef>

#define NIL NULL

class Node
{
private:
public:
    int val;
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
    ~Node();
};

Node::Node(int value)
{
    Node::val = value;
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
    left_child->p = this;
    this->left = left_child;
}

void Node::set_right(Node *right_child)
{
    right_child->p = this;
    this->right = right_child;
}