# 图的创建（邻接矩阵，邻接表）——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​		图是由顶点的有穷非空集合和顶点之间边的集合组成的，表示为G(V, E).先把key值存到表里面去，存的过程哈希表Hashkey与表里面的值（Key）一一对应，存表冲突时使用开放地址法解决。时间复杂度为O(1)，空间复杂度为O(n).



# 2 邻接矩阵法

​	用一维数组表示图的顶点，用二维数组表示边的关系

## 2.1 数据结构

```c
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
```



# 2.2 构建图代码

```c
/*BuildMGraph*/
void PrintMGraph(M_GRAPH *MGraph) {
	int i, j;

	printf("MGraph->VectorNum = %d\n", MGraph->VectorNum);
	printf("MGraph->EadgeNum = %d\n", MGraph->EadgeNum);

	for (i = 0; i < MGraph->VectorNum; i++) {
		printf("MGraph->Vector[%d] = %d\n", i, MGraph->Vector[i]);
	}

	for (i = 0; i < MGraph->VectorNum; i++) {
		for (j = 0; j < MGraph->VectorNum; j++) {
			printf("MGraph->Vector[%d][%d] = %d, ", i, j, MGraph->Eadge[i][j]);
		}
		printf("\n");
	}
}

void BuildMGraph(M_GRAPH *MGraph, int *Vector, int *Eadge, int VectorNum, int EadgeNum) {
	int i = 0, j = 0;
	int *EadgeArr = Eadge;

	if ((MGraph == NULL) || (Vector == NULL) || (Eadge == NULL)) {
		return;
	}

	MGraph->VectorNum = VectorNum;
	MGraph->EadgeNum = EadgeNum;

	for (i = 0; i < VectorNum; i++) {
		MGraph->Vector[i] = Vector[i];
	}

	//printf("Eadge = 0x%lx, EadgeArr = 0x%lx\n", Eadge, EadgeArr);
	for (i = 0; i < VectorNum; i++) {
		Eadge = (EadgeArr + i * VectorNum);
		//Eadge = (int *)((unsigned long long)EadgeArr + i * VectorNum * sizeof(int));
		for (j = 0; j < VectorNum; j++) {
			//printf("Eadge[%d][%d] = %d, Eadge[%d] = 0x%lx\n", i, j, Eadge[j], j, &Eadge[j]);
			MGraph->Eadge[i][j] = Eadge[j];
		}
	}
}
```



##  （2）测试用例

```c
/*TestBuildMGraph*/
void TestMGraph(M_GRAPH *MGraph01, M_GRAPH *MGraph02) {
	int i, j;

	TestNum++;

	if ((MGraph01->VectorNum != MGraph02->VectorNum) || (MGraph01->EadgeNum != MGraph02->EadgeNum)) {
		FaildNum++;
		return;
	}

	for (i = 0; i < MGraph01->VectorNum; i++) {
		if (MGraph01->Vector[i] != MGraph02->Vector[i]) {
			FaildNum++;
			return;
		}
	}

	for (i = 0; i < MGraph01->VectorNum; i++) {
		for (j = 0; j < MGraph01->VectorNum; j++) {
			if (MGraph01->Eadge[i][j] != MGraph02->Eadge[i][j]) {
				FaildNum++;
				return;
			}
		}
	}

	PassNum++;
}

void TestBuildMGraph(void) {
	/*Test01*/
	M_GRAPH  MGraph01;
	int Vector01[]   = { 0, 1, 2, 3 };
	int Eadge01[][4] = {{0, 1, 1, 1},
						{1, 0, 1, 0},
						{1, 1, 0, 1},
						{1, 0, 1, 0}
	                   };
	int VectorNum01 = 4;
	int EadgeNum01  = 5;

	M_GRAPH CmpGraph01 = { 4, 5, {0, 1, 2, 3},
			                    {{0, 1, 1, 1},
			                     {1, 0, 1, 0},
			                     {1, 1, 0, 1},
			                     {1, 0, 1, 0}
	                            } 
	                     };

	/*Test02*/
	M_GRAPH  MGraph02;
	int Vector02[]    = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
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

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildMGraph(&MGraph01, Vector01, (int *)Eadge01, VectorNum01, EadgeNum01);
	PrintMGraph(&MGraph01);
	TestMGraph(&CmpGraph01, &MGraph01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildMGraph(&MGraph02, Vector02, Eadge02, VectorNum02, EadgeNum02);
	PrintMGraph(&MGraph02);
	TestMGraph(&CmpGraph02, &MGraph02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



## （3）**打印结果**

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
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0



# 3 邻接表

​	顶点用一维数组存，边的信息用链表存，数据结构如下图所示：

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



## 3.1 代码

```c
/*BuildAdjustListGraph*/
void PrintLstNode(const LIST_NODE *LstNode) {
	if (LstNode == NULL) {
		return;
	}

	while (LstNode != NULL) {
		//printf("LstNode = 0x%lx, LstNode->VectorIndex = %d, LstNode->Next = 0x%lx\n", LstNode, LstNode->VectorIndex, LstNode->Next);
		printf("LstNode->VectorIndex = %d\n", LstNode->VectorIndex);
		LstNode = LstNode->Next;
	}
}

