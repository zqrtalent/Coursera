#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int largest_number(int* numbers, int len, vector<int>& result);

int main()
{
    int n;    
    cin >> n;
    //n =2;

    int* numbers = new int[n];
    //numbers[0] = 998098;
    //numbers[1] = 99800;

     for(int i=0; i<n; i++){
         cin >> numbers[i];
     }
    
    vector<int> vectNumbers;
    largest_number(numbers, n, vectNumbers);
    for(int i=0; i<vectNumbers.size(); i++)
        cout << vectNumbers[i];
    delete [] numbers;
    return 0;
}

int largest_number(int* numbers, int len, vector<int>& result)
{
    int digits = 0;

    int* decimalSize = new int[len];
    for(int i=0; i<len; i++)
    {
        digits = 1;
        int num = numbers[i];
        if(num <= 0)
        {
            decimalSize[i] = 0;
            continue;
        }

        while( num/10 > 0 )
        {
            num = (num - num%10)/10;
            digits *= 10;
        }
        decimalSize[i] = digits;
    }

    int sameDecimalSize = 0;
    for(int i=0; i<len; i++)
    {
        int numberIndex = i;
        for(int j=i+1; j<len; j++)
        {
            if(decimalSize[numberIndex] == decimalSize[j])
            {
                if(numbers[numberIndex] < numbers[j])
                    numberIndex = j;
            }
            else
            {
                // 28282
                // 28

                // (28282 % 10*10) * 10*10 + 28  = 28228
                // 28 * 1000 + (28282 % 10*10)   = 28282

                int minIdx = decimalSize[numberIndex] < decimalSize[j] ? numberIndex : j;
                int maxIdx = decimalSize[numberIndex] > decimalSize[j] ? numberIndex : j;
                int decimalDiff = decimalSize[maxIdx] / decimalSize[minIdx];
                if(numbers[maxIdx]/decimalDiff == numbers[minIdx])
                {
                    int sameDigits = numbers[minIdx]; // 28
                    int val1 = (numbers[maxIdx] % decimalDiff) * decimalSize[minIdx] * 10 + sameDigits;
                    int val2 = sameDigits * decimalDiff + (numbers[maxIdx] % decimalDiff);

                    if( val1 < val2)
                        numberIndex = minIdx;
                    else
                        numberIndex = maxIdx;
                }
                else
                {
                    if(numbers[maxIdx]/decimalDiff < numbers[minIdx])
                        numberIndex = minIdx;
                    else
                        numberIndex = maxIdx;
                }

                
            }
        }

        if(numberIndex != i)
        {
            int temp = numbers[i];
            numbers[i] = numbers[numberIndex];
            numbers[numberIndex] = temp;

            temp = decimalSize[i];
            decimalSize[i] = decimalSize[numberIndex];
            decimalSize[numberIndex] = temp;
        }

        result.push_back(numbers[i]);
    }

    delete [] decimalSize;
    return result.size();
}