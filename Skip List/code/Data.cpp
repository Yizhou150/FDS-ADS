#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main(void) {

	freopen("data.in","w",stdout);

	int n,m;
	cin>>n>>m;
	int* data = new int[n+m+1];  // to store the insert function and delete function data order

	srand((unsigned)time(NULL));

	/* generate random data */
	for (int i = 0; i < n+m; i++)
		data[i] = 4 * i + rand() % 4;  // make sure they are different

	/* shuffle to generate a random input */
	for (int i = 0; i < n+m-1; i++) {
		int j = i + rand() % (n+m-i);
		int temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}

	/* output to file */
	cout<<n<<endl;
	for (int i = 0; i < n; i++) cout<<data[i]<<" ";
	cout<<endl;
		
	/* output the test cases */
	cout<<m<<endl;
	for (int i = 0; i < m; i++) {
		int x = (i % 2 == 0) ? rand() % ((n+m) * 4) : data[n+m-1-i];  // generate a random number for find function
		cout<<data[n+i]<<" "<<x<<" "<<data[i]<<endl;
	}

	return 0;
}