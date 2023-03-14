# 插入排序——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​    将要排序的元素插入前面的有序序列。

**注意：**

①  外层循环：从第二个元素开始，对每个元素进行操作；

②  先找到一个元素比前一个元素小的元素；

③  内存循环，移动前面的有序序列，直到出现比要插入的元素小的元素出现；

④  插入要排序的元素。



# 2 代码

```c
/*InsertSort*/
void InsertSort(int *Arr, int Num) {
	int i = 0;
	int j = 0;
	int Tmp;

	if ((Arr == NULL) || (Num <= 1)) {
		return ;
	}

	for (i = 1; i < Num; ++i) {
		Tmp = Arr[i];
		if (Arr[i] < Arr[i - 1]) {
			for (j = i - 1; Arr[j] > Tmp; --j) {
				Arr[j + 1] = Arr[j];
			}

			Arr[j + 1] = Tmp;
		}
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

/*TestInsertSort*/
void TestInsertSort(void) {
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
	InsertSort(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	InsertSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

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
> Correct!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0

