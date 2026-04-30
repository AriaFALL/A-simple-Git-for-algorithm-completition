#include<iostream>
#include<stack>

using namespace std;

int main()
{
    stack <int> s;
    int t=0;
    int count;
    while(t!=-1){
        int b;
        cin>>b;
        s.push(b);
        t=b;
        count++;
    }
    s.pop();
    cout<<s.size()<<endl;
    int m=s.size();
    for(int i=1;i<=m;i++){
        cout<<i<<" :"<<s.top()<<endl;
        s.pop();
    }
}