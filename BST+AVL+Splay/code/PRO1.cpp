#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

/* the basic structure of the three tree*/
typedef struct TreeNode *Tree;
struct TreeNode {
	int Element,Height;
	Tree Left,Right,Parent;
};

int n; // the size of the data
int *a,*b,*RandomArray1,*RandomArray2; // the arrays to store sequence of input data

/* Splay */

/* T's father P is the root and T is P's left child */
Tree LeftRotation(Tree T) {
	Tree P = T->Left; 
	P->Parent = T->Parent;
	T->Left = P->Right;
	if (P->Right!=NULL)
		P->Right->Parent = T;
	P->Right = T;
	T->Parent =P;
	T = P;
	return T;
}

/* T's father P is the root and T is P's right child */
Tree RightRotation(Tree T) {
	Tree P = T->Right;
	P->Parent = T->Parent;
	T->Right = P->Left;
	if (P->Left!=NULL) 
		P->Left->Parent = T;
	P->Left = T;
	T->Parent = P;
	T = P;
	return T;
}

/* T has a grandpa and the LR zig-zag case */
Tree LeftRightZigZagRotation(Tree T) {
	T->Left = RightRotation(T->Left);
	T = LeftRotation(T);
	return T;
}

/* T has a grandpa and the RL zig-zag case */
Tree RightLeftZigZagRotation(Tree T) {
	T->Right = LeftRotation(T->Right);
	T = RightRotation(T);
	return T;
}

/* T has a grandpa and the LL zig-zig case */
Tree LeftZigZigRotation(Tree T) {
	T = LeftRotation(T);
	T = LeftRotation(T);
	return T;
}

/* T has a grandpa and the RR zig-zig case */
Tree RightZigZigRotation(Tree T) {
	T = RightRotation(T);
	T = RightRotation(T);
	return T;
}

/*
 * Description: This function is used to implement splay operation.
 * Parameter[in] T  the element to splay up to the root
 * return T after splay as the new root of the tree
 */
Tree Splay(Tree T) {
	/* 
	 * P father of T
	 * G grandfather of T if exist
	 * PG great-grandfather of T is exist
	 */
	Tree P,G,PG;
	while (T->Parent!=NULL) { // until T is the root
		P = T->Parent;
		if (P->Parent == NULL) { // if T has no grandfather
			if (T == P->Left) T = LeftRotation(P);
			else T = RightRotation(P);
		}
		else {
			G = P->Parent;
			if (P == G->Left) { 
				if (T == P->Left) T = LeftZigZigRotation(G); // LL zig-zig case
				else T = LeftRightZigZagRotation(G); // LR zig-zag case
			}
			else {
				if (T == P->Left) T = RightLeftZigZagRotation(G); // RL zig-zag case
				else T = RightZigZigRotation(G); // RR zig-zig case
			}
			/* link the new T to the initial tree */
			PG = T->Parent;
			if (PG!=NULL) {
				if (PG->Left == G) PG->Left = T;
				else PG->Right = T;
			}
		}
	}
	return T;
}

/*
 * Description: This function is used to implement insertion.
 * Parameter[in] T  the root of the the tree
 * Parameter[in] x  the element to be inserted
 */
void SplayInsert(Tree &R,int x) {
	Tree T,P,G;

	/* build a new node*/
	T = new TreeNode;
	T->Element = x;
	T->Parent = T->Left = T->Right = NULL;

	/* if the tree is empty */
	if (R==NULL) R = T;
	else {
		/* find the place for the new node*/
		P = R;
		while (P != NULL) {
			G = P;
			if (T->Element < P->Element) 
				P = P->Left;
			else P = P->Right;
		}
		/* insert the new node */
		if (T->Element < G->Element) 
			G->Left = T;
		else if (T->Element > G->Element)
			G->Right = T;
		T->Parent = G;
		/* splay the new node to root */
		R = Splay(T);
	}
}

/*
 * Description: This function is used to implement deletion.
 * Parameter[in] T  the root of the tree
 * Parameter[in] X  the element to be deleted
 */
