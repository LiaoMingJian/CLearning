# 平衡二叉树——C语言描述——创建，增加结点

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​	是一种二叉排序树，其中每个结点的左子树和右子树的高度差至多等于1



# 2 数据结构

​	增加平衡因子，表示为左子树减右子树的差值。

```c
/*AVL_TREE_NODE*/
#define EH (0)
#define LH (1)
#define RH (-1)

typedef struct _AVL_TREE_NODE {
	int Data;
	int BF;
	struct _BINARY_TREE_NODE *LeftChild;
	struct _BINARY_TREE_NODE *RightChild;
}AVL_TREE_NODE;
```



# 2 增加平衡二叉树的结点

​    设置Taller标志，增加结点后，Taller为true，当高度一致时或者左右平衡处理后，Taller为false。

​	结点BF值的判断，当结点左右子树增加结点时，BF进行相应的变化，当BF的绝对值大于1值，进行左右平衡处理。

## （1）代码

```c
/*AVL_TREE_NODE*/
void PreOrderTraversePrintAVLTree(const AVL_TREE_NODE *AVLNode) {
	if (AVLNode == NULL) {
		return;
	} else {
		//printf("AVLNode = 0x%lx, AVLNode->Data = %d, AVLNode->BF = %d, AVLNode->LeftChild = 0x%lx, AVLNode->RightChild = 0x%lx\n", AVLNode, AVLNode->Data, AVLNode->BF, AVLNode->LeftChild, AVLNode->RightChild);
		printf("AVLNode->Data = %d, AVLNode->BF = %d\n", AVLNode->Data, AVLNode->BF);
		PreOrderTraversePrintAVLTree(AVLNode->LeftChild);
		PreOrderTraversePrintAVLTree(AVLNode->RightChild);
	}
}

void InOrderTraversePrintAVLTree(const AVL_TREE_NODE *AVLNode) {
	if (AVLNode == NULL) {
		return;
	} else {
		InOrderTraversePrintAVLTree(AVLNode->LeftChild);
		printf("AVLNode->Data = %d, AVLNode->BF = %d\n", AVLNode->Data, AVLNode->BF);
		InOrderTraversePrintAVLTree(AVLNode->RightChild);
	}
}

void PostOrderTraversePrintAVLTree(const AVL_TREE_NODE *AVLNode) {
	if (AVLNode == NULL) {
		return;
	} else {
		PostOrderTraversePrintAVLTree(AVLNode->LeftChild);
		PostOrderTraversePrintAVLTree(AVLNode->RightChild);
		printf("AVLNode->Data = %d, AVLNode->BF = %d\n", AVLNode->Data, AVLNode->BF);
	}
}

void LeftRotate(AVL_TREE_NODE **AVLNode) {
	AVL_TREE_NODE *AVLRightNode = NULL;

	AVLRightNode = (*AVLNode)->RightChild;
	(*AVLNode)->RightChild = AVLRightNode->LeftChild;
	AVLRightNode->LeftChild = *AVLNode;
	*AVLNode = AVLRightNode;
}

void RightRotate(AVL_TREE_NODE **AVLNode) {
	AVL_TREE_NODE *AVLLeftNode = NULL;

	AVLLeftNode = (*AVLNode)->LeftChild;
	(*AVLNode)->LeftChild = AVLLeftNode->RightChild;
	AVLLeftNode->RightChild = *AVLNode;
	*AVLNode = AVLLeftNode;
}

void RightBalance(AVL_TREE_NODE **AVLNode) {
	AVL_TREE_NODE *AVLRightNode = NULL;
	AVL_TREE_NODE *AVLRightLeftNode = NULL;

	AVLRightNode = (*AVLNode)->RightChild;

	if (AVLRightNode->BF == RH) {
		AVLRightNode->BF = EH;
		(*AVLNode)->BF = EH;
		LeftRotate(AVLNode);
	} else if (AVLRightNode->BF == LH) {
		AVLRightLeftNode = AVLRightNode->LeftChild;
		switch (AVLRightLeftNode->BF) {
			case LH:
				AVLRightNode->BF = RH;
				(*AVLNode)->BF = EH;
				break;
			case EH:
				AVLRightNode->BF = EH;
				(*AVLNode)->BF = EH;
				break;
			case RH:
				AVLRightNode->BF = EH;
				(*AVLNode)->BF = LH;
				break;
		}

		AVLRightLeftNode->BF = EH;
		RightRotate(&((*AVLNode)->RightChild));
		LeftRotate(AVLNode);
	}
}

void LeftBalance(AVL_TREE_NODE **AVLNode) {
	AVL_TREE_NODE *AVLLeftNode = NULL;
	AVL_TREE_NODE *AVLLeftRightNode = NULL;
	
	AVLLeftNode = (*AVLNode)->LeftChild;

	if (AVLLeftNode->BF == LH) {
		AVLLeftNode->BF = EH;
		(*AVLNode)->BF = EH;
		RightRotate(AVLNode);
	} else if (AVLLeftNode->BF == RH) {
		AVLLeftRightNode = AVLLeftNode->RightChild;
		switch (AVLLeftRightNode->BF) {
			case LH:
				AVLLeftNode->BF = EH;
				(*AVLNode)->BF = RH;
				break;
			case EH:
				AVLLeftNode->BF = EH;
				(*AVLNode)->BF = EH;
				break;
			case RH:
				AVLLeftNode->BF = LH;
				(*AVLNode)->BF = EH;
				break;
		}

		AVLLeftRightNode->BF = EH;
		LeftRotate(&((*AVLNode)->LeftChild));
		RightRotate(AVLNode);
	}
}

bool AddAVLNode(AVL_TREE_NODE **AVLNode, int Key, bool *Taller) {
	//printf("AVLNode = 0x%lx, *AVLNode = 0x%lx, *Taller = %d\n", AVLNode, *AVLNode, *Taller);
	if ((*AVLNode) == NULL) {
		//pritf("Test 01\n");
		*AVLNode = (AVL_TREE_NODE *)malloc(sizeof(AVL_TREE_NODE));
		if ((*AVLNode == NULL)) {
			return false;
		}
		(*AVLNode)->Data = Key;
		(*AVLNode)->BF = EH;
		(*AVLNode)->LeftChild = NULL;
		(*AVLNode)->RightChild = NULL;
		*Taller = true;
	} else {
		//printf("Left\n");
		if (Key < (*AVLNode)->Data) {
			if (!AddAVLNode(&((*AVLNode)->LeftChild), Key, Taller)) {
				return false;
			}

			if (*Taller == true) {
				switch ((*AVLNode)->BF) {
					case LH:
						LeftBalance(AVLNode);
						*Taller = false;
						break;
					case EH:
						(*AVLNode)->BF = LH;
						*Taller = true;
						break;
					case RH:
						(*AVLNode)->BF = EH;
						*Taller = false;
						break;
				}
			}
		} else if (Key > (*AVLNode)->Data) {
			if (!AddAVLNode(&((*AVLNode)->RightChild), Key, Taller)) {
				return false;
			}

			if (*Taller == true) {
				switch ((*AVLNode)->BF) {
					case LH:
						(*AVLNode)->BF = EH;
						*Taller = false;
						break;
					case EH:
						(*AVLNode)->BF = RH;
						*Taller = true;
						break;
					case RH:
						RightBalance(AVLNode);
						*Taller = false;
						break;
				}
			}
		} else {
			*Taller = false;
			return false;
		}
	}

	return true;
}
```



