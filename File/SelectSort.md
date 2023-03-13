# 选择排序——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​    将序列中最小或者最大的元素选出来放到最前面去。

**注意：**

①  使用下标进行迭代，而不是使用值。

②  外层循环条件是i < Num – 1;只需要对前n – 1个元素操作即可；内层循环因为要对所有元素比较，所以结束条件是j < Num，起始条件为i + 1，因为已经保证较小（或较大）的都在前面了。

# 2 代码

```c
/*SelectSort*/
void SelectSort(int *Arr, int Num) {
	int i = 0;
	int j = 0;;
	int MinIndex;

	if ((Arr == NULL) || (Num <= 1)) {
		return ;
	}

	for (i = 0; i < Num - 1; ++i) {
		MinIndex = i;
		for (j = i + 1; j < Num; ++j) {
			if (Arr[j] < Arr[MinIndex]) {
				MinIndex = j;
			}
		}

		if (i != MinIndex) {
			Swap(&Arr[i], &Arr[MinIndex]);
		}
	}
}
```

#  4 测试用例

```c
/*TestSelectSort*/
void TestSelectSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Only 1 Mem*/
	int Arr02[] = { 0 };
	int Num02 = 1;
	int CmpArr02[] = { 0 };


	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	SelectSort(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	SelectSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

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
>  
>
> -------Test 02----------
>
> Arr[0] = 0
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0

