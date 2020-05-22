 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 
 struct node;
 typedef struct node* ptrtoNode;
 
 struct node{
  int element;
  ptrtoNode left;
  ptrtoNode right;
 };
 void completethetree(ptrtoNode tree,int* a,int N);
 /* After build the tree,use this function to assign the nodes with values*/ 
 void output(ptrtoNode tree, int N);
 /* This function is used to output the result in level order*/


 int main(void)
 {

  	freopen("test.in","r",stdin);
  	
 	int N;
 	int i,j,k,tmp;
 	int leftnode[110],rightnode[110],keys[110];
 	/*the leftnode and rightnode are the left child_index and right child_index*/
 	/*the keys is a array to store the integer keys*/
 	
 	clock_t start,stop;
 	int r;
 	int ITERATIONS;
 	scanf("%d%d",&N,&ITERATIONS);/* N nodes contained*/
 	for (i=0;i<N;i++) scanf("%d%d",&leftnode[i],&rightnode[i]);  	
	/* the input folowed the order of the tree array's index,so use one single*/
 	for(i=0;i<N;i++) scanf("%d",&keys[i]);	
	/*get the N interger keys*/
 	
 	start=clock();
 	for (r=1;r<=ITERATIONS;r++) {
 	
 	ptrtoNode tree = (ptrtoNode)malloc(sizeof(struct node)*N);
 	/* this pointer is an array of structs ,they are numbered from 0 to N-1,and the number is exactly its index*/
 	if(tree==NULL)
 	exit(0);
 	/* if malloc fails,quit*/
 	for(i=0;i<N;i++)
 	{
  		if(leftnode[i]==-1)
  		tree[i].left = NULL;
  		else
  		tree[i].left = &tree[leftnode[i]]; /* build the left child*/
  		
  		if(rightnode[i]==-1)
  		tree[i].right = NULL;
  		else
  		tree[i].right = &tree[rightnode[i]];/* build the right child*/
 	}
	/*'for' to traverse the tree array and build up the binary tree*/
 		
 	for(i=0;i<N-1;i++)
 	{
 		k=i;
 		for(j=i;j<N;j++)
 		{
 			if(keys[j]<keys[k])
			k=j;	
 		}
 		tmp=keys[i];
		keys[i]=keys[k];
		keys[k]=tmp;
 	}/*get the keys sorted,using an old algorithm called selectsort*/
 	completethetree(tree,keys,N);
 	output(tree, N);
 	
 	free(tree);
	}
 	stop=clock();
	printf("The time comsumption is %lf£¨nodes=%d ITERATIONS=%d£©",((double) (stop-start))/CLK_TCK,N,ITERATIONS);

 	return 0;
 }

void completethetree(ptrtoNode tree,int* a,int N)
{
  ptrtoNode* stack;
  ptrtoNode t;
  
  stack = (ptrtoNode*)malloc(sizeof(ptrtoNode)*N);
  if(stack==NULL)
  return;
  /* if empty,quit*/
  
  int top=-1;/* the top of stack,if top=-1,the stack is empty*/
  int i=0;
  t=tree;   /* tree equals to the address of the root*/
  while(t||top!=-1)/* the loop stops after the tree is all traversed and the stack is empty*/
  {
    while(t)
    {
      top++;
      stack[top]=t;   /* push in*/
      t=t->left;      /*in this loop,we find the far left node*/
    }
    if(top!=-1)
    {
      t=stack[top];     /* pop the node*/
      stack[top]=NULL;
      top--;
      t->element=a[i];  /*assign the poped node*/
      i++;
      t=t->right;
    }
  }
  free(stack);
}
/* for binary search tree,we can output the keys in order by InOrderTraversal*/
/* as we have built the tree,we can assign values to the nodes exactly in the same way*/
/* by just changing printing to assiging(the a is the sorted keys)*/

 void output(ptrtoNode tree, int N)
{
  ptrtoNode* queue;/* use queue to output in level order*/
  ptrtoNode t;

  queue=(ptrtoNode*)malloc(sizeof(ptrtoNode)*N);
  if(queue==NULL)
  return;
  /*if empty , quit*/
  int front,rear;/* the front and rear end of the queue*/
  int flag=0;
  front=0;rear=0;

  queue[0]=tree; /* enqueue the root first*/
  rear++;
  while(front!=rear)
  {
    t=queue[front];
    /* in the test form for convenience we don't print out the results*/ 
    //if(flag==0)
    //{
    //  printf("%d",queue[front]->element);
    //  flag=1;         /*if the first one,printf the single number*/
    //}
    //else
    //printf(" %d",queue[front]->element);/* else with a blank in front of the number */
    queue[front++]=NULL;    /*deque the from the front end*/
    if(t->left)
    queue[rear++]=t->left;
    if(t->right)
    queue[rear++]=t->right; /*if it has children,enque its left then right child*/
  }
  //printf("\n"); /*line break*/
  free(queue);
}
