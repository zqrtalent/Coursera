#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int partition(vector<int>& arr, int len, int leftIndex, int rightIndex);
void partition3(vector<int>& arr, int len, int leftIndex, int rightIndex, int* arrMidIndexes);
void quick_sort(vector<int>& arr, int len, int leftIndex, int rightIndex);

int main()
{
    int n;    
    cin >> n;
    //n = 5;

    //int arr[] = {2, 3, 9, 2, 9};
    //int arr[] = {1, 1, 1, 1, 0};
    vector<int> arrQuickSort(n);
    for(int i=0; i<n; i++)
    {
        cin >> arrQuickSort[i];
        //arrQuickSort[i] = arr[i];
    }

    quick_sort(arrQuickSort, n, 0, n-1);
    
    for(int i=0; i<n; i++)
    {
        cout << arrQuickSort[i] << " ";
    }
    return 0;
}

int partition(vector<int>& arr, int len, int leftIndex, int rightIndex)
{
    int x = arr[leftIndex]; // Pivot element.
    int j = leftIndex;
    int tmp;

    for(int i=leftIndex+1; i<=rightIndex; i++)
    {
        if(arr[i] <= x)
        {
            j ++;
            tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;
        }
    }

    arr[leftIndex] = arr[j];
    arr[j] = x;
    return j;
}

void partition3(vector<int>& arr, int len, int leftIndex, int rightIndex, int* arrMidIndexes)
{
    int x = arr[leftIndex]; // Pivot element.
    int j = leftIndex;
    int tmp, equalCt = 0;

    vector<int> indices;
    for(int i=leftIndex+1; i<=rightIndex; i++)
    {
        if(arr[i] <= x)
        {
            j ++;
            tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;

            if(arr[j] == x)
            {
                indices.push_back(j);
                equalCt ++;
            }
        }
    }

    if(equalCt > 0)
    {
        indices.push_back(leftIndex);
        if(equalCt < (rightIndex - leftIndex))
        {
            int destIndex = j;
            for(int i=0; i<indices.size(); i++)
            {
                while(destIndex >= leftIndex && arr[destIndex] == x)
                {
                    destIndex --;
                }

                if(destIndex < leftIndex)
                    break;

                if(indices[i] <= destIndex)
                {
                    arr[indices[i]] = arr[destIndex];
                    arr[destIndex] = x;
                }
            }
        }
    }
    else
    {
        arr[leftIndex] = arr[j];
        arr[j] = x;
    }

    arrMidIndexes[0] = j-equalCt;
    arrMidIndexes[1] = j;
}

void quick_sort(vector<int>& arr, int len, int leftIndex, int rightIndex)
{
    int mid;
    int mids[2];
    if(leftIndex >= rightIndex)
        return;

    // partition3(pArr, len, leftIndex, rightIndex, (int*)mids);
    // quick_sort(pArr, len, leftIndex, mids[0] - 1);
    // quick_sort(pArr, len, mids[1] + 1, rightIndex);

    while(leftIndex < rightIndex)
    {
        //mid = partition(pArr, len, leftIndex, rightIndex);
        partition3(arr, len, leftIndex, rightIndex, (int*)mids);
        if((mids[0] - leftIndex) < (rightIndex - mids[1]))
        {
            quick_sort(arr, len, leftIndex, mids[0] - 1);
            leftIndex = mids[1] + 1;
        }
        else
        {
            quick_sort(arr, len, mids[1] + 1, rightIndex);
            rightIndex = mids[0] - 1;
        }
    }
}