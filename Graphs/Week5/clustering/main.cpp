#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <set>

using std::vector;
using std::pair;
using std::max;
using std::set;

struct DisjointSetsElement 
{
	int size, parent, rank;
  	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets 
{
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;
    //set<int> parents; // For clustering.
    int numParents; // NUmer of clusters.

    DisjointSets(int size): size(size), max_table_size(0), sets(size)
    {
        for (int i = 0; i < size; i++)
        {
            sets[i].parent = i;
            sets[i].size = 1;
            //parents.emplace(i);
        }

        numParents = size;
    }

    int getParent(int table) 
    {
        // find parent and compress path
        if(table != sets[table].parent)
        {
            sets[table].parent = getParent(sets[table].parent);
        }
        return sets[table].parent;
    }

    bool merge(int destination, int source) 
    {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        bool ret = false;

        if (realDestination != realSource) 
        {
            ret = true;
            // merge two components
            sets[realDestination].size += sets[realSource].size;
            sets[realSource].size = 0; 

            // Remove parent.
            //parents.erase(parents.find(sets[realSource].parent));
            numParents --;

            // use union by rank heuristic
            sets[realSource].parent = realDestination;
            if(sets[realSource].rank >= sets[realDestination].rank)
                sets[realDestination].rank = sets[realSource].rank + 1; 

            // update max_table_size
            max_table_size = max(max_table_size, sets[realDestination].size);
        }

        return ret;
    }
};

double CalcWeight(int x1, int y1, int x2, int y2) 
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

typedef struct Edge
{
    int srcNode;
    int destNode;
    double weight;

    Edge(int src, int dest, double w): srcNode(src), destNode(dest), weight(w) {}
} Edge;

bool CompareEdges(Edge a, Edge b) 
{
    return a.weight < b.weight;
}

double clustering(vector<int> x, vector<int> y, int k) 
{
    //write your code here
    int n = x.size();
    DisjointSets disjointSet(n);
    vector<Edge> edges;

    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            edges.push_back(Edge(i, j, CalcWeight(x[i], y[i], x[j], y[j])));
        }
    }
    std::sort(edges.begin(), edges.end(), CompareEdges);

    // Minimum distance between connected components(clusters).
    double minDistance = edges[edges.size()-1].weight + 100.0;
    for(int i=0; i<edges.size(); i++)
    {
        int srcNode = edges[i].srcNode, destNode = edges[i].destNode;
        if(disjointSet.getParent(srcNode) != disjointSet.getParent(destNode))
        {
            // Momet when number of clusters equal to number k.
            //if(disjointSet.parents.size() == k)
            if(disjointSet.numParents == k)
            {
                if(minDistance > edges[i].weight)
                    minDistance = edges[i].weight;
            }
            else
            {
                disjointSet.merge(srcNode, destNode);
            }
        }
    }

    return minDistance;
} 

int main() 
{
    size_t n;
    int k;

    n = 12;
    std::cin >> n;
    vector<int> x(n), y(n);

    int arrX[] = {7, 4, 5, 1, 2, 5, 3, 7, 2, 4, 6, 2};
    int arrY[] = {6, 3, 1, 7, 7, 7, 3, 8, 8, 4, 7, 6};

    for (size_t i = 0; i < n; i++) 
    {
        //x[i] = arrX[i]; y[i] = arrY[i];
        std::cin >> x[i] >> y[i];
    }

    //2.828427125
    
    k = 3;
    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
