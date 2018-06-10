#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) 
{
    vector<int> points;
    std::sort(segments.begin(), segments.end(), [](const Segment& a, const Segment& b) -> bool {
        return a.end < b.end;
    });


    //write your code here
    int point = segments[0].end;
    points.push_back(point);

    for (size_t i = 1; i < segments.size(); ++i) 
    {
        // if the point is not in the segment
        if (point < segments[i].start || point > segments[i].end) { 
            point = segments[i].end;
            points.push_back(point);
        }
    }
    return points;
}

int main() 
{
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) 
    {
        std::cin >> segments[i].start >> segments[i].end;
    }
    
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) 
    {
        std::cout << points[i] << " ";
    }
}
