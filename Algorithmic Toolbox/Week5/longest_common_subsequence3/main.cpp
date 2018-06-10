#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

/*
Edit distance  is number of 
#mismatches + #insertions (When we select a symbol from second string) + #deletions (When we select a symbol from first string)

Compute the length of a longest common subsequence of three sequences.
*/

/*Reconstructs common subsequence.*/
void outputAlignment(int i, int j, int** distancesMatrix, vector<int> &a, vector<int> &b, vector<int>& commonA, vector<int>& commonB)
{
    if(i == 0 && j == 0)
        return;

    int distanceCurr = distancesMatrix[i][j];
    if(i > 0 && distanceCurr == distancesMatrix[i-1][j]) // Deletions
    {
        outputAlignment(i-1, j, distancesMatrix, a, b, commonA, commonB);
        commonA.push_back(a[i-1]);
        //commonB.push_back(0x7fffffff);
    }
    else
        if(j > 0 && distanceCurr == distancesMatrix[i][j-1]) // Insertions
        {
            outputAlignment(i, j-1, distancesMatrix, a, b, commonA, commonB);
            //commonA.push_back(0x7fffffff);
            commonB.push_back(b[j-1]);
        }
        else
        {
            outputAlignment(i-1, j-1, distancesMatrix, a, b, commonA, commonB);
            if( a[i-1] == b[i-1] )
            {
                commonA.push_back(a[i-1]);
                commonB.push_back(b[j-1]);
            }
        }
}

/* Longest common distance. */
int lcs3(vector<int> &a, vector<int> &b, vector<int> &c)
{
    int distancesMatrix[102][102][102];
    int len1 = a.size()+1, len2 = b.size()+1, len3 = c.size()+1;
    memset(distancesMatrix, 0, sizeof(distancesMatrix));
    
    int editDistance = 0;
    int insertions = 0, deletions = 0, match = 0, mismatch = 0,deletionsIns = 0;
    for(int i=1; i<len1; i++)
    {
        for(int j=1; j<len2; j++)
        {
            for(int k=1; k<len3; k++)
            {
                insertions = distancesMatrix[i][j-1][k]; // Insertion
                deletions = distancesMatrix[i-1][j][k]; // Deletion
                deletionsIns = distancesMatrix[i][j][k-1]; // Insertion/Deletion
                
                mismatch = distancesMatrix[i-1][j-1][k-1]; // Mismatch
                match = distancesMatrix[i-1][j-1][k-1] + 1; // Match

                if(a[i-1] == b[j-1] && a[i-1] == c[k-1])
                    distancesMatrix[i][j][k] = max(max(insertions, max(deletionsIns, deletions)), match);
                else
                    distancesMatrix[i][j][k] = max(max(insertions, max(deletionsIns, deletions)), mismatch);
            }
        }
    }
    
    editDistance = distancesMatrix[a.size()][b.size()][c.size()];
    return editDistance;
}

int main() 
{
    size_t n = 3;
    std::cin >> n;
    int aa[] = {1, 2, 3};
    int bb[] = {2, 1, 3};
    int cc[] = {1, 3, 5};
    vector<int> a(n);

    for (size_t i = 0; i < n; i++) 
    {
        std::cin >> a[i];
        //a[i] = aa[i];
    }

    size_t m = 3;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) 
    {
        std::cin >> b[i];
        //b[i] = bb[i];
    }

    size_t k = 3;
    std::cin >> k;
    vector<int> c(k);
    for (size_t i = 0; i < k; i++) 
    {
        std::cin >> c[i];
        //c[i] = cc[i];
    }

    std::cout << lcs3(a, b, c) << std::endl;
    return 0;
}
