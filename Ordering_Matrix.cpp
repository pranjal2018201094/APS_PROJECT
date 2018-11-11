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

	//************NOW INSERTING THE EDGE IN THE NEW GRAPH WITH TRIANGULIZATION******************
	int i, j, k;

	for( k = ordered_vertices.size() - 1 ; k >= 0 ; k-- )
	{
		// cout<<"k = "<<k<<endl;		
		// cout<<"Kth value = "<<ordered_vertices[ k ]<<endl;
		for( j = k -1 ; j >= 0 ; j-- )
		{
			// cout<<"j = "<<ordered_vertices[ j ]<<endl;

			if( graph[ ordered_vertices[ k ] - 1 ][ ordered_vertices[ j ] - 1 ] != infy || graph[ ordered_vertices[ j ] - 1 ][ ordered_vertices[ k ] - 1 ] != infy )
				for( i = j - 1 ; i >= 0; i-- )
				{
					// cout<<"i = "<<ordered_vertices[ i ]<<endl;
					if ( graph[ ordered_vertices[ k ] - 1 ][ ordered_vertices[ i ] - 1 ] != infy || graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ k ] - 1 ] != infy )
					{
						int mij, mik, mkj, mjk, mki, mji;

						//*****************Calculation for i-to-j*******************
						mij = graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ j ] - 1 ] ;

						mik = graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ k ] - 1 ] ;

						mkj = graph[ ordered_vertices[ k ] - 1 ][ordered_vertices[ j ] - 1 ] ;

						mij = mij < mik + mkj ? mij : mik + mkj ;

						// cout<<"Triangulised distance between "<< ordered_vertices[ i ]<<" to "<<ordered_vertices[ j ]<<" through "<<ordered_vertices[ k ]<<" is "<<mij<<endl;

						graph[ ordered_vertices[ i ] - 1 ][ ordered_vertices[ j ] - 1 ] = mij ;

						//***************Calculation for j-to-i***********************
						mji = graph[ ordered_vertices[ j ] - 1 ][ ordered_vertices[ i ] - 1 ] ;

						mjk = graph[ ordered_vertices[ j ] - 1 ][ ordered_vertices[ k ] - 1 ] ;

						mki = graph[ ordered_vertices[ k ] - 1 ][ ordered_vertices[ i ] - 1 ] ;

						mji = mji < mjk + mki ? mji : mjk + mki ;

						// cout<<"Triangulised distance between "<< ordered_vertices[ j ]<<" to "<<ordered_vertices[ i ]<<" through "<<ordered_vertices[ k ]<<" is "<<mji<<endl;

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

	// cout<<"Prior neighbours"<<endl;
	for( k = s ; k >= 0 ; k-- )//for vertices which occur before 's' in ordering
	{
		// if( k > 0 )
		// cout<<"Out"<<endl;
		for( j = 0; j < neighbourL[ ordered_vertices[ k ] - 1 ].size() ; j++ )
		{
			// cout<<"In"<<endl;
			// if( graph[ ordered_vertices[ k ] - 1 ][ ordered_vertices[ j ] - 1 ] != infy )
			// {
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
				// graph[ ordered_vertices[ s ] - 1 ][ neighbourL[ ordered_vertices[ k ] - 1 ][ j ] ] = graph[ ordered_vertices[ s ] - 1 ][ neighbourL[ ordered_vertices[ k ] - 1 ][ j ] ] < graph[ ordered_vertices[ s ] - 1 ][ ordered_vertices[ k ] - 1 ] + graph[ ordered_vertices[ k ] - 1 ][ neighbourL[ ordered_vertices[ k ] - 1 ][ j ] ] ? graph[ ordered_vertices[ s ] - 1 ][ neighbourL[ ordered_vertices[ k ] - 1 ][ j ] ] : graph[ ordered_vertices[ s ] - 1 ][ ordered_vertices[ k ] - 1 ] + graph[ ordered_vertices[ k ] - 1 ][ neighbourL[ ordered_vertices[ k ] - 1 ][ j ] ] ;

			// }
		}
	}

	// cout<<"\n All pair shortest distances, after first loop, for "<<s<<"  : "<<endl;
	// for( int i = 0 ; i < n ; i++ )
	// 	for( int j = 0 ; j < n ; j++ )
	// 		cout<<i+1<<"  "<<j+1<<"  "<<graph[ i ][ j ]<<endl;

	// cout<<"For neighbours after that vertex"<<endl;
	for( k = 0 ; k < ordered_vertices.size() - 1 ; k++ )//for vertices which occurs after 's' in ordering
	{
		// cout<<"Out"<<endl;
		// if( k <= ordered_vertices.size() - 2 )
		for( j = 0 ; j < neighbourR[ ordered_vertices[ k ] - 1 ].size() ; j++ )
		{
			// cout<<"In"<<endl;
			// cout<<"Inner most loop for  k = "<<k<<endl;
			// if( graph[ ordered_vertices[ k ] - 1 ][ neighbour[ ordered_vertices[ k ] - 1 ][ j ] - 1 ] != infy )
			// {
				int msj, msk, mkj;

				// cout<<"1"<<endl;
				msj = graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] ] ;//Initializing variables
				// cout<<"2"<<endl;
				msk = graph[ ordered_vertices[ s ] - 1 ][ ordered_vertices[ k ] - 1 ] ;
				// cout<<"3"<<endl;
				mkj = graph[ ordered_vertices[ k ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] ] ;
				// cout<<"4"<<endl;

				if( msk == infy || mkj == infy )
				{
					//do nothing	
				}
				else
				{
					graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] ] = msj < msk + mkj ? msj : msk + mkj ;
				// cout<<"5"<<endl;
				}

				// graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] - 1 ] = graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] - 1 ] < graph[ ordered_vertices[ s ] - 1 ][ ordered_vertices[ k ] - 1 ] + graph[ ordered_vertices[ k ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] - 1 ] ? graph[ ordered_vertices[ s ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] - 1 ] : graph[ ordered_vertices[ s ] - 1 ][ ordered_vertices[ k ] - 1 ] + graph[ ordered_vertices[ k ] - 1 ][ neighbourR[ ordered_vertices[ k ] - 1 ][ j ] - 1 ] ;
			// }
		}
	}
	// cout<<"\n All pair shortest distances, after second loop, for "<<s<<"  : "<<endl;
	// for( int i = 0 ; i < n ; i++ )
	// 	for( int j = 0 ; j < n ; j++ )
	// 		cout<<i+1<<"  "<<j+1<<"  "<<graph[ i ][ j ]<<endl;	
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
	// cout<<"\n Number of vertices in graph = "<<n<<endl;

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

	// cout<<"\n Taking input : "<<endl;
	while( infile >> ch >> a >> b >> w)//Reading the file and storing into the map
	{
		if( graph[a - 1][b - 1] != infy )
		{
			// cout<<"\n MULTIPLE ENTRIES FOR SAME EDGE "<<endl;
			exit(EXIT_FAILURE);
		}

		graph[a - 1][b - 1] = w;
		// graph_tri[a - 1][b - 1] = w;
		// cout<<a<<"  "<<b<<"  "<<graph[a - 1][b - 1]<<endl;

		// in_degree[a - 1]++;
		in_degree[b - 1]++;

	}

	//**********************TO GET THE ORDERING*******************************************
	// t1 = clock();
	 
	order( in_degree, ordered_vertices ); 

	// cout<<"Ordering:-"<<endl;//******************OK TESTED************************
	// for( int i = 0 ; i < ordered_vertices.size() ; i++ )
	// 	cout<<ordered_vertices[i]<<endl;


	//***********************FOR TRIANGULARIZING THE GRAPH******************************** 
	triangle(graph, ordered_vertices );//order of argument is " original graph, triangulised graph, in_degree vector, ordered_vertices vector"

	// cout<<"\n After triangulisation  : "<<endl;
	// for( int i = 0 ; i < n ; i++ )
	// 	for( int j = 0 ; j < n ; j++ )
	// 		cout<<i+1<<"  "<<j+1<<"  "<<graph[ i ][ j ]<<endl;

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


		// for( int i = 0 ; i < ordered_vertices.size() ; i++ )
		// {
		// 	cout<<"Right neighbours of "<<ordered_vertices[ i ]<<endl;
		// 	for( int j = 0 ; j < neighbourR[ ordered_vertices[ i ] - 1 ].size() ; j++ )
		// 		cout<<neighbourR[ ordered_vertices[ i ] - 1 ][ j ] + 1<<endl;
		// }

		// for( int i = 0 ; i < ordered_vertices.size() ; i++ )
		// {
		// 	cout<<"Left neighbours of "<<ordered_vertices[ i ]<<endl;
		// 	for( int j = 0 ; j < neighbourL[ ordered_vertices[ i ] - 1 ].size() ; j++ )
		// 		cout<<neighbourL[ ordered_vertices[ i ] - 1 ][j] + 1<<endl;
		// }

	//**********************FINDING THE ALL PAIR SHORTEST PATH***********************************
	int v;

	// cout<<"After filling neighbour vectors "<<endl;

	for(v = 0 ; v < n ; v++ )//for making diagonal of matrix 0
		graph[v][v] = 0 ;

	// cout<<"Calling min_path "<<endl;

	auto start = high_resolution_clock::now();
	for(v = 0 ; v < n ; v++ )//for every vertices we will call min_path in the order of  ordered_vertices
		min_path( v, graph, ordered_vertices, neighbourR, neighbourL ) ;

	// t2 = clock();
	auto stop = high_resolution_clock::now(); 


	//**************PRINTING SHORTEST DISTANCE GRAPH*************************

	auto duration = duration_cast<microseconds>(stop - start); 
	// cout<<"\n All pair shortest distances  : "<<endl;
	for( int i = 0 ; i < n ; i++ )
		for( int j = 0 ; j < n ; j++ )
			cout<<i+1<<" "<<j+1<<" "<<graph[ i ][ j ]<<endl;

	cout<<"Time taken = "<<duration.count()<<" ms"<<endl;	

	return 0;	
	
}