#include <bits/stdc++.h>
using namespace std;
void create_wu(vector<int>&root,vector<int>&size)
{
    for(int i=0;i<root.size();i++)
     {
        root[i]=i;
        size[i]=1;

     }

}


int find(int key,vector<int>&root)
{

  while(key!=root[key])
  {
  key=root[key];
  }

  return key;
}


void weighted_Union( int l , int r , vector<int>&root , vector<int>&size )
{
int root_l,root_r;
root_l=find(l,root);
root_r=find(r,root);
 if(size[root_l]>size[root_r])
 {
     
     root[root_r]=root_l;
     size[root_l]=size[root_l]+size[root_r];
 }
 else 
 {   
 	   root[root_l]=root_r;
     size[root_r]=size[root_r]+size[root_l];
   }



}



int main()
{

int l,r,root_l1,root_r1;
vector<int>root(6);
vector<int>size(6);
vector<pair<int,int>> res;
map<int,vector<pair<int,int>>> m;
vector<vector<int>> graph{{0,15,14,13,12,11},{15,0,10,9,8,7},{14,10,0,6,5,4},{13,9,6,0,3,2},{12,8,5,3,0,1},{11,7,4,2,1,0}};

priority_queue<int,vector<int>,greater<int>> pq;   //min heap
clock_t start,end;
start=clock();
for(int i=0;i<graph[0].size();i++)
{
  for(int j=0;j<graph[0].size();j++)
  {
    if(graph[i][j]!=0)
    {   
    	if(j>i)
    	{
           // cout<<graph[i][j]<<endl;
           pq.push(graph[i][j]);
    	   m[graph[i][j]].push_back(make_pair(i,j));

    	}
    	

    }

  }

}


float calculated_time;

create_wu(root,size);
// krushkal's logic starts from here.

while(!pq.empty())
{

l=m[pq.top()][0].first;
r=m[pq.top()][0].second;

root_l1=find(l,root);
root_r1=find(r,root);

// cout<<root_l1<<" "<<root_r1<<endl;
if(root_r1!=root_l1)
{  
	// cout<<l<<" "<<r<<endl;
	weighted_Union(root_l1,root_r1,root,size);
	res.push_back(make_pair(l,r));
}


m[pq.top()].erase(m[pq.top()].begin());
pq.pop();
}

end=clock();
calculated_time=(float)(end-start)/CLOCKS_PER_SEC;
calculated_time=calculated_time*1000000;


cout<<"TIME TAKEN USING MIN HEAP :"<<calculated_time<<" microseconds\n";
// printing minimum spanning tree.

cout<<"SPANIING TREE EDGES\n";
for(int i=0;i<res.size();i++)
{


	cout<<res[i].first<<" "<<res[i].second<<endl;
}


return 0;
}








