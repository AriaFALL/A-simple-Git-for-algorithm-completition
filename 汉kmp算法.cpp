#include<iostream>
#include<vector>
#include<string>
using namespace std;

int kmp(string main,string pattern){
    string news=pattern+'#'+main;
    vector <int> pi(news.size());
    for(int i=1;i<news.size();i++){
        int len=pi[i-1];
        while(len!=0 && news[len]!=news[i]){
            len=pi[len-1];
        }
        if(news[len]==news[i]){
            pi[i]=len+1;
            if(pi[i]==pattern.size()){
                return i-2*pattern.size();
            }
        }
    }
    return -1;
}