#include <iostream>
#define N 9

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
	for (int row = 0; row < 3; row++) 
		for (int col = 0; col < 3; col++) 
			if (grid[row+boxStartRow][col+boxStartCol] == num) 
				return true; 
	return false; 
} 

int[][] calc_possibilities(int grid[N][N], int row, int col, int *grid_f[N][N][N+1]){

	//Check if number is used in its row
	for(int num=1, num<=N; k++)
	{
		if(UsedInRow(grid[N][N], row, num ))
		{
			grid_f[row][col][num-1]=0
		}
	}


}
void main()
{
	int grid[N][N] = {{3, 0, 2, 5, 0, 8, 4, 0, 0}, 
					{5, 6, 0, 0, 0, 0, 0, 0, 0}, 
					{0, 8, 7, 0, 0, 0, 0, 3, 1}, 
					{0, 0, 3, 0, 1, 0, 0, 8, 0}, 
					{9, 0, 0, 8, 6, 3, 0, 0, 5}, 
					{0, 5, 0, 0, 9, 0, 6, 0, 0}, 
					{1, 3, 0, 0, 0, 0, 2, 5, 0}, 
					{0, 0, 0, 0, 0, 0, 0, 7, 4}, 
					{0, 0, 5, 2, 0, 6, 3, 0, 0}}; 
	int grid_f[N][N][N+1];// grid[pos][pos][possibilities]

	//setting for all cells' possibilities to have all numbers
	for (int row = 0; row < count; row++)
		for(int col=0;col<N;col++)
			for(int depth=1;depth<N+1;depth++)grid_f[row][col][depth]=1;




}
int[] calc_possibilities(int grid[N][N], int i , int j)
{

}
