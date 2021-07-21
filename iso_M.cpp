#include <bits/stdc++.h>
#include "helper.h"

using namespace std;
#define pb push_back
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define interval pair<int,int> 
#define Point pair<int,int>
#define inf INT_MAX
///stripeM for Measure Problem
///
/// X_union will be a real number the size of each x_union interval for measure problem
class stripeM{
	public:
	///X_interval of frame
	interval x_interval;
	///Y_interval of frame
	interval y_interval;
	///x_union real number
	int x_union;

	/// Constructor for Measure Problem
	stripeM(interval x,interval y,int xu){
		x_interval = x;
		y_interval = y;
		x_union = xu;
	}
	///To display Measure stripeM
	void show(){
		cout <<"Interval x: "<< x_interval.first<<" "<<x_interval.second<<endl;
		cout <<"Interval y: "<< y_interval.first<<" "<<y_interval.second<<endl;
		cout<<"X_Union :"<< x_union<<"\n";
		cout<<endl;
	}
};

/// CPY function introduces a finer partition for given set of stripeM from Points given in set P 
/// @param S : Vector of stripeM to be applied 
/// @param P : all Y points projection Set
/// @param x_int : Interval of x for given stripeM
/// @return sfinal : vector of stripeM with finer y partition but same x_union.
vector<stripeM> cpy(vector<stripeM>S ,set<int> P,interval x_int){



	set<interval> iy = partition(P);
	vector<stripeM> sfinal;
	for(auto l: iy){
		stripeM s(x_int,l,0);
		sfinal.pb(s);
	}


	int i =0,j=0;
//for all stripeM in sfinal , select S[i] from S such that they s.final's y interval is included in S[i]'s y interval  
	while(i!=sfinal.size()&&j!=S.size()){

		if((sfinal[i].y_interval.first>=S[j].y_interval.first) && (sfinal[i].y_interval.second<=S[j].y_interval.second)){
			sfinal[i].x_union = S[j].x_union; //Will have the same xunion in same y interval slide
			i++;
		}

		else j++;
	}



	return sfinal;
}


/// If For Sleft There exists a Right edge which does no have it's partner in Sleft then it's partner must be in SRight. 
///Hence the Right edge's xunion = x_interval \n
/// Similarly if Sright has a Left edge which does not have it's partner, then that stripeM must be blackened \n
///Blacken function given a certain list of intervals will blacken those stripes which contain them \n
/// @param S : Vector of stripeM to be applied 
/// @param J : list of intervals to blackened with augemented Unique Id
/// @return blackens the S stripeM appropriately 
/// @note As the interval J is sorted and vector of stripeM is also sorted with Y coordinate it can be done in O(n) time using two pointer techniques
void blacken(vector<stripeM> &S,list<pair<interval,int>> J){


	int i =0,j=0;
	auto itr  = J.begin();
	while(i!=S.size() && itr!=J.end()){
		if((S[i].y_interval.first>=(*itr).first.first) && (S[i].y_interval.second<= (*itr).first.second)){ // If S[i] is containted in given Interval
				S[i].x_union = S[i].x_interval.second - S[i].x_interval.first; //Blackens the stripeM
				i++;
		}
		else if(S[i].y_interval.second>(*itr).first.second){ //If S[i]'s y interval start is more than current J interval increment J interval
			itr++;
		}
		else i++;
	}

}


/// Concatenate two vector of Stripes \n
/// As both stripeM will have same partition of Y coordinates and sorted from CPY() method it can be done in 1 loop for all partitions \n
/// As x_union is a real number then we can assign sfinal[i] = S1[i].x_union + S2[i].x_union \n
/// @param S1 : stripeM Vector
/// @param S2 : stripeM Vector 
/// @param P : Set of all Y coordinates
/// @param x_int : X interval
/// @return blackens the S stripeM appropriately 
vector<stripeM> concat(vector<stripeM> S1,vector<stripeM> S2,set<int> P, interval x_int ){

	//Create a set of stripeM with partitions of P and 0 x_union
	set<interval> iy = partition(P);
	vector<stripeM> sfinal;
	for(auto l: iy){
		stripeM s(x_int,l,0);
		sfinal.pb(s);
	}
	int i =0;

	while(i!=sfinal.size()){
		sfinal[i].x_union = S1[i].x_union + S2[i].x_union;
		i++;
	}

	return sfinal;


}

