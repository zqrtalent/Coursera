#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
using namespace std;

/*
in:
3 2 
0 5 
-3 2 
7 10 
1 6

out:
2 0
*/

#define MEKE_SEGMENT(a,b) \
    (((long long)a) << 32) | (long long)(0xFFFFFFFF&b)

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points);
void quick_sort(vector<long long>& arr, int len, int leftIndex, int rightIndex);
void partition3(vector<long long>& arr, int len, int leftIndex, int rightIndex, int* arrMidIndexes);
int binarySearch(vector<long long>& sorted, long long searchVal, bool& exists);

int main()
{
    int n, m;
    std::cin >> n >> m;

    //n = 4;
    //m = 4;
    // int arrStarts[] = {1, 4, 4, 8 };
    // int arrEnds[] = {4, 8, 12, 12};
    // int arrPoints[] = {0, 1, 4, 5};

    // int arrStarts[] = {1, 3, 5, 7 };
    // int arrEnds[] = {12, 11, 9, 8};
    // int arrPoints[] = {0, 1, 4, 5, 7, 8, 12, 13, 6};
    // m = sizeof(arrPoints)/sizeof(int);

    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
        // starts[i] = arrStarts[i];
        // ends[i] = arrEnds[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
        //points[i] = arrPoints[i];
    }

    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}

/*
1, 5
2, 4
3, 6
7, 9

+ segment start
- segment end
1+, 2+, 3+, 4-, 5-, 6-, 7+, 9-

Numbers represent in segment value multiplicators.
1, 2, 3, 2, 2, 0, 1, 0 

*/

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> searchPoints) 
{
    int segmentsCt = starts.size();
    vector<long long> points(segmentsCt*2);
    vector<int> segmentsKoef(points.size());

    int loop = 0;
    for(int i=0; i<segmentsCt; i++)
    {
        points[loop++] = MEKE_SEGMENT(starts[i], -1-i); // Segment start, negative segment index represents the start of segment
        points[loop++] = MEKE_SEGMENT(ends[i], i+1); // Segment end.
    }

    quick_sort(points, points.size(), 0, points.size()-1);

    int segmentKoef = 0;
    loop = 0;
    while(loop < points.size())
    {
        long long val = points[loop];
        int segIndex = val&0xFFFFFFFF; 
        int startPoint = (int)((val>>32)&0xFFFFFFFF);

        if(segIndex < 0) // Starting segment point.
        {
            segmentsKoef[-1*segIndex - 1] = ++segmentKoef;
        }
        else
        if(segIndex > 0)  // Ending segment point
        {
            vector<int> endingIndexes, startingIndexes;
            while(loop < points.size())
            {
                val = points[loop];
                int segIndexNew = val&0xFFFFFFFF; 
                int startPointNext = (int)((val>>32)&0xFFFFFFFF);
                if(startPointNext > startPoint)
                    break;
                
                if(segIndexNew < 0) // Starting segment point.
                    startingIndexes.push_back(-1*segIndexNew - 1);
                else    // Ending segment point
                    endingIndexes.push_back(segIndexNew-1 + segmentsCt);
                loop ++;
            }

            for(int i: endingIndexes)
            {
                segmentsKoef[i] = segmentKoef + startingIndexes.size();
            }

            segmentKoef -=  (endingIndexes.size() - startingIndexes.size());
            for(int i: startingIndexes)
            {
                segmentsKoef[i] = segmentKoef;
            }
            continue;
        }

        loop ++;
    }
    
    vector<int> cnt(searchPoints.size());
    bool exists = false;
    for(int i=0; i<cnt.size(); i++)
    {
        int pointVal = searchPoints[i];
        int insertIndex = binarySearch(points, MEKE_SEGMENT(pointVal, 0), exists);
        if( insertIndex >= 0 && insertIndex < points.size())
        {
            int inSegmentKoef = 0;
            int segIndex = points[insertIndex]&0xFFFFFFFF; 
            int startPoint = (int)((points[insertIndex] >> 32)&0xFFFFFFFF);

            if(startPoint == pointVal)
            {
                inSegmentKoef = (segIndex < 0 ? segmentsKoef[-1*segIndex - 1] : segmentsKoef[segIndex-1 + segmentsCt]);
            }
            else
            {
                assert(startPoint > pointVal);
                // Check previous closest point value.
                insertIndex --;
                if(insertIndex < points.size())
                {
                    int segIndexNew = points[insertIndex]&0xFFFFFFFF; 
                    int startPointNew = (int)((points[insertIndex] >> 32)&0xFFFFFFFF);

                    if(segIndexNew > 0) // Ending segment point.
                    {
                        inSegmentKoef = segmentsKoef[segIndexNew-1 + segmentsCt] - 1;
                    }
                    else // Starting segment point.
                        inSegmentKoef = segmentsKoef[-1*segIndexNew - 1];
                }
            }

            cnt[i] = inSegmentKoef;
        }
        else
            cnt[i] = 0;
    }

    return cnt;
}

