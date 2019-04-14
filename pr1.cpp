#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
#define N 25
#define n 5

void init(int grid[N][N],bool po[N][N][N]){
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
}

void RemoveConstrain(int grid[N][N],bool po[N][N][N]){
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
}
void printGrid(int grid[N][N]) 
{ 
	for (int row = 0; row < N; row++) 
	{ 
	for (int col = 0; col < N; col++) 
				printf("%3d",grid[row][col]); 
		printf("\n"); 
	} 
} 

bool elemination(int grid[N][N],bool po[N][N][N]){         //eleminitaio	n function
	bool count=0;
	for(int r=0;r<N;r++){                 //elemination row-wise  
	for(int c=0;c<N;c++){
		int a1=0,flg=0;
		for(int k=0;k<N;k++){          //checking each posibility cell in number direction
		if(grid[r][c]==k+1){continue;}           
			a1+=po[r][c][k];
			flg+=k*po[r][c][k];
		}
		if(a1==1){
			count=1;
			//cout<<r<<","<<c<<"ele"<<endl;
			grid[r][c]=flg+1;

		}
	}
}
//cout<<"closing elem"<<endl;
return count;
}

bool loneR(int grid[N][N],bool po[N][N][N]){
bool count=0;	
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
		for(int ex=0;ex<N;ex++){         //remove posibility after assignment for row
			po[i][flg1][ex]=0;
		}
		po[i][flg1][k]=1;
		count=1;
		
	}
	if(a2==1 && grid[flg2][i]==0){        //remove posibility after assignment for column
		grid[flg2][i]=k+1;
		//cout<<flg2<<","<<i<<endl;
		for(int ex=0;ex<N;ex++){
			po[flg2][i][ex]=0;
		}
		po[flg2][i][k]=1;
		count=1;
		
	}
}

for(int br=0;br<N;br+=n){                     //box lone ranger check         
	for(int bc=0;bc<N;bc+=n){
		int a1=0,flg1=0,flg2=0;
		for(int r=0;r<n;r++){
			for(int c=0;c<n;c++){
				a1+=po[br+r][bc+c][k];
				flg1+=r*po[br+r][bc+c][k];
				flg2+=c*po[br+r][bc+c][k];
			}
		}
		if(a1==1 && grid[br+flg1][bc+flg2]==0){
			count=1;
			grid[br+flg1][bc+flg2]=k+1;
			for(int r=0;r<n;r++){
			for(int c=0;c<n;c++){
				for(int num=0;num<N;num++){
					po[br+flg1][bc+flg2][num]=0;
				}
			}
			}
			po[br+flg1][bc+flg2][k]=1;
		}

	}
}
}
//cout<<"closing LR"<<endl;

return count;
}

