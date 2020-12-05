#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map> 
#include <string>
#include "RangeTree.h"
using namespace std;

bool compare(const std::pair<int, int>& firstElem, const std::pair<int,int>& secondElem)
{
  return firstElem.first < secondElem.first;
}

bool comprobar(vector<pair<int,int>>v1,vector<pair<int,int>>v2)
{
    unordered_map<string,bool>m;
    if(v1.size()!=v2.size()) return false;
    for(int i=0;i<v1.size();i++)
    {
        string l=to_string(v1[i].first)+'-'+to_string(v1[i].second);
        m[l]=1;
    }

    for(int i=0;i<v2.size();i++)
    {
        string l=to_string(v2[i].first)+'-'+to_string(v2[i].second);

        if(m[l]==0) return false;
    }
    return true;
}

vector<std::pair<int,int>> find(vector<std::pair<int,int>>v, int x_from, int x_to, int y_from, int y_to)
{
    vector<std::pair<int,int>> r; 
    for(auto i:v)
    {
        if( x_from <=i.first && i.first<=x_to && y_from <=i.second && i.second<=y_to)
            r.push_back(i);
    }
    return r;
}
