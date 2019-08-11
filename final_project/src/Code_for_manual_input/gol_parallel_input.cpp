#include <iostream>
#include<omp.h>
#include <fstream>
using namespace std;


int n;
int **current_grid;
int **next_grid;

void initialise(char* filename)
{
	ifstream f(filename);

	f>>n;

	

	

	current_grid = new int*[n];
	next_grid = new int*[n];

	for(int i = 0; i<n; i++)
	{
		current_grid[i] = new int[n];
	}

	for(int i = 0; i<n; i++)
	{
		next_grid[i] = new int[n];
	}

	for(int i = 0; i< n ; i++)
	{
		for(int j = 0; j< n ; j++)
		{
			f>>current_grid[i][j];
		}
	}

	f.close();

}

int count_neighbours(int **current_grid,int x ,int y )
{
	int sum=0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int row = (x+i+n)%n;
			int col = (y+j+n)%n;
			sum+=current_grid[row][col];

		}
		
	}
	sum-=current_grid[x][y];
	return sum;
}

void read_initial_state(char* filename)
{
	ifstream f(filename);

	

	
	f.close();
}


int main(int argc, char** argv)
{
		
	
	int iterations=atoi(argv[2]);
	initialise(argv[1]);

	

	
	for (int k = 0; k < iterations+1; ++k)
	
	{
	
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; ++j)
			{
				next_grid[i][j]=current_grid[i][j];
			}	
		}	

	
		cout<<"state"<< k<<endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if(current_grid[i][j]==0)
				{
					
					cout << " \u25A1 ";
					
				}

				else{

					std::cout<<" \u25A0 ";
					
				}

			}
			cout<<endl; 

		}
	
		#pragma omp  parallel for 
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int x=count_neighbours(current_grid,i,j);
				
				if(current_grid[i][j]==0 && x==3)
					next_grid[i][j]=1;
				else if (current_grid[i][j]==1 && (x<2 || x>3) )
					next_grid[i][j]=0;
				else if (current_grid[i][j]==1 && (x==2 || x==3))
					next_grid[i][j]=1;
				else 
					next_grid[i][j]=0;
				
					 	 
			}
		
		}

			
			
		for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					current_grid[i][j]=next_grid[i][j];
				}	
			}	

		
	

	}
		

	return 0;
}



