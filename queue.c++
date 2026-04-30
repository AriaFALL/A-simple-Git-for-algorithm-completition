#include<iostream>
#include<vector>
#include<string>
#include<queue>

using namespace std;

int main(){
    int t;
    cin>>t;
    vector <string> duiwu;
    for(int i=0;i<t;i++){
        string s;
        cin>>s;
        int ret=0;
        if(i==0){
            duiwu.push_back(s);
        }
        if(s!="younik" && i!=0){
            for(int o=0;o<=len;o++){
                if(s==duiwu[o]){
                    ret=1;
                    break;
                }
            }
            if(ret==0){
                duiwu.push_back(s);
            }
        }else if(s=="younik" && i!=0){
            break;
        }
    }
    int len=duiwu.size();
    cout<<len;
    return 0;
}