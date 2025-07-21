#include<bits/stdc++.h>
using namespace std;

const int mxsize = 300;
int ar[mxsize];
int top = -1;

void push(int x){
	if(top == mxsize){
		printf("Overflow\n");
	}
	top++;
	ar[top] = x;
}

void pop(){
	if(top == -1){
		cout<<"stack is empty"<<endl;
		return;
	}
	top--;
}
void print(){
	if(top == -1){
		cout<<"stack is empty"<<endl;
	}
	else{
		cout<<ar[top]<<endl;
	}
	return;
}

int main()
{
	push(4);
	push(6);
	push(1);
	pop();//popped 1
	print();//top elements now shuld 6be 
}
