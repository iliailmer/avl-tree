#include "btree.h"
#include <stdio.h>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    int n = 9;
    vector<int> A(n, 0);

    for (int i = 0; i < n; i++)
    {
        A[i] = i;
    }
    BinaryTree tree = BinaryTree(A, 0, n - 1);
    return 0;
}
/*
    Node root = Node(12);
    Node lc = Node(8);
    Node rc = Node(14);
    Node a = Node(2);
    lc.set_left(&a);
    Node b = Node(5);
    lc.set_right(&b);

    

    root.set_left(&lc);
    root.set_right(&rc);

    printf("root: %d\n", root.get_val());
    printf("left: %d\n", root.get_left());
    printf("left's parent: %d\n", lc.get_parent());

    printf("left's left child: %d\n", lc.get_left());
    printf("left's right child: %d\n", lc.get_right());
    printf("right: %d\n", root.get_right());
    printf("right's parent: %d\n\n", rc.get_parent());

    BinaryTree tree = BinaryTree(&root);

    tree.inorder_tree_walk(&root);
    int key = 3;
    Node *result = tree.search(&root, key);
    if (result == NIL || result == nullptr)
    {
        printf("KEY %d NOT FOUND\n", key);
    }
    else
    {
        printf("%d\n", result->get_val());
    }
    

    printf("Tree Height: %d\n", tree.get_height(&root));
*/