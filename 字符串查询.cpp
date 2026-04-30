#include<iostream>
#include<string>

using namespace std;

void caozuo (string &s,string fd,string s){
    size_t pos=s.find(fd);
    while((pos=s.find(fd,pos)!=string :: npos)){
        s.replace(pos,fd,to);
        pos+=fd.size();

    }
}