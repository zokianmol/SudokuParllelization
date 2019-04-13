#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
#define N 16
#define n 4

void printGrid(int grid[N][N]) 
{ 
	for (int row = 0; row < N; row++) 
	{ 
	for (int col = 0; col < N; col++) 
			printf("%3d", grid[row][col]); 
		printf("\n"); 
	} 
} 

int main(){
int count=1,old_count=0;
/*int grid[N][N] =     {{10,22,14,0,0,0,0,13,0,18,0,20,25,0,0,0,21,0,1,0,0,0,0,12,0 },
{0,0,0,12,0,17,15,1,25,10,0,3,13,0,7,0,0,16,0,0,11,18,24,4,0 },
{0,0,0,0,0,0,0,0,0,0,24,12,0,0,0,0,0,0,2,0,10,25,6,1,0 },
{0,0,0,9,0,0,0,23,0,5,0,0,19,0,0,0,0,12,0,0,17,0,20,0,0 },
{0,0,5,0,16,12,6,20,8,0,0,0,0,0,0,10,0,0,0,0,0,2,19,0,0 },
{5,0,0,20,0,0,0,9,14,6,0,0,0,0,17,1,0,0,0,0,0,23,16,11,0 },
{24,0,16,0,0,0,0,19,15,0,0,5,18,1,0,8,0,25,6,0,0,0,12,0,0 },
{0,0,12,14,0,0,0,0,17,0,0,0,0,24,20,13,0,0,3,0,0,0,0,0,4 },
{0,18,19,13,0,0,0,10,0,3,2,0,9,6,0,16,0,23,0,21,0,0,0,24,0 },
{0,0,1,6,9,0,24,0,0,12,0,16,22,0,0,20,19,0,17,0,0,0,2,0,0 },
{0,0,0,0,0,0,0,21,0,0,0,24,0,3,13,18,11,17,0,0,0,0,22,0,1 },
{0,0,0,0,0,0,0,0,0,9,0,0,8,0,1,0,0,0,0,0,0,24,0,7,0 },
{0,0,0,0,12,18,0,0,0,0,0,0,0,14,2,21,8,0,13,1,19,0,9,0,0 },
{0,14,0,0,0,15,3,4,7,0,5,0,0,0,0,0,6,0,0,22,8,0,21,0,2 },
{0,16,3,0,25,0,0,0,0,1,0,0,12,9,21,0,2,15,7,20,0,0,0,0,0 },
{0,0,0,0,0,23,0,0,0,15,0,0,0,16,0,7,14,0,0,0,3,0,13,0,0 },
{0,0,0,4,7,9,0,14,0,0,0,1,0,8,0,0,0,0,24,0,6,22,0,0,0 },
{0,5,0,1,6,0,0,12,11,0,0,25,14,0,0,0,0,13,0,19,24,0,0,0,0 },
{0,9,0,0,0,4,13,0,0,8,19,0,0,7,0,0,0,21,20,0,25,1,0,0,11 },
{16,0,11,0,0,0,20,3,0,25,0,23,0,0,9,22,1,6,15,0,4,7,14,0,0 },
{0,0,0,16,0,3,0,0,0,0,0,0,4,0,0,6,12,8,0,13,0,0,0,0,0 },
{14,20,0,7,22,0,16,5,12,0,0,0,21,23,25,4,0,1,0,0,0,0,3,0,0 },
{0,1,0,15,0,20,0,0,4,0,8,0,0,0,0,0,0,0,0,16,14,12,17,19,24 },
{0,0,0,25,0,0,0,0,0,7,0,0,3,0,22,14,0,0,0,0,0,0,10,0,0 },
{3,0,0,0,5,14,25,15,18,13,0,7,0,17,0,0,20,0,22,0,0,11,0,0,0 }};*/
 int grid[N][N] = {{0,15,0,1,0,2,10,14,12,0,0,0,0,0,0,0},
                      {0,6,3,16,12,0,8,4,14,15,1,0,2,0,0,0},
                      {14,0,9,7,11,3,15,0,0,0,0,0,0,0,0,0},
                      {4,13,2,12,0,0,0,0,6,0,0,0,0,15,0,0},
                      {0,0,0,0,14,1,11,7,3,5,10,0,0,8,0,12},
                      {3,16,0,0,2,4,0,0,0,14,7,13,0,0,5,15},
                      {11,0,5,0,0,0,0,0,0,9,4,0,0,6,0,0},
                      {0,0,0,0,13,0,16,5,15,0,0,12,0,0,0,0},
                      {0,0,0,0,9,0,1,12,0,8,3,10,11,0,15,0},
                      {2,12,0,11,0,0,14,3,5,4,0,0,0,0,9,0},
                      {6,3,0,4,0,0,13,0,0,11,9,1,0,12,16,2},
                      {0,0,10,9,0,0,0,0,0,0,12,0,8,0,6,7},
                      {12,8,0,0,16,0,0,10,0,13,0,0,0,5,0,0},
                      {5,0,0,0,3,0,4,6,0,1,15,0,0,0,0,0},
                      {0,9,1,6,0,14,0,11,0,0,2,0,0,0,10,8},
                      {0,14,0,0,0,13,9,0,4,12,11,8,0,0,2,0}};


//vector<vector<vector<bool>>> po(N,vector<vector<bool>>(N,vector<bool>(N,1)));
int po[N][N][N];
for(int r=0;r<N;r++){                         //initialization of posibility matrix 
	for(int c=0;c<N;c++){
		for(int d=0;d<N;d++){
			po[r][c][d]=1;                      //posibility = 1 ; not possible =0;
		}
	}
}
for(int r=0;r<N;r++){
	for(int c=0;c<N;c++){
		if(grid[r][c]!=0){
			for(int k=0;k<N;k++){
				po[r][c][k]=0;
			}
		po[r][c][grid[r][c]-1]=1;                 //posibility of existing grid	
		}
	}
}

while(old_count!=count){
old_count=count;
count=0;
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
	for(int j=0;j<N;j++){                    //removing checked numbers from posibility matrix 
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
			}
		}
		}
		for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(vector<int>::iterator k=bv.begin();k!=bv.end();k++){
			if(grid[br+i][bc+j]==0){                //removing from posibility matrix
			po[br+i][bc+j][*k]=0;
			}
			}
			}
		}
	bv.clear();
	}
}	

