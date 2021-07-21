#include <bits/stdc++.h>
#include "geo.h"
using namespace std;
/// Interval is defined as a pair of coord
#define interval pair<int,int> 

///Function to find intersection of two lists
///
///This function takes 2 sorted list as an input and find elements common in both the lists and output them as a seperate list in O(n+m) time
///@param s1, sorted List of {interval, rectangle No.} 
///@param s2, sorted List of {interval, rectangle No.} 
///@return sans: Sorted List of intersection of s1 and s2
list<pair<interval,int>> intersect(list<pair<interval,int>> s1,list<pair<interval,int>> s2);
///Function to find union of two lists
///
///This function takes 2 sorted list as an input and find the total union of those 2 lists.
/// It merges the two list by maintaining two pointers one for each list and compares element pointed by that two pointers in O(n+m) time
///@param s1, sorted List of {interval, rectangle No.} 
///@param s2, sorted List of {interval, rectangle No.} 
///@return sans: Sorted List of Union of s1 and s2
list<pair<interval,int>> uni(list<pair<interval,int>> s1,list<pair<interval,int>> s2);

///Function to find set difference
///
///This function takes 2 sorted list and find intersecting elements using @see intersect(list<pair<interval,int>> s1,list<pair<interval,int>> s2) and remove the
/// common elements from S1 list. Takes O(n)time using two pointer stratefy
///@param s1, sorted List of {interval, rectangle No.} 
///@param s2, sorted List of {interval, rectangle No.} 
///@return sans: Sorted List of set difference **sans = S1 - S2**
list<pair<interval,int>> diff(list<pair<interval,int>> s1,list<pair<interval,int>> s2);

///Converts set of coordinates to set of interval
///
/// for a given set of points say {x1,x2,x3,.....} to intervals : {{x1,x2} ,{x2,x3},{x3,x4} ,.... }
///@param c, set of coords  
///@return set of intervals
set<interval> intervals(set<int> c);

///Interval Projection of all Y coordinates
///
/// for a given set of points say {y1,y2,y3,.....} to intervals : {{y1,y2} ,{y2,y3},{y3,y4} ,.... }
///@param c, set of coords  
///@return set of intervals
set<interval> partition(set<int> y);

///Gets all vertical edges of all rectangles
///
///
///@param R vector of rectangles 
///@return vector of all vertical edges 
vector<edge> getVEdge(vector<rectangle> R);

///Comparator function for vertical sorting edges according to x coordinates and if two edges have same x coordinate then Left edge comes first  
bool compEd(edge e1,edge e2);
///Comparator function for horizontal sorting edges according to y coordinates and if two edges have same y coordinate then Bottom edge comes first  
bool compH(edge e1,edge e2);

///Gets all horizontal edges of all rectangles
///
///
///@param R vector of rectangles 
///@return vector of all horizontal edges 
vector<edge> getHEdge(vector<rectangle> R);