bool twin(int grid[N][N],bool po[N][N][N]){       //if twin found it return 1 , finding existing twin also
bool count=0;	
for(int r=0;r<N;r++){                             //find twin from row and column
	vector<int> flg1,flg2,num1,num2;
	for(int n1=0;n1<N;n1++){
		int a1=0;
		int b1=0;
		for(int c=0;c<N;c++){
			a1+=po[r][c][n1];
			b1+=po[c][r][n1];
		}
		if(a1==2){
		num1.push_back(n1);                    //find twin number in row
		}
    	if(b1==2){
		num2.push_back(n1);                     //find twin number in column
	    }
	}
	
	if(num1.size()>=2){                        //if twin vector contain more than two
	bool twin=1,brk=0;	                          //assume there is two twin numbers
	for(vector<int>::iterator k=num1.begin();k!=num1.end()-1;k++){             //on first twin number =>k
	for(vector<int>::iterator l=k+1;l!=num1.end();l++){                          //on second twin number =>l
	for(int c=0;c<N;c++){
		if(po[r][c][*k]!=po[r][c][*l]){                   //check posibility matrix rows of two twin numbers
			twin=0;                                   //twin not found flag
			break;
		}
	}
	if(twin==1){                       //if twin found
		for(int c=0;c<N;c++){                    
			if(po[r][c][*k]==1){
				flg1.push_back(c);                   //find location of twin 
				//cout<<"twin";
				count=1;
			}
		}
		for(int depth=0;depth<N;depth++){               //remove from posibility list
			po[r][flg1[0]][depth]=0;
			po[r][flg1[1]][depth]=0;

		}
		po[r][flg1[0]][*k]=1;                             //add single posibility
		po[r][flg1[0]][*l]=1;
		po[r][flg1[1]][*k]=1;
		po[r][flg1[1]][*l]=1;
		brk=1;
		break;
	}
	else{
		twin=1;
	}

	}
	if(brk==1){
		break;
	}	
	}
	}

	if(num2.size()>=2){                                 //colum twin find
	bool twin=1,brk=0;	
	for(vector<int>::iterator k=num2.begin();k!=num2.end()-1;k++)	{
	for(vector<int>::iterator l=k+1;l!=num2.end();l++){
	for(int c=0;c<N;c++){
		if(po[c][r][*k]!=po[c][r][*l]){
			twin=0;
			break;
		}
	}
	if(twin==1){
		for(int c=0;c<N;c++){
			if(po[c][r][*k]==1){
				flg2.push_back(c);
				//cout<<"twin";
				count=1;
			}
		}
		for(int depth=0;depth<N;depth++){
			po[flg2[0]][r][depth]=0;
			po[flg2[1]][r][depth]=0;

		}
		po[flg2[0]][r][*k]=1;
		po[flg2[0]][r][*l]=1;
		po[flg2[1]][r][*k]=1;
		po[flg2[1]][r][*l]=1;

		brk=1;
		break;
	}
	else{
		twin=1;
	}
	
	}
	if(brk==1){
		break;
	}	
	}
	}
    flg1.clear();
    flg2.clear();
    num1.clear();
    num2.clear();
}

for(int br=0;br<N;br+=n){                     //box twin check         
	for(int bc=0;bc<N;bc+=n){
		vector<int> num1,flg1,flg2;
		for(int n1=0;n1<N;n1++){
		int a1=0;
		for(int r=0;r<n;r++){
			for(int c=0;c<n;c++){
				a1+=po[br+r][bc+c][n1];
			}
		}
		if(a1==2){
			num1.push_back(n1);
		}
		}
		if(num1.size()>=2){                        //if twin vector contain more than two
		bool twin=1,brk=0;	                          //assume there is two twin numbers
		for(vector<int>::iterator k=num1.begin();k!=num1.end()-1;k++){             //on first twin number =>k
		for(vector<int>::iterator l=k+1;l!=num1.end();l++){
			for(int r=0;r<n;r++){
				for(int c=0;c<n;c++){
					if(po[br+r][bc+c][*k]!=po[br+r][bc+c][*l]){
						twin=0;
						break;
					}
				}
				if(twin==0){
					break;
				}
			}
			if(twin==1){
				for(int r=0;r<n;r++){
					for(int c=0;c<n;c++){
						if(po[br+r][bc+c][*k]==1){
							flg1.push_back(r);
							flg2.push_back(c);
							//cout<<"twin"<<endl;
							count=1;
						}
					}
				}
				for(int r=0;r<n;r++){
					for(int c=0;c<n;c++){
						po[br+r][bc+c][*k]=0;
					}
				}
				po[br+flg1[0]][bc+flg2[0]][*k]=1;
				po[br+flg1[0]][bc+flg2[0]][*l]=1;
				po[br+flg1[1]][bc+flg2[1]][*k]=1;
				po[br+flg1[1]][bc+flg2[1]][*l]=1;
				brk=1;
				break;
			}
			else{
				twin=1;
			}
		}
		if(brk==1){
			break;
		}
		}
		}
	}
}
return count;
}
bool final_check(int grid[N][N],bool po[N][N][N]){
for(int r=0;r<N;r++){                       //find min posibility
	for(int c=0;c<N;c++){
		int s;
		for(int d=0;d<N;d++){
			s+=po[r][c][d];

		}
		if(s!=1){
			cout<<"at"<<r<<","<<c<<"fault"<<endl;
			return false;
		}
	}
}
return true;
}
/*bool triplet(int grid[N][N], bool po[N][N][N])
{	
	vector<int> temperory_storage;
	int flag=0,flag_temp=0;	//flag: incrementing it for number being found in three cells | flag_temp : 0 for not found, 1 for triplet found
	int counter=0;			//stores the number of cells per row/coloumns/box that contains a particular number
	temperory_storage.empty();
	for(int r=0; r<N;r++) //for each row
	{	for(int k=0;r<N;k++)	//For each Number
		{	for(int c=0; c<N; c++) counter+=po[r][c][k];	//For each Cell
			if(counter==3)
			{	if(temperory_storage.size==NULL)
				{
					flag++;
					for(int c=0; c<N; c++)	temperory_storage.pushback(c);
				}
				else
				{	for(int c=0; c<N; c++)
					{	if(po[r][c][k]==1)
						{
							for(vector<int>::iterator i=temperory_storage.begin(); i<temperory_storage.end(); i++)
							{
								if(c!=*i)flag_temp=1;		//if the coloumn number does not exist in before the previous depth values, then flag will turn 1
							}									
						}							
					}
				}								
			}
			counter=0;			
		}//end of depth			
		if(flag==3)			//triplet is found
	}
return false;
}	*/

