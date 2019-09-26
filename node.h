class Node
{
private:
    int val;
    Node * left;
    Node * right;
public:
    int get_val();

    Node(int value);
    ~Node();
};

Node::Node(int value)
{
    Node::val = value;
}

Node::~Node()
{
}
