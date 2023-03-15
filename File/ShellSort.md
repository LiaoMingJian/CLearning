# 基尔排序——C语言描述

[toc]

# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

**算法思想：**引入增量Incre（如Incre = Num / 2，不一定为最优），将原来的无序序列划分多个子序列，然后以增量Incre尺度进行插入排序，先使得多个无序子序列变得有序。当Incre为1时，该序列已经基本有序，然后进行一次完整的插入排序。

**注意：**

①  最外层循环控制增量的变化；

②  里面两层是与插入排序一致，中间那层的初始值应为Incre，最里面那层循环迭代，j -= Incre，j每次都需要减Incre.

# 2 代码

```c
/*ShellSort*/
void ShellSort(int *Arr, int Num) {
	int i, j, Tmp, Incre;

	if ((Arr == NULL) || (Num <= 1)) {
		return ;
	}

	for (Incre = Num / 2; Incre > 0; Incre /= 2) {
		for (i = Incre; i < Num; i++) {
			if (Arr[i] < Arr[i - Incre]) {
				Tmp = Arr[i];
				for (j = i - Incre; (Arr[j] > Tmp) && (j >= 0); j -= Incre) {
					Arr[j + Incre] = Arr[j];
				}
				
				Arr[j + Incre] = Tmp;
			}
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

/*TestShellSort*/
void TestShellSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Normal*/
	int Arr02[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num02 = 8;
	int CmpArr02[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test03: Two Mem*/
	int Arr03[] = { 1, 0 };
	int Num03 = 2;
	int CmpArr03[] = { 0, 1 };

	/*Test04: Only 1 Mem*/
	int Arr04[] = { 0 };
	int Num04 = 1;
	int CmpArr04[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	ShellSort(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	ShellSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	ShellSort(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	ShellSort(Arr04, Num04);
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

