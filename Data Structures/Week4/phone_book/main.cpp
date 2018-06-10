#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

struct ValueContainer{
    string name;
    struct ValueContainer* nextValue;
};

class HashSet
{
public:
    HashSet(int bucketCount){
        arraySize = bucketCount;
        _hashTable = malloc(sizeof(ValueContainer*)*bucketCount);
        memset(_hashTable, 0, sizeof(_hashTable));
    }

    ~HashSet(){
        CleanUp();
        free(_hashTable);
    }

private:
    int arraySize;
    ValueContainer** _hashTable;

    void CleanUp(){
        ValueContainer *val, *nextVal;
        for(int i=0; i<arraySize; i++){
            if(_hashTable[i] != nullptr){
                val = _hashTable[i];
                while(val != nullptr){
                    nextVal = val->nextValue;
                    delete val;
                    val = nextVal;
                }

                _hashTable[i] = nullptr;
            }
        }
    }

public:
    void Add(string name){
         ValueContainer* pVal = new ValueContainer();
         pVal->name = name;

        long hashValue = HashFunction(number);
        if(_hashTable[hashValue] != nullptr){
            ValueContainer* pLast = _hashTable[hashValue];
            ValueContainer* pPrev = nullptr;
            while(pLast){
                if(pLast->name == name){
                    // If number exists then overwrite name.
                    pLast->name = name;
                    return;
                }
                pPrev = pLast;
                pLast = pLast->nextValue;
            }
            
            if(pPrev)
                pPrev->nextValue = pVal;
        }
        else{
            _hashTable[hashValue] = pVal;
        }
    }

    void Remove(string name){
        FindAndRemove(name, true);
    }
    
    ValueContainer* Find(string name){
        return FindAndRemove(name, false);
    }

    string Check(int i){
        if(i<0 || i >= arraySize)
            return "";

        string ret = "";
        ValueContainer* pLast = _hashTable[i];
        while(pLast){
            ret += pLast->name + " ";
            pLast = pLast->nextValue;
        }
        return ret;
    }

private:
    ValueContainer* FindAndRemove(string number, bool remove){
        long hashValue = HashFunction(number);
        if(_hashTable[hashValue] != nullptr){
            ValueContainer* pVal = _hashTable[hashValue];
            ValueContainer* pPrevVal = nullptr;
            while(pVal != nullptr){
                if(pVal->number == number){
                    if(remove){
                        if(pPrevVal)
                            pPrevVal->nextValue = pVal->nextValue;
                        else
                            _hashTable[hashValue] = pVal->nextValue;
                    }
                    return pVal;
                }
                pPrevVal = pVal;
                pVal = pVal->nextValue;
            }
        }
        return nullptr;
    }

private:
    size_t HashFunction(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % arraySize;
    }
};

class QueryProcessor {
    // int bucket_count;
    // // store all strings in one vector
    // vector<string> elems;
    // size_t hash_func(const string& s) const {
    //     static const size_t multiplier = 263;
    //     static const size_t prime = 1000000007;
    //     unsigned long long hash = 0;
    //     for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
    //         hash = (hash * multiplier + s[i]) % prime;
    //     return hash % bucket_count;
    // }

    HashSet _set;

public:
    explicit QueryProcessor(int bucket_count): _set(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // // use reverse order, because we append strings to the end
            // for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
            //     if (hash_func(elems[i]) == query.ind)
            //         std::cout << elems[i] << " ";

            cout << _set.Check(query.ind);
            std::cout << "\n";
        } else {
            //vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find"){
                writeSearchResult(_set.Find(query.s) != nullptr);
            }
            else if (query.type == "add") {
                _set.Add(query.s);
                // if (it == elems.end())
                //     elems.push_back(query.s);

            } else if (query.type == "del") {
                _set.Remove(query.s);
                // if (it != elems.end())
                //     elems.erase(it);

            }
        }
    }

    void processQueries() {
        int n = 3;
        //cin >> n;

        Query qq[3];
        qq[0].type = "add";
        qq[0].s = "world";

        qq[0].type = "add";
        qq[0].s = "HellO";

        qq[0].type = "check";
        qq[0].s = "";

        for (int i = 0; i < n; ++i)
            //processQuery(readQuery());
            processQuery(qq[i];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count = 5;
    //cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
