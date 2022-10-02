# 截取字符串，查找字符串，替换字符串——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 截取字符串

```c
OP_STATUS SubString(char *Sub, const char *Str, const unsigned int Pos, const unsigned int SubLen)
```

用Sub返回串Str的第Pos个字符起长度为SubLen的字串

入参应该满足条件如下:其中“StrLen(Str) – Pos + 1”中“+ 1”是要把Pos的字符也算进去

1 <= Pos <= StrLen(Str1)

0 <= SubLen <= StrLen(Str) – Pos + 1

**代码：**

```c
OP_STATUS SubString(char *Sub, const char *Str, const unsigned int Pos, const unsigned int SubLen) {
	char *TraSub = Sub;
	char *TraStr = Str;
	unsigned int Num = 0;

	printf("SubString start\n");
	if (NULL == Str || NULL == Sub) {
		return ERROR;
	}

	if (Pos < 1 || Pos > StringLen(Str)) {
		return ERROR;
	}

	if (SubLen > StringLen(Str) - Pos + 1) {
		return ERROR;
	}

	/*TraStr move to Pos*/
	for (Num = 0; Num < Pos - 1; ++Num) {
		TraStr++;
	}

	/*Copy Str into Sub, lenth is SubLen*/
	for (Num = 0; Num < SubLen; ++Num) {
		*TraSub = *TraStr;
		TraStr++;
		TraSub++;
	}

	*TraSub = '\0';
	
	printf("SubString end\n");
	return SUCCESS;
}
```



**测试用例代码：**

```c
void TestSubString(void) {
	/*Test01*/
	char Str01[] = "abc";
	unsigned int SubPos01 = 1;
	unsigned int SubLen01 = 1;
	char *Sub01 = NULL;
	char Res01[] = "a";

	/*Test02*/
	char Str02[] = "abc";
	unsigned int SubPos02 = 2;
	unsigned int SubLen02 = 2;
	char *Sub02 = NULL;
	char Res02[] = "bc";

	Sub01 = (char *)malloc(SubLen01 + 1);
	if (Sub01 == NULL) {
		goto EXIT;
	}
	Sub02 = (char *)malloc(SubLen02 + 1);
	if (Sub02 == NULL) {
		goto EXIT;
	}

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("\n-------Test 01----------\n");
	SubString(Sub01, Str01, SubPos01, SubLen01);
	printf("Sub01 = %s\n", Sub01);
	StringCompareTest(Res01, Sub01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	SubString(Sub02, Str02, SubPos02, SubLen02);
	printf("Sub02 = %s\n\n", Sub02);
	StringCompareTest(Res02, Sub02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();

EXIT:
	if (Sub01 != NULL) {
		free(Sub01);
		Sub01 = NULL;
	}

	if (Sub02 != NULL) {
		free(Sub02);
		Sub02 = NULL;
	}
}
```

**结果：**

> -------Test start----------
>
> -------Test 01----------
>
> SubString start
>
> SubString end
>
> Sub01 = a
>
> StrCopmare start
>
> Str1 = a
>
> Str2 = a
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 02----------
>
> SubString start
>
> SubString end
>
> Sub02 = bc
>
>  
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 2, PassNum = 2, FaildNum = 0



# 2 查找字符串

```c
unsigned int FindStrIndex(char *Str, const char *FindStr, const unsigned int FindStrPos)
```

**需求：**在Str串的Pos位置之后，找第一个FinStr,找到返回Str的下标，找不到返回0。

**方法：**

1. 使用SubString函数截取字串，长度为FinStr的长度

2. 使用截取的字串与FinStr进行比较

**代码：**

