#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

typedef unsigned long long bigint;


int main()
{
    string text = "[](()";
    cin >> text;

    stack<int> stackAnalyze;
    int unmatchedIdx = -1;
    for(int i=0; i<text.length(); i++)
    {
        if(text[i] == '[' || text[i] == '(' || text[i] == '{')
        {
            stackAnalyze.push(i);
        }
        else
        if(text[i] == ']' || text[i] == ')' || text[i] == '}')
        {
            if( stackAnalyze.empty() ||
                (text[i] == ']' && text[stackAnalyze.top()] != '[') ||
                (text[i] == ')' && text[stackAnalyze.top()] != '(') ||
                (text[i] == '}' && text[stackAnalyze.top()] != '{'))
            {
                unmatchedIdx = i + 1;
                break;
            }
            stackAnalyze.pop();
        }
    }

    if(stackAnalyze.empty() && unmatchedIdx == -1)
        cout << "Success" << endl;
    else
    {
        if(unmatchedIdx == -1)
            cout << stackAnalyze.top() + 1 << endl;
        else
            cout << unmatchedIdx << endl;
    }

    return 0;
}
