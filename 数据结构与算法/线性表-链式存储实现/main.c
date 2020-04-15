//
//  main.c
//  线性表-链式存储实现
//
//  Created by 王海龙 on 2020/4/14.
//  Copyright © 2020 WHL. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define MAXSIZE 20 /* 存储空间初始分配量 */
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

//定义节点
typedef  struct Node {
    ElemType data;
    struct Node *next;
}Node;

typedef struct Node *LinkList;

//初始化单链表线性表
Status InitList(LinkList *L){
    //产生头节点，并使用L指向头节点
    *L = (LinkList)malloc(sizeof(Node));
    //存储空间分配失败
    if (*L == NULL) return ERROR;
    //将头节点的指针域置空
    (*L)->next = NULL; //(*L)->next 这个（）不能去掉是为了把*和L作为一个整体
    return OK;
    
}
//单链表的插入
Status ListInsert(LinkList *L, int i, ElemType e){
    int j = 1;
    LinkList p,s;
    p = *L;
    //寻找第i-1 个位置的节点
    while (p && j<i) {
        p = p->next;
        ++j;
    }
    //第i个元素不存在
    if (!p || j>i) return ERROR;
    
    //生成新的节点s
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    //将p的后继节点赋给s的后继节点
    s->next = p->next;
    //将p的后继节点赋成s
    p->next = s;
    
    return OK;
}

//单链表的取值
Status GetElem(LinkList L, int i, ElemType *e) {
    int j=1;
    LinkList p;
    //将结点p 指向链表L的第一个结点;
    p = L->next;
    while (p && j<i) {
        p = p->next;
        ++j;
    }
    //p不为空,且计算j不等于i,则循环继续
    if (!p || j>i) return ERROR;
    *e = p->data;
    return OK;
}

//单链表删除元素


/**
 初始条件:顺序线性表L已存在
 操作结果:依次对L的每个元素输出
 */
Status ListTraverse(LinkList L) {
    LinkList p = L->next;
    while (p) {
        printf("%d\n",p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    Status iStatus;
    LinkList L;
    struct Node *L2;
    ElemType e;
    iStatus = InitList(&L);
    printf("L 是否初始化成功?(0:失败,1:成功) %d\n",iStatus);
    return 0;
}
