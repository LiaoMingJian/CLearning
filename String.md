# 字符串——创建，获取长度，复制，搜索——C语言描述

[toc]

# 1.字符串的存储结构

​	串的数据结构一般采用数组的形式，字符串为’\0’为表示结尾。

# 2操作字符串

​     创建，打印，获取长度，拷贝子串，搜索子串

**代码：**

```c
void OperateString(void) {
	LIST_STATUS Status;
	char Str1[] = "hello";
	int Str1Len;
	char *T = (char *)malloc(sizeof(Str1));

	Str1Len = StringLen(Str1);
	printf("Str1Len = 0x%x\n", Str1Len);

	Status = StrCopy(T, Str1);
	if (Status == SUCCESS) {
		printf("StrCopy successful!\n");
	}else {
		printf("StrCopy failed!\n");
	}
	
	printf("T = %s\n", T);
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
