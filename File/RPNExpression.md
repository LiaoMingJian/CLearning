# 栈的作用——波兰表达式的运用，计算字符表达式

[toc]

# 1 创建一个链栈

​	需完成进栈，出栈，打印的操作。

## **（1）链栈的存储结构**

```c
#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			5

typedef int ElemType;
typedef int LIST_STATUS;
typedef char ElemCharType;

typedef struct _Node {
	ElemType Data;
	struct _Node *Next;
}Node;

typedef struct _LINK_STACK {
	Node * Top;
	int Count;
}LINK_STACK;
```

## **（2）打印**

```c
LIST_STATUS PrintLinkStack(LINK_STACK * const LinkStack) {
	Node *TraStackNode;

	printf("PrintLinkStack start\n");

	if (NULL == LinkStack) {
		return ERROR;
	}

	printf("LinkStack->Top = 0x%x\n", LinkStack->Top);
	printf("LinkStack->Count = %d\n", LinkStack->Count);

	TraStackNode = LinkStack->Top;

	while (TraStackNode != NULL) {
		printf("TraStackNode = 0x%x, TraStackNode->Data = %d\n", TraStackNode, TraStackNode->Data);
		TraStackNode = TraStackNode->Next;
	}

	printf("PrintLinkStack end\n\n");
	return SUCCESS;
}
```

## **（3）进栈**

```c
LIST_STATUS PushLinkStack(LINK_STACK *LinkStack, int PushData) {
	LINK_STACK *TraLinkStack = LinkStack;
	Node *PushNode;

	printf("PushLinkStack start\n");

	if (NULL == LinkStack) {
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

## **（4）出栈**

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

# 2 中缀表达式转换为后缀表达式

**（1）需求与算法**

**中缀表达式为：**9+(3-1)*3+10/2

**要转换成后缀表达式为：**9 3 1 - 3 * + 10 2 / +

 

**算法：**

**符号优先级：**"* /" > " + -"，“(”与“)”做特殊情况处理

 

**（2）进栈**

①  进栈原则：新元素优先级 > 栈顶元素优先级

②  当新元素为“("，进栈

③  只进新元素

 

**（3)出栈**

①  出栈的原则：新元素优先级 <= 栈顶元素优先级

②当新元素为“)”时，将到栈里面“(”（包括）之前的符号全部出栈

**①**  当符号不为"()"时，满足出栈原则时，新元素不断与栈顶元素比，不断出栈，直到不满足出栈条件，或者遇到“(”时，将新元素入栈

**②**  最后栈里面的元素也要按顺序出栈

 

**（3）其它注意的问题**

①注意多位数的处理

②注意每个数之间要有空格隔开



**代码：**

```c
bool IfPopValid(LINK_STACK * const LinkStack, char NewChar) {
	LINK_STACK *TraStackNode = LinkStack;

	printf("IfNewCharPriorityNotHigh start\n");

	/*Empty LinkStack*/
	if (TraStackNode->Top == NULL && TraStackNode->Count == 0) {
		return false;
	}

	if (NewChar == '(') {
		return false;
	} else if (NewChar == ')') {
		return true;
	} else if (NewChar == '+' || NewChar == '-') {
		return true;	
	} else if (NewChar == '*' || NewChar == '/') {
		if (TraStackNode->Top->Data == '+' || TraStackNode->Top->Data == '-') {
			return false;
		} else if (TraStackNode->Top->Data == '*' || TraStackNode->Top->Data == '/') {
			return true;
		}
	}

	printf("IfNewCharPriorityNotHigh end\n\n");
}

LIST_STATUS PushInfixExpression(LINK_STACK *LinkStack, char NewChar) {
	LINK_STACK *TraStackNode = LinkStack;
	Node *AddNode = (Node *)malloc(sizeof(Node));

	LIST_STATUS Status;

	printf("PushInfixExpression start\n");
	printf("In PushInfixExpression, NewChar = %c\n", NewChar);

	Status = PushLinkStack(LinkStack, NewChar);

	printf("PushInfixExpression end\n\n");

	return Status;
}

