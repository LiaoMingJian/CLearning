# 二叉树（存储结构，三种遍历方式，构建树）——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​     二叉树是n(n >= 0)个结点的有限集合，该集合或者空集（称为空二叉树），或者由一个根结点和两棵互不相交的，分别称为根结点的左子树和右子树的二叉树组成

# 2  特殊二叉树

​     斜树，满二叉树，完全二叉树

# 3 二叉树的性质

（1）在二叉树的第 i 层至多有2^(i-1)个结点

（2）深度为k的二叉至多有2^k – 1个结点

（3）对于任何一棵二叉树T，如果其终端结点数位n0，度为2的结点数为n2，则 n0 = n2 + 1

（4）具有n个结点的完全二叉树的深度为(log2n) + 1

（5）如果对一颗有n个结点的完全二叉树（深度为(log2n) + 1）的结点按层序编号（从第1层到第（log2n）+1层，每层从左到右），对任一结点j（1 <= i <= n）有：

①如果i = 1，则结点i是二叉树的根，无双亲；如果i>1，则其双亲是结点i/2;

②如果2i > n，则结点i无左孩子（结点i为叶子结点）；否则其左孩子是结点2i;

①   如果2i + 1 > n，则结点i无右孩子；否则其右孩子是结点2i+1

#  4 二叉树存储结构

​	采用链式存储结构

```c
typedef struct _BINARY_TREE_NODE {
​     int Data;
​     struct _BINARY_TREE_NODE *LeftChild;
​     struct _BINARY_TREE_NODE *RightChild;
}BINARY_TREE_NODE;
```

# 5  二叉树的遍历方式

​	**采用递归方式**

## 5.1 前序遍历

​	根-左-右

**代码：**

```c
void PreOrderTraversePrintBinaryTree(const BINARY_TREE_NODE *BiTreeNode) {	
	if (BiTreeNode == NULL) {
		return;
	} else {
		printf("BiTreeNode->Data = %d\n", BiTreeNode->Data);
		PreOrderTraversePrintBinaryTree(BiTreeNode->LeftChild);
		PreOrderTraversePrintBinaryTree(BiTreeNode->RightChild);
	}
}
```

## 5.2 前序遍历

​     左-根-右

**代码：**

```c
void InOrderTraversePrintBinaryTree(const BINARY_TREE_NODE *BiTreeNode) {
	if (BiTreeNode == NULL) {
		return;
	} else {
		InOrderTraversePrintBinaryTree(BiTreeNode->LeftChild);
		printf("BiTreeNode->Data = %d\n", BiTreeNode->Data);
		InOrderTraversePrintBinaryTree(BiTreeNode->RightChild);
	}
}
```

## 5.3 后序遍历

​     左-右-根

**代码：**

```c
void PostOrderTraversePrintBinaryTree(const BINARY_TREE_NODE *BiTreeNode) {
	if (BiTreeNode == NULL) {
		return;
	} else {
		PostOrderTraversePrintBinaryTree(BiTreeNode->LeftChild);
		PostOrderTraversePrintBinaryTree(BiTreeNode->RightChild);
		printf("BiTreeNode->Data = %d\n", BiTreeNode->Data);
	}
}
```

# 6 二叉树的构建

​	使用前序遍历的方式创建。

**（1）结点法**

**每个结点都输入进去，包括叶子结点的两个孩子结点**

```c
void PreOderBuildBinaryTree01(BINARY_TREE_NODE **BiTreeNodePtr, int *DataPtr, int Index)
```

​	BiTreeNodePtr表示树结点的地址，DataPtr表示结点的数据（以前序遍历的顺序排列，叶子结点的两个孩子结点，其值为0，表示结点地址为空），Index表示结点数据的下标。

**代码：**

```c
void PreOderBuildBinaryTree01(BINARY_TREE_NODE **BiTreeNodePtr, int *DataPtr, int Index) {
	static int TraIndex = 0;

	printf("PreOderBuildBinaryTree01 start\n");

	if (DataPtr[TraIndex] == 0) {
		*BiTreeNodePtr = NULL;
		TraIndex++;
		return ;
	} else {
		*BiTreeNodePtr = (BINARY_TREE_NODE *)malloc(sizeof(BINARY_TREE_NODE));
		printf("In else, DataPtr[TraIndex] = %d\n", DataPtr[TraIndex]);
		(*BiTreeNodePtr)->Data = DataPtr[TraIndex];
		TraIndex++;

		PreOderBuildBinaryTree01(&((*BiTreeNodePtr)->LeftChild), DataPtr, TraIndex);
		PreOderBuildBinaryTree01(&((*BiTreeNodePtr)->RightChild), DataPtr, TraIndex);
	}

	printf("PreOderBuildBinaryTree01 end\n\n");
}
```

