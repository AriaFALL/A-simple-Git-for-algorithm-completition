#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector <pii> segs;
using pii =pair<int,int>;
//题意：
//输入N行数字，要求合并区间
void hebing (vector <pii>& segs){
    vector <pii> res;
    int st=-2e9,ed=-2e9;
    sort(segs.begin(),segs.end());
    for(auto seg:segs){
        if(ed<seg.first){
            if(st!=-2e9) res.push_back({st,ed});
            st=seg.first;
            ed=seg.second;
        }else{
            ed=max(ed,seg.second);
        }
    }
    if(st!=-2e9) res.push_back({st,ed});
    segs=res;
}
int main(){
    int n;
    cin>>n;
    while(n--){
        int st,ed;
        cin>>st>>ed;
        segs.push_back({st,ed});
    }
    hebing(segs);
}