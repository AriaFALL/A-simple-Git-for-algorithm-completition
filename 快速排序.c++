#include<iostream>
#include<algorithm>
using namespace std;
void quick_sort(int* a,int l,int r){
    if(l>=r){
        return ;
    }
    int i=l-1;
    int j=r+1;
    int mid=(i+j)/2;
    int g=a[mid];
    while(i<j){
        do{
            i++;
        }while(i<j && a[i]<a[mid]);
        do{
            j--;
        }while(i<j && a[j]>a[mid]);
        if(i<j){
            swap(a[i],a[j]);
        }
    }
    quick_sort(a,l,j);
    quick_sort(a,j+1,r);
}
int main(){
    int a[]={1,5,89,54,564,78,35,245,112,56};
    quick_sort(a,0,9);
    for(int i=0;i<10;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}