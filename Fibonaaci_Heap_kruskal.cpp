#include<bits/stdc++.h>
using namespace std;

int total_node=0;
int minimum=0;

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
	{key=root[key];}

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
class Node
{
	public:
		int key;
		Node* left;
		Node* right;
		Node* parent;
		Node* child;
		int mark;
		int degree;


		Node()
		{
			
			left=NULL;
			right=NULL;
			parent=NULL;
			child=NULL;
			mark=0;
			degree=0;
		}
		Node(int y)
		{
			key=y;
			left=NULL;
			right=NULL;
			parent=NULL;
			child=NULL;
			mark=0;
			degree=0;
		}
};

Node *mini=NULL;
void insert(int val)
{
	total_node++;
	Node* new_n=new Node(val);
	new_n->key=val;
	new_n->left=new_n;
	new_n->right=new_n;
	if(mini==NULL)
	{
		
		mini=new_n;
		return;
	}

		
	(mini->left)->right=new_n;
	new_n->left=mini->left;
	new_n->right=mini;
	mini->left=new_n;
	if(new_n->key<mini->key)
	{mini=new_n;}

}

void display()
{
	if(mini==NULL)
	{
		cout<<"empty"<<endl;
		return;
	}

	Node* p=mini->right;
	cout<<"roots are"<<endl;
	cout<<mini->key<<" ";
	while(p!=mini && p->right!=NULL)
	{
		cout<<p->key<<" ";
		p=p->right;

	}

}
void swap_n(Node* trav,Node* p)
{
	Node* temp=NULL;
	temp=trav;
	trav=p;
	p=temp;
}

void make_parent(Node* childn,Node* parentn)
{
	(childn->left)->right=childn->right;
	(childn->right)->left=childn->left;

	if(parentn->right==parentn)
	{
		mini=parentn;

	}
	childn->left=childn;
	childn->right=childn;
	childn->parent=parentn;
	if(parentn->child==NULL)
	{
		parentn->child=childn;
	}
	childn->right=parentn->child;
	childn->left=(parentn->child)->left;
	((parentn->child)->left)->right=childn;
	(parentn->child)->left=childn;
	if(childn->key<(parentn->child)->key)
	{
		parentn->child=childn;
	}
	parentn->degree++;
	
}
void merge_degree()
{
	int max_d=(log(total_node)/log(2));
	Node* deg[max_d+1]={NULL};

	Node *trav=mini;
	int deg_i;
	do
	{
		deg_i=trav->degree;
		while(deg_i<=max_d && deg[deg_i]!=NULL && trav!=mini)
		{
			Node *p=deg[deg_i];
			if(trav->key>p->key)
			{
				Node* ptr3=trav;
				trav=p;
				p=ptr3;
							}

			if(p==mini)
			{
				mini=trav;
			}
			if(p==trav)
			{
				break;
			}
			make_parent(p,trav);
			if(trav->right==trav)
			{
				mini=trav;
			}

			deg[deg_i]=NULL;
			deg_i++;

		}
		deg[deg_i]=trav;
		trav=trav->right;
	}while(trav!=mini);

	mini=NULL;
	for(int i=0;i<=max_d;i++)
	{
		if(deg[i]!=NULL)
		{
			deg[i]->left=deg[i];
			deg[i]->right=deg[i];
			if(mini!=NULL)
			{
				(mini->left)->right=deg[i];
				deg[i]->right=mini;
				deg[i]->left=mini->left;
				mini->left=deg[i];
				if(deg[i]->key<mini->key)
				{
					mini=deg[i];
				}
			}

			else
			{
				mini=deg[i];
			}
			if(mini==NULL)
				mini=deg[i];
			else if(deg[i]->key<mini->key)
				{
					mini=deg[i];
				}
		}
	}
	
}
void extract_min()
{
	if(mini==NULL)
	{
		cout<<"empty "<<endl;
		return;
	}
	Node* temp=mini;
	Node* x=NULL;
	Node* xr=temp;
	minimum=temp->key;

	//bringing the heap of mini above
	if(temp->child!=NULL)
	{
		x=temp->child;
		
		do
		{
			xr=x->right;
			x->left=mini->left;
			x->right=mini;
			(mini->left)->right=x;
			mini->left=x;
			
			if(x->key<mini->key)
			{
				mini=x;
			}
			x->parent=NULL;
			x=xr;
		}while(xr!=temp->child);


	}

	(temp->left)->right=temp->right;
	(temp->right)->left=temp->left;
	mini=temp->right;
		if(temp->right==temp && temp->child==NULL)
	{
		mini=NULL;
		//return;
	}


	else
	{
		mini=temp->right;
		merge_degree();

		}

		total_node--;

}
int main()
{

	int l,r,root_l1,root_r1;
	vector<int>root(6);
	vector<int>size(6);
	vector<pair<int,int>> res;
map<int,vector<pair<int,int>>> m;
    clock_t start,end;
vector<vector<int>> graph{{0,15,14,13,12,11},{15,0,10,9,8,7},{14,10,0,6,5,4},{13,9,6,0,3,2},{12,8,5,3,0,1},{11,7,4,2,1,0}};
vector<int>edges;
	for(int i=0;i<graph[0].size();i++)
	{
	  for(int j=0;j<graph[0].size();j++)
	  {
		    if(graph[i][j]!=0)
		    {   
		    	if(j>i)
		    	{
		    		edges.push_back(graph[i][j]);
		    		 m[graph[i][j]].push_back(make_pair(i,j));

		    	}
		    }
	  }
	}


	for(int i=0;i<edges.size();i++)
	{insert(edges[i])}
	
start=clock();
//display();

float calculated_time;

create_wu(root,size);

for(int i=0;i<edges.size();i++)
{
		minimum=-1;
	 	extract_min();
	 	int min_n=minimum;
	 	l=m[min_n][0].first;
		r=m[min_n][0].second;

		root_l1=find(l,root);
		root_r1=find(r,root);

		if(root_r1!=root_l1)
		{  
			weighted_Union(root_l1,root_r1,root,size);
			res.push_back(make_pair(l,r));
		}

		m[min_n].erase(m[min_n].begin());
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