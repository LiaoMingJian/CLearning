# 共享栈，创建，打印，入栈，出栈——C语言描述

[toc]



## 1. 共享栈的顺序存储结构

​    一个数组里面有两个栈指针，一个在数组下标为0（Top = -1时栈1为空栈），一个在数组尾（Top = MAXSIZE栈2为空栈）。当Top1 + 1 = Top2时，该共享栈为满栈。

**代码：**

```c
#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			5

typedef int ElemType;
typedef int LIST_STATUS;
typedef struct _SQ_DOUBLE_STACK {
	ElemType Data[MAXSIZE];
	int Top1;
	int Top2;
}SQ_DOUBLE_STACK;

```

 

## 2 操作共享栈

​    创建，打印，入栈，出栈。

**代码：**

```c
void OperateSQDoubleStack(void) {
	LIST_STATUS Status;
	SQ_DOUBLE_STACK  *SqDbStack = (SQ_DOUBLE_STACK *)malloc(sizeof(SQ_DOUBLE_STACK));
	int CreateNum = 4;

	Status = CreateSQDoubleStack(SqDbStack, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateSQDoubleStack succeed!\n");
	}
	else {
		printf("CreateSQDoubleStack failed!\n");
	}

	PrintSQDoubleStack(SqDbStack);
}
```

## 3 创建共享栈

​    创建一个共享栈，两边栈的有个元素。

**代码：**

```c
/*SQ_DOUBLE_STACK*/
LIST_STATUS CreateSQDoubleStack(SQ_DOUBLE_STACK *SqDbStack, int CreateNum) {
	SQ_DOUBLE_STACK *TraDbStack;
	int TraIndex;

	printf("CreateSQDoubleStack start\n");

	if (NULL == SqDbStack || CreateNum > MAXSIZE) {
		return ERROR;	
	}

	for (TraIndex = 0; TraIndex < MAXSIZE; ++TraIndex) {
		if (TraIndex <=1 || TraIndex > 2) {
			SqDbStack->Data[TraIndex] = TraIndex;
		}
	}

	SqDbStack->Top1 = 1;
	SqDbStack->Top2 = 3;

	printf("CreateSQDoubleStack start\n");
	return SUCCESS;
}

```

**结果：**

> CreateSQDoubleStack start
>
> CreateSQDoubleStack start
>
> CreateSQDoubleStack succeed!
>
> PrintSQDoubleStack start
>
> TraDbStack->Top1 = 1
>
> TraDbStack->Top2 = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 0
>
> PrintSQDoubleStack->Data[TraIndex] = 1
>
> PrintSQDoubleStack->Data[TraIndex] = -842150451
>
> PrintSQDoubleStack->Data[TraIndex] = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 4
>
> PrintSQDoubleStack end

 

## 4  打印共享栈

**代码：**

```c
void PrintSQDoubleStack(SQ_DOUBLE_STACK * const SqDbStack) {
	SQ_DOUBLE_STACK *TraDbStack = SqDbStack;
	int TraIndex;

	printf("PrintSQDoubleStack start\n");

	printf("TraDbStack->Top1 = %d\n", TraDbStack->Top1);
	printf("TraDbStack->Top2 = %d\n", TraDbStack->Top2);
	for (TraIndex = 0; TraIndex < MAXSIZE; ++TraIndex) {
		printf("PrintSQDoubleStack->Data[TraIndex] = %d\n", TraDbStack->Data[TraIndex]);
	}

	printf("PrintSQDoubleStack end\n\n");
}

```



## 5 共享栈——入栈

```c
LIST_STATUS PushSQDoubleStack(SQ_DOUBLE_STACK *SqDbStack, int PushData, int StackNum)
```

​    通过StackNum编号来判断要入栈的编号。

**代码：**

```c
LIST_STATUS PushSQDoubleStack(SQ_DOUBLE_STACK *SqDbStack, int PushData, int PushStackNum) {
	printf("PushSQDoubleStack start\n");

	if (NULL == SqDbStack || SqDbStack->Top1 + 1 == SqDbStack->Top2) {
		return ERROR;	
	}

	if (1 == PushStackNum) {
		SqDbStack->Data[++SqDbStack->Top1] = PushData;
	
	} else if (2 == PushStackNum) {
		SqDbStack->Data[--SqDbStack->Top2] = PushData;
	}

	printf("PushSQDoubleStack end\n");
	return SUCCESS;
}
```

**结果：**

> CreateSQDoubleStack start
>
> CreateSQDoubleStack start
>
> CreateSQDoubleStack succeed!
>
> PrintSQDoubleStack start
>
> TraDbStack->Top1 = 1
>
> TraDbStack->Top2 = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 0
>
> PrintSQDoubleStack->Data[TraIndex] = 1
>
> PrintSQDoubleStack->Data[TraIndex] = -842150451
>
> PrintSQDoubleStack->Data[TraIndex] = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 4
>
> PrintSQDoubleStack end
>
>  
>
> PushSQDoubleStack start
>
> PushSQDoubleStack end
>
> CreateSQDoubleStack succeed!
>
> PrintSQDoubleStack start
>
> TraDbStack->Top1 = 2
>
> TraDbStack->Top2 = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 0
>
> PrintSQDoubleStack->Data[TraIndex] = 1
>
> PrintSQDoubleStack->Data[TraIndex] = 10
>
> PrintSQDoubleStack->Data[TraIndex] = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 4
>
> PrintSQDoubleStack end

 

## 6  共享栈——出栈

```c
LIST_STATUS PopSQDoubleStack(SQ_DOUBLE_STACK *SqDbStack, int *PopData, int PopStackNum)
```

​    通过PopStackNum编号来判断要出栈的编号

**代码：**

```c
LIST_STATUS PopSQDoubleStack(SQ_DOUBLE_STACK *SqDbStack, int *PopData, int PopStackNum) {
	printf("PopSQDoubleStack start\n");

	if (NULL == SqDbStack) {
		return ERROR;
	}

	if (1 == PopStackNum) {
		if (SqDbStack->Top1 == -1) {
			return ERROR;
		} else {
			*PopData = SqDbStack->Data[SqDbStack->Top1--];
		}
	}
	else if (2 == PopStackNum) {
		if (SqDbStack->Top2 == MAXSIZE) {
			return ERROR;
		} else {
			*PopData = SqDbStack->Data[SqDbStack->Top2++];
		}
	}

	printf("PopSQDoubleStack end\n");
	return SUCCESS;
}
```

**结果：**

> CreateSQDoubleStack start
>
> CreateSQDoubleStack start
>
> CreateSQDoubleStack succeed!
>
> PrintSQDoubleStack start
>
> TraDbStack->Top1 = 1
>
> TraDbStack->Top2 = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 0
>
> PrintSQDoubleStack->Data[TraIndex] = 1
>
> PrintSQDoubleStack->Data[TraIndex] = -842150451
>
> PrintSQDoubleStack->Data[TraIndex] = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 4
>
> PrintSQDoubleStack end
>
>  
>
> PopSQDoubleStack start
>
> PopSQDoubleStack end
>
> PopSQDoubleStack succeed!
>
> *PopData = 1
>
> PrintSQDoubleStack start
>
> TraDbStack->Top1 = 0
>
> TraDbStack->Top2 = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 0
>
> PrintSQDoubleStack->Data[TraIndex] = 1
>
> PrintSQDoubleStack->Data[TraIndex] = -842150451
>
> PrintSQDoubleStack->Data[TraIndex] = 3
>
> PrintSQDoubleStack->Data[TraIndex] = 4
>
> PrintSQDoubleStack end