```c
unsigned int FindStrIndex(char *Str, const char *FindStr, const unsigned int FindStrPos) {
	unsigned int StrLenth = StringLen(Str);
	unsigned int FindStrLenth = StringLen(FindStr);
	char *Sub = NULL;
	unsigned int Index = 0;
	unsigned int FindStrIndex = 0;

	OP_STATUS  Status = SUCCESS;

	printf("FindStrIndex start\n");
	if (Str == NULL || FindStr == NULL || FindStrPos == 0 || FindStrPos > StrLenth - FindStrLenth + 1) {
		printf("Invaild parameter!\n");
		FindStrIndex = 0;
		goto EXIT;
	}

	Sub = (char *)malloc(StringLen(Str) + 1);
	if (Sub == NULL) {
		FindStrIndex = 0;
		goto EXIT;
	}	

	for (Index = FindStrPos - 1; Index <= StrLenth - FindStrLenth + 1; ++Index) {
		Status = SubString(Sub, Str, Index, FindStrLenth);
		if (Status == SUCCESS) {
			if (StrCopmare(FindStr, Sub) == 0) {
				FindStrIndex = Index;
				goto EXIT;
			}
		}
	}

EXIT:	
	if (Sub != NULL) {
		free(Sub);
		Sub = NULL;
	}
	
	printf("FindStrIndex = %d\n", FindStrIndex);
	printf("FindStrIndex end\n");
	return FindStrIndex;
}
```



**测试用例代码：**

