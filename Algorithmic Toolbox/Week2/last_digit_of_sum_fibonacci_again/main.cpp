#include <iostream>
#include <algorithm>
using namespace std;

unsigned long long last_digit_fibonacci(int n);

int main()
{
    int n;    
    cin >> n;
    
    cout << last_digit_fibonacci(n-1) % 10 << endl;
    return 0;
}

// Fibonacci for last numbers.
unsigned long long last_digit_fibonacci(int n)
{
    unsigned long long f = 1;
    if(n < 2)
        return f;

    unsigned long long prev = 1;
    unsigned long long tmp;
    for(int i=2; i<=n; i++)
    {
        tmp = f;
        f = (f + prev) % 1000000000;
        prev = tmp;
    }

    return f;
}