#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

/*
An undirected graph is called bipartite if its vertices can be split into two parts such that each edge of the 
graph joins to vertices from different parts. Bipartite graphs arise naturally in applications where a graph is 
used to model connections between objects of two different types (say, boys and girls; or students and dormitories).
*/

bool explore_bipartite(vector<vector<int>> &adj, int node, int* visitedWithSetNumber, int setNumber/*1 or 2*/)
{
    // Mark as visited.
    visitedWithSetNumber[node] = setNumber;

    vector<int> &edges = adj[node];
    int setNumber2 = (setNumber == 1 ? 2 : 1);

    for(int i=0; i<edges.size(); i++)
    {
        // // node -> edges[i]
        // for(int j=0; j<currentSet.size(); j++){
        //     if(edges[i] == currentSet[j])
        //         return false;
        // }

        //if(std::find(currentSet.begin(), currentSet.end(), edges[i]) != currentSet.end())
        //    return false;

        if(visitedWithSetNumber[edges[i]] != 0)
        {
            if(visitedWithSetNumber[edges[i]] == setNumber)
                return false; // Should have been part of that set.
            continue;
        }

        if(!explore_bipartite(adj, edges[i], visitedWithSetNumber, setNumber2))
            return false;
    }


    return true;
}

int bipartite(vector<vector<int>> &adj) 
{
    int* visited = new int[adj.size()];
    for(int i=0; i<adj.size(); i++)
        visited[i] = 0;
    //memset(visited, 0, sizeof(int)*adj.size());

    //vector<int> set1, set2;
    bool isBipartite = explore_bipartite(adj, 0, visited, 1);

    delete [] visited;
    return (isBipartite /*&& (set1.size() + set2.size() == adj.size())*/) ? 1 : 0 ; // 1 or 0
}

int main() 
{
    int n, m;
    std::cin >> n >> m;
    //n =4; m = 4;
    //n =5; m = 4;

    //int arrX[] = {1, 4, 2, 3};
    //int arrY[] = {2, 1, 3, 1};
    //int arrX[] = {5, 4, 3, 1};
    //int arrY[] = {2, 2, 4, 4};

  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    //x = arrX[i]; y = arrY[i];
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  std::cout << bipartite(adj);
}