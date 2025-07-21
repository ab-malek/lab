#include<stdio.h>

int main()
{
	int n = 6;
	int ar[] = {3,7,11,32,41,99};
	int i,j;
	int x = 99;//find x in the array

	int low = 0,high= n-1;
	while(low<=high){
		int mid = (low+high)/2;
		if(ar[mid] == x){
			printf("%d found at position %d \n",x,mid+1);
			return 0;
		}
		else if(ar[mid]<x){
			low = mid+1;
		}
		else{
			high = mid-1;
		}
	}
	printf("Not found\n");
}
