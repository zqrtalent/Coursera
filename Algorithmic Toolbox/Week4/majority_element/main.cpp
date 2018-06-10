#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

/*
A majority element in an array A[] of size n is an element that appears more than n/2 times (and hence there is at most one such element).
*/

struct TreeItem
{
    long long value;
    long long count;
    struct TreeItem* right;
    struct TreeItem* left;
};

void solution_bst();
int InsertBST(vector<struct TreeItem>& arrValues, TreeItem* parentNode, long long value, int len);

void solution1_binarysearch();
void solution2_naive();
int add_sorted_order(vector<long long>& sorted, vector<long long>& arrCts, long long value);

int main()
{
    solution_bst();
    //solution1_binarysearch();
    //solution2_naive();
    return 0;
}

int InsertBST(vector<struct TreeItem>& arrValues, TreeItem* parentNode, long long value, int len)
{
    int ct = 0;
    if(parentNode == nullptr)
    {
        arrValues[len].value = value;
        arrValues[len].count = 1;
        arrValues[len].left = nullptr;
        arrValues[len].right = nullptr; 
        return 1;
    }
    else
    {
        if(parentNode->value > value)
        {
            if(parentNode->left == nullptr)
            {
                arrValues[len].value = value;
                arrValues[len].count = 1;
                arrValues[len].left = nullptr;
                arrValues[len].right = nullptr; 

                parentNode->left = &arrValues[len];
            }
            else
                ct = InsertBST(arrValues, parentNode->left, value, len);
        }
        else
        if(parentNode->value < value)
        {
            if(parentNode->right == nullptr)
            {
                arrValues[len].value = value;
                arrValues[len].count = 1;
                arrValues[len].left = nullptr;
                arrValues[len].right = nullptr; 

                parentNode->right = &arrValues[len];
            }
            else
                ct = InsertBST(arrValues, parentNode->right, value, len);
        }
        else
        {
            ct = ++parentNode->count;
        }
    }

    return ct;
}

void solution_bst()
{
    int n;    
    cin >> n;
    //n = 5;
    //n = 10;

    vector<struct TreeItem> arrValues(n, TreeItem());
    //long long arr[] = {2, 124554847, 2, 941795895, 2, 2, 2, 2, 792755190, 756617003};
    int arr[] = {2, 3, 9, 2, 2};
    
    long long val;
    int result = 0;
    for(int i=0; i<n; i++)
    {
        cin >> val;
        //val = arr[i];

        if(result == 0 && InsertBST(arrValues, (i==0 ? nullptr : &arrValues[0]), val, i) > n/2)
        {
            result = 1;
        }
    }

    cout << result << endl;
}

void solution2_naive()
{
    int n;    
    cin >> n;
    //n = 5;
    //n = 10;

    vector<long long> arrValues(n);
    long long arr[] = {2, 124554847, 2, 941795895, 2, 2, 2, 2, 792755190, 756617003};
    //int arr[] = {1, 2, 3, 44, 5};
    
    long long val;
    for(int i=0; i<n; i++)
    {
        cin >> val;
        //val = arr[i];

        arrValues[i] = val;
    }

    int result = 0, ct = 1;
    for(int i=0; i<=(n/2); i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(arrValues[i] == arrValues[j])
            {
                ct ++;
            }
        }

        if(ct > n/2)
        {
            result = 1;
            break;
        }
        ct = 1;
    }

    cout << result << endl;
}

void solution1_binarysearch()
{
    int n;    
    cin >> n;
    //n = 5;
    //n = 10;

    vector<long long> arrSorted, arrCts;
    long long arr[] = {2, 124554847, 2, 941795895, 2, 2, 2, 2, 792755190, 756617003};
    //int arr[] = {1, 2, 3, 44, 5};
    
    long long val;
    for(int i=0; i<n; i++)
    {
        cin >> val;
        //val = arr[i];

        add_sorted_order(arrSorted, arrCts, val);
    }

    int result = 0;
    if(arrCts.size() <= n/2)
    {
        for(int i=0; i<arrCts.size(); i++)
        {
            if(arrCts[i] > n/2)
            {
                result = 1;
                break;
            }
        }
    }

    cout << result << endl;
}

int add_sorted_order(vector<long long>& sorted, vector<long long>& arrCts, long long value)
{
    int low = 0, high = sorted.size()-1, mid = 0;
    if( sorted.size() > 0 && 
        (value < sorted[low] || value > sorted[high]))
    {
        if(value < sorted[low])
            mid = 0;
        else
            mid = sorted.size();

        arrCts.insert(arrCts.begin()+mid, 1);
        sorted.insert(sorted.begin()+mid, value);
        return mid;
    }

    while(high > low)
    {
        mid = low + (high-low)/2;
        if(sorted[mid] == value)
        {
            arrCts[mid] ++;
            return mid;
        }

        if(value < sorted[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if(high == low)
    {
        if(low >= 0 && low < sorted.size() && sorted[low] == value)
        {
            arrCts[low] ++;
            return low;
        }
    }

    arrCts.insert(arrCts.begin()+mid, 1);
    sorted.insert(sorted.begin()+mid, value);
    return mid;
}