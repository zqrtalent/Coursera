#include <iostream>
#include <vector>
#include <string.h>
using std::vector;

/*
Discrete knapsack problem:
Example demonstrating to build a matrix and use backtracing for optimal solution.

$30    $14   $16    $9
6       3     4     2

    0   1   2   3   4   5   6   7   8   9   10
0   0   0   0   0   0   0   0   0   0   0   0 
1   0   0   0   0   0   0   30  30  30  30  30
2   0   0   0  14  14  14   30  30  30  44  44
3   0   0   0  14  16  16   30  30  30  44  46
4   0   0   9  14  16  23   30  30  39  44  46

                  1   2   3   4
Optimal solution: [1] [0] [1] [0]


Th another sample matrix.

    0   1   2   3   4   5   6   7   8   9   10
0   0   0   0   0   0   0   0   0   0   0   0 
1   0   1   1   1   1   1   1   1   1   1   1
4   0   1   1   1   4   5   5   5   5   5   5
8   0   1   1   1   4   5   5   5   8   9   9
*/

int optimal_weight(int W, const vector<int> &w) 
{
  // Matrix array allocation and initialization.
  int n = w.size() + 1;
  int** matrix = new int*[n];
  for(int i=0; i<n; i++)
  {
      matrix[i] = new int[W+1];
      if(i == 0)
        memset(matrix[i], 0, sizeof(int)*(W+1));
      else
        matrix[i][0] = 0;
  }

  // Loop for each item to place in knapsack.
  for(int i=1; i<n; i++)
  {
    // Loop for weight from 1 to total weight of knapsack.
    for(int j=1; j<=W; j++)
    {
      matrix[i][j] = matrix[i-1][j];
      if(w[i-1] <= j)
      {
        int val = matrix[i-1][j - w[i-1]] + w[i-1]; // In our case i-th value is weight.
        if(val > matrix[i][j])
          matrix[i][j] = val; 
      }
    }
  }

  // // Output matrix.
  // for(int i=0; i<n; i++)
  // {
  //     for(int j=0; j<=W; j++)
  //       std::cout << matrix[i][j] << " ";
  //     std::cout << std::endl;
  // }

  int result = matrix[n-1][W];
  // Clean up memory usage.
  delete [] matrix[0];
  delete [] matrix;
  return result;
}

int main() 
{
  int n = 3, W = 10;
  int arr[] = { 1, 4, 8 };
  std::cin >> W >> n;

  vector<int> w(n);
  for (int i = 0; i < n; i++)
  {
    std::cin >> w[i];
    //w[i] = arr[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}