# 二分查找——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​	对半查找。

# 2 代码

```c
/*BinarySearch*/
//int Arr01[] = {0, 1, 2, 3, 4, 5};
//2, 1, 5, 7, {0}
int BinarySearch(int *Arr, int Num, int SearchValue) {
	int Low = 0;
	int High = Num - 1;
	int Mid = 0;

	if (Arr == NULL || Num <= 0 || SearchValue < Arr[Low] || SearchValue > Arr[High]) {
		return -1;
	}

	while (Low <= High) {
		Mid = (Low + High) / 2;
		
		if (SearchValue < Arr[Mid]) {
			High = Mid - 1;
		} else if (SearchValue > Arr[Mid]) {
			Low = Mid + 1;
		} else {
			return Mid;
		}
	}
	
	return -1;
}
```



#  4 测试用例

```c
/*TestBinarySearch*/
void TestCmpRes(int CmpRes01, int Res01) {
	TestNum++;

	if (CmpRes01 != Res01) {
		FaildNum++;
	}
	else {
		PassNum++;
	}
}

void TestBinarySearch(void) {
	/*Test01: Normal*/
	int Arr01[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue01 = 2;
	int Res01 = 0;
	int CmpRes01 = 2;
	int Num01 = 6;

	/*Test02: Bounary*/
	int Arr02[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue02 = 0;
	int Res02 = 0;
	int CmpRes02 = 0;
	int Num02 = 6;

	/*Test03: Bounary*/
	int Arr03[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue03 = 5;
	int Res03 = 0;
	int CmpRes03 = 5;
	int Num03 = 6;

	/*Test04: Don't exit*/
	int Arr04[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue04 = 7;
	int Res04 = 0;
	int CmpRes04 = -1;
	int Num04 = 6;

	/*Test05: Only a Mem and exit*/
	int Arr05[] = { 0 };
	int SearchValue05 = 0;
	int Res05 = 0;
	int CmpRes05 = 0;
	int Num05 = 1;

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	Res01 = BinarySearch(Arr01, Num01, SearchValue01);
	TestCmpRes(CmpRes01, Res01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	Res02 = BinarySearch(Arr02, Num02, SearchValue02);
	TestCmpRes(CmpRes02, Res02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	Res03 = BinarySearch(Arr03, Num03, SearchValue03);
	TestCmpRes(CmpRes03, Res03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	Res04 = BinarySearch(Arr04, Num04, SearchValue04);
	TestCmpRes(CmpRes04, Res04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	Res05 = BinarySearch(Arr05, Num05, SearchValue05);
	TestCmpRes(CmpRes05, Res05);

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
>  
>
>  -------Test 02----------
>
>  
>
> -------Test 03----------
>
>  
>
> -------Test 04----------
>
>  
>
> -------Test 05----------
>
>   
>
>  -------Test result----------
>
> Print test result;
>
> TestNum = 5, PassNum = 5, FaildNum = 0

