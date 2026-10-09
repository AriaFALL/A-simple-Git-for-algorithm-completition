#include<iostream>
#include<string>

using namespace std;

void caozuo (string &s,string fd,string s){
    size_t pos=0;
    while((pos=s.find(fd,pos)!=string :: npos)){
        s.replace(pos,fd,to);
        pos+=fd.size();
    }
}