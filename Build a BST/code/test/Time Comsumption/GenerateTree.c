#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>

typedef struct treenode {
	int Data,Number;
	struct treenode *Left,*Right;
} *Tree;

Tree root;

int infix[110];
int pseudolevel[110];  // a random sequence used to help built a random tree
int level[110];  // the level-order of the binary tree
int input[110];  // the random squenece of keys as the input of the test program
Tree Btree[110];  // the array of pointer pointing to the tree nodes and the index stands for its number

int N=0,M=1;

/*
 *Description：This procedure is to generate a binary search tree using the method of generating tree with infix-order and level-order
 *Parameter[in] il the left bound of infix-order in recursion
 *Parameter[in] ir the right bound of infix-order in recursion
 *Parameter[in] ll the left bound of pseudolevel-order in recursion
 *Parameter[in] ir the right bound of pseudolevel-order in recursion
 *return tree  the root of the generated tree in recursion
 */

Tree CreateBtree(int il,int ir,int ll,int lr) {
	Tree r;
	int i,j,key=0;
	if (il>ir) return NULL;
	/* the two loops are to find the current root which must be the first key value shown both in the infix-order and pseudolevel-order */
	for (i=ll;i<=lr;i++) {
		for (j=il;j<=ir;j++)
			if (pseudolevel[i]==infix[j]) {
				key=pseudolevel[i];
				break;
			}
		if (key!=0) break;
	};
	r=(Tree)malloc(sizeof(struct treenode));
	r->Data=key;  //key if the key of each nodes
	r->Number=N;  //N is the index of each nodes
	Btree[N++]=r; //store the nodes in the Btree array according to the number
	r->Left=CreateBtree(il,j-1,ll,lr); //recurs to create the left-child-tree
	r->Right=CreateBtree(j+1,ir,ll,lr); //recurs to creat the right-child-tree
	return r;
}

/*
 *Description：This procedure is to output the structure of the generated tree in the required form using as the input of our program
 *Parameter[in] n the number of nodes of the tree
 */

void OutputInputData(int n,int iterations) {
	int i,k,temp;
	printf("%d %d\n",n,iterations);

	for (i=0;i<n;i++) {
		if (Btree[i]->Left==NULL) printf("-1 ");  //if no left-child output -1
		else printf("%d ",Btree[i]->Left->Number);  //output the left-child's index
		if (Btree[i]->Right==NULL) printf("-1 ");  //if no right-childe output -1
		else printf("%d ",Btree[i]->Right->Number);  //output the right-child's index
		printf("\n");
	}

	/* this part uses shuffle algorithm to disorder the infix-order into a random sequence*/
	for (i=1;i<=n;i++) 
		input[i]=infix[i];
	for (i=n;i>=2;i--) {
		k=rand()%i+1;  // choose a radom element before the current element
		/* swap the two element */
		temp=input[i];
		input[i]=input[k];
		input[k]=temp;
	}
	/* this part is to output the random squence as the required input keys sequence */
	for (i=1;i<=n;i++) {
		printf("%d",input[i]); 
		if (i!=n) printf(" ");
		else printf("\n");
	}
}

int main(void) {
	freopen("input.in","r",stdin);  //read the user's input
	freopen("test.in","w",stdout);  //this is to write the output of this program into a file test.in

	int n,i,k,temp;
	int ITERATIONS,NUMBER_OF_NODES;;

	/* initialize */
	memset(infix,0,sizeof(infix));
	memset(pseudolevel,0,sizeof(pseudolevel));
	memset(level,0,sizeof(level));
	memset(input,0,sizeof(input));
	
	scanf("%d%d",&NUMBER_OF_NODES,&ITERATIONS);
	n=NUMBER_OF_NODES;  //choose the size of the tree
	srand((unsigned)time(NULL));
	/* randomly create an increasing squence as the infix-order of the binary tree*/
	for (i=1;i<=n;i++) 
		infix[i]=rand()%(1000-(n-i)-infix[i-1]-1)+infix[i-1]+1;
	/* shuffle the infix-order to generate a constraint */
	for (i=1;i<=n;i++) 
		pseudolevel[i]=infix[i];
	for (i=n;i>=2;i--) {
		k=rand()%i+1;
		temp=pseudolevel[i];
		pseudolevel[i]=pseudolevel[k];
		pseudolevel[k]=temp;
	}

	/* use the infix-order and the constraint to generate a binary search tree*/
	root=CreateBtree(1,n,1,n);

	OutputInputData(n,ITERATIONS);

	return 0;
}
