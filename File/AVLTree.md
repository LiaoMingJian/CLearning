# 平衡二叉树——创建，增加结点，删除结结点——C语言描述

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
	struct _AVL_TREE_NODE *LeftChild;
	struct _AVL_TREE_NODE *RightChild;
}AVL_TREE_NODE;
```



# 2 增加平衡二叉树的结点

​    设置Taller标志，增加结点后，Taller为true，当高度一致时或者左右平衡处理后，Taller为false。

​	结点BF值的判断，当结点左右子树增加结点时，BF进行相应的变化，当BF的绝对值大于1值，进行左右平衡处理。（具体可以看测试用例的示意图）

​    **左平衡有四种情况**：

①  结点左子树左高，结点做右旋操作；

②  结点左子树右高且该结点左子树的右子树等高，结点左孩子做左旋操作，结点做右旋操作；

③  结点左子树右高且该结点左子树的右子树左高，结点左孩子做左旋操作，结点做右旋操作；

④  结点左子树右高且该结点左子树的右子树右高，结点左孩子做左旋操作，结点做右旋操作；

 

**右平衡有四种情况**：

⑤  结点右子树右高，结点做左旋操作；

⑥  结点右子树左高且该结点右子树的左子树等高，结点右孩子做右旋操作，结点做左旋操作；

⑦  结点右子树左高且该结点右子树的左子树左高，结点左孩子做右旋操作，结点做左旋操作；

⑧  结点右子树左高且该结点右子树的左子树右高，结点左孩子做右旋操作，结点做左旋操作；

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
	if ((AVLNode == NULL) || (Taller == NULL)) {
		return false;
	}

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



## （3）**打印结果**

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





# 3  构建平衡二叉树

​    直接调用增加结点的函数。

## （1）**代码：**

```c
/*BuildAVLTree*/
void BuildAVLTree(AVL_TREE_NODE **AVLNode, int *Arr, int Num) {
	int Index = 0;
	bool Taller = false;

	if ((AVLNode == NULL) || (Arr == NULL)) {
		return;
	}

	for (Index = 0; Index < Num; Index++) {
		AddAVLNode(AVLNode, Arr[Index], &Taller);
	}
}
```



## （2）**测试用例：**

```c
/*TestBuildAVLTree*/
void TestBuildAVLTree(void) {
	/*Test01*/
	//         50
	AVL_TREE_NODE *AVLNode01 = NULL;
	int Arr01[] = { 50 };
	int Num01 = 1;
	int CmpAVLNode01[] = { 50 };

	/*Test02*/
	//  LeftBalance_LH
	//         50
	//      30
	//   20
	//  50_RightRotate
	//		   30
	//      20    50
	AVL_TREE_NODE *AVLNode02 = NULL;
	int Arr02[] = { 50, 30, 20 };
	int Num02 = 3;
	int CmpAVLNode02[] = { 30, 20, 50 };

	/*Test03*/
	//  LeftBalance_RH_EH
	//         50
	//     30
	//       40
	//  30_LeftRotate
	//		   50
	//      40
	//   30
	//  50_RightRotate
	//         40
	//      30    50
	AVL_TREE_NODE *AVLNode03 = NULL;
	int Arr03[] = { 50, 30, 40 };
	int Num03 = 3;
	int CmpAVLNode03[] = { 40, 30, 50 };

	/*Test04*/
	//  LeftBalance_RH_LH
	//             50
	//     30            60
	//  20    40
	//      35
	//  30_LeftRotate
	//		      50
	//      40           60
	//   30
	// 20  35
	//  50_RightRotate
	//            40
	//      30         50
	//    20  35         60
	AVL_TREE_NODE *AVLNode04 = NULL;
	int Arr04[] = { 50, 30, 20, 40, 35, 60 };
	int Num04 = 6;
	int CmpAVLNode04[] = { 40, 30, 20, 35, 50, 60 };

	/*Test05*/
	//  LeftBalance_RH_RH
	//             50
	//     30            60
	//  20    40
	//          45
	//  30_LeftRotate
	//		      50
	//      40           60
	//   30   45
	// 20
	//  50_RightRotate
	//            40
	//      30         50
	//    20        45    60
	AVL_TREE_NODE *AVLNode05 = NULL;
	int Arr05[] = { 50, 30, 60, 20, 40, 45 };
	int Num05 = 6;
	int CmpAVLNode05[] = { 40, 30, 20, 50, 45, 60 };

	/*Test06*/
	//  RightBalance_RH
	//         50
	//             60
	//                70
	//  50_LeftRotate
	//		   60
	//      50    70
	AVL_TREE_NODE *AVLNode06 = NULL;
	int Arr06[] = { 50, 60, 70 };
	int Num06 = 3;
	int CmpAVLNode06[] = { 60, 50, 70 };

	/*Test07*/
	//  RightBalance_LH_EH
	//         50
	//             60
	//           55
	//  60_RightRotate
	//		   50
	//             55
	//                60
	//  50_LeftRotate
	//		   55
	//      50    60
	AVL_TREE_NODE *AVLNode07 = NULL;
	int Arr07[] = { 50, 60, 55 };
	int Num07 = 3;
	int CmpAVLNode07[] = { 55, 50, 60 };

	/*Test08*/
	//  RightBalance_LH_LH
	//         50
	//    30         70
	//            60    80
	//           55
	//  70_RightRotate
	//		   50
	//    30         60
	//             55  70
	//                   80
	//  50_LeftRotate
	//		   60
	//    50         70
	//  30  55          80
	AVL_TREE_NODE *AVLNode08 = NULL;
	int Arr08[] = { 50, 30, 70, 60, 55, 80 };
	int Num08 = 6;
	int CmpAVLNode08[] = { 60, 50, 30, 55, 70, 80 };

	/*Test09*/
	//  RightBalance_LH_RH
	//         50
	//    30         70
	//            60    80
	//             65
	//  70_RightRotate
	//		   50
	//    30         60
	//                  70
	//                65  80
	//  50_LeftRotate
	//		   60
	//    50         70
	//  30         65  80
	AVL_TREE_NODE *AVLNode09 = NULL;
	int Arr09[] = { 50, 30, 70, 60, 80, 65 };
	int Num09 = 6;
	int CmpAVLNode09[] = { 60, 50, 30, 70, 65, 80 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildAVLTree(&AVLNode01, Arr01, Num01);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode01);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode01, AVLNode01, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildAVLTree(&AVLNode02, Arr02, Num02);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode02);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode02, AVLNode02, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	BuildAVLTree(&AVLNode03, Arr03, Num03);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode03);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode03, AVLNode03, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	BuildAVLTree(&AVLNode04, Arr04, Num04);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode04);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode04, AVLNode04, Num04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	BuildAVLTree(&AVLNode05, Arr05, Num05);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode05);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode05, AVLNode05, Num05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	BuildAVLTree(&AVLNode06, Arr06, Num06);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode06);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode06, AVLNode06, Num06);

	/*Test07*/
	printf("\n-------Test 07----------\n");
	BuildAVLTree(&AVLNode07, Arr07, Num07);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode07);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode07, AVLNode07, Num07);

	/*Test08*/
	printf("\n-------Test 08----------\n");
	BuildAVLTree(&AVLNode08, Arr08, Num08);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode08);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode08, AVLNode08, Num08);

	/*Test09*/
	printf("\n-------Test 09----------\n");
	BuildAVLTree(&AVLNode09, Arr09, Num09);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode09);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode09, AVLNode09, Num09);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



