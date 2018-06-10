#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
You are given a primitive calculator that can perform the following three operations with the current number 𝑥: multiply 𝑥 by 2, 
multiply 𝑥 by 3, or add 1 to 𝑥. Your goal is given a positive integer 𝑛,  find the minimum number of operations needed to obtain the number 𝑛 starting 
from the number 1.
*/

/*
96234
14
1 3 9 10 11 22 66 198 594 1782 5346 16038 16039 32078 96234
  c c a  a  b  c  c   c   c    c    c     a     b     c

a = operation +1
b = operation *2
c = operation *3
*/

vector<int> optimal_sequence(int n) {
    
    vector<int> values(n+1);
    values[0] = 0;

    for(int m=1; m<=n; m ++)
    {
        values[m] = values[m-1] + 1;

        if(m%2 == 0)
            values[m] = std::min(values[m/2] + 1, values[m]);
        if(m%3 == 0)
            values[m] = std::min(values[m/3] + 1, values[m]);
    }

    std::vector<int> sequence;


    while(n > 1)
    {
        sequence.push_back(n);
        if(n%2 == 0 && values[n/2] == values[n]-1)
        {
            n /= 2;
            continue;
        }
        else
        if(n%3 == 0 && values[n/3] == values[n]-1)
        {
            n /= 3;
            continue;
        }
        else
        //if(values[n-1] == values[n]-1)
        {
            n --;
            continue;
        }
    }

    sequence.push_back(1);
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