LIST_STATUS PopInfixExpression(LINK_STACK *LinkStack, char NewChar, char *PostfixExpression, int *PostEIndex) {
	LINK_STACK *TraStackNode = LinkStack;
	int *PopData = (int)malloc(sizeof(int));
	
	printf("PopInfixExpression start\n");

	printf("PopData = 0x%x\n", PopData);
	printf("In PopInfixExpression, NewChar = %c\n", NewChar);
	printf("In PopInfixExpression, PostfixExpression = %s\n", PostfixExpression);

	PrintCharLinkStack(LinkStack);

	if (NewChar == ')') {
		while (TraStackNode->Top != NULL) {
			if (TraStackNode->Top->Data != '(') {
				PopLinkStack(TraStackNode, PopData);
				PostfixExpression[(*PostEIndex)++] = *PopData;
				PostfixExpression[(*PostEIndex)++] = ' ';
			}else if (TraStackNode->Top->Data == '(') {
				PopLinkStack(TraStackNode, PopData);
				break;
			}
			//TraStackNode->Top = TraStackNode->Top->Next;
		}
	} else if (NewChar == '+' || NewChar == '-') {
		while ((TraStackNode->Top != NULL) && (TraStackNode->Top->Data != '(')) {
			PopLinkStack(TraStackNode, PopData);
			PostfixExpression[(*PostEIndex)++] = *PopData;
			PostfixExpression[(*PostEIndex)++] = ' ';

			//TraStackNode->Top = TraStackNode->Top->Next;
		}
		PushLinkStack(LinkStack, NewChar);
	} else if (NewChar == '*' || NewChar == '/') {
		while ( (TraStackNode->Top != NULL) && (TraStackNode->Top->Data != '(') && 
			((TraStackNode->Top->Data == '*') || (TraStackNode->Top->Data == '/')) ) {
			PopLinkStack(TraStackNode, PopData);
			printf("*PopData = %c\n", *PopData);
			PostfixExpression[(*PostEIndex)++] = *PopData;
			PostfixExpression[(*PostEIndex)++] = ' ';

			//TraStackNode->Top = TraStackNode->Top->Next;
		}
		PushLinkStack(LinkStack, NewChar);
	}

	printf("In PopInfixExpression, PostfixExpression = %s\n", PostfixExpression);

	printf("PopData = 0x%x\n", PopData);
	free(PopData);

	PrintCharLinkStack(LinkStack);

	printf("PopInfixExpression end\n\n");
}


