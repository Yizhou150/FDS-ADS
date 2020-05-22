#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

/* three alogrithm of different time complexity*/

/*
 *Description£ºThis procedure is used to find the maximum sub-matrix within O(n^6)
 *Parameter[in] a  the pointer array of the initial matrix
 *Parameter[in] n  the size of the square matrix
 *return maximum  the maximal sum of sub-matrix
 */
long int GetMaxInOn6(int (*a)[102],int n);

/*
 *Description£ºThis procedure is used to find the maximum sub-matrix within O(n^4)
 *Parameter[in] a  the pointer array of the initial matrix
 *Parameter[in] n  the size of the square matrix
 *return maximum  the maximal sum of sub-matrix
 */
long int GetMaxInOn4(int (*a)[102],int n);

/*
 *Description£ºThis procedure is used to find the maximum sub-matrix within O(n^3)
 *Parameter[in] a  the pointer array of the initial matrix
 *Parameter[in] n  the size of the square matrix
 *return maximum  the maximal sum of sub-matrix
 */
long int GetMaxInOn3(int (*a)[102],int n);

/* testing function */

/*
 *Description: This procedure is used to test the time of each algorithm
 *Parameter[in] a  the pointer array of the initial matrix
 *Parameter[in] Algorithm  the pointer of the test algorithm
 *Parameter[in] n  the size of the square matrix
 *Parameter[in] k  the run times of the algorithm for testing
 *output stop-start the total ticks
 *output duration  algorithm comsuption time  
*/
void TestTime(int (*a)[102],long int (*Algorithm)(int(*)[102],int),int n,int k);


int main(){
    
    int n,m,k,i,j;
    int a[102][102];
    
    /* n stands for the size of matrix
	 * m stands for the test algorithm 1/2/3
	 * k stands for the iteration */
    scanf("%d %d %d",&n,&m,&k);  
    
    /* generate a random matrix for testing*/
    srand((unsigned)time(NULL));
    for (i=0;i<=n;i++) 
    	for (j=0;j<=n;j++) a[i][j]=0;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++) a[i][j]=rand()-16383;    //make sure there the range is [-16363,16384]
    
    /* test each algorithm */
    if (m==1) TestTime(a,GetMaxInOn6,n,k);
    if (m==2) TestTime(a,GetMaxInOn4,n,k);
    if (m==3) TestTime(a,GetMaxInOn3,n,k);
    system("pause");
    return 0;
}

void TestTime(int (*a)[102],long int (*Algorithm)(int(*)[102],int),int n,int k) {
    clock_t start,stop;
    double TotalTime;
    int i;
    long int ans;
    start=clock();  //start time
    for(i=1;i<=k;i++) ans=(*Algorithm)(a,n);
    stop=clock();   //stop time
    
    printf("%ld\n",stop-start);
    TotalTime=((double)(stop-start))/CLK_TCK;
    printf("%lf\n",TotalTime);
}

long int GetMaxInOn6(int (*a)[102],int n) {
    int i1,i2,i3,j1,j2,j3;
    long int ThisSum,MaxSum=0;
    
    ThisSum=0;
    for(i1=1;i1<=n;i1++)
        for(j1=1;j1<=n;j1++)  //enumerate the upper-left corners (i1,j1)
            for(i2=i1;i2<=n;i2++)
                for(j2=j1;j2<=n;j2++) {  //enumerate the lower-right corners (i2,j2)
                    ThisSum=0;
                    for(i3=i1;i3<=i2;i3++)
                        for(j3=j1;j3<=j2;j3++) ThisSum=ThisSum+a[i3][j3]; //traverse the sub-matrix to get the sum
                    if(ThisSum>MaxSum) MaxSum=ThisSum;
                    
                }
    return MaxSum;
}

long int GetMaxInOn4(int (*a)[102],int n) {
    int i,j,i1,j1,i2,j2;
    long int Sum,MaxSum;
    long int PreSum[102][102];
    
    MaxSum=0;
    
    /* initialize the prefix sum matrix */
    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            PreSum[i][j]=0;
    
    /* calculate the prefix sum matrix */
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            PreSum[i][j]=PreSum[i-1][j]+PreSum[i][j-1]-PreSum[i-1][j-1]+a[i][j];
    
    /* find the maximum */
    for(i1=1;i1<=n;i1++)
        for(j1=1;j1<=n;j1++) //enumerate the upper-left corners (i1,j1)
            for(i2=i1;i2<=n;i2++)
                for(j2=j1;j2<=n;j2++){  //enumerate the lower-right corners (i2,j2)
                    Sum=PreSum[i2][j2]-PreSum[i1-1][j2]-PreSum[i2][j1-1]+PreSum[i1-1][j1-1];  //calculate the sum
                    if(Sum>MaxSum) MaxSum=Sum;
                }
    return MaxSum;
}

long int GetMaxInOn3(int (*a)[102],int n) {
    int i,j,iu,il;
    long int Sum,MaxSum;
    long int PreSum[102][102];
    
    /* initialize the prefix sum matrix */
    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            PreSum[i][j]=0;
    
    /* calculate the prefix sum matrix */
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            PreSum[i][j]=PreSum[i-1][j]+PreSum[i][j-1]-PreSum[i-1][j-1]+a[i][j];
    
    MaxSum=0;
    for (iu=1;iu<=n;iu++) //enumerate the upper-bounds
        for (il=iu;il<=n;il++) { //enumerate the lower-bounds
            Sum=0;
            /* dynamic prgramming */
            for (j=1;j<=n;j++) {
                if (Sum<0) Sum=0;  // DP equation: sum[j]=max{sum[j-1],0}+element[j]
                Sum+=PreSum[il][j]-PreSum[il][j-1]-PreSum[iu-1][j]+PreSum[iu-1][j-1];
                if (Sum>MaxSum) MaxSum=Sum;
            }
        }
    return MaxSum;
}
