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

	// cout<<"Going to open file"<<endl ;

	// cout<<"\n Input file name is " << argv[1];
	ifstream infile( argv[1] );//Getting input from file
	// infile.getline( buffer, BUFFER_SIZE, '\n' );
	// cout<<"Going to read first line "<<endl;
	infile >>number_of_vertex>>e;

	// cout<<"\n Data red from file = "<<buffer; 
	// number_of_vertex = ( unsigned int ) atoi(buffer);
	// cout<<"\n Number of vertices = " << number_of_vertex << endl ;

	// cout<<"Going to allocate memory for matrix"<<endl;

		// *A=(int *)malloc( number_of_vertex*sizeof( int ) ) ;

	// cout<<"Memory  for columns "<<endl;
	vector< vector< int > > A(number_of_vertex);//Original graph
	for( int i = 0 ; i < number_of_vertex ; i++ )
		A[i].resize(number_of_vertex);

	// cout<<"Setting values infinity "<<endl;
	for( i = 0 ; i < number_of_vertex  ; i++ )
		for( j = 0 ; j <  number_of_vertex ; j++ )
			if( i == j )
				A[i][j] = 0 ;
			else
				A[i][j]=1000000;

	char ch;//to support the test file
	while( infile >> ch >> a >> b >> w )
	{
		// cout<<"\n Taking input "<<endl;	

		// char *vAs, *vBs, *eLs;
		// int vA, vB, eL;

		// vAs = buffer;// reading from file
		// vBs = strpbrk(vAs, " \t");
		// eLs = strpbrk(vBs, " \t");
		// vA = ( unsigned int ) atoi(vAs);
		// vB = ( unsigned int ) atoi(vBs);
		// eL = ( int )atoi(eLs);

		A[a - 1][b - 1] = w;

		// cout<<a<<" "<<b<<" "<<w<<endl;
	}

	// cout<<"\n Enter the number of vertices you want "<<endl;
	// cin>>number_of_vertex;


	// cout<<"\n Enter the input into the adjancy matrix "<<endl; //Input
	// for(i=0;i<number_of_vertex;i++)
	// 	for(j=0;j<number_of_vertex;j++)
	// 	{
	// 		cout<<"[ "<<i<<" ] [ "<<j<<" ] = ";
	// 		cin>>A[i*number_of_vertex+j];
	// 	}
	auto start = high_resolution_clock::now(); 
	auto stop = high_resolution_clock::now(); 

	try //Processing, Floyd Warshall's standard algorithm for All Pair Shortest Path
	{
	// t1=clock();

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
	// t2= clock();
	stop = high_resolution_clock::now(); 
	}
	catch(exception *e)
	{
		cout<<e->what();
		exit(EXIT_FAILURE);
	}

	auto duration = duration_cast<microseconds>(stop - start); 

	// cout<<"\n Time taken = "<<(t2-t1); //Output

	// cout<<"\n All pair shortest distances  : "<<endl;
	for(i=0;i<number_of_vertex;i++)
	{
		for(j=0;j<number_of_vertex;j++)
		{
			cout<<i+1<<" "<<j+1<<" "<<A[i][j]<<endl;
		}
		// cout<<"\n";
	}		

	cout<<"Time taken = "<<duration.count()<<" ms"<<endl;

	return 0;
}