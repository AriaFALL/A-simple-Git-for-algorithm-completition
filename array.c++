#include<iostream>
#include<string>
#include<array>
using namespace std;

int main(){
    array <string,2> a={"hello ","worlad"};
    string s;
    s=a[0]+a[1];
    cout<<s;
}