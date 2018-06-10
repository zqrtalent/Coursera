#include <iostream>
#include <string>
#include <string.h>
using namespace std;

/*
Edit distance  is number of 
#mismatches + #insertions (When we select a symbol from second string) + #deletions (When we select a symbol from first string)
*/

void outputAlignment(int i, int j, int** distancesMatrix, string& s1, string& s2, string& str1, string& str2)
{
    if(i == 0 && j == 0)
        return;

    int distanceCurr = distancesMatrix[i][j];
    if(i > 0 && distanceCurr == distancesMatrix[i-1][j]+1) // Deletions
    {
        outputAlignment(i-1, j, distancesMatrix, s1, s2, str1, str2);
        s1 += str1[i-1];
        s2 += '_';
    }
    else
        if(j > 0 && distanceCurr == distancesMatrix[i][j-1]+1) // Insertions
        {
            outputAlignment(i, j-1, distancesMatrix, s1, s2, str1, str2);
            s1 += '_';
            s2 += str2[j-1];
        }
        else
        {
            outputAlignment(i-1, j-1, distancesMatrix, s1, s2, str1, str2);
            s1 += str1[i-1];
            s2 += str2[j-1];
        }
}

int edit_distance(const string &str1, const string &str2) 
{
    int len1 = str1.length()+1, len2 = str2.length()+1;
    int** distancesMatrix = new int*[len1];
    for(int k=0; k<len1; k++)
    {
        distancesMatrix[k] = new int[len2];
        memset(distancesMatrix[k], 0, len2*sizeof(int));
    }        

    for(int i=0; i<len1; i++)
    {
        distancesMatrix[i][0] = i;
    }

    for(int j=0; j<len2; j++)
    {
        distancesMatrix[0][j] = j;
    }
    
    int editDistance = 0;
    int insertions = 0, deletions = 0, match = 0, mismatch = 0;
    for(int i=1; i<len1; i++)
    {
        for(int j=1; j<len2; j++)
        {
            insertions = distancesMatrix[i][j-1]+1;
            deletions = distancesMatrix[i-1][j]+1;
            match = distancesMatrix[i-1][j-1];
            mismatch = distancesMatrix[i-1][j-1]+1;

            if(str1[i-1] == str2[j-1])
                distancesMatrix[i][j] = min(min(insertions, deletions), match);
            else
                distancesMatrix[i][j] = min(min(insertions, deletions), mismatch);
        }
    }

    string s1, s2, str11 = str1, str22 = str2;
    outputAlignment(str1.length(), str2.length(), distancesMatrix, s1, s2, str11, str22);
    cout << s1 << endl << s2 << endl;

    editDistance = distancesMatrix[str1.length()][str2.length()];
    // for(int k=0; k<len2; k++)
    // {
    //     delete [] distancesMatrix[k];
    // }
    delete [] distancesMatrix[0];
    delete [] distancesMatrix;
    return editDistance;
}

int main() {
  string str1 = "editing";
  string str2 = "distanc";
  //std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
