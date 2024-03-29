#include "avltree.h"
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <stdio.h>
#include <iostream>
#include <fstream>
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
void print2DUtil(Node *root, int space, ofstream &outfile)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->right, space, outfile);

    // Print current node after space
    // count
    outfile << "\n"; //cout << endl;
    for (int i = 3; i < space; i++)
        outfile << " ";           //cout << " ";
    outfile << root->val << "\n"; // << "(" << root->height << ")"

    //cout << root->val << "\n";

    // Process left child
    print2DUtil(root->left, space, outfile);
}
int main(int argc, char const *argv[])
{
    Node *root = NIL;

    AVLTree tree = AVLTree(root);

    int operation_count = 0;
    for (size_t i = 0; i < atoi(argv[1]); i++)
    {
        tree.root = tree.insert(tree.root, i, &operation_count);
    }

    operation_count = operation_count / atoi(argv[1]);
    tree.inorder_tree_walk(tree.root);
    printf("\nThe AVL-Tree is of height %d, root is %d\n", tree.root->height, tree.root->get_val());
    printf("%d", tree.root->left->val);
    ofstream outfile;
    outfile.open("original.txt", ios::out);
    print2DUtil(tree.root, 0, outfile);
    outfile.close();

    int val, counter, nodes;
    counter = 0;
    nodes = countNodes(tree.root);
    countLeaves(tree.root, &counter);
    printf("\nLeaves: %d\nTotal Nodes: %d\n", counter, nodes);

    cout << "How many values to insert?" << endl;
    int i, n, to_insert;
    cin >> n;
    i = 0;
    while (i < n)
    {
        i += 1;
        cout << "Enter a value to insert:" << endl;
        cin >> to_insert;

        operation_count = 0;
        auto start = high_resolution_clock::now();
        tree.root = tree.insert(tree.root, to_insert, &operation_count);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // count leaves
        counter = 0;
        nodes = countNodes(tree.root);
        countLeaves(tree.root, &counter);
        printf("The new AVL-Tree: ");
        //tree.inorder_tree_walk(tree.root);
        printf("\n\tLeaves: %d\n\tNodes: %d\n\tHeight: %d\n", counter, nodes, tree.root->height);

        cout << "Insertion time " << duration.count() << " microseconds, size " << nodes << endl;
        cout << "Operation count " << operation_count << " operations" << endl;
    }
    outfile.open("inserted.txt");
    print2DUtil(tree.root, 0, outfile);
    outfile.close();
    cout << "\nInsertion finished, begin search\n"
         << endl;

    cout << "Enter a value to find:" << endl;
    cin >> val;
    Node *found;
    operation_count = 0;
    auto start = high_resolution_clock::now();
    found = tree.search(tree.root, val, &operation_count);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (found != NIL)
    {
        printf("Success, found %d,\toperation count %d\n", found->get_val(), operation_count);
    }
    else
    {
        printf("Search failed, %d not found :(\tOperation count %d\n", val, operation_count);
    }
    cout << "Search time " << duration.count() << " microseconds" << endl;

    cout << "\nSearch finished, begin deletion\n"
         << endl;
    cout << "Enter a value to delete" << endl;
    cin >> val;
    operation_count = 0;
    printf("\n");
    printf("Before: ");

    outfile.open("deletion_before.txt", ios::out);
    if (atoi(argv[1]) <= 20000)
    {
        //tree.inorder_tree_walk(tree.root);
        print2DUtil(tree.root, 0, outfile);
    }
    else
    {
        printf("Tree too big, no output.");
    }
    outfile.close();
    printf("\n\tLeaves: %d\n\tNodes: %d\n\tHeight: %d\n", counter, nodes, tree.root->height);
    start = high_resolution_clock::now();
    Node *deleted = tree._delete(tree.root, val, &operation_count);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);

    counter = 0;
    nodes = countNodes(tree.root);
    countLeaves(tree.root, &counter);
    printf("\n");
    printf("After: ");
    outfile.open("deletion_after.txt", ios::out);
    if (atoi(argv[1]) <= 20000)
    {
        //tree.inorder_tree_walk(tree.root);
        print2DUtil(tree.root, 0, outfile);
    }
    else
    {
        printf("Tree too big, no inorder output.");
    }
    outfile.close();

    printf("\n\tLeaves: %d\n\tNodes: %d\n\tHeight: %d\n", counter, nodes, tree.root->height);
    printf("\n");
    cout << "Deletion time " << duration.count() << " microseconds, tree size " << nodes << " nodes." << endl;
    cout << "Deletion status is " << tree.deletion_success << " (1 - success, 0 - fail, no such element found)" << endl;
    cout << "Operation count: " << operation_count << " operations" << endl;

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