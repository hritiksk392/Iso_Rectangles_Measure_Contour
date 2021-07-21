#include <bits/stdc++.h>
#include "geo.h"
using namespace std;
#define interval pair<int,int> 
#define endl "\n"

list<pair<interval,int>> intersect(list<pair<interval,int>> s1,list<pair<interval,int>> s2){
   	
    list<pair<interval,int>> sans;
	auto itr1 = s1.begin();
	auto itr2 = s2.begin();

	while(itr1!=s1.end() && itr2!=s2.end()){
		if(*itr1 == *itr2){
			sans.push_back(*itr1);
			itr1++;
			itr2++;
		}
		else if( *itr1 > *itr2){
			itr2++;
		}
		else itr1++;

	}
   
	return sans;
}

list<pair<interval,int>> uni(list<pair<interval,int>> s1,list<pair<interval,int>> s2){
    s1.merge(s2); ///Merge Function uses O(n) time to merge 2 sorted List
		return s1;

}

list<pair<interval,int>> diff(list<pair<interval,int>> s1,list<pair<interval,int>> s2){
	list <pair<interval,int>> inter = intersect(s1,s2); ///Using Intersect Function
	auto itr1 = inter.begin();
    list<pair<interval,int>> sans;
	
	for(auto l : s1){
		if(l == *itr1){
			itr1++;
		}
		else sans.push_back(l);
	}

	return sans;
}

set<interval> intervals(set<int> c){
	set<interval> s;
	vector<int> v;
	for(auto l : c){
		v.push_back(l);
	}
	for(int i=0;i<v.size()-1;i++){
		s.insert({v[i],v[i+1]});
	}
	
	
	return s;
}

set<interval> partition(set<int> y){
	set<interval> res = intervals(y);
	return res;
}

vector<edge> getVEdge(vector<rectangle> R){
	vector<edge> ans;
	int count =0;
	for(auto l : R){
		edge e1(l.y_interval,l.x_left,'L',count);
		edge e2(l.y_interval,l.x_right,'R',count);
		count++;
		ans.push_back(e1); ans.push_back(e2);
	}
	return ans;
}

bool compEd(edge e1,edge e2){
	if(e1.coord == e2.coord) {
		return (e1.side < e2.side);
	}
	else 
		return e1.coord<e2.coord;
}
bool compH(edge e1,edge e2){
	
	if(e1.coord == e2.coord) {
		return (e1.side < e2.side);
	}
	else 
		return e1.coord<e2.coord;
}

vector<edge> getHEdge(vector<rectangle> R){
	vector<edge> ans;
	int count =0;
	for(auto l : R){
		edge e1(l.x_interval,l.y_bottom,'B',count);
		edge e2(l.x_interval,l.y_top,'T',count);
		count++;
		ans.push_back(e1);
		ans.push_back(e2);
	}

	sort(ans.begin(),ans.end(),compH);

	return ans;

}
