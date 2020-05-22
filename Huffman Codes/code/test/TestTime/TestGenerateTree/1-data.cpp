#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
struct Node{
	char c;
	int  f;
	
};

bool cmpQ(Node x,Node y) {
	return x.f < y.f;  // increasing order
}

int main(void) {

	// redirect the input and output
	freopen("size.in","r",stdin);  //include n and m 
	freopen("input.in","w",stdout); 
	int n,m;  // n - number of the characters		m - number of the cases
	cin>>n;  // length of the sequence
//	cin>>m;  // number of the cases
	Node node[n];
	srand((unsigned)time(NULL));
	
	cout<<n<<endl;  //N
	
	for (int i = 0; i < n; i++){  //random frequency
		node[i].f =rand() %(n/2) + 1 ; 
		//node[i].f =1; 
	} 
	
	for (int i = 0; i < n; i++){  //characters
		if(i<10)	node[i].c=48+i;
		else if(i<36)	node[i].c=55+i;
		else if(i<62)	node[i].c=61+i;
		else if(i==62)  node[i].c=45;
	}
	
	
	sort(node,node+n,cmpQ);
	for(int i = 0; i < n; i++){
		if(i!=n-1) printf("%c %d ",node[i].c,node[i].f);
		else printf("%c %d",node[i].c,node[i].f); 
	}
	printf("\n");
	
	cout<<m<<endl; 
	 
//	for(int i = 0; i < n; i++)	printf("%c %d\n",node[i].c,node[i].f);

	//cin>>m;
	
/*	for(int i = 0; i < m; i++){
		//true case
		for(int j = 0; j < n; j++){
			printf("%c ",node[j].c);
			for(int k=0; k<)
		}
		//random case
		printf("");
	}*/ 
	// randomly create an input
	
	return 0;	
}
