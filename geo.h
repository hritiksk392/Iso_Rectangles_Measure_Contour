#include <bits/stdc++.h>
using namespace std;
#define interval pair<int,int> 
#define Point pair<int,int>
#define inf INT_MAX
/// Ctree tree structure BST for x_union of stripes for contour calculation
typedef struct ctree{
	///x coordinate
	int x;  
	/// Side = {L,R} and if not an verical edge then 'U'
	char side;
	struct ctree *left;
	struct ctree *right;

}ctree;
/// To create a new node for ctree given member values
void getnewNode(ctree **root,int x, int side,ctree * left,ctree*right);
/// Preorder Traversal of ctree 
void preorder(ctree *root);

/// A helper function for ctree to get leaf values into vector for @see getOrder(ctree*root, set<interval> &temp);
/// 
/// @param root : root of ctree
/// @param t : output vector
void  gHelper(ctree *root, vector<int> &t);

/// To get disjoint interval set for a given stripe's ctree
///
///@param root : Root tree
///@param temp : output set of intervals
void getOrder(ctree*root, set<interval> &temp);

///Class for line segment 
///
/// A line segment will contain an interval {x or y} and corresponding coordinate to represent a line parallel to x axis or y axis
class LineSeg{
	public:
	interval intr;
	int coord;
	///Constructor takes Interval x and coord y as an input
	LineSeg(interval x,int y);
	///To display an edge
	void show();
};
///Class to show a single Rectangle
///
///A iso-rectangle can be represented as 2 x coordinates and 2 y coordinates or as 2 intervals (X interval and y interval)
/// A iso-rectangle object can be created by any of the two inputs
class rectangle{
	public:
	int x_left;
	int x_right;
	int y_bottom;
	int y_top;

	interval x_interval;
	interval y_interval;

	rectangle(int x,int y,int z,int a);
	rectangle(interval x,interval  y);

};
///Edge Class
///
///A edge may represent a horizontal or a vertical edge which can be determined using @param side
///It edge will be line segment with a **Unique identification id** (uid) representing its rectangle
class edge{
	public:
	///Interval and coord for the Line segment 
	interval intr;
	int coord;
	char side;
	int uid;

	edge(interval i, int x, char s,int ui);
	///To display an edge
	void show();
};