```c
void TestFindStrIndex(void) {
	/*Test01*/
	char Str01[] = "abcdef";
	char FindStr01[] = "bc";
	unsigned int FindStrPos01 = 1;
	unsigned int FindRes01;
	unsigned int ComPos01 = 2;

	/*Test02*/
	char Str02[] = "abcdef";
	char FindStr02[] = "ef";
	unsigned int FindStrPos02 = 2;
	unsigned int FindRes02;
	unsigned int ComPos02 = 5;

	/*Test03*/
	char Str03[] = "abcdef";
	char FindStr03[] = "ee";
	unsigned int FindStrPos03 = 1;
	unsigned int FindRes03;
	unsigned int ComPos03 = 0;

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	FindRes01 = FindStrIndex(Str01, FindStr01, FindStrPos01);
	ValueTest(ComPos01, FindRes01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	FindRes02 = FindStrIndex(Str02, FindStr02, FindStrPos02);
	ValueTest(ComPos02, FindRes02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	FindRes03 = FindStrIndex(Str03, FindStr03, FindStrPos03);
	ValueTest(ComPos03, FindRes03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



**结果：**

> -------Test start----------
> -------Test 01----------
> FindStrIndex start
> SubString start
> SubString start
> SubString end
> StrCopmare start
> Str1 = bc
> Str2 = ab
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = bc
> Str2 = bc
> ret = 0
> StrCopmare end
> FindStrIndex = 2
> FindStrIndex end
> ValueTest test succeed!
>
> -------Test 02----------
> FindStrIndex start
> SubString start
> SubString end
> StrCopmare start
> Str1 = ef
> Str2 = ab
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = ef
> Str2 = bc
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = ef
> Str2 = cd
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = ef
> Str2 = de
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = ef
> Str2 = ef
> ret = 0
> StrCopmare end
> FindStrIndex = 5
> FindStrIndex end
> ValueTest test succeed!
>
> -------Test 03----------
> FindStrIndex start
> SubString start
> SubString start
> SubString end
> StrCopmare start
> Str1 = ee
> Str2 = ab
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = ee
> Str2 = bc
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = ee
> Str2 = cd
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = ee
> Str2 = de
> ret = 1
> StrCopmare end
> SubString start
> SubString end
> StrCopmare start
> Str1 = ee
> Str2 = ef
> ret = -1
> StrCopmare end
> FindStrIndex = 0
> FindStrIndex end
> ValueTest test succeed!
>
> -------Test result----------
> Print test result;
> TestNum = 3, PassNum = 3, FaildNum = 0

# 3 替换字符串

```c
OP_STATUS StrReplace(const char *Str3, const char *StrRep, char *NewStrRep)
```

## 3.1 需求

​	 Str3，StrRep和NewStrRep都存在，用子串NewStrRep替换主串Str3中出现的所有的子串StrRep。

## 3.2 方法

（1）使用查找字符串的FindStrIndex函数，查找相应的子串，查到位置为FindPosRet

（2）查到就使用MoveBackStr函数主串移动，从FindPosRet的位置开始移动，移动为长度为子串NewStrRep的长度减去NewStrRep子串的长度。（值为0不移动，大于往后移动，小于0往前移动）

 （3）再使用CopyStrWhithoutTail函数将要替换的子串拷进主串

## 3.3 移动字串MoveBackStr

```c
void MoveBackStr(char *Str, const unsigned int Pos, const int MvLen) 
```

Str表示主串，Pos表示查找后的位置，MvLen表示要移动的长度，值为NewStrRep的长度减去NewStrRep子串的长度。（值为0不移动，大于往后移动，小于0往前移动）。

当MvLen大于0时，字串往后移动

当MvLen小于0时，字串往前移动

当MvLen等于0时，字串往前移动

**代码：**

```c
OP_STATUS MoveBackStr(char *Str, const unsigned int Pos, const int MvLen) {
	OP_STATUS Status = SUCCESS;
	char *TraStr = Str;
	unsigned int Index = 0;
	int TraPos = Pos - 1;
	unsigned int TraStrLen = StringLen(TraStr);

	int TraMvLen = MvLen;

	printf("MoveBackStr start\n");	

	if (TraStr == NULL || Pos > TraStrLen + 1) {
		Status = INVALID_PARAMETER;
		goto EXIT;
	}

	/*
	Example 1:
	Pos  = 1
	ab = 2
	RepLen = 4
	MvLen  = 4 - 2 = 2	

	Pos	
	0	1	2	3	4	5
	a	b	c	\0		
			a	b	c	\0
	----------------------------
	Example 2:
	Pos = 2
	bcde = 4
	RepLen = 2
	MvLen = 2 - 4 = -2

		Pos
	0	1	2	3	4	5	6
	a	b	c	d	e	f	\0
	a	d	e	f	\0	
	*/

	if (TraMvLen > 0) {
		for (Index = TraStrLen + 1 + TraMvLen; Index >= TraPos + TraMvLen; --Index) {
			TraStr[Index] = TraStr[Index - TraMvLen];
		}	
	} else if (TraMvLen < 0) {
		TraMvLen = 0 - TraMvLen;
		printf("TraMvLen = %d\n", TraMvLen);
		for (Index = TraPos; Index <= TraStrLen + 1 - TraMvLen; ++Index) {
			TraStr[Index] = TraStr[Index + TraMvLen];
		}
	}

	printf("TraStr = %s\n", TraStr);
EXIT:
	printf("MoveBackStr end\n");
	return Status;
}
```



**测试用例代码：**

```c
void TestMoveBackStr(void) {
	/*Test01*/
	char Str01[20] = "abc";
	unsigned int Pos01 = 1;
	int MvLen01 = 2;
	char CpmStr01[] = "ababc";

	/*Test02*/
	char Str02[20] = "abcdef";
	unsigned int Pos02 = 2;
	int MvLen02 = -2;
	char CpmStr02[] = "adef";

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	MoveBackStr(Str01, Pos01, MvLen01);
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CpmStr01, Str01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	MoveBackStr(Str02, Pos02, MvLen02);
	printf("Str02 = %s\n", Str02);
	StringCompareTest(CpmStr02, Str02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**结果：**

>-------Test start----------
>
>-------Test 01----------
>
>MoveBackStr start
>
>TraStr = ababc
>
>MoveBackStr end
>
>Str01 = ababc
>
>StrCopmare start
>
>Str1 = ababc
>
>Str2 = ababc
>
>ret = 0
>
>StrCopmare end
>
>StringCompareTest test succeed!
>
> 
>
>-------Test 02----------
>
>MoveBackStr start
>
>TraMvLen = 2
>
>TraStr = adef
>
>MoveBackStr end
>
>Str02 = adef
>
>StrCopmare start
>
>Str1 = adef
>
>Str2 = adef
>
>ret = 0
>
>StrCopmare end
>
>StringCompareTest test succeed!
>
> 
>
>-------Test result----------
>
>Print test result;
>
>TestNum = 2, PassNum = 2, FaildNum = 0



## 3.4 拷贝子串函数 CopyStrWhithoutTail

```c
OP_STATUS CopyStrWhithoutTail(char *Str, const unsigned int Pos, const char *CpyStr)
```

Str是传进去要处理的字符串，Pos是Str的位置，CpyStr是指要替换的子串

**代码：**

```c
OP_STATUS CopyStrWhithoutTail(char *Str, const unsigned int Pos, const char *CpyStr) {
	OP_STATUS		Status = SUCCESS;
	char			*TraStr = Str;
	char			*TraCpyStr = CpyStr;
	unsigned int	TraPos = Pos - 1;
	unsigned int	TraStrLen = StringLen(TraStr);
	unsigned int	TraCpStrLen = StringLen(TraCpyStr);
	unsigned int	Index = 0;

	printf("CopyStrWhithoutTail start\n");

	if (TraStr == NULL || Pos > TraStrLen + 1) {
		Status = INVALID_PARAMETER;
		goto EXIT;
	}

	for (Index = TraPos; Index < TraPos + TraCpStrLen; ++Index) {
		TraStr[Index] = *TraCpyStr;
		++TraCpyStr;
	}

	//for (Index = TraPos; Index < TraPos + TraCpStrLen; ++Index) {
	//	*(TraStr + Index) = *TraCpyStr;
	//	++TraCpyStr;
	//}

	printf("TraStr = %s\n", TraStr);
EXIT:
	printf("CopyStrWhithoutTail end\n");
	return Status;
}
```

**测试用例代码：**

```c
void TestCopyStrWhithoutTail(void) {
	char Str01[20] = "ababc";
	unsigned int Pos01 = 1;
	char RepStr01[] = "1234";
	char CpmStr01[] = "1234c";

	printf("-------Test start----------\n");
	InitNum();
	printf("-------Test 01----------\n");
	CopyStrWhithoutTail(Str01, Pos01, RepStr01);	
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CpmStr01, Str01);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**结果：**

> -------Test start----------
>
> -------Test 01----------
>
> CopyStrWhithoutTail start
>
> TraStr = 1234c
>
> CopyStrWhithoutTail end
>
> Str01 = 1234c
>
> StrCopmare start
>
> Str1 = 1234c
>
> Str2 = 1234c
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 1, PassNum = 1, FaildNum = 0



## 3.5 **查找字符串，移动字符串和拷贝字符** 函数TestFindStrIndexToMoveBackStrToCopyStrWhithoutTail

```c
void TestFindStrIndexToMoveBackStrToCopyStrWhithoutTail(void)
```

​	先后调用FindStrIndex函数，MoveBackStr函数和CopyStrWhithoutTail函数来实现字符串的替换

**代码：**

```c
void TestFindStrIndexToMoveBackStrToCopyStrWhithoutTail(void) {
	/*Test01*/
	char Str01[20] = "abcdef";
	unsigned int Pos01 = 1;
	unsigned int RetPos01;
	char FindStr01[] = "bc";
	char RepStr01[] = "12";
	int MvLen01 = StringLen(RepStr01) - StringLen(FindStr01);
	char CmpStr01[] = "a12def";

	/*Test02*/
	char Str02[20] = "abcdef";
	unsigned int Pos02 = 1;
	unsigned int RetPos02;
	char FindStr02[] = "bc";
	char RepStr02[] = "1234";
	int MvLen02 = StringLen(RepStr02) - StringLen(FindStr02);
	char CmpStr02[] = "a1234def";

	/*Test03*/
	char Str03[20] = "abcdef";
	unsigned int Pos03 = 1;
	unsigned int RetPos03;
	char FindStr03[] = "bcde";
	char RepStr03[] = "12";
	int MvLen03 = StringLen(RepStr03) - StringLen(FindStr03);
	char CmpStr03[] = "a12f";

	/*Test04*/
	char Str04[20] = "abcdef";
	unsigned int Pos04 = 1;
	unsigned int RetPos04;
	char FindStr04[] = "cdef";
	char RepStr04[] = "1234";
	int MvLen04 = StringLen(RepStr04) - StringLen(FindStr04);
	char CmpStr04[] = "ab1234";

	/*Test05*/
	char Str05[20] = "abcdef";
	unsigned int Pos05 = 1;
	unsigned int RetPos05;
	char FindStr05[] = "cdef";
	char RepStr05[] = "123456";
	int MvLen05 = StringLen(RepStr05) - StringLen(FindStr05);
	char CmpStr05[] = "ab123456";

	/*Test06*/
	char Str06[20] = "abcdef";
	unsigned int Pos06 = 1;
	unsigned int RetPos06;
	char FindStr06[] = "cdef";
	char RepStr06[] = "12";
	int MvLen06 = StringLen(RepStr06) - StringLen(FindStr06);
	char CmpStr06[] = "ab12";

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	RetPos01 = FindStrIndex(Str01, FindStr01, Pos01);
	printf("RetPos01 = %d\n", RetPos01);
	MoveBackStr(Str01, RetPos01, MvLen01);
	printf("Str01 = %s\n", Str01);
	CopyStrWhithoutTail(Str01, RetPos01, RepStr01);
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CmpStr01, Str01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	RetPos02 = FindStrIndex(Str02, FindStr02, Pos02);
	printf("RetPos02 = %d\n", RetPos02);
	MoveBackStr(Str02, RetPos02, MvLen02);
	printf("Str02 = %s\n", Str02);
	CopyStrWhithoutTail(Str02, RetPos02, RepStr02);
	printf("Str02 = %s\n", Str02);
	StringCompareTest(CmpStr02, Str02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	RetPos03 = FindStrIndex(Str03, FindStr03, Pos03);
	printf("RetPos03 = %d\n", RetPos03);
	MoveBackStr(Str03, RetPos03, MvLen03);
	printf("Str03 = %s\n", Str03);
	CopyStrWhithoutTail(Str03, RetPos03, RepStr03);
	printf("Str03 = %s\n", Str03);
	StringCompareTest(CmpStr03, Str03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	RetPos04 = FindStrIndex(Str04, FindStr04, Pos04);
	printf("RetPos04 = %d\n", RetPos04);
	MoveBackStr(Str04, RetPos04, MvLen04);
	printf("Str04 = %s\n", Str04);
	CopyStrWhithoutTail(Str04, RetPos04, RepStr04);
	printf("Str04 = %s\n", Str04);
	StringCompareTest(CmpStr04, Str04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	RetPos05 = FindStrIndex(Str05, FindStr05, Pos05);
	printf("RetPos05 = %d\n", RetPos05);
	MoveBackStr(Str05, RetPos05, MvLen05);
	printf("Str05 = %s\n", Str05);
	CopyStrWhithoutTail(Str05, RetPos05, RepStr05);
	printf("Str05 = %s\n", Str05);
	StringCompareTest(CmpStr05, Str05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	RetPos06 = FindStrIndex(Str06, FindStr06, Pos06);
	printf("RetPos06 = %d\n", RetPos06);
	MoveBackStr(Str06, RetPos06, MvLen06);
	printf("Str06 = %s\n", Str06);
	CopyStrWhithoutTail(Str06, RetPos06, RepStr06);
	printf("Str06 = %s\n", Str06);
	StringCompareTest(CmpStr06, Str06);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```

**结果：**

> -------Test start----------
>
> -------Test 01----------
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = ab
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 2
>
> FindStrIndex end
>
> RetPos01 = 2
>
> MoveBackStr start
>
> TraStr = abcdef
>
> MoveBackStr end
>
> Str01 = abcdef
>
> CopyStrWhithoutTail start
>
> TraStr = a12def
>
> CopyStrWhithoutTail end
>
> Str01 = a12def
>
> StrCopmare start
>
> Str1 = a12def
>
> Str2 = a12def
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 02----------
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = ab
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 2
>
> FindStrIndex end
>
> RetPos02 = 2
>
> MoveBackStr start
>
> TraStr = abcbcdef
>
> MoveBackStr end
>
> Str02 = abcbcdef
>
> CopyStrWhithoutTail start
>
> TraStr = a1234def
>
> CopyStrWhithoutTail end
>
> Str02 = a1234def
>
> StrCopmare start
>
> Str1 = a1234def
>
> Str2 = a1234def
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 03----------
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bcde
>
> Str2 = abcd
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bcde
>
> Str2 = bcde
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 2
>
> FindStrIndex end
>
> RetPos03 = 2
>
> MoveBackStr start
>
> TraMvLen = 2
>
> TraStr = adef
>
> MoveBackStr end
>
> Str03 = adef
>
> CopyStrWhithoutTail start
>
> TraStr = a12f
>
> CopyStrWhithoutTail end
>
> Str03 = a12f
>
> StrCopmare start
>
> Str1 = a12f
>
> Str2 = a12f
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 04----------
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = abcd
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = bcde
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = cdef
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 3
>
> FindStrIndex end
>
> RetPos04 = 3
>
> MoveBackStr start
>
> TraStr = abcdef
>
> MoveBackStr end
>
> Str04 = abcdef
>
> CopyStrWhithoutTail start
>
> TraStr = ab1234
>
> CopyStrWhithoutTail end
>
> Str04 = ab1234
>
> StrCopmare start
>
> Str1 = ab1234
>
> Str2 = ab1234
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 05----------
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = abcd
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = bcde
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = cdef
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 3
>
> FindStrIndex end
>
> RetPos05 = 3
>
> MoveBackStr start
>
> TraStr = abcdcdef
>
> MoveBackStr end
>
> Str05 = abcdcdef
>
> CopyStrWhithoutTail start
>
> TraStr = ab123456
>
> CopyStrWhithoutTail end
>
> Str05 = ab123456
>
> StrCopmare start
>
> Str1 = ab123456
>
> Str2 = ab123456
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 06----------
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = abcd
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = bcde
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = cdef
>
> Str2 = cdef
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 3
>
> FindStrIndex end
>
> RetPos06 = 3
>
> MoveBackStr start
>
> TraMvLen = 2
>
> TraStr = abef
>
> MoveBackStr end
>
> Str06 = abef
>
> CopyStrWhithoutTail start
>
> TraStr = ab12
>
> CopyStrWhithoutTail end
>
> Str06 = ab12
>
> StrCopmare start
>
> Str1 = ab12
>
> Str2 = ab12
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 6, PassNum = 6, FaildNum = 0



## 3.6 替换字符串总流程函数 StrReplace

```c
OP_STATUS StrReplace(char *Str1, const char *FindStr, const char *StrRep)
```

St1为主串，FindStr为查找子串，StrRep为要替换的子串

先后调用FindStrIndex函数，MoveBackStr函数和CopyStrWhithoutTail进行实现

**代码：**

```c
OP_STATUS StrReplace(char *Str1, const char *FindStr, const char *StrRep) {
	OP_STATUS		Status = SUCCESS;
	char			*TraStr1 = Str1;
	char			*TraFindStr = FindStr;
	char			*TraStrRep = StrRep;

	unsigned int TraStr1Len = StringLen(TraStr1);
	unsigned int FindStrLen = StringLen(TraFindStr);
	unsigned int TraStrRepLen = StringLen(TraStrRep);

	unsigned int Pos;
	unsigned int FindPosRet = 0;

	int MvLen = TraStrRepLen - FindStrLen;
	printf("MvLen = %d\n", MvLen);

	if (TraStr1 == NULL || TraFindStr == NULL || TraStrRep == NULL) {
		printf("Invaild parameter!\n");
		Status =  INVALID_PARAMETER;
		goto EXIT;
	}
	
	Pos = 1;
	do {
		printf("Pos = %d\n", Pos);
		/*Find TraStrRep*/
		FindPosRet = FindStrIndex(TraStr1, TraFindStr, Pos);
		printf("FindRetPos = %d\n", FindPosRet);
		if (FindPosRet == 0) {
			break;
		}

		/*Replace with TraNewStrRep*/
		/*Move back*/
		Status = MoveBackStr(TraStr1, FindPosRet, MvLen);
		if (Status != SUCCESS) {
			printf("Invaild parameter!\n");
			goto EXIT;
		}

		printf("TraStr1 = %s\n", TraStr1);
		/*CopyStrWhithoutTail*/
		Status = CopyStrWhithoutTail(TraStr1, FindPosRet, TraStrRep);
		if (Status != SUCCESS) {
			printf("Invaild parameter!\n");
			goto EXIT;
		}
		printf("TraStr1 = %s\n", TraStr1);

		Pos = FindPosRet + TraStrRepLen;
	} while (FindPosRet != 0);

EXIT:
	return Status;
}
```



**测试用例代码：**

```c
void TestStrReplace(void) {
	OP_STATUS Status;
	/*Test01*/
	char Str01[30] = "abcdef";
	char FindStr01[] = "bc";	
	char RepStr01[] = "12";
	char CmpStr01[] = "a12def";

	/*Test02*/
	char Str02[30] = "abcdef";
	char FindStr02[] = "bc";
	char RepStr02[] = "1234";
	char CmpStr02[] = "a1234def";

	/*Test03*/
	char Str03[30] = "abcdef";
	char FindStr03[] = "bcde";
	char RepStr03[] = "12";
	char CmpStr03[] = "a12f";

	/*Test04*/
	char Str04[30] = "abcdef";
	char FindStr04[] = "cdef";
	char RepStr04[] = "1234";
	char CmpStr04[] = "ab1234";

	/*Test05*/
	char Str05[30] = "abcdef";
	char FindStr05[] = "cdef";
	char RepStr05[] = "123456";
	char CmpStr05[] = "ab123456";

	/*Test06*/
	char Str06[30] = "abcdef";
	char FindStr06[] = "cdef";
	char RepStr06[] = "12";
	char CmpStr06[] = "ab12";

	/*Test07*/
	char Str07[30] = "abcbcfbc";
	char FindStr07[] = "bc";
	char RepStr07[] = "12";
	char CmpStr07[] = "a1212f12";

	/*Test08*/
	char Str08[30] = "abcbcfbc";
	char FindStr08[] = "bc";
	char RepStr08[] = "1234";
	char CmpStr08[] = "a12341234f1234";

	/*Test09*/
	char Str09[30] = "abcbcfbc";
	char FindStr09[] = "bc";
	char RepStr09[] = "1";
	char CmpStr09[] = "a11f1";

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	StrReplace(Str01, FindStr01, RepStr01);
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CmpStr01, Str01);
	
	/*Test02*/
	printf("\n-------Test 02----------\n");
	StrReplace(Str02, FindStr02, RepStr02);
	printf("Str02 = %s\n", Str02);
	StringCompareTest(CmpStr02, Str02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	StrReplace(Str03, FindStr03, RepStr03);
	printf("Str03 = %s\n", Str03);
	StringCompareTest(CmpStr03, Str03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	StrReplace(Str04, FindStr04, RepStr04);
	printf("Str04 = %s\n", Str04);
	StringCompareTest(CmpStr04, Str04);
	
	/*Test05*/
	printf("\n-------Test 05----------\n");
	StrReplace(Str05, FindStr05, RepStr05);
	printf("Str05 = %s\n", Str05);
	StringCompareTest(CmpStr05, Str05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	StrReplace(Str06, FindStr06, RepStr06);
	printf("Str06 = %s\n", Str06);
	StringCompareTest(CmpStr06, Str06);

	/*Test07*/
	printf("\n-------Test 07----------\n");
	StrReplace(Str07, FindStr07, RepStr07);
	printf("Str07 = %s\n", Str07);
	StringCompareTest(CmpStr07, Str07);

	/*Test08*/
	printf("\n-------Test 08----------\n");
	StrReplace(Str08, FindStr08, RepStr08);
	printf("Str08 = %s\n", Str08);
	StringCompareTest(CmpStr08, Str08);

	/*Test09*/
	printf("\n-------Test 09----------\n");
	StrReplace(Str09, FindStr09, RepStr09);
	printf("Str09 = %s\n", Str09);
	StringCompareTest(CmpStr09, Str09);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



**结果：**

> TraStr1 = abef
>
> CopyStrWhithoutTail start
>
> TraStr = ab12
>
> CopyStrWhithoutTail end
>
> TraStr1 = ab12
>
> Pos = 5
>
> FindStrIndex start
>
> Invaild parameter!
>
> FindStrIndex = 0
>
> FindStrIndex end
>
> FindRetPos = 0
>
> Str06 = ab12
>
> StrCopmare start
>
> Str1 = ab12
>
> Str2 = ab12
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 07----------
>
> MvLen = 0
>
> Pos = 1
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = ab
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 2
>
> FindStrIndex end
>
> FindRetPos = 2
>
> MoveBackStr start
>
> TraStr = abcbcfbc
>
> MoveBackStr end
>
> TraStr1 = abcbcfbc
>
> CopyStrWhithoutTail start
>
> TraStr = a12bcfbc
>
> CopyStrWhithoutTail end
>
> TraStr1 = a12bcfbc
>
> Pos = 4
>
> FindStrIndex start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = 2b
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 4
>
> FindStrIndex end
>
> FindRetPos = 4
>
> MoveBackStr start
>
> TraStr = a12bcfbc
>
> MoveBackStr end
>
> TraStr1 = a12bcfbc
>
> CopyStrWhithoutTail start
>
> TraStr = a1212fbc
>
> CopyStrWhithoutTail end
>
> TraStr1 = a1212fbc
>
> Pos = 6
>
> FindStrIndex start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = 2f
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = fb
>
> ret = -1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 7
>
> FindStrIndex end
>
> FindRetPos = 7
>
> MoveBackStr start
>
> TraStr = a1212fbc
>
> MoveBackStr end
>
> TraStr1 = a1212fbc
>
> CopyStrWhithoutTail start
>
> TraStr = a1212f12
>
> CopyStrWhithoutTail end
>
> TraStr1 = a1212f12
>
> Pos = 9
>
> FindStrIndex start
>
> Invaild parameter!
>
> FindStrIndex = 0
>
> FindStrIndex end
>
> FindRetPos = 0
>
> Str07 = a1212f12
>
> StrCopmare start
>
> Str1 = a1212f12
>
> Str2 = a1212f12
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 08----------
>
> MvLen = 2
>
> Pos = 1
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = ab
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 2
>
> FindStrIndex end
>
> FindRetPos = 2
>
> MoveBackStr start
>
> TraStr = abcbcbcfbc
>
> MoveBackStr end
>
> TraStr1 = abcbcbcfbc
>
> CopyStrWhithoutTail start
>
> TraStr = a1234bcfbc
>
> CopyStrWhithoutTail end
>
> TraStr1 = a1234bcfbc
>
> Pos = 6
>
> FindStrIndex start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = 4b
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 6
>
> FindStrIndex end
>
> FindRetPos = 6
>
> MoveBackStr start
>
> TraStr = a1234bcbcfbc
>
> MoveBackStr end
>
> TraStr1 = a1234bcbcfbc
>
> CopyStrWhithoutTail start
>
> TraStr = a12341234fbc
>
> CopyStrWhithoutTail end
>
> TraStr1 = a12341234fbc
>
> Pos = 10
>
> FindStrIndex start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = 4f
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = fb
>
> ret = -1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 11
>
> FindStrIndex end
>
> FindRetPos = 11
>
> MoveBackStr start
>
> TraStr = a12341234fbcbc
>
> MoveBackStr end
>
> TraStr1 = a12341234fbcbc
>
> CopyStrWhithoutTail start
>
> TraStr = a12341234f1234
>
> CopyStrWhithoutTail end
>
> TraStr1 = a12341234f1234
>
> Pos = 15
>
> FindStrIndex start
>
> Invaild parameter!
>
> FindStrIndex = 0
>
> FindStrIndex end
>
> FindRetPos = 0
>
> Str08 = a12341234f1234
>
> StrCopmare start
>
> Str1 = a12341234f1234
>
> Str2 = a12341234f1234
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test 09----------
>
> MvLen = -1
>
> Pos = 1
>
> FindStrIndex start
>
> SubString start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = ab
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 2
>
> FindStrIndex end
>
> FindRetPos = 2
>
> MoveBackStr start
>
> TraMvLen = 1
>
> TraStr = acbcfbc
>
> MoveBackStr end
>
> TraStr1 = acbcfbc
>
> CopyStrWhithoutTail start
>
> TraStr = a1bcfbc
>
> CopyStrWhithoutTail end
>
> TraStr1 = a1bcfbc
>
> Pos = 3
>
> FindStrIndex start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = 1b
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 3
>
> FindStrIndex end
>
> FindRetPos = 3
>
> MoveBackStr start
>
> TraMvLen = 1
>
> TraStr = a1cfbc
>
> MoveBackStr end
>
> TraStr1 = a1cfbc
>
> CopyStrWhithoutTail start
>
> TraStr = a11fbc
>
> CopyStrWhithoutTail end
>
> TraStr1 = a11fbc
>
> Pos = 4
>
> FindStrIndex start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = 1f
>
> ret = 1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = fb
>
> ret = -1
>
> StrCopmare end
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = bc
>
> Str2 = bc
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 5
>
> FindStrIndex end
>
> FindRetPos = 5
>
> MoveBackStr start
>
> TraMvLen = 1
>
> TraStr = a11fc
>
> MoveBackStr end
>
> TraStr1 = a11fc
>
> CopyStrWhithoutTail start
>
> TraStr = a11f1
>
> CopyStrWhithoutTail end
>
> TraStr1 = a11f1
>
> Pos = 6
>
> FindStrIndex start
>
> Invaild parameter!
>
> FindStrIndex = 0
>
> FindStrIndex end
>
> FindRetPos = 0
>
> Str09 = a11f1
>
> StrCopmare start
>
> Str1 = a11f1
>
> Str2 = a11f1
>
> ret = 0
>
> StrCopmare end
>
> StringCompareTest test succeed!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 9, PassNum = 9, FaildNum = 0









