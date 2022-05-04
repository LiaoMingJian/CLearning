# 链表的创建，节点增加，删除，逆转——C语言描述

[toc]



# 1. 链表的结构

**（1）链表的结构图**

​	如图所示，三个节点，每个节点都有数据（data）和指针，前两个节点的指针都指向下一个节点的的首地址，尾节点指向NULL，这就形成了一个链表。

![img](file:///C:/Users/74140/AppData/Local/Temp/msohtmlclip1/01/clip_image002.png)

 

# 2. 链表的创建

**例子1：**创建上图的链表。

**方法：**三个节点都给出来

```c
void TestLink() {
​     typedef struct MyNode{
​          int Date;
​          struct MyNode *Next;
​     }Node;
    
​     //Node N1, N2, N3;       
​     Node N1;
​     Node N2;
​     Node N3;
    
​     Node *PN = NULL;
​     N1.Date = 1;
​     N1.Next = &N2;
​     N2.Date = 2;
​     N2.Next = &N3;
​     N3.Date = 3;
​     N3.Next = NULL;   
    
​     PN = &N1;
​     while (PN != NULL) {
​          printf("Node.Date = %d\n", PN->Date);
​          PN = PN->Next;
​     }
}
```

**结果：**

> Node.Date = 1
>
> Node.Date = 2
>
> Node.Date = 3

 

**例子2**：简化的写法

```c
void TestCreateLink02() {
​     typedef struct MyNode {
​          int Date;
​          struct MyNode *Next;
​     }Node;
    
​     Node N3 = {3, NULL};
​     Node N2 = {2, &N3};
​     Node N1 = {1, &N2};
​     Node *PN = NULL;

​     for (PN = &N1; PN != NULL; PN = PN->Next) {
​          printf("Node.Date = %d\n", PN->Date);   
​     }
}
```

**结果：**

> Node.Date = 1
>
> Node.Date = 2
>
> Node.Date = 3

 

# 3. 链表的操作

​	操作链表的节点。

**例子：**创建一个链表，操作链表的具体实现在其它函数中.

**代码：**

```c
//Create link
typedef struct Node {
​     int Data;
​     struct Node *Next;
}MyNode;

void OperateLink() {
​     MyNode N3 = { 3, NULL };
​     MyNode N2 = { 2, &N3 };
​     MyNode N1 = { 1, &N2 };
​     MyNode *PN = NULL;   
​     MyNode *PNReturnHeadNode = NULL;
​     MyNode HeadNode = {0, NULL};
​     MyNode TailNode = { 4, NULL };
​     MyNode MiddleNode = {23, NULL};
​     int DeleteDate = 2;

      //Print link
​     printf("Print the created link:\n");
​     for (PN = &N1; PN != NULL; PN = PN->Next) {
​          printf("Node.Data = %d\n", PN->Data);
​     }
    
​     //Add head node
​     //PNReturnHeadNode = AddHeadNode(&N1, &HeadNode);
    
​     //Add tail node
​     //PNReturnHeadNode = AddTailNode(&N1, &TailNode);

​     //Add middle node
​     PNReturnHeadNode = TestAddMiddleNode(&N1, &N2, &MiddleNode);
    
​     //Delete head node
​     //PNReturnHeadNode = DeleteHeadNode(&N1);

​     //Delete tail node
​     //PNReturnHeadNode = DeleteTailNode(&N1);

​     //Delete middle node
​     //PNReturnHeadNode = DeletMiddleNode(&N1, DeleteDate);

​     //Reverse link
​     //PNReturnHeadNode = ReverseLink(&N1);

​     //Printf link
​     if (NULL != PNReturnHeadNode) {
​          printf("Operate succeed!\n");
​          printf("Print operated link:\n");
​          for (PN = PNReturnHeadNode; PN != NULL; PN = PN->Next) {
​              printf("Node.Data = %d\n", PN->Data);
​          }
​     } else {
​          printf("Operate filed!\n");
​     }
}
```

# 4. 链表节点的插入

**（1）头插**

**例子：**链表头插入节点N0

**方法：**直接将N0的next指针N1;

**代码：**

```c
MyNode* AddHeadNode(MyNode *LNode, MyNode *HeadNode) {
​     //Judge node
​     if (NULL == LNode) {
​          if (NULL == HeadNode) {
​              return NULL;
​          } else {        
​              return HeadNode;
​          }
​     }
    
​     //Add head node
​     HeadNode->Next = HeadNode;
​     return HeadNode;
}
```

**结果：**

> Print the created link:
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3
>
> Operate succeed!
>
> Print operated link:
>
> Node.Data = 0
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3

**（2）尾插**

**例子：**链表尾部插入节点N4。

**方法：**先移动指针到最后一个节点（N3），然后把N3的指针指向N4，把N4指向NULL.

**代码：**

```c
MyNode* AddTailNode(MyNode *LNode, MyNode *TailNode) {
​     MyNode *PN = NULL;
    
​     //Judge node
​     if (NULL == LNode) {
​          if (NULL == TailNode) {
​              return NULL;
​          } else {
​              return TailNode;
​          }
​     }
    
​     //Move PN to N3
​     for (PN = LNode; PN->Next != NULL; PN = PN->Next) {
​     }

​     //Add TailNode
​     if (PN->Next == NULL) {
​          PN->Next = TailNode;
​          PN->Next->Next = NULL;
​     }
    
​     return LNode;
}
```

**结果：**

> Print the created link:
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3
>
> Operate succeed!
>
> Print operated link:
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3
>
> Node.Data = 4
>
>  

**（3）中间插**

**例子：**在链表的N2和N3中间插入节点N23

**方法：**N2指针指向N23，N23指向N3.

**代码：**

```c
MyNode* TestAddMiddleNode(MyNode *LNode, MyNode *PreNode, MyNode *MiddleNode) {
​     MyNode *PN = NULL;
​     MyNode *PNTemp = NULL;

      //Judge
​     if (NULL == LNode) {
​          return MiddleNode;
​     }

​     //Move PN to PreNode
​     for (PN = LNode; PN->Next != PreNode; PN = PN->Next) {
​     }

​     //Add MiddleNode
​     if (PN->Next == PreNode) {
​          PNTemp = PN->Next;
​          PN->Next = MiddleNode;
​          PN->Next->Next = PNTemp;
​     }
}
```

**结果：**

> Print the created link:
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3
>
> Operate succeed!
>
> Print operated link:
>
> Node.Data = 1
>
> Node.Data = 23
>
> Node.Data = 2
>
> Node.Data = 3

# 5  链表节点的删除

**（1）头删**

**例子：**删除头节点N1

**方法：**将N1的Next指针置NULL

**代码：**

```c
MyNode* DeleteHeadNode(MyNode *LNode) {
​     MyNode *PNRt = NULL; 

      //Judge LNode
​     if (LNode == NULL) {
​          return NULL;  
​     } else if(LNode->Next == NULL) {
​          return LNode;
​     }    

​     //Delete head node
​     PNRt = LNode->Next;
​     LNode->Next = NULL;
​     return PNRt;
}
```

**结果：**

> Print the created link:
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3
>
> Operate succeed!
>
> Print operated link:
>
> Node.Data = 2
>
> Node.Data = 3
>
>  

**（2）尾删**

**例子：**删除N3

**方法：**N2的Next指针指向NULL

**代码：**

```c
MyNode* DeleteTailNode(MyNode *LNode) {
​     MyNode *PNtemp = LNode;   
​     
     //Judge LNode
​     if (NULL == LNode ) {
​          return NULL;
​     } else if(NULL == LNode->Next) {
​          return LNode;
​     }
    
​     //Move PNRt to N2
​     for (PNtemp = LNode; PNtemp->Next->Next != NULL; PNtemp = PNtemp->Next) {
​     }

​     //Delete tail node
​     PNtemp->Next = NULL;

​     return LNode;
}
```

**结果：**

> Print the created link:
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3
>
> Operate succeed!
>
> Print operated link:
>
> Node.Data = 1
>
> Node.Data = 2
>
>  

**（3）中间删除**

**例子：**删除N2

**方法：**N1的Next指针指向N3，N2的Next指针置NULL

**代码：**

```c
MyNode* DeletMiddleNode(MyNode *LNode, int DeleteDate) {
​     MyNode *PN = LNode;
​     MyNode *PNTemp = NULL;

​     //Judge node
​     if (NULL == LNode) {
​          return NULL;
​     }else if (NULL == LNode->Next) {
​          return LNode;
​     }

​     //Move PN to N1
​     for (PN = LNode; PN->Next->Data != DeleteDate; PN = PN->Next) { 
​     }
   
​     //Delete N2
​     PNTemp = PN->Next;
​     PN->Next = PN->Next->Next;
​     PNTemp->Next = NULL;
​     
​     return LNode;
}
```

**结果：**

> Print the created link:
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3
>
> Operate succeed!
>
> Print operated link:
>
> Node.Data = 1
>
> Node.Data = 3
>
>  

# 6 链表逆序

**例子：**将N1->N2->N3改成N3->N2->N1

**方法：**最小重复操作：循环体只完成两个节点的逆序操作。双指针法：PCur为当前的节点，PNext为后继节点，PTemp存PNext->Next。完成一次逆转后（PNext->Next = PCur），PCur与PNext向前面迭代（PCur = PNext, PNext = PTemp）。当PNext 为NULL停止循环。

**代码：**

```c
MyNode* ReverseLink(MyNode *LNode) {
​     MyNode *PCur = NULL;
​     MyNode *PNext = NULL;
​     MyNode *PTemp = NULL;

​     if (NULL == LNode) {
​          return NULL;
​     } else if (NULL == LNode->Next) {
​          return LNode;
​     }

​     PCur = NULL;
​     PNext = LNode; 
​     while (PNext != NULL) {
​          PTemp = PNext->Next;        
​          //Reverse
​          PNext->Next = PCur;
​          //Iterate
​          PCur = PNext;
​          PNext = PTemp;         
​     }

​     return PCur;
}
```

**结果：**

> Print the created link:
>
> Node.Data = 1
>
> Node.Data = 2
>
> Node.Data = 3
>
> Operate succeed!
>
> Print operated link:
>
> Node.Data = 3
>
> Node.Data = 2
>
> Node.Data = 1
