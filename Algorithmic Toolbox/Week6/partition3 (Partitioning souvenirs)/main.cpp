#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;

/*
~Dynamic Programming~

You and two of your friends have just returned back home after visiting various countries. 
Now you would like to evenly split all the souvenirs that all three of you bought.

https://en.wikipedia.org/wiki/Partition_problem
https://en.wikipedia.org/wiki/Subset_sum_problem
*/

/* Recursive approach. */
// int knapsack(unordered_map<int,int> &values, vector<int>& weights, int w)
// {
//     // Lookup for value by specified weight.
//     unordered_map<int,int>::const_iterator iFind = values.find(w);
//     if(iFind != values.end())
//         return iFind->second;

//     values.emplace(w, 0); // Insert new value.

//     unordered_map<int, int>::iterator iCurrValue = values.find(w);
//     for(int i=0; i<weights.size(); i++)
//     {
//         if(w >= weights[i])
//         {
//             int val = knapsack(values, weights, w - weights[i]) + weights[i]; // In our case value is weight.
//             if(val > iCurrValue->second)
//             {
//                 iCurrValue->second = val;
//             }
//             //if(val > values[w])
//             //    values[w] = val;
//         }
//     }

//     return iCurrValue->second;
//     //return values[w];
// }

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
*/

int knapsack(int W, const vector<int> &w, vector<int>& indexes) 
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
    //         std::cout << matrix[i][j] << " ";
    //     std::cout << std::endl;
    // }

    int result = matrix[n-1][W];

    // Perform backtracing.
    int x = W;
    //vector<int> backTrace(n-1);
    for(int i=n-1; i>0; i--)
    {
        if(matrix[i][x] != matrix[i-1][x])
        {
            if(matrix[i-1][x - w[i-1]] + w[i-1] == matrix[i][x])
            {
                //backTrace[i-1] = w[i-1];
                x -= w[i-1];

                indexes.push_back(i-1); 
            }
        }
        // else
        //     backTrace[i-1] = 0;
    }

    // Clean up memory usage.
    delete [] matrix[0];
    delete [] matrix;
    return result;
}

void removeSpecifiedValues(vector<int> &A, const vector<int>& indexes)
{   
    for(int j=0; j<indexes.size(); j++)
        A[indexes[j]] = -1;

    int i = 0;
    while(i < A.size())
    {
        if(A[i] == -1)
        {
            A.erase(A.begin()+i);
            continue;
        }
        i ++;
    }
}

int partition3(vector<int> &A) 
{
    int sum = A[0];
    for(int i=1; i<A.size(); i++)
        sum += A[i];

    if(sum % 3 != 0)
        return 0;

    int evenShareSize = sum / 3;
    vector<int> indexes;

    if(knapsack(evenShareSize*2, A, indexes) != evenShareSize*2)
        return 0;

    vector<int> A1(indexes.size());
    for(int i=0; i<indexes.size(); i++)
        A1[i] = A[indexes[i]];

    indexes.clear();
    if(knapsack(evenShareSize, A1, indexes) != evenShareSize)
        return 0;

    // // Remove values.
    // removeSpecifiedValues(A, indexes);
    // indexes.clear();
    // if(knapsack(evenShareSize, A, indexes) != evenShareSize)
    //     return 0;

    // removeSpecifiedValues(A, indexes);
    // sum = 0;
    // for(int i=0; i<A.size(); i++)
    //     sum += A[i];

    // return (sum == evenShareSize);
    return 1;
}

int main() 
{
    // vector<int> indexes;
    // vector<int> aa(4);
    // aa[0] = 6;
    // aa[1] = 3;
    // aa[2] = 4;
    // aa[3] = 2;

    // knapsack(10, aa, indexes);    
    // return 0;

    int n = 6;
    int arr[] = {3, 3, 1, 2, 2, 2};
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) 
    {
        std::cin >> A[i];
        //A[i] = arr[i];
    }

    std::cout << partition3(A) << '\n';
}


175934571723671182 59