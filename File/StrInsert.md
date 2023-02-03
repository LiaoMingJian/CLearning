# 插入字符串——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 插入字符串

```c
OP_STATUS StrInsert(char *Str, const unsigned int InSertPos, const char *InsertStr)
```

## 1.1功能需求：

​     在主串Str的第InSertPos个位置的后面插入子串InsertStr

## 1.2 条件

Str与InsertStr非空

0<=InSertPos<=StringLen(Str) + 1



## 1.3方法

①先调MoveBackStr函数，移动字符

```c
OP_STATUS MoveBackStr(char *Str, const unsigned int Pos, const int MvLen)
```

​	Str为数移动主串的字符，Pos为要移动的位置，MvLen为移动的长度，值为InsertStr的长度

 

②调用CopyStrWhithoutTail函数，插入字串

```c
OP_STATUS CopyStrWhithoutTail(char *Str, const unsigned int Pos, const char *CpyStr)
```

Str为数移动主串的字符，Pos为要移动的位置，CpyStr为要插入的子串。

## 1.4 代码实现

**①MoveBackStr函数**

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



**②CopyStrWhithoutTail函数**

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



**③StrInsert函数**

```c
OP_STATUS StrInsert(char *Str, const unsigned int InSertPos, const char *InsertStr) {
	OP_STATUS Status = SUCCESS;
	char *TraStr = Str;
	unsigned int TraInSertPos = InSertPos;
	char *TraInserStr = InsertStr;
	unsigned int TraInsertLen = StringLen(TraInserStr);

	printf("StrInsert start\n");

	if (TraStr == NULL || TraInSertPos > StringLen(TraStr) + 1 || InsertStr == NULL) {
		Status = INVALID_PARAMETER;
		goto EXIT;
	}

	printf("TraInsertLen = %d\n", TraInsertLen);

	Status = MoveBackStr(TraStr, TraInSertPos, TraInsertLen);
	printf("TraStr = %s\n", TraStr);
	if (Status != SUCCESS) {
		goto EXIT;
	}

	Status = CopyStrWhithoutTail(TraStr, TraInSertPos, TraInserStr);
	printf("TraStr = %s\n", TraStr);

EXIT:
	printf("StrInsert end\n");
	return Status;
}
```



**测试用例代码：**

```c
OP_STATUS StrInsert(char *Str, const unsigned int InSertPos, const char *InsertStr) {
	OP_STATUS Status = SUCCESS;
	char *TraStr = Str;
	unsigned int TraInSertPos = InSertPos;
	char *TraInserStr = InsertStr;
	unsigned int TraInsertLen = StringLen(TraInserStr);

	printf("StrInsert start\n");

	if (TraStr == NULL || TraInSertPos > StringLen(TraStr) + 1 || InsertStr == NULL) {
		Status = INVALID_PARAMETER;
		goto EXIT;
	}

	printf("TraInsertLen = %d\n", TraInsertLen);

	Status = MoveBackStr(TraStr, TraInSertPos, TraInsertLen);
	printf("TraStr = %s\n", TraStr);
	if (Status != SUCCESS) {
		goto EXIT;
	}

	Status = CopyStrWhithoutTail(TraStr, TraInSertPos, TraInserStr);
	printf("TraStr = %s\n", TraStr);

EXIT:
	printf("StrInsert end\n");
	return Status;
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