**（2）结点孩子法**

```c
void PostOrderTraversePrintBinaryTree(const BINARY_TREE_NODE *BiTreeNode);
```

​	BiTreeNodePtr表示树结点的地址，DataPtr表示结点的数据（以前序遍历的顺序排列，BINARY_TREE_NODE_DATA数据结构如下），IfExistNodeFlag表示该结点是否存在，1为存在，0表示不存在。

```c
typedef struct _BINARY_TREE_NODE {
	char Data;
	struct _BINARY_TREE_NODE *LeftChild;
	struct _BINARY_TREE_NODE *RightChild;
}BINARY_TREE_NODE;
```

**代码：**

```c
static int TraIndex = 0;
void PreOderBuildBinaryTree02(BINARY_TREE_NODE **BiTreeNodePtr, BINARY_TREE_NODE_DATA *DataPtr, char IfExistNodeFlag) {
	char IfExistLeftChildNodeFlag = 0;
	char IfExistRightChildNodeFlag = 0;

	//printf("PreOderBuildBinaryTree02 start\n"); 
	//TraIndex = 0;

	if (IfExistNodeFlag == 0) {
		*BiTreeNodePtr = NULL;
		//TraIndex++;
		return;
	}
	else {
		*BiTreeNodePtr = (BINARY_TREE_NODE *)malloc(sizeof(BINARY_TREE_NODE));
		//printf("In else, DataPtr[%d] = %d\n", TraIndex, DataPtr[TraIndex].BiTreeNodeData);
		(*BiTreeNodePtr)->Data = DataPtr[TraIndex].BiTreeNodeData;
		IfExistLeftChildNodeFlag = DataPtr[TraIndex].IsExistLeftChildFlag;
		IfExistRightChildNodeFlag = DataPtr[TraIndex].IsExistRightChildFlag;
		//printf("IfExistLeftChildNodeFlag = %d, IfExistRightChildNodeFlag = %d\n", IfExistLeftChildNodeFlag, IfExistRightChildNodeFlag);

		TraIndex++;

		PreOderBuildBinaryTree02(&((*BiTreeNodePtr)->LeftChild), DataPtr, IfExistLeftChildNodeFlag);

		//printf("In Right, TraIndex = %d\n", TraIndex);
		PreOderBuildBinaryTree02(&((*BiTreeNodePtr)->RightChild), DataPtr, IfExistRightChildNodeFlag);
	}

	//printf("PreOderBuildBinaryTree02 end\n\n");
}

/*BINARY_TREE*/
void BuildBinaryTree(BINARY_TREE_NODE **BiTreeNodePtr, BINARY_TREE_NODE_DATA *DataPtr, char IfExistNodeFlag) {
	TraIndex = 0;
	PreOderBuildBinaryTree02(BiTreeNodePtr, DataPtr, IfExistNodeFlag);
}
```

**测试用例：**

```c
typedef struct _BINARY_TREE_NODE_DATA {
	char BiTreeNodeData;
	char IsExistLeftChildFlag;
	char IsExistRightChildFlag;
}BINARY_TREE_NODE_DATA;

```

```c
/*BINARY_TREE*/
static int PreOrderTraverseCompareNum = 0;
static int BiIndex = 0;
void PreOrderTraverseCompare(const int *CmpNode, const BINARY_TREE_NODE *BiTreeNode) {
	if (BiTreeNode == NULL) {
		return;
	}
	else {
		printf("BiTreeNode->Data = %c , CmpNode[%d] = %c\n", BiTreeNode->Data, BiIndex, CmpNode[BiIndex]);
		if (BiTreeNode->Data == CmpNode[BiIndex]) {
			//printf("BiTreeNode->Data = %c , CmpNode[%d] = %c\n", BiTreeNode->Data, Index, CmpNode[Index]);
			PreOrderTraverseCompareNum++;
		}

		BiIndex++;
		PreOrderTraverseCompare(CmpNode, BiTreeNode->LeftChild);
		PreOrderTraverseCompare(CmpNode, BiTreeNode->RightChild);
	}
}

void CmpPreOderBuildBinaryTree(const int *CmpNode, const BINARY_TREE_NODE *BiTreeNode, int NodeNum) {
	//unsigned char Index = 0;
	BiIndex = 0;
	PreOrderTraverseCompareNum = 0;

	TestNum++;

	PreOrderTraverseCompare(CmpNode, BiTreeNode);
	printf("PreOrderTraverseCompareNum = %d, NodeNum = %d\n", PreOrderTraverseCompareNum, NodeNum);
	if (PreOrderTraverseCompareNum != NodeNum) {
		FaildNum++;
	}
	else {
		PassNum++;
	}
}

```

