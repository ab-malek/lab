#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define nl '\n'
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define all(a) a.begin(),a.end()
#define flush fflush(stdout) 
#define int long long
#define printVec(v) for(int i=0;i<v.size();i++){cout<<v[i]<<" ";}cout<<nl
#define printVecPair(v) for(auto it : v){cout<<it.first<<" "<<it.second<<nl;}



int partition(int ar[],int l,int r){
	int pivot = ar[l];
	int i = l,j = r;
	while(i<j){
		while(ar[i]<=pivot)i++;
		while(ar[j]>pivot)j--;

		if(i<j){
			swap(ar[i],ar[j]);
		}
	}
	if(i>j){
		swap(ar[j],ar[l]);
	}
	return j;
}

void quicksort(int ar[],int l,int r){

	if(l<r){
		int pivot = partition(ar,l,r);

		quicksort(ar,l,pivot-1);
		quicksort(ar,pivot+1,r);

	}
}

int32_t main()
{
	int ar[] = {6,44,3,44,534,1,11,2};

	int n = 8;
	int l = 0,r = n-1;
	quicksort(ar,l,r);

	for(int i=0;i<n;i++){
		cout<<ar[i]<<" ";
	}
	cout<<nl;
}
