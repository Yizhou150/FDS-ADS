#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define maxn 10000 

void Hashing(int RandomArray[],int num,int TableSize);

	int main(){
		freopen("input.in","r",stdin); 
		freopen("HashResult_1.out","w",stdout); 
		int num,TableSize;
		int *RandomArray;
		int *a;
		scanf("%d",&num);
		scanf("%d",&TableSize);
		int n,i,k,temp;
		n=num;  // choose the number of digits 
		srand((unsigned)time(NULL));
		/* randomly create an increasing squence*/
		RandomArray = (int*) malloc(sizeof(int)*(num+1));
		a = (int*) malloc(sizeof(int)*(num+1));
	
		for (i=0;i<n;i++)    
			a[i]=rand()%(maxn*(i+1)/n);  //generate the random array
		
		/* shuffle the random array to generate a constraint */
		for (i=0;i<n;i++) 
			RandomArray[i]=a[i];
		for (i=n-1;i>=1;i--) {   //´òÂÒ 
			k=rand()%i+1;
			temp=RandomArray[i];
			RandomArray[i]=RandomArray[k];
			RandomArray[k]=temp;
		} 
		/*after generating the random array, we use hashing to sort the array*/
		printf("%d\n",TableSize);
		Hashing(RandomArray,num,TableSize);
		return 0;	
	}
	
void Hashing(int RandomArray[],int num,int TableSize){	
		int i,j;
		int *Hash,key;
   		Hash = (int *) malloc(sizeof(int)*TableSize);
   		
   		for(i=0;i<TableSize;i++){
   			Hash[i]=-1;   //Set all value in the hash table as -1 
   		}
   		
		for(i=0;i<num;i++){   //hashing
				key=RandomArray[i];
				for(j=0;j<TableSize;j++){	//put the data into hash table and linear probing 
					if(Hash[(key+j)%TableSize]==-1){
						Hash[(key+j)%TableSize]=key;
						break;
					}	
				}
			}
			
		for(i=0;i<TableSize;i++){
			if(i==TableSize-1) printf("%d",Hash[i]);
			else printf("%d ",Hash[i]);
		}	
			
}

