#include<iostream>
using namespace std;
int main(){
    int a;
    cin>>a;
    int len=a.size();
    for(int i=len-1;i>=0;i--){
       int b= (a>>i)&1;
        cout<<b;
    }
    //low_bit:余倒数第一个1和后面的0；
    int y=a&-a;
    cout<<y;
}