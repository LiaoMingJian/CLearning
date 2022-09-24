# 字符串——创建，获取长度，复制，截取，搜索——C语言描述

[toc]

# 1.字符串的存储结构

​	串的数据结构一般采用数组的形式，字符串为’\0’为表示结尾。

# 2操作字符串

​     创建，打印，获取长度，拷贝子串，搜索子串

**代码：**

```c
void OperateString(void) {
	LIST_STATUS Status;
	char Str1[] = "hello199";
	char Str2[] = "hello200";
	int Str1Len;
	char *CpyStr = (char *)malloc(sizeof(Str1));
	int CmpResult;

	char *ConcatStr = (char *)malloc(sizeof(Str1) + sizeof(Str2) + 1);

	char *SubStr = (char *)malloc(sizeof(Str1));
	unsigned int Pos = 2;
	unsigned int SubLen = 3;
	
/*
	Str1Len = StringLen(Str1);
	printf("Str1Len = 0x%x\n", Str1Len);

	Status = StrCopy(CpyStr, Str1);
	if (Status == SUCCESS) {
		printf("StrCopy successful!\n");
	}else {
		printf("StrCopy failed!\n");
	}	
	printf("CpyStr = %s\n\n", CpyStr);

	if (CpyStr != NULL) {
		free(CpyStr);
		CpyStr = NULL;
	}

	CmpResult = StrCopmare(Str1, Str2);
	printf("CmpResult = %d\n", CmpResult);

	Status = StrConcat(ConcatStr, Str1, Str2);
	if (Status == SUCCESS) {
		printf("StrConcat successful!\n");
	}
	else {
		printf("StrConcat failed!\n");
	}
	printf("ConcatStr = %s\n", ConcatStr);	

	if (ConcatStr != NULL) {
		free(ConcatStr);
		ConcatStr = NULL;
	}
*/

	Status = SubString(SubStr, Str1, Pos, SubLen);
	if (Status == SUCCESS) {
		printf("SubString successful!\n");
	}
	else {
		printf("SubString failed!\n");
	}
	printf("SubStr = %s\n", SubStr);
}
```

# 3 获取串的长度

​     返回字符串的长度，不包括结尾字符’\0’.

**代码:**

```c
int StringLen(const char * const Str) {
	char *TraStr = Str;
	int StrLen = 0;

	printf("StringLen start\n");
	if (NULL == Str) {
		return 0;	
	}

	while (*TraStr != '\0') {
		StrLen++;
		TraStr++;
	}	

	printf("StringLen end\n");	
	return StrLen;
}
```

**结果：**

> StringLen start
>
> StringLen end
>
> Str1Len = 0x5



# 4 拷贝字符串

​		将字符串S拷贝给新串T

```c
StrCopy(char *T, char *S)
```



**代码：**

```c
LIST_STATUS StrCopy(char *T, char *S) {
	char *TraS = S;
	char *TraT = T;

	printf("StrCopy start\n");

	if (T == NULL || S == NULL ) {
		return ERROR;	
	}

	while (*TraS != '\0') {
		*TraT = *TraS;
		TraT++;
		TraS++;
	}

	*TraT = '\0';

	printf("StrCopy end\n");

	return SUCCESS;
}
```

**结果：**

> StringLen start
>
> StringLen end
>
> Str1Len = 0x5
>
> StrCopy start
>
> StrCopy end
>
> StrCopy successful!
>
> T = hello



# 5 比较两个字符串

```c
int StrComPare(const char *S1, const char *S2)
```

​     相等返回0，当S1 > S2时，返回值为1， 当S1 < S2 时，返回值为-1

两个字符串相等条件：两个字符串长度相等并且两个字符串每个位置对应的成员相等。

​     当两个字符串不相等时，给定两个串，S1 = “a1a2…an”, S2 = “b1b2…bm”，当满足以下条件之一时，S1 < S2.

（1）n < m，且ai = bi (i = 1,2,…,n)

（2）存在k <= min(m, n), 使得ai = bi(i=1,2,…,k-1)，ak < bk

代码：

