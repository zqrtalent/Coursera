#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

struct Item
{
    int value;
    int weight;
    double perUnitValue;

    bool operator()(const struct Item& val1, const struct Item& val2) const 
    {
        return val1.perUnitValue > val2.perUnitValue;
    }
} MyItem;

double fractional_knapsack(int maxWeight, vector<struct Item>& arrItems, int len);

int main()
{
    int n;    
    cin >> n;
    //n = 1;

    int maxWeight;
    cin >> maxWeight;
    //maxWeight = 1000;

    Item* arrItems = new Item[n];
    vector<struct Item> arr(n, Item());

    for(int i=0; i<n; i++)
    {
        cin >> arr[i].value;
        cin >> arr[i].weight;
        arr[i].perUnitValue = (double)arr[i].value/arr[i].weight;

        // cin >> arrItems[i].value;
        // cin >> arrItems[i].weight;
        // arrItems[i].perUnitValue = (double)arrItems[i].value/arrItems[i].weight;
    }

    cout << std::setprecision(9) << fractional_knapsack(maxWeight, arr, n) << endl;
    
    delete [] arrItems;;
    return 0;
}

double fractional_knapsack(int maxWeight, vector<struct Item>& arrItems, int len)
{
    sort(arrItems.begin(), arrItems.end(), MyItem);

    double maxValues = 0.0;
    for(int i=0; i<len; i++)
    {
        if(maxWeight < arrItems[i].weight)
        {
            maxValues += maxWeight*arrItems[i].perUnitValue;
            break;
        }
        else
        {
            maxValues += arrItems[i].value;
            maxWeight -= arrItems[i].weight;
            if(maxWeight == 0)
                break;
        }
    }

    return maxValues;
}