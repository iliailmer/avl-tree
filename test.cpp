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
int create_random_data(int min, int max)
{
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed); // a source of random data

    std::uniform_int_distribution<int> dist(min, max);
    int v;
    v = dist(eng);
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
    vector<int> A = create_random_data(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

    Node *root = NIL;

    //display(A);

    AVLTree tree = AVLTree(root);

    for (size_t i = 0; i < A.size(); i++)
    {
        tree.root = tree.insert(tree.root, A[i]);
    }

    printf("\nThe Tree: ");
    tree.inorder_tree_walk(tree.root);
    int random = create_random_data(atoi(argv[2]), atoi(argv[3])); // get 1 random integer
    int val;
    printf("\nInserting %d\n", random);
    auto start = high_resolution_clock::now();
    tree.root = tree.insert(tree.root, random);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    printf("The Tree: ");
    tree.inorder_tree_walk(tree.root);
    printf("\n");

    cout << "Insertion time " << duration.count() << " microseconds, size " << A.size() << endl;

    cout << "Enter a value to find:" << endl;

    cin >> val;
    start = high_resolution_clock::now();
    Node *found = NIL;
    found = tree.search(tree.root, val);
    stop = high_resolution_clock::now();
    if (found != NIL)
    {
        printf("Success, found %d, its parent was %d\n", found->get_val(), found->p->get_val());
    }
    else
    {
        printf("Search failed, %d not found\n", val);
    }
    cout << "Search time " << duration.count() << " microseconds, size " << A.size() << endl;

    cout << "Enter a value to delete" << endl;
    cin >> val;
    printf("\n");
    printf("Before: ");
    tree.inorder_tree_walk(tree.root);
    start = high_resolution_clock::now();
    Node *deleted = tree._delete(tree.root, val);
    stop = high_resolution_clock::now();
    printf("\n");
    printf("After: ");
    tree.inorder_tree_walk(tree.root);
    printf("\n");
    cout << "Deletion time " << duration.count() << " microseconds, size " << A.size() << endl;
    cout << "Deletion status is " << tree.deletion_success<<endl;
    printf("\n");
    printf("Balance or the root: %d\n", tree.get_balance(tree.root));
    printf("Height: %d\n", tree.get_height(tree.root));
    if (tree.is_avl(tree.root))
    {
        printf("Is AVL\n");
    }
    else
    {
        printf("Is Not AVL\n");
    }
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