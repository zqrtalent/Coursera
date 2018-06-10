#include <iostream>
#include <algorithm>
using namespace std;

const int _coinValues[] = {1, 5, 10};
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