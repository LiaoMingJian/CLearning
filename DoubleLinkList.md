# 双向链表

[toc]



# 1 双向链表的存储结构

​    每个结点有一个都有指向前驱结点和后继结点的指针。

**代码：**

```c
#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			10

typedef int ElemType;
typedef int LIST_STATUS;

typedef struct _Double_link_Node {
	ElemType Data;
	struct _Double_link_Node *Next;
	struct _Double_link_Node *Prior;
}Double_Link_Node;
```

# 2 操作双向链表

```c
void OperateDoubleLinkList(void)
```

​	创建，打印，双向链表，并增加，删除结点

**代码：**

```c
/*DoubleLinkedList*/
void OperateDoubleLinkList(void) {
	Double_Link_Node *DoubleHead;
	LIST_STATUS Status;
	int CreateNum = 5;
	int AddNodeIndex = 2;
	int AddNodeData = 15;
	int DeleteNodeIndex = 3;

	DoubleHead = (Double_Link_Node *)malloc(sizeof(Double_Link_Node));
	
	Status = CreateDoubleLinkList(DoubleHead, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateDoubleLinkList succeed!\n");
	}
	else {
		printf("CreateDoubleLinkList failed!\n");
	}

	GetDoubleLinkListLenth(DoubleHead);
	PrintDoubleLinkList(DoubleHead);
	
	/*
	Status = AddDoubleLinkListNode(DoubleHead, AddNodeIndex, AddNodeData);
	if (SUCCESS == Status) {
		printf("AddDoubleLinkListNode succeed!\n");
	}
	else {
		printf("AddDoubleLinkListNode failed!\n");
	}
	*/

	/*
	Status = DeleteDoubleLinkListNode(DoubleHead, DeleteNodeIndex);
	if (SUCCESS == Status) {
		printf("DeleteDoubleLinkListNode succeed!\n");
	}
	else {
		printf("DeleteDoubleLinkListNode failed!\n");
	}
	*/

	Status = DeleteWholeDoubleLinkList(DoubleHead);
	if (SUCCESS == Status) {
		printf("DeleteWholeDoubleLinkList succeed!\n");
	}
	else {
		printf("DeleteWholeDoubleLinkList failed!\n");
	}

	GetDoubleLinkListLenth(DoubleHead);
	PrintDoubleLinkList(DoubleHead);
}
```

# 2 创建双向链表

```c
LIST_STATUS CreateDoubleLinkList(Double_Link_Node *DoubleHead, int CreateNum)
```

​    创建结点数为5（不包括头结点）的双向链表。

**代码：**

```c
LIST_STATUS CreateDoubleLinkList(Double_Link_Node *DoubleHead, int CreateNum) {
	int i = 0;	
	Double_Link_Node *CreateNode;
	Double_Link_Node *TraNode;

	printf("CreateDoubleLinkList start!\n");

	if (NULL == DoubleHead) {
		return ERROR;
	}

	/*Creat empty double link list*/
	DoubleHead->Data = CreateNum;
	DoubleHead->Next = NULL;
	DoubleHead->Prior = NULL;

	TraNode = DoubleHead;

	for (i = 1; i <= CreateNum; ++i) {
		CreateNode = (Double_Link_Node *)malloc(sizeof(Double_Link_Node));
		CreateNode->Data = i;

		CreateNode->Next = TraNode->Next;
		CreateNode->Prior = TraNode;
		TraNode->Next = CreateNode;

		TraNode = TraNode->Next;
	}

	printf("CreateDoubleLinkList end!\n");
	
	return SUCCESS;
}
```

 

**结果：**

> CreateDoubleLinkList start!
> CreateDoubleLinkList end!
> CreateDoubleLinkList succeed!
> DoubleLinkListLenth = 5
> CreateDoubleLinkList start!
> The Index = 0, TraNode = 0x986c58, TraNode->Data = 5, TraNode->Prior = 0x0, TraNode->Next = 0x986c90
> The Index = 1, TraNode = 0x986c90, TraNode->Data = 1, TraNode->Prior = 0x986c58, TraNode->Next = 0x985ed8
> The Index = 2, TraNode = 0x985ed8, TraNode->Data = 2, TraNode->Prior = 0x986c90, TraNode->Next = 0x985f10
> The Index = 3, TraNode = 0x985f10, TraNode->Data = 3, TraNode->Prior = 0x985ed8, TraNode->Next = 0x98f2f8
> The Index = 4, TraNode = 0x98f2f8, TraNode->Data = 4, TraNode->Prior = 0x985f10, TraNode->Next = 0x98f330
> The Index = 5, TraNode = 0x98f330, TraNode->Data = 5, TraNode->Prior = 0x98f2f8, TraNode->Next = 0x0
> CreateDoubleLinkList end!

 