```c
/*BINARY_TREE*/
void TestPreOderBuildBinaryTree(void) {
	/*Test01*/
	//    10
	//  20    30
	BINARY_TREE_NODE *BiTreeNodePtr01 = NULL;
	BINARY_TREE_NODE_DATA Data01[] = { {10 , 1, 1}, {20, 0, 0}, {30, 0, 0} };
	int NodeNum01 = 3;
	char IfExistNodeFlag01 = 1;
	int CmpBiTreeNodeData01[] = { 10, 20, 30 };

	/*Test02*/
	//    10
	//  20    30
	//   40  
	BINARY_TREE_NODE *BiTreeNodePtr02 = NULL;
	BINARY_TREE_NODE_DATA Data02[] = { {10, 1, 1}, {20, 0, 1}, {40, 0, 0}, {30, 0, 0} };
	int NodeNum02 = 4;
	char IfExistNodeFlag02 = 1;
	int CmpBiTreeNodeData02[] = { 10, 20, 40, 30 };

	/*Test03*/
	//        10
	//   20        50
	// 30  40   60    70
	BINARY_TREE_NODE *BiTreeNodePtr03 = NULL;
	BINARY_TREE_NODE_DATA Data03[] = { {10, 1, 1}, {20, 1, 1}, {30, 0, 0}, {40, 0, 0}, {50, 1, 1}, {60, 0, 0}, {70, 0, 0} };
	int NodeNum03 = 7;
	char IfExistNodeFlag03 = 1;
	int CmpBiTreeNodeData03[] = { 10, 20, 30, 40, 50, 60, 70 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildBinaryTree(&BiTreeNodePtr01, Data01, IfExistNodeFlag01);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("\nCmpPreOderBuildBinaryTree\n");
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData01, BiTreeNodePtr01, NodeNum01);


	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildBinaryTree(&BiTreeNodePtr02, Data02, IfExistNodeFlag02);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("\nCmpPreOderBuildBinaryTree\n");
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData02, BiTreeNodePtr02, NodeNum02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	BuildBinaryTree(&BiTreeNodePtr03, Data03, IfExistNodeFlag03);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr03);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr03);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr03);
	printf("\nCmpPreOderBuildBinaryTree\n");
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData03, BiTreeNodePtr03, NodeNum03);

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
> PreOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 30
>
> InOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 30
>
> PostOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 10
>
>  
>
> CmpPreOderBuildBinaryTree
>
> BiTreeNode->Data = 10 , CmpNode[0] = 10
>
> BiTreeNode->Data = 20 , CmpNode[1] = 20
>
> BiTreeNode->Data = 30 , CmpNode[2] = 30
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 02----------
>
> PreOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 40
>
> BiTreeNode->Data = 30
>
> InOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 40
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 30
>
> PostOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 40
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 10
>
>  
>
> CmpPreOderBuildBinaryTree
>
> BiTreeNode->Data = 10 , CmpNode[0] = 10
>
> BiTreeNode->Data = 20 , CmpNode[1] = 20
>
> BiTreeNode->Data = 40 , CmpNode[2] = 40
>
> BiTreeNode->Data = 30 , CmpNode[3] = 30
>
> PreOrderTraverseCompareNum = 4, NodeNum = 4
>
>  
>
> -------Test 03----------
>
> PreOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 40
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 60
>
> BiTreeNode->Data = 70
>
> InOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 40
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 60
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 70
>
> PostOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 40
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 60
>
> BiTreeNode->Data = 70
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 10
>
>  
>
> CmpPreOderBuildBinaryTree
>
> BiTreeNode->Data = 10 , CmpNode[0] = 10
>
> BiTreeNode->Data = 20 , CmpNode[1] = 20
>
> BiTreeNode->Data = 30 , CmpNode[2] = 30
>
> BiTreeNode->Data = 40 , CmpNode[3] = 40
>
> BiTreeNode->Data = 50 , CmpNode[4] = 50
>
> BiTreeNode->Data = 60 , CmpNode[5] = 60
>
> BiTreeNode->Data = 70 , CmpNode[6] = 70
>
> PreOrderTraverseCompareNum = 7, NodeNum = 7
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 3, PassNum = 3, FaildNum = 0