/*int *find_least_po(int grid[N][N],bool po[N][N][N]){              //returns no of posibility , row, col
static int num[3]={N,0,0};
for(int r=0;r<N;r++){
for(int c=0;c<N;c++){
	int local_sum=0;
	for(int depth=0;depth<N;depth++){
		local_sum+=po[r][c][depth];
	}
	if(local_sum<num[0] && grid[r][c]==0 ){           //find min sum;
		num[0]=local_sum;
		num[1]=r;
		num[2]=c;
	}
}

}
return num;
}*/


//following function include constrain removeing according to initial grid  ,elimination, lone ranger, twin  
void TryToSolve(int grid[N][N],bool po[N][N][N]){
int count=0,itr=0;
do{
count=0;                            //start counting from each iteration
RemoveConstrain(grid,po);
count+=elemination(grid,po);         //return 1 if it is done
count+=loneR(grid,po);
twin(grid,po);
itr++;
}while(count!=0);
cout<<"iterations"<<itr<<endl;
}

//tree point contains grid and posibility matrics
//functions void copy,bool issolved,bool isvalid 
struct tree_point{
	int grid[N][N];
	bool po[N][N][N]; 
	int sum,r,c;
	void copy(int g[N][N],bool p[N][N][N]){                 //copy grid and posibility
		for(int r=0;r<N;r++){
			for(int c=0;c<N;c++){
				for(int depth=0;depth<N;depth++){
					po[r][c][depth]=p[r][c][depth];
				}
				grid[r][c]=g[r][c];
			}

		}
	}
	bool isValid(){                //check if solved sudoku is valid (return false if empty cell contain no posibility)
		bool final=1;
		for(int r=0;r<N;r++){
			for(int c=0;c<N;c++){
				if(grid[r][c]==0){
					bool valid=0;
					for(int depth=0;depth<N;depth++){
						if(po[r][c][depth]!=0){
							valid=1;
							break;
						}
					}
					if(valid==0){
					return valid;
					}
					else{
					final=valid;
					}
				}
			}
		}
	}
	bool isSolved(){
	if(isValid()){
		for(int r=0;r<N;r++){
			for(int c=0;c<N;c++){
				if(grid[r][c]==0) return false;

			}
		}
		return true;
	}
	else{
		return false;
	}
	}  
};
struct tree{
	vector<tree_point> t;
	vector<int> sum,row,col;
	int size=0;
	void pos(){
		for(int depth=0;depth<N;depth++){
		cout<<t[size-1].po[0][0][depth]<<endl;
	}
	}

