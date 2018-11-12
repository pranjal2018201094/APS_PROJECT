#include<bits/stdc++.h>
#define infy 1000000
using namespace std;
using namespace std::chrono;

int n;

void order( vector< int > &in_degree, vector< int > &ordered_vertices )
{
	vector< pair< int, int > > degree;//  to store vertices and their degree,so that we can apply sort on it

	int i = 0 ;

	while( i < in_degree.size() )
	{
		degree.push_back( make_pair( in_degree[i], i )) ;
		i++;
	}

	sort( degree.begin(), degree.end() ) ;

	vector< pair< int, int > > :: iterator itr ;

	itr = degree.begin() ; 
	i = 0 ;

	while( itr != degree.end() )
	{
		ordered_vertices[i] =  itr->second + 1  ;
		itr++ ;
		i++ ;
	}

}

void triangle( vector< vector< int > > &graph, vector< int > &ordered_vertices)//********************OK TESTED**********
{

	//************NOW INSERTING NEW EDGES IN THE GRAPH WITH TRIANGULIZATION******************
	int i, j, k;

	for( k = ordered_vertices.size() - 1 ; k >= 0 ; k-- )
	{

		for( j = k -1 ; j >= 0 ; j-- )
		{
			if( graph[ ordered_vertices[ k ] - 1 ][ ordered_vertices[ j ] - 1 ] != infy || graph[ ordered_vertices[ j ] - 1 ][ ordered_vertices[ k ] - 1 ] != infy )
				for( i = j - 1 ; i >= 0; i-- )
				{
					if ( graph[ ordered_vertices[ k ] - 1 ][ ordered_vertices[ i ] - 1 ] != infy || graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ k ] - 1 ] != infy )
					{
						int mij, mik, mkj, mjk, mki, mji;

						//*****************Calculation for i-to-j*******************
						mij = graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ j ] - 1 ] ;

						mik = graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ k ] - 1 ] ;

						mkj = graph[ ordered_vertices[ k ] - 1 ][ordered_vertices[ j ] - 1 ] ;

						mij = mij < mik + mkj ? mij : mik + mkj ;

						graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ j ] - 1 ] = mij ;

						//***************Calculation for j-to-i***********************
						mji = graph[ ordered_vertices[ j ] - 1 ][ ordered_vertices[ i ] - 1 ] ;

						mjk = graph[ ordered_vertices[ j ] - 1 ][ ordered_vertices[ k ] - 1 ] ;

						mki = graph[ ordered_vertices[ k ] - 1 ][ ordered_vertices[ i ] - 1 ] ;

						mji = mji < mjk + mki ? mji : mjk + mki ;

						graph[ ordered_vertices[ j ] - 1 ][ ordered_vertices[ i ] - 1 ] = mji;

						//***************Checking for consistency*************************
						if( mij + mji < 0 )
						{
							cout<<"\nINCONSISTENT GRAPH"<<endl;
							exit(EXIT_FAILURE);
						}
					}	

				}
		}
	}
	//****************TRIANGULARIZED GRAPH'S CODE IS UPTO HERE******************************
}

void min_path( int s,  vector< vector< int > > &graph, vector< int > &ordered_vertices, vector< vector< int > > &neighbourR, vector< vector< int > > &neighbourL )
{

	int k, i, j;//declaring helper variables

	for( k = s ; k >= 0 ; k-- )//for vertices which occur before 's' in ordering
	{
		for( j = 0; j < neighbourL[ ordered_vertices[ k ] - 1 ].size() ; j++ )
		{
				int msj, msk, mkj;

				msj = graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] ][ j ] - 1 ] ;//Initializing variables

				msk = graph[ ordered_vertices[ s ] - 1 ][ ordered_vertices[ k ] - 1 ] ;

				mkj = graph[ ordered_vertices[ k ] - 1 ][ neighbourL[ ordered_vertices[ k ] ][ j ] ] ;

				if( msk == infy || mkj == infy )
				{
					//do nothing	
				}
				else
				{
					graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] ] = msj < msk + mkj ? msj : msk + mkj ;
				}
		}
	}

	for( k = 0 ; k < ordered_vertices.size() - 1 ; k++ )//for vertices which occurs after 's' in ordering
	{
		for( j = 0 ; j < neighbourR[ ordered_vertices[ k ] - 1 ].size() ; j++ )
		{
				int msj, msk, mkj;

				msj = graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] ] ;//Initializing variables
			
				msk = graph[ ordered_vertices[ s ] - 1 ][ ordered_vertices[ k ] - 1 ] ;

				mkj = graph[ ordered_vertices[ k ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] ] ;

				if( msk == infy || mkj == infy )
				{
					//do nothing	
				}
				else
				{
					graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] ] = msj < msk + mkj ? msj : msk + mkj ;
				}
		}
	}

}


