# 递归——C语言描述

[toc]

# 1.1 要点：

①找出最小子结构

②弄清楚每一层这个**函数的作用**（一般是返回一个值），处理好当前这层的逻辑

③出当前这层与下一层之间的关系

# 1.2 例子

**（1）打印斐波拉契数列**

**①****递归法**

**分析：**1, 1, 2, 3, 5，每个数等于前两个数之和。

**方法：**每一层的返回值等于推给后面两层

**代码：**

**版本1：直接打印数列**

```c
int RecFab(int i) {
​     if (1 == i) {
​          return 1;
​     } else if (2 == i) {
​          return 1;
​     } 
​          
​     return RecFab(i - 2) + RecFab(i - 1);       
}

void FabByRec() {
​     int i = 0;
​     int n = 5;

​     for (i = 1; i <= 5; ++i) {
​          printf("RecFab(%d) = %d\n", i, RecFab(i));
​     }
}
```

**结果：**

> RecFab(i) = 0
>
> RecFab(i) = 1
>
> RecFab(i) = 2
>
> RecFab(i) = 3
>
> RecFab(i) = 4

 

**版本2：用递归的方法把数列存在一个数组里面**

**分析：**递归的三步法：退出条件，本层逻辑，下层逻辑。在处理当前层次逻辑的时候，数组进行填值。

**代码：**

```c
int RecFab02(int * const a, const int i) {
​     //1, 1, 2, 3, 5
​     //Exit condition
​     if (1 == i) {
​          a[i - 1] = 1;
​          return 1;
​     } else if (2 == i) {
​          a[i - 1] = 1;
​          return 1;
​     }
​    
​     //Finish operation in this level
​     a[i - 1] = RecFab02(a, i - 2) + RecFab02(a, i - 1);

​     //Next level
​     return RecFab02(a, i - 2) + RecFab02(a, i - 1);
}

void FabByRec02() {
​     int i = 5;
​     int a[5];

​     RecFab02(a, i);
    
​     for (i = 0; i < 5; ++i) {
​          printf("a[%d] = %d\n", i, a[i]);
​     }
}
```

**结果：**

> a[0] = 1
>
> a[1] = 1
>
> a[2] = 2
>
> a[3] = 3
>
> a[4] = 5

**②循环法**

**分析：**1, 1, 2, 3, 5，每个数等于前两个数之和。

**方法：**使用双指针法，不断往前面迭代

**代码：**

**版本1：**a[0], a[1]单独写

```c
void FabByLoop01() {
​     int i = 0;
​     int a[10];
​     int p = 0;
    
​     a[0] = 1;
​     a[1] = 1;
​     
​     //1,1,2,3
​     for (i = 2; i < 10; ++i) {        
​          a[i] = a[i - 2]+ a[i - 1];
​          printf("a[%d] = %d\n", i, a[i]);
​     }
}
```

**结果：**

> a[2] = 2
>
> a[3] = 3
>
> a[4] = 5

**版本2：**a[0], a[1]合入循环里面

```c
void FabByLoop02() {
​     int i = 0;
​     int a[5];
​     
​     //1,1,2,3,5
​     for (i = 0; i < 5; ++i) {         
​          if (0 == i) {
​              a[i] = 1;       
​          } else if (1 == i) {
​              a[i] = 1;
​          } else {
​              a[i] = a[i - 2] + a[i - 1];
​          }

​          printf("a[%d] = %d\n", i, a[i]);
​     }
}
```

**结果：**

> a[0] = 1
>
> a[1] = 1
>
> a[2] = 2
>
> a[3] = 3
>
> a[4] = 5

**（2）数组相加**

**分析：**1,2,3三个数相加

**方法：**每次返回下一层的值，这个值是这层的值i与下层值RecAdd01(i - 1)之和。一起加起来

```c
int RecAdd01(int i) {    
​     if (1 == i) {
​          return 1;
​     }
    
​     return i + RecAdd01(i - 1);
}

void AddValByRec01() {
​     int i = 3;

​     //1, 2, 3
​     printf("sum = %d\n", RecAdd01(i));
}
```

**结果：**

> sum = 6