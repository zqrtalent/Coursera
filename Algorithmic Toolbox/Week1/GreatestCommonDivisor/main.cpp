#include <iostream>
#include <algorithm>
using namespace std;

unsigned long long GCD(unsigned long long a, unsigned long long b);

int main()
{
    unsigned long long a, b;    
    cin >> a;
    cin >> b;
    cout << GCD(max(a,b), min(a,b)) << endl;
    return 0;
}

//Euclidean algorithm
unsigned long long GCD(unsigned long long a, unsigned long long b)
{
    if(b == 0)
        return a;
    return GCD(b, a % b);
}