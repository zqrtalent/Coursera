#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void different_sumonds(long value, vector<int> &summonds);

int main()
{
    int n;    
    cin >> n;
    
    vector<int> summonds;
    different_sumonds(n, summonds);

    cout << summonds.size() << endl;
    for(int i=0; i<summonds.size(); i++)
        cout << summonds[i] << " ";
    return 0;
}

void different_sumonds(long value, vector<int> &summonds)
{
    if(value <= 0)
        return;

    int prevVal = 1;
    while(value > 2*prevVal)
    {
        value -= prevVal;
        summonds.push_back(prevVal);
        prevVal ++;
    }

    summonds.push_back(value);
}