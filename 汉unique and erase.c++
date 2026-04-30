#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    vector<int> a;
    sort(a.begin(),a.end());
    auto op = unique(a.begin(),a.end());
    a.erase(op,a.end());
    
}