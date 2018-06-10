#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

/*
~Dynamic Programming~
Maximum value of aithmetic expression.

In this problem, your goal is to add parentheses to a given arithmetic expression to maximize its value.

max(5-8+7*4-8+9) = ?

Exp1 = 5-8+7*4
MIN(Exp1) = MIN_MATRIX[1,4] = -55

Exp2 = 8+7*4-8
MIN(Exp2) = MIN_MATRIX[2,5] = -60

Exp3 = 5-8+7*4-8+9
MIN(Exp2) = MIN_MATRIX[1,6] = -94


MIN Matrix:

    1       2       3       4       5       6
1   5      -3     -10     -55     -63     -94
2           8      15      36     -60    -195
3                   7      28     -28     -91
4                           4      -4     -13
5                                   8      17
6                                           9

MAX Matrix:
Same logic applies to the MAX matrix as MIN matrix.

    1       2       3       4       5       6
1   5      -3       4      25      65     200
2           8      15      60      52      75
3                   7      28      20      35
4                           4      -4       5
5                                   8      17
6                                           9
*/

inline long long performOperation(long long val1, long long val2, char opCode)
{
    switch(opCode)
    {
        case '-':
            return val1 - val2;
        case '+':
            return val1 + val2;
        case '*':
            return val1 * val2;
        default:
            return val1 / val2;
    }

    return 0; // throw exception.
} 

void MinMax(int i, int j, long long** minMatrix, long long** maxMatrix, vector<char>& operations, long long& minValue, long long& maxValue);
long long RetrieveMaxValue(long long** minMatrix, long long** maxMatrix, vector<char>& operations, string& expression);
long long Parantheses(vector<long long>& numbers, vector<char>& operations, string& expression);

int main()
{
    string s;
    //s = "5-8+7*4-8+9";
    //s = "1+2-3*4-5";
    // (1+2)-(3*(4-5))
    cin >> s;

    int operationsCt = s.length()/2;
    vector<char> operations(operationsCt);
    vector<long long> numbers(operationsCt + 1);

    int iNum = 0, iOp = 0;
    for(int i=0; i<s.length(); i++)
    {
        if(i%2 == 0)
            numbers[iNum++] = (long long)(s[i]-'0');
        else
            operations[iOp++] = s[i];
    }

    string expr;
    long long maxVal = Parantheses(numbers, operations, expr);
    cout << maxVal << endl;
    return maxVal;
}

void MinMax(int i, int j, long long** minMatrix, long long** maxMatrix, vector<char>& operations, long long& minValue, long long& maxValue)
{
    minValue = 0x7fffffffffffffff;
    maxValue = 0x8000000000000000;

    for(int k=i; k<=(j-1); k++)
    {
        long long a = performOperation(maxMatrix[i][k], maxMatrix[k+1][j], operations[k]);
        long long b = performOperation(maxMatrix[i][k], minMatrix[k+1][j], operations[k]);
        long long c = performOperation(minMatrix[i][k], maxMatrix[k+1][j], operations[k]);
        long long d = performOperation(minMatrix[i][k], minMatrix[k+1][j], operations[k]);

        minValue = min(minValue, min(a, min(b, min(c, d))));
        maxValue = max(maxValue, max(a, max(b, max(c, d))));
    }
}

long long RetrieveMaxValue(long long** minMatrix, long long** maxMatrix, vector<char>& operations, string& expression)
{
    int n = operations.size()+1;
    long long maxValue = max(minMatrix[0][n-1], maxMatrix[0][n-1]);
    return maxValue;
}

long long Parantheses(vector<long long>& numbers, vector<char>& operations, string& expression)
{
    int n = numbers.size();
    long long** minMatrix = new long long*[n];
    long long** maxMatrix = new long long*[n];
    for(int i=0; i<n; i++)
    {
        minMatrix[i] = new long long[n];
        minMatrix[i][i] = numbers[i];
        
        maxMatrix[i] = new long long[n];
        maxMatrix[i][i] = numbers[i];
    }

    long long minVal = 0, maxVal = 0;
    for(int s=0; s<n-1; s++)
    {
        for(int i=0; i<(n-s-1); i++)
        {
            int j = i + s + 1;
            MinMax(i, j, minMatrix, maxMatrix, operations, minVal, maxVal);

            minMatrix[i][j] = minVal;
            maxMatrix[i][j] = maxVal;
        }
    }

    // // Output matrix.
    // for(int i=0; i<n; i++)
    // {
    //     for(int j=0; j<n; j++)
    //         std::cout << minMatrix[i][j] << " ";
    //     std::cout << std::endl;
    // }
    // cout << " ======= " << endl;
    // for(int i=0; i<n; i++)
    // {
    //     for(int j=0; j<n; j++)
    //         std::cout << maxMatrix[i][j] << " ";
    //     std::cout << std::endl;
    // }

    long long maxValue = RetrieveMaxValue(minMatrix, maxMatrix, operations, expression);
     // Clean up memory usage.
    delete [] maxMatrix[0];
    delete [] maxMatrix;
    delete [] minMatrix[0];
    delete [] minMatrix;
    return maxValue;
}