#include<bits/stdc++.h>
using namespace std;

void triangle( map< int, map<int, int> > &graph_ori, map< int, map<int, int> > &graph_tri, map< int, int > &in_degree )
{
	//********************CODE FOR ORDERING THE VERTICES ACCORDING TO THERE DEGREE*****************

	vector< pair<int, int> > degree;//structure is degree, vertex, so that we can easily sort it 

	map< int, map<int, int> > :: iterator itrr;//to traverse whole original map

	//Considering degree = in_degree + out_degree

	for( itrr = graph_ori.begin() ; itrr != graph_ori.end() ; itrr++)
	{
		degree.push_back( make_pair( graph_ori[ itrr->first ].size() + in_degree[ itrr->first ], itrr->first ));//( degree, vertx )
	}

	sort( degree.begin(), degree.end() );// to order the vertices according to there degree

	vector< pair< int, int > > :: iterator it3;
	vector< int > ordered_vertices;

	//**************Storing ordered vertices in a vector ordered_vertices*******************
	for( it3 = degree.begin() ; it3 != degree.end() ; it3++ )
		ordered_vertices.push_back( it3->second );

	//******************UPTO HERE, THERE IS CODE FOR ORDERING THE VERTICES ACCORDING TO THERE DEGREE*********

	//************NOW INSERTING THE EDGE IN THE NEW GRAPH WITH TRIANGULIZATION******************

	// vector< pair< int, int > > :: iterator itr;// to iterate through-out the degree vertex
	// map< int, int > :: iterator it1;// to traverse neighbours of any vertex
	// map< int, int > :: iterator it2;// to traverse every possible pair of immediate neighbours
	int i, j, k;

	for( k = ordered_vertices.size() - 1 ; k >= 0 ; k-- )
	{
		for( j = k -1 ; j >= 0 ; j-- )
		{
			for( i = j - 1 ; i >= 0 ; i-- )
			{
				int mij, mik, mkj, mjk, mki, mji;

				//*****************Calculation for i-to-j*******************
				if( graph_ori[ ordered_vertices[ i ] ][ ordered_vertices[ j ] ] )//weight of i to j
					mij = graph_ori[ ordered_vertices[ i ] ][ ordered_vertices[ j ] ] ;
				else
					mij = 1000000;

				if( graph_ori[ ordered_vertices[ i ] ][ ordered_vertices[ k ] ] )// weight of i to k
					mik = graph_ori[ ordered_vertices[ i ] ][ ordered_vertices[ k ] ] ;
				else
					mik = 1000000;

				if( graph_ori[ ordered_vertices[ k ] ][ ordered_vertices[ j ] ] )// weight of k to j
					mkj = graph_ori[ ordered_vertices[ k ] ][ordered_vertices[ j ] ] ;
				else
					mkj = 1000000;

				mij = mij < mik + mkj ? mij : mik + mkj ;
				graph_tri[ ordered_vertices[ i ] ][ ordered_vertices[ j ] ] = mij ;

				if( ordered_vertices[ i ] == 2 && ordered_vertices[ j ] == 3 )
				{
					cout<<ordered_vertices[ i ]<<" "<<ordered_vertices[ j ]<<endl;
					cout<<"At k = "<<ordered_vertices[ k ]<<" value is "<<mij<<endl;
				}

				//***************Calculation for j-to-i***********************
				if( graph_ori[ ordered_vertices[ j ] ][ ordered_vertices[ i ] ] )//weight of j to i
					mji = graph_ori[ ordered_vertices[ j ] ][ ordered_vertices[ i ] ] ;
				else
					mji = 1000000;

				if( graph_ori[ ordered_vertices[ j ] ][ ordered_vertices[ k ] ] )// weight of j to k
					mjk = graph_ori[ ordered_vertices[ j ] ][ ordered_vertices[ k ] ] ;
				else
					mjk = 1000000;

				if( graph_ori[ ordered_vertices[ k ] ][ ordered_vertices[ i ] ] )// weight of k to i
					mki = graph_ori[ ordered_vertices[ k ] ][ ordered_vertices[ i ] ] ;
				else
					mki = 1000000;

				mji = mji < mjk + mki ? mji : mjk + mki ;
				graph_tri[ ordered_vertices[ j ] ][ ordered_vertices[ i ] ] = mji;

				if( ordered_vertices[ j ] == 2 && ordered_vertices[ i ] == 3 )
				{

					cout<<ordered_vertices[ j ]<<" "<<ordered_vertices[ i ]<<endl;
					cout<<"At k = "<<ordered_vertices[ k ]<<" value is "<<mji<<endl;
				}
				//***************Checking for consistency*************************
				if( mij + mji < 0 )
				{
					cout<<"\nINCONSISTENT GRAPH"<<endl;
					exit(EXIT_FAILURE);
				}
				/*if( it1 == it2 && it2 != graph_ori[ itr->second ].begin() )
					continue;

				else if( graph_ori[itr->second ].size() == 1 )
				{
					graph_tri[itr->second][it1->first] = graph_ori[itr->second][it1->first] ;
					graph_tri[it1->first][itr->second] = graph_ori[itr->second][it1->first] ; 
				}

				else if( graph_ori[ it1->first ][ it2->first ] )
				{
					int x, y;

					x = graph_ori[ it1->first ][ it2->first ];
					y = graph_ori[ itr->second ][ it1->first ] + graph_ori[ itr->second ][ it2->first ];
					int z = ( x <= y )? x : y;

					// cout<<"\n For "<<it1->first<<" "<<it2->first<<endl;
					// cout<<"\t"<<"Pre = "<<x<<"\t"<<"Sum = "<<y<<endl;

					if( graph_tri[ it1->first ][ it2->first ] )
					{
						z = z < graph_tri[ it1->first ][ it2->first ] ? z : graph_tri[ it1->first ][ it2->first ] ;	
					}

					graph_tri[ it1->first ][ it2->first ] = z ;// Inserting in the triangularized graph 
					graph_tri[ it2->first ][ it1->first ] = z ;

					// cout<<"\n\t Final value: "<<z<<endl;
				}*/

			}
		}
	}
	//****************TRIANGULARIZED GRAPH'S CODE IS UPTO HERE*******************************


}