# 3 打印双向链表

```c
LIST_STATUS PrintDoubleLinkList(Double_Link_Node * const DoubleHead)
```

**代码：**

```c
LIST_STATUS PrintDoubleLinkList(Double_Link_Node * const DoubleHead) {
	Double_Link_Node *TraNode;
	int TraIndex = 0;

	printf("CreateDoubleLinkList start!\n");

	if (NULL == DoubleHead) {
		return ERROR;	
	}

	TraNode = DoubleHead;

	while (TraNode != NULL) {
		printf("The Index = %d, TraNode = 0x%x, TraNode->Data = %d, TraNode->Prior = 0x%x, TraNode->Next = 0x%x\n", TraIndex, TraNode, TraNode->Data, TraNode->Prior, TraNode->Next);
		++TraIndex;

		TraNode = TraNode->Next;
	}

	printf("CreateDoubleLinkList end!\n\n");
}
```

# 4 获取双向链表长度

```c
int GetDoubleLinkListLenth(Double_Link_Node * const DoubleHead)
```

​    获取的双向链表的长度（不包含头结点）。

**代码：**

```c
int GetDoubleLinkListLenth(Double_Link_Node * const DoubleHead) {
	Double_Link_Node * TraNode;
	
	int DoubleLinkListLenth = 0;

	if (NULL == DoubleHead) {
		return 0;
	}
	
	if (NULL == DoubleHead->Next) {
		return 0;
	}
	
	TraNode = DoubleHead->Next;
	
	/*DoubleLinkListLenth is not incluede of DoubleHead*/
	while (TraNode != NULL) {
		++DoubleLinkListLenth;
		TraNode = TraNode->Next;
	}
	
	printf("DoubleLinkListLenth = %d\n", DoubleLinkListLenth);

	return DoubleLinkListLenth;
}
```

# 5 增加双向链表结点

```c
LIST_STATUS AddDoubleLinkListNode(Double_Link_Node *DoubleHead, int AddNodeIndex, int AddNodeData)
```

​	在链表第AddNodeIndex结点（不算头结点）的位置，插入一个结点。

**代码：**

```c
LIST_STATUS AddDoubleLinkListNode(Double_Link_Node *DoubleHead, int AddNodeIndex, int AddNodeData) {
	Double_Link_Node *AddNode;
	Double_Link_Node *TraNode;
	int TraIndex = 1;

	printf("AddDoubleLinkList start!\n");

	if (NULL == DoubleHead || AddNodeIndex < 1 || AddNodeIndex > GetDoubleLinkListLenth(DoubleHead) + 1) {
		return ERROR;	
	}

	TraNode = DoubleHead;
	
	printf("TraNode = 0x%x\n", TraNode);

	/*Find the previous node of AddNodeIndex*/
	for (TraIndex = 1; TraIndex <= AddNodeIndex - 1 ; ++TraIndex) {
		TraNode = TraNode->Next;
		printf("TraIndex = %d, TraNode = 0x%x\n", TraIndex, TraNode);
	}

	printf("TraIndex = %d, TraNode = 0x%x\n", TraIndex, TraNode);

	AddNode = (Double_Link_Node *)malloc(sizeof(Double_Link_Node));
	
	AddNode->Data = 15;
	AddNode->Next = TraNode->Next;
	AddNode->Prior = TraNode;

	TraNode->Next->Prior = AddNode;
	TraNode->Next = AddNode;

	DoubleHead->Data++;

	printf("AddDoubleLinkList end!\n");
	return SUCCESS;
}
```

**结果：**

