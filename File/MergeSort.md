# 归并排序——C语言描述，递归法与循环法

[toc]

# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 递归法

## （1）算法思想

​	2路归并：将n个元素的序列不断对半划分成子序列，然后再两两归并有序序列，如此反复，得到有序序列。占空间，效率高，稳定的排序

## （2）时间复杂度：

​	为nlogn。递归深度logn，最底下那层只有1元素，只扫描一次，最上面那层归并所有元素都得扫描一遍，类似等差数列，首项为1， 尾项为n，项数为|logn| + 1，所以时间复杂度为nlogn。

## （3）空间复杂度：

​	为n。最终需要n个元素的空间存相应的数据（不是nlogn，尽管每次合并操作都需要申请额外的内存空间，但在合并完成之后，临时开辟的内存空间就被释放掉了。在任意时刻，CPU 只会有一个函数在执行，也就只会有一个临时的内存空间在使用。临时内存空间最大也不会超过 n 个元素的大小，所以归并排序的空间复杂度是 O(n)）。

## （4）稳定的排序：

​	因为if (Arr02[Low] <= Arr02[j])的结果不过成功与否肯定会执行下面的语句，不会跳过。

## （5）代码

```c
/*MergeSort*/
void Merge(int *Arr01, int *Arr02, int Low, int Mid, int High) {
	int i, j, k;

	for (i = Low, j = Mid + 1; (Low <= Mid) && (j <= High); i++) {
		if (Arr02[Low] <= Arr02[j]) {
			Arr01[i] = Arr02[Low++];
		}
		else {
			Arr01[i] = Arr02[j++];
		}
	}

	if (Low <= Mid) {
		for (k = 0; k <= (Mid - Low); k++) {
			Arr01[i + k] = Arr02[Low + k];
		}
	}

	if (j <= High) {
		for (k = 0; k <= (High - j); k++) {
			Arr01[i + k] = Arr02[j + k];
		}
	}
}

void MSort(int *Arr01, int *Arr, int Low, int High) {
	int Mid;
	int Arr02[10];

	if (Low == High) {
		Arr01[Low] = Arr[Low];
	}
	else {
		Mid = (Low + High) / 2;
		MSort(Arr02, Arr, Low, Mid);
		MSort(Arr02, Arr, Mid + 1, High);
		Merge(Arr01, Arr02, Low, Mid, High);
	}
}

void MergeSort(int *Arr, int Num) {
	if ((Arr == NULL) || (Num <= 1)) {
		return;
	}

	MSort(Arr, Arr, 0, Num - 1);
}
```

##  （5）测试用例

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

/*TestMergeSort*/
void TestMergeSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4};
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	MergeSort(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	MergeSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	MergeSort(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	MergeSort(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	MergeSort(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

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
> Arr[1] = 3
>
> Arr[2] = 3
>
> Arr[3] = 4
>
> Arr[4] = 5
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
> -------Test 04----------
>
> Arr[0] = 0
>
> Arr[1] = 1
>
> Correct!
>
>  
>
> -------Test 05----------
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
> TestNum = 5, PassNum = 5, FaildNum = 0



# 2 循环法

## **（1）算法思想**

​    直接将数组元素直接按一个元素为增量两两归并到一个临时数组，然后再以两个元素（上把的两倍）为增量将临时数组的元素归并回原数组。以此类推，反复执行前面的步骤，直至将原数组变得有序。

## **（2）时间复杂度** 

​    为nlogn。外层循环每次以4的倍数递减，总共需log4(n) + 1次，中层循环次数为n/2k，内层循环归并时时需扫描数组元素的个数为2k次，所以中层加内层循环每次操作次数为n次。所以总时间复杂度为(log4(n) + 1)*n，比使用递归的归并排序时间复杂度（log2(n) + 1） * n要好。

**例子**：假如一共有8个元素(N = 8).循环次数如下表所示。

| 外层循环次数 | k    | 中层循环次数     | 内层循环数组移动次数 |
| ------------ | ---- | ---------------- | -------------------- |
| 1            | 1    | N / 2k = 8/2 = 4 | 2k = 2               |
| 1            | 2    | N / 2k = 8/4 = 2 | 2k = 4               |
| 2            | 4    | N / 2k = 8/8 = 1 | 2k = 8               |
| 2            |      |                  |                      |

## **（3）空间复杂度**

​	只申请了一个大小为Sizeof(int) * Num 的空间，没有额外的栈空间.

## （4）代码

```c
/*MergeSort*/
void Merge02(int *Arr02, int *Arr01, int Low, int Mid, int High) {
	int i, j, k;

	for (i = Low, j = Mid + 1; (Low <= Mid) && (j <= High); i++) {
		if (Arr02[Low] <= Arr02[j]) {
			Arr01[i] = Arr02[Low++];
		}
		else {
			Arr01[i] = Arr02[j++];
		}
	}

	if (Low <= Mid) {
		for (k = 0; k <= Mid - Low; k++) {
			Arr01[i + k] = Arr02[Low + k];
		}
	}

	if (j <= High) {
		for (k = 0; k <= High - j; k++) {
			Arr01[i + k] = Arr02[j + k];
		}
	}
}

void MergePass(int *Arr02, int *Arr01, int Incre, int Num) {
	int i = 0;

	while ((i + 2 * Incre - 1) < Num) {
		Merge02(Arr02, Arr01, i, i + Incre - 1, i + 2 * Incre - 1);
		i += 2 * Incre;
	}

	if ((i + Incre - 1) < (Num - 1)) {
		Merge02(Arr02, Arr01, i, i + Incre - 1, Num - 1);
	} else {
		while (i < Num) {
			Arr01[i] = Arr02[i];
			i++;
		}
	}
}

/*MergeSorByCycle*/
void MergeSorByCycle(int *Arr, int Num) {
	int Incre = 1;
	int *Arr01 = NULL;

	if ((Arr == NULL) || (Num <= 1)) {
		return;
	}

	Arr01 = (int *)malloc(sizeof(int) * Num);
	if (Arr01 == NULL) {
		goto EXIT;
	}

	while (Incre < Num) {
		MergePass(Arr, Arr01, Incre, Num);
		Incre *= 2;
		MergePass(Arr01, Arr, Incre, Num);
		Incre *= 2;
	}	

EXIT:
	if (Arr01 != NULL) {
		free(Arr01);
		Arr01 = NULL;
	}
}
```

## （5）测试用例

```c
/*TestMergeSorByCycle*/
void TestMergeSorByCycle(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4 };
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	MergeSorByCycle(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	MergeSorByCycle(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	MergeSorByCycle(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	MergeSorByCycle(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	MergeSorByCycle(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

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
> Arr[1] = 3
>
> Arr[2] = 3
>
> Arr[3] = 4
>
> Arr[4] = 5
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
> -------Test 04----------
>
> Arr[0] = 0
>
> Arr[1] = 1
>
> Correct!
>
>  
>
> -------Test 05----------
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
> TestNum = 5, PassNum = 5, FaildNum = 0







