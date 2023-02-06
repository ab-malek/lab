#include<stdio.h>

int main()
{
	int n = 5;
	int ar[] = {6,3,88,1,7};
	int i,j;
	for(i=0;i<n;i++){
		for(j = 0;j<n-1;j++){
			if(ar[j]>ar[j+1]){
				// swap ar[j] and ar[j+1]
				int temp =ar[j];
				ar[j] = ar[j+1];
				ar[j+1] = temp;

			}
		}
	}

	for(int i=0;i<n;i++){
		printf("%d\n",ar[i]);
	}
}
