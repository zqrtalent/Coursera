#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#define MIN_VALUE 0x8000000000000000
#define MAX_VALUE 0x7FFFFFFFFFFFFFFF

struct Node;
long long GetMinKey(vector<Node>& tree, int node);
long long GetMaxKey(vector<Node>& tree, int node);

struct Node 
{
    long key;
    int left;
    int right;
    int parent;

    long long minKey;
    long long maxKey;

    Node() : key(0), left(-1), right(-1), parent(-1), minKey(-1), maxKey(-1) {}
    Node(int key_, int left_, int right_, int parent_) : key(key_), left(left_), right(right_), parent(parent_), minKey(-1), maxKey(-1) {}
};

bool isValidNode(vector<Node>& tree, int node)
{
    if(tree[node].left != -1 && !isValidNode(tree, tree[node].left))
        return false;
    if(tree[node].right != -1 && !isValidNode(tree, tree[node].right))
        return false;

    long long key = tree[node].key;
    long long minKey = GetMaxKey(tree, tree[node].left);
    long long maxKey = GetMinKey(tree, tree[node].right);
    if( (tree[node].left == -1 || key > minKey) && 
        (tree[node].right == -1 || key <= maxKey))
        return true;
    return false;
}

long long GetMinKey(vector<Node>& tree, int node)
{
    if(node == -1)
        return MAX_VALUE;

    if(tree[node].minKey != -1)
        return tree[node].minKey;

    long long key = tree[node].key;
    long long minKey = GetMinKey(tree, tree[node].left);

    if( ((tree[node].left == -1) || key > minKey) && 
        ((tree[node].right == -1) || key <= GetMaxKey(tree, tree[node].right)) ){
        tree[node].minKey = (tree[node].left == -1 || tree[node].right == -1) ? key : minKey;
        return tree[node].minKey;
    }

    tree[node].minKey = MAX_VALUE;
    return MAX_VALUE;
}

long long GetMaxKey(vector<Node>& tree, int node)
{
    if(node == -1)
        return MIN_VALUE;

    if(tree[node].maxKey != -1)
        return tree[node].maxKey;

    long long key = tree[node].key; 
    long long maxKey = GetMaxKey(tree, tree[node].right);

    if( ((tree[node].right == -1) || key <= maxKey) && 
        ((tree[node].left == -1) || key > GetMinKey(tree, tree[node].left)) ){
        tree[node].maxKey = (tree[node].left == -1 || tree[node].right == -1) ? key : maxKey;
        return tree[node].maxKey;
    }
    tree[node].maxKey = MIN_VALUE;
    return MIN_VALUE;
}

bool IsBinarySearchTree(vector<Node>& tree) 
{
    // Implement correct algorithm here
    if(tree.size() <= 1)
        return true;
    return isValidNode(tree, 0);
}

int main() 
{
    // int nodes = 3;
    // int vertices[3][3] = {{2, 1, 2}, {1, -1, -1}, {2, -1, -1}};
    // int nodes = 5;
    // int vertices[5][3] = {{1, -1, 1}, {2, -1, 2}, {3, -1, 3}, {4, -1, 4}, {5, -1, -1}};
    int nodes = 7;
    //int vertices[7][3] = {{3, 1, 2}, {2, 3, 4}, {6, 5, 6}, {1, -1, -1}, {4, -1, -1}, {5, -1, -1}, {7, -1, -1}};
    int vertices[7][3] = {{4, 1, 2}, {2, 3, 4}, {6, 5, 6}, {1, -1, -1}, {2, -1, -1}, {5, -1, -1}, {7, -1, -1}};
    cin >> nodes;

    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) 
    {
        int key, left, right;
        // key = vertices[i][0];
        // left = vertices[i][1];
        // right = vertices[i][2];
        cin >> key >> left >> right;
        
        tree.push_back(Node(key, left, right, -1));
    }

    // Assign parent indexes.
    for (int i = 0; i < nodes; ++i) 
    {
        if(tree[i].left != -1)
            tree[tree[i].left].parent = i;
        if(tree[i].right != -1)
            tree[tree[i].right].parent = i;
    }

    if (IsBinarySearchTree(tree))
        cout << "CORRECT" << endl;
    else
        cout << "INCORRECT" << endl;
    return 0;
}