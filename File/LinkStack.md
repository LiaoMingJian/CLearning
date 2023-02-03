#  链栈之创建，打印，进栈与出栈——C语言描述

[toc]



## 1 链栈的存储结构

​    链表的头结点作为栈顶。

**代码：**

```c
#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			5

typedef int ElemType;
typedef int LIST_STATUS;

typedef struct _Node {
	ElemType Data;
	struct _Node *Next;
}Node;

typedef struct _LINK_STACK {
	Node * Top;
	int Count;
}_LINK_STACK;

```

 

## 2  操作链栈

```c
void OperateLinkStack(void)
```

​	创建，打印，进栈，出栈

**代码：**

```c
void OperateLinkStack(void) {
	LIST_STATUS Status;
	LINK_STACK *LinkStack = (LINK_STACK *)malloc(sizeof(LINK_STACK));
	Node *LinkHead = (Node *)malloc(sizeof(Node));
	int CreateNum = 4;
	int PushData = 5;
	int *PopData = (int *)malloc(sizeof(int));
	
	Status = CreateLinkStack(LinkStack, LinkHead, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateLinkStack succeed!\n");
	}
	else {
		printf("CreateLinkStack failed!\n");
	}

	PrintLinkStack(LinkStack);

	/*
	Status = PushLinkStack(LinkStack, PushData);
	if (SUCCESS == Status) {
		printf("PushLinkStack succeed!\n");
	}
	else {
		printf("PushLinkStack failed!\n");
	}
	*/

	Status = PopLinkStack(LinkStack, PopData);
	if (SUCCESS == Status) {
		printf("PopLinkStack succeed!\n");
		printf("*PopData = %d\n", *PopData);
	}
	else {
		printf("PopLinkStack failed!\n");
	}

	PrintLinkStack(LinkStack);
}

```

 

## 3  创建链栈

```c
LIST_STATUS CreateLinkStack(LINK_STACK *LinkStack, Node *LinkHead, int CreateNum)
```

​     创建结点个数为CreateNum（包括头结点）的链栈。

**代码：**

```c
LIST_STATUS CreateLinkStack(LINK_STACK *LinkStack, Node *LinkHead, int CreateNum) {
	LINK_STACK *TraStack = LinkStack;
	Node *TraNode = LinkHead;
	Node *CreateNode;
	int TraIndex = 0;
	
	printf("CreateLinkStack start\n");

	if (NULL == LinkStack || NULL == LinkHead) {
		return ERROR;
	}

	/*Create empty link*/
	LinkHead->Data = 4;
	LinkHead->Next = NULL;

	LinkStack->Top = LinkHead;
	LinkStack->Count = CreateNum;
	
	for (TraIndex = 1; TraIndex <= CreateNum - 1; ++TraIndex) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = TraIndex;

		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		TraNode = TraNode->Next;
	}

	printf("CreateLinkStack end\n");
	return SUCCESS;
}

```

**结果：**

> CreateLinkStack start
>
> CreateLinkStack end
>
> CreateLinkStack succeed!
>
> PrintLinkStack start
>
> LinkStack->Top = 0x12e0508
>
> LinkStack->Count = 4
>
> TraStackNode = 0x12e0508, TraStackNode->Data = 4
>
> TraStackNode = 0x12e6cc0, TraStackNode->Data = 1
>
> TraStackNode = 0x12e6cf8, TraStackNode->Data = 2
>
> TraStackNode = 0x12e5f40, TraStackNode->Data = 3
>
> PrintLinkStack end

 

## 4  打印链栈

```c
LIST_STATUS PrintLinkStack(LINK_STACK * const LinkStack)
```

**代码：**

```c
LIST_STATUS PrintLinkStack(LINK_STACK * const LinkStack) {
	Node *TraStackNode;

	printf("PrintLinkStack start\n");

	if (NULL == LinkStack || NULL == LinkStack->Top) {
		return ERROR;
	}

	printf("LinkStack->Top = 0x%x\n", LinkStack->Top);
	printf("LinkStack->Count = %d\n", LinkStack->Count);

	TraStackNode = LinkStack->Top->Next;

	while (TraStackNode != NULL) {
		printf("TraStackNode = 0x%x, TraStackNode->Data = %d\n", TraStackNode, TraStackNode->Data);
		TraStackNode = TraStackNode->Next;
	}

	printf("PrintLinkStack end\n");
	return SUCCESS;
}

```

 

