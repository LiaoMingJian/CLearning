# 堆排序——C语言描述

[toc]

# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

**（1）算法思想：**

将待排序的序列构造成一个大顶堆。将堆顶元素与数组末尾的元素进行交换。数组长度减一，并重新调整堆。反复执行，即可得有序序列。

**（2）利用二叉树的性质：**

一个完全二叉树，按编号0开始进行层序遍历。

①  当i为0时，无双亲结点；

②  当i有左孩子时，左孩子的编号为2i + 1；

③  当i有右孩子时，右孩子的编号为2i + 2；

 

**（3）时间复杂度**

时间复杂度为nlogn。创建堆复杂度最大为nlogn（假如每个结点之后的孩子结点都需要交换，根结点需要交换的次数为完成二叉树的深度（|logn| + 1），类似等差数列）。调整堆复杂度最大度也是nlogn（每次交换堆顶，重新调整堆，从根结点开始调整，最大调整次数为为二叉树的深度，（|logi| + 1）），需要调整n-1次，所以复杂度为nlogn)。

 

**注意：**

**(1)HeapSort:**

①  创建堆：从最后一个非叶子结点开始（(Num - 1)/2），到根结点结束，所有的非叶子结点都要处理；

②  调整堆： NodeIndex无需等于0，因为只剩一个元素时无需再交换和调整；

③  调整堆：因为只交换了第一个元素，所以调整堆的时候只对从第一个结点开始调整，长度也要递减。

 

**(1) HeapAdjust:**

①  使用循环的原因是交换过的结点是需要再次与他的孩子结点进行调整的;

②  从左孩子结点开始，每次都取结点的左孩子;

③  先孩子结点相互比较，然后与双亲结点进行比较;

④  孩子结点比较后使用i++的方式，是了保证下一个循环使用交换过结点进行比较.

⑤  如发生了交换，NoteIndex = i, 进行迭代

# 2 代码

```c
void Swap(int *Mem01, int *Mem02) {
	int Tmp = *Mem01;
	*Mem01 = *Mem02;
	*Mem02 = Tmp;
}

void HeapAdjust(int *Arr, int NodeIndex, int Num) {
	int i;

	for (i = 2 * NodeIndex + 1; i < Num; i = 2 * i + 1) {
		if (((i + 1) < Num) && (Arr[i] < Arr[i + 1])) {
			i++;
		}

		if (Arr[i] < Arr[NodeIndex]) {
			break;
		} else {
			Swap(&Arr[i], &Arr[NodeIndex]);
		}

		NodeIndex = i;
	}
}

/*HeapSort*/
// { 1, 3, 2, 5, 4, 0 }
void HeapSort(int *Arr, int Num) {
	int NodeIndex;

	if ((Arr == NULL) || (Num <= 1)) {
		return ;
	}

	for (NodeIndex = (Num - 1) / 2; NodeIndex >= 0; --NodeIndex) {
		HeapAdjust(Arr, NodeIndex, Num);
	}

	for (NodeIndex = Num - 1; NodeIndex > 0; --NodeIndex) {
		Swap(&Arr[0], &Arr[NodeIndex]);
		HeapAdjust(Arr, 0, NodeIndex);
	}
}

```

#  4 测试用例

```c
void TestCmpArr(int *CmpArr, int Num, int *Arr) {
	int Index = 0;
	int CmpNum = 0;

	TestNum++;

	for (Index = 0; Index < Num; ++Index) {
		if (CmpArr[Index] == Arr[Index]) {
			CmpNum++;
		}
	}

	if (CmpNum != Num) {
		printf("Incorrect!\n");
		FaildNum++;
	}
	else {
		printf("Correct!\n");
		PassNum++;
	}
}

/*TestHeapSort*/
void TestHeapSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };
	//int CmpArr01[] = { 5, 4, 2, 3, 1, 0 };

	/*Test02: Normal*/
	int Arr02[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num02 = 8;
	int CmpArr02[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	//int CmpArr02[] = { 7, 6, 5, 4, 3, 2, 1, 0 };

	/*Test03: Two Mem*/
	int Arr03[] = { 1, 0 };
	int Num03 = 2;
	int CmpArr03[] = { 0, 1 };
	//int CmpArr03[] = { 1, 0 };

	/*Test04: Only 1 Mem*/
	int Arr04[] = { 0 };
	int Num04 = 1;
	int CmpArr04[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	HeapSort(Arr01, Num01);

	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	HeapSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	HeapSort(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	HeapSort(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

 **打印结果**：

> -------Test start----------
>
>   
>
> -------Test 01----------
>
> Arr[0] = 0
>
> Arr[1] = 1
>
> Arr[2] = 2
>
> Arr[3] = 3
>
> Arr[4] = 4
>
> Arr[5] = 5
>
> Correct!
>
>   
>
> -------Test 02----------
>
> Arr[0] = 0
>
> Arr[1] = 1
>
> Arr[2] = 2
>
> Arr[3] = 3
>
> Arr[4] = 4
>
> Arr[5] = 5
>
> Arr[6] = 6
>
> Arr[7] = 7
>
> Correct!
>
>   
>
> -------Test 03----------
>
> Arr[0] = 0
>
> Arr[1] = 1
>
> Correct!
>
>   
>
> -------Test 04----------
>
> Arr[0] = 0
>
> Correct!
>
>   
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 4, PassNum = 4, FaildNum = 0