/*RPN*/
void RPNString(void) {
	char InfixExpression[] = "9+(3-1)*3+10/2";//9 3 1 - 3 * + 10 2 / +
	//char InfixExpression[] = "9313102";//9313102
	//char InfixExpression[] = "2+1*3+2/1";//2 1 3 * + 2 1 / +
	//char InfixExpression[] = "14*23/32";//14 23 * 32 /
	//char InfixExpression[] = "(2+1)";//2 1 +
	//char InfixExpression[] = "3+(2-1)";//3 2 1 - +
	//char InfixExpression[] = "3+(2-1)*4";//3 2 1 - 4 * +

	char *PostfixExpression = (char *)malloc(sizeof(char) * sizeof(InfixExpression) * 2);
	int PostEIndex = 0;
	int TraIndex = 0;
	int ResData;
	
	LINK_STACK *LinkStack = (LINK_STACK *)malloc(sizeof(LINK_STACK));
	LinkStack->Top = NULL;
	LinkStack->Count = 0;

	LINK_STACK *TraStackNode = LinkStack;

	char *PopData = (char *)malloc(sizeof(char));

	printf("InfixExpression = %s\n", InfixExpression);
	
	for (TraIndex = 0; TraIndex < strlen(InfixExpression); ++TraIndex) {
		printf("In RPNString, InfixExpression[%d] = %c\n", TraIndex, InfixExpression[TraIndex]);
		if (InfixExpression[TraIndex] >= '0' && InfixExpression[TraIndex] <= '9') {
			PostfixExpression[PostEIndex++] = InfixExpression[TraIndex];
			/*long number*/
			while ( (TraIndex + 1 < strlen(InfixExpression)) && ((InfixExpression[TraIndex + 1] >= '0' && InfixExpression[TraIndex + 1] <= '9')) ) {
				PostfixExpression[PostEIndex++] = InfixExpression[++TraIndex];				
			}
			PostfixExpression[PostEIndex++] = ' ';
		} else if (IfPopValid(LinkStack, InfixExpression[TraIndex]) == true) {
			PopInfixExpression(LinkStack, InfixExpression[TraIndex], PostfixExpression, &PostEIndex);
		} else if (IfPopValid(LinkStack, InfixExpression[TraIndex]) == false) {
			PushInfixExpression(LinkStack, InfixExpression[TraIndex]);
		}
	}

	printf("In RPNString, PostfixExpression = %s\n", PostfixExpression);

	/*Pop remain operator*/
	printf("Pop remain operator\n");
	while ((TraStackNode->Top != NULL) && (TraStackNode->Count != 0)) {
		if (TraStackNode->Top->Next == NULL) {
			PopLinkStack(LinkStack, PopData);
			PostfixExpression[PostEIndex++] = *PopData;
		} else {
			PopLinkStack(LinkStack, PopData);
			PostfixExpression[PostEIndex++] = *PopData;
			PostfixExpression[PostEIndex++] = ' ';
		}
	}

	PrintCharLinkStack(LinkStack);

	PostfixExpression[PostEIndex++] = '\0';
	
	printf("In RPNString, PostfixExpression = %s\n\n", PostfixExpression);
	
	/*Operate PostfixExpression*/
	ResData = OpPostfixFunc(PostfixExpression, strlen(PostfixExpression));

	printf("In RPNString, ResData = %d\n", ResData);

	free(PostfixExpression);
	free(LinkStack);

```

# 3 计算后缀表达式

**（1）需求与算法**

**后缀表达式：**9 3 1 - 3 * + 10 2 / +

**计算出结果：**20

 

**算法：**

**（2）遇到数字**

​	将数进栈

 

**(3)遇到符号**

​	将栈的最上面两个元素出栈，第一个出栈的元素作为被操作数，第二个出栈的元素作为操作数，符号操作的结果进栈

 

**(4)其它注意的问题**

①注意多位数的处理

②注意每个数之间有空格隔开



**代码：**

```c
int OpPopDataFunc(char Op, int Data1, int Data2) {
	int ResData;

	if (Op == '+') {
		ResData = Data2 + Data1;
		return ResData;
	} else if (Op == '-') {
		ResData = Data2 - Data1;
		return ResData;
	} else if (Op == '*') {
		ResData = Data2 * Data1;
		return ResData;
	} else if (Op == '/') {
		ResData = Data2 / Data1;
		return ResData;
	}
}

int OpPostfixFunc(char *PostfixExpressionInput, int PostfixExpressionInputSize) {
	//char PostfixExpression[] = "1 10 + 234 - 10 *";
	//char PostfixExpression[] = "2 1 +";
	//char PostfixExpression[] = "9 3 1 - 3 * + 10 2 / +";
	char *PostfixExpression = PostfixExpressionInput;

	int Ret;
	int TraIndex = 0;

	LINK_STACK *LinkStack = (LINK_STACK *)malloc(sizeof(LINK_STACK));
	LinkStack->Top = NULL;
	LinkStack->Count = 0;
	
	int PushData = 0;
	int *PopData1 = (int *)malloc(sizeof(int));
	int *PopData2 = (int *)malloc(sizeof(int));	
	int *ResData1 = (int *)malloc(sizeof(int));
	int ResData2 = 0;
	int OpData;	

	printf("\nOpPostfixFunc start\n");
	printf("In OpPostfixFunc, PostfixExpression = %s\n", PostfixExpression);
	printf("PostfixExpressionInputSize = %d\n", PostfixExpressionInputSize);

	for (TraIndex = 0; TraIndex < PostfixExpressionInputSize; ++TraIndex) {
		printf("PostfixExpression[%d] = %c\n", TraIndex, PostfixExpression[TraIndex]);
		if (PostfixExpression[TraIndex] == ' ') {
			continue;
		} else if (PostfixExpression[TraIndex] >= '0' && PostfixExpression[TraIndex] <= '9') {
			PushData = PostfixExpression[TraIndex] - 48;
			printf("PushData 01 = %d\n", PushData);

			/*Judge wheather PostfixExpression[TraIndex] is long number*/
			while ((TraIndex + 1 < PostfixExpressionInputSize) && (PostfixExpression[TraIndex + 1] != ' ')) {
				printf("In while, PostfixExpression[%d] = %c\n", TraIndex + 1, PostfixExpression[TraIndex + 1]);
				PushData = PushData * 10 + (PostfixExpression[TraIndex + 1] - 48);
				++TraIndex;				
				printf("PushData 02 = %d\n", PushData);
			}

			/*Push should make PostfixExpression[TraIndex] int type */
			PushLinkStack(LinkStack, PushData);
			PrintLinkStack(LinkStack);
		} else if (PostfixExpression[TraIndex] == '+' || PostfixExpression[TraIndex] == '-' || PostfixExpression[TraIndex] == '*' || PostfixExpression[TraIndex] == '/') {
			PopLinkStack(LinkStack, PopData1);
			PopLinkStack(LinkStack, PopData2);

			/*
			printf("*PopData1 = %d\n", *PopData1);
			printf("*PopData2 = %d\n", *PopData2);			
			*/
			OpData = OpPopDataFunc(PostfixExpression[TraIndex], *PopData1, *PopData2);
			printf("OpData = %d\n", OpData);

			PushLinkStack(LinkStack, OpData);
		}	
	}

	PrintLinkStack(LinkStack);

	if (LinkStack->Count == 1) {
		PopLinkStack(LinkStack, ResData1);

		printf("*ResData1 = %d\n", *ResData1);

		ResData2 = *ResData1;
	}

	free(LinkStack);
	free(ResData1);
	free(PopData1);
	free(PopData2);

	printf("In OpPostfixFunc, ResData2 = %d\n", ResData2);

	return ResData2;
}
```

**打印结果：**

> InfixExpression = 9+(3-1)*3+10/2
>
> In RPNString, InfixExpression[0] = 9
>
> In RPNString, InfixExpression[1] = +
>
> IfNewCharPriorityNotHigh start
>
> IfNewCharPriorityNotHigh start
>
> PushInfixExpression start
>
> In PushInfixExpression, NewChar = +
>
> PushLinkStack start
>
> PushLinkStack end
>
> PushInfixExpression end
>
>  
>
> In RPNString, InfixExpression[2] = (
>
> IfNewCharPriorityNotHigh start
>
> IfNewCharPriorityNotHigh start
>
> PushInfixExpression start
>
> In PushInfixExpression, NewChar = (
>
> PushLinkStack start
>
> PushLinkStack end
>
> PushInfixExpression end
>
>  
>
> In RPNString, InfixExpression[3] = 3
>
> In RPNString, InfixExpression[4] = -
>
> IfNewCharPriorityNotHigh start
>
> PopInfixExpression start
>
> PopData = 0xf15f00
>
> In PopInfixExpression, NewChar = -
>
> In PopInfixExpression, PostfixExpression = 9 3 屯屯屯屯屯屯屯屯屯屯屯屯屯?
>
> PrintCharLinkStack start
>
> LinkStack->Top = 0xf20338
>
> LinkStack->Count = 2
>
> TraStackNode = 0xf20338, TraStackNode->Data = (
>
> TraStackNode = 0xf15ec8, TraStackNode->Data = +
>
> PrintCharLinkStack end
>
>  
>
> PushLinkStack start
>
> PushLinkStack end
>
> In PopInfixExpression, PostfixExpression = 9 3 屯屯屯屯屯屯屯屯屯屯屯屯屯?
>
> PopData = 0xf15f00
>
> PrintCharLinkStack start
>
> LinkStack->Top = 0xf20370
>
> LinkStack->Count = 3
>
> TraStackNode = 0xf20370, TraStackNode->Data = -
>
> TraStackNode = 0xf20338, TraStackNode->Data = (
>
> TraStackNode = 0xf15ec8, TraStackNode->Data = +
>
> PrintCharLinkStack end
>
>  
>
> PopInfixExpression end
>
>  
>
> In RPNString, InfixExpression[5] = 1
>
> In RPNString, InfixExpression[6] = )
>
> IfNewCharPriorityNotHigh start
>
> PopInfixExpression start
>
> PopData = 0xf15f00
>
> In PopInfixExpression, NewChar = )
>
> In PopInfixExpression, PostfixExpression = 9 3 1 屯屯屯屯屯屯屯屯屯屯屯屯?
>
> PrintCharLinkStack start
>
> LinkStack->Top = 0xf20370
>
> LinkStack->Count = 3
>
> TraStackNode = 0xf20370, TraStackNode->Data = -
>
> TraStackNode = 0xf20338, TraStackNode->Data = (
>
> TraStackNode = 0xf15ec8, TraStackNode->Data = +
>
> PrintCharLinkStack end
>
>  
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack start
>
> PopLinkStack end
>
> In PopInfixExpression, PostfixExpression = 9 3 1 - 屯屯屯屯屯屯屯屯屯屯屯?
>
> PopData = 0xf15f00
>
> PrintCharLinkStack start
>
> LinkStack->Top = 0xf15ec8
>
> LinkStack->Count = 1
>
> TraStackNode = 0xf15ec8, TraStackNode->Data = +
>
> PrintCharLinkStack end
>
>  
>
> PopInfixExpression end
>
>  
>
> In RPNString, InfixExpression[7] = *
>
> IfNewCharPriorityNotHigh start
>
> IfNewCharPriorityNotHigh start
>
> PushInfixExpression start
>
> In PushInfixExpression, NewChar = *
>
> PushLinkStack start
>
> PushLinkStack end
>
> PushInfixExpression end
>
>  
>
> In RPNString, InfixExpression[8] = 3
>
> In RPNString, InfixExpression[9] = +
>
> IfNewCharPriorityNotHigh start
>
> PopInfixExpression start
>
> PopData = 0xf15f00
>
> In PopInfixExpression, NewChar = +
>
> In PopInfixExpression, PostfixExpression = 9 3 1 - 3 屯屯屯屯屯屯屯屯屯屯?
>
> PrintCharLinkStack start
>
> LinkStack->Top = 0xf20370
>
> LinkStack->Count = 2
>
> TraStackNode = 0xf20370, TraStackNode->Data = *
>
> TraStackNode = 0xf15ec8, TraStackNode->Data = +
>
> PrintCharLinkStack end
>
>  
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack start
>
> PopLinkStack end
>
> PushLinkStack start
>
> PushLinkStack end
>
> In PopInfixExpression, PostfixExpression = 9 3 1 - 3 * + 屯屯屯屯屯屯屯屯?
>
> PopData = 0xf15f00
>
> PrintCharLinkStack start
>
> LinkStack->Top = 0xf15ec8
>
> LinkStack->Count = 1
>
> TraStackNode = 0xf15ec8, TraStackNode->Data = +
>
> PrintCharLinkStack end
>
>  
>
> PopInfixExpression end
>
>  
>
> In RPNString, InfixExpression[10] = 1
>
> In RPNString, InfixExpression[12] = /
>
> IfNewCharPriorityNotHigh start
>
> IfNewCharPriorityNotHigh start
>
> PushInfixExpression start
>
> In PushInfixExpression, NewChar = /
>
> PushLinkStack start
>
> PushLinkStack end
>
> PushInfixExpression end
>
>  
>
> In RPNString, InfixExpression[13] = 2
>
> In RPNString, PostfixExpression = 9 3 1 - 3 * + 10 2 屯屯屯屯屯妄
>
> Pop remain operator
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack start
>
> PopLinkStack end
>
> PrintCharLinkStack start
>
> In RPNString, PostfixExpression = 9 3 1 - 3 * + 10 2 / +
>
>  
>
>  
>
> OpPostfixFunc start
>
> In OpPostfixFunc, PostfixExpression = 9 3 1 - 3 * + 10 2 / +
>
> PostfixExpressionInputSize = 22
>
> PostfixExpression[0] = 9
>
> PushData 01 = 9
>
> PushLinkStack start
>
> PushLinkStack end
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf20408
>
> LinkStack->Count = 1
>
> TraStackNode = 0xf20408, TraStackNode->Data = 9
>
> PrintLinkStack end
>
>  
>
> PostfixExpression[1] =
>
> PostfixExpression[2] = 3
>
> PushData 01 = 3
>
> PushLinkStack start
>
> PushLinkStack end
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf20440
>
> LinkStack->Count = 2
>
> TraStackNode = 0xf20440, TraStackNode->Data = 3
>
> TraStackNode = 0xf20408, TraStackNode->Data = 9
>
> PrintLinkStack end
>
>  
>
> PostfixExpression[3] =
>
> PostfixExpression[4] = 1
>
> PushData 01 = 1
>
> PushLinkStack start
>
> PushLinkStack end
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf20478
>
> LinkStack->Count = 3
>
> TraStackNode = 0xf20478, TraStackNode->Data = 1
>
> TraStackNode = 0xf20440, TraStackNode->Data = 3
>
> TraStackNode = 0xf20408, TraStackNode->Data = 9
>
> PrintLinkStack end
>
>  
>
> PostfixExpression[5] =
>
> PostfixExpression[6] = -
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack start
>
> PopLinkStack end
>
> OpData = 2
>
> PushLinkStack start
>
> PushLinkStack end
>
> PostfixExpression[7] =
>
> PostfixExpression[8] = 3
>
> PushData 01 = 3
>
> PushLinkStack start
>
> PushLinkStack end
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf20698
>
> LinkStack->Count = 3
>
> TraStackNode = 0xf20698, TraStackNode->Data = 3
>
> TraStackNode = 0xf204d8, TraStackNode->Data = 2
>
> TraStackNode = 0xf20408, TraStackNode->Data = 9
>
> PrintLinkStack end
>
>  
>
> PostfixExpression[9] =
>
> PostfixExpression[10] = *
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack start
>
> PopLinkStack end
>
> OpData = 6
>
> PushLinkStack start
>
> PushLinkStack end
>
> PostfixExpression[11] =
>
> PostfixExpression[12] = +
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack start
>
> PopLinkStack end
>
> OpData = 15
>
> PushLinkStack start
>
> PushLinkStack end
>
> PostfixExpression[13] =
>
> PostfixExpression[14] = 1
>
> PushData 01 = 1
>
> In while, PostfixExpression[15] = 0
>
> PushData 02 = 10
>
> PushLinkStack start
>
> PushLinkStack end
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf206d0
>
> LinkStack->Count = 2
>
> TraStackNode = 0xf206d0, TraStackNode->Data = 10
>
> TraStackNode = 0xf207b0, TraStackNode->Data = 15
>
> PrintLinkStack end
>
>  
>
> PostfixExpression[16] =
>
> PostfixExpression[17] = 2
>
> PushData 01 = 2
>
> PushLinkStack start
>
> PushLinkStack end
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf20580
>
> LinkStack->Count = 3
>
> TraStackNode = 0xf20580, TraStackNode->Data = 2
>
> TraStackNode = 0xf206d0, TraStackNode->Data = 10
>
> TraStackNode = 0xf207b0, TraStackNode->Data = 15
>
> PrintLinkStack end
>
>  
>
> PostfixExpression[18] =
>
> PostfixExpression[19] = /
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack start
>
> PopLinkStack end
>
> OpData = 5
>
> PushLinkStack start
>
> PushLinkStack end
>
> PostfixExpression[20] =
>
> PostfixExpression[21] = +
>
> PopLinkStack start
>
> PopLinkStack end
>
> PopLinkStack start
>
> PopLinkStack end
>
> OpData = 20
>
> PushLinkStack start
>
> PushLinkStack end
>
> PrintLinkStack start
>
> LinkStack->Top = 0xf205f0
>
> LinkStack->Count = 1
>
> TraStackNode = 0xf205f0, TraStackNode->Data = 20
>
> PrintLinkStack end
>
>  
>
> PopLinkStack start
>
> PopLinkStack end
>
> *ResData1 = 20
>
> In OpPostfixFunc, ResData2 = 20
>
> In RPNString, ResData = 20
