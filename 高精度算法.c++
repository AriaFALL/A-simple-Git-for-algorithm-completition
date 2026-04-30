#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<int> add(vector<int> &a,vector<int> &b){
    vector <int> c;
    int t=0;
    for(int i=0;i<a.size() || i<b.size();i++){
        if(i<a.size())t+=a[i];
        if(i<b.size())t+=b[i];
        c.push_back(t%10);
        t/=10;
        }
        if(t)c.push_back(1);
        return c;
}

vector<int> sub(vector<int> &a,vector<int> &b){
    int t=0;
    vector<int> c;
    for(int i=0;i<a.size();i++){
        t = a[i] - t;
        if(i<b.size())t = t - b[i];
        c.push_back((t+10)%10);
        if(t>=0)t=0;
        else t=1;
    }
    while(c.size()>1 && c.back()==0) c.pop_back();
    return c;
}

vector<int> chengfa_dijingdu(vector<int> a,int b){
    vector<int> c;
    int t=0;
    for(int i=0;i<a.size() || t;i++){
        if(i<a.size())t=(a[i]*b)+t;
        c.push_back(t%10);
        t/=10;

    }
    return c;
}

vector<int> chengfa_gaojingdu(vector<int> a, vector<int> b) {
    // 处理乘数为0的情况
    if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0)) {
        return {0};
    }
    
    vector<int> c(a.size() + b.size(), 0);
    
    for(int i = 0; i < b.size(); i++){
        for(int j = 0; j < a.size(); j++){
            c[j + i] += a[j] * b[i];
        }
    }
    
    // 处理所有进位（从低位到高位）
    for(int i = 0; i < c.size() - 1; i++){
        c[i + 1] += c[i] / 10;  // 进位
        c[i] = c[i] % 10;       // 保留个位
    }
     
    // 移除高位的0
    while(c.size() > 1 && c.back() == 0){
        c.pop_back();
    }
    
    return c;
}

vector<int> chufa_gaojingdu_xiaoshu(vector<int> a,int b,int count){
    vector<int>c;
    int t=0;
    for(int i=0;i<a.size();i++){
        t=t*10+a[i];
        if(t>=b){
            c.push_back(t/b);
            t=t%b;
        }else{
            c.push_back(0);
        }
        ci++;
    }
    int ci=0;
    while(ci<=count && t!=0){
        t=t*10;
        if(t>=b){
            c.push_back(t/b);
            t=t%b;
        }else{
            c.push_back(0);
        }
    }
    return c;
}

int main(){
    vector <int> a={1,5,3,1};
    int b=4;
    int count=5;
    vector<int>c=chufa_gaojingdu_xiaoshu(a,b,count);
    for(int i=0;i<a.size();i++){
        cout<<c[i];
    }
    cout<<".";
    for(int i=a.size();i<c.size();i++){
        cout<<c[i];
    }
    return 0;
}