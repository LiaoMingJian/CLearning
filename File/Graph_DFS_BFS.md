# 图的遍历——DFS, BFS（邻接矩阵，邻接表）——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})



# 1 图的深度优先遍历（DFS）

## 1.1 邻接矩阵

​	使用递归法

### （1） 数据结构

```c
typedef struct _LIST_NODE_DATA {
	int  Num;
	int  Vector[MAX_VEXS_SIZE];
}LIST_NODE_DATA;

typedef struct _LIST_NODE {
	int               VectorIndex;
	struct _LIST_NODE *Next;
}LIST_NODE;

typedef struct _ADJUST_LIST {
	int       Data;
	LIST_NODE *FirstEadge;
}ADJUST_LIST;

typedef struct _ADJUST_LIST_GRAPH {
	int          VectorNum;
	int          EadgeNum;
	ADJUST_LIST  AdjustGraph[MAX_VEXS_SIZE];
}ADJUST_LIST_GRAPH;

void BuildAdjustListGraph(ADJUST_LIST_GRAPH *AdjListGraph, ADJUST_LIST_GRAPH *AdjListGraphData, LIST_NODE_DATA *LstNodeData);

void PrintAdjLstGraph(const ADJUST_LIST_GRAPH *AdjListGraph01);

/*MGraphDFS*/
void MGraphDFS(M_GRAPH *MGraph, bool *Visited, int *ResultArr);
```



### （2）代码

```c
/*MGraphDFS*/
static int MGrResIndex = 0;
void MGrDFS(M_GRAPH *MGraph, bool *Visited, int i, int *ResultArr) {
	int j = 0;

	if ((MGraph == NULL) || (Visited == NULL) || (ResultArr == NULL)) {
		return;
	}

	Visited[i] = true;
	ResultArr[MGrResIndex] = i;
	MGrResIndex++;
	printf("MGraph->Vector[%d] = %d\n", i, MGraph->Vector[i]);

	for (j = 0; j < MGraph->VectorNum; j++) {
		if ((MGraph->Eadge[i][j] == 1) && (Visited[j] == false)) {
			MGrDFS(MGraph, Visited, j, ResultArr);
		}
	}
}

void MGraphDFS(M_GRAPH *MGraph, bool *Visited, int *ResultArr) {
	int i = 0;

	if ((MGraph == NULL) || (Visited == NULL) || (ResultArr == NULL)) {
		return;
	}

	MGrResIndex = 0;

	for (i = 0; i < MGraph->VectorNum; i++) {
		Visited[i] = false;
	}

	for (i = 0; i < MGraph->VectorNum; i++) {
		if (Visited[i] == false) {
			MGrDFS(MGraph, Visited, i, ResultArr);
		}
	}
}
```



###  （3）测试用例

