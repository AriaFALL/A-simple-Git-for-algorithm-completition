#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector <int> a={1,2,4,6,9,98,789,4562};
    int r=a.size()-1;
    int l=0;
    int target;
    cin>>target;
    int ret=0;
    while(l<=r && ret==0 ){ // 寻找唯一的数
        int mid=(l+r)/2;
        if(a[mid]<target){
            l=mid+1;
        }else if(a[mid]==target){
            ret=1;
            cout<<"找到了！";
        }else{
            r=mid-1;
        }
    }
    if(ret==0){
        cout<<"没找到";
    }
}

//寻找第一个>=x的数。

while (l<r){
    int mid=(l+r)/2;
    if(a[mid]<target){
        l=mid+1;
    }else {
        r=mid;
    }
}
