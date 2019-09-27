#include "btree.h"

#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[])
{
    Node root = Node(12);
    Node lc = Node(8);
    Node rc = Node(14);

    root.set_left(&lc);
    root.set_right(&rc);

    printf("root: %d\n", root.get_val());
    printf("left: %d\n", root.get_left());
    printf("left's parent: %d\n", lc.get_parent());
    printf("right: %d\n", root.get_right());
    printf("left's parent: %d\n\n", rc.get_parent());

    BinaryTree tree = BinaryTree(&root);

    tree.inorder_tree_walk(&root);
    return 0;
}