> CreateDoubleLinkList start!
>
> CreateDoubleLinkList end!
>
> CreateDoubleLinkList succeed!
>
> DoubleLinkListLenth = 5
>
> CreateDoubleLinkList start!
>
> The Index = 0, TraNode = 0xc35ed8, TraNode->Data = 5, TraNode->Prior = 0x0, TraNode->Next = 0xc35f10
>
> The Index = 1, TraNode = 0xc35f10, TraNode->Data = 1, TraNode->Prior = 0xc35ed8, TraNode->Next = 0xc37600
>
> The Index = 2, TraNode = 0xc37600, TraNode->Data = 2, TraNode->Prior = 0xc35f10, TraNode->Next = 0xc37638
>
> The Index = 3, TraNode = 0xc37638, TraNode->Data = 3, TraNode->Prior = 0xc37600, TraNode->Next = 0xc37670
>
> The Index = 4, TraNode = 0xc37670, TraNode->Data = 4, TraNode->Prior = 0xc37638, TraNode->Next = 0xc3c738
>
> The Index = 5, TraNode = 0xc3c738, TraNode->Data = 5, TraNode->Prior = 0xc37670, TraNode->Next = 0x0
>
> CreateDoubleLinkList end!
>
>  
>
> AddDoubleLinkList start!
>
> DoubleLinkListLenth = 5
>
> TraNode = 0xc35ed8
>
> TraIndex = 1, TraNode = 0xc35f10
>
> TraIndex = 2, TraNode = 0xc35f10
>
> AddDoubleLinkList end!
>
> AddDoubleLinkListNode succeed!
>
> DoubleLinkListLenth = 6
>
> CreateDoubleLinkList start!
>
> The Index = 0, TraNode = 0xc35ed8, TraNode->Data = 6, TraNode->Prior = 0x0, TraNode->Next = 0xc35f10
>
> The Index = 1, TraNode = 0xc35f10, TraNode->Data = 1, TraNode->Prior = 0xc35ed8, TraNode->Next = 0xc3c770
>
> The Index = 2, TraNode = 0xc3c770, TraNode->Data = 15, TraNode->Prior = 0xc35f10, TraNode->Next = 0xc37600
>
> The Index = 3, TraNode = 0xc37600, TraNode->Data = 2, TraNode->Prior = 0xc3c770, TraNode->Next = 0xc37638
>
> The Index = 4, TraNode = 0xc37638, TraNode->Data = 3, TraNode->Prior = 0xc37600, TraNode->Next = 0xc37670
>
> The Index = 5, TraNode = 0xc37670, TraNode->Data = 4, TraNode->Prior = 0xc37638, TraNode->Next = 0xc3c738
>
> The Index = 6, TraNode = 0xc3c738, TraNode->Data = 5, TraNode->Prior = 0xc37670, TraNode->Next = 0x0
>
> CreateDoubleLinkList end!

# 6 删除双向链表结点

```c
LIST_STATUS DeleteDoubleLinkListNode(Double_Link_Node *DoubleHead, int DeleteNodeIndex)
```

​    将链表第DeleteNodeIndex个结点(不算头结点)删除。

**代码：**

```c
LIST_STATUS DeleteDoubleLinkListNode(Double_Link_Node *DoubleHead, int DeleteNodeIndex) {
	Double_Link_Node *TraNode;
	int TraIndex;

	printf("DeleteDoubleLinkListNode start!\n");

	if (NULL == DoubleHead || DeleteNodeIndex < 1 || DeleteNodeIndex > GetDoubleLinkListLenth(DoubleHead)) {
		return ERROR;	
	}

	TraNode = DoubleHead;

	for (TraIndex = 1; TraIndex <= DeleteNodeIndex; ++TraIndex) {
		TraNode = TraNode->Next;	
	}

	TraNode->Prior->Next = TraNode->Next;
	TraNode->Next->Prior = TraNode->Prior;		

	free(TraNode);
	DoubleHead->Data--;

	printf("DeleteDoubleLinkListNode start!\n");

	return SUCCESS;
}
```

**结果：**

