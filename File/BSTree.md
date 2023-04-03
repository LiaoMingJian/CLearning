# 二叉搜索树——C语言描述——创建，查找，增加，删除结点

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​	中序遍历是有序的序列（从小到大）

**构建二叉树链接：**

https://blog.csdn.net/m0_59469991/article/details/127337105

# 2 查找

## （1）代码

```c
/*BSTSearch*/
bool BSTSearch(BINARY_TREE_NODE *BSTNode, BINARY_TREE_NODE *PreBSTNode, int Key, BINARY_TREE_NODE **RtNode) {
	if (BSTNode == NULL) {
		*RtNode = PreBSTNode;
		return false;
	}

	if (Key < BSTNode->Data) {
		BSTSearch(BSTNode->LeftChild, BSTNode, Key, RtNode);
	}
	else if (Key > BSTNode->Data) {
		BSTSearch(BSTNode->RightChild, BSTNode, Key, RtNode);
	}
	else {
		*RtNode = BSTNode;
		return true;
	}
}
```



##  （2）测试用例

```c
void CmpBool(bool Mem01, bool Mem02) {
	TestNum++;
	if (Mem01 == Mem02) {
		PassNum++;
	}
	else {
		FaildNum++;
		printf("Incorrect!\n");
	}
}

/*BSTSearch*/
void TestBSTSearch(void) {
	//    50
	//  10    70
	//   30  
	BINARY_TREE_NODE *BiTreeNodePtr = NULL;
	BINARY_TREE_NODE_DATA Data[] = { {50, 1, 1}, {10, 0, 1}, {30, 0, 0}, {70, 0, 0} };
	char IfExistNodeFlag = 1;

	/*Test01*/
	BINARY_TREE_NODE *BSTNode01 = NULL;
	int SearchKey01 = 30;
	bool SearchResult01;
	bool CmpResult01 = true;

	/*Test02*/
	BINARY_TREE_NODE *BSTNode02 = NULL;
	int SearchKey02 = 50;
	bool SearchResult02;
	bool CmpResult02 = true;

	/*Test03*/
	BINARY_TREE_NODE *BSTNode03 = NULL;
	int SearchKey03 = 100;
	bool SearchResult03;
	bool CmpResult03 = false;

	BuildBinaryTree(&BiTreeNodePtr, Data, IfExistNodeFlag);
	// printf("PreOrderTraversePrintBinaryTree\n");
	// PreOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("InOrderTraversePrintBinaryTree\n");
	// InOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("PostOrderTraversePrintBinaryTree\n");
	// PostOrderTraversePrintBinaryTree(BiTreeNodePtr);

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	SearchResult01 = BSTSearch(BiTreeNodePtr, BiTreeNodePtr, SearchKey01, &BSTNode01);
	CmpBool(CmpResult01, SearchResult01);

	/*Test02*/
	printf("-------Test 02----------\n");
	SearchResult02 = BSTSearch(BiTreeNodePtr, BiTreeNodePtr, SearchKey02, &BSTNode02);
	CmpBool(CmpResult02, SearchResult02);

	/*Test03*/
	printf("-------Test 03----------\n");
	SearchResult03 = BSTSearch(BiTreeNodePtr, BiTreeNodePtr, SearchKey03, &BSTNode03);
	CmpBool(CmpResult03, SearchResult03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



 **打印结果**

> -------Test start----------
>
>    
>
> -------Test 01----------
>
>  -------Test 02----------
>
>  -------Test 03----------
>
>   
>
> -------Test result----------
>
>  Print test result;
>
> TestNum = 3, PassNum = 3, FaildNum = 0



# 3 增加结点

## **（1）代码**

```c
/*AddBSTNode*/
void AddBSTNode(BINARY_TREE_NODE *BSTNode, BINARY_TREE_NODE *AddNode) {
	int Key;
	BINARY_TREE_NODE *PreBSTNode = NULL;

	if ((BSTNode == NULL) || (AddNode == NULL)) {
		return;
	}

	Key = AddNode->Data;

	if (!BSTSearch(BSTNode, BSTNode, Key, &PreBSTNode)) {
		AddNode->LeftChild = NULL;
		AddNode->RightChild = NULL;
		if (Key < PreBSTNode->Data) {
			PreBSTNode->LeftChild = AddNode;
		}
		else {
			PreBSTNode->RightChild = AddNode;
		}
	}
}
```

## （2）测试用例

```c
/*AddBSTNode*/
void TestAddBSTNode(void) {
	//     50
	//  10     70
	//    30  
	BINARY_TREE_NODE *BiTreeNodePtr = NULL;
	BINARY_TREE_NODE_DATA Data[] = { {50, 1, 1}, {10, 0, 1}, {30, 0, 0}, {70, 0, 0} };
	char IfExistNodeFlag = 1;

	/*Test01*/
	//      50
	//  10      70
	//    30  
	//   20
	BINARY_TREE_NODE AddNode01 = { 20, NULL, NULL };
	int Num01 = 5;
	int CmpBSTNode01[] = { 50, 10, 30, 20, 70 };

	/*Test02*/
	//          50
	//    10         70
	// 5     30  
	//	  20
	BINARY_TREE_NODE AddNode02 = { 5, NULL, NULL };
	int Num02 = 6;
	int CmpBSTNode02[] = { 50, 10, 5, 30, 20, 70 };

	/*Test03*/
	//          50
	//    10          70
	// 5     30    60
	//	  20
	BINARY_TREE_NODE AddNode03 = { 60, NULL, NULL };
	int Num03 = 7;
	int CmpBSTNode03[] = { 50, 10, 5, 30, 20, 70, 60 };

	BuildBinaryTree(&BiTreeNodePtr, Data, IfExistNodeFlag);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("InOrderTraversePrintBinaryTree\n");
	// InOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("PostOrderTraversePrintBinaryTree\n");
	// PostOrderTraversePrintBinaryTree(BiTreeNodePtr);

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	AddBSTNode(BiTreeNodePtr, &AddNode01);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode01, BiTreeNodePtr, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	AddBSTNode(BiTreeNodePtr, &AddNode02);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode02, BiTreeNodePtr, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	AddBSTNode(BiTreeNodePtr, &AddNode03);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode03, BiTreeNodePtr, Num03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**结果：**

>PreOrderTraversePrintBinaryTree
>
>BiTreeNode->Data = 50
>
>BiTreeNode->Data = 10
>
>BiTreeNode->Data = 30
>
>BiTreeNode->Data = 70
>
>-------Test start----------
>
> 
>
>-------Test 01----------
>
>Compare
>
>BiTreeNode->Data = 50 , CmpNode[0] = 50
>
>BiTreeNode->Data = 10 , CmpNode[1] = 10
>
>BiTreeNode->Data = 30 , CmpNode[2] = 30
>
>BiTreeNode->Data = 20 , CmpNode[3] = 20
>
>BiTreeNode->Data = 70 , CmpNode[4] = 70
>
>PreOrderTraverseCompareNum = 5, NodeNum = 5
>
> 
>
>-------Test 02----------
>
>Compare
>
>BiTreeNode->Data = 50 , CmpNode[0] = 50
>
>BiTreeNode->Data = 10 , CmpNode[1] = 10
>
>BiTreeNode->Data = 5 , CmpNode[2] = 5
>
>BiTreeNode->Data = 30 , CmpNode[3] = 30
>
>BiTreeNode->Data = 20 , CmpNode[4] = 20
>
>BiTreeNode->Data = 70 , CmpNode[5] = 70
>
>PreOrderTraverseCompareNum = 6, NodeNum = 6
>
> 
>
>-------Test 03----------
>
>Compare
>
>BiTreeNode->Data = 50 , CmpNode[0] = 50
>
>BiTreeNode->Data = 10 , CmpNode[1] = 10
>
>BiTreeNode->Data = 5 , CmpNode[2] = 5
>
>BiTreeNode->Data = 30 , CmpNode[3] = 30
>
>BiTreeNode->Data = 20 , CmpNode[4] = 20
>
>BiTreeNode->Data = 70 , CmpNode[5] = 70
>
>BiTreeNode->Data = 60 , CmpNode[6] = 60
>
>PreOrderTraverseCompareNum = 7, NodeNum = 7
>
> 
>
>-------Test result----------
>
>Print test result;
>
>TestNum = 3, PassNum = 3, FaildNum = 0



# 4 删除结点

## （1）代码

```c
void DelNode(BINARY_TREE_NODE **BSTNode) {
	BINARY_TREE_NODE *P = NULL;
	BINARY_TREE_NODE *S = NULL;

	if ((*BSTNode)->LeftChild == NULL) {
		P = *BSTNode;
		*BSTNode = (*BSTNode)->RightChild;
		free(P);
	} else if ((*BSTNode)->RightChild == NULL) {
		P = *BSTNode;
		*BSTNode = (*BSTNode)->LeftChild;
		free(P);
	} else {
		P = *BSTNode;
		S = (*BSTNode)->LeftChild;

		while (S->RightChild != NULL) {
			P = S;
			S = S->RightChild;
		}

		(*BSTNode)->Data = S->Data;

		if (P != *BSTNode) {
			P->RightChild = S->LeftChild;
		} else {
			P->LeftChild = S->LeftChild;
		}
		free(S);
	}
}

void DelBSTNode(BINARY_TREE_NODE **BSTNode, int Key) {
	if ((*BSTNode == NULL)) {
		return;
	}

	if (Key < (*BSTNode)->Data) {
		DelBSTNode(&((*BSTNode)->LeftChild), Key);
	} else if (Key > (*BSTNode)->Data) {
		DelBSTNode(&(*BSTNode)->RightChild, Key);
	} else {
		DelNode(BSTNode);
	}
}
```



## （2）测试用例

```c
/*TestDelBSTNode*/
void TestDelBSTNode(void) {
	//          50
	//    20           70
	// 10    30    60	  90
	BINARY_TREE_NODE *BiTreeNodePtr = NULL;
	BINARY_TREE_NODE_DATA Data[] = { {50, 1, 1}, {20, 1, 1}, {10, 0, 0}, {30, 0, 0}, {70, 1, 1}, {60, 0, 0}, {90, 0, 0} };
	char IfExistNodeFlag = 1;

	/*Test01*/
	//          50
	//    20           70
	//        30    60    90
	int Key01 = 10;
	int Num01 = 6;
	int CmpBSTNode01[] = { 50, 20, 30, 70, 60, 90 };

	/*Test02*/
	//          50
	//    30           70
	//              60    90
	int Key02 = 20;
	int Num02 = 5;
	int CmpBSTNode02[] = { 50, 30, 70, 60, 90 };

	/*Test03*/
	//          50
	//    30           60
	//						90
	int Key03 = 70;
	int Num03 = 4;
	int CmpBSTNode03[] = { 50, 30, 60, 90 };

	/*Test04*/
	//          30
	//                60
	//						90
	int Key04 = 50;
	int Num04 = 3;
	int CmpBSTNode04[] = { 30, 60, 90 };

	BuildBinaryTree(&BiTreeNodePtr, Data, IfExistNodeFlag);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("InOrderTraversePrintBinaryTree\n");
	// InOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("PostOrderTraversePrintBinaryTree\n");
	// PostOrderTraversePrintBinaryTree(BiTreeNodePtr);

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	DelBSTNode(&BiTreeNodePtr, Key01);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode01, BiTreeNodePtr, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	DelBSTNode(&BiTreeNodePtr, Key02);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode02, BiTreeNodePtr, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	DelBSTNode(&BiTreeNodePtr, Key03);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode03, BiTreeNodePtr, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	DelBSTNode(&BiTreeNodePtr, Key04);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode04, BiTreeNodePtr, Num04);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**结果：**

>PreOrderTraversePrintBinaryTree
>
>BiTreeNode->Data = 50
>
>BiTreeNode->Data = 20
>
>BiTreeNode->Data = 10
>
>BiTreeNode->Data = 30
>
>BiTreeNode->Data = 70
>
>BiTreeNode->Data = 60
>
>BiTreeNode->Data = 90
>
>-------Test start----------
>
> 
>
>-------Test 01----------
>
>Compare
>
>BiTreeNode->Data = 50 , CmpNode[0] = 50
>
>BiTreeNode->Data = 20 , CmpNode[1] = 20
>
>BiTreeNode->Data = 30 , CmpNode[2] = 30
>
>BiTreeNode->Data = 70 , CmpNode[3] = 70
>
>BiTreeNode->Data = 60 , CmpNode[4] = 60
>
>BiTreeNode->Data = 90 , CmpNode[5] = 90
>
>PreOrderTraverseCompareNum = 6, NodeNum = 6
>
> 
>
>-------Test 02----------
>
>Compare
>
>BiTreeNode->Data = 50 , CmpNode[0] = 50
>
>BiTreeNode->Data = 30 , CmpNode[1] = 30
>
>BiTreeNode->Data = 70 , CmpNode[2] = 70
>
>BiTreeNode->Data = 60 , CmpNode[3] = 60
>
>BiTreeNode->Data = 90 , CmpNode[4] = 90
>
>PreOrderTraverseCompareNum = 5, NodeNum = 5
>
> 
>
>-------Test 03----------
>
>Compare
>
>BiTreeNode->Data = 50 , CmpNode[0] = 50
>
>BiTreeNode->Data = 30 , CmpNode[1] = 30
>
>BiTreeNode->Data = 60 , CmpNode[2] = 60
>
>BiTreeNode->Data = 90 , CmpNode[3] = 90
>
>PreOrderTraverseCompareNum = 4, NodeNum = 4
>
> 
>
>-------Test 04----------
>
>Compare
>
>BiTreeNode->Data = 30 , CmpNode[0] = 30
>
>BiTreeNode->Data = 60 , CmpNode[1] = 60
>
>BiTreeNode->Data = 90 , CmpNode[2] = 90
>
>PreOrderTraverseCompareNum = 3, NodeNum = 3
>
> 
>
>-------Test result----------
>
>Print test result;
>
>TestNum = 4, PassNum = 4, FaildNum = 0
