#include <iostream>
#include <vector>
using namespace std;
 vector<int>path;
int dfs(vector<vector<int>> &op,vector<bool> &visited,int n,int i){
    if(i==n){
        return 1;
    }
    int ret=0;
    int ed=0;
    for(int j:op[i]){
        if(!visited[j]){
            ret=1;
            ed=j;
            visited[j]=true;
            path.push_back(j);
            int res= dfs(op,visited,n,i+1);
            if(res==1){
                return 1;
            }else{
            path.pop_back();
             return -1;
            }
        }
    }
    if(!ret){
        return -1;
    }
}

int main() {
   int n;
   cin>>n;
   vector<vector<int>> op(n);
   for(int i=0;i<n;i++){
    int k;
    cin>>k;
    while(k--){
        int o;cin>>o;
        op[i].push_back(o);
    }
    }
    vector<bool> visited(n+1);
   int res = dfs(op,visited,n,0);
   if(res==1){
    for(int j:path){
        cout<<j<<" ";
    }
   }else{
    cout<<"kou is angry";
   }
}