## （3）**结果：**

> -------Test start----------
>
>  
>
> -------Test 01----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 0
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
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 03----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
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
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 35, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test 05----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 45, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test 06----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 07----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 08----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test 09----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 65, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 9, PassNum = 9, FaildNum = 0



# 4  删除平衡二叉树结点

​    设置Shorter标志，增加结点后，Taller为true，当高度一致时或者左右平衡处理后，Taller为false。

结点BF值的判断，当结点左右子树减少结点时，BF进行相应的变化，当BF的绝对值大于1值，进行左右平衡处理。（具体可以看测试用例的示意图）

注意:

①  Shorter与增加结点不一样，当结点BF时，它孩子结点被删除是，Shorter 为false.而因删除结点引起的左右平衡操作后，Shorter是为true;

②  将循环的删除操作改成了递归的形式。



## （1）代码

```c
/*DelAVLNode*/
void DelTwoChildNode(AVL_TREE_NODE **AVLNode, AVL_TREE_NODE **Tmp01, AVL_TREE_NODE **Tmp02, bool *Shorter) {
	AVL_TREE_NODE *Tmp03 = NULL;
	if ((*Tmp02)->RightChild == NULL) {
		//printf("(*AVLNode)->Data = %d\n", (*AVLNode)->Data);
		//printf("*Tmp01 = 0x%lx, (*Tmp01)->Data = %d, (*Tmp01)->BF = %d, (*Tmp01)->LeftChild = 0x%lx, (*Tmp01)->RightChild = 0x%lx\n", *Tmp01, (*Tmp01)->Data, (*Tmp01)->BF, (*Tmp01)->LeftChild, (*Tmp01)->RightChild);
		//printf("*Tmp02 = 0x%lx, (*Tmp02)->Data = %d, (*Tmp02)->BF = %d, (*Tmp02)->LeftChild = 0x%lx, (*Tmp02)->RightChild = 0x%lx\n", *Tmp02, (*Tmp02)->Data, (*Tmp02)->BF, (*Tmp02)->LeftChild, (*Tmp02)->RightChild);

		(*AVLNode)->Data = (*Tmp02)->Data;
		if (*Tmp01 != *AVLNode) {
			Tmp03 = *Tmp02;
			(*Tmp01)->RightChild = (*Tmp02)->LeftChild;
		} else {
			Tmp03 = *Tmp02;
			(*Tmp01)->LeftChild = (*Tmp02)->LeftChild;
		}

		free(Tmp03);
		Tmp03 = NULL;

		*Shorter = true;
	} else if ((*Tmp02)->RightChild != NULL) {
		DelTwoChildNode(AVLNode, Tmp02, &((*Tmp02)->RightChild), Shorter);
	}

	if (*Tmp01 != *AVLNode) {
		if (*Shorter) {
			switch ((*Tmp01)->BF) {
				case EH:
					(*Tmp01)->BF = LH;
					*Shorter = false;
					break;
				case LH:
					LeftBalance(Tmp01);
					*Shorter = true;
					break;
				case RH:
					(*Tmp01)->BF = EH;
					*Shorter = true;
					break;
				}
		}
	} else {
		if (*Shorter) {
			switch ((*Tmp01)->BF) {
				case EH:
					(*Tmp01)->BF = RH;
					*Shorter = false;
					break;
				case LH:
					(*Tmp01)->BF = EH;
					*Shorter = true;
					break;
				case RH:
					RightBalance(Tmp01);
					*Shorter = true;
					break;
			}
		}
	}
}

void DelAVLNode(AVL_TREE_NODE **AVLNode, bool *Shorter) {
	AVL_TREE_NODE *Tmp01 = NULL;
	AVL_TREE_NODE *Tmp02 = NULL;

	if ((*AVLNode)->LeftChild == NULL) {
		Tmp01 = *AVLNode;
		*AVLNode = (*AVLNode)->RightChild;

		free(Tmp01);
		Tmp01 = NULL;
		*Shorter = true;
	} else if ((*AVLNode)->RightChild == NULL) {
		Tmp01 = *AVLNode;
		*AVLNode = (*AVLNode)->LeftChild;

		free(Tmp01);
		Tmp01 = NULL;
		*Shorter = true;
	} else {
		//printf("(*AVLNode) = 0x%lx, (*AVLNode)->Data = %d, (*AVLNode)->BF = %d, (*AVLNode)->LeftChild = 0x%lx, (*AVLNode)->RightChild) = 0x%lx\n", (*AVLNode), (*AVLNode)->Data, (*AVLNode)->BF, (*AVLNode)->LeftChild, (*AVLNode)->RightChild);
		DelTwoChildNode(AVLNode, AVLNode, &((*AVLNode)->LeftChild), Shorter);
	}
}

/*DelAVLNode*/
bool DeleteAVLNode(AVL_TREE_NODE **AVLNode, int Key, bool *Shorter) {
	if ((AVLNode == NULL) || (Shorter == NULL)) {
		return false;
	}

	if (*AVLNode == NULL) {
		return false;
	}

	if (Key < (*AVLNode)->Data) {
		if (!DeleteAVLNode(&((*AVLNode)->LeftChild), Key, Shorter)) {
			return false;
		}

		if (*Shorter) {
			switch ((*AVLNode)->BF) {
				case EH:
					(*AVLNode)->BF = RH;
					*Shorter = false;
					break;
				case LH:
					(*AVLNode)->BF = EH;
					*Shorter = true;
					break;
				case RH:
					RightBalance(AVLNode);
					*Shorter = true;
					break;
			}
		}
	} else if (Key > (*AVLNode)->Data) {
		if (!DeleteAVLNode(&((*AVLNode)->RightChild), Key, Shorter)) {
			return false;
		}

		if (*Shorter) {
			switch ((*AVLNode)->BF) {
				case EH:
					(*AVLNode)->BF = LH;
					*Shorter = false;
					break;
				case LH:
					LeftBalance(AVLNode);
					*Shorter = true;
					break;
				case RH:
					(*AVLNode)->BF = EH;
					*Shorter = true;
					break;
				}
		}
	} else {
		DelAVLNode(AVLNode, Shorter);
	}
    
  	return true;
}
```



