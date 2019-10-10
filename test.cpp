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
vector<int> create_random_data(int n, int min, int max)
{
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed); // a source of random data

    std::uniform_int_distribution<int> dist(min, max);
    std::vector<int> v(n);

    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

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
    vector<int>
        A = create_random_data(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    Node *root = newNode(A[0]);

    //display(A);

    AVLTree tree = AVLTree(root);
    auto start = high_resolution_clock::now();
    for (size_t i = 1; i < A.size(); i++)
    {
        Node *x = newNode(A[i]);
        tree.insert(x);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Insertion time " << duration.count() << " microseconds, size " << A.size() << endl;
    //printf("Inorder avl Tree: \n");
    //tree.inorder_tree_walk(tree.root);
    printf("\n");
    printf("Balance: %d\n", tree.get_balance(tree.root));
    printf("Height: %d\n", tree.get_height(tree.root));
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