///Function to generate stripes for Measure problem
///
/// Creates horizontal stripes in time O(nlogn) time using divide n conquer approach by dividing given set of Verical edges into 2 with equal size. \n
/// BASE CASE := Given vector of Vertical Edge has only 1 element then create stripeM for single Edge \n
/// DIVIDE : Divide the vector of vertical edges into 2 by selecting median xm \n
/// CONQUER : Solve seperately for 2 sets of Vertical edges \n
/// MERGE : Merge the stripeM by copying, blackening and concatenating the two different Stripes
/// @param V : Vector of Vertical Edges
/// @param x_ext: x interval of stripes
/// @param L : Contains the y-projections of all left edges whose partner is not in V.
/// @param R : Contains the y-projections of all right edges whose partner is not in V.
/// @param P : contains the y-projection of all endpoints of line segments in V plus the flame boundaries in y-direction, namely -inf, +inf
/// @param S:  Output vector of Stripes
void getStripe(vector<edge> &V, interval x_ext, list<pair<interval,int>> &L,list<pair<interval,int>> &R,set<int> &P,vector<stripeM> &S){
 //base case
	if(V.size()==1){
		edge v = V[0];
		if(v.side=='L') L.push_back({v.intr,v.uid}); //If left side insert in L set
		else R.push_back({v.intr,v.uid});	//else in Right side
		int temp[] = {-inf,v.intr.first,v.intr.second,inf};

		P.insert(temp,temp+4); 	//Creating Y projections containing points in temp
		set<interval> par = partition(P);	//Creating partitions
		
		//Initializing stripes
		for(auto l : par){
			stripeM s(x_ext,l,0);
			S.pb(s);
		}
//Select the stripeM that contain the vertical edge and update it's x_union according to it's side
		for(int i=0;i<S.size();i++){

			if(S[i].y_interval == v.intr){
				if(v.side == 'L')
				{S[i].x_union = x_ext.second - v.coord;}
			
				else {S[i].x_union = v.coord - x_ext.first ;}
				
				break;	
			}

		}
		return;

	}
	
	//Generic case	
	int n =V.size();
	int xm = V[n/2-1].coord + V[n/2].coord; //Finding xm as the median x coordinate
	xm/=2;
	//Divide into 2 vectors of Vertical edges
	vector<edge> V1(V.begin(),V.begin() + n/2);
	vector<edge> V2(V.begin()+n/2,V.end());

	//Creating L ,R and P for each set of edges
	list<pair<interval,int>> L1,R1,L2,R2;
	set<int> P1,P2;
	vector<stripeM> S1,S2;
	//Conquer step run for each set
	getStripe(V1,{x_ext.first,xm},L1,R1,P1,S1);

	getStripe(V2,{xm,x_ext.second},L2,R2,P2,S2);
	
	//Merge Step
	//LR = intersection of L1 and R2
	list<pair<interval,int>> LR = intersect(L1,R2);

	L = uni(diff(L1,LR),L2);	 // L = L1/LR U L2 only those L which has no partner
	R = uni(R1,diff(R2,LR)); 	// R= R1 U R2/L2 only those R which has no partner
	P= P1;
	for(auto l :P2) P.insert(l); // P = P1 U P2

	//Copying the new stripes with finer partition from new P  set without changing x_union
	vector<stripeM> sleft = cpy(S1,P,{x_ext.first,xm});
	vector<stripeM> sright = cpy(S2,P,{xm,x_ext.second});
	
	list<pair<interval,int>> diffR = diff(R2,LR);
	list<pair<interval,int>> diffL = diff(L1,LR);
		
	//Blackening the sleft with R2/LR interval
	blacken(sleft,diffR);
	//Blackening the sright with L1/LR interval
	blacken(sright,diffL);
	
	// Joining the two set of stripes
	S = concat(sleft,sright,P,x_ext);



}
/// Rectangle_DAC function for Initialization of frames
///
/// Vertical Edges are sorted and Frame with x interval ={-inf, inf} and y interval ={-inf,inf } is initiated.
///@param Re: vector of all iso rectangles
/// @param S : Output vector of stripeM
void rDac(vector<rectangle> Re,vector<stripeM> &S){
	vector<edge> vrx = getVEdge(Re);

	sort(vrx.begin(), vrx.end(),compEd);

	list<pair<interval,int>> L,R;
	set<int> P;
	
	getStripe(vrx,{-inf,inf}, L,R,P,S);
} 
///To find Measure of n iso rectangle
///
///In a given stripeM the x union contains x_interval of area intersected by rectangles. \n
/// In each stripeM the width = y_interval and summation of all disjoint x_interval = xunion \n
///@note: Area covered by each stripeM = (y_interval) * (x_union) and hence sum for all to get Union area or final measure
long long  measure(vector<stripeM> S){
	long long  measValue =0;
	for(auto st :S){
		measValue += (long long )st.x_union*(long long)(st.y_interval.second - st.y_interval.first);

	}
	return measValue;
}
 
///Driver function for Measure Problem
///
///Input format : First line n : number of iso rectangles \n
/// Next n lines contain x1 x2 y1 y2 which is the x interval= [x1,x2] and y interval = [y1,y2] for ith rectangle
int32_t main(){
	//Take input from file input.txt 
		IOS
		#ifndef ONLINE_JUDGE 
    	freopen("input.txt", "r", stdin); 
		#endif 
auto start = chrono::steady_clock::now();

		int n;
		vector<rectangle> v;
		cin>>n;
		while(n--){
			int x1,x2,y1,y2; //Input intervals
			cin>>x1>>x2>>y1>>y2;
			rectangle r1({min(x1,x2),max(x1,x2)},{min(y1,y2),max(y1,y2)});
			v.pb(r1);
		}
	//Get all vertical edges
	vector<edge> ex =getVEdge(v);

	//calling the rDac(function)
	vector<stripeM> Sf;
	rDac(v,Sf);

	//Calculate measure
	int meas = measure(Sf);
	cout <<meas<<endl;
	std::ofstream out("meas.txt");
	out << meas;
	out.close();

auto end = chrono::steady_clock::now();
auto diff = end - start;
//Execution time calculation
 cout <<"Execution Time:"<< chrono::duration <double, milli> (diff).count() << " ms" << endl;
  return 0;
}