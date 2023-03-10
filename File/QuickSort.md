# 快速排序——C语言描述

[toc]

# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

**核心：**就是让元素回到自己的位置。 

**注意：**

1 i, j需要定义，因为递归部分需要用到；

2 哪边做哨兵，另一边先移动；

3 当移动指针时，相等时也要移动，注意加上i，j范围的判断；

4 可以用手做意向进行想象。

**参考链接：**

https://blog.csdn.net/weixin_43296982/article/details/123098472?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167845920716800192277020%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167845920716800192277020&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-123098472-null-null.142

# 2 代码

**（1）左边第一个元素为哨兵**

```c
/*QuickSort*/
//{ 5, 2, 6, 3, 1, 4 }
void QuickSort(int *Arr, int Low, int High) {
	int i = Low;
	int j = High;
	int FlagValue = Arr[Low];
	int Tmp;

	if ((Arr == NULL) || (i > j)) {
		return ;
	}

	while (i < j) {
		while ((Arr[j] >= FlagValue) && (i < j)) {
			--j;
		}

		while ((Arr[i] <= FlagValue) && (i < j)) {
			++i;
		}

		if (i < j) {
			Tmp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = Tmp;
		}
	}

	Arr[Low] = Arr[i];
	Arr[i] = FlagValue;

	QuickSort(Arr, Low, i - 1);
	QuickSort(Arr, i + 1, High);
}

```

**（2）右边第一个元素为哨兵**

```c
void QuickSort(int *Arr, int Low, int High) {
	int i = Low;
	int j = High;
	int FlagValue = Arr[High];
	int Tmp;

	if ((Arr == NULL) || (i > j)) {
		return;
	}

	while (i < j) {
		while ((Arr[i] <= FlagValue) && (i < j)) {
			++i;
		}

		while ((Arr[j] >= FlagValue) && (i < j)) {
			--j;
		}

		if (i < j) {
			Tmp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = Tmp;
		}
	}

	Arr[High] = Arr[j];
	Arr[j] = FlagValue;

	QuickSort(Arr, Low, j - 1);
	QuickSort(Arr, j + 1, High);
}
```



#  4 测试用例

```c
/*TestQuickSort*/
void TestQuickSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 5, 2, 6, 3, 1, 4 };
	int Num01 = 6;
	int Low01 = 0;
	int High01 = Num01 - 1;
	int CmpArr01[] = { 1, 2, 3, 4, 5, 6 };

	/*Test02: Normal*/
	int Arr02[] = { 8, 7, 6, 5, 4, 3, 2, 1};
	int Num02 = 8;
	int Low02 = 0;
	int High02 = Num02 - 1;
	int CmpArr02[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	/*Test03: Normal*/
	int Arr03[] = { 0};
	int Num03 = 1;
	int Low03 = 0;
	int High03 = Num03 - 1;
	int CmpArr03[] = { 0};

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	QuickSort(Arr01, Low01, High01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	QuickSort(Arr02, Low02, High02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	QuickSort(Arr03, Low03, High03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

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
> Arr[0] = 1
>
> Arr[1] = 2
>
> Arr[2] = 3
>
> Arr[3] = 4
>
> Arr[4] = 5
>
> Arr[5] = 6
>
>  
>
> -------Test 02----------
>
> Arr[0] = 1
>
> Arr[1] = 2
>
> Arr[2] = 3
>
> Arr[3] = 4
>
> Arr[4] = 5
>
> Arr[5] = 6
>
> Arr[6] = 7
>
> Arr[7] = 8
>
>  
>
> -------Test 03----------
>
> Arr[0] = 0
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 3, PassNum = 3, FaildNum = 0

