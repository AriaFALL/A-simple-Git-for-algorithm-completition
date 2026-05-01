#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 节点类型定义
typedef enum { ATOM, LIST } NodeTag;

typedef struct GLNode {
    NodeTag tag;  // 标记是原子还是子表
    union {
        char atom;  // 原子值
        struct GLNode* hp;  // 指向子表
    };
    struct GLNode* tp;  // 指向下一个兄弟节点
} GLNode, *GList;

// 创建原子节点
GLNode* createAtom(char atom) {
    GLNode* node = (GLNode*)malloc(sizeof(GLNode));
    node->tag = ATOM;
    node->atom = atom;
    node->tp = NULL;
    return node;
}

// 创建子表节点
GLNode* createList(GLNode* hp) {
    GLNode* node = (GLNode*)malloc(sizeof(GLNode));
    node->tag = LIST;
    node->hp = hp;
    node->tp = NULL;
    return node;
}

// 从字符串构建广义表，例如："(a,(b,c),d)"
GLNode* createGList(const char** str) {
    const char* s = *str;
    
    // 跳过空格
    while (*s && isspace(*s)) s++;
    
    if (*s == '\0') return NULL;
    
    if (*s == '(') {  // 遇到子表
        s++;  // 跳过 '('
        
        GLNode* head = NULL;  // 子表的第一个元素
        GLNode* tail = NULL;
        
        // 跳过空格
        while (*s && isspace(*s)) s++;
        
        if (*s == ')') {  // 空表
            s++;
            *str = s;
            return createList(NULL);  // 空子表
        }
        
        while (*s && *s != ')') {
            GLNode* node = NULL;
            
            if (*s == '(') {  // 嵌套子表
                node = createGList(&s);
            } else if (isalpha(*s)) {  // 原子
                node = createAtom(*s);
                s++;
            }
            
            // 跳过逗号和空格
            while (*s && (isspace(*s) || *s == ',')) s++;
            
            // 将节点加入链表
            if (node) {
                if (head == NULL) {
                    head = tail = node;
                } else {
                    tail->tp = node;
                    tail = node;
                }
            }
        }
        
        if (*s == ')') s++;
        *str = s;
        
        return createList(head);
    }
    
    return NULL;
}

// 打印广义表
void printGList(GList list, int isFirst) {
    if (list == NULL) {
        printf("()");
        return;
    }
    
    if (list->tag == ATOM) {
        printf("%c", list->atom);
    } else {  // LIST
        printf("(");
        GLNode* p = list->hp;
        int first = 1;
        while (p) {
            if (!first) printf(", ");
            printGList(p, 0);
            p = p->tp;
            first = 0;
        }
        printf(")");
    }
    
    if (isFirst) printf("\n");
}

// 求广义表深度
int getDepth(GList list) {
    if (list == NULL) return 1;  // 空表深度为1
    
    if (list->tag == ATOM) return 0;  // 原子深度为0
    
    GLNode* p = list->hp;
    int maxDepth = 0;
    
    while (p) {
        int depth = getDepth(p);
        if (depth > maxDepth) {
            maxDepth = depth;
        }
        p = p->tp;
    }
    
    return maxDepth + 1;
}

// 销毁广义表
void destroyGList(GList list) {
    if (list == NULL) return;
    
    if (list->tag == LIST) {
        // 递归销毁子表
        GLNode* p = list->hp;
        while (p) {
            GLNode* temp = p;
            p = p->tp;
            destroyGList(temp);
        }
    }
    
    free(list);
}

int main() {
    const char* str1 = "(a,(b,c),d)";
    const char* str2 = "((a,b),(c,(d,e)),f)";
    
    printf("示例1: %s\n", str1);
    const char* p1 = str1;
    GList list1 = createGList(&p1);
    printf("广义表: ");
    printGList(list1, 1);
    printf("深度: %d\n", getDepth(list1));
    
    printf("\n示例2: %s\n", str2);
    const char* p2 = str2;
    GList list2 = createGList(&p2);
    printf("广义表: ");
    printGList(list2, 1);
    printf("深度: %d\n", getDepth(list2));
    
    // 清理内存
    destroyGList(list1);
    destroyGList(list2);
    
    return 0;
}