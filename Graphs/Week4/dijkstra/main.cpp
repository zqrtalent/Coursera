#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

typedef struct FlightInfo
{
    int id;         // Node index
    int distance;   // Used as a key.
} FlightInfo;

class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
{reverse=revparam;}

  bool operator() (const FlightInfo& lhs, const FlightInfo &rhs) const
  {
    if (reverse) return (lhs.distance > rhs.distance);
    else return (lhs.distance < rhs.distance);
  }
};

int distance(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, int t) 
{
    vector<int> dist(adj.size());
    vector<int> prev(adj.size());
    vector<int> latest_dist_values(adj.size());
    
    priority_queue<FlightInfo, vector<FlightInfo>, mycomparison> prior_queue(mycomparison(true));
    for(int i=0; i<adj.size(); i++)
    {
        if(i != s)
        {
            dist[i] = 0x7fffffff;
            prev[i] = -1;
            latest_dist_values[i] = dist[i];
            prior_queue.emplace(FlightInfo { i, dist[i] });
        }
    }

    dist[s] = 0;
    latest_dist_values[s] = dist[s];
    prior_queue.emplace(FlightInfo {  s, dist[s] });

    while(!prior_queue.empty())
    {
        int u = prior_queue.top().id;
        int distance = prior_queue.top().distance;
        prior_queue.pop();

        // Check for latest value.
        if(latest_dist_values[u] != distance)
            continue;

        int index = 0;
        for(int v : adj[u])
        {
            // Update distance value.
            int newDist = dist[u] + cost[u][index]; 
            if(newDist > 0 && dist[v] > newDist)
            {
                dist[v] = newDist;
                prev[v] = u;
                
                //priority_queue
                prior_queue.emplace(FlightInfo {v, dist[v]});
                latest_dist_values[v] = dist[v];
            }

            index ++;
        }
    }

    return dist[t] == 0x7fffffff ? -1 : dist[t];
}

int main() 
{
    /*
    59 124 132 232 321 242 354 541 253 344 15
    */

    int n, m;
    n = 4; m = 4;
    int arrX[] = {1, 4, 2, 1};
    int arrY[] = {2, 1, 3, 3};
    int arrW[] = {1, 2, 2, 5};
    std::cin >> n >> m;
    
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());

    for (int i = 0; i < m; i++) 
    {
        int x, y, w;
        std::cin >> x >> y >> w;
        //x = arrX[i]; y = arrY[i]; w  = arrW[i];

        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }

    int s, t;
    //s = 1; t = 3;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
