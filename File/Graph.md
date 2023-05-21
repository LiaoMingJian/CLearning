# 图的创建——C语言描述

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
```



# 2.2 构建图代码

```c
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

/*BuildMGraph*/
void BuildMGraph(M_GRAPH *MGraph, int *Vector, int (*Eadge)[4], int VectorNum, int EadgeNum) {
	int i = 0, j = 0;
	
	if ((MGraph == NULL) || (Vector == NULL) || (Eadge == NULL)) {
		return;
	}

	MGraph->VectorNum = VectorNum;
	MGraph->EadgeNum = EadgeNum;

	for (i = 0; i < VectorNum; i++) {
		MGraph->Vector[i] = Vector[i];
	}

	for (i = 0; i < VectorNum; i++ ) {
		for (j = 0; j < VectorNum; j++) {
			printf("Eadge[%d][%d] = %d\n", i, j, Eadge[i][j]);
			MGraph->Eadge[i][j] = Eadge[i][j];
		}
	}
}
```



##  （2）测试用例

```c
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
	int Vector01[]   = {0, 1, 2, 3};
	int Eadge01[][4] = { {0, 1, 1, 1},
                         {1, 0, 1, 0},
	                     {1, 1, 0, 1},
	                     {1, 0, 1, 0} };
	int VectorNum01  = 4;
	int EadgeNum01   = 5;
	
	M_GRAPH CmpGraph01 = { 4, 5, {0, 1, 2, 3}, 
					     { {0, 1, 1, 1},
					       {1, 0, 1, 0},
					       {1, 1, 0, 1},
					       {1, 0, 1, 0} }};
	
	printf("-------Test start----------\n");
	InitNum();
	BuildMGraph(&MGraph01, Vector01, Eadge01, VectorNum01, EadgeNum01);
	PrintMGraph(&MGraph01);
	TestMGraph(&CmpGraph01, &MGraph01);

	/*Test01*/
	printf("\n-------Test 01----------\n");


	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



## （3）**打印结果**

> Eadge[0][0] = 0
>
> Eadge[0][1] = 1
>
> Eadge[0][2] = 1
>
> Eadge[0][3] = 1
>
> Eadge[1][0] = 1
>
> Eadge[1][1] = 0
>
> Eadge[1][2] = 1
>
> Eadge[1][3] = 0
>
> Eadge[2][0] = 1
>
> Eadge[2][1] = 1
>
> Eadge[2][2] = 0
>
> Eadge[2][3] = 1
>
> Eadge[3][0] = 1
>
> Eadge[3][1] = 0
>
> Eadge[3][2] = 1
>
> Eadge[3][3] = 0
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
> -------Test 01----------
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 1, PassNum = 1, FaildNum = 0
