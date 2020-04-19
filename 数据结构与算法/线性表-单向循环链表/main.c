//
//  main.c
//  线性表-单向循环链表
//
//  Created by 王海龙 on 2020/4/17.
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

//循环链表的创建
/**
 2种情况：①第一次开始创建；②已经创建，往里面新增数据
  判断是否是第一次创建链表
  YES:创建一个新节点，并使得新节点的next指向自身:(*L)->next = (*L)
  NO:找链表尾节点，将尾节点next指向头新节点，将新节点的next指向(*L)
 */

Status CreateList(LinkList *L) {
    int item;
    LinkList temp = NULL;
    LinkList target = NULL;
    printf("请输入节点的值，输入0结束\n");
    while (1) {
        scanf("%d",&item);
        if (item == 0) break;
        /*如果输入的链表是空的则创建一个新的链表将其next指针指向自己
         (*head)->next = (*head);
         */
        if (*L == NULL) {
            *L = (LinkList)malloc(sizeof(Node));
            if (!L) exit(0);
            (*L)->data = item;
            (*L)->next = (*L);
        }else {
            /*
             输入的链表不是空的，寻找到链表的尾结点，是尾节点的next指向新的结点，
             将新的结点的next指向头结点
             */
            for (target = *L; target->next != *L; target = target->next);
            temp = (LinkList)malloc(sizeof(Node));
            if (!temp) return ERROR;
            temp->data = item;//将输入的值放入新的结点中
            temp->next = *L;//将新的尾结点的next指向头结点
            target->next = temp;//将当前的尾结点指向新的结点
        }
    }
    return OK;
}

/**
在上面的代码中，我们使用for循环实现了关于最后一个结点的获取，但是这种方式会增加时间复杂度，
所以在创建链表时可以使用一个临时指针来记录最后一个节点，
用来确保每次新增数据后，都能添加到最后并且及时修改链表信息
 */
Status CreateList2(LinkList *L) {
    int item;
    LinkList temp = NULL;
    LinkList r = NULL; //临时指针记录最后一个结点
    printf("请输入新的结点,当输入0时结束\n");
    while (1) {
        scanf("%d",&item);
        if (item == 0) {
            break;
        }
        if (*L == NULL) {
            *L = (LinkList)malloc(sizeof(Node));
            (*L)->data = item;
            (*L)->next = *L;
            r = *L;
        }else {
            temp = (LinkList)malloc(sizeof(Node));
            temp->data = item;
            temp->next = *L;
            r->next = temp;
            r = temp;// r 记录当前链表的最后一个结点,省去方法1中for循环查找尾结点的过程
            
        }
    }
    return OK;
}

//循环链表插入数据
Status ListInsert(LinkList *L,int place,ElemType e) {
    LinkList temp,target;
    int i;
    if (place == 1) {
        /*如果插入的位置为1，则插入的时首元结点，需要特殊处理
         1.创建新结点temp，并判断是否创建成功，成功则赋值，否则返回ERROR
         2.找到链表最后的尾结点
         3.让新结点的next 指向头结点
         4.让尾结点的next指向新的头结点
         5.让头指针指向temp（临时的头结点）
         */
        temp = (LinkList)malloc(sizeof(Node));
        if (!temp) return ERROR;
        temp->data = e;
        //target 初始为头结点，从头结点开始循环遍历，只要target->next ！= *L就继续循环遍历，target ==  *L 时则找到了尾结点结束遍历
        for (target = *L; target->next != *L; target = target->next);
        temp->next = *L;
        target->next = temp;
        *L = temp;
    }else {
        /* 1.创建新结点temp,并判断是否创建成功,成功则赋值,否则返回ERROR;
           2.先找到插入的位置,如果超过链表长度,则自动插入队尾;
           3.插入结点的前驱结点指向新结点,新结点的next 指向target原来的next位置;
           4.通过target找到要插入位置的前一个结点, 让target->next = temp;
         */
        temp = (LinkList)malloc(sizeof(Node));
        if (temp == NULL) {
            return ERROR;
        }
        temp->data = e;
        for (i = 1,target = *L; target->next != *L && i != place - 1; target = target->next, i++);
        temp->next = target->next;
        target->next = temp;
    }
    return OK;
}

//单向循环链表的删除
Status ListDelete(LinkList *L, int place) {
    if (*L == NULL) return ERROR;
    LinkList temp = *L;
    LinkList target;
    int i;
    
    if (place == 1) {
        //①如果删除的只剩下首元结点了，则直接将*L置空
        if ((*L)->next == (*L)) {
            (*L) = NULL;
            return OK;
        }
        //②链表还有很多数据，但是删除的是首元结点
        //1.找到尾结点，使尾结点的next 指向头结点的下一个结点
        //2.新结点作为头结点，则释放原来的就结点
        for (target = *L; target->next != *L; target = target->next);
        target->next = (*L)->next;
        temp = *L;
        *L = (*L)->next;
        free(temp);
    }else {
        //如果删掉其他结点
        /**
         1.找到删除结点前一个结点target
         2.target 指向要删除结点的下一个结点，target->next 即要删除的结点temp
         3.释放要删除的结点temp
         */
        for (i = 1, target = *L; target->next != *L && i<place -1; target = target->next ,i++);
        temp = target->next;
        target->next = temp->next;
        free(temp);
    }
    return OK;
}

//循环链表查询值
int FindValue(LinkList L, int value) {
    if (L == NULL) {
        return ERROR;
    }
    int i = 1;
    LinkList p = L;
    while (p->data != value && p->next != L) {
        p = p->next;
        i++;
    }
    
    return i;
}

//遍历循环链表
void show(LinkList p) {
    if (p == NULL) {
        printf("打印的链表为空！\n");
        return;
    }else {
        LinkList temp;
        temp = p;
        do {
            printf("%5d",temp->data);
            temp = temp->next;
        } while (temp!=p);
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
//    LinkList head;
//    CreateList(&head);
//    printf("原始链表1\n");
//    show(head);
    printf("原始链表2\n");
    LinkList head2;
    CreateList2(&head2);
    show(head2);
    printf("指定位置插入结点\n");
    int place,item;
    scanf("%d %d",&place,&item);
    ListInsert(&head2, place, item);
    show(head2);
    printf("请输入要删除的结点位置:");
    scanf("%d",&item);
    ListDelete(&head2, item);
    show(head2);
    printf("请输入查询的数据:");
    scanf("%d",&item);
    int findIndex = FindValue(head2, item);
    printf("查询数据结点的位置:%d\n",findIndex);
    show(head2);
    return 0;
}
