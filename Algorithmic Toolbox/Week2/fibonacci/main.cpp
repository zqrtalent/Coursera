#include <iostream>
#include <algorithm>
using namespace std;

unsigned long long fibonacci(int n);

int main()
{
    int n;    
    cin >> n;
    
    cout << fibonacci(n-1) << endl;
    return 0;
}

unsigned long long fibonacci(int n)
{
    unsigned long long f = 1;
    if(n < 0)
        return 0;
    if(n < 2)
        return f;

    unsigned long long prev = 1;
    unsigned long long tmp;
    for(int i=2; i<=n; i++)
    {
        tmp = f;
        f = (f + prev);
        prev = tmp;
    }

    return f;
}