#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n;    
    cin >> n;
    
    unsigned long long* pArr = new unsigned long long[n];
    pArr[0] = 1;
    pArr[1] = 1;

    for(int i=2; i<n; i++)
    {
        pArr[i] = pArr[i-2] + pArr[i-1];
    }

    cout << pArr[n-1] << endl;
    delete [] pArr;
    return 0;
}