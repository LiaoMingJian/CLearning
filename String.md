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
