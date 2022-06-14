

###  线性表的链式存储结构（链表结点创建，增加，删除）

[toc]



#### 1  头指针与头结点

​    头指针是链表的必须要素，指针指向链表第一个结点。头结点是链表的非必要元素，头结点的数据可存链表的长度，指针指向链表的第一个节点。

#### 2  空链表

​    头指针指向头节点，头结点的指针域指向NULL.

#### 3  链表的存储结构

```c
typedef struct _Node {
​     ElemType Data;
​     struct _Node *Next;
}Node;


typedef struct _Node *LinkList;
```

 

#### 4 链表的操作

​	操作链表的创建，插入，删除。

**代码：**

```c
LIST_STATUS OperateLinkList(void) {
	LinkList L = NULL;
	LIST_STATUS Status;
	unsigned int n = 5;
	unsigned int AddIndex = 4;
	int AddNodeData = 25;
	unsigned int DeleteIndex = 4;

	LinkList RevList;

	L = (LinkList)malloc(sizeof(Node));

	/*
	Status = CreatLinkListHead(L, n);
	if (SUCCESS == Status) {
		printf("CreatLinkListHead succeed!\n");
	} else {
		printf("CreatLinkListHead filed!\n");
	}
	*/

	Status = CreatLinkListTail(L, n);
	if (SUCCESS == Status) {
		printf("CreatLinkListTail succeed!\n");
	} else {
		printf("CreatLinkListTail filed!\n");
	}

	PrintLinkList(L);

	/*
	Status = DeleteLinkList(L);
	if (SUCCESS == Status) {
		printf("DeleteLinkList succeed!\n");
	}
	else {
		printf("DeleteLinkList filed!\n");
	}
	*/

	/*
	Status = AddLinkListNode01(L, AddIndex, AddNodeData);
	if (SUCCESS == Status) {
		printf("AddLinkListNode01 succeed!\n");
	} else {
		printf("AddLinkListNode01 filed!\n");
	}
	*/

	/*
	Status = AddLinkListNode02(L, AddIndex, AddNodeData);
	if (SUCCESS == Status) {
		printf("AddLinkListNode02 succeed!\n");
	}
	else {
		printf("AddLinkListNode02 filed!\n");
	}
	*/

	/*
	Status = DeleteLinkListNode(L, DeleteIndex);
	if (SUCCESS == Status) {
		printf("DeleteLinkListNode succeed!\n");
	}
	else {
		printf("DeleteLinkListNode filed!\n");
	}
	*/

	RevList = ReverseLinkListNode(L);

	PrintLinkList(RevList);
}
```



#### 5  单链表打印的输出

```c
LIST_STATUS PrintLinkList(const LinkList L)
```

**输入：**链表头指针

**代码：**

```c
LIST_STATUS PrintLinkList(const LinkList L) {    
​     LinkList Temp;
    
​     printf("PrintLinkList start\n");
​     Temp = L;

​     if (NULL == L) {
​         return ERROR;
​     }

​     while (Temp != NULL) {
​         printf("L->Data = %d\n", Temp->Data);
​         Temp = Temp->Next;
​     }

​     printf("PrintLinkList end\n");
​     return SUCCESS;
}
```

 

#### 6  单链表整表创建

```c
LIST_STATUS CreatLinkListHead(const LinkList L, int n)
```

**输入：**头指针L，和需要创建的结点的个数n的链表。头结点的数据存的为链表的长度。

**方法****1****：头插法**

**分析：**先创建一个头结点，使用循环的方式创建剩下的结点，每个新加入的结点都插入到头结点后面。

**代码：**

```c
LIST_STATUS CreatLinkListHead(const LinkList L, int n) {
​     int i;
​     LinkList AddNode;
​     LinkList Temp;
​     Temp = L;

​     printf("CreatLinkListHead start\n");

​     if (NULL == Temp) {
​         return ERROR; 
​     }

​     /*Create Head node*/
​     Temp->Data = n;
​     Temp->Next = NULL;

​     /*Create remaining node*/
​     for (i = 0; i < n; ++i) {
​         AddNode = (LinkList)malloc(sizeof(Node));
​         AddNode->Data = i;
​         AddNode->Next = Temp->Next;
​         Temp->Next = AddNode;
​     }
    
​     printf("CreatLinkListHead end\n");
​     return SUCCESS;
}
```

 

**结果：**

> CreatLinkListHead start
>
> CreatLinkListHead end
>
> CreatLinkListHead succeed!
>
> PrintLinkList start
>
> L->Data = 5
>
> L->Data = 4
>
> L->Data = 3
>
> L->Data = 2
>
> L->Data = 1
>
> L->Data = 0
>
> PrintLinkList end

 