void SplayDelete(Tree &R,int x) {
	Tree P,TL,TR;
	/* if there is no node left in the tree*/
	if (R == NULL) return;

	/* otherwise find the node to delete */
	P = R;
	while (P != NULL) {
		if (x < P->Element)
			P = P->Left;
		else if (x > P->Element)
			P = P->Right;
		else break;
	}
	/* splay the node to the root*/
	if (P != R)
		R = Splay(P);

	/* record the right and left tree of the root */
	TL = R->Left;
	TR = R->Right;
	/* romove the root */
	delete R;

	/* if there is a left tree then adjust the Left Tree */
	if (TL != NULL) {
		/* break the link between the left child and the deleted root */
		TL->Parent = NULL;
		/* find the largest element in the left tree */
		P = TL;
		while (P->Right != NULL)
			P=P->Right;
		/* splay the maximum to the root */
		if (P!=TL)
			R = Splay(P);
		else R = P;
		/* link the new root and the right tree */
		R->Right = TR;
		if (TR != NULL)
			TR->Parent = R;
	}
	/* if the root has no left tree the make its right son the new root */
	else if (TR != NULL) {
		TR->Parent = NULL;
		R = TR;
	}
	/* if the root has no child then the tree will be empty */
	else R = NULL;
}

/* AVL */

/*
 * Description: This function is used to find the larger one between two numbers
 */
int Max(int a, int b) {
	if (a > b)return a;
	else return b;
}

/*
 * Description: This function is used to get the Height of one node.	
 */
int GetHeight(Tree T) {
	if (!T)
		return -1;/* Define the height of empty nodes as -1 */
	else 
		return T->Height; 
}

/*
 * Description: This function is used to implement the single left rotation.
 */
Tree AVL_LL_Rotation(Tree A) {
	Tree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;//Update the height of the affected nodes 
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;
	return B;
}

/*
 * Description: This function is used to implement the single right rotation.
 */
Tree AVL_RR_Rotation(Tree A) {
	Tree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;//Update the height of the affected nodes
	B->Height = Max(GetHeight(B->Right), A->Height) + 1;
	return B;
}

/*
 * Description: This function is used to implement the double single right rotation.
 */
Tree AVL_LR_Rotation(Tree A) {
	Tree B = A->Left;
	Tree C = B->Right;
	B->Right = C->Left;
	C->Left = B;
	A->Left = C->Right;
	C->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;//Update the height of the affected nodes
	B->Height = Max(GetHeight(B->Left), GetHeight(B->Right)) + 1;
	C->Height = Max(GetHeight(C->Left), GetHeight(C->Right)) + 1;
	return C;
}

/*
 * Description: This function is used to implement the double right single rotation.
 */
Tree AVL_RL_Rotation(Tree A) {
	Tree B = A->Right;
	Tree C = B->Left;
	B->Left = C->Right;
	C->Right = B;
	A->Right = C->Left;
	C->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;//Update the height of the affected nodes
	B->Height = Max(GetHeight(B->Left), GetHeight(B->Right)) + 1;
	C->Height = Max(GetHeight(C->Left), GetHeight(C->Right)) + 1;
	return C;
}

/*
 * Description: This function is used to implement insertion.
 * Parameter[in] T  the root of the sub-tree to insert the new element
 * Parameter[in] X  the element to be inserted
 * return T  the new sub-tree after insertion
 */
Tree AVLInsert(Tree T, int X) {
	if (!T) {// If X have reach the right position, Create a new node.
		T = (Tree)malloc(sizeof(struct TreeNode));
		T->Element = X;
		T->Height = 0;//Set the height as 0, for it's a leaf node.
		T->Left = T->Right = NULL;
	}
	else if (X < T->Element) {
		T->Left = AVLInsert(T->Left, X);
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2) {// If X have been inserted, check the balance factor of current node
			if (X < T->Left->Element)// Judge LL or LR
				T = AVL_LL_Rotation(T);
			else
				T = AVL_LR_Rotation(T);
		}
	}
	else if (X > T->Element) {
		T->Right = AVLInsert(T->Right, X);
		if (GetHeight(T->Left) - GetHeight(T->Right) == -2) {// If X have been inserted, check the balance factor of current node
			if (X > T->Right->Element)// Judge RR or RL
				T =AVL_RR_Rotation(T);
			else
				T = AVL_RL_Rotation(T);
		}
	}
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;//Update the height of current node
	return T;
}

/*
 * Description: This function is used to find the minimum number of current node's right subtree.
 */
Tree FindMin(Tree T) {
	if (!T)return NULL;
	else if (!T->Left)return T;
	else return FindMin(T->Left);
}

/*
 * Description: This function is used to implement deletion.
 * Parameter[in] T  the root of the sub-tree to delete the new element
 * Parameter[in] X  the element to be deleted
 * return T  the new sub-tree after deletion
 */
