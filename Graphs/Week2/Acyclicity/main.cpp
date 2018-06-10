#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
using namespace std;

/*
Theorem: If G contains a cycle, it cannot be linearly ordered! 
How to linearly order? Find sinc node, remove and add as a last element in array.
*/

// Remove sink vertices.
bool hasCycle(vector<vector<int>> &adj, int* pArrVisited, int* pArrRemoved, int x) 
{
    if(pArrVisited[x] == 1)
        return true;

    pArrVisited[x] = 1;

    int x2;
    int i = 0;
    auto connections = adj[x];
    int size = connections.size();

    while(i < size)
    {
        x2 = connections[i];
        //if(pArrVisited[x2] == 1)
        //    return 1;

        if(pArrRemoved[x2] != 1)
        {
            if(hasCycle(adj, pArrVisited, pArrRemoved, x2) == 1)
                return true;
            if(pArrRemoved[x2] == 1)
            {
                connections.erase(connections.begin() + i);
                size --;
                continue;
            }
        }

        i ++;
    }

    // Remove sinc node.
    if(size == 0)
        pArrRemoved[x] = 1;

    pArrVisited[x] = 0;
    return false;
}

int acyclic(vector<vector<int>> &adj) 
{
    int* pArrVisited = new int[adj.size()];
    int* pArrRemoved = new int[adj.size()];
    memset(pArrVisited, 0, sizeof(int)*adj.size());
    memset(pArrRemoved, 0, sizeof(int)*adj.size());
    int nRet = 0;

    for(int i=0; i<adj.size(); i++)
    {
        if(pArrRemoved[i] == 0 && 
            hasCycle(adj, pArrVisited, pArrRemoved, i))
        {
            nRet = 1;
            break;
        }
    }

    delete [] pArrVisited;
    delete [] pArrRemoved;
    return nRet;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    //n = 4;
    //m = 4;
    vector<vector<int> > adj(n, vector<int>());

    //int nn[] = {1, 2, 3 ,3};
    //int mm[] = {2, 3 ,4, 1};
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    //x = nn[i];
    //y = mm[i];
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
  
}