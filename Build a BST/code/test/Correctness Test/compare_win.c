#include<stdio.h>
#include<stdlib.h>

int main(void) {
	int i,nodes,TEST_TIMES;
	freopen("input.in","r",stdin);
	scanf("%d%d",&nodes,&TEST_TIMES);
	/* test for TEST_TIMES times*/
	for (i=1;i<=TEST_TIMES;i++) {
		/*run the three executable fils*/
		system("GenerateTree");
		system("testfile");
		system("answer");
		/* compare the output of our program and the answer*/
		if (system("fc test1.out test2.out")) {
			printf("wrong in --> %d",i); // if they are different output "wrong"
			system("pause"); 
			return 0;
		}
	}
	printf("success\n"); // if the program passed all the test output "success"
	system("pause");
	return 0;
}