int main(int argc, char *argv[])
{
	if( argc != 2 )//Checking if command is appropriate
	{
		cout<<"INVALID COMMAND"<<endl;
		exit(EXIT_FAILURE);
	}

	ifstream infile(argv[1]);//Opening the file havin input

	if( !infile.good() )
		exit( EXIT_FAILURE );

	int n, a, b, w;//Declaring variables for accessing the file

	/*We are using structure of graph as map< int, map<int, int> > because it makes it easy to access 
	the graph get the degree, and traverse the neighbour and their weights, as if we want weight 
	from a->b, we can access it just by typing graph[a][b], and if we want to access th number of 
	neighbours of the node 'a' then we have to just type, graph[a].size()*/

	map< int, map<int, int> > graph;//Original graph, structure is a, b, w, where (a,b) is edge and w is weight between them
	map< int, map<int, int> > graph_tri;//diagonalised graph, structure is same as above
	map< int, int > in_degree; 

	infile >> n;
	cout<<"\n Number of vertices in graph = "<<n<<endl;

	cout<<"\n Taking input : "<<endl;
	while( infile >> a >> b >> w)//Reading the file and storing into the map
	{
		if( graph[a][b] )
		{
			cout<<"\n MULTIPLE ENTRIES FOR SAME EDGE ";
			exit(EXIT_FAILURE);
		}
		cout<<a<<"  "<<b<<"  "<<w<<endl;
		graph[a][b] = w;
		graph_tri[a][b] = w;
		in_degree[b]++;


	}

	triangle(graph, graph_tri, in_degree );//order of argument is " original graph, triangulised graph"

	//**************PRINTING TRIANGULARIZED GRAPH*************************

	map< int, map< int, int > > :: iterator itrr;
	map< int, int > :: iterator it;

	itrr = graph_tri.begin();

	cout<<"\n Printing output : "<<endl;
	while( itrr != graph_tri.end() )
	{
		it = graph_tri[ itrr-> first ].begin();

		while( it != graph_tri[ itrr-> first ].end() )
		{
			cout<<itrr->first<<"\t"<<it->first<<"\t"<<it->second<<endl;
			it++;
		}
		itrr++;
	}
}