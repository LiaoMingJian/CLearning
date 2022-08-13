#  队列的链式存储结构——链队列——C语言描述

[toc]

​	相当于单链表，入队尾插，出队头删.

# 1.操作链队列

​	创建，打印，入队，出队，清除队列。

代码：

```c
void OperateLinkQueue(void) {
	LINK_QUEUE *LinkQueue = (LINK_QUEUE *)malloc(sizeof(LINK_QUEUE));
	LIST_STATUS Status;

	int CreateNum = 3;
	int AddData = 4;
	int *DelData = (int *)malloc(sizeof(int));

	/*Create empty linkQueue*/
	Node *HeadNode = (Node *)malloc(sizeof(Node));
	HeadNode->Data = CreateNum;
	HeadNode->Next = NULL;
	LinkQueue->Front = HeadNode;
	LinkQueue->Rear = HeadNode;

	Status = CreateLinkQueue(LinkQueue, HeadNode, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateLinkQueue succeed!\n");
	}
	else {
		printf("CreateLinkQueue failed!\n");
	}
	
	PrintLinkQueue(LinkQueue);

	
	Status = EnterLinkQueue(LinkQueue, AddData);
	if (SUCCESS == Status) {
		printf("EnterLinkQueue succeed!\n");
	}
	else {
		printf("EnterLinkQueue failed!\n");
	}
	
	PrintLinkQueue(LinkQueue);
	

	/*
	Status = ExitLinkQueue(LinkQueue, DelData);
	if (SUCCESS == Status) {
		printf("ExitLinkQueue succeed!\n");
	}
	else {
		printf("ExitLinkQueue failed!\n");
	}

	PrintLinkQueue(LinkQueue);
	*/

	/*
	Status = DelLinkQueue(LinkQueue, HeadNode);
	if (SUCCESS == Status) {
		printf("DelLinkQueue succeed!\n");
	}
	else {
		printf("DelLinkQueue failed!\n");
	}

	PrintLinkQueue(LinkQueue);
	*/

	free(LinkQueue);
	free(DelData);
	free(HeadNode);

	LinkQueue = NULL;
	DelData = NULL;
	HeadNode = NULL;
}
```

# 2.创建链队列

​     创建结点数为3的链队列

**代码：**

```c
LIST_STATUS CreateLinkQueue(LINK_QUEUE *LinkQueue, Node *HeadNode, int CreateNum) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *TraNode = HeadNode;
	Node *CreateNode;
	int TraIndex = 0;	

	printf("CreateLinkQueue start!\n");

	if (NULL == LinkQueue || NULL == HeadNode) {
		return ERROR;
	}

	for (TraIndex = 0; TraIndex < CreateNum - 1; ++TraIndex) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = TraIndex;

		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		TraLinkQueue->Rear = CreateNode;		
		TraNode = TraNode->Next;
	}

	printf("CreateLinkQueue end!\n");
	return SUCCESS;
}
```

结果：

> CreateLinkQueue start!
>
> CreateLinkQueue end!
>
> CreateLinkQueue succeed!
>
> PrintLinkQueue start!
>
> TraLinkQueue->Front = 926c48
>
> TraLinkQueue->Rear = 925ec8
>
> NodeHead = 0x926c48, NodeHead->Data = 3, NodeHead->Next = 0x925e90
>
> NodeHead = 0x925e90, NodeHead->Data = 0, NodeHead->Next = 0x925ec8
>
> NodeHead = 0x925ec8, NodeHead->Data = 1, NodeHead->Next = 0x0
>
> PrintLinkQueue end!



# 3.删除链队列

​     除了头结点外，其它结点均删除。

**代码：**

```c
LIST_STATUS CreateLinkQueue(LINK_QUEUE *LinkQueue, Node *HeadNode, int CreateNum) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *TraNode = HeadNode;
	Node *CreateNode;
	int TraIndex = 0;	

	printf("CreateLinkQueue start!\n");

	if (NULL == LinkQueue || NULL == HeadNode) {
		return ERROR;
	}

	for (TraIndex = 0; TraIndex < CreateNum - 1; ++TraIndex) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = TraIndex;

		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		TraLinkQueue->Rear = CreateNode;		
		TraNode = TraNode->Next;
	}

	printf("CreateLinkQueue end!\n");
	return SUCCESS;
}
```



**结果：**

> CreateLinkQueue start!
>
> CreateLinkQueue end!
>
> CreateLinkQueue succeed!
>
> PrintLinkQueue start!
>
> TraLinkQueue->Front = b66060
>
> TraLinkQueue->Rear = b6f848
>
> NodeHead = 0xb66060, NodeHead->Data = 3, NodeHead->Next = 0xb66098
>
> NodeHead = 0xb66098, NodeHead->Data = 0, NodeHead->Next = 0xb6f848
>
> NodeHead = 0xb6f848, NodeHead->Data = 1, NodeHead->Next = 0x0
>
> PrintLinkQueue end!
>
>  
>
> DelLinkQueue start!
>
> DelLinkQueue end!
>
> DelLinkQueue succeed!
>
> PrintLinkQueue start!
>
> TraLinkQueue->Front = b66060
>
> TraLinkQueue->Rear = b66060
>
> NodeHead = 0xb66060, NodeHead->Data = 3, NodeHead->Next = 0x0
>
> PrintLinkQueue end!