void partition3(vector<long long>& arr, int len, int leftIndex, int rightIndex, int* arrMidIndexes)
{
    long long x = arr[leftIndex]; // Pivot element.
    int j = leftIndex;
    long long tmp, equalCt = 0;

    vector<int> indices;
    for(int i=leftIndex+1; i<=rightIndex; i++)
    {
        if(arr[i] <= x)
        {
            j ++;
            tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;

            if(arr[j] == x)
            {
                indices.push_back(j);
                equalCt ++;
            }
        }
    }

    if(equalCt > 0)
    {
        indices.push_back(leftIndex);
        if(equalCt < (rightIndex - leftIndex))
        {
            int destIndex = j;
            for(int i=0; i<indices.size(); i++)
            {
                while(destIndex >= leftIndex && arr[destIndex] == x)
                {
                    destIndex --;
                }

                if(destIndex < leftIndex)
                    break;

                if(indices[i] <= destIndex)
                {
                    arr[indices[i]] = arr[destIndex];
                    arr[destIndex] = x;
                }
            }
        }
    }
    else
    {
        arr[leftIndex] = arr[j];
        arr[j] = x;
    }

    arrMidIndexes[0] = j-equalCt;
    arrMidIndexes[1] = j;
}

void quick_sort(vector<long long>& arr, int len, int leftIndex, int rightIndex)
{
    int mid;
    int mids[2];
    if(leftIndex >= rightIndex)
        return;

    while(leftIndex < rightIndex)
    {
        partition3(arr, len, leftIndex, rightIndex, (int*)mids);
        if((mids[0] - leftIndex) < (rightIndex - mids[1]))
        {
            quick_sort(arr, len, leftIndex, mids[0] - 1);
            leftIndex = mids[1] + 1;
        }
        else
        {
            quick_sort(arr, len, mids[1] + 1, rightIndex);
            rightIndex = mids[0] - 1;
        }
    }
}

int binarySearch(vector<long long>& sorted, long long searchVal, bool& exists)
{
    exists = false;
    int low = 0, high = sorted.size()-1, mid = -1;
    if(searchVal < sorted[low] || searchVal > sorted[high])
        return (searchVal < sorted[low]) ? low : high + 1;

    // for(int i=0; i<sorted.size(); i++)
    // {
    //     if(sorted[i] >= searchVal)
    //         return i;
    // }
    // return 0;

    while(high > low)
    {
        mid = low + (high-low)/2;
        if(sorted[mid] == searchVal)
        {
            exists = true;
            return mid;
        }
        if(searchVal < sorted[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if(high == low)
    {
        if( low >= 0 && low < sorted.size() && sorted[low] == searchVal )
        {
            exists = true;
        }
        return searchVal > sorted[low] ? low + 1 : low;
    }

    return mid;
}
