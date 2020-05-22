#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<stdio.h>
#include<time.h>

using namespace std;
clock_t start, stop;
double duration;

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


/* the compare function */
bool cmpQ(HuffNodePtr x,HuffNodePtr y) {
	return x->f < y->f;  // increasing order
}

bool cmpS(string x,string y) {
	return x.length()<y.length();
}

long long wpl = 0;

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

void insert(HuffNodePtr x, Heap H){
	int i;
	H->size++;  /* expand the size of the heap */
	for (i = H->size; (H->Elements[i / 2])->f > x->f; i /= 2)  /* compare the value */
		H->Elements[i] = H->Elements[i / 2];  /* percolate up each vertex whose value is less than x's value */
	H->Elements[i] = x;  /* place the new vertex */
}

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


HuffTree GenerateHuffmanTree(Heap H, int n) {
	HuffNodePtr temp;
	int ite = H->size-1;
	for (int i = 0; i < ite; i++) {
		HuffNodePtr x = H->Elements[1];
		deleteMin(H);
		HuffNodePtr y = H->Elements[1];
		deleteMin(H);
		temp = new HuffNode;
		temp->f = x->f + y->f;
		temp->Left = x;
		temp->Right = y;
		insert(temp,H);
	}
	
	return H->Elements[1];
}


int main(void) {
	int n,m;
	int iter=1000;
	freopen("input.in","r",stdin);
	cin>>n;  // number of nodes

		
	map<char,int> freq;

	/* input and initialize */
	Heap* H;
	H= new Heap[iter];
	for (int i=0;i<iter;i++)
		H[i] = initialize_heap(n,H[i]);
	HuffNodePtr temp;
	
	
	for (int i = 0; i < n; i++) {
		temp = new HuffNode;
		cin >> temp->c >> temp->f;
		temp->Left = temp->Right = NULL;
		freq[temp->c] = temp->f;
		for(int j=0;j<iter;j++)
			insert(temp,H[j]);
	}
	
	
	/* generate huffman tree */
	start = clock();
	for(int i=0;i<iter;i++)
		HuffTree root = GenerateHuffmanTree(H[i],n);
	stop = clock();
	duration = ((double)(stop - start) / CLK_TCK/iter) ;
	printf("%f", duration);
	

	return 0;
}
