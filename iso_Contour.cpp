#include <bits/stdc++.h>
#include "helper.h"
using namespace std;
#define push_back push_back
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define interval pair<int,int> 
#define Point pair<int,int>
#define inf INT_MAX
///stripeC for Contour Problem
///
/// For contour problem X_union will be a disjoint set of x intervals represented by a Binary search tree which contains interval on its leaves
class stripeC{
	public:
	///X_interval of frame
	interval x_interval;
	///Y_interval of frame
	interval y_interval;
	/// Root of tree containing disjoint set of x intervals
	ctree *tree;
//Constructor for Contour problem
	stripeC(interval x,interval y,ctree **tt){
		x_interval = x;
		y_interval = y;
		tree = *tt;
	}
	///Shows Contour stripeC traversal
	void show(){
		cout <<"Interval x: "<< x_interval.first<<" "<<x_interval.second<<endl;
		cout <<"Interval y: "<< y_interval.first<<" "<<y_interval.second<<endl;
		cout <<"Tree"<<endl;
		
		if(tree!=NULL)
		preorder(tree);
		cout<<endl;
	}
};

/// CPY function introduces a finer partition for given set of stripeC from Points given in set P 
/// @param S : Vector of stripeC to be applied 
/// @param P : all Y points projection Set
/// @param x_int : Interval of x for given stripeC
/// @return sfinal : vector of stripeC with finer y partition but same x_union (tree).
vector<stripeC> cpy(vector<stripeC>S ,set<int> P,interval x_int){

	set<interval> iy = partition(P);
	vector<stripeC> sfinal;
	for(auto l: iy){
		ctree *temp=NULL;
		stripeC s(x_int,l,&temp);
		sfinal.push_back(s);
	}

	int i =0,j=0;
//for all stripeC in sfinal , select S[i] from S such that they s.final's y interval is included in S[i]'s y interval  
	while(i!=sfinal.size()&&j!=S.size()){

		if((sfinal[i].y_interval.first>=S[j].y_interval.first) && (sfinal[i].y_interval.second<=S[j].y_interval.second)){
			sfinal[i].tree = S[j].tree; //Equate same BST tree Pointer rather than copying the disjoint interval
			i++;
		}
		else j++;
	}

	return sfinal;
}

/// If For Sleft There exists a Right edge which does no have it's partner in Sleft then it's partner must be in SRight. 
///Hence the Right edge's xunion = x_interval \n
/// Similarly if Sright has a Left edge which does not have it's partner, then that stripeC must be blackened \n
///Blacken function given a certain list of intervals will blacken those stripes which contain them \n
/// @param S : Vector of stripeC to be applied 
/// @param J : list of intervals to blackened with augemented Unique Id
/// @return blackens the S stripeC appropriately 
/// @note As the interval J is sorted and vector of stripeC is also sorted with Y coordinate it can be done in O(n) time using two pointer techniques
void blacken(vector<stripeC> &S,list<pair<interval,int>> J){


	int i =0,j=0;
	auto itr  = J.begin();
	while(i!=S.size() && itr!=J.end()){
		if((S[i].y_interval.first>=(*itr).first.first) && (S[i].y_interval.second<= (*itr).first.second)){ // If S[i] is containted in given Interval
				S[i].tree = NULL; //As the S[i] is entirely contain in the given S[i]'s x interval then disjoint set will be empty hence NULL pointer
				i++;
		}
		else if(S[i].y_interval.second>(*itr).first.second){ //If S[i]'s y interval start is more than current J interval increment J interval
			itr++;
		}
		else i++;
	}

}
/// Concatenate two vector of Stripes \n
/// As both stripeC will have same partition of Y coordinates and sorted from CPY() method it can be done in 1 loop for all partitions \n
///If one of the stripeC contain null x_union then Sfinal[i]'s x_union = x_union of non NUll stripeC \n
///IF both are non null we have to create a new node with side = undefined and x =sleft.x_interval.top and sleft as Left child and sright as right child \n
///This ensures the resultant tree is also binary search tree
/// @param S1 : stripeC Vector
/// @param S2 : stripeC Vector 
/// @param P : Set of all Y coordinates
/// @param x_int : X interval
/// @return blackens the S stripeC appropriately 
vector<stripeC> concat(vector<stripeC> S1,vector<stripeC> S2,set<int> P, interval x_int ){
	//Initialize stripes
	set<interval> iy = partition(P);
	vector<stripeC> sfinal;
	for(auto l: iy){
		ctree *temp=NULL;
		stripeC s(x_int,l,&temp);
		sfinal.push_back(s);
	}

	int i =0;

	while(i!=sfinal.size()){
		if(S1[i].tree!=NULL && S2[i].tree !=NULL) //if both are not null
		{	
			int xt = S1[i].x_interval.second; //Create a new node for ctree with side = undefined and sleft.x_interval.top and sleft as Left child and sright as right child
			ctree * temp =NULL;
			getnewNode(&temp,xt,'U',S1[i].tree,S2[i].tree);   
			sfinal[i].tree = temp; 
		}
		else if(S1[i].tree!=NULL && S2[i].tree==NULL){
			sfinal[i].tree = S1[i].tree;
		} 
		else if(S1[i].tree ==NULL && S2[i].tree!=NULL) {
			sfinal[i].tree = S2[i].tree;
				}

		else {
			
			sfinal[i].tree = NULL;
		}
		i++;
	}

	return sfinal;


}

