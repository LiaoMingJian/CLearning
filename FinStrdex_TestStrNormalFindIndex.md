# 查找字符串两种方法（截取子串，朴素匹配法）——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 查找字符串——截取字串方法

```c
unsigned int FindStrIndex(char *Str, const char *FindStr, const unsigned int FindStrPos)
```

## 1.1需求：在Str串的Pos位置之后，找第一个FinStr,找到返回Str的下标，找不到返回0。

## 1.2  条件

​	FindStr与FindStr非空，0 < FindStrPos<= FindStrLen - FindStrLen

## 1.3 方法：

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
> ValueTest test succeed!
>
>  
>
> -------Test 02----------
>
> FindStrIndex start
>
> SubString start
>
> SubString end
>
> StrCopmare start
>
> Str1 = ef
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
> Str1 = ef
>
> Str2 = bc
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
> Str1 = ef
>
> Str2 = cd
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
> Str1 = ef
>
> Str2 = de
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
> Str1 = ef
>
> Str2 = ef
>
> ret = 0
>
> StrCopmare end
>
> FindStrIndex = 5
>
> FindStrIndex end
>
> ValueTest test succeed!
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
> Str1 = ee
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
> Str1 = ee
>
> Str2 = bc
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
> Str1 = ee
>
> Str2 = cd
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
> Str1 = ee
>
> Str2 = de
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
> Str1 = ee
>
> Str2 = ef
>
> ret = -1
>
> StrCopmare end
>
> FindStrIndex = 0
>
> FindStrIndex end
>
> ValueTest test succeed!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 3, PassNum = 3, FaildNum = 0



# 2 查找字符串——朴素匹配方法

```c
unsigned int StrNormalFindIndex(const char *Str, const char *FindStr, const unsigned int FindPos)
```

## 2.1 功能需求：

Str为主串，FindStr为要找的子串，FindPos为从主串Str的第FindPos个位置开始找子串FindStr,找到返回主串的位置，找不到返回0.

 

## 2.2 条件

​     Str与FindStr非空，且FindPos <= StrLen



## 2.3 代码

**①StrNormalFindIndex函数**

```c
unsigned int StrNormalFindIndex(const char *Str, const char *FindStr, const unsigned int FindPos) {
	unsigned int RetPos = 0;	
	char *TraStr = Str;
	char *TraFindStr = FindStr;
	unsigned int TraFindFos = FindPos;

	unsigned int TraStrLen = StringLen(TraStr);
	unsigned int TraFindStrLen = StringLen(TraFindStr);

	unsigned int StrIndexOut = TraFindFos;
	unsigned int StrIndexIn = 0;
	unsigned int FindStrIndex = 0;	

	printf("StrNormalFindIndex start\n");
	if (TraStr == NULL || TraFindStr == NULL || TraStrLen < TraFindStrLen || FindPos > TraStrLen) {
		goto EXIT;
	}

	for (StrIndexOut = TraFindFos - 1; StrIndexOut <= TraStrLen - TraFindStrLen; ++StrIndexOut) {
		for (StrIndexIn = StrIndexOut; StrIndexIn < StrIndexOut + TraFindStrLen; ++StrIndexIn) {
			if (TraStr[StrIndexIn] == TraFindStr[FindStrIndex]) {
				++FindStrIndex;
			} else {
				FindStrIndex = 0;
				break;
			}
		}
	
		if (StrIndexIn == StrIndexOut + TraFindStrLen) {
			printf("Find Success!\n");			
			RetPos = StrIndexOut + 1;
			break;
		}
	}

EXIT:
	printf("RetPos = %d\n", RetPos);
	printf("StrNormalFindIndex end\n");	
	return RetPos;
}
```



**②测试用例代码**

```c
void TestStrNormalFindIndex(void) {
	/*Test01*/
	char Str01[20] = "abcdef";
	char FindStr01[] = "bc";
	unsigned int FindPos01 = 1;
	unsigned int RetPos01;
	unsigned int CmpFindPos01 = 2;

	/*Test02*/
	char Str02[20] = "abcdef";
	char FindStr02[] = "ef";
	unsigned int FindPos02 = 2;
	unsigned int RetPos02;
	unsigned int CmpFindPos02 = 5;

	/*Test03*/
	char Str03[20] = "abcdef";
	char FindStr03[] = "ee";
	unsigned int FindPos03 = 1;
	unsigned int RetPos03;
	unsigned int CmpFindPos03 = 0;

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	RetPos01 = StrNormalFindIndex(Str01, FindStr01, FindPos01);
	printf("RetPos01 = %d\n", RetPos01);
	ValueTest(CmpFindPos01, RetPos01);
	
	/*Test02*/
	printf("\n-------Test 02----------\n");
	RetPos02 = StrNormalFindIndex(Str02, FindStr02, FindPos02);
	printf("RetPos02 = %d\n", RetPos02);
	ValueTest(CmpFindPos02, RetPos02);
	
	/*Test03*/
	printf("\n-------Test 03----------\n");
	RetPos03 = StrNormalFindIndex(Str03, FindStr03, FindPos03);
	printf("RetPos03 = %d\n", RetPos03);
	ValueTest(CmpFindPos03, RetPos03);

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
> StrNormalFindIndex start
>
> Find Success!
>
> RetPos = 2
>
> StrNormalFindIndex end
>
> RetPos01 = 2
>
> ValueTest test succeed!
>
>  
>
> -------Test 02----------
>
> StrNormalFindIndex start
>
> Find Success!
>
> RetPos = 5
>
> StrNormalFindIndex end
>
> RetPos02 = 5
>
> ValueTest test succeed!
>
>  
>
> -------Test 03----------
>
> StrNormalFindIndex start
>
> RetPos = 0
>
> StrNormalFindIndex end
>
> RetPos03 = 0
>
> ValueTest test succeed!
>
>  
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 3, PassNum = 3, FaildNum = 0