for(int r=0;r<N;r++){                 //elemination row-wise  
	for(int c=0;c<N;c++){
		int a1=0,flg=0;
		for(int k=0;k<N;k++){          //checking each posibility cell in number direction
		if(grid[r][c]==k+1){continue;}           
			a1+=po[r][c][k];
			flg+=k*po[r][c][k];
		}
		if(a1==1){
			count++;
			grid[r][c]=flg+1;

		}
	}
}

for(int k=0;k<N;k++){                 //lone ranger
for(int i=0;i<N;i++){
	int a1=0,a2=0,flg1=0,flg2=0;
	for(int j=0;j<N;j++){
		a1+=po[i][j][k];              // kth number in row  
		a2+=po[j][i][k];             //kth number in column
		flg1+=j*po[i][j][k];
		flg2+=j*po[j][i][k];
	
	}
	if(a1==1 && grid[i][flg1]==0){
		grid[i][flg1]=k+1;
		for(int ex=0;ex<N;ex++){         //remove posibility after assignment
			po[i][flg1][ex]=0;
		}
		po[i][flg1][k]=1;
		count++;
		
	}
	if(a2==1 && grid[flg2][i]==0){        //remove posibility after assignment
		grid[flg2][i]=k+1;
		for(int ex=0;ex<N;ex++){
			po[flg2][i][ex]=0;
		}
		po[flg2][i][k]=1;
		count++;
		
	}
}
for(int br=0;br<N;br+=n){                   //box check
	for(int bc=0;bc<N;bc+=n){
		
		int a1=0,flg1=0,flg2=0;
		for(int r=0;r<n;r++){
			for(int c=0;c<n;c++){
				a1+=po[br+r][bc+c][k];
				flg1=r*po[br+r][bc+c][k];
				flg2=c*po[br+r][bc+c][k];
			}
		}

	}
}
for(int k=0;k<N;k++){
for(int r=0;r<N;r++){
	for int(c=0;c<N;c++){

	}
}
} 
}

printGrid(grid); 
cout<<count;


} 