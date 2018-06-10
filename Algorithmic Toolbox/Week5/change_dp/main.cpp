#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

/*
~Dynamic Programming~

Money change problem.
*/

int DP_Change_MinNumberCoins(int money, vector<int>& coins);

int main()
{
    vector<int> coins;
    coins.push_back(1);
    coins.push_back(3);
    coins.push_back(4);
    
    int money;
    cin >> money;

    int minChange = DP_Change_MinNumberCoins(money, coins);
    cout << minChange << endl;
    return 0;
}

int DP_Change_MinNumberCoins(int money, vector<int>& coins)
{
    vector<int> minNumCoins(money+1);
    minNumCoins[0] = 0;

    for(int m=1; m<=money; m ++)
    {
        minNumCoins[m] = 0x7fffffff;

        for(int i=0; i<coins.size(); i++)
        {
            if(m >= coins[i])
            {
                int numCoins = minNumCoins[m - coins[i]] + 1;
                if(numCoins < minNumCoins[m])
                    minNumCoins[m] = numCoins;
            }
            else
                break;
        }
    }
    return minNumCoins[money];
}
