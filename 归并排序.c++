#include<iostream>
#include<vector>
using namespace std;

void Merge_sort(vector<int>&a ,vector<int>&temp,int start,int mid,int end){
    int i=start;
    int j=mid+1;
    while(i!=mid+1 && j!=end+1){
        if(a[i]<a[j]){
            int op=a[i++];
            temp.push_back(op);
        }else{
            int op=a[j++];
            temp.push_back(op);
        }
    }
    while(i!=mid+1){
        int op=a[i++];
        temp.push_back(op);
    }while(j!=end+1){
        int op=a[j++];
        temp.push_back(op);
    }
    for(int y=start;y<=end;y++){
        a[y]=temp[y];
    }
}

void Merge(vector<int>&a,vector<int>&temp,int start,int end){
    int mid;
    if(start<end){
        mid=start+(end-start)/2;
        Merge(a,temp,start,mid);
        Merge(a,temp,mid+1,end);
        Merge_sort(a,temp,start,mid,end);
    }
}

int main(){
    
}