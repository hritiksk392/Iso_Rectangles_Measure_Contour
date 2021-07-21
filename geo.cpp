#include <bits/stdc++.h>
#include "geo.h"
using namespace std;
#define interval pair<int,int> 
#define Point pair<int,int>
#define inf INT_MAX


void getnewNode(ctree **root,int x, int side,ctree * left,ctree*right){
	*root = (ctree *)malloc(sizeof(ctree));
	(*root)->x =x;
	(*root)->side =side;
	(*root)->left =left;
	(*root)->right = right;

}

void preorder(ctree *root){
	if(root==NULL) return;

	preorder(root->left);
	cout <<root->x <<" "<<root->side<<endl;
	preorder(root->right);

}

void  gHelper(ctree *root, vector<int> &t){
	if(root==NULL) return;

	gHelper(root->left,t);
	if(root->side =='L' || root->side =='R') t.push_back(root->x);
	gHelper(root->right,t);


}

void getOrder(ctree*root, set<interval> &temp){
	vector<int> order;

	gHelper(root,order);

	for(int i=0;i<order.size();i+=2){
		temp.insert({order[i],order[i+1]});
	}

}

LineSeg::LineSeg(interval x,int y){
    intr = x;
    coord= y;
	

}
void LineSeg :: show(){
	cout <<intr.first<<","<<intr.second<<"," <<coord<<endl;
}

rectangle::rectangle(int x,int y,int z,int a){
        x_left = x;
		x_right= y;
		y_bottom= z;
		y_top= a;

		x_interval = {x,y};
		y_interval = {z,a};    
}
rectangle::rectangle(interval x,interval  y){
        x_interval = x;
		y_interval= y;
		x_left = x_interval.first;
		x_right = x_interval.second;
		y_bottom = y_interval.first;
		y_top = y_interval.second;   
}

edge :: edge(interval i, int x, char s,int ui){
    intr = i;
	coord =x;
	side = s;
	uid= ui;
}

void edge::show(){
        cout << "Interval :"<< intr.first<<","<<intr.second<<":"<<coord<<endl;
		cout <<"side: "<<side<<"Ui: "<<uid<<endl;
}

