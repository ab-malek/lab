#include<bits/stdc++.h>
using namespace std;
#define long long int

int inverse_mod(int a, int b, int &x, int &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }


    int x1, y1;

    int gcd = inverse_mod(b,a%b, x1,y1);

    x  = y1;
    y = x1 - (a/b)*y1;

    return gcd;
}


int mod_exp(int a,int b,int mod){

    if(b == 0){
        return 1;
    }
    int res = mod_exp(a,b/2,mod);

    if(b%2 == 1){
        return (res * res * 1ll * a) % mod;
    }
    else{
        return (res * 1ll * res) % mod;
    }
}

int main(){
    int p = 61, q =  53;
    int n = p*q;
    int phi = (p-1) * (q-1);

    int e = 17;
    int x,y;
    int gcd = inverse_mod(e,phi,x,y);

    if(gcd != 1){
        cout<<"Inverse mod does not exits"<<endl;
        return -1;
    }
    x %= phi;
    int d = (x + phi) % phi;

    string message;

    getline(cin, message);

    vector<int> cipher;

    for(auto c : message){
        int val = int(c);

        val = mod_exp(val, e, n);

        cipher.push_back(val);
    }


    for(auto it : cipher){
        cout<<it<<" ";
    }
    cout<<endl;

    string plain = "";

    for(auto it : cipher){
        int val = mod_exp(it, d, n);
        char c = char(val);
        plain += c;
    }
    cout<<plain<<endl;
}