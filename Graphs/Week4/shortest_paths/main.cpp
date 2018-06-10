#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::unordered_map;
using std::set;

typedef struct Edge
{
    int srcNode;
    int destNode;
    int weight;
} Edge;

void shortest_paths(
    vector<vector<int>> &adj, 
    vector<vector<int>> &cost, 
    int s, 
    vector<long long> &distances, 
    vector<int> &reachable, 
    vector<int> &shortest,
    int numEdges) 
{
    //write your code here
    vector<int> prev(adj.size(), -1);

    int source = s;
    distances[source] = 0;
    // vector<Edge> edges(numEdges, Edge());

    // int loop = 0;
    // for(int i=0; i<adj.size(); i++)
    // {
    //     for(int j=0; j<adj[i].size(); j++)
    //     {
    //         edges[loop].srcNode = i;
    //         edges[loop].destNode = adj[i][j];
    //         edges[loop].weight = cost[i][j];
    //         loop ++;
    //     }
    // }

    queue<int> qPath;
    // relax edges.
    int numVertices = adj.size();
    for(int x=1; x<=adj.size()-1; x++)
    {
        for(int i=0; i<adj.size(); i++)
        {
            for(int j=0; j<adj[i].size(); j++)
            {

                // edges[loop].srcNode = i;
                // edges[loop].destNode = adj[i][j];
                // edges[loop].weight = cost[i][j];
                // loop ++;

                // v - dest node.
                // u - src node.
                // w - weight of the edge.
                int v = adj[i][j], u = i, w = cost[i][j];
                if( distances[v] > distances[u] + w)
                {
                    distances[v] = distances[u] + w;
                    prev[v] = u;
                    reachable[v] = 1;

                    if(x == numVertices - 1)
                    {
                        qPath.push(v);
                        std::cout << v << " ";
                    }
                }
            }
        }

        // for(Edge& edge: edges)
        // {
        //     if( distances[edge.destNode] > distances[edge.srcNode] + edge.weight)
        //     {
        //         distances[edge.destNode] = distances[edge.srcNode] + edge.weight;
        //         prev[edge.destNode] = edge.srcNode;
        //     }
        // }
    }

    //Determine shortest path for each vertex.
    unordered_map<int, int> map_predecessors;
    for(int i=0; i<prev.size(); i++)
    {
        if(prev[i] != -1)
            map_predecessors.emplace(prev[i], i);
    }

    int srcNode = source;
    //set<int> reachable_nodes;
    //reachable_nodes.emplace(srcNode);
    reachable[srcNode] = 3;
    std::unordered_map<int, int>::iterator it = map_predecessors.find(srcNode);
    while(it != map_predecessors.end())
    {
        srcNode = it->second;
        //reachable_nodes.emplace(srcNode);
        reachable[srcNode] = 3;
        it = map_predecessors.find(srcNode);
    }

    for(int i=0; i<adj.size(); i++)
    {
        // There is a path
        //if(distances[i] != std::numeric_limits<int>::max())
        if(distances[i] != 0x7fffffff)
        {
            //if(reachable_nodes.find(i) == reachable_nodes.end())
            if(reachable[i] == 3)
                shortest[i] = 1;
            else
                shortest[i] = 0;
            reachable[i] = 1;
        }
        else // There is no path.
        {
            reachable[i] = 0;
        }
    }
}

int main() 
{
    int n, m, s;
    n = 6; m = 7;
    //n = 5; m = 4;
    //std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());

    int arrX[] = {1, 2, 1, 3, 5, 4, 6};
    int arrY[] = {2, 3, 3, 5, 4, 3, 1};
    int arrW[] = {10, 5, 100, 7, 10, -18, -1};

    // int arrX[] = {1, 4, 2, 3};
    // int arrY[] = {2, 1, 3, 1};
    // int arrW[] = {1, 2, 2, -5};
    for (int i = 0; i < m; i++) 
    {
        int x, y, w;
        x = arrX[i]; y = arrY[i]; w = arrW[i];
        //std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }

    s = 1;
    //s = 4;
    //std::cin >> s;
    s--;
    //vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<long long> distance(n, std::numeric_limits<int>::max());
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    shortest_paths(adj, cost, s, distance, reachable, shortest, m);

    for (int i = 0; i < n; i++) 
    {
        if (!reachable[i]) 
            std::cout << "*\n";
        else if (!shortest[i]) 
            std::cout << "-\n";
        else 
            std::cout << distance[i] << "\n";
    }
}