##  （2）测试用例

```c
/*AVL_TREE_NODE*/
void PreOrderTraverseAVLCompare(const int *CmpNode, const AVL_TREE_NODE *AVLNode) {
	if (AVLNode == NULL) {
		return;
	} else {
		//printf("CmpNode[%d] = %d, AVLNode->Data = 0x%lx, AVLNode->BF = %d, BiTreeNode->LeftChild = 0x%lx, BiTreeNode->RightChild = 0x%lx\n", CmpNode[BiIndex], AVLNode->Data, AVLNode->BF, AVLNode->LeftChild, AVLNode->RightChild);
		//printf("AVLNode->Data = %d, AVLNode->BF = %d\n", AVLNode->Data, AVLNode->BF);
		if (AVLNode->Data == CmpNode[BiIndex]) {
			PreOrderTraverseCompareNum++;
		}

		BiIndex++;
		PreOrderTraverseAVLCompare(CmpNode, AVLNode->LeftChild);
		PreOrderTraverseAVLCompare(CmpNode, AVLNode->RightChild);
	}
}

void CmpPreOderBuildAVLTree(const int *CmpNode, const AVL_TREE_NODE *AVLNode, int NodeNum) {
	BiIndex = 0;
	PreOrderTraverseCompareNum = 0;

	TestNum++;
	PreOrderTraverseAVLCompare(CmpNode, AVLNode);
	printf("PreOrderTraverseCompareNum = %d, NodeNum = %d\n", PreOrderTraverseCompareNum, NodeNum);
	if (PreOrderTraverseCompareNum != NodeNum) {
		FaildNum++;
	} else {
		PassNum++;
	}
}


/*AddAVLNode*/
void TestAddAVLNode(void) {
	AVL_TREE_NODE *AVLNode = NULL;

	/*Test01*/
	// 30_EH
	//	30
	int Key01          = 30;
	int Num01          = 1;
	bool Taller01      = false;
	int CmpAVLNode01[] = { 30 };

	/*Test02*/
	// 30_LH
	//	    30
	//	10
	int Key02 = 10;
	int Num02 = 2;
	bool Taller02 = false;
	int CmpAVLNode02[] = { 30, 10 };

	/*Test03*/
	// 30_EH
	//	    30
	//	10      40
	int Key03 = 40;
	int Num03 = 3;
	bool Taller03 = false;
	int CmpAVLNode03[] = { 30, 10, 40 };

	/*Test04*/
	// 10_LH
	//	    30
	//   10    40
	// 9
	int Key04 = 9;
	int Num04 = 4;
	bool Taller04 = false;
	int CmpAVLNode04[] = { 30, 10, 9, 40 };

	/*Test05*/
	// LeftBlance_LH
	//	       30
	//     10       40
	//   9    
	// 5
	// 10_RightRotate
	//	       30
	//     9       40
	//  5    10
	int Key05 = 5;
	int Num05 = 5;
	bool Taller05 = false;
	int CmpAVLNode05[] = { 30, 9, 5, 10, 40 };

	/*Test06*/
	// 30_EH
	//	        30
	//     9        40
	//   5   10        50
	int Key06 = 50;
	int Num06 = 6;
	bool Taller06 = false;
	int CmpAVLNode06[] = { 30, 9, 5, 10, 40, 50 };

	/*Test07*/
	// 5_LH
	//	        30
	//     9        40
	//   5   10        50
	// 1
	int Key07 = 1;
	int Num07 = 7;
	bool Taller07 = false;
	int CmpAVLNode07[] = { 30, 9, 5, 1, 10, 40, 50 };

	/*Test08*/
	// LeftBlance_RH_EH_5_1
	//	        30
	//     9        40
	//   5   10        50
	// 1
	//  3
	// 1_LeftRotate
	//	         30
	//      9        40
	//    5   10        50
	//  3
	// 1
	// 5_RightRotate
	//	         30
	//      9        40
	//   3    10        50
	// 1   5
	int Key08 = 3;
	int Num08 = 8;
	bool Taller08 = false;
	int CmpAVLNode08[] = { 30, 9, 3, 1, 5, 10, 40, 50 };

	/*Test09*/
	// LeftBlance_RH_LH_9_3
	//	         30
	//      9        40
	//   3    10        50
	// 1   5
	//    4
	// 3_LefteRotate
	//	           30
	//        9        40
	//     5    10        50
	//   3
	// 1  4
	// 7_RightRotate
	//	          30
	//       5        40
	//    3    9         50
	//  1  4    10
	int Key09 = 4;
	int Num09 = 9;
	bool Taller09 = false;
	int CmpAVLNode09[] = { 30, 5, 3, 1, 4, 9, 10, 40, 50 };

	/*Test10*/
	// 9_EH
	//	          30
	//       5        40
	//    3    9         50
	//  1  4  6 10
	int Key10 = 6;
	int Num10 = 10;
	bool Taller10 = false;
	int CmpAVLNode10[] = { 30, 5, 3, 1, 4, 9, 6, 10, 40, 50 };

	/*Test11*/
	// LeftBalance_RH_RH_30_5
	//	             30
	//       5               40
	//    3    9                 50
	//  1  4  6 10
	//            15
	// 5_LeftRotate
	//	             30
	//       9               40
	//    5    10                 50
	//  3  6     15
	// 1 4
	// 30_RightRotate
	//	             9
	//       5               30
	//    3    6          10    40
	//   1 4                15    50
	int Key11 = 15;
	int Num11 = 11;
	bool Taller11 = false;
	int CmpAVLNode11[] = { 9, 5, 3, 1, 4, 6, 30, 10, 15, 40, 50 };

	/*Test12*/
	// RightBalance_RH
	//	             9
	//       5               30
	//    3    6          10    40
	//   1 4                15    50
	//                               60
	// 40_LeftRotate
	//	             9
	//       5                30
	//    3    6          10       50
	//   1 4                15  40   60
	int Key12 = 60;
	int Num12 = 12;
	bool Taller12 = false;
	int CmpAVLNode12[] = { 9, 5, 3, 1, 4, 6, 30, 10, 15, 50, 40, 60 };

	/*Test13*/
	// RightBalance_LH_EH
	//	              9
	//       5                 30
	//    3    6          10       50
	//   1 4                 15  40   60
	//                     12
	// 15_RightRotate
	//	              9
	//       5                 30
	//    3    6          10        50
	//   1 4                 12   40   60
	//                         15
	// 12_LeftRotate
	//	              9
	//       5                 30
	//    3    6          12        50
	//   1 4           10    15   40   60
	int Key13 = 12;
	int Num13 = 13;
	bool Taller13 = false;
	int CmpAVLNode13[] = { 9, 5, 3, 1, 4, 6, 30, 12, 10, 15, 50, 40, 60 };

	/*Test14*/
	// 6_RH
	//	              9
	//       5                 30
	//    3    6          12         50
	//   1 4     7      10    15   40    60
	int Key14 = 7;
	int Num14 = 14;
	bool Taller14 = false;
	int CmpAVLNode14[] = { 9, 5, 3, 1, 4, 6, 7, 30, 12, 10, 15, 50, 40, 60 };

	/*Test15*/
	// 60_RH
	//	              9
	//       5                 30
	//    3    6          12          50
	//   1 4     7      10    15   40    60
	//                                     70
	int Key15 = 70;
	int Num15 = 15;
	bool Taller15 = false;
	int CmpAVLNode15[] = { 9, 5, 3, 1, 4, 6, 7, 30, 12, 10, 15, 50, 40, 60, 70 };

	/*Test16*/
	// 60_EH
	//	              9
	//       5                 30
	//    3    6          12           50
	//   1 4     7      10    15   40     60
	//                                  55  70
	int Key16 = 55;
	int Num16 = 16;
	bool Taller16 = false;
	int CmpAVLNode16[] = { 9, 5, 3, 1, 4, 6, 7, 30, 12, 10, 15, 50, 40, 60, 55, 70 };

	/*Test17*/
	// RightBalance_LH_LH
	//	              9
	//       5                 30
	//    3    6          12            50
	//   1 4     7      10    15   40        60
	//                                     55  70
	//                                    53
	// 60_RightRotate
	//	              9
	//       5                 30
	//    3    6          12           50
	//   1 4     7      10    15   40      55
	//                                   53   60
	//                                          70
	// 50_LeftRotate
	//	              9
	//       5                    30
	//    3    6           12           55
	//   1 4     7      10    15     50    60
	//                             40  53    70
	int Key17 = 53;
	int Num17 = 17;
	bool Taller17 = false;
	int CmpAVLNode17[] = { 9, 5, 3, 1, 4, 6, 7, 30, 12, 10, 15, 55, 50, 40, 53, 60, 70 };

	/*Test18*/
	// RightBalance_LH_RH
	//	              9
	//       5                     30
	//    3    6           12                 55
	//   1 4     7      10    15         50      60
	//                                 40  53      70
	//                                      54
	// 55_RightRotate
	//	              9
	//       5                    30
	//    3    6           12              50
	//   1 4     7      10    15       40      55
	//                                      53    60
	//                                       54     70
	// 30_LeffRotate
	//	              9
	//       5                      50
	//    3    6             30            55
	//   1 4     7       12     40      53    60   
	//                 10   15           54     70
	int Key18 = 54;
	int Num18 = 18;
	bool Taller18 = false;
	int CmpAVLNode18[] = { 9, 5, 3, 1, 4, 6, 7, 50, 30, 12, 10, 15, 40, 55, 53, 54, 60, 70 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	AddAVLNode(&AVLNode, Key01, &Taller01);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode01, AVLNode, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	AddAVLNode(&AVLNode, Key02, &Taller02);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode02, AVLNode, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	AddAVLNode(&AVLNode, Key03, &Taller03);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode03, AVLNode, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	AddAVLNode(&AVLNode, Key04, &Taller04);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode04, AVLNode, Num04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	AddAVLNode(&AVLNode, Key05, &Taller05);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode05, AVLNode, Num05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	AddAVLNode(&AVLNode, Key06, &Taller06);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode06, AVLNode, Num06);

	/*Test07*/
	printf("\n-------Test 07----------\n");
	AddAVLNode(&AVLNode, Key07, &Taller07);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode07, AVLNode, Num07);

	/*Test08*/
	printf("\n-------Test 08----------\n");
	AddAVLNode(&AVLNode, Key08, &Taller08);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode08, AVLNode, Num08);

	/*Test09*/
	printf("\n-------Test 09----------\n");
	AddAVLNode(&AVLNode, Key09, &Taller09);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode09, AVLNode, Num09);

	/*Test10*/
	printf("\n-------Test 10----------\n");
	AddAVLNode(&AVLNode, Key10, &Taller10);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode10, AVLNode, Num10);

	/*Test11*/
	printf("\n-------Test 11----------\n");
	AddAVLNode(&AVLNode, Key11, &Taller11);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode11, AVLNode, Num11);

	/*Test12*/
	printf("\n-------Test 12----------\n");
	AddAVLNode(&AVLNode, Key12, &Taller12);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode12, AVLNode, Num12);

	/*Test13*/
	printf("\n-------Test 13----------\n");
	AddAVLNode(&AVLNode, Key13, &Taller13);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode13, AVLNode, Num13);

	/*Test14*/
	printf("\n-------Test 14----------\n");
	AddAVLNode(&AVLNode, Key14, &Taller14);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode14, AVLNode, Num14);

	/*Test15*/
	printf("\n-------Test 15----------\n");
	AddAVLNode(&AVLNode, Key15, &Taller15);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode15, AVLNode, Num15);

	/*Test16*/
	printf("\n-------Test 16----------\n");
	AddAVLNode(&AVLNode, Key16, &Taller16);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode16, AVLNode, Num16);

	/*Test17*/
	printf("\n-------Test 17----------\n");
	AddAVLNode(&AVLNode, Key17, &Taller17);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode17, AVLNode, Num17);

	/*Test18*/
	printf("\n-------Test 18----------\n");
	AddAVLNode(&AVLNode, Key18, &Taller18);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode18, AVLNode, Num18);

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
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 1, NodeNum = 1
>
>  
>
> -------Test 02----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 2, NodeNum = 2
>
>  
>
> -------Test 03----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 04----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 1
>
> AVLNode->Data = 9, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 4, NodeNum = 4
>
>  
>
> -------Test 05----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 9, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 5, NodeNum = 5
>
>  
>
> -------Test 06----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 9, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = -1
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test 07----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 9, AVLNode->BF = 1
>
> AVLNode->Data = 5, AVLNode->BF = 1
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = -1
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 7, NodeNum = 7
>
>  
>
> -------Test 08----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 9, AVLNode->BF = 1
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = -1
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 8, NodeNum = 8
>
>  
>
> -------Test 09----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 9, AVLNode->BF = -1
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = -1
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 9, NodeNum = 9
>
>  
>
> -------Test 10----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 9, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = -1
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 10, NodeNum = 10
>
>  
>
> -------Test 11----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 9, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 1
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = -1
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = -1
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 11, NodeNum = 11
>
>  
>
> -------Test 12----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 9, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 1
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = -1
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 12, NodeNum = 12
>
>  
>
> -------Test 13----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 9, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 1
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 12, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 13, NodeNum = 13
>
>  
>
> -------Test 14----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 9, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = -1
>
> AVLNode->Data = 7, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 12, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 14, NodeNum = 14
>
>  
>
> -------Test 15----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 9, AVLNode->BF = -1
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = -1
>
> AVLNode->Data = 7, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = -1
>
> AVLNode->Data = 12, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = -1
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 15, NodeNum = 15
>
>  
>
> -------Test 16----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 9, AVLNode->BF = -1
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = -1
>
> AVLNode->Data = 7, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = -1
>
> AVLNode->Data = 12, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 16, NodeNum = 16
>
>  
>
> -------Test 17----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 9, AVLNode->BF = -1
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = -1
>
> AVLNode->Data = 7, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = -1
>
> AVLNode->Data = 12, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 53, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = -1
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 17, NodeNum = 17
>
>  
>
> -------Test 18----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 9, AVLNode->BF = -1
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 1, AVLNode->BF = 0
>
> AVLNode->Data = 4, AVLNode->BF = 0
>
> AVLNode->Data = 6, AVLNode->BF = -1
>
> AVLNode->Data = 7, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 12, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 53, AVLNode->BF = -1
>
> AVLNode->Data = 54, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = -1
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 18, NodeNum = 18
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 18, PassNum = 18, FaildNum = 0



>
