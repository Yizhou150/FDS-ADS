#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define maxn 10000 
void Hashing(int RandomArray[],int num,int TableSize);

	int main(){
		freopen("HashInput.out","r",stdin); 
		freopen("HashResult_2.out","w",stdout); 
		int num,TableSize;
		int i;
		int *HardVersionArray;
		scanf("%d",&num);
		scanf("%d",&TableSize);
   		HardVersionArray=(int*)malloc(sizeof(int)*num);
		for(i=0;i<num;i++) scanf("%d",&HardVersionArray[i]);
		/*after generating the random array, we use hashing to sort the array*/
		printf("%d\n",TableSize);
		Hashing(HardVersionArray,num,TableSize);
		return 0;
	}
	
void Hashing(int HardVersionArray[],int num,int TableSize){	
		int i,j;
		int *Hash,key;
   		Hash = (int *) malloc(sizeof(int)*TableSize);
   		
   		for(i=0;i<TableSize;i++){
   			Hash[i]=-1;   //先置所有为-1 
   		}
   		
		for(i=0;i<num;i++){   //hashing
				key=HardVersionArray[i];
				for(j=0;j<TableSize;j++){	//linear probing 
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

