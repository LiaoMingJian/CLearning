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
		PreOrderTraversePrintBinaryTree(BiTreeNode->LeftChild);
		printf("BiTreeNode->Data = %d\n", BiTreeNode->Data);
		PreOrderTraversePrintBinaryTree(BiTreeNode->RightChild);
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
		PreOrderTraversePrintBinaryTree(BiTreeNode->LeftChild);
		PreOrderTraversePrintBinaryTree(BiTreeNode->RightChild);
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
void PreOderBuildBinaryTree02(BINARY_TREE_NODE **BiTreeNodePtr, BINARY_TREE_NODE_DATA *DataPtr, int Index, int IfExistNodeFlag)
```

​	BiTreeNodePtr表示树结点的地址，DataPtr表示结点的数据（以前序遍历的顺序排列，BINARY_TREE_NODE_DATA数据结构如下），IfExistNodeFlag表示该结点是否存在，1为存在，0表示不存在。

```c
typedef struct _BINARY_TREE_NODE_DATA {
	int BiTreeNodeData;
	int IsExistLeftChildFlag;
	int IsExistRightChildFlag;
}BINARY_TREE_NODE_DATA;
```

**代码：**

```c
void PreOderBuildBinaryTree02(BINARY_TREE_NODE **BiTreeNodePtr, BINARY_TREE_NODE_DATA *DataPtr, int Index, int IfExistNodeFlag) {
	static int TraIndex = 0;
	int IfExistLeftChildNodeFlag;
	int IfExistRightChildNodeFlag;
	
	printf("PreOderBuildBinaryTree02 start\n");

	if (IfExistNodeFlag == 0) {
		*BiTreeNodePtr = NULL;
		//TraIndex++;
		return;
	} else {
		*BiTreeNodePtr = (BINARY_TREE_NODE *)malloc(sizeof(BINARY_TREE_NODE));
		printf("In else, DataPtr[%d] = %d\n", TraIndex, DataPtr[TraIndex]);
		(*BiTreeNodePtr)->Data = DataPtr[TraIndex].BiTreeNodeData;
		IfExistLeftChildNodeFlag = DataPtr[TraIndex].IsExistLeftChildFlag;
		IfExistRightChildNodeFlag = DataPtr[TraIndex].IsExistRightChildFlag;
		printf("IfExistLeftChildNodeFlag = %d, IfExistRightChildNodeFlag = %d\n", IfExistLeftChildNodeFlag, IfExistRightChildNodeFlag);

		TraIndex++;

		PreOderBuildBinaryTree02(&((*BiTreeNodePtr)->LeftChild), DataPtr, TraIndex, IfExistLeftChildNodeFlag);

		printf("In Right, TraIndex = %d\n", TraIndex);
		PreOderBuildBinaryTree02(&((*BiTreeNodePtr)->RightChild), DataPtr, TraIndex, IfExistRightChildNodeFlag);
	}

	printf("PreOderBuildBinaryTree02 end\n\n");
}
```

**测试用例：**

```c
static int PreOrderTraverseCompareNum = 0;

void PreOrderTraverseCompare(const int *CmpNode, const BINARY_TREE_NODE *BiTreeNode, unsigned int Index) {	
	if (BiTreeNode == NULL) {
		return;
	} else {
		if (BiTreeNode->Data == CmpNode[Index]) {
			PreOrderTraverseCompareNum++;
		}
	
		Index++;
		PreOrderTraverseCompare(CmpNode, BiTreeNode->LeftChild, Index);
		PreOrderTraverseCompare(CmpNode, BiTreeNode->RightChild, Index);	
	} 
}
```

```c
void CmpPreOderBuildBinaryTree(const int *CmpNode, const BINARY_TREE_NODE *BiTreeNode, int Num) {
	unsigned int Index = 0;
	
	TestNum++;

	PreOrderTraverseCompare(CmpNode, BiTreeNode, Index);	

	if (PreOrderTraverseCompareNum != PreOrderTraverseCompareNum) {
		FaildNum++;
	} else {
		PassNum++;
	}
}
```

```c
void TestPreOderBuildBinaryTree(void) {
	/*Test01*/
	BINARY_TREE_NODE *BiTreeNodePtr01 = NULL;
	int Data01[] = {10, 20, 0, 40, 0, 0, 30, 0, 0};
	int Index01 = 0;
	int CmpBiTreeNodeData01[] = { 10, 20, 40, 30 };

	/*Test02*/
	BINARY_TREE_NODE *BiTreeNodePtr02 = NULL;
	BINARY_TREE_NODE_DATA Data02[] = { {10, 1, 1}, {20, 0, 1}, {40, 0, 0}, {30, 0, 0} };
	int Index02 = 0;
	int IfExistNodeFlag02 = 1;
	int CmpBiTreeNodeData02[] = {10, 20, 40, 30};

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	PreOderBuildBinaryTree01(&BiTreeNodePtr01, Data01, Index01);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData01, BiTreeNodePtr01, Index01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	PreOderBuildBinaryTree02(&BiTreeNodePtr02, Data02, Index02, IfExistNodeFlag02);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData02, BiTreeNodePtr02, Index02);

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
> PreOderBuildBinaryTree01 start
>
> In else, DataPtr[TraIndex] = 10
>
> PreOderBuildBinaryTree01 start
>
> In else, DataPtr[TraIndex] = 20
>
> PreOderBuildBinaryTree01 start
>
> PreOderBuildBinaryTree01 start
>
> In else, DataPtr[TraIndex] = 40
>
> PreOderBuildBinaryTree01 start
>
> PreOderBuildBinaryTree01 start
>
> PreOderBuildBinaryTree01 end
>
>  
>
> PreOderBuildBinaryTree01 end
>
>  
>
> PreOderBuildBinaryTree01 start
>
> In else, DataPtr[TraIndex] = 30
>
> PreOderBuildBinaryTree01 start
>
> PreOderBuildBinaryTree01 start
>
> PreOderBuildBinaryTree01 end
>
>  
>
> PreOderBuildBinaryTree01 end
>
>  
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
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 40
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 10
>
>  
>
> -------Test 02----------
>
> PreOderBuildBinaryTree02 start
>
> In else, DataPtr[0] = 10
>
> IfExistLeftChildNodeFlag = 1, IfExistRightChildNodeFlag = 1
>
> PreOderBuildBinaryTree02 start
>
> In else, DataPtr[1] = 20
>
> IfExistLeftChildNodeFlag = 0, IfExistRightChildNodeFlag = 1
>
> PreOderBuildBinaryTree02 start
>
> In Right, TraIndex = 2
>
> PreOderBuildBinaryTree02 start
>
> In else, DataPtr[2] = 40
>
> IfExistLeftChildNodeFlag = 0, IfExistRightChildNodeFlag = 0
>
> PreOderBuildBinaryTree02 start
>
> In Right, TraIndex = 3
>
> PreOderBuildBinaryTree02 start
>
> PreOderBuildBinaryTree02 end
>
>  
>
> PreOderBuildBinaryTree02 end
>
>  
>
> In Right, TraIndex = 3
>
> PreOderBuildBinaryTree02 start
>
> In else, DataPtr[3] = 30
>
> IfExistLeftChildNodeFlag = 0, IfExistRightChildNodeFlag = 0
>
> PreOderBuildBinaryTree02 start
>
> In Right, TraIndex = 4
>
> PreOderBuildBinaryTree02 start
>
> PreOderBuildBinaryTree02 end
>
>  
>
> PreOderBuildBinaryTree02 end
>
>  
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
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 40
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 10
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0







