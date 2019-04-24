// A Backtracking program  in C to solve Sudoku problem 
#include <omp.h>
#include <stdio.h> 
  
// UNASSIGNED is used for empty cells in sudoku grid 
#define UNASSIGNED 0 
  
// N is used for the size of Sudoku grid. Size will be NxN 
#define N 16 
#define n 4 //sqrt(N)
  
#define num_threads 8 //number of omp threads

bool flag=0; //Whether job is done

// This function finds an entry in grid that is still unassigned 
bool FindUnassignedLocation(int grid[N][N], int &row, int &col); 
  
// Checks whether it will be legal to assign num to the given row, col 
bool isSafe(int grid[N][N], int row, int col, int num); 
  
/* Takes a partially filled-in grid and attempts to assign values to 
  all unassigned locations in such a way to meet the requirements 
  for Sudoku solution (non-duplication across rows, columns, and boxes) */
bool SolveSudoku(int grid[N][N],bool current_flag) 
{ 

    if(current_flag==1) return false;
    int row, col; 
  
    // If there is no unassigned location, we are done 
    if (!FindUnassignedLocation(grid, row, col)) 
       return true; // success! 
     
  
    for (int num = 1; num <=N; num++) 
    { 
        // if looks promising 
        if (isSafe(grid, row, col, num)) 
        { 
            // make tentative assignment 
            grid[row][col] = num; 
  
            // return, if success, yay! 
            if (SolveSudoku(grid,flag)) 
            {
              flag=1; //Set flag to 'solved'. This setting is global

                return true; 
  
            }
                
            // failure, unmake & try again 
            grid[row][col] = UNASSIGNED; 
        } 
    } 
    return false; // this triggers backtracking 
} 
  
/* Searches the grid to find an entry that is still unassigned. If 
   found, the reference parameters row, col will be set the location 
   that is unassigned, and true is returned. If no unassigned entries 
   remain, false is returned. */
bool FindUnassignedLocation(int grid[N][N], int &row, int &col) 
{ 
    for (row = N-1; row >= 0; row--) 
        for (col = 0; col <N; col++) 
            if (grid[row][col] == UNASSIGNED) 
                return true; 
    return false; 
} 
  
/* Returns a boolean which indicates whether an assigned entry 
   in the specified row matches the given number. */
bool UsedInRow(int grid[N][N], int row, int num) 
{ 
    for (int col = 0; col < N; col++) 
        if (grid[row][col] == num) 
            return true; 
    return false; 
} 
  
/* Returns a boolean which indicates whether an assigned entry 
   in the specified column matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num) 
{ 
    for (int row = 0; row < N; row++) 
        if (grid[row][col] == num) 
            return true; 
    return false; 
} 
  
/* Returns a boolean which indicates whether an assigned entry 
   within the specified 3x3 box matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) 
{ 
    for (int row = 0; row < n; row++) 
        for (int col = 0; col < n; col++) 
            if (grid[row+boxStartRow][col+boxStartCol] == num) 
                return true; 
    return false; 
} 
  
/* Returns a boolean which indicates whether it will be legal to assign 
   num to the given row,col location. */
bool isSafe(int grid[N][N], int row, int col, int num) 
{ 
    /* Check if 'num' is not already placed in current row, 
       current column and current 3x3 box */
    return !UsedInRow(grid, row, num) && 
           !UsedInCol(grid, col, num) && 
           !UsedInBox(grid, row - row%n , col - col%n, num)&& 
            grid[row][col]==UNASSIGNED; 
} 
  
/* A utility function to print grid  */
void printGrid(int grid[N][N]) 
{ 
    for (int row = 0; row < N; row++) 
    { 
       for (int col = 0; col < N; col++) 
             printf("%3d", grid[row][col]); 
        printf("\n"); 
    } 
} 
  
int main() 
{  int row, col;
  bool f;
    // 0 means unassigned cells 
    
    int grid2[16][16] = {{8,15,0,1,0,2,10,14,12,0,0,0,0,0,0,0},
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

/*
     int grid[N][N]={{0,9,0,0,0,0,0,0,0,13,7,0,3,0,0,0},
     				{0,0,2,0,11,6,3,4,0,9,0,0,0,8,10,15},
     				{0,16,0,10,0,0,12,0,0,4,0,3,6,0,13,0},
     				{0,0,6,8,2,16,0,0,0,10,5,0,0,1,7,9},
     				{12,10,5,0,0,0,0,0,0,0,4,6,15,0,3,14},
     				{0,1,0,0,0,4,11,0,16,0,0,14,0,5,6,0},
     				{0,0,8,14,5,15,0,3,0,0,0,0,0,12,0,0},
     				{15,0,0,6,10,9,0,8,0,0,12,0,1,11,16,0},
     				{0,0,0,0,0,0,0,0,2,0,0,16,13,6,1,0},
     				{0,5,0,16,6,0,8,0,0,0,0,1,0,0,11,0},
     				{0,15,11,0,1,0,0,0,0,0,0,0,9,14,12,7},
     				{0,0,1,0,3,10,15,7,9,0,0,11,0,0,0,0},
     				{4,11,0,5,0,0,0,0,1,14,3,10,2,13,15,0},
     				{13,0,0,0,0,0,0,2,0,11,0,0,12,7,0,6},
     				{0,0,0,0,7,1,0,11,0,0,0,13,0,3,4,8},
     				{8,0,3,12,0,14,0,13,4,5,6,7,11,0,0,0}};
 
 */

 /*//When n=3
 int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0}, 
					{5, 2, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 8, 7, 0, 0, 0, 0, 3, 1}, 
					{0, 0, 3, 0, 1, 0, 0, 8, 0}, 
					{9, 0, 0, 8, 6, 3, 0, 0, 5}, 
					{0, 5, 0, 0, 9, 0, 6, 0, 0}, 
					{1, 3, 0, 0, 0, 0, 2, 5, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 7, 4}, 
					{0, 0, 5, 2, 0, 6, 3, 0, 0}};
*/


  
  //Here goes serial code                  
	f= FindUnassignedLocation(grid, row, col);
	printf("Row=%d, Col=%d\n",row, col );
  	SolveSudoku(grid,flag);
 
  printf("Flag=%d\n",flag ); //this returned 0, meaning flag is not globally set to 1
  printGrid(grid);


/*
//Parallel code below
omp_set_num_threads(num_threads);
 f= FindUnassignedLocation(grid, row, col);

int loops_per_thread=N/num_threads;

omp_set_num_threads(num_threads);
#pragma omp parallel for firstprivate(grid) shared(flag) schedule(static,loops_per_thread)
 
for (int i=N; i>=1; i--)
  {

    if (flag==0){
grid[row][col]=i;
 if(SolveSudoku(grid,flag))
  {printf("Thread rank: %d has solved successfully with i=%d\n", omp_get_thread_num(),i);
    printGrid(grid);
}  

}
}
*/
//printGrid(grid);
}
