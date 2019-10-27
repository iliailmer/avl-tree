#include "avltree.h"
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <stdio.h>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int create_random_data(int min, int max)
{
    std::random_device r;
    std::seed_seq seed{r()};
    std::mt19937 eng(seed); // a source of random data

    std::uniform_int_distribution<int> dist(min, max);
    int v;
    v = dist(eng);
    return v;
}
void countLeaves(Node *tracker, int *counter);
int countNodes(Node *tracker);

void display(vector<int> A)
{
    printf("Input Array: \n");
    for (size_t i = 0; i < A.size(); i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    vector<int> A;
    Node *root = NIL;

    AVLTree tree = AVLTree(root);
    /*     for (int i = 0; i < atoi(argv[1]); i++)
    {
        A.push_back(i);
    } */
    //display(A);
    for (size_t i = 0; i < atoi(argv[1]); i++)
    {
        tree.root = tree.insert(tree.root, i);
    }
    printf("\nThe AVL-Tree is of height %d\n", tree.root->height);
    int random = create_random_data(atoi(argv[2]), atoi(argv[3])); // get 1 random integer
    int val, counter, nodes;
    counter = 0;
    nodes = countNodes(tree.root);
    countLeaves(tree.root, &counter);
    printf("\nLeaves: %d\nNodes: %d\n", counter, nodes);
    printf("\nInserting random number %d\n", random);
    auto start = high_resolution_clock::now();
    tree.root = tree.insert(tree.root, random);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // count leaves
    counter = 0;
    nodes = countNodes(tree.root);
    countLeaves(tree.root, &counter);
    printf("The new AVL-Tree: ");
    //tree.inorder_tree_walk(tree.root);
    printf("\nLeaves: %d\nNodes: %d\nHeight: %d\n", counter, nodes, tree.root->height);

    cout << "Insertion time " << duration.count() << " microseconds, size " << nodes << endl;

    cout << "Enter a value to find:" << endl;

    cin >> val;
    Node *found = NIL;

    start = high_resolution_clock::now();
    found = tree.search(tree.root, val);
    stop = high_resolution_clock::now();

    if (found != NIL)
    {
        if (found == found->p->left)
        {
            printf("Success, found %d, its parent is %d, its sibling (right) is %d\n", found->get_val(), found->p->get_val(), found->p->right->get_val());
        }
        if (found == found->p->right)
        {
            printf("Success, found %d, its parent is %d, its sibling (left) is %d\n", found->get_val(), found->p->get_val(), found->p->left->get_val());
        }
    }
    else
    {
        printf("Search failed, %d not found :(\n", val);
    }
    cout << "Search time " << duration.count() << " microseconds, size " << nodes << endl;

    cout << "Enter a value to delete" << endl;
    cin >> val;
    printf("\n");
    printf("Before: ");
    printf("\n\tLeaves: %d\n\tNodes: %d\n\tHeight: %d\n", counter, nodes, tree.root->height);
    //tree.inorder_tree_walk(tree.root);
    start = high_resolution_clock::now();
    Node *deleted = tree._delete(tree.root, val);
    stop = high_resolution_clock::now();

    counter = 0;
    nodes = countNodes(tree.root);
    countLeaves(tree.root, &counter);
    printf("\n");
    printf("After: ");
    printf("\n\tLeaves: %d\n\tNodes: %d\n\tHeight: %d\n", counter, nodes, tree.root->height);
    //tree.inorder_tree_walk(tree.root);
    printf("\n");
    cout << "Deletion time " << duration.count() << " microseconds, tree size " << nodes << " nodes." << endl;
    cout << "Deletion status is " << tree.deletion_success << endl;
    printf("\n");

    printf("Balance of the root: %d\n", tree.get_balance(tree.root));
    // printf("Height: %d\n", tree.get_height(tree.root));

    if (tree.is_avl(tree.root))
    {
        printf("Is AVL\n");
    }
    else
    {
        printf("Is Not AVL\n");
    }
    counter = 0;
    nodes = countNodes(tree.root);
    countLeaves(tree.root, &counter);
    printf("Leaves: %d\nNodes: %d\n", counter, nodes);
    return 0;
}

void countLeaves(Node *tracker, int *counter)
{
    if ((tracker->left == NIL) && (tracker->right == NIL))
    {
        *counter = *counter + 1;
    }
    else
    {
        if (tracker->left != NIL)
        {
            countLeaves(tracker->left, counter);
        }
        if (tracker->right != NIL)
        {
            countLeaves(tracker->right, counter);
        }
    }
}
int countNodes(Node *tracker)
{
    int count = 1;
    if (tracker->left != NIL)
    {
        count += countNodes(tracker->left);
    }
    if (tracker->right != NIL)
    {
        count += countNodes(tracker->right);
    }
    return count;
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