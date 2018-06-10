#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

typedef long long ull;

struct Data {
    string pattern, text;
};

Data read_input() 
{
    Data data;
    //std::cin >> data.pattern >> data.text;
    data.pattern = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    data.text    = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaass";

    data.pattern = "Test";
    data.text    = "testTesttesT";
    return data;
}

void print_occurrences(const std::vector<int>& output) 
{
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ull PolynomialHash(const char* s, long long len, ull primeNumber, ull x)
{
    //[(104 % 101 ) × 256 + 105] % 101 
    ull hash = 0;
    for (int i = len-1; i >= 0; i--)
        hash = (hash * x + s[i]) % primeNumber;
    // for (long long i = 0; i < len; i++)
    //     hash = (hash * x + s[i]) % primeNumber;
    return hash;
}

vector<ull> PrecomputeHashes(const string& text, const string& pattern, ull primeNumber, ull x)
{
    // vector<ull> hashes((text.size()-pattern.size())+1);
    // ull y = 1;
    // ull rolling_hash = 0;
    // long long patternTextSize = pattern.size();

    // for(int i=0; i<patternTextSize; i++)
    // {
    //     rolling_hash = (rolling_hash * x + text[i]) % primeNumber;
    //     y = (y * x) % primeNumber;
    // }

    // hashes[0] = rolling_hash;
    // //hashes[0] = PolynomialHash(text.c_str(), pattern.size(), primeNumber, x);

    // for(int i=1; i<hashes.size(); i++)
    // {
    //     hashes[i] = (hashes[i-1] * x + text[i + patternTextSize - 1] - y * text[i - 1]) % primeNumber;
    // }
    // return hashes;

    vector<ull> hashes((text.size()-pattern.size())+1);
    long long patternTextSize = pattern.size();
    hashes[hashes.size()-1] = PolynomialHash(&text.c_str()[text.size()-patternTextSize], patternTextSize, primeNumber, x);

    ull y = 1;
    for(long long i=0; i<pattern.size(); i++)
        y = (y*x)%primeNumber;

    for(long long i=hashes.size()-2; i>=0; i--)
    {
        hashes[i] = (hashes[i+1] * x + text[i] - y * text[i+patternTextSize]) % primeNumber;
    }
    return hashes;
}

vector<int> RabinKarp(const string& text, const string& pattern)
{
    srand(time(nullptr));
    ull x = 256;//rand() % pattern.size();
    ull primeNumber = 1610612741;
    ull hashPattern = PolynomialHash(pattern.c_str(), pattern.size(), primeNumber, x);
    vector<ull> hashes = PrecomputeHashes(text, pattern, primeNumber, x);

    vector<int> result;
    for(long long i=0; i<=(text.size()-pattern.size()); i++)
    {
        //if(PolynomialHash(&text.c_str()[i], pattern.size(), primeNumber, x) != hashPattern)
        if(hashes[i] != hashPattern)
            continue;
        if(!text.compare(i, pattern.size(), pattern))
            result.push_back(i);
    }
    return result;
}

vector<int> get_occurrences(const Data& input) 
{
    const string& s = input.pattern, t = input.text;
    return RabinKarp(t, s);
}

int main() 
{
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
