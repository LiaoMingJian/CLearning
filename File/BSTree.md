# 二叉搜索树——C语言描述——创建，查找，增加，删除结点

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​	树上每个左子树的结点均小于根结点，且根结点小于右子树的所有结点，中序遍历是从小到大序列。

**构建二叉树链接：**

https://blog.csdn.net/m0_59469991/article/details/127337105

# 2 查找

​	递归法查找，查到时把该结点返回，没查到时返回上一个结点。

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

**①方法一：**

​	先查找key值对应的结点是否存在，不存在的话，就增加结点。注意树原来就是空的情况。

```c
void AddBSTNode(BINARY_TREE_NODE **BSTNode, int Key) {
	BINARY_TREE_NODE *AddNode = NULL;
	BINARY_TREE_NODE *PreNode = NULL;

	if (BSTNode == NULL) {
		return;
	}

	if (!BSTSearch(*BSTNode, *BSTNode, Key, &PreNode)) {
		AddNode = (BINARY_TREE_NODE *)malloc(sizeof(BINARY_TREE_NODE));
		if (AddNode == NULL) {
			return;
		}
		AddNode->Data = Key;
		AddNode->LeftChild = NULL;
		AddNode->RightChild = NULL;

		if (PreNode == NULL) {
			*BSTNode = AddNode;
		} else if (Key < PreNode->Data) {
			PreNode->LeftChild = AddNode;
		} else {
			PreNode->RightChild = AddNode;
		}
	}
}
```

**②方法二：**

​	直接构建。

**代码：**

```c
void AddBSTNode02(BINARY_TREE_NODE **BSTNode, int Key) {
	if (*BSTNode == NULL) {
		*BSTNode = (BINARY_TREE_NODE *)malloc(sizeof(BINARY_TREE_NODE));
		if (*BSTNode == NULL) {
			return;
		}
		(*BSTNode)->Data = Key;
		(*BSTNode)->LeftChild = NULL;
		(*BSTNode)->RightChild = NULL;
	}
	else {
		if (Key < (*BSTNode)->Data) {
			AddBSTNode02(&((*BSTNode)->LeftChild), Key);
		}
		else if (Key > (*BSTNode)->Data) {
			AddBSTNode02(&((*BSTNode)->RightChild), Key);
		}
		else {
			return;
		}
	}
}
```

## （2）测试用例

```c
/*AddBSTNode*/
void TestAddBSTNode(void) {
	BINARY_TREE_NODE *BSTNode = NULL;
	BINARY_TREE_NODE *BSTNode11 = NULL;

	/*Test01*/
	//	20
	int Key01 = 20;
	int Num01 = 1;
	int CmpBSTNode01[] = {20};

	/*Test02*/
	//	    20
	//	10
	int Key02 = 10;
	int Num02 = 2;
	int CmpBSTNode02[] = { 20, 10 };

	/*Test03*/
	//	    20
	//	10		50
	int Key03 = 50;
	int Num03 = 3;
	int CmpBSTNode03[] = { 20, 10, 50 };

	/*Test04*/
	//  	    20
	//	  10		 50
	//			 30
	int Key04 = 30;
	int Num04 = 4;
	int CmpBSTNode04[] = { 20, 10, 50, 30 };

	/*Test05*/
	//  	    20
	//	   10		 50
	//	5		 30
	int Key05 = 5;
	int Num05 = 5;
	int CmpBSTNode05[] = { 20, 10, 5, 50, 30 };

	printf("-------Test start----------\n");
	InitNum();
	
	/*Test01*/
	printf("\n-------Test 01----------\n");
	AddBSTNode(&BSTNode, Key01);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode01, BSTNode, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	AddBSTNode(&BSTNode, Key02);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode02, BSTNode, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	AddBSTNode(&BSTNode, Key03);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode03, BSTNode, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	AddBSTNode(&BSTNode, Key04);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode04, BSTNode, Num04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	AddBSTNode(&BSTNode, Key05);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode05, BSTNode, Num05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**结果：**

>-------Test start----------
>
> 
>
>-------Test 01----------
>
>Compare
>
>BiTreeNode->Data = 20
>
>PreOrderTraverseCompareNum = 1, NodeNum = 1
>
>  
>
>-------Test 02----------
>
>Compare
>
>BiTreeNode->Data = 20
>
>BiTreeNode->Data = 10
>
>PreOrderTraverseCompareNum = 2, NodeNum = 2
>
> 
>
>-------Test 03----------
>
>Compare
>
> BiTreeNode->Data = 20
>
>BiTreeNode->Data = 10
>
>BiTreeNode->Data = 50
>
>PreOrderTraverseCompareNum = 3, NodeNum = 3
>
> 
>
>-------Test 04----------
>
>Compare
>
>BiTreeNode->Data = 20
>
>BiTreeNode->Data = 10
>
>BiTreeNode->Data = 50
>
> BiTreeNode->Data = 30
>
>PreOrderTraverseCompareNum = 4, NodeNum = 4
>
> 
>
>-------Test 05----------
>
>Compare
>
>BiTreeNode->Data = 20
>
>BiTreeNode->Data = 10
>
>BiTreeNode->Data = 5
>
>BiTreeNode->Data = 50
>
>BiTreeNode->Data = 30
>
>PreOrderTraverseCompareNum = 5, NodeNum = 5
>
>  
>
>-------Test result----------
>
>Print test result;
>
>TestNum = 5, PassNum = 5, FaildNum = 0



# 4 创建二叉排序树

​	利用增加结点的函数进行创建。

**代码：**

```c
void BuildBSTree(BINARY_TREE_NODE **BSTNode, int *Arr, int Num) {
	int i = 0;

	if ((BSTNode == NULL) || (Arr == NULL)) {
		return;
	}

	for (i = 0; i < Num; i++) {
		AddBSTNode(BSTNode, Arr[i]);
	}
}
```



**测试用例：**

```c
/*TestBuildBSTree*/
void TestBuildBSTree(void) {
	/*Test01*/
	//		   30
	//	  20	    50
	// 10		 40
	int Arr01[] = { 30, 20, 50, 40, 10 };
	int Num01 = 5;
	BINARY_TREE_NODE *BSTNode01 = NULL;
	int CmpBSTNode01[] = {30, 20, 10, 50, 40};

	/*Test02*/
	//		   20
	//	  10	     50
	//			 30
	//				40	
	int Arr02[] = { 20, 50, 10, 30, 40 };
	int Num02 = 5;
	BINARY_TREE_NODE *BSTNode02 = NULL;
	int CmpBSTNode02[] = { 20, 10, 50, 30, 40 };

	/*Test03*/
	//		   30
	//	  10	    50
	//		20	 40
	//				
	int Arr03[] = { 30, 10, 50, 20, 40 };
	int Num03 = 5;
	BINARY_TREE_NODE *BSTNode03 = NULL;
	int CmpBSTNode03[] = { 30, 10, 20, 50, 40 };

	/*Test04*/
	//	  10
	//	     20
	//	        30
	//	           40
	//                50
	int Arr04[] = { 10, 20, 30, 40, 50 };
	int Num04 = 5;
	BINARY_TREE_NODE *BSTNode04 = NULL;
	int CmpBSTNode04[] = { 10, 20, 30, 40, 50 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildBSTree(&BSTNode01, Arr01, Num01);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BSTNode01);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode01, BSTNode01, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildBSTree(&BSTNode02, Arr02, Num02);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BSTNode02);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode02, BSTNode02, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	BuildBSTree(&BSTNode03, Arr03, Num03);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BSTNode03);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode03, BSTNode03, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	BuildBSTree(&BSTNode04, Arr04, Num04);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BSTNode04);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode04, BSTNode04, Num04);

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
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 40
>
> Compare
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 40
>
> PreOrderTraverseCompareNum = 5, NodeNum = 5
>
>  
>
> -------Test 02----------
>
> PreOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 40
>
> Compare
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 40
>
> PreOrderTraverseCompareNum = 5, NodeNum = 5
>
>  
>
> -------Test 03----------
>
> PreOrderTraversePrintBinaryTree
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 40
>
> Compare
>
> BiTreeNode->Data = 30
>
> BiTreeNode->Data = 10
>
> BiTreeNode->Data = 20
>
> BiTreeNode->Data = 50
>
> BiTreeNode->Data = 40
>
> PreOrderTraverseCompareNum = 5, NodeNum = 5
>
>  
>
> -------Test 04----------
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
> Compare
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
> PreOrderTraverseCompareNum = 5, NodeNum = 5
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 4, PassNum = 4, FaildNum = 0



