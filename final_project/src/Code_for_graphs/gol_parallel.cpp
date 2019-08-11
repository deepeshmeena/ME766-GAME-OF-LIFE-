#include <iostream>
#include<omp.h>
using namespace std;
#define n 10
#define interations 5

int count_neighbours(int A[][n],int x ,int y )
{
	int sum=0;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			int row = (x+i+n)%n;
			int col = (y+j+n)%n;
			sum+=A[row][col];

		}
		
	}
	sum-=A[x][y];
	return sum;
}


int main()
{
	
	omp_set_num_threads(5);
	int A[n][n];
	int C[n][n];
	

	
	
	
    	 
        for ( int i = 0; i < n; ++i)
    	{
    		for (int j = 0; j < n; ++j)
    		{
    			
    			double r = ((double) rand() / (RAND_MAX)) ;
				if(r>0.5)A[i][j]=1;
				else A[i][j]=0;

				
    			

    			
    		}
    	}

     	
    	for ( int k = 0; k < interations+1; ++k)
    	
    	{
    	
    		for (int i = 0; i < n; ++i)
    		{
    			for (int j = 0; j < n; ++j)
    			{
    				C[i][j]=A[i][j];
    			}	
    		}	

    	//print the intial stage
    		cout<<"state"<< k<<endl;
    		for (int i = 0; i < n; ++i)
    		{
    			for (int j = 0; j < n; ++j)
    			{
    				if(A[i][j]==0)
    				{
    					//std::cout<< " . ";
    					cout << " \u25A1 ";
    					
    				}

    				else{

    					std::cout<<" \u25A0 ";
    					
    				}

    			}
    			cout<<endl; 
    		}


    	
           
         #pragma omp  parallel for 
     		for ( int i = 0; i < n; ++i)
    		{
    			for (int j = 0; j < n; ++j)
    			{
    				int x=count_neighbours(A,i,j);
    				//cout<<x<<" ";
    				if(A[i][j]==0 && x==3)
    					C[i][j]=1;
    				else if (A[i][j]==1 && (x<2 || x>3) )
    					C[i][j]=0;
    				else if (A[i][j]==1 && (x==2 || x==3))
    					C[i][j]=1;
    				else 
    					C[i][j]=0;
    				
    					 	 
    			}
    		
    		}

    			
    		#pragma omp  parallel for 	
    		for (int i = 0; i < n; ++i)
    			{
    				for (int j = 0; j < n; ++j)
    				{
    					A[i][j]=C[i][j];
    				}	
    			}	

    		
    
    	}

    
	return 0;
}



