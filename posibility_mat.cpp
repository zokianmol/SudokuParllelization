#include <iostream>
#include <vector>
using namespace std;
#define N 9
#define n 3



int main(){
int grid[N][N] = {  {3, 0, 6, 5, 0, 8, 4, 0, 0}, 
					{5, 2, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 8, 7, 0, 0, 0, 0, 3, 1}, 
					{0, 0, 3, 0, 1, 0, 0, 8, 0}, 
					{9, 0, 0, 8, 6, 3, 0, 0, 5}, 
					{0, 5, 0, 0, 9, 0, 6, 0, 0}, 
					{1, 3, 0, 0, 0, 0, 2, 5, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 7, 4}, 
					{0, 0, 5, 2, 0, 6, 3, 0, 0}}	;

vector<vector<vector<bool>>> po(N,vector<vector<bool>>(N,vector<bool>(N,1)));


for(int i=0;i<N;i++){               //row and column check
	vector<int> rv;
	vector<int> cv;
	for(int j=0;j<N;j++){
		if(grid[i][j]!=0){
			rv.push_back(grid[i][j]-1);
		}
		if(grid[j][i]!=0){
			cv.push_back(grid[j][i]-1);
		}
	}
	for(int j=0;j<N;j++){
		if(grid[i][j]==0){
			for(vector<int>::iterator k=rv.begin();k!=rv.end();k++){
			po[i][j][*k]=0;}
		}
		if(grid[j][i]==0){
			for(vector<int>::iterator k=cv.begin();k!=cv.end();k++){
			po[j][i][*k]=0;}
		}
	}
	rv.clear();
	cv.clear();
	}

for(int br=0;br<N;br+=n){                   //box check
	for(int bc=0;bc<N;bc+=n){
		vector<int> bv;
		for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(grid[br+i][bc+j]!=0){
			bv.push_back(grid[br+i][bc+j]-1);
			cout<<grid[br+i][bc+j];
			}
		}
		}
		for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(vector<int>::iterator k=bv.begin();k!=bv.end();k++){
			if(grid[br+i][bc+j]==0){
			po[br+i][bc+j][*k]=0;
			}
			}
			}
		}
	cout<<endl;	
	bv.clear();
	}
}	
for(int i=0;i<N;i++){
	cout<<po[2][3][i]<<endl;
}	
} 
