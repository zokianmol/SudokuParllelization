#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
#define N 25
#define n 5

struct vec{
	vector<int> V;
	void print(){
		for(int i=0;i<n;i++){
			cout<<V[i]<<" ";
		}
		cout<<endl;
	}
	void cp(int v[n]){
		V.clear();
		for(int i=0;i<n;i++){
			V.push_back(v[i]);
		}
	}
};

struct listvec{
	vector<vec> V;
	int size=0;
	void push(vec &v2){
	size++;
	V.push_back(v2);
	}
	void print(){
		cout<<size<<endl;
	}
};



int main(){
	int a[]={1,2,3,4,5};
	int b[]={2,5,8,9,4};
	int c[]={7,8,9,10,11};
	int d[]={5,10,15,20,25};
	vec A,B,C,D;
	listvec V1;
	A.cp(a);
	A.print();
	V1.push(A);
	A.cp(b);
	A.print();
	V1.push(A);
	A.cp(c);
	A.print();
	V1.push(A);
	A.cp(d);
	
	V1.push(A);
	
	

cout<<endl;



V1.print();
V1.V[2].print();

}