void PrintAdjLstGraph(const ADJUST_LIST_GRAPH *AdjLstGraph) {
	int i = 0;

	if (AdjLstGraph == NULL) {
		return;
	}

	printf("AdjLstGraph->VectorNum = %d\n", AdjLstGraph->VectorNum);
	printf("AdjLstGraph->EadgeNum = %d\n", AdjLstGraph->EadgeNum);

	for (i = 0; i < AdjLstGraph->VectorNum; i++) {
		printf("AdjLstGraph->AdjustGraph[%d].Data = %d\n", i, AdjLstGraph->AdjustGraph[i].Data);
		//printf("AdjLstGraph->AdjustGraph[%d].FirstEadge = 0x%lx\n", i, AdjLstGraph->AdjustGraph[i].FirstEadge);
		PrintLstNode(AdjLstGraph->AdjustGraph[i].FirstEadge);
	}
}

void AddAdjLstNode(LIST_NODE **FirstEadge, LIST_NODE_DATA *LstNodeData) {
	int i = 0;
	LIST_NODE *AddNode = NULL;
	LIST_NODE *PreNode = NULL;

	if ((FirstEadge == NULL) || (LstNodeData == NULL)) {
		return;
	}

	for (i = 0; i < LstNodeData->Num; i++) {
		AddNode = (LIST_NODE *)malloc(sizeof(LIST_NODE));
		if (AddNode == NULL) {
			return;
		}
		AddNode->VectorIndex = LstNodeData->Vector[i];
		AddNode->Next = NULL;

		if (*FirstEadge == NULL) {
			*FirstEadge = AddNode;
			PreNode = AddNode;
		}
		else {
			AddNode->Next = PreNode->Next;
			PreNode->Next = AddNode;
			PreNode = PreNode->Next;
		}
	}
}

void BuildAdjustListGraph(ADJUST_LIST_GRAPH *AdjListGraph, ADJUST_LIST_GRAPH *AdjListGraphData, LIST_NODE_DATA *LstNodeData) {
	int i = 0;

	if ((AdjListGraph == NULL) || (AdjListGraphData == NULL) || (LstNodeData == NULL)) {
		return;
	}

	AdjListGraph->VectorNum = AdjListGraphData->VectorNum;
	AdjListGraph->EadgeNum = AdjListGraphData->EadgeNum;

	for (i = 0; i < AdjListGraphData->VectorNum; i++) {
		AdjListGraph->AdjustGraph[i].Data = AdjListGraphData->AdjustGraph[i].Data;
		AdjListGraph->AdjustGraph[i].FirstEadge = NULL;
		AddAdjLstNode(&(AdjListGraph->AdjustGraph[i].FirstEadge), &LstNodeData[i]);
	}
}
```



## 3.2 测试用例

```c
/*TestBuildAdjustListGraph*/
bool TestAdjLst(const LIST_NODE *CmpAdjLst, const LIST_NODE *AdjLst) {
	LIST_NODE *PCmpNode = CmpAdjLst;
	LIST_NODE *PNode = AdjLst;

	if ((CmpAdjLst == NULL) || (AdjLst == NULL)) {
		return false;
	}

	while ((PCmpNode != NULL) && (PNode != NULL)) {
		if (CmpAdjLst->VectorIndex != AdjLst->VectorIndex) {
			return false;
		}
		else {
			PCmpNode = PCmpNode->Next;
			PNode = PNode->Next;
		}
	}

	if (PCmpNode != PNode) {
		return false;
	}

	return true;
}

