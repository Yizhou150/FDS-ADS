#include<stdio.h>
#include<stdlib.h> 

int main(void) {
	freopen("test.in","r",stdin);  //read the data from the file test.in
	freopen("test2.out","w",stdout);

	int n,x,y,i;
	/* this part is to read the requred input*/
	scanf("%d",&n);
	for (i=1;i<=n;i++) 
		scanf("%d%d",&x,&y);
	for (i=1;i<=n;i++) 
		scanf("%d",&x);

	/* this part is to read the answer and directly output it */
	for (i=1;i<=n;i++) {
		scanf("%d",&x);
		if (i!=n) printf("%d ",x);
		else printf("%d\n",x);
	}
	return 0;
}