## (2)**测试用例：**

```c
/*TestDeleteAVLNode*/
void TestDeleteAVLNode(void) {
	/*Test01*/
	// Only_Del
	//         50
	//      30     70
	// 30_Del
	//         50
	//             70
	AVL_TREE_NODE *AVLNode01 = NULL;
	int Arr01[] = { 50, 30, 70 };
	int Num01 = 3;
	//int CmpAVLNode01[] = { 50, 30, 70 };
	int Key01 = 30;
	bool Shorter01 = false;
	int CmpNum01 = 2;
	int CmpAVLNode01[] = { 50, 70 };

	/*Test02*/
	// Only_Del
	//         50
	//      30     70
	// 70_Del
	//         50
	//      30
	AVL_TREE_NODE *AVLNode02 = NULL;
	int Arr02[] = { 50, 30, 70 };
	int Num02 = 3;
	//int CmpAVLNode02[] = { 50, 30, 70 };
	int Key02 = 70;
	bool Shorter02 = false;
	int CmpNum02 = 2;
	int CmpAVLNode02[] = { 50, 30 };

	/*Test03*/
	// Only_Del
	//         50
	//      30     70
	// 50_Del
	//         30
	//             70
	AVL_TREE_NODE *AVLNode03 = NULL;
	int Arr03[] = { 50, 30, 70 };
	int Num03 = 3;
	//int CmpAVLNode03[] = { 50, 30, 70 };
	int Key03 = 50;
	bool Shorter03 = false;
	int CmpNum03 = 2;
	int CmpAVLNode03[] = { 30, 70 };

	/*Test04*/
	// Leaf_leftbalance_LH
	//         50
	//      30     70
	//    20
	// 70_Del
	//         50
	//      30
	//    20
	// 50_RightRotate
	//         30
	//      20    50
	AVL_TREE_NODE *AVLNode04 = NULL;
	int Arr04[] = { 50, 30, 70, 20 };
	int Num04 = 4;
	//int CmpAVLNode04[] = { 50, 30, 20, 70};
	int Key04 = 70;
	bool Shorter04 = false;
	int CmpNum04 = 3;
	int CmpAVLNode04[] = { 30, 20, 50 };

	/*Test05*/
	// Leaf_Leftbalance_RH_EH
	//         50
	//      30     70
	//       40
	// 70_Del
	//         50
	//      30
	//       40
	// 30_LeftRotate
	//         50
	//      40
	//    30
	// 50_RightRotate
	//         40
	//      30    50
	AVL_TREE_NODE *AVLNode05 = NULL;
	int Arr05[] = { 50, 30, 70, 40 };
	int Num05 = 4;
	//int CmpAVLNode05[] = { 50, 30, 40, 70};
	int Key05 = 70;
	bool Shorter05 = false;
	int CmpNum05 = 3;
	int CmpAVLNode05[] = { 40, 30, 50 };

	/*Test06*/
	// Leaf_Leftbalance_RH_LH
	//         50
	//      30     70
	//    20  40     80
	//       35
	// 70_Del
	//         50
	//      30     80
	//    20  40
	//       35
	// 30_LeftRotate
	//         50
	//      40   80
	//    30
	//  20 35
	// 50_RightRotate
	//         40
	//      30    50
	//    20 35    80
	AVL_TREE_NODE *AVLNode06 = NULL;
	int Arr06[] = { 50, 30, 70, 20, 40, 80, 35 };
	int Num06 = 7;
	//int CmpAVLNode06[] = { 50, 30, 20, 40, 35, 70, 80};
	int Key06 = 70;
	bool Shorter06 = false;
	int CmpNum06 = 6;
	int CmpAVLNode06[] = { 40, 30, 20, 35, 50, 80 };

	/*Test07*/
	// Leaf_Leftbalance_RH_RH
	//         50
	//      30     70
	//    20  40     80
	//         45
	// 70_Del
	//         50
	//      30     80
	//    20  40
	//         45
	// 30_LeftRotate
	//         50
	//      40   80
	//    30 45
	//  20 
	// 50_RightRotate
	//         40
	//      30    50
	//    20    45  80
	AVL_TREE_NODE *AVLNode07 = NULL;
	int Arr07[] = { 50, 30, 70, 20, 40, 80, 45 };
	int Num07 = 7;
	//int CmpAVLNode07[] = { 50, 30, 20, 40, 45, 70, 80};
	int Key07 = 70;
	bool Shorter07 = false;
	int CmpNum07 = 6;
	int CmpAVLNode07[] = { 40, 30, 20, 50, 45, 80 };


	/*Test08*/
	// Leaf_leftbalance_RH
	//         50
	//      30     70
	//               80
	// 30_Del
	//         50
	//             70
	//               80
	// 50_LeftRotate
	//         70
	//      50    80
	AVL_TREE_NODE *AVLNode08 = NULL;
	int Arr08[] = { 50, 30, 70, 80 };
	int Num08 = 4;
	//int CmpAVLNode08[] = { 50, 30, 70, 80};
	int Key08 = 30;
	bool Shorter08 = false;
	int CmpNum08 = 3;
	int CmpAVLNode08[] = { 70, 50, 80 };

	/*Test09*/
	// Leaf_leftbalance_LH_EH
	//         50
	//      30     70
	//            60
	// 30_Del
	//         50
	//             70
	//            60
	// 70_RightRotate
	//         50
	//            60
	 //              70
	// 50_LeftRotate
	//         60
	//      50    70
	AVL_TREE_NODE *AVLNode09 = NULL;
	int Arr09[] = { 50, 30, 70, 60 };
	int Num09 = 4;
	//int CmpAVLNode09[] = { 50, 30, 70, 60};
	//int CmpNum09 = 4;
	int Key09 = 30;
	bool Shorter09 = false;
	int CmpNum09 = 3;
	int CmpAVLNode09[] = { 60, 50, 70 };


	/*Test10*/
	// Leaf_leftbalance_LH_LH
	//         50
	//      30     70
	//    20     60  80
	//          55
	// 30_Del
	//         50
	//      20     70
	//           60  80
	//          55
	// 70_RightRotate
	//         50
	//      20     60
	//           55  70
	//                80
	// 50_LeftRotate
	//         60
	//      50     70
	//    20  55     80
	AVL_TREE_NODE *AVLNode10 = NULL;
	int Arr10[] = { 50, 30, 70, 20, 60, 80, 55 };
	int Num10 = 7;
	// int CmpAVLNode10[] = { 50, 30, 20, 70, 60, 55, 80};
	// int CmpNum10 = 7;
	int Key10 = 30;
	bool Shorter10 = false;
	int CmpNum10 = 6;
	int CmpAVLNode10[] = { 60, 50, 20, 55, 70, 80 };

	/*Test11*/
	// Leaf_leftbalance_LH_RH
	//         50
	//      30     70
	//    20     60  80
	//            65
	// 30_Del
	//         50
	//      20     70
	//           60  80
	//            65
	// 70_RightRotate
	//         50
	//      20     60
	//               70
	//              65 80
	// 50_LeftRotate
	//         60
	//      50     70
	//    20     65  80
	AVL_TREE_NODE *AVLNode11 = NULL;
	int Arr11[] = { 50, 30, 70, 20, 60, 80, 65 };
	int Num11 = 7;
	// int CmpAVLNode11[] = { 50, 30, 20, 70, 60, 65, 80};
	// int CmpNum11 = 7;
	int Key11 = 30;
	bool Shorter11 = false;
	int CmpNum11 = 6;
	int CmpAVLNode11[] = { 60, 50, 20, 70, 65, 80 };


	/*Test12*/
	// OnlyDel_NoRotate
	//             50
	//       30          70
	//    20    40     60  80
	//  10     35
	// 50_del
	//             40
	//       30          70
	//    20    35     60  80 
	//  10
	AVL_TREE_NODE *AVLNode12 = NULL;
	int Arr12[] = { 50, 30, 70, 20, 40, 60, 80, 10, 35 };
	int Num12 = 9;
	//int CmpAVLNode12[] = { 50, 30, 20, 10, 40, 35, 70, 60, 80 };
	//int CmpNum12 = 9;
	int Key12 = 50;
	bool Shorter12 = false;
	int CmpNum12 = 8;
	int CmpAVLNode12[] = { 40, 30, 20, 10, 35, 70, 60, 80 };

	/*Test13*/
	// OnlyDel_NoRotate
	//                            50
	//            30                            70
	//     20              40               60       80
	//  10   25         35    45          55  65   75  90
	// 5 15           33 37  43                         100
	//              31
	// 50_del
	//                            45
	//            30                            70
	//     20              40               60       80
	//  10   25         35    43          55  65   75  90
	// 5 15           33 37                           100
	//              31
	// 40_RightRotate
	//                            45
	//            30                            70
	//     20              35               60       80
	//  10   25         33    40          55  65   75  90
	// 5 15           31    37  43                      100
	AVL_TREE_NODE *AVLNode13 = NULL;
	int Arr13[] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 90, 5, 15, 33, 37, 43, 100, 31 };
	int Num13 = 22;
	//int CmpAVLNode13[] = { 50, 30, 20, 10, 5, 15, 25, 40, 35, 33, 31, 37, 45, 43, 70, 60, 55, 65, 80, 75, 90, 100 };
	//int CmpNum13 = 22;
	int Key13 = 50;
	bool Shorter13 = false;
	int CmpNum13 = 21;
	int CmpAVLNode13[] = { 45, 30, 20, 10, 5, 15, 25, 35, 33, 31, 40, 37, 43, 70, 60, 55, 65, 80, 75, 90, 100 };

	/*Test14*/
	// Root_Tmp01_EH_RootRightbalance_RH
	//          50
	//    20          70
	//      30     60   80
	//                   90
	// 50_Del
	//          30
	//    20          70
	//             60   80
	//                   90
	// 30_LeftRotate
	//          70
	//    30          80
	//   20 60         90
	AVL_TREE_NODE *AVLNode14 = NULL;
	int Arr14[] = { 50, 20, 70, 30, 60, 80, 90 };
	int Num14 = 7;
	// int CmpAVLNode14[] = { 50, 20, 30, 70, 60, 80, 90 };
	// int CmpNum14 = 7;
	int Key14 = 50;
	bool Shorter14 = false;
	int CmpNum14 = 6;
	int CmpAVLNode14[] = { 70, 30, 20, 60, 80, 90 };


	/*Test15*/
	// Root_Tmp01Leftbalance_LH_RootRightbalance_RH
	//          50
	//    20          70
	//  10   30     60   80
	// 5           55   75  90
	//                       100
	// 50_Del
	//          30
	//    20          70
	//  10         60   80
	// 5           55  75  90
	//                      100
	// 20_RightRotate
	//          30
	//    10          70
	//  5   20      60   80
	//             55  75  90
	//                      100
	// 30_LeftRotate
	//          70
	//    30          80
	//  10   60     75  90
	// 5 20 55           100
	AVL_TREE_NODE *AVLNode15 = NULL;
	int Arr15[] = { 50, 20, 70, 10, 30, 60, 80, 5, 55, 75, 90, 100 };
	int Num15 = 12;
	// int CmpAVLNode15[] = { 50, 20, 10, 5, 30, 70, 60, 55, 80, 75, 90, 100 };
	// int CmpNum15 = 12;
	int Key15 = 50;
	bool Shorter15 = false;
	int CmpNum15 = 11;
	int CmpAVLNode15[] = { 70, 30, 10, 5, 20, 60, 55, 80, 75, 90, 100 };


	/*Test16*/
	// Root_Tmp01Leftbalance_RH_RootRightbalance_RH
	//          50
	//    20          70
	//  10   30     60   80
	//   15       55   75  90
	//                       100
	// 50_Del
	//          30
	//    20          70
	//  10         60   80
	//   15       55  75  90
	//                      100
	// 10_LeftRotate
	//          30
	//    20          70
	//  15         60   80
	// 10         55  75  90
	//                      100
	// 20_RightRotate
	//          30
	//    15          70
	//  10  20      60   80
	//            55  75  90
	//                      100
	// 30_LeftRotate
	//          70
	//    30          80
	//  15   60     75  90
	//10 20 55           100
	AVL_TREE_NODE *AVLNode16 = NULL;
	int Arr16[] = { 50, 20, 70, 10, 30, 60, 80, 15, 55, 75, 90, 100 };
	int Num16 = 12;
	// int CmpAVLNode16[] = { 50, 20, 10, 15, 30, 70, 60, 55, 80, 75, 90, 100 };
	// int CmpNum16 = 12;
	int Key16 = 50;
	bool Shorter16 = false;
	int CmpNum16 = 11;
	int CmpAVLNode16[] = { 70, 30, 15, 10, 20, 60, 55, 80, 75, 90, 100 };

	/*Test17*/
	// Root_Tmp01Leftbalance_LH_RootRightbalance_RH
	//            50
	//      20            70
	//    10   30     60        80
	//   5 15 25    55 67    75     90
	//  3          53   68  73    85  100
	//                                  110
	// 50_Del
	//            30
	//      20            70
	//    10   25     60        80
	//   5 15       55 67    75     90
	//  3          53   68  73    85  100
	//                                  110
	// 20_RightRotate
	//            30
	//      10            70
	//    5    20     60       80
	//   3   15 25  55 67    75    90
	//             53   68  73    85  100
	//                                  110
	// 30_LeftRotate
	//                     70
	//          30                    80
	//    10         60           75      90
	//  5   20     55  67        73     85  100
	// 3   15 25  53    68                   110
	AVL_TREE_NODE *AVLNode17 = NULL;
	int Arr17[] = { 50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 55, 67, 75, 90, 3, 53, 68, 73, 85, 100, 110 };
	int Num17 = 21;
	// int CmpAVLNode15[] = { 50, 20, 10, 5, 3, 15, 30, 25, 70, 60, 55, 53, 67, 68, 80, 75, 73, 90, 85, 100, 110 };
	// int CmpNum15 = 21;
	int Key17 = 50;
	bool Shorter17 = false;
	int CmpNum17 = 20;
	int CmpAVLNode17[] = { 70, 30, 10, 5, 3, 20, 15, 25, 60, 55, 53, 67, 68, 80, 75, 73, 90, 85, 100, 110 };


	/*Test18*/
	// Leftbalance_RH_RootRightbalance_RH
	//          50
	//    20          70
	//  10   30     60   80
	// 5          55   75  90
	//                       100
	// 30_Del
	//          50
	//    20          70
	//  10          60   80
	// 5          55   75  90
	//                       100
	// 20_RightRotate
	//          50
	//    10          70
	//  5   20      60   80
	//            55   75  90
	//                       100
	// 50_LeftRotate
	//            70
	//      50          80
	//   10    60     75   90
	//  5 20  55             100
	AVL_TREE_NODE *AVLNode18 = NULL;
	int Arr18[] = { 50, 20, 70, 10, 30, 60, 80, 5, 55, 75, 90, 100 };
	int Num18 = 12;
	// int CmpAVLNode18[] = { 50, 20, 10, 5, 30, 70, 60, 55, 80, 75, 90, 100 };
	// int CmpNum18 = 12;
	int Key18 = 30;
	bool Shorter18 = false;
	int CmpNum18 = 11;
	int CmpAVLNode18[] = { 70, 50, 10, 5, 20, 60, 55, 80, 75, 90, 100 };


	/*Test19*/
	// No_Rotate
	//          50
	//    20          70
	//  10   30
	// 30_Del
	//          50
	//    20          70
	//  10
	AVL_TREE_NODE *AVLNode19 = NULL;
	int Arr19[] = { 50, 20, 70, 10, 30 };
	int Num19 = 5;
	// int CmpAVLNode19[] = { 50, 20, 10, 30, 70 };
	// int CmpNum19 = 5;
	int Key19 = 30;
	bool Shorter19 = false;
	int CmpNum19 = 4;
	int CmpAVLNode19[] = { 50, 20, 10, 70 };


	printf("-------Test start----------\n");
	InitNum();

	 /*Test01*/
	 printf("\n-------Test 01----------\n");
	 BuildAVLTree(&AVLNode01, Arr01, Num01);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode01);
	 DeleteAVLNode(&AVLNode01, Key01, &Shorter01);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode01);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode01, AVLNode01, CmpNum01);

	 /*Test02*/
	 printf("\n-------Test 02----------\n");
	 BuildAVLTree(&AVLNode02, Arr02, Num02);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode02);
	 DeleteAVLNode(&AVLNode02, Key02, &Shorter02);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode02);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode02, AVLNode02, CmpNum02);

	 /*Test03*/
	 printf("\n-------Test 03----------\n");
	 BuildAVLTree(&AVLNode03, Arr03, Num03);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode03);
	 DeleteAVLNode(&AVLNode03, Key03, &Shorter03);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode03);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode03, AVLNode03, CmpNum03);

	 /*Test04*/
	 printf("\n-------Test 04----------\n");
	 BuildAVLTree(&AVLNode04, Arr04, Num04);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode04);
	 DeleteAVLNode(&AVLNode04, Key04, &Shorter04);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode04);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode04, AVLNode04, CmpNum04);

	 /*Test05*/
	 printf("\n-------Test 05----------\n");
	 BuildAVLTree(&AVLNode05, Arr05, Num05);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode05);
	 DeleteAVLNode(&AVLNode05, Key05, &Shorter05);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode05);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode05, AVLNode05, CmpNum05);

	 /*Test06*/
	 printf("\n-------Test 06----------\n");
	 BuildAVLTree(&AVLNode06, Arr06, Num06);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode06);
	 DeleteAVLNode(&AVLNode06, Key06, &Shorter06);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode06);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode06, AVLNode06, CmpNum06);

	 /*Test07*/
	 printf("\n-------Test 07----------\n");
	 BuildAVLTree(&AVLNode07, Arr07, Num07);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode07);
	 DeleteAVLNode(&AVLNode07, Key07, &Shorter07);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode07);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode07, AVLNode07, CmpNum07);

	 /*Test08*/
	 printf("\n-------Test 08----------\n");
	 BuildAVLTree(&AVLNode08, Arr08, Num08);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode08);
	 DeleteAVLNode(&AVLNode08, Key08, &Shorter08);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode08);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode08, AVLNode08, CmpNum08);

	 /*Test09*/
	 printf("\n-------Test 09----------\n");
	 BuildAVLTree(&AVLNode09, Arr09, Num09);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode09);
	 DeleteAVLNode(&AVLNode09, Key09, &Shorter09);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode09);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode09, AVLNode09, CmpNum09);

	 /*Test10*/
	 printf("\n-------Test 10----------\n");
	 BuildAVLTree(&AVLNode10, Arr10, Num10);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode10);
	 DeleteAVLNode(&AVLNode10, Key10, &Shorter10);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode10);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode10, AVLNode10, CmpNum10);

	 /*Test11*/
	 printf("\n-------Test 11----------\n");
	 BuildAVLTree(&AVLNode11, Arr11, Num11);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode11);
	 DeleteAVLNode(&AVLNode11, Key11, &Shorter11);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode11);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode11, AVLNode11, CmpNum11);

	/*Test12*/
	printf("\n-------Test 12----------\n");
	BuildAVLTree(&AVLNode12, Arr12, Num12);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode12);
	DeleteAVLNode(&AVLNode12, Key12, &Shorter12);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode12);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode12, AVLNode12, CmpNum12);

	/*Test13*/
	printf("\n-------Test 13----------\n");
	BuildAVLTree(&AVLNode13, Arr13, Num13);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode13);
	DeleteAVLNode(&AVLNode13, Key13, &Shorter13);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode13);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode13, AVLNode13, CmpNum13);

	/*Test14*/
	printf("\n-------Test 14----------\n");
	BuildAVLTree(&AVLNode14, Arr14, Num14);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode14);
	DeleteAVLNode(&AVLNode14, Key14, &Shorter14);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode14);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode14, AVLNode14, CmpNum14);

	/*Test15*/
	printf("\n-------Test 15----------\n");
	BuildAVLTree(&AVLNode15, Arr15, Num15);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode15);
	DeleteAVLNode(&AVLNode15, Key15, &Shorter15);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode15);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode15, AVLNode15, CmpNum15);

	/*Test16*/
	printf("\n-------Test 16----------\n");
	BuildAVLTree(&AVLNode16, Arr16, Num16);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode16);
	DeleteAVLNode(&AVLNode16, Key16, &Shorter16);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode16);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode16, AVLNode16, CmpNum16);

	/*Test17*/
	printf("\n-------Test 17----------\n");
	BuildAVLTree(&AVLNode17, Arr17, Num17);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode17);
	DeleteAVLNode(&AVLNode17, Key17, &Shorter17);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode17);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode17, AVLNode17, CmpNum17);

	/*Test18*/
	printf("\n-------Test 18----------\n");
	BuildAVLTree(&AVLNode18, Arr18, Num18);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode18);
	DeleteAVLNode(&AVLNode18, Key18, &Shorter18);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode18);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode18, AVLNode18, CmpNum18);

	/*Test19*/
	printf("\n-------Test 19----------\n");
	BuildAVLTree(&AVLNode19, Arr19, Num19);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode19);
	DeleteAVLNode(&AVLNode19, Key19, &Shorter19);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode19);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode19, AVLNode19, CmpNum19);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

## （3）结果

> -------Test start----------
>
>  
>
> -------Test 01----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 2, NodeNum = 2
>
>  
>
> -------Test 02----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = 0
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
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 30, AVLNode->BF = -1
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 2, NodeNum = 2
>
>  
>
> -------Test 04----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 05----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = -1
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 06----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = -1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 1
>
> AVLNode->Data = 35, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 35, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 80, AVLNode->BF = 0
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
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = -1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = -1
>
> AVLNode->Data = 45, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 45, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test 08----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 09----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 1
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 3, NodeNum = 3
>
>  
>
> -------Test 10----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 1
>
> AVLNode->Data = 60, AVLNode->BF = 1
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test 11----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 1
>
> AVLNode->Data = 60, AVLNode->BF = -1
>
> AVLNode->Data = 65, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 65, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test 12----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 1
>
> AVLNode->Data = 35, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 40, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 35, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 8, NodeNum = 8
>
>  
>
> -------Test 13----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 30, AVLNode->BF = -1
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 25, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 1
>
> AVLNode->Data = 35, AVLNode->BF = 1
>
> AVLNode->Data = 33, AVLNode->BF = 1
>
> AVLNode->Data = 31, AVLNode->BF = 0
>
> AVLNode->Data = 37, AVLNode->BF = 0
>
> AVLNode->Data = 45, AVLNode->BF = 1
>
> AVLNode->Data = 43, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 65, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 100, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 45, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 25, AVLNode->BF = 0
>
> AVLNode->Data = 35, AVLNode->BF = 0
>
> AVLNode->Data = 33, AVLNode->BF = 1
>
> AVLNode->Data = 31, AVLNode->BF = 0
>
> AVLNode->Data = 40, AVLNode->BF = 0
>
> AVLNode->Data = 37, AVLNode->BF = 0
>
> AVLNode->Data = 43, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 65, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 100, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 21, NodeNum = 21
>
>  
>
> -------Test 14----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 20, AVLNode->BF = -1
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 90, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 90, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 6, NodeNum = 6
>
>  
>
> -------Test 15----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 1
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 60, AVLNode->BF = 1
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 100, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 1
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 100, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 11, NodeNum = 11
>
>  
>
> -------Test 16----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = -1
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 60, AVLNode->BF = 1
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 100, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 1
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 100, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 11, NodeNum = 11
>
>  
>
> -------Test 17----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 1
>
> AVLNode->Data = 5, AVLNode->BF = 1
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 1
>
> AVLNode->Data = 25, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 1
>
> AVLNode->Data = 53, AVLNode->BF = 0
>
> AVLNode->Data = 67, AVLNode->BF = -1
>
> AVLNode->Data = 68, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 1
>
> AVLNode->Data = 73, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 85, AVLNode->BF = 0
>
> AVLNode->Data = 100, AVLNode->BF = -1
>
> AVLNode->Data = 110, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 1
>
> AVLNode->Data = 3, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 15, AVLNode->BF = 0
>
> AVLNode->Data = 25, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 0
>
> AVLNode->Data = 55, AVLNode->BF = 1
>
> AVLNode->Data = 53, AVLNode->BF = 0
>
> AVLNode->Data = 67, AVLNode->BF = -1
>
> AVLNode->Data = 68, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 1
>
> AVLNode->Data = 73, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 85, AVLNode->BF = 0
>
> AVLNode->Data = 100, AVLNode->BF = -1
>
> AVLNode->Data = 110, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 20, NodeNum = 20
>
>  
>
> -------Test 18----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = -1
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 1
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = -1
>
> AVLNode->Data = 60, AVLNode->BF = 1
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 100, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> AVLNode->Data = 50, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 5, AVLNode->BF = 0
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 60, AVLNode->BF = 1
>
> AVLNode->Data = 55, AVLNode->BF = 0
>
> AVLNode->Data = 80, AVLNode->BF = -1
>
> AVLNode->Data = 75, AVLNode->BF = 0
>
> AVLNode->Data = 90, AVLNode->BF = -1
>
> AVLNode->Data = 100, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 11, NodeNum = 11
>
>  
>
> -------Test 19----------
>
> PreOrderTraversePrintAVLTree
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 0
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 30, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> After DeleteAVLNode
>
> AVLNode->Data = 50, AVLNode->BF = 1
>
> AVLNode->Data = 20, AVLNode->BF = 1
>
> AVLNode->Data = 10, AVLNode->BF = 0
>
> AVLNode->Data = 70, AVLNode->BF = 0
>
> Compare
>
> PreOrderTraverseCompareNum = 4, NodeNum = 4
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 19, PassNum = 19, FaildNum = 0
