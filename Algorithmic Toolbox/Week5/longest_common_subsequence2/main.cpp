#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

/*
Edit distance  is number of 
#mismatches + #insertions (When we select a symbol from second string) + #deletions (When we select a symbol from first string)

Compute the length of a longest common subsequence of two sequences.
*/

/* Longest common distance. */
int lcs2(vector<int> &a, vector<int> &b)
{
    int len1 = a.size()+1, len2 = b.size()+1;
    int** distancesMatrix = new int*[len1];
    for(int k=0; k<len1; k++)
    {
        distancesMatrix[k] = new int[len2];
        memset(distancesMatrix[k], 0, len2*sizeof(int));
    }
    
    int editDistance = 0;
    int insertions = 0, deletions = 0, match = 0, mismatch = 0;
    for(int i=1; i<len1; i++)
    {
        for(int j=1; j<len2; j++)
        {
            insertions = distancesMatrix[i][j-1]; // Insertion
            deletions = distancesMatrix[i-1][j]; // Deletion
            match = distancesMatrix[i-1][j-1] + 1; // Match
            mismatch = distancesMatrix[i-1][j-1]; // Mismatch

            if(a[i-1] == b[j-1])
                distancesMatrix[i][j] = max(max(insertions, deletions), match);
            else
                distancesMatrix[i][j] = max(max(insertions, deletions), mismatch);
        }
    }

    editDistance = distancesMatrix[a.size()][b.size()];
    
    delete [] distancesMatrix[0];
    delete [] distancesMatrix;
    return editDistance;
}

int main() 
{
    size_t n;
    std::cin >> n;
    vector<int> a(n);

    for (size_t i = 0; i < n; i++) 
    {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) 
    {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
    return 0;
}