int main(int argc, char *argv[])
{

	clock_t t1, t2;

	if( argc != 2 )//Checking if command is appropriate
	{
		cout<<"INVALID COMMAND"<<endl;
		exit(EXIT_FAILURE);
	}

	ifstream infile(argv[1]);//Opening the file havin input

	if( !infile.good() )
	{
		cout<<"Checking goodness of file "<<endl ;
		exit( EXIT_FAILURE );
	}

	int  a, b, w, e;//Declaring variables for accessing the file
	char ch;//for the sake of test_file format

	infile >> n >> e;

	vector< int > in_degree(n); //to store the in degerees of vertices
	vector< int > ordered_vertices(n);//vector storing vertices numbers  according to there order

	vector< vector< int > > graph(n);//Original graph
	for( int i = 0 ; i < n ; i++ )
		graph[i].resize(n);

	for( int i = 0 ; i < n ; i++ )
		for( int j = 0 ; j < n ; j++ )
		{
			graph[ i ][ j ] = infy ;
		}

	while( infile >> ch >> a >> b >> w)//Reading the file and storing into the map
	{
		if( graph[a - 1][b - 1] != infy )
		{
			exit(EXIT_FAILURE);
		}

		graph[a - 1][b - 1] = w;

		in_degree[b - 1]++;

	}

	//**********************TO GET THE ORDERING*******************************************
	 
	order( in_degree, ordered_vertices ); 

	//***********************FOR TRIANGULARIZING THE GRAPH******************************** 
	triangle(graph, ordered_vertices );//order of argument is " original graph, triangulised graph, in_degree vector, ordered_vertices vector"

	//***********************TO STORE THE NEIGHBOURS**************************************

	/*We are storing the neighbours of a vertex inamanner that, the neighbour should appear after
	the vertex in the order, i.e., we will add 'v' as neighbour of 'u' if index of v 'vi' is greater
	than 'u th' index 'ui'*/

	vector< vector< int > > neighbourR(n);// to store the neighbours of a particular vertex after the ordering is done

	for( int i = 0 ; i < ordered_vertices.size() ; i++ )
		for( int j = i + 1 ; j < ordered_vertices.size() ; j++ )
		{
			if( graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ j ] - 1 ] != infy )
				neighbourR[ ordered_vertices[ i ] - 1 ].push_back( ordered_vertices[ j ] - 1 );
		} 

	vector< vector< int > > neighbourL(n);// to store the neighbours of a particular vertex after the ordering is done

	for( int i = 0 ; i < ordered_vertices.size()  ; i++ )
		for( int j = i - 1 ; j >= 0 ; j-- )
		{
			if( graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ j ] - 1 ] != infy )
				neighbourR[ ordered_vertices[ i ] - 1 ].push_back( ordered_vertices[ j ] - 1 );
		} 

	//**********************FINDING THE ALL PAIR SHORTEST PATH***********************************
	int v;

	for(v = 0 ; v < n ; v++ )//for making diagonal of matrix 0
		graph[v][v] = 0 ;

	auto start = high_resolution_clock::now();
	for(v = 0 ; v < n ; v++ )//for every vertices we will call min_path in the order of  ordered_vertices
		min_path( v, graph, ordered_vertices, neighbourR, neighbourL ) ;

	auto stop = high_resolution_clock::now(); 


	//**************PRINTING SHORTEST DISTANCE GRAPH*************************

	auto duration = duration_cast<microseconds>(stop - start); 
	//Uncomment this loop to see the  all pair shortes paths
	// for( int i = 0 ; i < n ; i++ )
	// 	for( int j = 0 ; j < n ; j++ )
	// 		cout<<i+1<<" "<<j+1<<" "<<graph[ i ][ j ]<<endl;

	cout<<"Time taken = "<<duration.count()<<" ms"<<endl;	

	return 0;	
	
}