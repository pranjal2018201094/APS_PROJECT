#include<bits/stdc++.h>
using namespace std;

void triangle( map< int, map<int, int> > &graph_ori, map< int, map<int, int> > &graph_tri )
{
	//********************CODE FOR ORDERING THE VERTICES ACCORDING TO THERE DEGREE*****************

	vector< pair<int, int> > degree;//structure is degree, vertex, so that we can easily sort it 

	map< int, map<int, int> > :: iterator itrr;//to traverse whole original map

	for( itrr = graph_ori.begin() ; itrr != graph_ori.end() ; itrr++)
	{
		degree.push_back( make_pair( graph_ori[ itrr->first ].size(), itrr->first ));//( degree, vertx )
	}

	sort( degree.begin(), degree.end() );// to order the vertices according to there degree

	/* Uncomment it to see ordering of vertices
	vector< pair< int, int > > :: iterator it3;
	cout<<"\n Ordering of vertices is as follows "<<endl;
	for( it3 = degree.begin() ; it3 != degree.end() ; it3++ )
		cout<<it3->second;*/	

	//******************UPTO HERE, THERE IS CODE FOR ORDERING THE VERTICES ACCORDING TO THERE DEGREE*********

	//************NOW INSERTING THE EDGE IN THE NEW GRAPH WITH TRIANGULIZATION******************

	vector< pair< int, int > > :: iterator itr;// to iterate through-out the degree vertex
	map< int, int > :: iterator it1;// to traverse neighbours of any vertex
	map< int, int > :: iterator it2;// to traverse every possible pair of immediate neighbours

	for( itr = degree.begin() ; itr != degree.end() ; itr++ )
	{
		for( it1 = graph_ori[ itr->second ].begin() ; it1 != graph_ori[ itr->second ].end() ; it1++ )
		{
			for( it2 = graph_ori[ itr->second ].begin() ; it2 != graph_ori[ itr->second ].end() ; it2++ )
			{
				if( it1 == it2 && it2 != graph_ori[ itr->second ].begin() )
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
				}

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

	infile >> n;
	cout<<"\n Number of vertices in graph = "<<n<<endl;

	while( infile >> a >> b >> w)//Reading the file and storing into the map
	{
		if( graph[a][b] || graph[b][a] )
		{
			cout<<"\n MULTIPLE ENTRIES FOR SAME EDGE ";
			exit(EXIT_FAILURE);
		}
		cout<<a<<"  "<<b<<"  "<<w<<endl;
		graph[a][b] = w;
		graph[b][a] = w;


	}

	triangle(graph, graph_tri);//order of argument is " original graph, triangulised graph"

	//**************PRINTING TRIANGULARIZED GRAPH*************************

	map< int, map< int, int > > :: iterator itrr;
	map< int, int > :: iterator it;

	itrr = graph_tri.begin();

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