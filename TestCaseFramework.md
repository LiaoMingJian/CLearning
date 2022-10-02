# 测试用例框架——C语言

[toc]

# 1 宏定义

```c
static int TestNum = 0;
static int PassNum = 0;
static int FaildNum = 0;
```

# 2 初始化函数

```c
void InitNum(void) {
	TestNum = 0;
	PassNum = 0;
	FaildNum = 0;
}
```



# 3 测试的结果函数

```c
void TestResult(void) {
	printf("Print test result;\n");
	printf("TestNum = %d, PassNum = %d, FaildNum = %d\n", TestNum, PassNum, FaildNum);
}
```

# 4 状态测试函数

```c
OP_STATUS StatusTest(OP_STATUS Status1, OP_STATUS Status2) {
	TestNum++;

	printf("StatusTest:\n");
	if (Status1 == Status2) {
		printf("Test succeed!\n");
		PassNum++;
		return SUCCESS;
	} else {
		printf("%s test faild!\n", __func__);
		FaildNum++;
		return ERROR;
	}
} 
```

# 5  字符串的比较函数

```c
int StrCopmare(const char *Str1, const char *Str2) {
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
	printf("ret = %d\n", ret);
	printf("StrCopmare end\n");
	return ret;
}
```



```c
void StringCompareTest(const char *TestStr1, const char *NewStrRep) {
	int Res;
	char *TraTestStr1 = TestStr1;
	char *TraNewStrRep = NewStrRep;

    TestNum++;
	Res = StrCopmare(TraTestStr1, TraNewStrRep);
	
	if (Res == 0) {
		printf("%s test succeed!\n", __func__);
		PassNum++;
		return SUCCESS;
	}
	else {
		printf("%s test faild!\n", __func__);
		FaildNum++;
		return ERROR;
	}
}
```

# 6 值比较函数

```c
void ValueTest(const unsigned int Value01, const unsigned int Value02) {
	TestNum++;
    if (Value01 == Value02) {
		printf("%s test succeed!\n", __func__);
		PassNum++;
		return SUCCESS;
	}
	else {
		printf("%s test faild!\n", __func__);
		FaildNum++;
		return ERROR;
	}
}
```

























