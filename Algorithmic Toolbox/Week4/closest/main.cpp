#include <iostream>
#include <algorithm>
using namespace std;

/*
Failed case #1/23: (Wrong answer)

Input:
2
0 0
3 4

Your output:
-1

Correct output:
5.000000000
 (Time used: 0.00/2.00, memory used: 22179840/536870912.)
*/

const int _coinValues[] = {1, 5, 10, 20, 50, 100, 500, 1000};
int min_number_changes(long value);

int main()
{
    int n;    
    cin >> n;
    
    cout << min_number_changes(n) << endl;
    return 0;
}

int min_number_changes(long value)
{
    int numChanges = 0;
    int coinIndex = (sizeof(_coinValues)/sizeof(int)) - 1;
    while(coinIndex >= 0){
        if(value >= _coinValues[coinIndex]){
            numChanges += value / _coinValues[coinIndex];
            value %= _coinValues[coinIndex]; 
            if(value == 0)
                break;
        }

        coinIndex --;
    }

    return numChanges;
}