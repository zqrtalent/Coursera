#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

void dfs(vector<vector<int> > &adj, vector<int> &order, int* pArrRemoved, int x, int* removedCt) 
{
    int x2;
    int i = 0;
    auto connections = adj[x];
    int size = connections.size();
    int removedChildCt = 0;

    while(i < size)
    {
        x2 = connections[i];
        if(pArrRemoved[x2] != 1)
        {
            dfs(adj, order, pArrRemoved, x2, removedCt);
            
            if(pArrRemoved[x2] == 1)
            {
                connections.erase(connections.begin() + i);
                size --;
                continue;
            }
        }
        else
        {
          removedChildCt ++;
        }

        i ++;
    }

    // Remove sinc node.
    if((size - removedChildCt) == 0)
    {
        pArrRemoved[x] = 1;
    }

    (*removedCt) ++;
    order[adj.size() - *removedCt] = x;
}     

vector<int> toposort(vector<vector<int> > adj) {
  
    vector<int> order(adj.size(), 0);

    int* pArrVisited = new int[adj.size()];
    int* pArrRemoved = new int[adj.size()];
    memset(pArrVisited, 0, sizeof(int)*adj.size());
    memset(pArrRemoved, 0, sizeof(int)*adj.size());
    int removedCt = 0;

    for(int i=0; i<adj.size(); i++)
    {
        if(pArrRemoved[i] == 0)
            dfs(adj, order, pArrRemoved, i, &removedCt);
    }

    delete [] pArrVisited;
    delete [] pArrRemoved;

  return order;
}

/*
What is topological sort?
Basically we run depth first search and reverse post order numbers.
Simple right?
*/
int main() {
  size_t n, m;
  std::cin >> n >> m;
  //n=4;
  //m=1;

  //int nn[] = {2, 3, 3, 4, 4, 5, 5};
  //int mm[] = {1, 2, 1, 3, 1, 2, 3};
  int nn[] = {3};
  int mm[] = {1};
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    //x = nn[i];
    //y = mm[i];
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}