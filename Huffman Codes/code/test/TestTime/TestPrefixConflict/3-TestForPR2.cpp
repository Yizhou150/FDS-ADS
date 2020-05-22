#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<ctime>
using namespace std;

typedef struct HuffNode {
	char c;  // the character
	int f, w;  // the frequency and the weight
	HuffNode *Left, *Right;  // the left and right son
} *HuffNodePtr;  // the pointer
typedef HuffNodePtr HuffTree;

typedef struct TrieNode {
	bool isLeaf,isVisited;
	TrieNode *Left,*Right;
} *TrieNodePtr;
typedef TrieNodePtr TrieTree;

TrieNodePtr createTrieNode() {
	TrieNodePtr T = new TrieNode;
	T->Left=T->Right = NULL;
	T->isLeaf = T->isVisited = false;
	return T;
}

bool insert(TrieTree root, string s) {
	TrieNodePtr T = root;
	for (int i = 0; i < s.length(); i++) {
		if (s[i]=='0') {
			if ( T->Left == NULL)
				T->Left = createTrieNode();
			T = T->Left;
		}
		else {
			if (T->Right == NULL)
				T->Right = createTrieNode();
			T = T->Right;
		}
		if (T->isLeaf)
			return false;
		if (i == s.length()-1 && T->isVisited) 
			return false;
		if (i == s.length()-1) T->isLeaf = true;
		T->isVisited = true;
	}
	return true;
}

/* the compare function */
bool cmpQ(HuffNodePtr x,HuffNodePtr y) {
	return x->f < y->f;  // increasing order
}

long long wpl = 0;

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

void WPL(HuffTree root) {
	if (root == NULL) return;
	wpl += root->f;
	WPL(root->Left);
	WPL(root->Right);
}

int main(void) {
	int n,m;
	clock_t start,stop;
	double sum;
	freopen("input4program.in","r",stdin);
	cin>>n;  // number of nodes
	HuffNodePtr* Q_leaf = new HuffNodePtr[n];  // initial nodes as leaves
	map<char,int> freq;

	/* input and initialize */
	for (int i = 0; i < n; i++) {
		Q_leaf[i] = new HuffNode;
		cin >> Q_leaf[i]->c >> Q_leaf[i]->f;
		freq[Q_leaf[i]->c] = Q_leaf[i]->f;
		Q_leaf[i]->Left = Q_leaf[i]->Right = NULL;
		Q_leaf[i]->w = 0;
	}

	/* sort by the frequency */
	sort(Q_leaf,Q_leaf+n,cmpQ);

	/* generate huffman tree */
	HuffTree Huffroot = GenerateHuffmanTree(Q_leaf,n);

	/* encode and calulate the wpl*/
	WPL(Huffroot);
	wpl -= Huffroot->f;

	/* judge */
	char ci;
	string* code = new string[n];
	int pseudo_wpl;
	cin>>m;
		for (int r = 0; r < m; r++) {
			pseudo_wpl = 0;
			for (int i = 0; i < n; i++) {
				cin>>ci>>code[i];
				pseudo_wpl += freq[ci]*code[i].length();
			}
			if (pseudo_wpl != wpl) {
			//	cout<<"No"<<endl;
				continue;
			}
			else {
				start = clock();
				/* use trie tree */
				bool flag = true;
				TrieTree Trieroot = createTrieNode();
				for (int i = 0; i < n; i++)
					if (!insert(Trieroot,code[i])) {
						flag = false;
						break;
					}
				//if (flag) cout<<"Yes"<<endl;
				//else cout<<"No"<<endl;
				stop = clock();
			}
			sum=sum+(stop - start);
		}
		cout<<m<<" student submissions"<<" with "<<n<<" characters"<<endl;
		cout<<"duration:"<<sum/CLOCKS_PER_SEC<<endl;
	system("pause");
	return 0;
}