```c
/*TestMGraphDFS*/
void TestMGraphDFS(void) {
	/*Test01*/
	M_GRAPH  MGraph01;
	int Vector01[] = { 0, 1, 2, 3 };
	// A  B  C  D  
	int Eadge01[][4] = { {0, 1, 1, 1},  //A
						{1, 0, 1, 0},  //B
						{1, 1, 0, 1},  //C
						{1, 0, 1, 0},  //D
	};
	int VectorNum01 = 4;
	int EadgeNum01 = 5;
	M_GRAPH CmpGraph01 = { 4, 5, { 0, 1, 2, 3},
								 {{0, 1, 1, 1},  //A
								  {1, 0, 1, 0},  //B
								  {1, 1, 0, 1},  //C
								  {1, 0, 1, 0},  //D
								 }
	};
	bool Visited01[4] = { 0 };
	int DFSResult01[4] = { 0 };
	int CmpVector01[] = { 0, 1, 2, 3 };

	/*Test02*/
	M_GRAPH  MGraph02;
	int Vector02[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	// A  B  C  D  E  F  G  H  I  
	int Eadge02[][9] = { {0, 1, 0, 0, 0, 1, 0, 0, 0},  //A
						{1, 0, 1, 0, 0, 0, 1, 0, 1},  //B
						{0, 1, 0, 1, 0, 0, 0, 0, 1},  //C
						{0, 0, 1, 0, 1, 0, 1, 1, 1},  //D
						{0, 0, 0, 1, 0, 1, 0, 1, 0},  //E
						{1, 0, 0, 0, 1, 0, 1, 0, 0},  //F
						{0, 1, 0, 1, 0, 1, 0, 1, 0},  //G
						{0, 0, 0, 1, 1, 0, 1, 0, 0},  //H
						{0, 1, 1, 1, 0, 0, 0, 0, 0},  //I
	};
	int VectorNum02 = 9;
	int EadgeNum02 = 15;
	M_GRAPH CmpGraph02 = { 9, 15, { 0, 1, 2, 3, 4, 5, 6, 7, 8},
								  {{0, 1, 0, 0, 0, 1, 0, 0, 0},  //A
								   {1, 0, 1, 0, 0, 0, 1, 0, 1},  //B
								   {0, 1, 0, 1, 0, 0, 0, 0, 1},  //C
								   {0, 0, 1, 0, 1, 0, 1, 1, 1},  //D
								   {0, 0, 0, 1, 0, 1, 0, 1, 0},  //E
								   {1, 0, 0, 0, 1, 0, 1, 0, 0},  //F
								   {0, 1, 0, 1, 0, 1, 0, 1, 0},  //G
								   {0, 0, 0, 1, 1, 0, 1, 0, 0},  //H
								   {0, 1, 1, 1, 0, 0, 0, 0, 0},  //I
								  }
	};
	bool Visited02[9] = { 0 };
	int DFSResult02[9] = { 0 };
	int CmpVector02[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildMGraph(&MGraph01, Vector01, (int *)Eadge01, VectorNum01, EadgeNum01);
	PrintMGraph(&MGraph01);
	//TestMGraph(&CmpGraph01, &MGraph01);
	MGraphDFS(&MGraph01, Visited01, DFSResult01);
	TestCmpArr(CmpVector01, VectorNum01, DFSResult01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildMGraph(&MGraph02, Vector02, (int *)Eadge02, VectorNum02, EadgeNum02);
	PrintMGraph(&MGraph02);
	//TestMGraph(&CmpGraph02, &MGraph02);
	MGraphDFS(&MGraph02, Visited02, DFSResult02);
	TestCmpArr(CmpVector02, VectorNum02, DFSResult02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



### （4）**打印结果**

> -------Test start----------
>
>  
>
> -------Test 01----------
>
> MGraph->VectorNum = 4
>
> MGraph->EadgeNum = 5
>
> MGraph->Vector[0] = 0
>
> MGraph->Vector[1] = 1
>
> MGraph->Vector[2] = 2
>
> MGraph->Vector[3] = 3
>
> MGraph->Vector[0][0] = 0, MGraph->Vector[0][1] = 1, MGraph->Vector[0][2] = 1, MGraph->Vector[0][3] = 1,
>
> MGraph->Vector[1][0] = 1, MGraph->Vector[1][1] = 0, MGraph->Vector[1][2] = 1, MGraph->Vector[1][3] = 0,
>
> MGraph->Vector[2][0] = 1, MGraph->Vector[2][1] = 1, MGraph->Vector[2][2] = 0, MGraph->Vector[2][3] = 1,
>
> MGraph->Vector[3][0] = 1, MGraph->Vector[3][1] = 0, MGraph->Vector[3][2] = 1, MGraph->Vector[3][3] = 0,
>
> MGraph->Vector[0] = 0
>
> MGraph->Vector[1] = 1
>
> MGraph->Vector[2] = 2
>
> MGraph->Vector[3] = 3
>
> Correct!
>
>  
>
> -------Test 02----------
>
> MGraph->VectorNum = 9
>
> MGraph->EadgeNum = 15
>
> MGraph->Vector[0] = 0
>
> MGraph->Vector[1] = 1
>
> MGraph->Vector[2] = 2
>
> MGraph->Vector[3] = 3
>
> MGraph->Vector[4] = 4
>
> MGraph->Vector[5] = 5
>
> MGraph->Vector[6] = 6
>
> MGraph->Vector[7] = 7
>
> MGraph->Vector[8] = 8
>
> MGraph->Vector[0][0] = 0, MGraph->Vector[0][1] = 1, MGraph->Vector[0][2] = 0, MGraph->Vector[0][3] = 0, MGraph->Vector[0][4] = 0, MGraph->Vector[0][5] = 1, MGraph->Vector[0][6] = 0, MGraph->Vector[0][7] = 0, MGraph->Vector[0][8] = 0,
>
> MGraph->Vector[1][0] = 1, MGraph->Vector[1][1] = 0, MGraph->Vector[1][2] = 1, MGraph->Vector[1][3] = 0, MGraph->Vector[1][4] = 0, MGraph->Vector[1][5] = 0, MGraph->Vector[1][6] = 1, MGraph->Vector[1][7] = 0, MGraph->Vector[1][8] = 1,
>
> MGraph->Vector[2][0] = 0, MGraph->Vector[2][1] = 1, MGraph->Vector[2][2] = 0, MGraph->Vector[2][3] = 1, MGraph->Vector[2][4] = 0, MGraph->Vector[2][5] = 0, MGraph->Vector[2][6] = 0, MGraph->Vector[2][7] = 0, MGraph->Vector[2][8] = 1,
>
> MGraph->Vector[3][0] = 0, MGraph->Vector[3][1] = 0, MGraph->Vector[3][2] = 1, MGraph->Vector[3][3] = 0, MGraph->Vector[3][4] = 1, MGraph->Vector[3][5] = 0, MGraph->Vector[3][6] = 1, MGraph->Vector[3][7] = 1, MGraph->Vector[3][8] = 1,
>
> MGraph->Vector[4][0] = 0, MGraph->Vector[4][1] = 0, MGraph->Vector[4][2] = 0, MGraph->Vector[4][3] = 1, MGraph->Vector[4][4] = 0, MGraph->Vector[4][5] = 1, MGraph->Vector[4][6] = 0, MGraph->Vector[4][7] = 1, MGraph->Vector[4][8] = 0,
>
> MGraph->Vector[5][0] = 1, MGraph->Vector[5][1] = 0, MGraph->Vector[5][2] = 0, MGraph->Vector[5][3] = 0, MGraph->Vector[5][4] = 1, MGraph->Vector[5][5] = 0, MGraph->Vector[5][6] = 1, MGraph->Vector[5][7] = 0, MGraph->Vector[5][8] = 0,
>
> MGraph->Vector[6][0] = 0, MGraph->Vector[6][1] = 1, MGraph->Vector[6][2] = 0, MGraph->Vector[6][3] = 1, MGraph->Vector[6][4] = 0, MGraph->Vector[6][5] = 1, MGraph->Vector[6][6] = 0, MGraph->Vector[6][7] = 1, MGraph->Vector[6][8] = 0,
>
> MGraph->Vector[7][0] = 0, MGraph->Vector[7][1] = 0, MGraph->Vector[7][2] = 0, MGraph->Vector[7][3] = 1, MGraph->Vector[7][4] = 1, MGraph->Vector[7][5] = 0, MGraph->Vector[7][6] = 1, MGraph->Vector[7][7] = 0, MGraph->Vector[7][8] = 0,
>
> MGraph->Vector[8][0] = 0, MGraph->Vector[8][1] = 1, MGraph->Vector[8][2] = 1, MGraph->Vector[8][3] = 1, MGraph->Vector[8][4] = 0, MGraph->Vector[8][5] = 0, MGraph->Vector[8][6] = 0, MGraph->Vector[8][7] = 0, MGraph->Vector[8][8] = 0,
>
> MGraph->Vector[0] = 0
>
> MGraph->Vector[1] = 1
>
> MGraph->Vector[2] = 2
>
> MGraph->Vector[3] = 3
>
> MGraph->Vector[4] = 4
>
> MGraph->Vector[5] = 5
>
> MGraph->Vector[6] = 6
>
> MGraph->Vector[7] = 7
>
> MGraph->Vector[8] = 8
>
> Correct!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0



## 1.2 邻接表

​	使用递归法

### （1） 数据结构

```c
/*ADJUST_LIST_GRAPH*/
typedef struct _LIST_NODE_DATA {
	int  Num;
	int  Vector[MAX_VEXS_SIZE];
}LIST_NODE_DATA;

typedef struct _LIST_NODE {
	int               VectorIndex;
	struct _LIST_NODE *Next;
}LIST_NODE;

typedef struct _ADJUST_LIST {
	int       Data;
	LIST_NODE *FirstEadge;
}ADJUST_LIST;

typedef struct _ADJUST_LIST_GRAPH {
	int          VectorNum;
	int          EadgeNum;
	ADJUST_LIST  AdjustGraph[MAX_VEXS_SIZE];
}ADJUST_LIST_GRAPH;

void BuildAdjustListGraph(ADJUST_LIST_GRAPH *AdjListGraph, ADJUST_LIST_GRAPH *AdjListGraphData, LIST_NODE_DATA *LstNodeData);

