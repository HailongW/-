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
 初始条件:链式线性表L已经存在
 操作结果:删除链表第i个位置的元素，并用e返回其值，L的长度减1
 */
Status ListDelete(LinkList *L, int i,ElemType *e) {
    int j = 1;
    LinkList p,q;
    p = (*L)->next;
    //查找到第i-1个的节点， p 指向该节点
    while (p->next && j < (i-1)) {
        p = p->next;
        j++;
    }
    //当i>链表长度 时或i<1时，删除位置不合理
    if (!(p->next) && (j>i-1))  return ERROR;
    //将q 指向要删除的节点
    q = p->next;
    //将q的后继节点赋值给p
    p->next = q->next;
    
    //将q节点中的数据数据给e
    *e = q->data;
    
    //让系统回收此节点，释放内存
    free(q);
    
    return OK;
}

/**
 初始条件:链式线性表L已存在
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

//清空链表
/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L) {
    
    LinkList p, q;
    p = (*L)->next; //p 指向第一个节点
    while (p) {     //没到表尾，p就不为空，继续循环删除
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL; //头结点指针域为空
    
    return OK;
}

//单链表前插入法
/* 随机产生n个元素值,建立带表头结点的单链线性表L(前插法)*/
Status CreateListHead(LinkList *L, int n) {
    int j = 0;
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    LinkList p;
    while (j<n) {
        //生成新节点
        p = (LinkList)malloc(sizeof(Node));
        //将j值赋给新节点
        p->data = j;
        //将p的next 指向 头结点的next
        p->next = (*L)->next;
        //将头结点的next指向p
        (*L)->next = p;
        
        j++;
    }
    return OK;
}

//单链表的后插入法
/* 随机产生n个元素值,建立带表头结点的单链线性表L(后插法)*/
Status CreateListTail(LinkList *L, int n) {
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    LinkList p,r; //r 指向尾部节点
    r = *L;
    for (int i = 0; i<n; i++) {
        p = (LinkList)malloc(sizeof(Node));
        p->data = i;
        //将表尾终端结点的指针指向新结点
        r->next = p;
        //将当前的新结点定义为表尾终端结点
        r = p;
    }
    //将尾指针的next = null
    r->next = NULL;
    
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
    
    //单链表插入数据
    for (int i = 1; i<10; i++) {
        ListInsert(&L, i, i);
    }
    ListTraverse(L);
    
    //单链表获取元素
    GetElem(L, 5, &e);
    printf("第5个元素的值为：%d\n",e);
    
    //删除第5个元素
    ListDelete(&L, 5, &e);
    printf("删除第5个元素位置值为%d\n",e);
    ListTraverse(L);
    
    //前插法创建整个链表L
    ClearList(&L);
    CreateListHead(&L, 20);
    printf("整理创建L的元素(前插法):\n");
    ListTraverse(L);
    
    //尾插法创建整个链表L
    ClearList(&L);
    CreateListTail(&L, 20);
    printf("整理创建L的元素(后插法):\n");
    ListTraverse(L);
   
    
    
    return 0;
}
