# 树的存储结构（双亲表示法，孩子表示法，孩子兄弟表示法）——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})



# 1 树的基本概念

度：结点的子树个数



# 2 树的存储结构

双亲表示法，孩子表示法，孩子兄弟表示法

# 3 树的双亲表示法

## 3.1 存储结构代码

```c
#define PT_TREE_MAXSIZE			100
typedef struct {
	int Data;
	int Parent;
}PTNode;

typedef struct {
	PTNode Node[PT_TREE_MAXSIZE];
	int Root;
	int Num;
}PTree;
```

## 3.2 构建树

```c
OP_STATUS BuildPTree(PTree *PTree01, const unsigned int PTNodeNum, const int *PTNodeData, const int *PTNodeParent)
```

**(1)条件**

PTNodeNum表示结点个数，PTNodeData表示结点的数据，PTNodeParent表示结点双亲位置

**(2)代码**

```c
OP_STATUS BuildPTree(PTree *PTree01, const unsigned int PTNodeNum, const int *PTNodeData, const int *PTNodeParent) {
	OP_STATUS Status = SUCCESS;
	PTree *TraPTree01 = PTree01;
	int *TraPTNodeData = PTNodeData;
	int *TraPTNodeParent = PTNodeParent;

	unsigned int Index = 0;

	printf("BuildPTree start\n");

	if (TraPTree01 == NULL || TraPTNodeData == NULL || TraPTNodeParent == NULL) {
		return ERROR;
	}

	TraPTree01->Num = PTNodeNum;
	TraPTree01->Root = 0;

	for (Index = 0; Index < PTNodeNum; ++Index) {
		//printf("TraPTNodeData[%d] = %d, TraPTNodeParent[%d] = %d\n", Index, TraPTNodeData[Index], Index, TraPTNodeParent[Index]);
		TraPTree01->Node[Index].Data = TraPTNodeData[Index];
		TraPTree01->Node[Index].Parent = TraPTNodeParent[Index];
	}	

	printf("BuildPTree end\n");
	return SUCCESS;
}
```

**(3)测试用例**

**代码：**

**①打印树**

```c
void PrintPTree(const PTree *PTree01, const int PTNodeNum) {
	PTree *TraPTree01 = PTree01;
	unsigned int Index = 0;
	
	printf("TraPTree01->Root = %d, TraPTree01->Num = %d\n", TraPTree01->Root, TraPTree01->Num);

	for (Index = 0; Index < PTNodeNum; ++Index) {
		printf("TraPTree01->Node[%d].Data = %d, TraPTree01->Node[%d].Parent = %d\n", Index, TraPTree01->Node[Index].Data, Index, TraPTree01->Node[Index].Parent);
	}
}
```

**②比较树**

```c
OP_STATUS PTreeCmpTest(const PTree *PT01, const PTree *PT02, const unsigned int PTNodeNum01) {
	PTree *TraPT01 = PT01;
	PTree *TraPT02 = PT02;
	unsigned int Index = 0;

	TestNum++;
	
	if (TraPT01->Num != TraPT02->Num || TraPT01->Root != TraPT02->Root) {
		FaildNum++;
		return ERROR;
	}

	for (Index = 0; Index < PTNodeNum01; ++Index) {
		if (TraPT01->Node[Index].Data != TraPT02->Node[Index].Data || TraPT01->Node[Index].Parent != TraPT02->Node[Index].Parent) {
			FaildNum++;
			return ERROR;
		}
	}

	PassNum++;
	return SUCCESS;
}
```

