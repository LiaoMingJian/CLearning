# 线性表的链式存储结构——循环链表

[toc]

​	循环链表就是单链表最后一个结点的指针不指向NULL，而是指向头结点。

# 1 存储结构

```c
typedef int ElemType;
typedef int LIST_STATUS;

typedef struct _Node {
	ElemType Data;
	struct _Node *Next;
}Node;
```

 

# 2操作循环链表

​    创建，打印，合并两个循环链表的操作

代码：

```c
LIST_STATUS OperatorLoopLinkList(void) {
	Node *LoopHead01;
	Node *LoopHead02;
	Node *MergeLoopHead;
	int CreateNum = 3;
	
	LIST_STATUS Status;

	/*Create empty link list*/
	LoopHead01 = (Node *)malloc(sizeof(Node));
	LoopHead02 = (Node *)malloc(sizeof(Node));


	Status = CreateLoopLinkList01(LoopHead01, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateLoopLinkList01 succeed!\n");
	} else {
		printf("CreateLoopLinkList01 failed!\n");
	}

	PrintLoopLinkList(LoopHead01);

	Status = CreateLoopLinkList02(LoopHead02, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateLoopLinkList02 succeed!\n");
	}
	else {
		printf("CreateLoopLinkList02 failed!\n");
	}

	PrintLoopLinkList(LoopHead02);

	MergeLoopHead = MergeTwoLoopLinkList(LoopHead01, LoopHead02);

	PrintLoopLinkList(MergeLoopHead);
}
```

# 3 创建循环链表

 

​    创建结点数为3的循环链表

 

**代码：**

```c
LIST_STATUS CreateLoopLinkList(Node *LoopHead, int CreateNum) {
	int i = 0;
	Node *TraNode;
	Node *CreateNode;

	printf("CreateLoopLinkList start\n");

	if (NULL == LoopHead) {
		return ERROR;
	}

	/*Create TailNode*/
	LoopHead->Data = CreateNum;
	LoopHead->Next = NULL;

	TraNode= LoopHead;

	for (i = 1; i <= CreateNum; ++i) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = i;
		
		/*Insert Node in the tail of link list*/
		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		/*Move TraNode*/
		TraNode = TraNode->Next;
	}

	/*Deal with the last Node*/
	if (NULL == TraNode->Next) {
		TraNode->Next = LoopHead;
	}

	printf("CreateLoopLinkList end\n");
	return SUCCESS;
}

```

 

**结果：**

> CreateLoopLinkList start
>
> CreateLoopLinkList end
>
> CreateLoopLinkList succeed!
>
> PrintLoopLinkList start
>
> TraNode->Data = 3
>
> TraNode->Data = 1
>
> TraNode->Data = 2
>
> TraNode->Data = 3
>
> PrintLoopLinkList end

# 4 打印循环链表

**代码：**

```c
LIST_STATUS PrintLoopLinkList(Node *LoopHead) {
	Node *TraNode;

	printf("PrintLoopLinkList start\n");

	TraNode = LoopHead;

	if (NULL == LoopHead) {
		return ERROR;
	}

	while (TraNode->Next != LoopHead) {
		printf("TraNode->Data = %d\n", TraNode->Data);
		TraNode = TraNode->Next;
	}
	
	if (TraNode->Next == LoopHead) {
		printf("TraNode->Data = %d\n", TraNode->Data);	
	}

	printf("PrintLoopLinkList end\n");
}

```

# 5 合并循环链表

​    将两个循环链表进行合并，将第二个循环链表的头节点删除

**代码：**

```c
Node* MergeTwoLoopLinkList(Node *LoopHead01, Node *LoopHead02) {
	Node *TraNode01;
	Node *TraNode02;

	printf("MergeTwoLoopLinkList start\n");

	if (NULL == LoopHead01) {
		return LoopHead02;
	}

	if (NULL == LoopHead02) {
		return LoopHead01;
	}

	LoopHead01->Data += LoopHead02->Data;\

	TraNode01 = LoopHead01;
	TraNode02 = LoopHead02;

	/*Find the tail01*/
	while (TraNode01->Next != LoopHead01) {
		TraNode01 = TraNode01->Next;
	}

	/*Find the tail02*/
	while (TraNode02->Next != LoopHead02) {
		TraNode02 = TraNode02->Next;
	}

	/*Link with tail01 with LoopHead01->Next*/
	if (TraNode01->Next == LoopHead01) {
		TraNode01->Next = LoopHead02->Next;	
	}

	/*Link with tail02 with LoopHead01*/
	if (TraNode02->Next == LoopHead02) {
		TraNode02->Next = LoopHead01;
	}

	/*Free LoopHead02*/
	free(LoopHead02);

	printf("MergeTwoLoopLinkList end\n");

	return LoopHead01;
}
```

**结果：**

> TraNode->Data = 2
>
> TraNode->Data = 3
>
> PrintLoopLinkList end
>
> CreateLoopLinkList start
>
> CreateLoopLinkList end
>
> CreateLoopLinkList02 succeed!
>
> PrintLoopLinkList start
>
> TraNode->Data = 3
>
> TraNode->Data = 4
>
> TraNode->Data = 5
>
> TraNode->Data = 6
>
> PrintLoopLinkList end
>
> MergeTwoLoopLinkList start
>
> MergeTwoLoopLinkList end
>
> PrintLoopLinkList start
>
> TraNode->Data = 6
>
> TraNode->Data = 1
>
> TraNode->Data = 2
>
> TraNode->Data = 3
>
> TraNode->Data = 4
>
> TraNode->Data = 5
>
> TraNode->Data = 6
>
> PrintLoopLinkList end
