# 栈的顺序存储结构——c语言描述

[toc]



# 1栈的定义

​    先进后出的数据结构

# 2栈的顺序存储结构

**当栈为空栈时，****top = -1**

**代码：**

```c
#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			5

typedef int ElemType;
typedef int LIST_STATUS;
typedef struct _SQ_STACK {
	ElemType Data[MAXSIZE];
	int Top;
}SQ_STACK;

```



## 2.1 操作顺序栈

**代码：**

```c
void OperateSqStack(void) {
	LIST_STATUS Status;
	SQ_STACK *SqStack = (SQ_STACK *)malloc(sizeof(SQ_STACK));
	int CreateNum = 3;
	int PushData = 3;
	int *PopData = (int *)malloc(sizeof(int));
	
	Status = CreateSQStack(SqStack, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateSQStack succeed!\n");
	}
	else {
		printf("CreateSQStack failed!\n");
	}

	PrintSQStack(SqStack);

	/*
	Status = PushSQStack(SqStack, PushData);
	if (SUCCESS == Status) {
		printf("PushSQStack succeed!\n");
	}
	else {
		printf("PushSQStack failed!\n");
	}
	*/

	PopSQStack(SqStack, PopData);
	if (SUCCESS == Status) {
		printf("PushSQStack succeed!\n");
	}
	else {
		printf("PushSQStack failed!\n");
	}

	PrintSQStack(SqStack);
}

```

 

## 2.2 创建顺序栈

```c
LIST_STATUS CreateSQStack(SQ_STACK *SqStack, int CreateNum)
```

​	创建个数为CreateNum的栈

**代码：**

```c
LIST_STATUS CreateSQStack(SQ_STACK *SqStack, int CreateNum) {
	int TraIndex;

	printf("CreateSQStack start\n");

	if (NULL == SqStack || CreateNum > MAXSIZE) {
		return ERROR;
	}

	for (TraIndex = 0; TraIndex < CreateNum; ++TraIndex) {
		SqStack->Data[TraIndex] = TraIndex;
	}

	SqStack->Top = CreateNum - 1;

	printf("CreateSQStack end\n");
	return SUCCESS;
}
```

**结果：**

> CreateSQStack start
>
> CreateSQStack end
>
> CreateSQStack succeed!
>
> CreateSQStack start
>
> TraStack->Top = 2
>
> TraStack->Data[TraIndex] = 0
>
> TraStack->Data[TraIndex] = 1
>
> TraStack->Data[TraIndex] = 2
>
> TraStack->Data[TraIndex] = -842150451
>
> TraStack->Data[TraIndex] = -842150451
>
> CreateSQStack end

## 2.3 打印顺序栈

```c
void PrintSQStack(SQ_STACK * const SqStack)
```

**代码：**

```c
void PrintSQStack(SQ_STACK * const SqStack) {
	SQ_STACK *TraStack = SqStack;
	int TraIndex;

	printf("CreateSQStack start\n");

	printf("TraStack->Top = %d\n", TraStack->Top);
	for (TraIndex = 0; TraIndex < MAXSIZE; ++TraIndex) {
		printf("TraStack->Data[TraIndex] = %d\n", TraStack->Data[TraIndex]);
	}

	printf("CreateSQStack end\n");
}
```

 

## 2.4 进栈

​	栈顶增加一个元素

**代码：**

```c
LIST_STATUS PushSQStack(SQ_STACK *SqStack, int PushData) {	
	printf("PushSQStack start\n");

	if (NULL == SqStack || SqStack->Top == MAXSIZE - 1) {
		return ERROR;
	}

	SqStack->Top++;
	SqStack->Data[SqStack->Top] = PushData;

	printf("PushSQStack end\n\n");

	return SUCCESS;
}
```

**结果：**

> CreateSQStack start
>
> CreateSQStack end
>
> CreateSQStack succeed!
>
> CreateSQStack start
>
> TraStack->Top = 2
>
> TraStack->Data[TraIndex] = 0
>
> TraStack->Data[TraIndex] = 1
>
> TraStack->Data[TraIndex] = 2
>
> TraStack->Data[TraIndex] = -842150451
>
> TraStack->Data[TraIndex] = -842150451
>
> CreateSQStack end
>
> PushSQStack start
>
> PushSQStack end
>
>  
>
> PushSQStack succeed!
>
> CreateSQStack start
>
> TraStack->Top = 3
>
> TraStack->Data[TraIndex] = 0
>
> TraStack->Data[TraIndex] = 1
>
> TraStack->Data[TraIndex] = 2
>
> TraStack->Data[TraIndex] = 3
>
> TraStack->Data[TraIndex] = -842150451

 

## 2.5出栈

**代码：**

```c
LIST_STATUS PopSQStack(SQ_STACK *SqStack, int *PopData) {
	printf("PopSQStack start\n");

	if (NULL == SqStack || SqStack->Top == -1) {
		return ERROR;	
	}

	*PopData = SqStack->Data[SqStack->Top];
	SqStack->Top--;

	printf("PopSQStack end\n");
}
```

**结果：**

> CreateSQStack start
>
> CreateSQStack end
>
> CreateSQStack succeed!
>
> CreateSQStack start
>
> TraStack->Top = 2
>
> TraStack->Data[TraIndex] = 0
>
> TraStack->Data[TraIndex] = 1
>
> TraStack->Data[TraIndex] = 2
>
> TraStack->Data[TraIndex] = -842150451
>
> TraStack->Data[TraIndex] = -842150451
>
> CreateSQStack end
>
>  
>
> PopSQStack start
>
> PopSQStack end
>
> PushSQStack succeed!
>
> CreateSQStack start
>
> TraStack->Top = 1
>
> TraStack->Data[TraIndex] = 0
>
> TraStack->Data[TraIndex] = 1
>
> TraStack->Data[TraIndex] = 2
>
> TraStack->Data[TraIndex] = -842150451
>
> TraStack->Data[TraIndex] = -842150451