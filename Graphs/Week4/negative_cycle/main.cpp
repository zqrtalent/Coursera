#include <iostream>
#include <vector>
#include <limits.h>
using std::vector;

typedef struct Edge
{
    int srcNode;
    int destNode;
    int weight;
} Edge;

int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost, int numEdges)
{
    vector<long> distances(adj.size(), INT_MAX);
    //vector<int> prev(adj.size(), -1);

    int source = 0;
    distances[source] = 0;
    vector<Edge> edges(numEdges, Edge());

    int loop = 0;
    for(int i=0; i<adj.size(); i++)
    {
        for(int j=0; j<adj[i].size(); j++)
        {
            edges[loop].srcNode = i;
            edges[loop].destNode = adj[i][j];
            edges[loop].weight = cost[i][j];
            loop ++;
        }
    }

    // relax edges.
    for(int i=1; i<=adj.size()-1; i++)
    {
        for(Edge& edge: edges)
        {
            if( distances[edge.destNode] > distances[edge.srcNode] + edge.weight)
            {
                distances[edge.destNode] = distances[edge.srcNode] + edge.weight;
                //prev[edge.destNode] = edge.srcNode;
            }
        }
    }

    // Check for negative-weight cycles.
    for(Edge& edge: edges)
    {
        if(distances[edge.destNode] > distances[edge.srcNode] + edge.weight)
        {
            return 1; // Negative cycle.
        }
    }

    return 0;
}

int main() 
{
    int n, m;
    n=4;m=4;
    //n=5;m=4;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());

    int arrX[] = {1, 4, 2, 3};
    int arrY[] = {2, 1, 3, 1};
    int arrW[] = {1, 2, 2, -5};

    for (int i = 0; i < m; i++) 
    {
        int x, y, w;
        //x = arrX[i];y = arrY[i];w = arrW[i];
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost, m);
}
