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

class node {
	public:
		int data;
		node* left;
		node* right;

	node(int d){
		this->data = d;
		this->left = NULL;
		this->right = NULL;
	}
};

node* buildtree(node* root){
	int data;
	cout<<"Enter the data "<<nl;
	cin>>data;
	root = new node(data);

	if(data == -1){
		return NULL;
	}

	cout<<"Enter data for inserting at left of "<<data<<nl;
	root->left = buildtree(root->left);
	cout<<"Enter data for inserting at right of "<<data<<nl;
	root->right = buildtree(root->right);
	return root;

}

void inorder(node* root){
	if(root == NULL ){
		return ;
	}

	inorder(root->left);
	cout<<root->data<<" ";
	inorder(root->right);
}

void preorder(node* root){
	if(root == NULL){
		return ;
	}

	cout<<root->data<<" ";
	preorder(root->left);
	preorder(root->right);
}

void postorder(node* root){
	if(root == NULL){
		return;
	}

	postorder(root->left);
	postorder(root->right);
	cout<<root->data<<" ";
}


int32_t main() {


   	node* root = NULL;
   root = buildtree(root);

   	cout<<"Inorder :";
   	inorder(root);
	cout<<nl;
   	cout<<"Preorder :";
   	preorder(root);
   	cout<<nl;
   	cout<<"Postorder :";
   	postorder(root);

}
