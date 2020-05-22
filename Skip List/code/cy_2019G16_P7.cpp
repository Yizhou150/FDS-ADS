#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<cmath>

using namespace std;

const int Min = -2147483647;

/* the structure of each node in the skip list */
typedef struct skipListNode {
	skipListNode *next, *down;
	int value;
} *skipListNodePtr;  // the pointer of skip list node

/* the structure of the skip list */
typedef struct skipList {
	int level, upperlevel;
	skipListNodePtr top;
} *skipListPtr;  // the pointer of skip list

int randomLevel(int max) {
	int k = 1;
	/* initialize the seed */
	/* if the random number is 1 we get the level increased by 1 otherwise stop */
	while (rand() % 2) 
		k++;
	if (k > max)
		k = max;
	/* return k as the random generated level */
	return k;
}

/* create a null skip list */
skipListPtr createSkipList(int n) {
	skipListPtr s = new skipList;
	s->level = 0;  // initialize the level to be zero
	s->upperlevel = log(n*1.0) / log(2.0) + 1;
	/* create and initilize the top node */
	s->top = new skipListNode;
	s->top->next = NULL;
	s->top->down = NULL;
	s->top->value = -1;

	return s;  // return the new skip list
}

/* insert one element into the skip list */
skipListPtr insertElement(skipListPtr s,int x) {
	/* get a random level */
	int level = randomLevel(s->upperlevel);

 	/* create new nodes for each level */
	skipListNodePtr* newNodes = new skipListNodePtr[level];
	for (int i = level - 1; i >= 0; i--) {
		newNodes[i] = new skipListNode;
		newNodes[i]->value = x;
		newNodes[i]->next = NULL;
		newNodes[i]->down = (i == level-1) ? NULL : newNodes[i+1]; // link the nodes from high level to low level
	}

	skipListNodePtr currentNode = s->top;
	/* make the current node point to the first level to insert*/
	for (int i = 0; i < (s->level - level); i++) {
		currentNode = currentNode->down;  // move down
		while (currentNode->next != NULL && currentNode->next->value < x) 
				currentNode = currentNode->next; // move backwards
	}

	/* insert the new nodes into each level */
	for (int i = 0; i < level; i++) {
		if (i < level - s->level) {
			/* create the new level and insert the new nodes */
			skipListNodePtr headNode = new skipListNode;
			headNode->value = Min;
			headNode->next = newNodes[i]; // insert the new nodes
			headNode->down = currentNode->down;
			currentNode->down = headNode;
			currentNode = headNode;
		}
		else {
			/* insert node to the existed levels */
			currentNode = currentNode->down; // move down by 1 level
		//	cout<<currentNode->value<<"# ";
			while (currentNode->next != NULL && currentNode->next->value < x) {
				//cout<<"!";
				currentNode = currentNode->next; // move backwards
			}
			/* insert the new node into current level */
			newNodes[i]->next = currentNode->next;
			currentNode->next = newNodes[i];
		}
	}
	/* update the level of the skiplist */
	if (level > s->level)
		s->level = level;
		
	return s;
}

/* insert one element into the skip list */
skipListPtr deleteElement(skipListPtr s, int x) {
	/* headNode point to the first node in each line 
	   currentNode points to the current node we search to */
	skipListNodePtr headNode, currentNode;
	headNode = currentNode = s->top->down;
	while (currentNode != NULL) {
		while (currentNode->next != NULL && currentNode->next->value < x)
			currentNode = currentNode->next; // move backwards
		/* if the node to delete in this level */
		if (currentNode->next != NULL && currentNode->next->value == x) {
			/* delete the node */
			skipListNodePtr temp = currentNode->next;
			currentNode->next = currentNode->next->next;
			delete temp;
		}
		/* if the current level become empty */
		if (headNode->next == NULL) {
			/* remove this level */
			skipListNodePtr temp = headNode;
			s->top->down = headNode->down;
			headNode = headNode->down;
			/* delete the head node */
			delete temp;
			s->level--;
		}
		else
			headNode = headNode->down;  // move down

		currentNode = currentNode->down; // move down
	}

	return s;
}

/* find element in the skip list 
   if find return true else return false */
bool findElement(skipListPtr s, int x) {
	skipListNodePtr currentNode = s->top->down;
	while (currentNode != NULL) {
		while (currentNode->next != NULL && currentNode->next->value < x)
			currentNode = currentNode->next;  // move backwards
		if (currentNode->next != NULL && currentNode->next->value == x) 
			return true;  // find
		currentNode = currentNode->down;  // move down by 1 level
	}
	return false;  // didn't find through the whole skip list
}

/* print out the skip list*/
void printSkipList(skipListPtr s) {
	skipListNodePtr head,k;
	head = s->top->down;
	/* if the list is empty */
	if (head == NULL) 
		cout<<"emtpy"<<endl;
	/* print the skip list by row */
	while (head != NULL) {
		k = head;
		/* print the row */
		while (k != NULL) {
			cout<<k->value<<" ";
			k = k->next;
		}
		head = head->down;  // move down
		cout<<endl;
	}
}

int main(void) {
	int n,m,x;

	freopen("data.in","r",stdin);

	clock_t start,stop;
	srand((unsigned)time(NULL));

	cin>>n;  // the size of the test case

	/* create an empty skip list */
	skipListPtr s = createSkipList(n);
	
	/* generate a skip list of size n */
	for (int i = 0; i < n; i++) {
		cin>>x;
		insertElement(s,x);
		//cout<<"insert :  "<<x<<" "<<endl;
		//printSkipList(s);
	}
	/* test operation time */
	cin>>m;  // number of test cases
	double insert_time = 0, find_time = 0, delete_time = 0;
	
	for (int i = 0; i < m; i++) {
		/* test the insert function */
		cin>>x;
		start = clock();
		insertElement(s,x);
		//cout<<"insert : "<<endl;
		//printSkipList(s);
		stop = clock();
		insert_time += double(stop - start)/CLOCKS_PER_SEC;

		/* test the find function */
		cin>>x;
		start = clock();
		bool b = findElement(s,x);
		//cout<<"Find "<<x<<" is "<<b<<endl;
		stop = clock();
		find_time += double(stop - start)/CLOCKS_PER_SEC;

		/* test the delete function */
		cin>>x;
		start = clock();
		deleteElement(s,x);
		//cout<<"Delete :  "<<x<<" "<<endl;
		//printSkipList(s);
		stop = clock();
		delete_time += double(stop - start)/CLOCKS_PER_SEC;
	}

	/* output the test result */
	cout<<"total time: "<<insert_time<<" "<<find_time<<" "<<delete_time<<endl;
	cout<<"time per operation: "<<insert_time/m<<" "<<find_time/m<<" "<<delete_time/m<<endl;
	
	system("pause");

	return 0;
}