```c
void TestBuildPTree(void) {
	PTree PTree01;
	unsigned int PTNodeNum01 = 7;
	int PTNodeData01[7] = { 0, 10, 20, 30, 40, 50, 60 };
	int PTNodeParent[7] = {-1, 0, 0, 1, 1, 2, 2};

	PTree CmpPTree = { {{0, -1}, {10, 0}, {20, 0}, {30, 1}, {40, 1}, {50, 2}, {60, 2}}, 0, 7 };

	BuildPTree(&PTree01, PTNodeNum01, PTNodeData01, PTNodeParent);
	
	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	PTreeCmpTest(&CmpPTree, &PTree01, PTNodeNum01);
	PrintPTree(&PTree01, PTNodeNum01);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**(4)结果**

> BuildPTree start
>
> BuildPTree end
>
> -------Test start----------
>
> -------Test 01----------
>
> TraPTree01->Root = 0, TraPTree01->Num = 7
>
> TraPTree01->Node[0].Data = 0, TraPTree01->Node[0].Parent = -1
>
> TraPTree01->Node[1].Data = 10, TraPTree01->Node[1].Parent = 0
>
> TraPTree01->Node[2].Data = 20, TraPTree01->Node[2].Parent = 0
>
> TraPTree01->Node[3].Data = 30, TraPTree01->Node[3].Parent = 1
>
> TraPTree01->Node[4].Data = 40, TraPTree01->Node[4].Parent = 1
>
> TraPTree01->Node[5].Data = 50, TraPTree01->Node[5].Parent = 2
>
> TraPTree01->Node[6].Data = 60, TraPTree01->Node[6].Parent = 2
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 1, PassNum = 1, FaildNum = 0











```c
unsigned int FindStrIndex(char *Str, const char *FindStr, const unsigned int FindStrPos)
```

## 1.1需求：在Str串的Pos位置之后，找第一个FinStr,找到返回Str的下标，找不到返回0。

## 1.2  条件

​	FindStr与FindStr非空，0 < FindStrPos<= FindStrLen - FindStrLen

## 1.3 方法：

1. 使用SubString函数截取字串，长度为FinStr的长度

2. 使用截取的字串与FinStr进行比较

**代码：**

```c
unsigned int FindStrIndex(char *Str, const char *FindStr, const unsigned int FindStrPos) {
	unsigned int StrLenth = StringLen(Str);
	unsigned int FindStrLenth = StringLen(FindStr);
	char *Sub = NULL;
	unsigned int Index = 0;
	unsigned int FindStrIndex = 0;

	OP_STATUS  Status = SUCCESS;

	printf("FindStrIndex start\n");
	if (Str == NULL || FindStr == NULL || FindStrPos == 0 || FindStrPos > StrLenth - FindStrLenth + 1) {
		printf("Invaild parameter!\n");
		FindStrIndex = 0;
		goto EXIT;
	}

	Sub = (char *)malloc(StringLen(Str) + 1);
	if (Sub == NULL) {
		FindStrIndex = 0;
		goto EXIT;
	}	

	for (Index = FindStrPos - 1; Index <= StrLenth - FindStrLenth + 1; ++Index) {
		Status = SubString(Sub, Str, Index, FindStrLenth);
		if (Status == SUCCESS) {
			if (StrCopmare(FindStr, Sub) == 0) {
				FindStrIndex = Index;
				goto EXIT;
			}
		}
	}

EXIT:	
	if (Sub != NULL) {
		free(Sub);
		Sub = NULL;
	}
	
	printf("FindStrIndex = %d\n", FindStrIndex);
	printf("FindStrIndex end\n");
	return FindStrIndex;
}
```



**测试用例代码：**

```c
void TestFindStrIndex(void) {
	/*Test01*/
	char Str01[] = "abcdef";
	char FindStr01[] = "bc";
	unsigned int FindStrPos01 = 1;
	unsigned int FindRes01;
	unsigned int ComPos01 = 2;

	/*Test02*/
	char Str02[] = "abcdef";
	char FindStr02[] = "ef";
	unsigned int FindStrPos02 = 2;
	unsigned int FindRes02;
	unsigned int ComPos02 = 5;

	/*Test03*/
	char Str03[] = "abcdef";
	char FindStr03[] = "ee";
	unsigned int FindStrPos03 = 1;
	unsigned int FindRes03;
	unsigned int ComPos03 = 0;

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	FindRes01 = FindStrIndex(Str01, FindStr01, FindStrPos01);
	ValueTest(ComPos01, FindRes01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	FindRes02 = FindStrIndex(Str02, FindStr02, FindStrPos02);
	ValueTest(ComPos02, FindRes02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	FindRes03 = FindStrIndex(Str03, FindStr03, FindStrPos03);
	ValueTest(ComPos03, FindRes03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



**结果：**

> -------Test start----------
>
> -------Test 01----------
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = ab
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 2
>
> FindStrIndex end
>
> ValueTest test succeed!
>
>  
>
> -------Test 02----------
>
> FindStrIndex start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ef
>
> Str2 = ab
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ef
>
> Str2 = bc
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ef
>
> Str2 = cd
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ef
>
> Str2 = de
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ef
>
> Str2 = ef
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 5
>
> FindStrIndex end
>
> ValueTest test succeed!
>
>  
>
> -------Test 03----------
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ee
>
> Str2 = ab
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ee
>
> Str2 = bc
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ee
>
> Str2 = cd
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ee
>
> Str2 = de
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ee
>
> Str2 = ef
>
> ret = -1
>
> StrCopmare end
>
> FindStrIndex = 0
>
> FindStrIndex end
>
> ValueTest test succeed!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 3, PassNum = 3, FaildNum = 0



# 2 查找字符串——朴素匹配方法

```c
unsigned int StrNormalFindIndex(const char *Str, const char *FindStr, const unsigned int FindPos)
```

## 2.1 功能需求：

Str为主串，FindStr为要找的子串，FindPos为从主串Str的第FindPos个位置开始找子串FindStr,找到返回主串的位置，找不到返回0.

 

## 2.2 条件

​     Str与FindStr非空，且FindPos <= StrLen



## 2.3 代码

**①StrNormalFindIndex函数**

```c
unsigned int StrNormalFindIndex(const char *Str, const char *FindStr, const unsigned int FindPos) {
	unsigned int RetPos = 0;	
	char *TraStr = Str;
	char *TraFindStr = FindStr;
	unsigned int TraFindFos = FindPos;

	unsigned int TraStrLen = StringLen(TraStr);
	unsigned int TraFindStrLen = StringLen(TraFindStr);

	unsigned int StrIndexOut = TraFindFos;
	unsigned int StrIndexIn = 0;
	unsigned int FindStrIndex = 0;	

	printf("StrNormalFindIndex start\n");
	if (TraStr == NULL || TraFindStr == NULL || TraStrLen < TraFindStrLen || FindPos > TraStrLen) {
		goto EXIT;
	}

	for (StrIndexOut = TraFindFos - 1; StrIndexOut <= TraStrLen - TraFindStrLen; ++StrIndexOut) {
		for (StrIndexIn = StrIndexOut; StrIndexIn < StrIndexOut + TraFindStrLen; ++StrIndexIn) {
			if (TraStr[StrIndexIn] == TraFindStr[FindStrIndex]) {
				++FindStrIndex;
			} else {
				FindStrIndex = 0;
				break;
			}
		}
	
		if (StrIndexIn == StrIndexOut + TraFindStrLen) {
			printf("Find Success!\n");			
			RetPos = StrIndexOut + 1;
			break;
		}
	}

EXIT:
	printf("RetPos = %d\n", RetPos);
	printf("StrNormalFindIndex end\n");	
	return RetPos;
}
```



**②测试用例代码**

```c
void TestStrNormalFindIndex(void) {
	/*Test01*/
	char Str01[20] = "abcdef";
	char FindStr01[] = "bc";
	unsigned int FindPos01 = 1;
	unsigned int RetPos01;
	unsigned int CmpFindPos01 = 2;

	/*Test02*/
	char Str02[20] = "abcdef";
	char FindStr02[] = "ef";
	unsigned int FindPos02 = 2;
	unsigned int RetPos02;
	unsigned int CmpFindPos02 = 5;

	/*Test03*/
	char Str03[20] = "abcdef";
	char FindStr03[] = "ee";
	unsigned int FindPos03 = 1;
	unsigned int RetPos03;
	unsigned int CmpFindPos03 = 0;

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	RetPos01 = StrNormalFindIndex(Str01, FindStr01, FindPos01);
	printf("RetPos01 = %d\n", RetPos01);
	ValueTest(CmpFindPos01, RetPos01);
	
	/*Test02*/
	printf("\n-------Test 02----------\n");
	RetPos02 = StrNormalFindIndex(Str02, FindStr02, FindPos02);
	printf("RetPos02 = %d\n", RetPos02);
	ValueTest(CmpFindPos02, RetPos02);
	
	/*Test03*/
	printf("\n-------Test 03----------\n");
	RetPos03 = StrNormalFindIndex(Str03, FindStr03, FindPos03);
	printf("RetPos03 = %d\n", RetPos03);
	ValueTest(CmpFindPos03, RetPos03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



**结果：**

> -------Test start----------
>
> -------Test 01----------
>
> StrNormalFindIndex start
>
> Find Success!
>
> RetPos = 2
>
> StrNormalFindIndex end
>
> RetPos01 = 2
>
> ValueTest test succeed!
>
>  
>
> -------Test 02----------
>
> StrNormalFindIndex start
>
> Find Success!
>
> RetPos = 5
>
> StrNormalFindIndex end
>
> RetPos02 = 5
>
> ValueTest test succeed!
>
>  
>
> -------Test 03----------
>
> StrNormalFindIndex start
>
> RetPos = 0
>
> StrNormalFindIndex end
>
> RetPos03 = 0
>
> ValueTest test succeed!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 3, PassNum = 3, FaildNum = 0

