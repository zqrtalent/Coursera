#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int BinarySearch(vector<int>& sorted, int searchVal)
{
    int low = 0, high = sorted.size()-1, mid = -1;
    if(searchVal < sorted[low] || searchVal > sorted[high])
        return -1;

    while(high > low)
    {
        mid = low + (high-low)/2;
        if(sorted[mid] == searchVal)
            return mid;
        if(searchVal < sorted[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if(high == low)
    {
        if( low >= 0 && low < sorted.size() && sorted[low] == searchVal )
            return low;
    }

    //return mid;
    return -1;
}

int main()
{
    int n;    
    cin >> n;
    //n = 10;
    //int arr[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    vector<int> arrSorted(n);
    for(int i=0; i<n; i++)
    {
        cin >> arrSorted[i];
        //arrSorted[i] = arr[i];
    }
    
    int m;    
    cin >> m;
    //m = 12;
    //int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    vector<int> arrSearch(m);
    for(int i=0; i<m; i++)
    {
        cin >> arrSearch[i];
        //arrSearch[i] = arr2[i];
    }

    // -1 0 1 2 3 4 5 6 7 8 9 -1
    for(int i=0; i<m; i++)
        cout << BinarySearch(arrSorted, arrSearch[i]) << " ";
    return 0;
}