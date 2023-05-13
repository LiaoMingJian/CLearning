# 哈希表——创建，查找结点——C语言描述

[toc]



# 0 测试用例框架

[https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22127137119%22%2C%22source%22%3A%22m0_59469991%22%7D](https://blog.csdn.net/m0_59469991/article/details/127137119?csdn_share_tail={"type"%3A"blog"%2C"rType"%3A"article"%2C"rId"%3A"127137119"%2C"source"%3A"m0_59469991"})

# 1 定义

​	先把key值存到表里面去，存的过程哈希表Hashkey与表里面的值（Key）一一对应，存表冲突时使用开放地址法解决。时间复杂度为O(1)，空间复杂度为O(n).



# 2 数据结构

​	增加平衡因子，表示为左子树减右子树的差值。

```c
#define EMPTY_FLAG           (-1)
#pragma pack(1)
typedef struct _HASH_TABLE {
	int *Table;
	int Num;
}HASH_TABLE;
#pragma pack()
```



# 2 初始化哈希表与查找

## （1）代码

```c
void HashTableInit(HASH_TABLE **HTable, int Num) {
	int i = 0;

	if (HTable == NULL) {
		return;
	}

	*HTable = (HASH_TABLE *)malloc(sizeof(HASH_TABLE));
	if (*HTable == NULL) {
		return;
	}

	(*HTable)->Num = Num;
	(*HTable)->Table = (int *)malloc(sizeof(int) * Num);
	if ((*HTable)->Table == NULL) {
		return;
	}

	for (i = 0; i < (*HTable)->Num; i++) {
		(*HTable)->Table[i] = EMPTY_FLAG;
	}
}


int Hash(HASH_TABLE *HTable, int Key) {
	return Key % (HTable->Num);
}


void InsertKey(HASH_TABLE *HTable, int Key) {
	int HashNum;

	HashNum = Hash(HTable, Key);
	while (HTable->Table[HashNum] != EMPTY_FLAG) {
		HashNum = (HashNum + 1) % HTable->Num;
	}

	HTable->Table[HashNum] = Key;
}

void InsertHash(HASH_TABLE *HTable, int *Arr, int Num) {
	int i = 0;

	for (i = 0; i < Num; i++) {
		InsertKey(HTable, Arr[i]);
	}
}


int SearchHash(HASH_TABLE *HTable, int Key) {
	int HashNum;

	if (HTable == NULL) {
		return -1;
	}

	HashNum = Hash(HTable, Key);

	while (HTable->Table[HashNum] != Key) {
		HashNum = (HashNum + 1) % HTable->Num;
		if ((HashNum == (HTable->Num - 1)) || (HTable->Table[HashNum] == EMPTY_FLAG)) {
			return -1;
		}
	}

	return HTable->Table[HashNum];
}
```



##  （2）测试用例

```c
void PrintHashTable(HASH_TABLE *HTable) {
	int i = 0;

	for (i = 0; i < HTable->Num; i++) {
		printf("HTable->Table[%d] = %d\n", i, HTable->Table[i]);
	}
}

/*TestSearchHash*/
void TestSearchHash(void) {
	/*Test01*/
	// {5, 1, 2, 3, 4}
	HASH_TABLE *HTable01 = NULL;
	int Arr01[] = { 1, 3, 5, 2, 4 };
	int Num01 = 5;
	int Key01 = 3;
	int Res01;
	int CmpRes01 = 3;

	/*Test02*/
	// {5, 1, 10, 3, 8}
	HASH_TABLE *HTable02 = NULL;
	int Arr02[] = { 1, 3, 5, 10, 8 };
	int Num02 = 5;
	int Key02 = 10;
	int Res02;
	int CmpRes02 = 10;

	/*Test03*/
	// {5, 1, 10, 3, 8}
	HASH_TABLE *HTable03 = NULL;
	int Arr03[] = { 1, 3, 5, 10, 8 };
	int Num03 = 5;
	int Key03 = 4;
	int Res03;
	int CmpRes03 = -1;

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	HashTableInit(&HTable01, Num01);
	InsertHash(HTable01, Arr01, Num01);
	PrintHashTable(HTable01);
	Res01 = SearchHash(HTable01, Key01);
	TestCmpRes(CmpRes01, Res01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	HashTableInit(&HTable02, Num02);
	InsertHash(HTable02, Arr02, Num02);
	PrintHashTable(HTable02);
	Res02 = SearchHash(HTable02, Key02);
	TestCmpRes(CmpRes02, Res02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	HashTableInit(&HTable03, Num03);
	InsertHash(HTable03, Arr03, Num03);
	PrintHashTable(HTable03);
	Res03 = SearchHash(HTable03, Key03);
	TestCmpRes(CmpRes03, Res03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}
```



## （3）**打印结果**

> -------Test start----------
>
>   
>
> -------Test 01----------
>
> HTable->Table[0] = 5
>
> HTable->Table[1] = 1
>
> HTable->Table[2] = 2
>
> HTable->Table[3] = 3
>
>  HTable->Table[4] = 4
>
>  
>
> -------Test 02----------
>
> HTable->Table[0] = 5
>
> HTable->Table[1] = 1
>
> HTable->Table[2] = 10
>
> HTable->Table[3] = 3
>
>  HTable->Table[4] = 8
>
>  
>
> -------Test 03----------
>
> HTable->Table[0] = 5
>
> HTable->Table[1] = 1
>
> HTable->Table[2] = 10
>
> HTable->Table[3] = 3
>
> HTable->Table[4] = 8
>
>   
>
> -------Test result----------
>
> Print test result;
>
> TestNum = 3, PassNum = 3, FaildNum = 0
