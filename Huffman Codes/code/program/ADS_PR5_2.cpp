#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

typedef struct HuffNode {
	char c;  // the character
	int f;  // the frequency and the weight
	HuffNode *Left, *Right;  // the left and right children
} *HuffNodePtr;  // the pointer
typedef HuffNodePtr HuffTree;

typedef struct TrieNode {
	bool isLeaf,isVisited;  // marks if the node is a leaf node or is visited
	TrieNode *Left,*Right;  // the left and right children
} *TrieNodePtr;  // the pointer
typedef TrieNodePtr TrieTree;

long long wpl = 0;  // the minimal weighted path length

/* This function is used to create a new node for trie tree
 * return the TrieNode pointer
 */
TrieNodePtr createTrieNode() {
	TrieNodePtr T = new TrieNode;
	T->Left=T->Right = NULL;
	T->isLeaf = T->isVisited = false;  // intialize
	return T;
}

/* This function is used to insert a new code to trie tree and judge if it is illegal
 * paramater root: the root of the trie tree
 * paramater s: the code to be inserted
 * return true for legal false for illegal
 */
bool insert(TrieTree root, string s) {
	TrieNodePtr T = root;
	for (int i = 0; i < s.length(); i++) {
		/* if 0 insert to the left subtree */
		if (s[i]=='0') {
			if ( T->Left == NULL)
				T->Left = createTrieNode();
			T = T->Left;
		}
		/* if 1 insert to the right subtree */
		else {
			if (T->Right == NULL)
				T->Right = createTrieNode();
			T = T->Right;
		}
		/* if the curent node is the leaf node of another code */
		if (T->isLeaf) return false;
		/* if current node reaches its end but the node is already visited */
		if (i == s.length()-1 && T->isVisited) return false; 
		/* set the leaf mark */
		if (i == s.length()-1) T->isLeaf = true;
		/* set the visited mark */
		T->isVisited = true;
	}
	return true;
}


/* This function is used to delete the trie tree and release the space
 * paramater root: the current node pointer
 */
void deleteTrieTree(TrieNodePtr root) {
	if (root == NULL) return;
	deleteTrieTree(root->Left);  // delete the left child
	deleteTrieTree(root->Right);  // delete thr right child
	delete root;
} 

/* the compare function for frequency */
bool cmpQ(HuffNodePtr x,HuffNodePtr y) {
	return x->f < y->f;  // increasing order
}

/* This function is used to generate a huffman tree
 * paramater Q_leaf: the initial nodes stored in increasing order
 * paramater n: number of nodes
 * return: the root of the generated huffman tree
 */
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
	}
	return root;
}

/* This function is used to calculated the weight of all nodes */
/* paramater root: the curent Huffnode pointer */
void WPL(HuffTree root) {
	if (root == NULL) return;
	wpl += root->f;
	WPL(root->Left);
	WPL(root->Right);
	delete root; // release the space
}

int main(void) {
	int n,m;

	cin>>n;  // number of nodes

	HuffNodePtr* Q_leaf = new HuffNodePtr[n];  // initial nodes as leaves
	map<char,int> freq;

	/* input and initialize */
	for (int i = 0; i < n; i++) {
		Q_leaf[i] = new HuffNode;
		cin >> Q_leaf[i]->c >> Q_leaf[i]->f;
		freq[Q_leaf[i]->c] = Q_leaf[i]->f;  // use a map for the afterwords match
		Q_leaf[i]->Left = Q_leaf[i]->Right = NULL;
	}

	/* sort by the frequency */
	sort(Q_leaf,Q_leaf+n,cmpQ);

	/* generate huffman tree */
	HuffTree Huffroot = GenerateHuffmanTree(Q_leaf,n);

	/* encode and calulate the wpl*/
	wpl -= Huffroot->f;  // the root->f should be excluded
	WPL(Huffroot);
	/* judge */
	char ci;
	string* code = new string[n];
	int pseudo_wpl;
	cin>>m;
	for (int r = 0; r < m; r++) {
		/* calculate the weighted path length of the case */
		pseudo_wpl = 0;
		for (int i = 0; i < n; i++) {
			cin>>ci>>code[i];
			pseudo_wpl += freq[ci]*code[i].length();
		}
		/* if not equal to the calculated minimal wpl */
		if (pseudo_wpl != wpl) {
			cout<<"No"<<endl;
			continue;
		}
		else {
			/* use trie tree to judge if all the nodes are the leaf-nodes */
			bool flag = true;
			TrieTree Trieroot = createTrieNode();  // an empty root
			for (int i = 0; i < n; i++)
				/* insert and judge if the node is a leaf-node */
				if (!insert(Trieroot,code[i])) {
					flag = false;
					break;
				}
			deleteTrieTree(Trieroot);
			if (flag) cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	delete []code;

	return 0;
}
