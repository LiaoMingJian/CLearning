# 栈的作用之递归，波兰表达式——C语言描述

[toc]



## 1 斐波拉契数列

公式：f(0) = 0, f(1) = 1, f(n) = f(n - 1) + f(n - 2)；（n>2）

**（1）循环实现**

**代码：**

```c
void FabByArr(void) {
	int i;
	int RecArr[5];

	RecArr[0] = 0;
	RecArr[1] = 1;	

	for (i = 2; i < 5; ++i) {
		RecArr[i] = RecArr[i - 2] + RecArr[i - 1];	
	}

	for (i = 0; i < 5; ++i) {
		printf("RecArr[%d] = %d\n", i, RecArr[i]);
	}
}
```

**结果：**

> RecArr[0] = 0
>
> RecArr[1] = 1
>
> RecArr[2] = 1
>
> RecArr[3] = 2
>
> RecArr[4] = 3

 

**（2）递归**

​	每调用一层函数时，就入栈，那层函数实现后就出栈

**代码：**

```c
int FabRec(int i) {
	if (0 == i) {
		return 0;
	}
	else if (1 == i) {
		return 1; 
	}
	
	return FabRec(i - 2) + FabRec(i - 1);
}

void PrintFabByRec(void) {
	int i = 0;

	for (i = 0; i < 5; ++i) {
		printf("The %d value = %d\n", i, FabRec(i));
	}
}

```

**结果：**

> The 0 value = 0
>
> The 1 value = 1
>
> The 2 value = 1
>
> The 3 value = 2
>
> The 4 value = 3