#include<stdio.h>
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int count;
    if(m%n!=0){
        printf("-1");
        return 0;
    }
    m=m/n;
    while(m%3==0){
        m=m/3;
        count++;
    }
    while(m/2==0){
        m=m/2;
        count++;
    }
    printf("%d",count);
    return 0;
}