# 5 删除结点

​	先查找Key值对应的结点，然后进行删除操作，注意DelBSTNode函数入参结点为双重指针，因为要修改结点的地址。

​	删除结点有三种情况：

①   结点只有左子树为空，只需将右子树替换原来根结点的位置。

②   结点只有右子树为空，只需将右子树替换原来根结点的位置。

③   结点的左右子树均不为空，先找到该结点的直接前驱结点（即中序遍历该结点的前驱结点），操作方法为先找该结点的左孩子，然后再找到最右的孩子，并记录最右孩子的前驱结点。将待删除结点的数据等于最右孩子结点数据，并将最右孩子的左子树移到最右孩子前驱结点的右子树位置。

## （1）代码

```c
void DelNode(BINARY_TREE_NODE **BSTNode) {
	BINARY_TREE_NODE *Tmp01 = NULL;
	BINARY_TREE_NODE *Tmp02 = NULL;

	if ((*BSTNode)->LeftChild == NULL) {
		Tmp01 = *BSTNode;
		*BSTNode = (*BSTNode)->RightChild;
		free(Tmp01);
		Tmp01 = NULL;
	} else if ((*BSTNode)->RightChild == NULL) {
		Tmp01 = *BSTNode;
		*BSTNode = (*BSTNode)->LeftChild;
		free(Tmp01);
		Tmp01 = NULL;
	} else {
		Tmp01 = *BSTNode;
		Tmp02 = (*BSTNode)->LeftChild;

		while (Tmp02->RightChild != NULL) {
			Tmp01 = Tmp02;
			Tmp02 = Tmp02->RightChild;
		}

		(*BSTNode)->Data = Tmp02->Data;

		if (Tmp01 != *BSTNode) {
			Tmp01->RightChild = Tmp02->LeftChild;
		}else {
			Tmp01->LeftChild = Tmp02->LeftChild;
		}

		free(Tmp02);
		Tmp02 = NULL;
	}
}

void DelBSTNode(BINARY_TREE_NODE **BSTNode, int Key) {
	if ((BSTNode == NULL) || (*BSTNode == NULL)) {
		return;
	}

	if (Key < (*BSTNode)->Data) {
		DelBSTNode(&((*BSTNode)->LeftChild), Key);
	} else if (Key > (*BSTNode)->Data) {
		DelBSTNode(&((*BSTNode)->RightChild), Key);
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