```c
int StrCopmare(const char Str1[], const char Str2[]) {
	char *TraStr1 = Str1;
	char *TraStr2 = Str2;
	int ret;
	int Str1Len = StringLen(Str1);
	int Str2Len = StringLen(Str2);

	printf("StrCopmare start\n");

	printf("Str1 = %s\n", Str1);
	printf("Str2 = %s\n", Str2);

	while (*TraStr1 != '\0' || *TraStr2 != '\0') {
		if (*TraStr1 == *TraStr2) {
			TraStr1++;
			TraStr2++;
		} else {
			break;
		}
	}

	if (*TraStr1 == '\0' && *TraStr2 == '\0' && Str1Len == Str2Len) {
		ret = 0;
		goto EXIT;
	}	

	if (*TraStr1 == '\0' && Str1Len < Str2Len) {
		ret = -1;
		goto EXIT;
	}

	if (*TraStr1 != '\0' && *TraStr2 != '\0' && *TraStr1 < *TraStr2) {
		ret = -1;
		goto EXIT;
	}

	ret = 1;

EXIT:
	printf("StrCopmare end\n");
	return ret;
}
```

**结果：**

> StringLen start
>
> StringLen end
>
> Str1Len = 0x8
>
> StrCopy start
>
> StrCopy end
>
> StrCopy successful!
>
> T = hello199
>
>  
>
> StringLen start
>
> StringLen end
>
> StringLen start
>
> StringLen end
>
> StrCopmare start
>
> Str1 = hello199
>
> Str2 = hello200
>
> StrCopmare end
>
> CmpResult = -1

# 6  拼接两个字符串

```c
LIST_STATUS StrConcat(char *NewStr, const char *Str1, const char *Str2)
```

​     把字符串Str2拼接到Str1后面，并存到NewStr里面。

**代码：**

```c
LIST_STATUS StrConcat(char *NewStr, const char *Str1, const char *Str2) {
	char *TraNewStr = NewStr;
	char *TraStr1 = Str1;
	char *TraStr2 = Str2;
	
	printf("StrConcat start\n");
	if (TraNewStr == NULL || Str1 == NULL || Str2 == NULL) {
		return ERROR;
	}

	while (*TraStr1 != '\0') {
		*TraNewStr = *TraStr1;

		TraNewStr++;
		TraStr1++;
	}
	
	while (*TraStr2 != '\0') {
		*TraNewStr = *TraStr2;

		TraNewStr++;
		TraStr2++;
	}

	*TraNewStr = '\0';
	
	printf("StrConcat end\n");
	return SUCCESS;
}
```



**结果：**

> StringLen start
>
> StringLen end
>
> Str1Len = 0x8
>
> StrCopy start
>
> StrCopy end
>
> StrCopy successful!
>
> T = hello199
>
>  
>
> StringLen start
>
> StringLen end
>
> StringLen start
>
> StringLen end
>
> StrCopmare start
>
> Str1 = hello199
>
> Str2 = hello200
>
> StrCopmare end
>
> CmpResult = -1
>
> StrConcat start
>
> StrConcat end
>
> StrConcat successful!
>
> ConcatStr = hello199hello200



# 7 截取字符串

```c
LIST_STATUS SubString(char *Sub, const char *Str, const unsigned int Pos, const unsigned int SubLen)
```

​	用Sub返回串Str的第Pos个字符起长度为SubLen的字串

入参应该满足条件如下:其中“StrLen(Str) – Pos + 1”中“+ 1”是要把Pos的字符也算进去

1 <= Pos <= StrLen(Str1)

0 <= SubLen <= StrLen(Str) – Pos + 1

**代码：**

```c
LIST_STATUS SubString(char *Sub, const char *Str, const unsigned int Pos, const unsigned int SubLen) {
	char *TraSub = Sub;
	char *TraStr = Str;
	unsigned int Index = 0;

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
	for (Index = 0; Index < Pos; ++Index) {
		TraStr++;
	}

	/*Copy Str into Sub, lenth is SubLen*/
	for (Index = 0; Index < SubLen; ++Index) {
		*TraSub = *TraStr;
		TraStr++;
		TraSub++;
	}

	*TraSub = '\0';
	
	printf("SubString end\n");
	return SUCCESS;
}
```



**结果：**

> SubString start
>
> StringLen start
>
> StringLen end
>
> StringLen start
>
> StringLen end
>
> SubString end
>
> SubString successful!
>
> SubStr = llo
