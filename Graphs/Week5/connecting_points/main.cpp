#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;
using std::max;

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

	DisjointSets(int size): size(size), max_table_size(0), sets(size) 
  {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
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

double minimum_distance(vector<int> x, vector<int> y)
{
    double result = 0.;
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

    for(int i=0; i<edges.size(); i++)
    {
      int srcNode = edges[i].srcNode, destNode = edges[i].destNode;
      if(disjointSet.getParent(srcNode) != disjointSet.getParent(destNode))
      {
        disjointSet.merge(srcNode, destNode);
        result += edges[i].weight;
      }
    }
    return result;
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
