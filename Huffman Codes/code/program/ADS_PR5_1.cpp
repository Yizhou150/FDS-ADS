#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

typedef struct HuffNode {
	char c;  // the character
	int f;  // the frequency and the weight
	HuffNode *Left, *Right;  // the left and right son
} *HuffNodePtr;  // the pointer
typedef HuffNodePtr HuffTree;

long long wpl = 0;  // the minimal weighted path length

/* the compare function for the frequency */
bool cmpQ(HuffNodePtr x,HuffNodePtr y) {
	return x->f < y->f;  // increasing order
}

/* the compare function for the code */
bool cmpS(string x,string y) {
	return x.length()<y.length();  // increasing order
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
	map<char,int> freq;  // the map using characters as keys and frequency as values

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
	HuffTree root = GenerateHuffmanTree(Q_leaf,n);

	/* encode and calulate the wpl*/
	wpl -= root->f;  // the root->f should be excluded
	WPL(root);

	/* judge */
	char ci;
	string* code = new string[n];
	int pseudo_wpl;
	cin>>m; // number of cases
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
			/* judge if all the nodes are the leaf-nodes */
			sort(code,code+n,cmpS);  // sort the codes in increasing length
			bool flag = true;
			for (int i = 0; i < n-1; i++)
				for (int j = i+1; j < n; j++) {
					/* if one code is the prefix of another then it can’t be a leaf node*/
					if (code[i] == code[j].substr(0,code[i].length())) {
						flag = false;
						break;
					}
				}
			if (flag) cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	delete []code;

	return 0;
}