Tree AVLDelete(Tree T, int X) {
	Tree Temp;
	if (!T)return NULL;
	else {
		if (X < T->Element)// If X is less than current element, turn to the left subtree. 
			T->Left = AVLDelete(T->Left, X);
		else if (X > T->Element)// If X is greater than current element, turn to the right subtree. 
			T->Right = AVLDelete(T->Right, X);
		else {
			if (T->Left&&T->Right) {// If the element deleted have both left and right subtrees, adjust the structure.
				Temp = FindMin(T->Right);// Find the minimum node of the right subtree 
				T->Element = Temp->Element;// Replace the current node.
				T->Right = AVLDelete(T->Right, T->Element);
			}
			else {//If the element deleted have one left or right subtrees, directly connect left or right subtree.
				Temp = T;
				if (!T->Left)T = T->Right;
				else T = T->Left;
				free(Temp);
			}
		}
		if (!T)return NULL;// If one leaf node is deleted, return NULL.

		T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1; // Update the height of the affected nodes

		if (GetHeight(T->Left) - GetHeight(T->Right) == 2) { // If X have been inserted, check the balance factor of current node
			if (X < T->Left->Element)// Judge LL or LR
				T = AVL_LL_Rotation(T);
			else
				T = AVL_LR_Rotation(T);
		}
		if (GetHeight(T->Left) - GetHeight(T->Right) == -2) { // If X have been inserted, check the balance factor of current node
			if (X > T->Right->Element)// Judge RR or RL
				T = AVL_RR_Rotation(T);
			else
				T = AVL_RL_Rotation(T);
		}
	}
	return T;
}

/* BST */

/*
 * Description: This function is used to implement insertion.
 * Parameter[in] T  the root of the sub-tree to insert the new element
 * Parameter[in] X  the element to be inserted
 * return T  the new sub-tree after insertion
 */
Tree BSTInsert(Tree T, int X) {
	if (!T) { // If X have reach the right position, Create a new node.
		T = new TreeNode;
		T->Element = X;
		T->Height = 0; //Set the height as 0, for it's a leaf node.
		T->Left = T->Right = NULL;
	}
	else {
		if (X < T->Element) // If X is less than current element, turn to the left subtree. 
			T->Left = BSTInsert(T->Left, X);
		else if (X > T->Element) // If X is greater than current element, turn to the right subtree. 
			T->Right = BSTInsert(T->Right, X);
	}
	return T;
}

/*
 * Description: This function is used to implement deletion.
 */
Tree BSTDelete(Tree T, int X) {
	Tree Temp;
	if (!T)return NULL;
	else {
		if (X < T->Element) // If X is less than current element, turn to the left subtree. 
			T->Left = BSTDelete(T->Left, X);
		else if (X > T->Element) // If X is greater than current element, turn to the right subtree. 
			T->Right = BSTDelete(T->Right, X);
		else {
			if (T->Left&&T->Right) { // If the element deleted have both left and right subtrees, adjust the structure.
				Temp = FindMin(T->Right); // Find the minimum node of the right subtree 
				T->Element = Temp->Element; //Replace the current element
				T->Right = BSTDelete(T->Right, T->Element);
			}
			else { //If the element deleted have one left or right subtrees, directly connect left or right subtree.
				Temp = T;
				if (!T->Left)T = T->Right;
				else T = T->Left;
				delete Temp;
			}
		}
	}
	return T;
}


/* create input */

void CreateArray(){
		int i,k,temp;
		srand((unsigned)time(NULL));
		/* randomly create an increasing squence*/
		RandomArray1 = new int[n+1];
		RandomArray2 = new int[n+1];
		a = new int[n+1];  //increasing
		b = new int[n+1];  //reverse
		
		a[0]=2; 
		for (i=1;i<n;i++)   //generate the random increasing array
			a[i]=a[i-1]+rand()%8+1;  
		
		for (i=0;i<n;i++){
			b[i]=a[n-i-1];
		} 
		
		/* shuffle the random array to generate a constraint */
		for (i=0;i<n;i++) 
			RandomArray1[i]=a[i];
		for (i=n-1;i>=1;i--) {   //Disrupt the order for insert
			k=rand()%i;
			temp=RandomArray1[i];
			RandomArray1[i]=RandomArray1[k];
			RandomArray1[k]=temp;
		} 
		for (i=0;i<n;i++) 
			RandomArray2[i]=a[i];
		for (i=n-1;i>=1;i--) {   //Disrupt the order for insert
			k=rand()%i;
			temp=RandomArray2[i];
			RandomArray2[i]=RandomArray2[k];
			RandomArray2[k]=temp;
		} 
}

/* time-testing part*/
 
