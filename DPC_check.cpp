#include<bits/stdc++.h>
#define MAX 1000007;
using namespace std;

int main()
{
	int e,v;
	cin>>e>>v;
	set<pair<pair<int,int> ,int >>edges;
	int arr[v][v];
	for (int i = 0; i < v; i++)
  		for (int j = 0; j < v; j++)
  		{
    		arr[i][j]=MAX;
  			if(i==j)
  				arr[i][j]=0;
  		}
	for(int i=0;i<e;i++)
	{
		int a,b,w;
		cin>>a>>b>>w;
		edges.insert({{a-1,b-1},w});
		arr[a-1][b-1]=w;
	}

	// for (int i = 0; i < v; i++)
	// {
	// 	for (int j = 0; j < v; j++)
 //    	{
 //    		cout<<arr[i][j]<<" ";
 //    	}
 //    	cout<<endl;
	// }
	int flag=1;
	for(int k=v-1;k>=0;k--)
	{
		for(int j=k-1;j>=0;j--)
		{
			for(int i=j-1;i>=0;i--)
			{
				arr[i][j]=min(arr[i][j],arr[i][k]+arr[k][j]);
				arr[j][i]=min(arr[j][i],arr[j][k]+arr[k][i]);
				edges.insert({{i,j},arr[i][j]});
				if(arr[i][j]+arr[j][i]<0)
				{
					flag=0;
					break;
				}
			}
			if(flag==0)
				break;
		}
		if(flag==0)
			break;
	}
	if(flag==0)
	{
		cout<<"INCONSISTENT"<<endl;
	}
	else
	{
		cout<<"CONSISTENT"<<endl;
	}

	// for (int i = 0; i < v; i++)
	// {
	// 	for (int j = 0; j < v; j++)
 //    	{
 //    		cout<<arr[i][j]<<" ";
 //    	}
 //    	cout<<endl;
	// }

	cout<<edges.size()<<endl;

	return 0;

}