//Function to generate stripes for Contour problem
///
/// Creates horizontal stripes in time O(nlogn) time using divide n conquer approach by dividing given set of Verical edges into 2 with equal size. \n
/// BASE CASE := Given vector of Vertical Edge has only 1 element then create stripeC for single Edge \n
/// DIVIDE : Divide the vector of vertical edges into 2 by selecting median xm \n
/// CONQUER : Solve seperately for 2 sets of Vertical edges \n
/// MERGE : Merge the stripeC by copying, blackening and concatenating the two different Stripes
/// @param V : Vector of Vertical Edges
/// @param x_ext: x interval of stripes
/// @param L : Contains the y-projections of all left edges whose partner is not in V.
/// @param R : Contains the y-projections of all right edges whose partner is not in V.
/// @param P : contains the y-projection of all endpoints of line segments in V plus the flame boundaries in y-direction, namely -inf, +inf
/// @param S:  Output vector of Stripes
void getStripe(vector<edge> V, interval x_ext,list<pair<interval,int>> &L,list<pair<interval,int>> &R,set<int> &P,vector<stripeC> &S){

	if(V.size()==1){
		edge v = V[0];
		if(v.side=='L') L.push_back({v.intr,v.uid});  //If left side insert in L set
		else R.push_back({v.intr,v.uid});	//else in Right side
		int temp[] = {-inf,v.intr.first,v.intr.second,inf};

		P.insert(temp,temp+4); 	//Creating Y projections containing points in temp
		set<interval> par = partition(P); //Creating partitions
		
		
		for(auto l : par){
			ctree * tree =NULL;
			stripeC s(x_ext,l,&tree);
			S.push_back(s);
		}

//Select the stripeC that contain the vertical edge and update it's x_union according to it's side
		for(int i=0;i<S.size();i++){

			if(S[i].y_interval == v.intr){
				if(v.side == 'L'){
					getnewNode(&S[i].tree,v.coord,'L',NULL,NULL);
			
				}
				else {
					getnewNode(&S[i].tree,v.coord,'R',NULL,NULL);
				
				}
				break;	
			}
		}
		return;

	}
	
	//Generic case	
	int n =V.size();
	int xm = V[n/2-1].coord + V[n/2].coord;  //Finding xm as the median x coordinate
	xm = xm/2;	

	//Divide into 2 vectors of Vertical edges
	vector<edge> V1(V.begin(),V.begin() + n/2);
	vector<edge> V2(V.begin()+n/2,V.end());
//Creating L ,R and P for each set of edges
	list<pair<interval,int>> L1,R1,L2,R2;
	set<int> P1,P2;
	vector<stripeC> S1,S2;
//Conquer step run for each set
	getStripe(V1,{x_ext.first,xm},L1,R1,P1,S1);

	getStripe(V2,{xm,x_ext.second},L2,R2,P2,S2);
//Merge Step
	//LR = intersection of L1 and R2

	list<pair<interval,int>> LR = intersect(L1,R2);

	L = uni(diff(L1,LR),L2);	// L = L1/LR U L2 only those L which has no partner
	R = uni(R1,diff(R2,LR));	// R= R1 U R2/L2 only those R which has no partner
	P= P1;	// P = P1 U P2
	for(auto l :P2) P.insert(l);


	vector<stripeC> sleft = cpy(S1,P,{x_ext.first,xm});
	vector<stripeC> sright = cpy(S2,P,{xm,x_ext.second});

//Copying the new stripes with finer partition from new P  set without changing x_union	
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
/// @param S : Output vector of stripeC
void rDac(vector<rectangle> Re,vector<stripeC> &S){
	vector<edge> vrx = getVEdge(Re);

	sort(vrx.begin(), vrx.end(),compEd);

	// for(auto l : vrx) l.show();
	list<pair<interval,int>> L,R;
	set<int> P;
	
	getStripe(vrx,{-inf,inf}, L,R,P,S);
} 
///For **visualization** all vertical edges of final contour Cycles
///
/// Using stripeC we now all endpoints of all elements of intervals in disjoint set s.x_union will have their vertical edge in final contour. \n
/// Thus we generate all vertical edges by going through each stripeC and add all vertical edges (stripeC's y interval) of its s.x_union 
vector<LineSeg> vertPieces(vector<stripeC> S){

	vector<LineSeg> vPieces;

	for(auto l: S){
		set<interval> xUnion;
		getOrder(l.tree, xUnion);

		for(auto t:xUnion){
			LineSeg p1(l.y_interval, t.first);
			LineSeg p2(l.y_interval, t.second);
			vPieces.push_back(p1);
			vPieces.push_back(p2);
		}

	}
	return vPieces;

}


/// Finds the free interval for edge h from stripeC x_union
///
/// Gets interval lying within h from S.x_union. \n
/// AS free interval will be complement of h wrt to h intersection S.x_union. So [x1,x2] and h intersect J = {[p1,p2],[p3,p4] ..} \n
/// Our free interval will be { [x1,p1],  [p2,p3], [p4, p5],....[pn,x2]} where pi != pj
/// @param h : horizontal edge
/// @param s: stripeC
/// @result : set of horizontal contour edges
vector<LineSeg> contour_Pieces(edge h , stripeC s){
	set<interval> temp;
	vector<LineSeg> ans;
	//Line number 431 - 448 can be optimised for O(n) to O(logn + p) using 1-D range tree;
//Get x_union
	getOrder(s.tree,temp);
	
//Start and end point of horizontal edge
	int x1 = h.intr.first;
	int x2 = h.intr.second;
	// Flag which monitors if edge is completely inclosed within s.x_union
	int flag=0;
	vector<interval> join; // intersection disjoin set
	//Finding intersection
	for(auto l : temp){
		if((l.first>=x1&&l.first<=x2) || (l.second>=x1&&l.second<=x2) ) {
			join.push_back(l);
		}
		if(l.first<=x1 && l.second >=x2){
			flag =1;
			break;
		}
	}
	if(flag){
		return ans;
	}
	//For finding complements 
	int start = x1, end = x2;
	int k=0;
	
	//AS free interval will be complement of h wrt to h intersection S.x_union. So [x1,x2] and h intersect J = {[p1,p2],[p3,p4] ..} 
	// Our free interval will be { [x1,p1],  [p2,p3], [p4, p5],....[pn,x2]} where pi != pj
	if(join.size()!=0){
	if(join[0].first < start){
		start = join[0].second;
		k++;
	}
	
	while(k!=join.size() && start<end){
		LineSeg p({start,join[k].first},h.coord); //Creating the complement interval
		ans.push_back(p);
		start = min(join[k].second,end); 	// updating start
		k++;
	}
	if(start !=end){ // if last interval cannot be completed in above loop ,then add it
		int n = join.size();
		LineSeg p({join[n-1].second,end},h.coord);
		ans.push_back(p);
	}
	vector<LineSeg> noNull; // remove interval [pi,pj] such that pi == pj
	for(auto l: ans){
		if(l.intr.first !=l.intr.second) noNull.push_back(l);
	}
	return noNull;
	}
	else { //iF s.x_union is null then whole horizontal edge will be in contour
	LineSeg p({h.intr.first,h.intr.second},h.coord);
	ans.push_back(p);
		return ans;
	}


}

///Contour Generates horizontal edges of contour cycles
///
/// Finds the stripeC for each horizontal edge and get horizontal edges using
/// @see contour_Pieces(edge h,stripeC S)
///@param hv : horizontal edges
///@param S : Set of Stripes
///@note as stripeC and horizontal edges are sorted with y coordinate 2 pointer technique can be used to get required stripeC for each edge h in O(n) time where n = # ofstripe
vector<LineSeg> contour(vector<edge> hv ,vector<stripeC> S){

	 int i = 0;
	 int j = 0;
	 vector<LineSeg> horzPieces;

	 while(j!=S.size() && i!= hv.size()){
	 
	 		if((hv[i].side =='B' )&&(S[j].y_interval.second == hv[i].coord)){
	 			vector<LineSeg> gans = contour_Pieces(hv[i],S[j]);
	 			for(auto l:gans) horzPieces.push_back(l);
	 			i++;
	 		}
	 
	 	else if(hv[i].side == 'T' && (S[j].y_interval.first == hv[i].coord)){
	 			vector<LineSeg> gans = contour_Pieces(hv[i],S[j]);
	 			for(auto l:gans) horzPieces.push_back(l);
	 			i++;
	 		
	 	}
	 	else j++;


	 }
	 return horzPieces;

}


///Driver function for Contour Problem
///
///Input format : First line n : number of iso rectangles \n
/// Next n lines contain x1 x2 y1 y2 which is the x interval= [x1,x2] and y interval = [y1,y2] for ith rectangle
int32_t main(){
		IOS
	
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin); 
    freopen("out.txt", "w", stdout);
#endif 
auto start = chrono::steady_clock::now();
	int n;
	vector<rectangle> v;
	cin>>n;

	while(n--){
			int x1,x2,y1,y2;
			cin>>x1>>x2>>y1>>y2;
			rectangle r1({min(x1,x2),max(x1,x2)},{min(y1,y2),max(y1,y2)});
			v.push_back(r1);
	}
	//Get all horizontal edges
	vector<edge> hor = getHEdge(v);
	vector<stripeC> Sf;

 rDac(v,Sf);
 vector<LineSeg> hPieces = contour(hor,Sf); //Run contour algo
 vector<LineSeg> vPieces = vertPieces(Sf); //get all vertical pieces for visualization
 //output for visualiztion
 for(auto l: hPieces) l.show();
 cout <<":";
 for(auto l : vPieces) l.show();
auto end = chrono::steady_clock::now();
auto diff = end - start;
//Execution time calculation
//  cout <<"Execution Time:"<< chrono::duration <double, milli> (diff).count() << " ms" << endl;
 
  return 0;
}