void PrintAdjLstGraph(const ADJUST_LIST_GRAPH *AdjListGraph01);
```



### （2） 代码

```c
/*AdjLstGraphDFS*/
static int AdjLstResIndex = 0;
void AdjLstGDFS(ADJUST_LIST_GRAPH *AdjLstGraph, bool *Visited, int i, int *ResultArr) {
	LIST_NODE *LstNode = NULL;
	if ((AdjLstGraph == NULL) || (Visited == NULL) || (ResultArr == NULL)) {
		return;
	}

	Visited[i] = true;
	ResultArr[AdjLstResIndex] = i;
	AdjLstResIndex++;
	printf("AdjLstGraph->AdjustGraph[%d].Data = %d\n", i, AdjLstGraph->AdjustGraph[i].Data);

	LstNode = AdjLstGraph->AdjustGraph[i].FirstEadge;
	while (LstNode != NULL) {
		if (Visited[LstNode->VectorIndex] == false) {
			AdjLstGDFS(AdjLstGraph, Visited, LstNode->VectorIndex, ResultArr);
		}
		LstNode = LstNode->Next;
	}
}

void AdjLstGraphDFS(ADJUST_LIST_GRAPH *AdjLstGraph, bool *Visited, int *ResultArr) {
	int i = 0;

	if ((AdjLstGraph == NULL) || (Visited == NULL) || (ResultArr == NULL)) {
		return;
	}

	AdjLstResIndex = 0;

	for (i = 0; i < AdjLstGraph->VectorNum; i++) {
		Visited[i] = false;
	}

	for (i = 0; i < AdjLstGraph->VectorNum; i++) {
		if (Visited[i] == false) {
			AdjLstGDFS(AdjLstGraph, Visited, i, ResultArr);
		}
	}
}
```



### （3）测试用例

```c
/*TestAdjLstGraphDFS*/
void TestAdjLstGraphDFS(void) {
	/*Test01*/
	ADJUST_LIST_GRAPH  AdjListGraph01;
	ADJUST_LIST_GRAPH  AdjListGraphData01 = { 4, 5, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}} };
	LIST_NODE_DATA     AdjListNodeData01[] = { {3, {1, 2, 3}}, {2, {0, 2}}, {3, {0, 1, 3}}, {2, {0, 2}} };
	bool Visited01[4] = { 0 };
	int VectorNum01 = 4;
	int DFSResult01[4] = { 0 };
	int CmpVector01[] = { 0, 1, 2, 3 };

	/*Test02*/
	ADJUST_LIST_GRAPH  AdjListGraph02;               //A          B           C           D           E           F           G           H           I
	ADJUST_LIST_GRAPH  AdjListGraphData02 = { 9, 15, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}, {40, NULL}, {50, NULL}, {60, NULL}, {70, NULL}, {80, NULL},
													}
	};
	//A            B                  C               D                     E               F               G                  H               I
	LIST_NODE_DATA     AdjListNodeData02[] = { {2, {1, 5}}, {4, {0, 2, 6, 8}}, {3, {1, 3, 8}}, {5, {2, 4, 6, 7, 8}}, {3, {3, 5, 7}}, {3, {0, 4, 6}}, {4, {1, 3, 5, 7}}, {3, {3, 4, 6}}, {3, {1, 2, 3}}
	};
	ADJUST_LIST_GRAPH  CmpAdjListGraph02 = { 9, 15, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}, {40, NULL}, {50, NULL}, {60, NULL}, {70, NULL}, {80, NULL},
													}
	};
	bool Visited02[9] = { 0 };
	int VectorNum02 = 9;
	int DFSResult02[9] = { 0 };
	int CmpVector02[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildAdjustListGraph(&AdjListGraph01, &AdjListGraphData01, AdjListNodeData01);
	PrintAdjLstGraph(&AdjListGraph01);
	AdjLstGraphDFS(&AdjListGraph01, Visited01, DFSResult01);
	TestCmpArr(CmpVector01, VectorNum01, DFSResult01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildAdjustListGraph(&AdjListGraph02, &AdjListGraphData02, AdjListNodeData02);
	PrintAdjLstGraph(&AdjListGraph02);
	AdjLstGraphDFS(&AdjListGraph02, Visited02, DFSResult02);
	TestCmpArr(CmpVector02, VectorNum02, DFSResult02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



### （4）结果

> -------Test start----------
>
>  
>
> -------Test 01----------
>
> AdjLstGraph->VectorNum = 4
>
> AdjLstGraph->EadgeNum = 5
>
> AdjLstGraph->AdjustGraph[0].Data = 0
>
> LstNode->VectorIndex = 1
>
> LstNode->VectorIndex = 2
>
> LstNode->VectorIndex = 3
>
> AdjLstGraph->AdjustGraph[1].Data = 10
>
> LstNode->VectorIndex = 0
>
> LstNode->VectorIndex = 2
>
> AdjLstGraph->AdjustGraph[2].Data = 20
>
> LstNode->VectorIndex = 0
>
> LstNode->VectorIndex = 1
>
> LstNode->VectorIndex = 3
>
> AdjLstGraph->AdjustGraph[3].Data = 30
>
> LstNode->VectorIndex = 0
>
> LstNode->VectorIndex = 2
>
> AdjLstGraph->AdjustGraph[0].Data = 0
>
> AdjLstGraph->AdjustGraph[1].Data = 10
>
> AdjLstGraph->AdjustGraph[2].Data = 20
>
> AdjLstGraph->AdjustGraph[3].Data = 30
>
> Correct!
>
>  
>
> -------Test 02----------
>
> AdjLstGraph->VectorNum = 9
>
> AdjLstGraph->EadgeNum = 15
>
> AdjLstGraph->AdjustGraph[0].Data = 0
>
> LstNode->VectorIndex = 1
>
> LstNode->VectorIndex = 5
>
> AdjLstGraph->AdjustGraph[1].Data = 10
>
> LstNode->VectorIndex = 0
>
> LstNode->VectorIndex = 2
>
> LstNode->VectorIndex = 6
>
> LstNode->VectorIndex = 8
>
> AdjLstGraph->AdjustGraph[2].Data = 20
>
> LstNode->VectorIndex = 1
>
> LstNode->VectorIndex = 3
>
> LstNode->VectorIndex = 8
>
> AdjLstGraph->AdjustGraph[3].Data = 30
>
> LstNode->VectorIndex = 2
>
> LstNode->VectorIndex = 4
>
> LstNode->VectorIndex = 6
>
> LstNode->VectorIndex = 7
>
> LstNode->VectorIndex = 8
>
> AdjLstGraph->AdjustGraph[4].Data = 40
>
> LstNode->VectorIndex = 3
>
> LstNode->VectorIndex = 5
>
> LstNode->VectorIndex = 7
>
> AdjLstGraph->AdjustGraph[5].Data = 50
>
> LstNode->VectorIndex = 0
>
> LstNode->VectorIndex = 4
>
> LstNode->VectorIndex = 6
>
> AdjLstGraph->AdjustGraph[6].Data = 60
>
> LstNode->VectorIndex = 1
>
> LstNode->VectorIndex = 3
>
> LstNode->VectorIndex = 5
>
> LstNode->VectorIndex = 7
>
> AdjLstGraph->AdjustGraph[7].Data = 70
>
> LstNode->VectorIndex = 3
>
> LstNode->VectorIndex = 4
>
> LstNode->VectorIndex = 6
>
> AdjLstGraph->AdjustGraph[8].Data = 80
>
> LstNode->VectorIndex = 1
>
> LstNode->VectorIndex = 2
>
> LstNode->VectorIndex = 3
>
> AdjLstGraph->AdjustGraph[0].Data = 0
>
> AdjLstGraph->AdjustGraph[1].Data = 10
>
> AdjLstGraph->AdjustGraph[2].Data = 20
>
> AdjLstGraph->AdjustGraph[3].Data = 30
>
> AdjLstGraph->AdjustGraph[4].Data = 40
>
> AdjLstGraph->AdjustGraph[5].Data = 50
>
> AdjLstGraph->AdjustGraph[6].Data = 60
>
> AdjLstGraph->AdjustGraph[7].Data = 70
>
> AdjLstGraph->AdjustGraph[8].Data = 80
>
> Correct!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0



# 2 图的广度度优先遍历（BFS）

​	看做层序遍历，引入队列

## 2.1 队列

​	先进先出的数据结构

### （1）数据结构

```c
/*LINK_QUEUE*/
typedef struct _LINK_NODE {
	int Data;
	struct _LINK_NODE *Next;
}LINK_NODE;

typedef struct _LINK_QUEUE {
	LINK_NODE *Front;
	LINK_NODE *Rear;
}LINK_QUEUE;

void InitLinkQueue(LINK_QUEUE **LinkQueue);
void BuildLinkQueue(LINK_QUEUE *LinkQueue, int Num, int *DataArr);
void PrintLinkQueue(LINK_QUEUE *LinkQueue);
void DestoryLinkQueue(LINK_QUEUE *LinkQueue);
void EnterLinkQueue(LINK_QUEUE *LinkQueue, int AddData);
void ExitLinkQueue(LINK_QUEUE *LinkQueue, int *ExitData);
```

### （2）初始化，打印，入队， 创建队列，出队，销毁队列

```c
/*LinkQueue*/
void InitLinkQueue(LINK_QUEUE **LinkQueue) {
	if (LinkQueue == NULL) {
		return;
	}

	*LinkQueue = (LINK_QUEUE *)malloc(sizeof(LINK_QUEUE));
	if (*LinkQueue == NULL) {
		return;
	}
	(*LinkQueue)->Front = NULL;
	(*LinkQueue)->Rear = NULL;
}

void PrintLinkQueue(LINK_QUEUE *LinkQueue) {
	LINK_NODE *PNode = NULL;

	if (LinkQueue == NULL) {
		return;
	}

	// printf("LinkQueue->Front = 0x%lx\n", LinkQueue->Front);
	// printf("LinkQueue->Rear = 0x%lx\n", LinkQueue->Rear);

	PNode = LinkQueue->Front;
	while (PNode != NULL) {
		//printf("PNode = 0x%lx, PNode->Data = %d, PNode->Next = 0x%lx\n", PNode, PNode->Data, PNode->Next);
		printf("PNode->Data = %d\n", PNode->Data);
		PNode = PNode->Next;
	}

	return;
}

void EnterLinkQueue(LINK_QUEUE *LinkQueue, int AddData) {
	LINK_NODE *AddNode = NULL;

	if (LinkQueue == NULL) {
		return;
	}

	AddNode = (LINK_NODE *)malloc(sizeof(LINK_NODE));
	if (AddNode == NULL) {
		return;
	}
	AddNode->Data = AddData;
	AddNode->Next = NULL;

	if (LinkQueue->Front == NULL) {
		LinkQueue->Front = AddNode;
		LinkQueue->Rear = AddNode;
	}
	else {
		AddNode->Next = LinkQueue->Rear->Next;
		LinkQueue->Rear->Next = AddNode;
		LinkQueue->Rear = LinkQueue->Rear->Next;
	}
}

void BuildLinkQueue(LINK_QUEUE *LinkQueue, int Num, int *DataArr) {
	int i = 0;

	if ((LinkQueue == NULL) || (DataArr == NULL)) {
		return;
	}

	for (i = 0; i < Num; ++i) {
		EnterLinkQueue(LinkQueue, DataArr[i]);
	}
}


```



### （3）创建队列测试用例

```c
/*TestBuildLinkQueue*/
void CmpLinkQueue(const int *CmpArr, const int Num, const LINK_NODE *LinkNode) {
	int        i = 0;
	LINK_NODE  *PNode = NULL;

	TestNum++;
	if ((CmpArr == NULL) || (LinkNode == NULL)) {
		FaildNum++;
		return;
	}

	PNode = (LINK_NODE *)LinkNode;
	while ((i < Num) && (PNode != NULL)) {
		if (CmpArr[i] != PNode->Data) {
			FaildNum++;
			return;
		}

		i++;
		PNode = PNode->Next;
	}

	PassNum++;
}

void TestBuildLinkQueue(void) {
	/*Test01*/
	LINK_QUEUE  *LinkQueue01 = NULL;
	int         Num01 = 3;
	int         DataArr01[3] = { 0, 10, 20 };
	int         CmpDataArr01[3] = { 0, 10, 20 };

	/*Test02*/
	LINK_QUEUE  *LinkQueue02 = NULL;
	int         Num02 = 1;
	int         DataArr02[1] = { 10 };
	int         CmpDataArr02[1] = { 10 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	InitLinkQueue(&LinkQueue01);
	BuildLinkQueue(LinkQueue01, Num01, DataArr01);
	PrintLinkQueue(LinkQueue01);
	CmpLinkQueue(CmpDataArr01, Num01, LinkQueue01->Front);
	DestoryLinkQueue(LinkQueue01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	InitLinkQueue(&LinkQueue02);
	BuildLinkQueue(LinkQueue02, Num02, DataArr02);
	PrintLinkQueue(LinkQueue02);
	CmpLinkQueue(CmpDataArr02, Num02, LinkQueue02->Front);
	DestoryLinkQueue(LinkQueue02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

void ExitLinkQueue(LINK_QUEUE *LinkQueue, int *ExitData) {
	LINK_NODE *DelNode = NULL;

	if ((LinkQueue == NULL) || (LinkQueue->Front == NULL)) {
		return;
	}

	if (LinkQueue->Front == LinkQueue->Rear) {
		LinkQueue->Rear = NULL;
	}

	*ExitData = LinkQueue->Front->Data;
	DelNode = LinkQueue->Front;
	LinkQueue->Front = LinkQueue->Front->Next;

	free(DelNode);
	DelNode = NULL;
}

void DestoryLinkQueue(LINK_QUEUE *LinkQueue) {
	LINK_NODE *PNode = NULL;
	LINK_NODE *DelNode = NULL;

	if ((LinkQueue == NULL) || (LinkQueue->Front == NULL)) {
		return;
	}

	PNode = LinkQueue->Front;
	while (PNode != NULL) {
		DelNode = PNode;
		PNode = PNode->Next;

		free(DelNode);
		DelNode = NULL;
	}

	LinkQueue->Front = NULL;
	LinkQueue->Rear = NULL;
	return;
}
```

**结果：**

> -------Test start----------
>
>  
>
> -------Test 01----------
>
> PNode->Data = 0
>
> PNode->Data = 10
>
> PNode->Data = 20
>
>  
>
> -------Test 02----------
>
> PNode->Data = 10
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0



### （4）出队测试用例

```c
/*TestExitLinkQueue*/
void CmpExitLinkQueue(const int *CmpDataArr, const int Num, const LINK_NODE *LinkNode, const int CmpValue, const int ResultValue) {
	TestNum++;

	if ((CmpDataArr == NULL) && (LinkNode == 0) && (Num == 0)) {
		PassNum++;
		return;
	}

	if (CmpValue != ResultValue) {
		FaildNum++;
		return;
	}

	TestNum--;
	CmpLinkQueue(CmpDataArr, Num, LinkNode);
}

void TestExitLinkQueue(void) {
	/*Test01*/
	LINK_QUEUE  *LinkQueue01 = NULL;
	int         Num01 = 3;
	int         DataArr01[3] = { 10, 20, 30 };
	int         ExitResultValue01 = 0;
	int         CmpExitValue01 = 10;
	int         CmpDataArr01[2] = { 20, 30 };

	/*Test02*/
	LINK_QUEUE  *LinkQueue02 = NULL;
	int         Num02 = 1;
	int         DataArr02[1] = { 10 };
	int         ExitResultValue02 = 0;
	int         CmpExitValue02 = 10;
	int         *CmpDataArr02 = NULL;

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	InitLinkQueue(&LinkQueue01);
	BuildLinkQueue(LinkQueue01, Num01, DataArr01);
	PrintLinkQueue(LinkQueue01);
	ExitLinkQueue(LinkQueue01, &ExitResultValue01);
	CmpExitLinkQueue(CmpDataArr01, Num01 - 1, LinkQueue01->Front, CmpExitValue01, ExitResultValue01);
	DestoryLinkQueue(LinkQueue01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	InitLinkQueue(&LinkQueue02);
	BuildLinkQueue(LinkQueue02, Num02, DataArr02);
	PrintLinkQueue(LinkQueue02);
	ExitLinkQueue(LinkQueue02, &ExitResultValue02);
	printf("\n");
	printf("ExitResultValue02 = %d\n", ExitResultValue02);
	PrintLinkQueue(LinkQueue02);
	CmpExitLinkQueue(CmpDataArr02, Num02 - 1, LinkQueue02->Front, CmpExitValue02, ExitResultValue02);
	DestoryLinkQueue(LinkQueue02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**结果：**

> -------Test start----------
>
>  
>
> -------Test 01----------
>
> PNode->Data = 10
>
> PNode->Data = 20
>
> PNode->Data = 30
>
>  
>
> -------Test 02----------
>
> PNode->Data = 10
>
>  
>
> ExitResultValue02 = 10
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0



## 2.2 邻接矩阵

​	看做层序遍历

### （1）数据结构

```c
/*M_GRAPH*/
#define MAX_VEXS_SIZE    (100)
#define MAX_VALUE        (65535)
#pragma pack(1)
typedef struct _M_GRAPH {
	int VectorNum;
	int EadgeNum;
	int Vector[MAX_VEXS_SIZE];
	int Eadge[MAX_VEXS_SIZE][MAX_VEXS_SIZE];
}M_GRAPH;
#pragma pack()

void PrintMGraph(M_GRAPH *MGraph);
void BuildMGraph(M_GRAPH *MGraph, int *Vector, int *Eadge, int VectorNum, int EadgeNum);

/*MGraghBFS*/
void MGraghBFS(M_GRAPH *MGraph, bool *Visited, int *ResultArr);
```



### （2）代码

```c
/*MGraghBFS*/
static int MGrBFSResIndex = 0;
void MGrBFS(M_GRAPH *MGraph, LINK_QUEUE *LstQueue, bool *Visited, int i, int *ResultArr) {
	int QIndex = 0;
	int j = 0;

	if ((MGraph == NULL) || (LstQueue == NULL) || (Visited == NULL) || (ResultArr == NULL)) {
		return;
	}

	Visited[i] = true;
	ResultArr[MGrBFSResIndex] = i;
	MGrBFSResIndex++;
	printf("MGraph->Vector[%d] = %d\n", i, MGraph->Vector[i]);

	EnterLinkQueue(LstQueue, i);
	while (IsLinkQueueEmpty(LstQueue) == false) {
		ExitLinkQueue(LstQueue, &QIndex);
		for (j = 0; j < MGraph->VectorNum; ++j) {
			if ((MGraph->Eadge[QIndex][j] == 1) && (Visited[j] == false)) {
				Visited[j] = true;
				ResultArr[MGrBFSResIndex] = j;
				MGrBFSResIndex++;
				printf("MGraph->Vector[%d] = %d\n", j, MGraph->Vector[j]);

				EnterLinkQueue(LstQueue, j);
			}
		}
	}
}

void MGraghBFS(M_GRAPH *MGraph, bool *Visited, int *ResultArr) {
	int i = 0;
	LINK_QUEUE *LstQueue = NULL;

	if ((MGraph == NULL) || (Visited == NULL) || (ResultArr == NULL)) {
		return;
	}

	MGrBFSResIndex = 0;

	for (i = 0; i < MGraph->VectorNum; i++) {
		Visited[i] = false;
	}

	InitLinkQueue(&LstQueue);
	for (i = 0; i < MGraph->VectorNum; i++) {
		if (Visited[i] == false) {
			MGrBFS(MGraph, LstQueue, Visited, i, ResultArr);
		}
	}
```



### （3）测试用例

```c
/*TestMGraghBFS*/
void TestMGraghBFS(void) {
	/*Test01*/
	M_GRAPH  MGraph01;
	int Vector01[] = { 0, 1, 2, 3 };
	// A  B  C  D  
	int Eadge01[][4] = { {0, 1, 1, 1},  //A
						{1, 0, 1, 0},  //B
						{1, 1, 0, 1},  //C
						{1, 0, 1, 0},  //D
	};
	int VectorNum01 = 4;
	int EadgeNum01 = 5;
	M_GRAPH CmpGraph01 = { 4, 5, { 0, 1, 2, 3},
								 {{0, 1, 1, 1},  //A
								  {1, 0, 1, 0},  //B
								  {1, 1, 0, 1},  //C
								  {1, 0, 1, 0},  //D
								 }
	};
	bool Visited01[4] = { 0 };
	int BFSResult01[4] = { 0 };
	int CmpVector01[] = { 0, 1, 2, 3 };

	/*Test02*/
	M_GRAPH  MGraph02;
	int Vector02[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	// A  B  C  D  E  F  G  H  I  
	int Eadge02[][9] = { {0, 1, 0, 0, 0, 1, 0, 0, 0},  //A
						{1, 0, 1, 0, 0, 0, 1, 0, 1},  //B
						{0, 1, 0, 1, 0, 0, 0, 0, 1},  //C
						{0, 0, 1, 0, 1, 0, 1, 1, 1},  //D
						{0, 0, 0, 1, 0, 1, 0, 1, 0},  //E
						{1, 0, 0, 0, 1, 0, 1, 0, 0},  //F
						{0, 1, 0, 1, 0, 1, 0, 1, 0},  //G
						{0, 0, 0, 1, 1, 0, 1, 0, 0},  //H
						{0, 1, 1, 1, 0, 0, 0, 0, 0},  //I
	};
	int VectorNum02 = 9;
	int EadgeNum02 = 15;
	M_GRAPH CmpGraph02 = { 9, 15, { 0, 1, 2, 3, 4, 5, 6, 7, 8},
								  {{0, 1, 0, 0, 0, 1, 0, 0, 0},  //A
								   {1, 0, 1, 0, 0, 0, 1, 0, 1},  //B
								   {0, 1, 0, 1, 0, 0, 0, 0, 1},  //C
								   {0, 0, 1, 0, 1, 0, 1, 1, 1},  //D
								   {0, 0, 0, 1, 0, 1, 0, 1, 0},  //E
								   {1, 0, 0, 0, 1, 0, 1, 0, 0},  //F
								   {0, 1, 0, 1, 0, 1, 0, 1, 0},  //G
								   {0, 0, 0, 1, 1, 0, 1, 0, 0},  //H
								   {0, 1, 1, 1, 0, 0, 0, 0, 0},  //I
								  }
	};
	bool Visited02[9] = { 0 };
	int BFSResult02[9] = { 0 };
	int CmpVector02[] = { 0, 1, 5, 2, 6, 8, 4, 3, 7 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildMGraph(&MGraph01, Vector01, (int *)Eadge01, VectorNum01, EadgeNum01);
	PrintMGraph(&MGraph01);
	//TestMGraph(&CmpGraph01, &MGraph01);
	MGraghBFS(&MGraph01, Visited01, BFSResult01);
	TestCmpArr(CmpVector01, VectorNum01, BFSResult01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildMGraph(&MGraph02, Vector02, (int *)Eadge02, VectorNum02, EadgeNum02);
	PrintMGraph(&MGraph02);
	printf("\nBFS\n");
	//TestMGraph(&CmpGraph02, &MGraph02);
	MGraghBFS(&MGraph02, Visited02, BFSResult02);
	printf("\nCmp\n");
	TestCmpArr(CmpVector02, VectorNum02, BFSResult02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



### （4）结果

>-------Test start----------
>
> 
>
>-------Test 01----------
>
>MGraph->VectorNum = 4
>
>MGraph->EadgeNum = 5
>
>MGraph->Vector[0] = 0
>
>MGraph->Vector[1] = 1
>
>MGraph->Vector[2] = 2
>
>MGraph->Vector[3] = 3
>
>MGraph->Vector[0][0] = 0, MGraph->Vector[0][1] = 1, MGraph->Vector[0][2] = 1, MGraph->Vector[0][3] = 1,
>
>MGraph->Vector[1][0] = 1, MGraph->Vector[1][1] = 0, MGraph->Vector[1][2] = 1, MGraph->Vector[1][3] = 0,
>
>MGraph->Vector[2][0] = 1, MGraph->Vector[2][1] = 1, MGraph->Vector[2][2] = 0, MGraph->Vector[2][3] = 1,
>
>MGraph->Vector[3][0] = 1, MGraph->Vector[3][1] = 0, MGraph->Vector[3][2] = 1, MGraph->Vector[3][3] = 0,
>
>MGraph->Vector[0] = 0
>
>MGraph->Vector[1] = 1
>
>MGraph->Vector[2] = 2
>
>MGraph->Vector[3] = 3
>
>Correct!
>
> 
>
>-------Test 02----------
>
>MGraph->VectorNum = 9
>
>MGraph->EadgeNum = 15
>
>MGraph->Vector[0] = 0
>
>MGraph->Vector[1] = 1
>
>MGraph->Vector[2] = 2
>
>MGraph->Vector[3] = 3
>
>MGraph->Vector[4] = 4
>
>MGraph->Vector[5] = 5
>
>MGraph->Vector[6] = 6
>
>MGraph->Vector[7] = 7
>
>MGraph->Vector[8] = 8
>
>MGraph->Vector[0][0] = 0, MGraph->Vector[0][1] = 1, MGraph->Vector[0][2] = 0, MGraph->Vector[0][3] = 0, MGraph->Vector[0][4] = 0, MGraph->Vector[0][5] = 1, MGraph->Vector[0][6] = 0, MGraph->Vector[0][7] = 0, MGraph->Vector[0][8] = 0,
>
>MGraph->Vector[1][0] = 1, MGraph->Vector[1][1] = 0, MGraph->Vector[1][2] = 1, MGraph->Vector[1][3] = 0, MGraph->Vector[1][4] = 0, MGraph->Vector[1][5] = 0, MGraph->Vector[1][6] = 1, MGraph->Vector[1][7] = 0, MGraph->Vector[1][8] = 1,
>
>MGraph->Vector[2][0] = 0, MGraph->Vector[2][1] = 1, MGraph->Vector[2][2] = 0, MGraph->Vector[2][3] = 1, MGraph->Vector[2][4] = 0, MGraph->Vector[2][5] = 0, MGraph->Vector[2][6] = 0, MGraph->Vector[2][7] = 0, MGraph->Vector[2][8] = 1,
>
>MGraph->Vector[3][0] = 0, MGraph->Vector[3][1] = 0, MGraph->Vector[3][2] = 1, MGraph->Vector[3][3] = 0, MGraph->Vector[3][4] = 1, MGraph->Vector[3][5] = 0, MGraph->Vector[3][6] = 1, MGraph->Vector[3][7] = 1, MGraph->Vector[3][8] = 1,
>
>MGraph->Vector[4][0] = 0, MGraph->Vector[4][1] = 0, MGraph->Vector[4][2] = 0, MGraph->Vector[4][3] = 1, MGraph->Vector[4][4] = 0, MGraph->Vector[4][5] = 1, MGraph->Vector[4][6] = 0, MGraph->Vector[4][7] = 1, MGraph->Vector[4][8] = 0,
>
>MGraph->Vector[5][0] = 1, MGraph->Vector[5][1] = 0, MGraph->Vector[5][2] = 0, MGraph->Vector[5][3] = 0, MGraph->Vector[5][4] = 1, MGraph->Vector[5][5] = 0, MGraph->Vector[5][6] = 1, MGraph->Vector[5][7] = 0, MGraph->Vector[5][8] = 0,
>
>MGraph->Vector[6][0] = 0, MGraph->Vector[6][1] = 1, MGraph->Vector[6][2] = 0, MGraph->Vector[6][3] = 1, MGraph->Vector[6][4] = 0, MGraph->Vector[6][5] = 1, MGraph->Vector[6][6] = 0, MGraph->Vector[6][7] = 1, MGraph->Vector[6][8] = 0,
>
>MGraph->Vector[7][0] = 0, MGraph->Vector[7][1] = 0, MGraph->Vector[7][2] = 0, MGraph->Vector[7][3] = 1, MGraph->Vector[7][4] = 1, MGraph->Vector[7][5] = 0, MGraph->Vector[7][6] = 1, MGraph->Vector[7][7] = 0, MGraph->Vector[7][8] = 0,
>
>MGraph->Vector[8][0] = 0, MGraph->Vector[8][1] = 1, MGraph->Vector[8][2] = 1, MGraph->Vector[8][3] = 1, MGraph->Vector[8][4] = 0, MGraph->Vector[8][5] = 0, MGraph->Vector[8][6] = 0, MGraph->Vector[8][7] = 0, MGraph->Vector[8][8] = 0,
>
> 
>
>BFS
>
>MGraph->Vector[0] = 0
>
>MGraph->Vector[1] = 1
>
>MGraph->Vector[5] = 5
>
>MGraph->Vector[2] = 2
>
>MGraph->Vector[6] = 6
>
>MGraph->Vector[8] = 8
>
>MGraph->Vector[4] = 4
>
>MGraph->Vector[3] = 3
>
>MGraph->Vector[7] = 7
>
> 
>
>Cmp
>
>Correct!
>
> 
>
>-------Test result----------
>
>Print test result;
>
>TestNum = 2, PassNum = 2, FaildNum = 0



## 2.2 邻接表

​	看做层序遍历

### （1）数据结构

```c
typedef struct _LIST_NODE_DATA {
	int  Num;
	int  Vector[MAX_VEXS_SIZE];
}LIST_NODE_DATA;

typedef struct _LIST_NODE {
	int               VectorIndex;
	struct _LIST_NODE *Next;
}LIST_NODE;

typedef struct _ADJUST_LIST {
	int       Data;
	LIST_NODE *FirstEadge;
}ADJUST_LIST;

typedef struct _ADJUST_LIST_GRAPH {
	int          VectorNum;
	int          EadgeNum;
	ADJUST_LIST  AdjustGraph[MAX_VEXS_SIZE];
}ADJUST_LIST_GRAPH;

void BuildAdjustListGraph(ADJUST_LIST_GRAPH *AdjListGraph, ADJUST_LIST_GRAPH *AdjListGraphData, LIST_NODE_DATA *LstNodeData);

void PrintAdjLstGraph(const ADJUST_LIST_GRAPH *AdjListGraph01);

/*AdjLstGraphBFS*/
void AdjLstGraphBFS(ADJUST_LIST_GRAPH *AdjLstGraph, bool *Visited, int *ResultArr);
```



### （2）代码

```c
/*AdjLstGraphBFS*/
static int AdjLStBFSResIndex = 0;
void AdjLstGrBFS(ADJUST_LIST_GRAPH *AdjLstGraph, LINK_QUEUE *LstQueue, bool *Visited, int i, int *ResultArr) {
	int QIndex = 0;
	LIST_NODE *LstNode = NULL;

	if ((AdjLstGraph == NULL) || (LstQueue == NULL) || (Visited == NULL) || (ResultArr == NULL)) {
		return;
	}

	Visited[i] = true;
	ResultArr[AdjLStBFSResIndex] = i;
	AdjLStBFSResIndex++;
	printf("AdjLstGraph->AdjustGraph[%d].Data = %d\n", i, AdjLstGraph->AdjustGraph[i].Data);

	EnterLinkQueue(LstQueue, i);
	while (IsLinkQueueEmpty(LstQueue) == false) {
		ExitLinkQueue(LstQueue, &QIndex);
		LstNode = AdjLstGraph->AdjustGraph[QIndex].FirstEadge;

		while (LstNode != NULL) {
			if (Visited[LstNode->VectorIndex] == false) {
				Visited[LstNode->VectorIndex] = true;
				ResultArr[AdjLStBFSResIndex] = LstNode->VectorIndex;
				AdjLStBFSResIndex++;
				printf("AdjLstGraph->AdjustGraph[%d].Data = %d\n", LstNode->VectorIndex, AdjLstGraph->AdjustGraph[LstNode->VectorIndex].Data);

				EnterLinkQueue(LstQueue, LstNode->VectorIndex);
			}
			LstNode = LstNode->Next;
		}
	}
}

void AdjLstGraphBFS(ADJUST_LIST_GRAPH *AdjLstGraph, bool *Visited, int *ResultArr) {
	int i = 0;
	LINK_QUEUE *LstQueue = NULL;

	if ((AdjLstGraph == NULL) || (Visited == NULL) || (ResultArr == NULL)) {
		return;
	}

	AdjLStBFSResIndex = 0;
	for (i = 0; i < AdjLstGraph->VectorNum; i++) {
		Visited[i] = false;
	}

	InitLinkQueue(&LstQueue);
	for (i = 0; i < AdjLstGraph->VectorNum; i++) {
		if (Visited[i] == false) {
			AdjLstGrBFS(AdjLstGraph, LstQueue, Visited, i, ResultArr);
		}
	}
}
```



### （3）测试用例

```c
/*TestAdjLstGraphBFS*/
void TestAdjLstGraphBFS(void) {
	/*Test01*/
	ADJUST_LIST_GRAPH  AdjListGraph01;
	ADJUST_LIST_GRAPH  AdjListGraphData01 = { 4, 5, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}} };
	LIST_NODE_DATA     AdjListNodeData01[] = { {3, {1, 2, 3}}, {2, {0, 2}}, {3, {0, 1, 3}}, {2, {0, 2}} };
	bool Visited01[4] = { 0 };
	int VectorNum01 = 4;
	int DFSResult01[4] = { 0 };
	int CmpVector01[] = { 0, 1, 2, 3 };

	/*Test02*/
	ADJUST_LIST_GRAPH  AdjListGraph02;               //A          B           C           D           E           F           G           H           I
	ADJUST_LIST_GRAPH  AdjListGraphData02 = { 9, 15, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}, {40, NULL}, {50, NULL}, {60, NULL}, {70, NULL}, {80, NULL},
													}
	};
	//A            B                  C               D                     E               F               G                  H               I
	LIST_NODE_DATA     AdjListNodeData02[] = { {2, {1, 5}}, {4, {0, 2, 6, 8}}, {3, {1, 3, 8}}, {5, {2, 4, 6, 7, 8}}, {3, {3, 5, 7}}, {3, {0, 4, 6}}, {4, {1, 3, 5, 7}}, {3, {3, 4, 6}}, {3, {1, 2, 3}}
	};
	ADJUST_LIST_GRAPH  CmpAdjListGraph02 = { 9, 15, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}, {40, NULL}, {50, NULL}, {60, NULL}, {70, NULL}, {80, NULL},
													}
	};
	bool Visited02[9] = { 0 };
	int VectorNum02 = 9;
	int DFSResult02[9] = { 0 };
	int CmpVector02[] = { 0, 1, 5, 2, 6, 8, 4, 3, 7 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildAdjustListGraph(&AdjListGraph01, &AdjListGraphData01, AdjListNodeData01);
	PrintAdjLstGraph(&AdjListGraph01);
	AdjLstGraphBFS(&AdjListGraph01, Visited01, DFSResult01);
	TestCmpArr(CmpVector01, VectorNum01, DFSResult01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildAdjustListGraph(&AdjListGraph02, &AdjListGraphData02, AdjListNodeData02);
	PrintAdjLstGraph(&AdjListGraph02);
	printf("\nBFS\n");
	AdjLstGraphBFS(&AdjListGraph02, Visited02, DFSResult02);
	TestCmpArr(CmpVector02, VectorNum02, DFSResult02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



### （4）结果

>-------Test start----------
>
> 
>
>-------Test 01----------
>
>AdjLstGraph->VectorNum = 4
>
>AdjLstGraph->EadgeNum = 5
>
>AdjLstGraph->AdjustGraph[0].Data = 0
>
>LstNode->VectorIndex = 1
>
>LstNode->VectorIndex = 2
>
>LstNode->VectorIndex = 3
>
>AdjLstGraph->AdjustGraph[1].Data = 10
>
>LstNode->VectorIndex = 0
>
>LstNode->VectorIndex = 2
>
>AdjLstGraph->AdjustGraph[2].Data = 20
>
>LstNode->VectorIndex = 0
>
>LstNode->VectorIndex = 1
>
>LstNode->VectorIndex = 3
>
>AdjLstGraph->AdjustGraph[3].Data = 30
>
>LstNode->VectorIndex = 0
>
>LstNode->VectorIndex = 2
>
>AdjLstGraph->AdjustGraph[0].Data = 0
>
>AdjLstGraph->AdjustGraph[1].Data = 10
>
>AdjLstGraph->AdjustGraph[2].Data = 20
>
>AdjLstGraph->AdjustGraph[3].Data = 30
>
>Correct!
>
> 
>
>-------Test 02----------
>
>AdjLstGraph->VectorNum = 9
>
>AdjLstGraph->EadgeNum = 15
>
>AdjLstGraph->AdjustGraph[0].Data = 0
>
>LstNode->VectorIndex = 1
>
>LstNode->VectorIndex = 5
>
>AdjLstGraph->AdjustGraph[1].Data = 10
>
>LstNode->VectorIndex = 0
>
>LstNode->VectorIndex = 2
>
>LstNode->VectorIndex = 6
>
>LstNode->VectorIndex = 8
>
>AdjLstGraph->AdjustGraph[2].Data = 20
>
>LstNode->VectorIndex = 1
>
>LstNode->VectorIndex = 3
>
>LstNode->VectorIndex = 8
>
>AdjLstGraph->AdjustGraph[3].Data = 30
>
>LstNode->VectorIndex = 2
>
>LstNode->VectorIndex = 4
>
>LstNode->VectorIndex = 6
>
>LstNode->VectorIndex = 7
>
>LstNode->VectorIndex = 8
>
>AdjLstGraph->AdjustGraph[4].Data = 40
>
>LstNode->VectorIndex = 3
>
>LstNode->VectorIndex = 5
>
>LstNode->VectorIndex = 7
>
>AdjLstGraph->AdjustGraph[5].Data = 50
>
>LstNode->VectorIndex = 0
>
>LstNode->VectorIndex = 4
>
>LstNode->VectorIndex = 6
>
>AdjLstGraph->AdjustGraph[6].Data = 60
>
>LstNode->VectorIndex = 1
>
>LstNode->VectorIndex = 3
>
>LstNode->VectorIndex = 5
>
>LstNode->VectorIndex = 7
>
>AdjLstGraph->AdjustGraph[7].Data = 70
>
>LstNode->VectorIndex = 3
>
>LstNode->VectorIndex = 4
>
>LstNode->VectorIndex = 6
>
>AdjLstGraph->AdjustGraph[8].Data = 80
>
>LstNode->VectorIndex = 1
>
>LstNode->VectorIndex = 2
>
>LstNode->VectorIndex = 3
>
> 
>
>BFS
>
>AdjLstGraph->AdjustGraph[0].Data = 0
>
>AdjLstGraph->AdjustGraph[1].Data = 10
>
>AdjLstGraph->AdjustGraph[5].Data = 50
>
>AdjLstGraph->AdjustGraph[2].Data = 20
>
>AdjLstGraph->AdjustGraph[6].Data = 60
>
>AdjLstGraph->AdjustGraph[8].Data = 80
>
>AdjLstGraph->AdjustGraph[4].Data = 40
>
>AdjLstGraph->AdjustGraph[3].Data = 30
>
>AdjLstGraph->AdjustGraph[7].Data = 70
>
>Correct!
>
> 
>
>-------Test result----------
>
>Print test result;
>
>TestNum = 2, PassNum = 2, FaildNum = 0
