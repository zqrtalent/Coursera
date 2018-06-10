#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long bigint;

// Greatest common divisor
bigint gcd(bigint a, bigint b);

int main()
{
    bigint a, b;    
    cin >> a;
    cin >> b;
    
    cout << gcd(max(a,b), min(a,b)) << endl;
    return 0;
}

// a >= b
bigint gcd(bigint a, bigint b)
{
    if(b == 0)
        return a;
    return gcd(b, a%b);
}