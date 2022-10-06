# 树的存储结构（双亲表示法，孩子双亲表示法，孩子兄弟表示法）——C语言描述

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



# 4 树的孩子双亲表示法

## 4.1 存储结构代码

采用多重链表方法。结点及它的数据和双亲采用数组方法，结点的孩子采用单链表的方法。

**代码：**

```c
/*ChildParentTree*/
#define CHILDE_PARENT_TREE_MAXSIZE			100
#define CHILD_TREE_CHILE_INDEX_SIZE			10

/*CTree*/
typedef struct _CHILD_NODE{
	int ChildIndex;
	struct _CHILD_NODE *Next;
}CHILD_NODE;

typedef struct {
	int Data;
	int Parent;
	CHILD_NODE *FirstChildIndex;
}CT_BOX;

typedef struct {
	CT_BOX Node[CHILDE_PARENT_TREE_MAXSIZE];
	int Root;
	int NodeNum;
}CHILD_PARTENT_TREE;

typedef struct {
	int Data;
	int Parent;
	int ChildNum;
	int ChildIndex[CHILD_TREE_CHILE_INDEX_SIZE];
}CHILD_PARENT_TREE_NODE_DATA;

typedef struct {
	int Root;
	int NodeNum;	
}CHILD_PARENT_TREE_ROOT_NODENUM_DATA;
```



## 4.2 构建树

```c
OP_STATUS BuildChildParentTree(CHILD_PARTENT_TREE *CPTree, const CHILD_PARENT_TREE_ROOT_NODENUM_DATA *CPTreeRootNodeNum, const CHILD_PARENT_TREE_NODE_DATA *CPTreeData) 
```

CPTree表示树，CPTreeRootNodeNum表示根的位置和结点数量，CPTreeData表示结点的数据。

**（1）构建树代码**

```c
/*ChildParentTree*/
OP_STATUS BuildChildParentTree(CHILD_PARTENT_TREE *CPTree, const CHILD_PARENT_TREE_ROOT_NODENUM_DATA *CPTreeRootNodeNum, const CHILD_PARENT_TREE_NODE_DATA *CPTreeData) {
	OP_STATUS Status = SUCCESS;
	CHILD_PARTENT_TREE *TraCPTree = CPTree;
	CHILD_PARENT_TREE_ROOT_NODENUM_DATA *TraCPTreeRootNodeNum = CPTreeRootNodeNum;
	CHILD_PARENT_TREE_NODE_DATA *TraCPTreeData = CPTreeData;

	unsigned int Index = 0;
	unsigned int NodeNum = TraCPTreeRootNodeNum->NodeNum;
	unsigned int ChildNumIndex = 0;

	CHILD_NODE	*ChildHeadNode = NULL;
	CHILD_NODE	*TraChildHeadNode = NULL;
	CHILD_NODE	*AddChildNode = NULL;
	//CHILD_NODE  *TraPrintChildNode = NULL;

	printf("BuildChildTree start\n");
	
	if (TraCPTree == NULL || TraCPTreeData == NULL) {
		Status = ERROR;
		goto EXIT;
	}

	TraCPTree->Root = TraCPTreeRootNodeNum->Root;
	TraCPTree->NodeNum = TraCPTreeRootNodeNum->NodeNum;

	for (Index = 0; Index < NodeNum; ++Index) {
		TraCPTree->Node[Index].Data = TraCPTreeData[Index].Data;
		TraCPTree->Node[Index].Parent = TraCPTreeData[Index].Parent;

		ChildHeadNode = (CHILD_NODE *)malloc(sizeof(CHILD_NODE));
		if (ChildHeadNode == NULL) {
			Status = ERROR;
			goto EXIT;
		}
		ChildHeadNode->Next = NULL;

		TraChildHeadNode = ChildHeadNode;

		/*Create CHILD_NODE Link*/
		//printf("\nTraCPTreeData[%d].ChildNum = %d\n", Index, TraCPTreeData[Index].ChildNum);
		for (ChildNumIndex = 0; ChildNumIndex < TraCPTreeData[Index].ChildNum; ++ChildNumIndex) {
			AddChildNode = (CHILD_NODE *)malloc(sizeof(CHILD_NODE));
			if (AddChildNode == NULL) {
				Status = ERROR;
				goto EXIT;
			}

			//printf("TraCPTreeData[%d].ChildIndex[%d] = %d\n", Index, ChildNumIndex, TraCPTreeData[Index].ChildIndex[ChildNumIndex]);
			AddChildNode->ChildIndex = TraCPTreeData[Index].ChildIndex[ChildNumIndex];
			AddChildNode->Next = TraChildHeadNode->Next;
			TraChildHeadNode->Next = AddChildNode;
			
			TraChildHeadNode = TraChildHeadNode->Next;
		}

		TraCPTree->Node[Index].FirstChildIndex = ChildHeadNode->Next;

		/*Print Link*/
		/*printf("\nPrint Link start\n");
		TraPrintChildNode = ChildHeadNode->Next;

		while (TraPrintChildNode != NULL) {
			printf("TraPrintChildNode->ChildIndex = %d\n", TraPrintChildNode->ChildIndex);
			TraPrintChildNode = TraPrintChildNode->Next;
		}
		printf("Print Link end\n");*/
	}

EXIT:
	printf("BuildChildTree end\n\n");
	return Status;
}
```

