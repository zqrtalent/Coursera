#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int reach(vector<vector<int>> &adj, int* pArrVisited, int x, int y) 
{
    // Check if visited.
    if(pArrVisited[x] == 1)
        return 0;

    // Mark visited.
    pArrVisited[x] = 1;

    auto connectionsX = adj[x];
    int x2;
    for(int i=0; i<connectionsX.size(); i++)
    {
        x2 = connectionsX[i];
        if(x2 == y || reach(adj, pArrVisited, x2, y) == 1)
            return 1;
    }

    return 0;
}

int main()
{
    size_t n, m;
    //m = n = 4;
    cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    
    int* pArrVisited = new int[n];
    memset(pArrVisited, 0, sizeof(int)*n);

    // int xx[4];
    // xx[0] = 1;
    // xx[1] = 3;
    // xx[2] = 4;
    // xx[3] = 1;

    // int yy[4];
    // yy[0] = 2;
    // yy[1] = 2;
    // yy[2] = 3;
    // yy[3] = 4;

    int x, y;
    for (size_t i = 0; i < m; i++) 
    {
        //int x, y;
        //x = xx[i];
        //y = yy[i];
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    
    //x = 1;
    //y = 4;
    cin >> x >> y;
    cout << reach(adj, pArrVisited, x - 1, y - 1) << endl;
    return 0;
}