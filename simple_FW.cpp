#include<iostream>
#include<time.h>
#include<limits.h>
#include<fstream>
#include<string.h>
#include <chrono> 
#include<vector>
#define BUFFER_SIZE 100
using namespace std;
using namespace std::chrono;
int main(int argc, char *argv[])
{
	if( argc != 2 )
	{
		cout<<"\n Incorrect command "<<endl;
		cout<<"Format is <object> <file_name>"<<endl;
		exit(EXIT_FAILURE);
	}

	unsigned int number_of_vertex, row, col, e, w, a, b;
	char buffer[BUFFER_SIZE];
	clock_t t1, t2;
	int i ,j, k;

	ifstream infile( argv[1] );//Getting input from file

	infile >>number_of_vertex>>e;

	vector< vector< int > > A(number_of_vertex);//Original graph
	for( int i = 0 ; i < number_of_vertex ; i++ )
		A[i].resize(number_of_vertex);

	for( i = 0 ; i < number_of_vertex  ; i++ )
		for( j = 0 ; j <  number_of_vertex ; j++ )
			if( i == j )
				A[i][j] = 0 ;
			else
				A[i][j]=1000000;

	char ch;//to support the test file

	while( infile >> ch >> a >> b >> w )
	{
		A[a - 1][b - 1] = w;
	}

	auto start = high_resolution_clock::now(); 
	auto stop = high_resolution_clock::now(); 

	try //Processing, Floyd Warshall's standard algorithm for All Pair Shortest Path
	{

	for(k=0;k<number_of_vertex;k++)
		for(i=0;i<number_of_vertex;i++)
			for(j=0;j<number_of_vertex;j++)	
			{
				if( A[i][k] == 1000000 || A[k][j] == 1000000 )
				{
					//do nothing
				}
				else
				{
					A[i][j]=(A[i][j]>(A[i][k] + A[k][j]))?(A[i][k] + A[k][j]) : A[i][j];
				}
			}

	stop = high_resolution_clock::now(); 
	}
	catch(exception *e)
	{
		cout<<e->what();
		exit(EXIT_FAILURE);
	}

	auto duration = duration_cast<microseconds>(stop - start); 

	for(i=0;i<number_of_vertex;i++)
	{
		for(j=0;j<number_of_vertex;j++)
		{
			cout<<i+1<<" "<<j+1<<" "<<A[i][j]<<endl;
		}
	}		

	cout<<"Time taken = "<<duration.count()<<" ms"<<endl;

	return 0;
}