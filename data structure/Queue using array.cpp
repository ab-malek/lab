#include<bits/stdc++.h>
using namespace std;

const int mxsize = 300;
int ar[mxsize];
int leftt = -1;
int top = -1;

void push(int x){
	// if(right == mxsize){
	// 	printf("Overflow\n");
	// }
	top++;
	ar[top] = x;
	if(leftt == -1) leftt = 0;
}

void pop(){
	if(leftt == -1 || leftt>top){
		cout<<"stack is empty"<<endl;
		return;
	}
	leftt++;
}
void print(){
	if(leftt == -1 || leftt>top){
		cout<<"stack is empty"<<endl;
	}
	else{
		cout<<ar[leftt]<<endl;
	}
	return;
}

int main()
{
	push(4);
	push(6);
	// push(1);
	// pop();//popped 1
	// pop();//popped 1
	print();//top elements now shuld 6be 
}
