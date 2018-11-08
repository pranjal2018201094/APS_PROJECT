#include<iostream>
#include<time.h>
#include<limits.h>
#include<fstream>
#include<string.h>
#define BUFFER_SIZE 100
using namespace std;
int main(int argc, char *argv[])
{
	if( argc != 2 )
	{
		cout<<"\n Incorrect command "<<endl;
		cout<<"Format is <object> <file_name>"<<endl;
		exit(EXIT_FAILURE);
	}

	unsigned int number_of_vertex, row, col;
	char buffer[BUFFER_SIZE];
	clock_t t1, t2;
	int *A, i ,j, k;

	// cout<<"\n Input file name is " << argv[1];
	ifstream infile( argv[1] );//Getting input from file
	infile.getline( buffer, BUFFER_SIZE, '\n' );

	cout<<"\n Data red from file = "<<buffer; 
	number_of_vertex = ( unsigned int ) atoi(buffer);
	cout<<"\n Number of vertices = " << number_of_vertex << endl ;

	A=(int *)malloc( number_of_vertex*number_of_vertex*sizeof( int ) ) ;

	for( i = 0 ; i < number_of_vertex * number_of_vertex -1 ; i++ )
		A[i]=INT_MAX;

	while( infile.getline(buffer, BUFFER_SIZE, '\n' ) && !infile.eof() )
	{
		// cout<<"\n Taking input "<<endl;	

		char *vAs, *vBs, *eLs;
		int vA, vB, eL;

		vAs = buffer;// reading from file
		vBs = strpbrk(vAs, " \t");
		eLs = strpbrk(vBs, " \t");
		vA = ( unsigned int ) atoi(vAs);
		vB = ( unsigned int ) atoi(vBs);
		eL = ( int )atoi(eLs);

		A[ vA * number_of_vertex + vB ] = eL;
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

	try //Processing, Floyd Warshall's standard algorithm for All Pair Shortest Path
	{
	t1=clock();
	for(k=0;k<number_of_vertex;k++)
		for(i=0;i<number_of_vertex;i++)
			for(j=0;j<number_of_vertex;j++)	
			{
				A[i*number_of_vertex+j]=(A[i*number_of_vertex+j]>(A[i*number_of_vertex+k] + A[k*number_of_vertex+j]))?(A[i*number_of_vertex+k] + A[k*number_of_vertex+j]) : A[i*number_of_vertex+j];
			}
	t1= clock();
	}
	catch(exception *e)
	{
		cout<<e->what();
		exit(EXIT_FAILURE);
	}

	cout<<"\n Time taken = "<<(t2-t1)/CLOCKS_PER_SEC; //Output

	for(i=0;i<number_of_vertex;i++)
	{
		for(j=0;j<number_of_vertex;j++)
		{
			cout<<A[i*number_of_vertex+j]<<" ";
		}
		cout<<"\n";
	}		

	return 0;
}