**方法****2****：尾插法**

```c
LIST_STATUS CreatLinkListTail(const LinkList L, int n)
```

**分析：**先创建一个头结点，使用循环的方式创建剩下的结点，每个新加入的结点插到最后。也类似双指针法，前面的指针在插入结点之后，往前面迭代

**代码：**

```c
LIST_STATUS CreatLinkListTail(const LinkList L, int n) {
​     LinkList AddNode;
​     LinkList Temp;
​     int i = 0;

​     printf("CreatLinkListTail start\n");

​     if (NULL == L) {
​         return ERROR;
​     }

​     Temp = L;

​     /*Create head node*/
​     Temp->Data = n;
​     Temp->Next = NULL;

​     /*Create remaining node*/
​     for (i = 0; i < n; ++i) {
​         AddNode = (LinkList)malloc(sizeof(Node));
​         AddNode->Data = i;​         
​         AddNode->Next = NULL;     
​         Temp->Next = AddNode;​         
​         Temp = Temp->Next;     
​     }
​    
​     printf("CreatLinkListTail end\n");
}
```

**结果：**

> CreatLinkListTail start
>
> CreatLinkListTail end
>
> CreatLinkListTail filed!
>
> PrintLinkList start
>
> L->Data = 5
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 2
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end

 

#### 7 单链表整表的删除

**输入：**链表的头指针

**分析：**按顺序释放结点。并将头结点置为NULL

**代码：**

```c
LIST_STATUS DeleteLinkList(LinkList L) {
​     LinkList DeleteNode;
​     LinkList DeleteNodeTemp;
​     printf("DeleteLinkList start\n");

​     if (NULL == L) {
​         return ERROR; 
​     } 

​     DeleteNode = L->Next;

​     while (NULL != DeleteNode) {
​         DeleteNodeTemp = DeleteNode->Next;
​         free(DeleteNode);
​         DeleteNode = DeleteNodeTemp;
​     }
​     
​     L->Data = 0;
​     L->Next = NULL;

​     printf("DeleteLinkList end\n");
​     return SUCCESS;
}
```

**结果：**

> CreatLinkListTail start
>
> CreatLinkListTail end
>
> CreatLinkListTail filed!
>
> PrintLinkList start
>
> L->Data = 5
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 2
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end
>
> DeleteLinkList start
>
> DeleteLinkList end
>
> DeleteLinkList succeed!
>
> PrintLinkList start
>
> L->Data = 0
>
> PrintLinkList end

 

#### 8  增加链表的结点

```c
AddLinkListNode01(const LinkList L, const unsigned int AddIndex, const int AddNodeData)
```

**问题：**在链表的第AddIndex个结点（包括头结点）后插入一个结点AddNode

**情况****1****：**头结点的数据域存的是链表的长度

**分析：**

\1.   判断AddIndex是否合法，当插入的位置小于1或者大于总数n+1时，为非法参数

\2.   遍历到对应的位置

\3.   插入数据，增加长度

**代码：**

```c
LIST_STATUS AddLinkListNode01(const LinkList L, const unsigned int AddIndex, const int AddNodeData) {
​     unsigned int i = 0;
​     LinkList AddNode;
​     LinkList Temp;
​     int n;

​     printf("AddLinkListNode01 start\n");
    
​     Temp = L;
​     n = Temp->Data;

​     if ((NULL == Temp) || (AddIndex < 1) || (AddIndex > Temp->Data + 1)) {
​         return ERROR; 
​     }

​     for (i = 0; i < n + 1; ++i) {
​         if ((i + 1) == AddIndex) {
​             AddNode = (LinkList)malloc(sizeof(LinkList));
​             AddNode->Data = AddNodeData;
​             AddNode->Next = Temp->Next;
​             Temp->Next = AddNode;
​              L->Data += 1;
​         }    

​         Temp = Temp->Next;
​     }

​     printf("AddLinkListNode01 end\n");
​     return SUCCESS;
}
```

 

**结果：**

> CreatLinkListTail start
>
> CreatLinkListTail end
>
> CreatLinkListTail filed!
>
> PrintLinkList start
>
> L->Data = 5
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 2
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end
>
> AddLinkListNode01 start
>
> AddLinkListNode01 end
>
> AddLinkListNode01 succeed!
>
> PrintLinkList start
>
> L->Data = 5
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 2
>
> L->Data = 25
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end



**情况****2****：**事先不知道头结点的长度

**分析：**

\4.   判断AddIndex是否合法，当插入的位置小于1或者大于总数n+1时，为非法参数

\5.   遍历到对应的位置

\6.   插入数据，增加长度

 