/* test part for splay */
void SplayTree(int *Array1,int *Array2){  // Array1 and Array2 is the insertion array and deletion array 
	cout<<"SplayTree:"<<endl;
	int i;
	Tree SplayT = NULL;
	clock_t startins,endins,startdel,enddel;   // timing part
	double durationins=0,durationdel=0;

	for (int ite=0;ite<100;ite++) {
		startins=clock();  //start timing for inserting
		for (i=0;i<n;i++) { 
			SplayInsert(SplayT,Array1[i]);  //insert the tree node
		}
		endins=clock();  //end timing for inserting
		durationins+=double(endins-startins)/CLOCKS_PER_SEC;
		
		startdel=clock();  //start timing for deleting
		for (i=0;i<n;i++) {
			SplayDelete(SplayT,Array2[i]);  //delete the tree node
		}
		enddel=clock();  //end timing for deleting
		durationdel+=double(enddel-startdel)/CLOCKS_PER_SEC;  //get the time interval in seconds 
	}
	cout<<"InsertTime: "<<setprecision(10)<<durationins/100<<"s"<<endl;
	cout<<"DeleteTime: "<<setprecision(10)<<durationdel/100<<"s"<<endl;
}


/* test part for splay */
void AVLTree(int *Array1,int *Array2){  // Array1 and Array2 is the insertion array and deletion array 
	cout<<"AVLTree:"<<endl;
	Tree AVLT=NULL;
	clock_t startins,endins,startdel,enddel; // timing part
	double durationins=0,durationdel=0;
	
	for (int ite=0;ite<100;ite++) {
		startins=clock();  //start timing for inserting
		for(int i=0;i<n;i++){
			AVLInsert(AVLT,Array1[i]);  //insert the tree node
		} 
		endins=clock();  //end timing for inserting
		durationins+=double(endins-startins)/CLOCKS_PER_SEC;

		startdel=clock();  //start timing for deleting
		for(int i=0;i<n;i++){
			AVLDelete(AVLT,Array2[i]);
		} 
		enddel=clock();  //end timing for deleting
		durationdel+=double(enddel-startdel)/CLOCKS_PER_SEC;
	}
	cout<<"InsertTime: "<<setprecision(10)<<durationins/100<<"s"<<endl;
	cout<<"DeleteTime: "<<setprecision(10)<<durationdel/100<<"s"<<endl;
}


/* test part for BST */
void BSTree(int *Array1,int *Array2){  // Array1 and Array2 is the insertion array and deletion array 
	cout<<"BSTree:"<<endl;
	Tree BST=NULL;
	clock_t startins,endins,startdel,enddel; // timing part
	double durationins=0,durationdel=0;
	
	for (int ite=0;ite<100;ite++) {
		startins=clock();  //start timing for inserting
		for(int i=0;i<n;i++){
			BSTInsert(BST,Array1[i]);
		} 
		endins=clock();  //end timing for inserting
		durationins+=double(endins-startins)/CLOCKS_PER_SEC;
	
		startdel=clock();  //start timing for deleting
		for(int i=0;i<n;i++){
			BSTDelete(BST,Array2[i]);
		} 
		enddel=clock();  //end timing for deleting
		durationdel+=double(enddel-startdel)/CLOCKS_PER_SEC;
	}
	cout<<"InsertTime: "<<setprecision(10)<<durationins/100<<"s"<<endl;
	cout<<"DeleteTime: "<<setprecision(10)<<durationdel/100<<"s"<<endl;
}

/* time test */
void TestTime(){
		cout<<"increasing insertion & increasing deletion"<<endl;  // get the time consumption in the situation with increasing order insertion and increasing order deletion
		BSTree(a,a);
		AVLTree(a,a);
		SplayTree(a,a); 
		cout<<endl;
		
		cout<<"increasing insertion & decreasing deletion"<<endl;  // get the time consumption in the situation with increasing order insertion and reversing order deletion
		BSTree(a,b);
		AVLTree(a,b);
		SplayTree(a,b); 
		cout<<endl;

		cout<<"random insertion & random deletion"<<endl;  // get the time consumption in the situation with random order insertion and random order deletion
		BSTree(RandomArray1,RandomArray2);
		AVLTree(RandomArray1,RandomArray2);
		SplayTree(RandomArray1,RandomArray2); 
		cout<<endl;
}		

int main(){
	int flag;
	cout<<"Please input the size of the tree:"<<endl;
	cin>>n;  //input the nodes of the tree
	CreateArray();  //create three kinds of arrays
	TestTime();  //timing function
	system("pause"); 
	return 0;
}
