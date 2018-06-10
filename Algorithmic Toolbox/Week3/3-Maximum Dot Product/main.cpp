#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

long long maximum_dot_product(vector<long long>& arrValues1, vector<long long>& arrValues2, int len);

int main()
{
    int n;    
    cin >> n;
    //n = 4;

    int val1[] = {1, 0, 1, 0};
    int val2[] = {10, 0, 10, 0};
    vector<long long> arrValues1(n);
    vector<long long> arrValues2(n);

    /*
    -2 -1 0 
    -6 -5 100
    */
   
    for(int i=0; i<n; i++)
    {
        cin >> arrValues1[i];
        //arrValues1[i] = val1[i];
    }

    for(int i=0; i<n; i++)
    {
        cin >> arrValues2[i];
        //arrValues2[i] = val2[i];
    }

    cout << maximum_dot_product(arrValues1, arrValues2, n) << endl;
    return 0;
}

// desc
bool compare(long long val1, long long val2)
{
    return (val1 > val2);
}

long long maximum_dot_product(vector<long long>& arrValues1, vector<long long>& arrValues2, int len)
{
    std::sort(arrValues1.begin(), arrValues1.end(), compare);
    std::sort(arrValues2.begin(), arrValues2.end(), compare);

    long long maxDotProduct = 0;
    for(int i=0; i<len; i++)
    {
        maxDotProduct += (arrValues1[i] * arrValues2[i]);
    }
    return maxDotProduct;
}