	bool push(tree_point &t1){
		if(t1.isValid()){
		int s=N,r1=0,c1=0;	
		for(int r=0;r<N;r++){                       //find min posibility
		for(int c=0;c<N;c++){
		int local_sum=0;
		for(int depth=0;depth<N;depth++){
		local_sum+=t1.po[r][c][depth];
		}
		if(local_sum<s && t1.grid[r][c]==0 ){           //find min sum;
		s=local_sum;
		r1=r;
		c1=c;
		}
		}
		}
		if(s==25 && r1==0 && c1==0){
		for(int r=0;r<N;r++){                       //find min posibility
		for(int c=0;c<N;c++){
		if(t1.grid[r][c]==0){
			r1=r;
			c1=c;
		}
		}
		}
		}
		row.push_back(r1);
		col.push_back(c1);
		sum.push_back(s);
		t.push_back(t1);
		size++;
		return true;          //successfully new entry added
	}
	else{
		return false;             //can't add new entry 
	}
	}
	bool forward_march(){
		if(sum[size-1]>0){
		tree_point tr1;
		tr1=t[size-1];              //last grids and matrix are copied
		int r=row[size-1];
		int c=col[size-1];
		int d=0;
			for(int depth=0;depth<N;depth++){
			if(tr1.po[r][c][depth]==1){
				d=depth;
				tr1.grid[r][c]=depth+1;
				break;
			}
		}
		//cout<<"trying to solve"<<endl;
		init(tr1.grid,tr1.po);
		TryToSolve(tr1.grid,tr1.po);
		if(tr1.isValid()){
			if(tr1.isSolved()){
				cout<<final_check(tr1.grid,tr1.po)<<"I'm  not assure that following sudoku is solved"<<endl;
				push(tr1);
				return false;                  //terminating condition
			}
			cout<<"go to next "<<endl;
			push(tr1);
			return true;
		}
		else{
			cout<<"wrong 000";
			sum[size-1]--;
			t[size-1].po[r][c][d]=0;
			cout<<"still fine"<<sum[size-1]<<endl;
			return true;
		}
		}
		else{
			cout<<"wrong go back"<<endl;
			size--;
			t.erase(t.end()-1);
			row.erase(row.end()-1);
			col.erase(col.end()-1);
			sum.erase(sum.end()-1);	
			sum[size-1]--;                                //back marching started
			for(int depth=0;depth<N;depth++){           
			    if(t[size-1].po[row[size-1]][col[size-1]][depth]==1){
			    	t[size-1].po[row[size-1]][col[size-1]][depth]=0;
			    	break;	
			    } 
			}
			return false;
			pg();
		}
	}
	
	void print_info(){
		cout<<sum[size-1]<<" "<<row[size-1]<< " "<<col[size-1]<<" "<<size<<endl;
	}
	void pg(){
		printGrid(t[size-1].grid);
	}
};





int main(){
/*int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0}, 
					{5, 2, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 8, 7, 0, 0, 0, 0, 3, 1}, 
					{0, 0, 3, 0, 1, 0, 0, 8, 0}, 
					{9, 0, 0, 8, 6, 3, 0, 0, 5}, 
					{0, 5, 0, 0, 9, 0, 6, 0, 0}, 
					{1, 3, 0, 0, 0, 0, 2, 5, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 7, 4}, 
					{0, 0, 5, 2, 0, 6, 3, 0, 0}}; */
int grid[N][N] =     {{10,22,14,0,0,0,0,13,0,18,0,20,25,0,0,0,21,0,1,0,0,0,0,12,0 },
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
{3,0,0,0,5,14,25,15,18,13,0,7,0,17,0,0,20,0,22,0,0,11,0,0,0 }};
 /*int grid[N][N] = {{0,15,0,1,0,2,10,14,12,0,0,0,0,0,0,0},
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
                      {0,14,0,0,0,13,9,0,4,12,11,8,0,0,2,0}};*/


//vector<vector<vector<bool>>> po(N,vector<vector<bool>>(N,vector<bool>(N,1)));
printGrid(grid);
bool po[N][N][N];
init(grid,po);
tree_point tp;
tree t;
tp.copy(grid,po);
TryToSolve(tp.grid,tp.po);
//int *minpos=find_least_po(tp.grid,tp.po);
t.push(tp);
cout<<endl;

for(int i=0;i<56;i++){
do{
t.print_info();
}while(t.forward_march());
t.print_info();
t.pg();	
}
cout << "seems it is solved";



/*int *a=grid[0];                     //pointer stuff
printGrid(grid); 
cout<<count<<" "<<itr<<endl;
cout<<grid+1<<endl<<grid<<endl;
cout<<a+1<<endl;
for(int i=0;i<N;i++){cout<<a+i<<endl;}*/


} 