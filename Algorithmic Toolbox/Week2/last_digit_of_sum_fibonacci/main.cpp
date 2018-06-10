#include <iostream>
#include <algorithm>
using namespace std;

int get_fibonacci_sum_last_digit(long long n);

int main()
{
    long long n;    
    cin >> n;
    
    cout << get_fibonacci_sum_last_digit(n) << endl;
    return 0;
}

int get_fibonacci_sum_last_digit(long long n) {
    const int kPisanoSize = 60;
    int rest = n % kPisanoSize;
    int preparedNumbers[kPisanoSize] = 
    {
        0, 1, 2, 4, 7, 2, 0, 3, 4, 8, 3, 2, 6, 9, 6, 6, 3, 
        0, 4, 5, 0, 6, 7, 4, 2, 7, 0, 8, 9, 8, 8, 7, 6, 4, 
        1, 6, 8, 5, 4, 0, 5, 6, 2, 9, 2, 2, 5, 8, 4, 3, 8, 
        2, 1, 4, 6, 1, 8, 0, 9, 0
    };
    return preparedNumbers[rest];
}

// 614162383528