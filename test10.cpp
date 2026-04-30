#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

void print_s(string s){
    for(int j=0;j<s.size()-1;j++){
        int res=s[j]-'a'+1;
        cout<<res<<' ';
    }
    int res=s.back()-'a'+1;
    cout<<res<<'\n';
}

int main(){
    int N,M;
    cin>>N>>M;
    string s;
    for(int i=0;i<N;i++){
        int a;
        cin>>a;
        char sp=a+'a'-1;
        s+=sp;
    }
    for(int i=0;i<M;i++){
        int take;
        cin>>take;
        if(take==1){
            int x;
            cin>>x;
            string fd,to;
            for(int j=0;j<x;j++){
                int y;
                char t;
                cin>>y;
                t=y-1+'a';
                fd+=t;
            }
            cin>>x;
            for(int j=0;j<x;j++){
                int y;
                cin>>y;
                char t=y-1+'a';
                to+=t;
            }
            size_t pos=s.find(fd);
            while(pos!=string :: npos){
                s.replace(pos,fd.size(),to);
                pos=s.find(fd);
            }
            print_s (s);
        }else if(take==2){
            int p=s.size();
            int g=1;
            while(g<p){
                int l=s[g-1]-'a'+1;
                int r=s[g]-'a'+1;
                if((l+r)/2==0){
                    char in=(l+r)/2+'a'-1;
                    s.insert(g,in);
                    g++;
                    p++;
                }
            }
            print_s (s);
        }else if(take==3){
            int l,r;
            cin>>l>>r;
            l--;
            r--;
            string now_l=s.substr(0,l);
            string now_r=s.substr(r+1);
            string now=s.substr(l+1,r-l);
            now=reverse(now.begin(),now.end());
            s=now_l+now+now_r;
            print_s (s);
        }
    }
}

