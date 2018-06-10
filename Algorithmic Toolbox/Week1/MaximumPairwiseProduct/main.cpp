#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n;    
    cin >> n;
    
    int* pArr = new int[n];
    long max = -1;
    int maxIdx = -1;
    for(int i=0; i<n; i++)
    {
        cin >> pArr[i];
        if(pArr[i] > max)
        {
            maxIdx = i;
            max = pArr[i];
        }
    }

    if(maxIdx > 0)
    {
        int firstVal = pArr[0];
        pArr[0] = max;
        pArr[maxIdx] = firstVal;
    }
    
    long max2 = -1;
    for(int i=1; i<n; i++)
    {
        if(pArr[i] > max2)
            max2 = pArr[i];
    }

    cout << max * max2 << endl;
    delete [] pArr;
    return 0;
}