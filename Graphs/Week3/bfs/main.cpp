#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

/*Minimum number of edges from node u to node v*/
int distance(vector<vector<int>>& adj, int fromNode, int toNode, int nodesCt)
{
    int n = adj.size();
    int* distances = new int[n];
    for(int i=0; i<nodesCt; i++)
        distances[i] = -1;

    int* prev = new int[n];
    queue<int> q;
    q.push(fromNode-1);
    distances[fromNode-1] = 0;

    int u, v;
    while(!q.empty())
    {
        v = q.front();
        q.pop();

        vector<int> edges = adj[v];
        for(int i=0; i<edges.size(); i++)
        {
            u = edges[i];
            if(distances[u] == -1)
            {
                distances[u] = distances[v] + 1;
                prev[u] = v;

                q.push(u);
            }
        }
    }

    int min_edges = distances[toNode-1];
    delete [] distances;
    delete [] prev;
    return min_edges;
}

int main() 
{
    int n, m;
    cin >> n >> m;
    //n = 5; m = 4;

    int arrX[] = {5, 1, 3, 1};
    int arrY[] = {2, 3, 4, 4};

    vector<vector<int>> adj(n, vector<int>());

    int x, y;
    for(int i=0; i<m; i++)
    {
        cin >> x >> y;
        //x = arrX[i]; y = arrY[i];

        adj[x-1].push_back(y-1);
        adj[y-1].push_back(x-1); 
    }

    int u, v;
    cin >> u >> v;
    //u = 3; v = 5;

    int min_distance = distance(adj, u, v, n);
    cout << min_distance << endl;
}

/*
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}

*/