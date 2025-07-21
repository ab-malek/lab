#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define nl '\n'
#define all(a) a.begin(),a.end()
#define flush fflush(stdout)
#define forz(i,n) for(int i=0;i<n;i++)
#define foro(i,n) for(int i=1;i<=n;i++)
// #define int long long
// #define int pi = 3.141592653589793238
#define malek cout<<"malek"<<nl
#define printVec(v) for(int i=0;i<v.size();i++){cout<<v[i]<<" ";}cout<<nl
#define printVecPair(v) for(auto it : v){cout<<it.first<<" "<<it.second<<nl;}

int partition(int ar[],int l,int h){
	int pivot = ar[l];

	int i = l,j = h;
	while(i<j){
		while(pivot>=ar[i])i++;
		while(pivot<ar[j])j--;
		if(i<j) swap(ar[i],ar[j]);
	}
	swap(ar[l],ar[j]);
	return j;

}


void quicksort(int ar[],int l,int h){
	if(l<h){
		int j = partition(ar,l,h);
		quicksort(ar,l,j-1);
		quicksort(ar,j+1,h);
	}
}

int32_t main() {
	int ar[] = {6,2,1,9,3};
	int n = 5;
	int l = 0,h = n-1;
	quicksort(ar,l,h);

	for(int i=0;i<n;i++){
		cout<<ar[i]<<" ";
	}
	cout<<nl;
}
