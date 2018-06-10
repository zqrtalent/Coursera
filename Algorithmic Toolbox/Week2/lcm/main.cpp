#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long bigint;

// Least common multiple
bigint lcm(bigint a, bigint b);

// Greatest common divisor.
bigint gcd(bigint a, bigint b);


int main()
{
    bigint a, b;    
    cin >> a;
    cin >> b;
    
    cout << lcm(a,b) << endl;
    return 0;
}

bigint lcm(bigint a, bigint b)
{
    return (a*b)/gcd(max(a,b), min(a,b));
}

// a >= b
bigint gcd(bigint a, bigint b)
{
    if(b == 0)
        return a;
    return gcd(b, a%b);
}