## 5  链栈——进栈

```c
LIST_STATUS PushLinkStack(LINK_STACK *LinkStack, int PushData)
```

​	进栈，在栈顶插入结点。

**代码：**

```c
LIST_STATUS PushLinkStack(LINK_STACK *LinkStack, int PushData) {
	LINK_STACK *TraLinkStack = LinkStack;
	Node *PushNode;

	printf("PushLinkStack start\n");

	if (NULL == LinkStack || NULL == LinkStack->Top ) {
		return ERROR;	
	}

	PushNode = (Node *)malloc(sizeof(Node));
	PushNode->Data = PushData;
	PushNode->Next = TraLinkStack->Top;

	TraLinkStack->Top = PushNode;
	TraLinkStack->Count++;

	printf("PushLinkStack end\n");
	return SUCCESS;
}

```

**结果：**

>  CreateLinkStack start
>
> CreateLinkStack end
>
> CreateLinkStack succeed!
>
> PrintLinkStack start
>
> LinkStack->Top = 0xd570b0
>
> LinkStack->Count = 4
>
> TraStackNode = 0xd570b0, TraStackNode->Data = 4
>
> TraStackNode = 0xd56cc0, TraStackNode->Data = 1
>
> TraStackNode = 0xd56cf8, TraStackNode->Data = 2
>
> TraStackNode = 0xd55f40, TraStackNode->Data = 3
>
> PrintLinkStack end
>
>  
>
> PushLinkStack start
>
> PushLinkStack end
>
> PushLinkStack succeed!
>
> PrintLinkStack start
>
> LinkStack->Top = 0xd55f78
>
> LinkStack->Count = 5
>
> TraStackNode = 0xd55f78, TraStackNode->Data = 5
>
> TraStackNode = 0xd570b0, TraStackNode->Data = 4
>
> TraStackNode = 0xd56cc0, TraStackNode->Data = 1
>
> TraStackNode = 0xd56cf8, TraStackNode->Data = 2
>
> TraStackNode = 0xd55f40, TraStackNode->Data = 3
>
> PrintLinkStack end

## 6  链栈——出栈

```c
LIST_STATUS PopLinkStack(LINK_STACK *LinkStack, int *PopData) 
```

**代码：**

```c
LIST_STATUS PopLinkStack(LINK_STACK *LinkStack, int *PopData) {
	LINK_STACK *TraLinkStack = LinkStack;
	LINK_STACK *DeleteNode;

	printf("PopLinkStack start\n");

	if (NULL == LinkStack || NULL == LinkStack->Top) {
		return ERROR;
	}

	*PopData = TraLinkStack->Top->Data;

	DeleteNode = TraLinkStack->Top;
	TraLinkStack->Top = TraLinkStack->Top->Next;
	TraLinkStack->Count--;
	free(DeleteNode);

	printf("PopLinkStack end\n");
	return SUCCESS;
}

```

**结果：**

> CreateLinkStack start
>
> CreateLinkStack end
>
> CreateLinkStack succeed!
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf86cf8
>
> LinkStack->Count = 4
>
> TraStackNode = 0xf86cf8, TraStackNode->Data = 4
>
> TraStackNode = 0xf85f70, TraStackNode->Data = 1
>
> TraStackNode = 0xf85fa8, TraStackNode->Data = 2
>
> TraStackNode = 0xf8c5a0, TraStackNode->Data = 3
>
> PrintLinkStack end
>
>  
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack succeed!
>
> *PopData = 4
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf85f70
>
> LinkStack->Count = 3
>
> TraStackNode = 0xf85f70, TraStackNode->Data = 1
>
> TraStackNode = 0xf85fa8, TraStackNode->Data = 2
>
> TraStackNode = 0xf8c5a0, TraStackNode->Data = 3
>
> PrintLinkStack end