**（2）打印树代码**

```c
void PrintChildParentTree(const CHILD_PARTENT_TREE *CPTree) {
	CHILD_PARTENT_TREE *TraCPTree = CPTree;
	unsigned int Index = 0;
	unsigned int ChildNumIndex = 0;

	CHILD_NODE *TraChildNode = NULL;

	printf("PrintChildParentTree start\n");
	printf("TraCPTree->Root = %d, TraCPTree->NodeNum = %d\n", TraCPTree->Root, TraCPTree->NodeNum);
	for (Index = 0; Index < TraCPTree->NodeNum; ++Index) {
		printf("TraCPTree->Node[%d].Data = %d, TraCPTree->Node[%d].Parent = %d\n", Index, TraCPTree->Node[Index].Data, Index, TraCPTree->Node[Index].Parent);

		TraChildNode = TraCPTree->Node[Index].FirstChildIndex;

		while (TraChildNode != NULL) {
			printf("TraChildNode->ChildIndex = %d\n", TraChildNode->ChildIndex);
			TraChildNode = TraChildNode->Next;
		}			
	}
	
	printf("PrintChildParentTree end\n");
}
```

**(3)测试用例代码**

```c
void TestBuildChildParentTree(void) {
	/*Test01*/
	CHILD_PARTENT_TREE CPTree01;
	CHILD_PARENT_TREE_ROOT_NODENUM_DATA CPTreeRootNodeNumData01 = { 0, 7 };
	CHILD_PARENT_TREE_NODE_DATA CPTreeNodeData01[7] = { {0, -1, 2, {1, 2}},
														{10, 0, 2, {3, 4}}, {20, 0, 2, {5, 6}},
														{30, 1, 0}, {40, 1, 0}, {50, 2, 0},{60, 2, 0} };

	PARENT_TREE CmpPTree01 = { {{0, -1},
								{10, 0}, {20, 0},
								{30, 1}, {40, 1}, {50, 2}, {60, 2}}, 0, 7 };
	
	/*Test02*/
	CHILD_PARTENT_TREE CPTree02;
	CHILD_PARENT_TREE_ROOT_NODENUM_DATA CPTreeRootNodeNumData02 = {0, 10};
	CHILD_PARENT_TREE_NODE_DATA CPTreeNodeData02[10] = { {0, -1, 2, {1, 2}},
														{10, 0, 1, {3}}, {20, 0, 2, {4, 5}}, 
														{30, 1, 3, {6, 7, 8}}, {40, 2, 1, {9}}, {50, 2, 0}, 
														{60, 3, 0}, {70, 3, 0}, {80, 3, 0}, {90, 4, 0} };

	PARENT_TREE CmpPTree02 = { {{0, -1},
							{10, 0}, {20, 0},
							{30, 1}, {40, 2}, {50, 2},
							{60, 3}, {70, 3}, {80, 3}, {90, 4}}, 0, 10 };	

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	BuildChildParentTree(&CPTree01, &CPTreeRootNodeNumData01, CPTreeNodeData01);
	PrintChildParentTree(&CPTree01);
	CPTreeCmpTest(&CmpPTree01, &CPTree01, CPTreeRootNodeNumData01.NodeNum);

	/*Test02*/
	printf("-------Test 02----------\n");
	BuildChildParentTree(&CPTree02, &CPTreeRootNodeNumData02, CPTreeNodeData02);
	PrintChildParentTree(&CPTree02);
	CPTreeCmpTest(&CmpPTree02, &CPTree02, CPTreeRootNodeNumData02.NodeNum);
	
	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**（4）结果：**

> -------Test start----------
> -------Test 01----------
> BuildChildTree start
> BuildChildTree end
> PrintChildParentTree start
> TraCPTree->Root = 0, TraCPTree->NodeNum = 7
> TraCPTree->Node[0].Data = 0, TraCPTree->Node[0].Parent = -1
> TraChildNode->ChildIndex = 1
> TraChildNode->ChildIndex = 2
> TraCPTree->Node[1].Data = 10, TraCPTree->Node[1].Parent = 0
> TraChildNode->ChildIndex = 3
> TraChildNode->ChildIndex = 4
> TraCPTree->Node[2].Data = 20, TraCPTree->Node[2].Parent = 0
> TraChildNode->ChildIndex = 5
> TraChildNode->ChildIndex = 6
> TraCPTree->Node[3].Data = 30, TraCPTree->Node[3].Parent = 1
> TraCPTree->Node[4].Data = 40, TraCPTree->Node[4].Parent = 1
> TraCPTree->Node[5].Data = 50, TraCPTree->Node[5].Parent = 2
> TraCPTree->Node[6].Data = 60, TraCPTree->Node[6].Parent = 2
> PrintChildParentTree end
>
> -------Test 02----------
> BuildChildTree start
> BuildChildTree end
> PrintChildParentTree start
> TraCPTree->Root = 0, TraCPTree->NodeNum = 10
> TraCPTree->Node[0].Data = 0, TraCPTree->Node[0].Parent = -1
> TraChildNode->ChildIndex = 1
> TraChildNode->ChildIndex = 2
> TraCPTree->Node[1].Data = 10, TraCPTree->Node[1].Parent = 0
> TraChildNode->ChildIndex = 3
> TraCPTree->Node[2].Data = 20, TraCPTree->Node[2].Parent = 0
> TraChildNode->ChildIndex = 4
> TraChildNode->ChildIndex = 5
> TraCPTree->Node[3].Data = 30, TraCPTree->Node[3].Parent = 1
> TraChildNode->ChildIndex = 6
> TraChildNode->ChildIndex = 7
> TraChildNode->ChildIndex = 8
> TraCPTree->Node[4].Data = 40, TraCPTree->Node[4].Parent = 2
> TraChildNode->ChildIndex = 9
> TraCPTree->Node[5].Data = 50, TraCPTree->Node[5].Parent = 2
> TraCPTree->Node[6].Data = 60, TraCPTree->Node[6].Parent = 3
> TraCPTree->Node[7].Data = 70, TraCPTree->Node[7].Parent = 3
> TraCPTree->Node[8].Data = 80, TraCPTree->Node[8].Parent = 3
> TraCPTree->Node[9].Data = 90, TraCPTree->Node[9].Parent = 4
> PrintChildParentTree end
>
> -------Test result----------
> Print test result;
> TestNum = 2, PassNum = 2, FaildNum = 0



