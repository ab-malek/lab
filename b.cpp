#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define nl '\n'
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define all(a) a.begin(),a.end()
#define flush fflush(stdout) 
#define int long long
#define malek cout<<"malek"<<nl
#define printVec(v) for(int i=0;i<v.size();i++){cout<<v[i]<<" ";}cout<<nl
#define printVecPair(v) for(auto it : v){cout<<it.first<<" "<<it.second<<nl;}


void solve(){
    int n;
    cin>>n;
    int mat[n][n];
    for(int i=0;i<n;i++){
        for(int j  = 0;j<n;j++){
            cin>>mat[i][j];
            if(mat[i][j] == 0){
                mat[i][j] = 1e9;
            }
        }
    }

    for(int k = 0;k<n;k++){
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n;j++){
                mat[i][j]  = min(mat[i][j],mat[i][k]+mat[k][j]);
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(mat[i][j] == 1e9) mat[i][j] = 0;
            else if(mat[i][j] != 0) mat[i][j] =1;
            cout<<mat[i][j]<<" ";
        }
        cout<<nl;
    }
}



int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin>>t;
    while(t--){
        solve();
    }
}