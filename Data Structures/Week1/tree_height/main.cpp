#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    int key;
    Node* parent;
    vector<Node*> children;
};

int tree_height(Node* pNode);

int main()
{
    int n;
    cin >> n;

    int k;
    Node* pArr = new Node[n];
    for(int i=0; i<n; i++)
    {
        Node* pNode = &pArr[i];
        cin >> pNode->key;
        pNode->parent = nullptr;
    }

    Node* pRoot = nullptr;
    for(int i=0; i<n; i++)
    {
        if(pArr[i].key == -1)
        {
            pRoot = &pArr[i];
        }
        else
        {
            auto parent = (Node*)&pArr[pArr[i].key];
            parent->children.push_back(&pArr[i]);
            pArr[i].parent = parent; 
        }
    }

    cout << tree_height(pRoot) << endl;

    delete [] pArr;
    return 0;
}


int tree_height(Node* pNode)
{
    if( pNode == nullptr )
        return 0;
    
    int maxsize = 1;
    for(int i=0; i<pNode->children.size(); i++)
    {
        maxsize = max(maxsize, tree_height(pNode->children[i])+1);
    }
    
    return maxsize;
}