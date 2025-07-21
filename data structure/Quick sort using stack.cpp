#include<bits/stdc++.h>
using namespace std;

int partition(int ar[],int l,int r){
	int pivot = ar[l];
	int i = l,j = r;
	while(i<j){
		while(ar[i]<=pivot){
			i++;
		}
		while(ar[j]>pivot){
			j--;
		}
		if(i<j){
			swap(ar[i],ar[j]);
		}
	}
	swap(ar[l],ar[j]);
	return j;
}
void quicksort(int ar[],int l,int r){
	stack<pair<int,int> > s;
	s.push({l,r});
	while(!s.empty()){
		l = s.top().first;
		r = s.top().second;
		s.pop();
		if(l>r){
			continue; //when the left is greater than right we have to stop our partitoning
		}
		int j = partition(ar,l,r);
			s.push({l,j-1});
			s.push({j+1,r});
	}

	return;
}

int main(){
	int n;
	cout<<"Enter the array size : ";
	cin>>n;
	cout<<"Enter the elements of array :";
	int ar[n];
	for(int i=0;i<n;i++){
		cin>>ar[i];
	}
	int l = 0,r = n-1;
	quicksort(ar,l,r);



	for(int i=0;i<n;i++){
		cout<<ar[i]<<" ";
	}
	cout<<endl;
}
