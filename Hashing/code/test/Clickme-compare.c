#include<stdio.h>
#include<stdlib.h>

#define TEST_TIMES 1000 

int main(void) {
	int i,tmp=0;
	for (i=1;i<=TEST_TIMES;i++) {
		system("1-GenerateRandomHashResult");
		system("2-GenerateNewHashInput");
		system("3-GenerateNewHashResult");

		if (system("fc HashResult_1.out HashResult_2.out")) {
			printf("wrong in --> %d",i);
			system("pause"); 
			return 0;
		}
	}
	printf("success\n");
	system("pause");
	return 0;
}
