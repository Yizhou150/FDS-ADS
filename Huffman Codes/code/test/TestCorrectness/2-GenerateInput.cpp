#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

typedef struct HuffNode {
	char c;  // the character
	int f, w;  // the frequency and the weight
	HuffNode *Left, *Right;  // the left and right son
} *HuffNodePtr;  // the pointer
typedef HuffNodePtr HuffTree;

/* the compare function */
bool cmpQ(HuffNodePtr x,HuffNodePtr y) {
	return x->f < y->f;  // increasing order
}

bool cmpS(string x,string y) {
	return x.length()<y.length();
}

long long wpl = 0;

HuffTree GenerateHuffmanTree(HuffNodePtr *Q_leaf, int n) {
	vector<HuffNodePtr> Q_nonleaf;  // generalized nodes as non-leaves
	int p = n, q = 0;  // p - number of nodes in Q_leaves		 q - number of nodes in Q_nonleaf
	int i = 0, j = 0; // i - index of the current element in Q_leaf		 j - index of the current element in Q_nonleaf
	HuffTree root;
	HuffNodePtr temp;
	while (p != 0 || q != 0) {
		/* if only 1 node left */
		if (p == 1 && q == 0) {
			root = Q_leaf[i];
			break;
		}
		if (p == 0 && q == 1) {
			root = Q_nonleaf[j];  //最后两个加起来 
			break;
		}
		
		/* pick 2 from the non-leaf nodes and add them up to make new node */
		if (q >= 2 && (p == 0 || Q_leaf[i]->f > Q_nonleaf[j+1]->f)) {
			temp = new HuffNode;
			temp->f = Q_nonleaf[j]->f + Q_nonleaf[j+1]->f;
			temp->Left = Q_nonleaf[j];
			temp->Right = Q_nonleaf[j+1];
			Q_nonleaf.push_back(temp);
			j+=2; q--;	
		}
		
		/* pick 2 from the leaf nodes and add them up to make new node */
		else if (p >= 2 && (q == 0 || Q_leaf[i+1]->f < Q_nonleaf[j]->f)) {
			temp = new HuffNode;
			temp->f = Q_leaf[i]->f + Q_leaf[i+1]->f;
			temp->Left = Q_leaf[i];
			temp->Right = Q_leaf[i+1];
			Q_nonleaf.push_back(temp);
			i+=2; p-=2; q++;	
		}
		/* pick 1 from leaf nodes and and 1 from non-leaf nodes */
		else {
			temp = new HuffNode;
			temp->f = Q_leaf[i]->f + Q_nonleaf[j]->f;
			temp->Left = Q_leaf[i];
			temp->Right = Q_nonleaf[j];
			Q_nonleaf.push_back(temp);
			i++; j++; p--;
		}
	//	cout<<i<<" "<<j<<" "<<p<<" "<<q<<" "<<temp->f<<endl;
	}
	return root;
}

void WPL(HuffTree root) {
	if (root == NULL) return;
	wpl += root->f;
	WPL(root->Left);
	WPL(root->Right);
}

void getCode(HuffTree rt, string code){
	
	if(rt->Left == NULL && rt->Right == NULL){
		cout << rt->c << " " << code <<endl;
		return ;
	}
	getCode(rt->Left,code+'0');
	getCode(rt->Right,code+'1');
}
void getWrongCode(HuffTree rt, string code){
	int t=rand()%2; 
	if(rt->Left == NULL && rt->Right == NULL){
		cout << rt->c << " " << code <<endl;
		return ;
	}
	char tmp='0'+t;
	getCode(rt->Left,code+tmp);
	getCode(rt->Right,code+tmp);
}
int main(void) {
	int n,m;
	freopen("input.in","r",stdin);
	freopen("input4program.in","w",stdout); 
	cin>>n;  // number of nodes
	
	HuffNodePtr* Q_leaf = new HuffNodePtr[n];  // initial nodes as leaves
	HuffNodePtr temp;
	map<char,int> freq;

	/* input and initialize */
	for (int i = 0; i < n; i++) {
		Q_leaf[i] = new HuffNode;
		cin >> Q_leaf[i]->c >> Q_leaf[i]->f;
		freq[Q_leaf[i]->c] = Q_leaf[i]->f;
		Q_leaf[i]->Left = Q_leaf[i]->Right = NULL;
		Q_leaf[i]->w = 0;
	}
	cout<<n<<endl;
	for(int i = 0; i < n; i++){
		cout<< Q_leaf[i]->c <<" "<< Q_leaf[i]->f<<" ";
	} 
	cout<<endl;
	cin>>m;
	/* sort by the frequency */
	sort(Q_leaf,Q_leaf+n,cmpQ);
	cout<<m<<endl; 
	
	
	/* generate huffman tree */
	for(int i=0;i<m;i++){
		int t=rand(); 
		sort(Q_leaf,Q_leaf+n,cmpQ);
		HuffTree root = GenerateHuffmanTree(Q_leaf,n);
		if(t%2==0) getCode(root,""); 
		if(t%2==1) getWrongCode(root,"");
	//	cout<<endl;
		/* encode and calulate the wpl*/
		
		for (int k=n-1;k>=1;k--) {   //shuffle algorithm
			int p=rand()%k+1;
			temp=Q_leaf[k];
			Q_leaf[k]=Q_leaf[p];
			Q_leaf[p]=temp;
		} 
	}
	

	return 0;
}
