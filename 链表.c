#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct iot {
    int num;
    struct iot *next;
}sto;

void weiba_ add(sto **head,int number,char *s){
    sto *p=(sto*)malloc(sizeof(sto));
    p->num=number;
     p->s = strdup(s);
    p->next=NULL;
    if(*head==NULL){
        *head=p;
    }
    else{
        sto *last=*head;
        while(last->next!=NULL){
            last=last->next;
        }
        last->next=p;
    }
}
void head_add(sto**head,int number,char *s){
    sto *p=(sto*)malloc(sizeof(sto));
    p->num=number;
     p->s = strdup(s);
     p->next=*head;
     *head=p;
}
void delete_number(sto **head,int number){

     if (*head == NULL) return; // 空链表，直接返回
  // 情况1：要删除的是头节点
     if ((*head)->num == number) {
     sto *temp = *head;
       *head = (*head)->next;
       free(temp);
       return;
   }
   //情况2
    while(p->num!=NULL){
        q=p;//上一个位置就此储存；
        p=p->next;
        if(p->num==number){
            q->next=p->next;
            free(p);
        }
        }
}
//for的遍历
for(sto *p=head;p;p=p->next){
    if(p->num==number){
        break;
    }
}



    int main(){
       int number;
    char buffer[100];  // 为输入分配固定缓冲区
    sto *head = NULL;

    while (1) {
        scanf("%d", &number);
        if (number == -1) break;  // 先检查终止条件
        
        scanf("%99s", buffer);    // 限制输入长度防溢出
        add(&head, number, buffer); // 正确传递指针地址
    }

    // 释放链表内存（重要！）
    sto *current = head;
    while (current) {
        sto *temp = current;
        current = current->next;
        free(temp->s);  // 释放字符串内存
        free(temp);     // 释放节点内存
    }
    }
