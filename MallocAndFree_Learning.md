# 空间申请（malloc）与释放（free）——C语言

[TOC]

# 1. malloc与free函数

**参考链接：**

[https://blog.csdn.net/qq_42565910/article/details/90346236?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522164905582216780265428895%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=164905582216780265428895&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-90346236.142^v5^pc_search_result_control_group,157^v4^control&utm_term=malloc%E5%87%BD%E6%95%B0&spm=1018.2226.3001.4187](https://blog.csdn.net/qq_42565910/article/details/90346236?ops_request_misc=%7B%22request%5Fid%22%3A%22164905582216780265428895%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=164905582216780265428895&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-90346236.142^v5^pc_search_result_control_group,157^v4^control&utm_term=malloc函数&spm=1018.2226.3001.4187)

 

**（1）头文件：**

```c
#include <malloc.h>
```

**（2）malloc函数原型**

​	返回的是一个void 类型的指针。

```c
extern void *malloc(unsigned int num_bytes);
```

 

**（3）free函数**

**①作用：**释放malloc与calloc申请的空间

**②形式：**free(malloc与calloc申请的空间返回的指针)

 

**例子：**

```c
//test malloc and free
void test03() {
	char *str = NULL;
	int i = 0;

	str = (char *)malloc(sizeof(char) * 3);

	str[0] = 'w';
	str[1] = 'e';
	str[2] = 'g';
    
	for (i = 0; i < 3; ++i) {
	printf("str[%d] = %c\n", i, str[i]);
	}
    
	free(str);
	str = NULL;
}
```

**结果：**

> str[0] = w
>
> str[1] = e
>
> str[2] = g

**（4）注意事项**

①使用了malloc函数申请了空间，为了避免内存泄漏，就要使用free函数释放空间，释放后并把指针置NULL。

②申请空间后的指针不能移动，不然释放失败。

③申请多少空间就使用多少空间，不能越界访问空间，不然会释放失败。

**例子：**

​	申请了两个字节的空间，却访问了第三个字节的空间，free释放str的时候没有办法去释放没有申请的空间，导致程序出错。

```c
void test03() {
	char *str = NULL;
	int i = 0;
    
	str = (char *)malloc(sizeof(char) * 2);//只申请了两个字节的空间
    
	str[0] = 'w';
	str[1] = 'e';
	str[2] = 'g';//越界访问第三个字节
    
	for (i = 0; i < 3; ++i) {
	printf("str[%d] = %c\n", i, str[i]);
	}
    
	free(str);
	str = NULL;
}
```


**结果：**

> 程序报错
