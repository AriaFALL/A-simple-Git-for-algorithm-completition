#include<stdio.h>
int main()
{
    int n;
    int x=0;
    int count=0;
    scanf("%d",&n);
    if(n%3!=0){
        printf("Error");
        return 0;
    }
    while(n!=153){
        x=0;
        while(n!=0){
            x=x+(n/10)*(n/10)*(n/10);
            n=n/10;
        }
        n=x;
        count++;
    }
    printf("%d",count);
}