# 4.打印链队列

**代码：**

```c
LIST_STATUS PrintLinkQueue(LINK_QUEUE * LinkQueue) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *NodeHead = LinkQueue->Front;

	printf("PrintLinkQueue start!\n");

	if (NULL == TraLinkQueue) {
		printf("LinkQueue = NULL\n");
		return ERROR;
	}

	printf("TraLinkQueue->Front = %x\n",TraLinkQueue->Front);
	printf("TraLinkQueue->Rear = %x\n", TraLinkQueue->Rear);

	while (NodeHead != NULL) {
		printf("NodeHead = 0x%lx, NodeHead->Data = %d, NodeHead->Next = 0x%lx\n", NodeHead, NodeHead->Data, NodeHead->Next);
		NodeHead = NodeHead->Next;
	}

	printf("PrintLinkQueue end!\n\n");
	return SUCCESS;
}
```

# 5.链队列——入队

**代码：**

```c
LIST_STATUS EnterLinkQueue(LINK_QUEUE * LinkQueue, int AddData) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *AddNode = (Node *)malloc(sizeof(Node));

	printf("EnterLinkQueue start!\n");

	if (NULL == TraLinkQueue) {
		return ERROR;
	}

	AddNode->Data = AddData;
	AddNode->Next = NULL;

	TraLinkQueue->Rear->Next = AddNode;
	TraLinkQueue->Rear = AddNode;

	printf("EnterLinkQueue end!\n");
	return SUCCESS;
}
```

**结果：**

> CreateLinkQueue start!
>
> CreateLinkQueue end!
>
> CreateLinkQueue succeed!
>
> PrintLinkQueue start!
>
> TraLinkQueue->Front = 926c48
>
> TraLinkQueue->Rear = 925ec8
>
> NodeHead = 0x926c48, NodeHead->Data = 3, NodeHead->Next = 0x925e90
>
> NodeHead = 0x925e90, NodeHead->Data = 0, NodeHead->Next = 0x925ec8
>
> NodeHead = 0x925ec8, NodeHead->Data = 1, NodeHead->Next = 0x0
>
> PrintLinkQueue end!
>
>  
>
> EnterLinkQueue start!
>
> EnterLinkQueue end!
>
> EnterLinkQueue succeed!
>
> PrintLinkQueue start!
>
> TraLinkQueue->Front = 926c48
>
> TraLinkQueue->Rear = 92c3e0
>
> NodeHead = 0x926c48, NodeHead->Data = 3, NodeHead->Next = 0x925e90
>
> NodeHead = 0x925e90, NodeHead->Data = 0, NodeHead->Next = 0x925ec8
>
> NodeHead = 0x925ec8, NodeHead->Data = 1, NodeHead->Next = 0x92c3e0
>
> NodeHead = 0x92c3e0, NodeHead->Data = 4, NodeHead->Next = 0x0
>
> PrintLinkQueue end!



# 6.链队列——出队

**代码：**

```c
LIST_STATUS ExitLinkQueue(LINK_QUEUE * LinkQueue, int *DelData) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *DelNode;

	printf("ExitLinkQueue start!\n");

	if (NULL == TraLinkQueue) {
		return ERROR;
	}
	
	if (TraLinkQueue->Front == TraLinkQueue->Rear) {
		printf("LinkQueue is empty!\n");
		return ERROR;	
	}

	*DelData = TraLinkQueue->Front->Data;
	DelNode = TraLinkQueue->Front;

	TraLinkQueue->Front = TraLinkQueue->Front->Next;
	free(DelNode);

	printf("ExitLinkQueue end!\n");
	return SUCCESS;
}
```

**结果：**

> CreateLinkQueue start!
>
> CreateLinkQueue end!
>
> CreateLinkQueue succeed!
>
> PrintLinkQueue start!
>
> TraLinkQueue->Front = 12a5e90
>
> TraLinkQueue->Rear = 12af7f8
>
> NodeHead = 0x12a5e90, NodeHead->Data = 3, NodeHead->Next = 0x12a5ec8
>
> NodeHead = 0x12a5ec8, NodeHead->Data = 0, NodeHead->Next = 0x12af7f8
>
> NodeHead = 0x12af7f8, NodeHead->Data = 1, NodeHead->Next = 0x0
>
> PrintLinkQueue end!
>
>  
>
> ExitLinkQueue start!
>
> ExitLinkQueue end!
>
> ExitLinkQueue succeed!
>
> PrintLinkQueue start!
>
> TraLinkQueue->Front = 12a5ec8
>
> TraLinkQueue->Rear = 12af7f8
>
> NodeHead = 0x12a5ec8, NodeHead->Data = 0, NodeHead->Next = 0x12af7f8
>
> NodeHead = 0x12af7f8, NodeHead->Data = 1, NodeHead->Next = 0x0
>
> PrintLinkQueue end!

