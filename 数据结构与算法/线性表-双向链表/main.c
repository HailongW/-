//
//  main.c
//  线性表-双向链表
//
//  Created by 王海龙 on 2020/4/21.
//  Copyright © 2020 WHL. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node {
    ElemType data;
    struct Node *prior;
    struct Node *next;
}Node;

typedef struct Node * LinkList;
//创建双向链表
Status CreateLinkList(LinkList *L) {
    //*指向头头结点
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) {
        return ERROR;
    }
    (*L)->prior = NULL;
    (*L)->next = NULL;
    (*L)->data = -1;
    //新增数据
    LinkList p = *L;
    for (int i=0; i<10; i++) {
        //1.创建一个临时结点
        LinkList temp = (LinkList)malloc(sizeof(Node));
        temp->next = NULL;
        temp->prior = NULL;
        temp->data = i;
        
        //2.为新增的节点创建双向链表关系
        //①temp 是p的后继结点
        p->next = temp;
        //②temp的前驱是p
        temp->prior = p;
        //③p要记录最后一个结点的位置，方便下一次插入
        p = p->next;
        
    }
    return OK;
}

//打印循环链表的元素
void display(LinkList L) {
    LinkList temp = L->next;
    if (temp == NULL) {
        printf("打印的双向链表为空！\n");
        return;
    }
    while (temp) {
        printf("%d\n",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

#pragma mark -双向链表的插入
Status ListInsert(LinkList *L, int i, ElemType e) {
    //出入的位置不合法 为0或者为负数
    if (i < 1) {
        return ERROR;
    }
    //新建结点
    LinkList temp = (LinkList)malloc(sizeof(Node));
    temp->data = e;
    temp->prior = NULL;
    temp->next = NULL;
    
    //将p指向头结点
    LinkList p = *L;
    //找到要插入位置i的前一个结点，比如说i是3，要在第3个位置插入新节点，则p是第2个位置的结点
    for (int j = 1; j<i && p; j++) {
        p = p->next;
    }
    //判断插入位置是否为链表尾部
    if (p->next == NULL) {
        p->next = temp;
        temp->prior = p;
    }else {
        //将p的后继结点的前驱指向要插入的新的结点temp
        p->next->prior = temp;
        //将temp的后继结点指向p的后继结点
        temp->next = p->next;
        //将p的后继结点指向temp
        p->next = temp;
        //将temp的前驱结点指向p
        temp->prior = p;
    }
    
    
    return OK;
}

#pragma mark - 删除双向链表指定位置上的结点
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int k = 1;
    LinkList p = *L;
    //1.判断双向链表是否为空,如果为空则返回ERROR;
    if (*L == NULL) {
        return ERROR;
    }
    
    //将指针p指向要删除元素位置的前一个结点
    while (k<i && p != NULL) {
        p = p->next;
        k++;
    }
    
    if (k>i || p == NULL) {
        return ERROR;
    }
    //创建临时指针指向要删除的结点，并将要删除的结点的data 赋值给*e，带回到主函数main
    LinkList delTemp = p->next; //temp 要删除的元素
    *e = delTemp->data;
    
    //将p的后继结点指向要删除结点的后继结点
    p->next = delTemp->next;
    
    //如果删除结点的下一个结点不为空,则将将要删除的下一个结点的前驱指针赋值p;
    if (delTemp->next != NULL) {
        delTemp->next->prior = p;
    }
    //释放delTemp 结点
    free(delTemp);
    
    return OK;
}

#pragma mark -删除双向链表指定的元素
Status ListDeleteVal(LinkList *L, ElemType data) {
    LinkList p = *L;
    //1.遍历双向循环链表
    while (p) {
        //2.判断当前结点的数据域和data是否相等,若相等则删除该结点
        if (p->data == data) {
            //3.将要删除结点的前驱结点的后继结点指向要删除结点的后继结点
            p->prior->next = p->next;
            //4.判断p是尾结点的情况，尾结点的后继结点是NULL
            if (p->next != NULL) {
                //如果p不是尾结点，将要删除结点的后继结点的前驱结点指向要删除结点的前驱结点
                p->next->prior = p->prior;
            }
            
            free(p);
            break;
        }
        //没有找到该节点继续移动指针
        p = p->next;
    }
    return OK;
}

#pragma mark - 在双向链表中查找元素
int selectElem(LinkList L, ElemType e) {
    LinkList p = L->next;
    int i = 1;
    while (p) {
        if (p->data == e) {
            return i;
        }
        i++;
        p = p->next;
    }
    return -1;
}

#pragma mark - 在双向链表中更新结点
Status replaceLinkListNode(LinkList *L,int index,ElemType newElem) {
    
    LinkList p = (*L)->next;
    int i = 1;
    while (p && i < index) {
        p = p->next;
        i++;
    }
    p->data = newElem;
    
    return OK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    LinkList L;
    CreateLinkList(&L);
    display(L);
    printf("请输入要插入的结点元素\n");
    int item;
    scanf("%d",&item);
    ListInsert(&L, 2, item);
    printf("\n");
    display(L);
    
    printf("请输入要删除的元素位置:");
    scanf("%d",&item);
    ElemType e;
    ListDelete(&L, item, &e);
    display(L);
    printf("请输入要删除的元素数据:");
    scanf("%d",&item);
    ListDeleteVal(&L, item);
    display(L);
    
    printf("请输入要查找的元素:");
    scanf("%d",&item);
    int index = selectElem(L,item);
    printf("该元素的位置：%d\n",index);
    
    printf("请输入替换结点的位置和数据:");
    int index1;
    scanf("%d %d",&index1, &item);
    replaceLinkListNode(&L, index, item);
    display(L);
    return 0;
}