void TestAdjLstGraph(const ADJUST_LIST_GRAPH *CmpAdjLstGraph, const ADJUST_LIST_GRAPH *AdjLstGraph) {
	int i = 0;

	TestNum++;

	if ((CmpAdjLstGraph == NULL) || (AdjLstGraph == NULL)) {
		FaildNum++;
		return;
	}

	if ((CmpAdjLstGraph->VectorNum != AdjLstGraph->VectorNum) || (CmpAdjLstGraph->EadgeNum != AdjLstGraph->EadgeNum)) {
		FaildNum++;
		return;
	}

	for (i = 0; i < CmpAdjLstGraph->VectorNum; i++) {
		if (CmpAdjLstGraph->AdjustGraph[i].Data != AdjLstGraph->AdjustGraph[i].Data) {
			FaildNum++;
			return;
		}
	}

	for (i = 0; i < CmpAdjLstGraph->VectorNum; i++) {
		if (TestAdjLst(CmpAdjLstGraph->AdjustGraph[i].FirstEadge, AdjLstGraph->AdjustGraph[i].FirstEadge) == false) {
			FaildNum++;
			return;
		}
	}

	PassNum++;
}

void BuildCmpAdjListGraph(ADJUST_LIST_GRAPH *AdjLstGraph, LIST_NODE_DATA *LstNodeData) {
	int i = 0;

	if ((AdjLstGraph == NULL) || (LstNodeData == NULL)) {
		return;
	}

	for (i = 0; i < AdjLstGraph->VectorNum; i++) {
		AddAdjLstNode(&(AdjLstGraph->AdjustGraph[i].FirstEadge), &LstNodeData[i]);
	}
}

void TestBuildAdjustListGraph(void) {
	/*Test01*/
	ADJUST_LIST_GRAPH  AdjLstGraph01;
	ADJUST_LIST_GRAPH  AdjLstGraphData01 = { 4, 5, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}} };
	LIST_NODE_DATA     AdjLstNodeData01[] = { {3, {1, 2, 3}}, {2, {0, 2}}, {3, {0, 1, 3}}, {2, {0, 2}} };
	ADJUST_LIST_GRAPH  CmpAdjLstGraph01 = { 4, 5, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}} };

	/*Test02*/
	ADJUST_LIST_GRAPH  AdjLstGraph02;               //A          B           C           D           E           F           G           H           I
	ADJUST_LIST_GRAPH  AdjLstGraphData02 = { 9, 15, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}, {40, NULL}, {50, NULL}, {60, NULL}, {70, NULL}, {80, NULL},
													}
	};
	//A            B                  C               D                     E               F               G                  H               I
	LIST_NODE_DATA     AdjLstNodeData02[] = { {2, {1, 5}}, {4, {0, 2, 6, 8}}, {3, {1, 3, 8}}, {5, {2, 4, 6, 7, 8}}, {3, {3, 5, 7}}, {3, {0, 4, 6}}, {4, {1, 3, 5, 7}}, {3, {3, 4, 6}}, {3, {1, 2, 3}}
	};
	ADJUST_LIST_GRAPH  CmpAdjLstGraph02 = { 9, 15, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}, {40, NULL}, {50, NULL}, {60, NULL}, {70, NULL}, {80, NULL},
													}
	};

	printf("-------Test start----------\n");
	InitNum();
	printf("-------Test01----------\n");
	BuildAdjustListGraph(&AdjLstGraph01, &AdjLstGraphData01, AdjLstNodeData01);
	PrintAdjLstGraph(&AdjLstGraph01);
	BuildCmpAdjListGraph(&CmpAdjLstGraph01, AdjLstNodeData01);
	TestAdjLstGraph(&CmpAdjLstGraph01, &AdjLstGraph01);

	printf("-------Test02----------\n");
	BuildAdjustListGraph(&AdjLstGraph02, &AdjLstGraphData02, AdjLstNodeData02);
	PrintAdjLstGraph(&AdjLstGraph02);
	BuildCmpAdjListGraph(&CmpAdjLstGraph02, AdjLstNodeData02);
	TestAdjLstGraph(&CmpAdjLstGraph02, &AdjLstGraph02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



**结果：**

> -------Test start----------
>
> -------Test01----------
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
> -------Test02----------
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
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0
