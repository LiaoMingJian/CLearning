# 文件读写操作——C语言

[toc]

## 1.1 文件的读写

​	创建、打开、关闭文本文件或二进制文件。

## 1.2 打开文件

**(1)fopen**

```c
FILE *fopen(const char *fileName, const char * mode);
```

**(2)fopen_s**

​	文件打开成功返回0，打开失败返回非0

```c
int fopen_s(FILE **fp, const char *filename, const char * mode) 
```

## 1.3  文件操作的模式

**（1）普通文件**

模式	描述

r	打开一个已有的文本文件，允许读取文件。

w   打开一个文本文件，允许写入文件。如果文件不存在，则会创建一个新文件。在这里，您的程序会从文件的开头写入内容。如果文件存在，则该会被截断为零长度，重新写入。

a    打开一个文本文件，以追加模式写入文件。如果文件不存在，则会创建一个新文件。在这里，您的程序会在已有的文件内容中追加内容。

r+   打开一个文本文件，允许读写文件。

w+  打开一个文本文件，允许读写文件。如果文件已存在，则文件会被截断为零长度，如果文件不存在，则会创建一个新文件。

a+   打开一个文本文件，允许读写文件。如果文件不存在，则会创建一个新文件。读取会从文件的开头开始，写入则只能是追加模式。

**（2）二进制文件**

"rb", "wb", "ab", "rb+", "r+b", "wb+", "w+b", "ab+", "a+b"

**注意：**

​	当文件没有关闭的时候，文件指针fp在是指向读写的位置，继续读写的话，也相当于追加读写。

## 1.4 关闭文件

​	关闭文件使用fclose函数，函数的原型：

```c
int fclose( FILE *fp );
```

​	如果成功关闭文件，fclose( ) 函数返回零，如果关闭文件时发生错误，函数返回 EOF。这个函数实际上，会清空缓冲区中的数据，关闭文件，并释放用于该文件的所有内存。EOF 是一个定义在头文件 stdio.h 中的常量，为-1.

### 1.5 写入文件

**（1）把单个字符写入文件**

​	函数 fputc() 把参数 c 的字符值写入到 fp 所指向的输出流中。如果写入成功，它会返回写入的字符，如果发生错误，则会返回 EOF

```c
int fputc( char c, FILE *fp );
```

**例子：**

**注意：**路径需要有两个斜杠”//”进行转义，

```c
void TestWriteChar() {
​     FILE *fp = NULL;
​     int ErrFlag = -1;
​     char a = 'a';
    
​     ErrFlag = fopen_s(&fp, "D:\\TestFile\\TestFile03.txt", "w+");
​     if (ErrFlag == 0) {
​          printf("File open succeed\n");
​     } else {
​          printf("File open filed\n");
​     }
    
​     fputc(a, fp);
​     fclose(fp);
}
```

**结果：**

> a

**（2）把字符串写入文件**

​	函数 fputs() 把字符串 s 写入到 fp 所指向的输出流中。如果写入成功，它会返回一个非负值，如果发生错误，则会返回 EOF.

```c
int fputs( const char *s, FILE *fp );
```

**或者：**

```c
int fprintf(FILE *fp, const char *format)
```

**例子：**

```c
void TestWritStr() {
​     FILE *fp = NULL;
​     int ErrFlag = -1;
​     char str01[4] = "we\n";
​     char str02[4] = "go\n";
    
​     ErrFlag = fopen_s(&fp, "D:\\TestFile\\TestFile04.txt", "w+");
​     if (ErrFlag == 0 ) {
​          printf("File open succeed\n");
​     } else {
​          printf("File open filed\n");
​     }
    
​     fputs(str01, fp);
​     fprintf(fp, str02);
​     fclose(fp);
}
```

**结果：**

> we
>
> go

 

### 1.5.5 读文件

**（1）读单个字符**

​	fgetc() 函数从 fp 所指向的输入文件中读取一个字符。返回值是读取的字符，如果发生错误则返回 EOF。

```c
int fgetc( FILE * fp );
```

**（2）读字符串**

​	函数 fgets() 从 fp 所指向的输入流中读取 n - 1 个字符。它会把读取的字符串复制到缓冲区 buf，并在最后追加一个 null 字符来终止字符串。

​	如果这个函数在读取最后一个字符之前就遇到一个换行符 '\n' 或文件的末尾 EOF，则只会返回读取到的字符，包括换行符。

```c
char *fgets( char *buf, int n, FILE *fp );
```

或者：

```c
int fscanf_s(FILE *fp, const char *format, len);
```

​     len是指定的读取长度。

​	 函数来从文件中读取字符串，但是在遇到第一个空格和换行符时，它会停止读取。



**例子：**

> TestFile04.txt数据是：
>
> **let's go**
>
> **we go**

**代码：**

```c
void TestReadFile() {
​     FILE *fp;
​     int FileOpenFlag = -1;
​     char buff[20];
    
​     FileOpenFlag = fopen_s(&fp, "D:\\TestFile\\TestFile04.txt", "r+");
​     if (0 == FileOpenFlag) {
​          printf("File open succeed\n");
​     } else {
​          printf("File open filed\n");
​     }
    
​     fscanf_s(fp, "%s", buff, 10);
​     printf("buff = %s\n", buff);  

​     fgets(buff, 10, fp);
​     printf("buff = %s\n", buff);  

​     fgets(buff, 10, fp);
​     printf("buff = %s\n", buff);
​     fclose(fp);
}
```

**结果：**fscanf_s遇到第一个空格的时候停止读取，fgets读取后面剩下字符串，第二个fgets读取第二行的字符串。

> File open succeed
>
> buff = let's
>
> buff = go
>
>  
>
> buff = we go

 