> CreateDoubleLinkList start!
>
> CreateDoubleLinkList end!
>
> CreateDoubleLinkList succeed!
>
> DoubleLinkListLenth = 5
>
> CreateDoubleLinkList start!
>
> The Index = 0, TraNode = 0xc35ed8, TraNode->Data = 5, TraNode->Prior = 0x0, TraNode->Next = 0xc35f10
>
> The Index = 1, TraNode = 0xc35f10, TraNode->Data = 1, TraNode->Prior = 0xc35ed8, TraNode->Next = 0xc37600
>
> The Index = 2, TraNode = 0xc37600, TraNode->Data = 2, TraNode->Prior = 0xc35f10, TraNode->Next = 0xc37638
>
> The Index = 3, TraNode = 0xc37638, TraNode->Data = 3, TraNode->Prior = 0xc37600, TraNode->Next = 0xc37670
>
> The Index = 4, TraNode = 0xc37670, TraNode->Data = 4, TraNode->Prior = 0xc37638, TraNode->Next = 0xc3c738
>
> The Index = 5, TraNode = 0xc3c738, TraNode->Data = 5, TraNode->Prior = 0xc37670, TraNode->Next = 0x0
>
> CreateDoubleLinkList end!
>
>  
>
> AddDoubleLinkList start!
>
> DoubleLinkListLenth = 5
>
> TraNode = 0xc35ed8
>
> TraIndex = 1, TraNode = 0xc35f10
>
> TraIndex = 2, TraNode = 0xc35f10
>
> AddDoubleLinkList end!
>
> AddDoubleLinkListNode succeed!
>
> DoubleLinkListLenth = 6
>
> CreateDoubleLinkList start!
>
> The Index = 0, TraNode = 0xc35ed8, TraNode->Data = 6, TraNode->Prior = 0x0, TraNode->Next = 0xc35f10
>
> The Index = 1, TraNode = 0xc35f10, TraNode->Data = 1, TraNode->Prior = 0xc35ed8, TraNode->Next = 0xc3c770
>
> The Index = 2, TraNode = 0xc3c770, TraNode->Data = 15, TraNode->Prior = 0xc35f10, TraNode->Next = 0xc37600
>
> The Index = 3, TraNode = 0xc37600, TraNode->Data = 2, TraNode->Prior = 0xc3c770, TraNode->Next = 0xc37638
>
> The Index = 4, TraNode = 0xc37638, TraNode->Data = 3, TraNode->Prior = 0xc37600, TraNode->Next = 0xc37670
>
> The Index = 5, TraNode = 0xc37670, TraNode->Data = 4, TraNode->Prior = 0xc37638, TraNode->Next = 0xc3c738
>
> The Index = 6, TraNode = 0xc3c738, TraNode->Data = 5, TraNode->Prior = 0xc37670, TraNode->Next = 0x0
>
> CreateDoubleLinkList end!

# 6 删除整个双向链表

​    删除整个双向链表（除了头结点）。

**代码：**

```c
LIST_STATUS DeleteWholeDoubleLinkList(Double_Link_Node *DoubleHead) {
	Double_Link_Node *TraNode = DoubleHead->Next;
	Double_Link_Node *DeleteNode = TraNode;

	printf("DeleteWholeDoubleLinkList start!\n");

	if (NULL == DoubleHead) {
		return ERROR;
	}
	
	while (TraNode != NULL) {
		DeleteNode = TraNode;		
		TraNode = TraNode->Next;

		free(DeleteNode);
		DoubleHead->Data--;
	}

	if (DoubleHead->Data == 0) {
		DoubleHead->Next = NULL;
	}

	printf("DeleteWholeDoubleLinkList end!\n");

	return SUCCESS;
}

```

**结果：**

> CreateDoubleLinkList start!
>
> CreateDoubleLinkList end!
>
> CreateDoubleLinkList succeed!
>
> DoubleLinkListLenth = 5
>
> CreateDoubleLinkList start!
>
> The Index = 0, TraNode = 0xc90fc8, TraNode->Data = 5, TraNode->Prior = 0x0, TraNode->Next = 0xc86c58
>
> The Index = 1, TraNode = 0xc86c58, TraNode->Data = 1, TraNode->Prior = 0xc90fc8, TraNode->Next = 0xc86c90
>
> The Index = 2, TraNode = 0xc86c90, TraNode->Data = 2, TraNode->Prior = 0xc86c58, TraNode->Next = 0xc85ed8
>
> The Index = 3, TraNode = 0xc85ed8, TraNode->Data = 3, TraNode->Prior = 0xc86c90, TraNode->Next = 0xc85f10
>
> The Index = 4, TraNode = 0xc85f10, TraNode->Data = 4, TraNode->Prior = 0xc85ed8, TraNode->Next = 0xc8c4e0
>
> The Index = 5, TraNode = 0xc8c4e0, TraNode->Data = 5, TraNode->Prior = 0xc85f10, TraNode->Next = 0x0
>
> CreateDoubleLinkList end!
>
>  
>
> DeleteWholeDoubleLinkList start!
>
> DeleteWholeDoubleLinkList end!
>
> DeleteWholeDoubleLinkList succeed!
>
> CreateDoubleLinkList start!
>
> The Index = 0, TraNode = 0xc90fc8, TraNode->Data = 0, TraNode->Prior = 0x0, TraNode->Next = 0x0
>
> CreateDoubleLinkList end!