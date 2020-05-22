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

/* the struct of binary heap used as a priority queue*/
typedef struct HeapStruct {
	int size,capacity;
	HuffNodePtr *Elements;
} *Heap;

long long wpl = 0;  // the minimal weighted path length

/* the compare function for codes */
bool cmpS(string x,string y) {
	return x.length()<y.length();
}

/* This function is used to initialize a min-heap
 * paramater m: the necessary capacity
 * paramater H: the heap pointer
 * return H: the heap pointer
 */
Heap initialize_heap(int m, Heap H) {
	H = new HeapStruct;
	 H->capacity = m+1;  /* the index should be from 1 to m */
	 H->size = 0;  /* there is no element in the heap currently */
	 H->Elements = new HuffNodePtr[m+1]; /* allocate the memory for elements */
	if (H == NULL) {
		printf("Out of space.");
		exit(0);
	}
	H->Elements[0] = new HuffNode;
	H->Elements[0]->f=-1;  /* put a negative integer at elements[0] as the minimum value */
	H->Elements[0]->Left = H->Elements[0] ->Right = NULL;
	return H;
}

/* This function is used to insert a node into the heap
 * paramater x: the new node pointer
 * paramater H: the heap pointer
 */
void insert(HuffNodePtr x, Heap H){
	int i;
	H->size++;  /* expand the size of the heap */
	for (i = H->size; (H->Elements[i / 2])->f > x->f; i /= 2)  /* compare the value */
		H->Elements[i] = H->Elements[i / 2];  /* percolate up each vertex whose value is less than x's value */
	H->Elements[i] = x;  /* place the new vertex */
}

/* This function is used to delete the minimal node from the heap
 * paramater H: the heap pointer
 */
void deleteMin(Heap H) {
	int i,child;
	HuffNodePtr x;
	x = H->Elements[H->size--];  /* shrink the size of the heap and put the last vertex on element[1] */
	for (i = 1; i * 2 <= H->size; i = child) {
		child = i*2;
		if (child + 1 <= H->size && (H->Elements[child + 1])->f < (H->Elements[child])->f)
			child++;  /* pick the smaller children */
		if ((H->Elements[child])->f < x->f)
			H->Elements[i] = H->Elements[child];  /* percolate down each child whose value is larger than x's value */
		else break;
	}
	H->Elements[i] = x;  /* replace the last vertex */
}

/* This function is used to generate a huffman tree
 * paramater H: the heap pointer
 * paramater n: number of nodes
 * return: the root of the generated huffman tree
 */
HuffTree GenerateHuffmanTree(Heap H, int n) {
	HuffNodePtr temp;
	int ite = H->size-1; // the iteration number
	for (int i = 0; i < ite; i++) {
		/* find the two min value and delete them from the heap*/
		HuffNodePtr x = H->Elements[1];
		deleteMin(H);
		HuffNodePtr y = H->Elements[1];
		deleteMin(H);
		/* create a new node as their parent and insert it into the heap */
		temp = new HuffNode;
		temp->f = x->f + y->f;
		temp->Left = x;
		temp->Right = y;
		insert(temp,H);
	}
	/* the last element in the heap is the root of the huffman tree */
	return H->Elements[1];
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

	map<char,int> freq;

	/* input and initialize */
	Heap H;
	H = initialize_heap(n,H);
	HuffNodePtr temp;
	for (int i = 0; i < n; i++) {
		temp = new HuffNode;
		cin >> temp->c >> temp->f;
		temp->Left = temp->Right = NULL;
		freq[temp->c] = temp->f;
		insert(temp,H);
	}

	/* generate huffman tree */
	HuffTree root = GenerateHuffmanTree(H,n);

	/* encode and calulate the wpl*/
	wpl -= root->f;
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