**代码：**

```c
LIST_STATUS AddLinkListNode02(const LinkList L, const unsigned int AddIndex, const int AddNodeData) {
​     unsigned int i = 1;
​     LinkList AddNode;
​     LinkList Temp;

​     printf("AddLinkListNode02 start\n");
​     Temp = L;

​     if ((NULL == Temp) || (AddIndex < 1)) {
​         return ERROR;
​     }

​     while (AddIndex != i && NULL != Temp) {
​         printf("Temp = 0x%x\n", Temp);
​         Temp = Temp->Next;
​         ++i;
​     }

​     if (NULL == Temp) {
​         printf("AddIndex is invalid\n");
​         return ERROR; 
​     }
    
​     AddNode = (LinkList)malloc(sizeof(LinkList));
​     AddNode->Data = AddNodeData;
​     AddNode->Next = Temp->Next;
​     Temp->Next = AddNode;
​     L->Data += 1;

​     printf("AddLinkListNode02 end\n");
​     return SUCCESS;
}
```

**结果：**

> CreatLinkListTail start
>
> CreatLinkListTail end
>
> CreatLinkListTail filed!
>
> PrintLinkList start
>
> L->Data = 5
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 2
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end
>
> AddLinkListNode02 start
>
> Temp = 0xe55d08
>
> Temp = 0xe55d40
>
> Temp = 0xe56fb0
>
> AddLinkListNode02 end
>
> AddLinkListNode02 succeed!
>
> PrintLinkList start
>
> L->Data = 6
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 2
>
> L->Data = 25
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end

 

#### 9 删除链表的结点

```c
DeleteLinkListNode(const LinkList L, const unsigned int DeleteIndex)
```

**问题：**在链表的第AddIndex个结点（包括头结点）后插入一个结点AddNode

**分析：**

\7.   判断AddIndex是否合法，当插入的位置小于1时，为非法参数

\8.   遍历到对应的位置

\9.   删除结点，减少链表长度

 

**代码：**

```c
LIST_STATUS DeleteLinkListNode(const LinkList L, const unsigned int DeleteIndex) {
​     int i = 1;
​     LinkList Temp;
​     LinkList DeleteNode;

​     printf("DeleteLinkListNode start\n");

​     if (NULL == L || DeleteIndex < 1) {
​         return ERROR;
​     }

​     Temp = L;

​     while ((i < DeleteIndex - 1) && (NULL != Temp)) {
​         ++i;
​         Temp = Temp->Next;
​     }

​     if (NULL == Temp) {
​         printf("DeleteIndex is invalid\n");
​         return ERROR;
​     }

​     DeleteNode = Temp->Next;
​     Temp->Next = DeleteNode->Next;
​     DeleteNode->Next = NULL;
​     free(DeleteNode);
​     L->Data -= 1;

​     printf("DeleteLinkListNode end\n");
​     return SUCCESS;
}
```

**结果：**

> CreatLinkListTail start
>
> CreatLinkListTail end
>
> CreatLinkListTail filed!
>
> PrintLinkList start
>
> L->Data = 5
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 2
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end
>
> DeleteLinkListNode start
>
> DeleteLinkListNode end
>
> DeleteLinkListNode succeed!
>
> PrintLinkList start
>
> L->Data = 4
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end



#### 5.3.3.7 链表逆转

**输入：**链表的头指针

**分析：**双指针法。一个指向一个结点，一个指向当前结点，完成逆转后，不断往前移动。

**代码：**

```c
LinkList ReverseLinkListNode(const LinkList L) {
​     LinkList Pre, Cur, Temp, Temp02;
    
​     printf("ReverseLinkListNode start\n");
​     if (NULL == L || NULL == L->Next) {
​         return NULL;
​     }
    
​     Pre = NULL;
​     Cur = L;

​     while (Cur != NULL) {
​         Temp = Cur->Next;
    
​         Cur->Next = Pre;
    
​         Pre = Cur;
​         Cur = Temp;
​     }

     printf("ReverseLinkListNode end\n");
    
​     return Pre;
}
```

 

**结果：**

> CreatLinkListTail start
>
> CreatLinkListTail end
>
> CreatLinkListTail filed!
>
> PrintLinkList start
>
> L->Data = 5
>
> L->Data = 0
>
> L->Data = 1
>
> L->Data = 2
>
> L->Data = 3
>
> L->Data = 4
>
> PrintLinkList end
>
> ReverseLinkListNode start
>
> PrintLinkList start
>
> L->Data = 4
>
> L->Data = 3
>
> L->Data = 2
>
> L->Data = 1
>
> L->Data = 0
>
> L->Data = 5
>
> PrintLinkList end

