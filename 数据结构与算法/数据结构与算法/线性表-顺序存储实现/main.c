//
//  main.c
//  数据结构与算法
//
//  Created by 王海龙 on 2020/4/13.
//  Copyright © 2020 WHL. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */
typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

/*线性结构使用顺序表的方式存储实现
 （逻辑相邻，物理存储地址相邻）
 */
//顺序表结构设计
typedef struct {
    ElemType *data;
    int length;
}sqlList;

//1.1 顺序表初始化
Status InitList(sqlList *L) {
     //为顺序表分配一个大小为MAXSIZE 的数组空间
    L->data = malloc(sizeof(ElemType) * MAXSIZE);
    if (!L->data) exit(ERROR);
    //空表长度为0
    L->length = 0;
    return OK;
}

//1.2顺序表的插入
/*
 初始条件:顺序线性表L已经存在，1≤i≤ListLength(L);
 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1
 */
Status ListInsert(sqlList *L, int i, ElemType e) {
    if (i<1 || i>L->length+1) return ERROR;
    //存储空间已满
    if (L->length == MAXSIZE) return ERROR;
    //插入数据不再表尾,则先移动出空余位置
    if (i<=L->length) {
        for (int j = L->length-1; j>=i-1; j--) {
            //插入位置以及之后的位置向后移动一位
            L->data[j+1] = L->data[j];
        }
    }
    //将元素e放入第i个位置上
    L->data[i-1] = e;
    //长度加1
    ++L->length;
    return OK;
    
}

//1.3 顺序表的取值
Status GetElem(sqlList L,int i, ElemType *e) {
    //判断i值是否合理，不合理直接返回ERROR
    if (i<1 || i > L.length) return ERROR;
    *e = L.data[i-1];
    return OK;
}

//1.4 顺序表的删除
/**
 初始条件:顺序表L已经存在，1≤i≤ListLength(L)
 操作结果:删除L的第i个数据元素,L的长度减1
 */
Status ListDelete(sqlList *L,int i) {
    //线性表为空
    if (L->length == 0) return ERROR;
    //i值不合法判断
    if (i<=1 || i > L->length + 1) return ERROR;
    for (int j = i; j<L->length; j++) {
        //被删除之后的元素向迁移
        L->data[j-1] = L->data[j];
    }
    L->length--;
    return OK;
}


//1.5 清空顺序表
Status ClearList(sqlList *L){
    L->length = 0;
    return OK;
}

//1.6 判断顺序表清空
/**
 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
 */
Status ListEmpty(sqlList L) {
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

//1.7 获取顺序表长度
int listLength(sqlList L) {
    return L.length;
}

//1.8 顺序输出List
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status TraverseList(sqlList L){
    int i;
    for (i=0; i<L.length; i++) {
        printf("%d\n",L.data[i]);
    }
    printf("\n");
    return OK;
}

//1.9 顺序表查找元素并返回位置
/**
 初始条件:顺序表L已经存在
 操作结果：返回L中第1个与e满足关系的数据元素的位序
 若这样的数据元素不存在，则返回值为0
 */
int LocateElem(sqlList L,ElemType e) {
    if (L.length == 0) return ERROR;
    for (int i = 0; i<L.length; i++) {
        if (L.data[i] == e) {
            return i + 1;
        }
    }
    return 0;
    /** CC 老师的写法
     int i;
       if (L.length==0) return 0;
       
       for(i=0;i<L.length;i++)
       {
           if (L.data[i]==e)
               break;
       }
     
       if(i>=L.length) return 0;
       return i+1;
     */
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    sqlList L;
    Status iStatus;
    ElemType e;
    
    //顺序表的初始化
    iStatus = InitList(&L);
    printf("初始化L后：L.length = %d\n",L.length);
    
    //顺序表数据插入 -- 头插法
    for (int j = 1; j<=5; j++) {
        iStatus = ListInsert(&L, 1, j);
    }
    printf("插入数据L长度：%d\n",L.length);
    TraverseList(L);
    //顺序表获取元素
    GetElem(L, 5, &e);
    printf("顺序表L第5个元素的位置:%d\n",e);
    //顺序表删除第2个元素
    ListDelete(&L, 2);
    printf("顺序表删除第%d个元素,长度length为%d\n",2,L.length);
     TraverseList(L);
    //查找对应元素e 的位置
    int index = LocateElem(L, 1);
    printf("顺序表L中数字1的位置:%d\n",index);
    
    //清空顺序表
    ClearList(&L);
    printf("清空后,L.length = %d\n",L.length);
    
    //判断顺序表是否为空
    iStatus = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",iStatus);

    return 0;
}
