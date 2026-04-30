#include<stdio.h>

struct days {
    int years;
    int month;
    int day;
};

void shuru (struct days *d){
    scanf("%d",&d->years);
    scanf("%d",&d->month);
    scanf("%d",&d->day);
}

struct jisuan{
    struct days a;
    struct days b;
};

struct days  hanshu (struct jisuan *l){
    struct days result;
    result.years=l->a.years-l->b.years;
    result.month=l->a.month-l->b.month;
    result.day=l->a.day-l->b.day;
    return result;
}

int main()
{

int i;
scanf("%d",&i);
struct days c[i];
for (int u=0;u<i;u++){
    shuru (&c[u]);
}
for (int g=i-1;g>=0;g--){
    printf("DAYS:%i__%i__%i\n",c[g].years,c[g].month,c[g].day);
}

for (int y=1;y<i;y++){
    struct jisuan t;
    t.a=c[y-1];
    t.b=c[y];
    struct days o=hanshu (&t);
    printf("差：%i__%i__%i",o.years,o.month,o.day);
}

return 0;
}