#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

/*
Inversion Count for an array indicates – how far (or close) the array is from being sorted. 
If array is already sorted then inversion count is 0. If array is sorted in reverse order that inversion count is the maximum.
*/

/*
Failed case #1/14: (Wrong answer)

Input:
5
2 3 9 2 9

Your output:
-1

Correct output:
2
 (Time used: 0.00/3.00, memory used: 20414464/536870912.)
*/

long long Merge(vector<long long>& arrLeft, vector<long long>& arrRight, vector<long long>& mergeInto, int midIndex);
long long MergeSort(vector<long long>& arr, int startIndex, int len, vector<long long>& arrCopyInto);

int main()
{
    int n = 5;    
    cin >> n;

    long long value, inversionCt = 0;
    vector<long long> arrMerge(n), arrSorted(n);
    long long arr[] = { 1, 9, 6, 4, 5 };
    //long long arr[] = { 0, 1, 0, 1, 0 };
    //long long arr[] = { 1, 1, 1, 0, 0 };

    for(int i=0; i<n; i++)
    {
        cin >> value;
        //value = arr[i];
        arrMerge[i] = value;
    }


    inversionCt = MergeSort(arrMerge, 0, arrSorted.size(), arrSorted);
    //inversionCt = MergeSort2(arrMerge, arrSorted, 0, arrMerge.size()-1);
    // for(int i=0; i<arrSorted.size(); i++)
    //     cout << arrSorted[i] << " ";
    
    cout << inversionCt << endl;
    return 0;
}

long long MergeSort(vector<long long>& arr, int startIndex, int len, vector<long long>& arrCopyInto)
{
    vector<long> ret;
    if(len <= 1)
    {
        if(len == 1)
            arrCopyInto[0] = arr[startIndex];
        return 0;
    }

    int n = len/2;
    long long inversionCt = 0;
    vector<long long> a(n);
    inversionCt = MergeSort(arr, startIndex, n, a);
    
    vector<long long> b(len-n);
    inversionCt += MergeSort(arr, startIndex+n, len-n, b);

    inversionCt += Merge(a, b, arrCopyInto, startIndex+n-1);
    return inversionCt;
}

long long Merge(vector<long long>& arrLeft, vector<long long>& arrRight, vector<long long>& mergeInto, int midIndex)
{
    long long inversionCt = 0;
    int copyIndex = 0, startIndexLeft = 0, lenLeft = arrLeft.size(), startIndexRight = 0, lenRight = arrRight.size();
    while(lenLeft > 0 && lenRight > 0){
        if(arrLeft[startIndexLeft] <= arrRight[startIndexRight]){
            mergeInto[copyIndex++] = arrLeft[startIndexLeft];
            startIndexLeft ++;
            lenLeft --;
        }
        else{
            mergeInto[copyIndex++] = arrRight[startIndexRight];
            startIndexRight ++;
            lenRight --;

            //inversionCt += (long long)(arrLeft.size() - startIndexLeft);// + mid - startIndexLeft;
            inversionCt += (long long)(arrLeft.size() - startIndexLeft);
        }
    }

    while(lenLeft > 0)
    {
        mergeInto[copyIndex++] = arrLeft[startIndexLeft];
        startIndexLeft ++;
        lenLeft --;
    }

    while(lenRight > 0)
    {
        mergeInto[copyIndex++] = arrRight[startIndexRight];
        startIndexRight ++;
        lenRight --;
    }

    return inversionCt;
}
