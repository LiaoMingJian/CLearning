# 循环队列——C语言描述

[toc]

# 1 循环队列的顺序存储结构

​        先进先出的数据结构，同时为了解决数组溢出的问题。

**(1)循环队列的存储结构**

```c
#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			5

typedef int ElemType;
typedef int LIST_STATUS;
typedef struct _SQ_QUEUE {
​     int Data[MAXSIZE];
​     int front;
​     int Rear;
}SQ_QUEUE;
```

**(2)操作循环队列**

​     创建，打印，出队，入队。

**代码：**

```c
void OperateQueue(void) {
	LIST_STATUS Status;
	
	SQ_QUEUE *SqQueue = (SQ_QUEUE *)malloc(sizeof(SQ_QUEUE));
	int *ExitData = (int *)malloc(sizeof(int));
	int EnterData = 3;


	Status = CreateSqQueue(SqQueue);
	if (SUCCESS == Status) {
		printf("CreateSqQueue succeed!\n");
	} else {
		printf("CreateSqQueue failed!\n");
	}

	SqQueueLength(SqQueue);
	PrintSqQueue(SqQueue);

	/*
	Status  = EnterSqQueue(SqQueue, EnterData);
	if (SUCCESS == Status) {
		printf("EnterSqQueue succeed!\n");
	} else {
		printf("EnterSqQueue failed!\n");
	}
	*/

	Status = ExitSqQueue(SqQueue, ExitData);
	if (SUCCESS == Status) {
		printf("ExitSqQueue succeed!\n");
	}
	else {
		printf("ExitSqQueue failed!\n");
	}

	SqQueueLength(SqQueue);
	PrintSqQueue(SqQueue);
	

	free(SqQueue);
	free(ExitData);
}
```

**(3)打印循环队列**

**代码：**

```c
LIST_STATUS PrintSqQueue(SQ_QUEUE *SqQueue) {
	SQ_QUEUE *TraSqQueue = SqQueue;
	int TraIndex = 0;

	printf("PrintSqQueue start\n");

	if (NULL == TraSqQueue) {
		return ERROR;
	}

	printf("TraSqQueue->front = %d\n", TraSqQueue->Front);
	printf("TraSqQueue->Rear = %d\n", TraSqQueue->Rear);

	for (TraIndex = 0; TraIndex < MAXSIZE; ++TraIndex) {
		printf("TraSqQueue->Data[%d] = %d\n", TraIndex, TraSqQueue->Data[TraIndex]);
	}

	printf("PrintSqueue end\n\n");

	return SUCCESS;
}
```

**(4)循环队列的长度**

​     要考虑Rear在Front的情况，循环长度的算法为：(Rear – Front + MAXSIZE) % MAXSIZE

**代码：**

```c
int SqQueueLength(SQ_QUEUE *SqQueue) {
	printf("SqQueueLength = %d\n", (SqQueue->Rear - SqQueue->Front + MAXSIZE) % MAXSIZE);
	return (SqQueue->Rear - SqQueue->Front + MAXSIZE) % MAXSIZE;
}
```

**(5)循环队列入队**

​     先判断队列是不是已经满了，然后再入队，入队完后，Rear往后面溢出，要考虑假溢出的情况，所以Rear指针移动方法为：(Rear + 1 + MAXSIZE) % MAXSIZE.

**代码：**

```c
LIST_STATUS EnterSqQueue(SQ_QUEUE *SqQueue, int EnterData) {
	SQ_QUEUE *TraSqQueue = SqQueue;

	printf("EnterSqQueue start\n");

	if (NULL == TraSqQueue) {
		return ERROR;
	}

	if ((TraSqQueue->Rear + 1 + MAXSIZE) % MAXSIZE == TraSqQueue->Front) {
		return ERROR;	
	}

	TraSqQueue->Data[TraSqQueue->Rear] = EnterData;
	TraSqQueue->Rear = (TraSqQueue->Rear + 1) % MAXSIZE;

	printf("EnterSqQueue end\n");

	return SUCCESS;
}
```

**结果：**

>CreateSqQueue start
>
>CreateSqQueue end
>
>CreateSqQueue succeed!
>
>SqQueueLength = 3
>
>PrintSqQueue start
>
>TraSqQueue->front = 0
>
>TraSqQueue->Rear = 3
>
>TraSqQueue->Data[0] = 0
>
>TraSqQueue->Data[1] = 1
>
>TraSqQueue->Data[2] = 2
>
>TraSqQueue->Data[3] = -842150451
>
>TraSqQueue->Data[4] = -842150451
>
>PrintSqueue end
>
> 
>
>EnterSqQueue start
>
>EnterSqQueue end
>
>EnterSqQueue succeed!
>
>SqQueueLength = 4
>
>PrintSqQueue start
>
>TraSqQueue->front = 0
>
>TraSqQueue->Rear = 4
>
>TraSqQueue->Data[0] = 0
>
>TraSqQueue->Data[1] = 1
>
>TraSqQueue->Data[2] = 2
>
>TraSqQueue->Data[3] = 3
>
>TraSqQueue->Data[4] = -842150451
>
>PrintSqueue end

**(5)循环队列出队**

​     先判断队列是不是为空（Rear == Front），然后再出队，出队完后，Rear往后面溢出，要考虑假溢出的情况，所以Front指针移动方法为：(Front + 1 + MAXSIZE) % MAXSIZE。

**代码：**

```c
LIST_STATUS ExitSqQueue(SQ_QUEUE *SqQueue, int *ExitData) {
	SQ_QUEUE *TraSqQueue = SqQueue;

	printf("ExitSqQueue start\n");

	if (NULL == TraSqQueue) {
		return ERROR;
	}

	if (TraSqQueue->Rear == TraSqQueue->Front) {
		return ERROR;
	}

	*ExitData = TraSqQueue->Data[TraSqQueue->Front];
	TraSqQueue->Front = (TraSqQueue->Front + 1) % MAXSIZE;

	printf("ExitSqQueue end\n");

	return SUCCESS;
}
```

**结果：**

> CreateSqQueue start
>
> CreateSqQueue end
>
> CreateSqQueue succeed!
>
> SqQueueLength = 3
>
> PrintSqQueue start
>
> TraSqQueue->front = 0
>
> TraSqQueue->Rear = 3
>
> TraSqQueue->Data[0] = 0
>
> TraSqQueue->Data[1] = 1
>
> TraSqQueue->Data[2] = 2
>
> TraSqQueue->Data[3] = -842150451
>
> TraSqQueue->Data[4] = -842150451
>
> PrintSqueue end
>
>  
>
> ExitSqQueue start
>
> ExitSqQueue end
>
> ExitSqQueue succeed!
>
> SqQueueLength = 2
>
> PrintSqQueue start
>
> TraSqQueue->front = 1
>
> TraSqQueue->Rear = 3
>
> TraSqQueue->Data[0] = 0
>
> TraSqQueue->Data[1] = 1
>
> TraSqQueue->Data[2] = 2
>
> TraSqQueue->Data[3] = -842150451
>
> TraSqQueue->Data[4] = -842150451
>
> PrintSqueue end





