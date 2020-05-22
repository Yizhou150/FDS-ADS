#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* the struct of each node int the adjacency list*/
typedef struct AdjListNode {
	int vertex;
	struct AdjListNode* next;
} *AdjList;

/* the struct of binary heap used as a priority queue*/
typedef struct HeapStuct {
	int size,capacity;
	int *elements;
} *PriorityQueue;

/*
 * Description: This function is used to initialize the binary heap
 * Parameter[in] m  the number of vertices may be pushed in the heap
 * Parameter[in] H  the biranay heap without initialization
 * return H  the initialized heap
*/
PriorityQueue initialize_heap(int m,PriorityQueue H);


/*
 * Description: This function is used to insert a new element into the heap
 * Parameter[in] x  the vertex
 * Parameter[in] value[]  the value of vertices
 * Parameter[in] H  the biranay heap without initialization
*/
void insert(int x,int value[], PriorityQueue H);

/*
 * Description: This function is used delete the minimum value in the heap
 * Parameter[in] value[]  the value of vertices
 * Parameter[in] H  the biranay heap without initialization
*/
void delete(int value[],PriorityQueue H);


int main(void) {
	/*
 	* n  table size
 	* m  the number of the elements in the hash table
 	* value[]  the value of each elements
 	* hashkey[]  the hash key (value % tablesize) of each elements
 	* in_degree[]  the in-degree of each vertex
 	* list[]  the adjacent nodes list of each vertex
 	* input[] the answer array storing the input sequence
	*/
	int n,m,i,j,x;
	int value[1001],hashkey[1000],in_degree[1001],input[1001];
	AdjList temp;
	AdjList list[1001];
	PriorityQueue Heap;

	/* sequentially read in the hash table and store the elements in the table*/
	scanf("%d",&n);
	for (i = 0, j = 0; i < n; i++) {
		scanf("%d",&x);  /* read in the value whose key is i */
		if (x >= 0) {
			value[j] = x;  /* the value of this element is x */
			hashkey[j++] = i;  /* the key of this element is i */
		}
	}
	m = j;  /* the number of the elements */ 

	if (m==0) printf("The table is empty.\n");

	/* 
	 * build adjacency list
	 * regard each element as a vertex
	 * if vertex i was pushed in before vertex j, then add a directed edge from i to j
	*/

	/* initialize the in_degree and list of each vertex */
	for (i = 0; i < m; i++) {
		in_degree[i] = 0;
		list[i] = NULL;
	}
	/* build the list */
	for (i = 0; i < m; i++) {
		j = i;
		/* find all the elements between the key postion and the actual position */
		while (hashkey[j] != value[i] % n) {
			j--;
			if (j == -1) j = m-1;
			if (j==i) {
				printf("Error\n");
				exit(0);
			} /* the place where the elements should be is empty then output error */
			in_degree[i]++;  /* j should be pushed in before i so add the in_degree of i by 1 */
			/* build a directed edge from j to i */
			temp = (AdjList) malloc(sizeof(struct AdjListNode));
			if (temp == NULL) {
				printf("Out of space.");
				exit(0);
			}
			temp->vertex = i;
			temp->next = NULL;
			if (list[j] == NULL) list[j] = temp;  /* the case of the j's first edge */
			else {
				temp->next = list[j];  /* add in a new edge in j's list */
				list[j] = temp;
			}
		}
	}

	/* topological sorting
	 * a heap is implemented to find the minimum value to the vertex whose in_degree equals 0
	*/
	
	Heap = initialize_heap(m, Heap);

	/* insert all the vertex whose in_degree equals 0 into the heap first*/

	for (i = 0; i < m; i++)
		if (in_degree[i] == 0)
			insert(i, value, Heap);

	for (i = 0; i < m; i++) {
		if (Heap->size==0) {
			printf("Error\n");
			exit(0);
		} /* there exits loop in the graph then output error */
		input[i]=value[Heap->elements[1]];  /* put the minimum value of vertex whose in_degree equals 0 into answer array*/
		temp = list[Heap->elements[1]];
		delete(value, Heap);   /* delete this vertex from heap */
		while (temp != NULL) {  /* travers all the next adjacency vertex of this minimum vertex */
			in_degree[temp->vertex]--;  /* decrease their in_degree by 1 */
			if (in_degree[temp->vertex] == 0)  /* if its in_degree equals 0 then it can be print out*/
				insert(temp->vertex, value, Heap);
			temp = temp->next;
		}
	}
	for (i=0;i<m-1;i++) printf("%d ",input[i]);
	printf("%d",input[m-1]);

	return 0;
}

PriorityQueue initialize_heap(int m, PriorityQueue H) {
	H = (PriorityQueue) malloc(sizeof(struct HeapStuct));
	H->capacity = m+1;  /* the index should be from 1 to m */
	H->size = 0;  /* there is no element in the heap currently */
	H->elements = (int*) malloc(sizeof(int)*H->capacity);  /* allocate the memory for elements */
	if (H == NULL) {
		printf("Out of space.");
		exit(0);
	}
	H->elements[0]=-1;  /* put a negative integer at elements[0] as the minimum value */
	return H;
}

void insert(int x, int value[], PriorityQueue H){
	int i;
	H->size++;  /* expand the size of the heap */
	for (i = H->size; value[H->elements[i / 2]] > value[x]; i /= 2)  /* compare the value */
		H->elements[i] = H->elements[i / 2];  /* percolate up each vertex whose value is less than x's value */
	H->elements[i] = x;  /* place the new vertex */
}

void delete(int value[], PriorityQueue H) {
	int x,i,child;
	x = H->elements[H->size--];  /* shrink the size of the heap and put the last vertex on element[1] */
	for (i = 1; i * 2 <= H->size; i = child) {
		child = i*2;
		if (child + 1 <= H->size && value[H->elements[child + 1]] < value[H->elements[child]])
			child++;  /* pick the smaller children */
		if (value[H->elements[child]] < value[x])
			H->elements[i] = H->elements[child];  /* percolate down each child whose value is larger than x's value */
		else break;
	}
	H->elements[i] = x;  /* replace the last vertex */
}