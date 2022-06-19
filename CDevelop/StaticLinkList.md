#  线性表的链式存储结构——静态链表，创建，打印链表，增加删除结点

[toc]



## 1.  静态链表的存储结构

```c
typedef struct {
​     ElemType Data;
​     int Cur;
}StNode;
```

 

​	用数组的方式实现链表操作。该结构体用Cur代替链表的指针。

​	数组的第一个元素和最后一个元素，作为特殊的元素处理，不存储数据，其它每个结点的Cur存储的是下一个结点的下标。

**（****1****）头结点与头指针**

数组的最后一个元素的下标（下标是999）相当于链表的头指针，这个元素相当于单链表的头结点，它的Cur存的是第一个有数值的结点下标（下图是下标1）。

如下图所示，一共有数组有1000个元素，数组存有数据的有6个结点，数组的最后一个元素是头结点，它的Cur存储的是数组第一个有数据的结点（下图为下标1），数组第一个元素存储的是备用链表空闲空间的第一个下标（下图是下标7）.

![](D:\我的学习\学习笔记\C\Markdown\线性表链表\StaticLinkList02.jpg)

 <center>
     图1 静态链表示例
 </center>



**（****2****）空链表**

​	当头结点指向0时，即数组最后一个元素的Cur存的是0时，该静态链表为空链表，如下图所示。

![](D:\我的学习\学习笔记\C\Markdown\线性表链表\StaticLinkList01.jpg)

 <center>
     图2 空链表示例
 </center>



## 2 操作静态链表

​    创建，打印静态链表，增加减少结点。

**代码：**

```c
LIST_STATUS OperatorStaticLinkList(void) {
​     LIST_STATUS Status;    
​     StNode SL[MAXSIZE];
​     int StNodeNum = 5;

​     Status = CreateStaticLinkList(SL, StNodeNum);

​     if (SUCCESS == Status) {
​         printf("CreateStaticLinkList succeed!\n");
​     } else {
​         printf("CreateStaticLinkList failed!\n");
​     }

​     PrintStaticLinkList(SL);
}
```

 

## 3 创建静态链表

```c
LIST_STATUS CreateStaticLinkList(StNode SL[], int StNodeNum)
```

​     创建静态链表，数组长度为10，其中有数据的结点个数为StNodeNum。

**代码：**

```c
LIST_STATUS CreateStaticLinkList(StNode SL[], int StNodeNum) {
​     int i = 0;
    
​     printf("CreateStaticLinkList start\n");

​     if (NULL == SL || 0 == SL[0].Cur) {
​         return ERROR;
​     }

​     for (i = 0; i < MAXSIZE - 1 ; ++i) {       
​         if (i > 0 && i < StNodeNum + 1) {
​             SL[i].Data = i;
​         }
​         if (0 == i) {
​             SL[i].Cur = StNodeNum + 1;
​         } else {
​             SL[i].Cur = i + 1;
​         }
​     }

​     SL[StNodeNum].Cur = 0;
​     SL[MAXSIZE - 1].Cur = 1;

​     printf("CreateStaticLinkList end\n");

​     return SUCCESS;
}
```

**结果：**

> CreateStaticLinkList start
>
> CreateStaticLinkList end
>
> CreateStaticLinkList succeed!
>
> PrintStaticLinkList start
>
> SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> PrintStaticLinkList end 

## 4 打印静态链表

**代码：**

```c
LIST_STATUS PrintStaticLinkList(const StNode SL[]) {
​     int i = 0;
    
​     printf("PrintStaticLinkList start\n");
    
​     if (NULL == SL || 0 == SL[0].Cur || 0 == SL[MAXSIZE - 1].Cur) {
​         return ERROR;
​     }

​     if (0 == i) {
​         printf("SL[%d].Cur = %d\n", i, SL[i].Cur);
​     }

​     i = SL[MAXSIZE - 1].Cur;

​     while (i < MAXSIZE - 1) {
​         if (0 != SL[i].Cur) {
​             printf("SL[%d].Data = %d, SL[%d].Cur = %d\n", i, SL[i].Data, i, SL[i].Cur);
​         } else {
​             printf("SL[%d].Data = %d, SL[%d].Cur = %d\n", i, SL[i].Data, i, SL[i].Cur);
​             break;
​         }
​         i = SL[i].Cur;
​     }

​     printf("PrintStaticLinkList end\n");
}
```

