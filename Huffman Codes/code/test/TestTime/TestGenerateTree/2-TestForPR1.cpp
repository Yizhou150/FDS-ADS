#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<time.h>
#include<stdio.h>

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
clock_t start, stop;
double duration;

HuffTree GenerateHuffmanTree(HuffNodePtr *Q_leaf, int n) {
	vector<HuffNodePtr> Q_nonleaf;  // generalized nodes as non-leaves
	int p = n, q = 0;  // p - number of nodes in Q_leaves q - number of nodes in Q_numleaf
	int i = 0, j = 0; // i - index of the current element in Q_leaf j - index of the current element in Q_nonleaf
	HuffTree root;
	HuffNodePtr temp;
	while (p != 0 || q != 0) {
		/* if only 1 node left */
		if (p == 1 && q == 0) {
			root = Q_leaf[i];
			break;
		}
		if (p == 0 && q == 1) {
			root = Q_nonleaf[j];
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
		//cout<<i<<" "<<j<<" "<<p<<" "<<q<<" "<<temp->f<<endl;
	}
	return root;
}


int main(void) {
	int n,m;
	int iter=1000;
	freopen("input.in","r",stdin);
	cin>>n;  // number of nodes

	HuffNodePtr** Q_leaf;
	Q_leaf= new HuffNodePtr* [iter];
	for(int i=0;i<iter;i++)
		Q_leaf[i]= new HuffNodePtr[n];  // initial nodes as leaves
	map<char,int> freq;

	/* input and initialize */
	for (int j=0 ; j<iter;j++)
		for (int i = 0; i < n; i++) {
			Q_leaf[j][i] = new HuffNode;
			freq[Q_leaf[j][i]->c] = Q_leaf[j][i]->f;
			Q_leaf[j][i]->Left = Q_leaf[j][i]->Right = NULL;
			Q_leaf[j][i]->w = 0;
		}
	for(int i=0;i<n;i++)
		cin >> Q_leaf[0][i]->c >> Q_leaf[0][i]->f;
		
	for (int j=1 ; j<iter;j++)
		for (int i = 0; i < n; i++){
			Q_leaf[j][i]->c=Q_leaf[0][i]->c;
			Q_leaf[j][i]->f=Q_leaf[0][i]->f;
		}
			
	/* sort by the frequency */
	for(int i=0;i<iter;i++)
		sort(Q_leaf[i],Q_leaf[i]+n,cmpQ);




	start = clock();
	/* generate huffman tree */
	for(int i=0;i<iter;i++)
		HuffTree root = GenerateHuffmanTree(Q_leaf[i],n);
	stop = clock();
	duration = ((double)(stop - start) / CLK_TCK/iter) ;
	printf("%f", duration);


}
