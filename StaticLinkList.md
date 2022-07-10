###  线性表的链式存储结构——静态链表

[toc]



# 1 静态链表的存储结构

```c
#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			10

typedef int ElemType;
typedef int LIST_STATUS;
typedef struct {
	ElemType Data;
	int Cur;
}StNode;
```

 

​	用数组的方式实现链表操作。该结构体用Cur代替链表的指针。

​	数组的第一个元素和最后一个元素，作为特殊的元素处理，不存储数据。数组最后一个元素相当于单链表的头结点，该元素的下标相当于单链表的头指针。数组的第一元素的Cur值存储的是备用链表（空闲空间）的第一个下标。当数组第一个元素的Cur为0时，说明已无空闲空间。

​	其它每个结点的Cur存储的是下一个结点的下标。

## **（****1****）头结点与头指针**

​	如下图，数组的最后一个元素的下标（999）相当于单链表的头指针，这个元素相当于单链表的头结点，它的Cur存的是第一个有数值的结点下标（下图是下标1）。

​	如下图所示，一共有数组有1000个元素，数组存有数据的有6个结点，数组的最后一个元素是头结点，它的Cur存储的是数组第一个有数据的结点（下图为下标1），数组第一个元素Cur值存储的是备用链表空闲空间的第一个下标（下图是下标7）.

![img](file:///C:/Users/74140/AppData/Local/Temp/msohtmlclip1/01/clip_image002.jpg)

 

## **（****2****）空链表**

当头结点指向0时，即数组最后一个元素的Cur存的是0时，该静态链表为空链表，如下图所示。

![img](file:///C:/Users/74140/AppData/Local/Temp/msohtmlclip1/01/clip_image004.jpg)

 

 

# 2 操作静态链表

​    创建，打印静态链表，增加减少结点。

**代码：**

```c
/*StaticLinkList*/
LIST_STATUS OperatorStaticLinkList(void) {
	LIST_STATUS Status;
	StNode SL[MAXSIZE];
	int StNodeNum = 5;
	int AddIndex = 3;
	int AddData = 25;
	int DeleteIndex = 1;
	
	Status = CreateStaticLinkList(SL, StNodeNum);
	if (SUCCESS == Status) {
		printf("CreateStaticLinkList succeed!\n");
	} else {
		printf("CreateStaticLinkList failed!\n");
	}

	PrintStaticArr(SL);
	StaticLinkLenth(SL);
	PrintStaticLinkList(SL);

	
	Status = AddStaticLinkListNode(SL, AddIndex, AddData);
	if (SUCCESS == Status) {
		printf("AddStaticLinkListNode succeed!\n");
	}
	else {
		printf("AddStaticLinkListNode failed!\n");
	}
		
	/*
	Status = DeleteStaticLinkListNode(SL, DeleteIndex);
	if (SUCCESS == Status) {
		printf("DeleteStaticLinkListNode succeed!\n");
	}
	else {
		printf("DeleteStaticLinkListNode failed!\n");
	}
	*/

	PrintStaticArr(SL);
	StaticLinkLenth(SL);
	PrintStaticLinkList(SL);
}
```



# 3 创建静态链表

```c
LIST_STATUS CreateStaticLinkList(StNode SL[], int StNodeNum)
```

​     创建静态链表，数组长度为10，其中有数据的结点个数为StNodeNum。

**要点：**

①  构建静态链表的时候要保证数组第一个元素的cur要等于备用链表第一个元素的下标，

②  数组最后一个元素的Cur要等于数组第一个有数据元素的下标。

③  有数据的最后一个元素的Cur为0，相当于单链表指向NULL。

 

**代码：**

```c
LIST_STATUS CreateStaticLinkList(StNode SL[], int StNodeNum) {
	int i = 0;

	printf("CreateStaticLinkList start\n");

	if (NULL == SL || 0 == SL[0].Cur) {
		return ERROR;
	}

	for (i = 0; i < MAXSIZE - 1 ; ++i) {		
		if (i > 0 && i < StNodeNum + 1) {
			SL[i].Data = i;
		}

		if (0 == i) {
			SL[i].Cur = StNodeNum + 1;
		} else {
			SL[i].Cur = i + 1;
		}

	}
	
	SL[StNodeNum].Cur = 0;

	SL[MAXSIZE - 1].Cur = 1;
	
	printf("CreateStaticLinkList end\n");

	return SUCCESS;
}
```

**结果：**

> CreateStaticLinkList start
>
> CreateStaticLinkList end
>
> CreateStaticLinkList succeed!
>
> PrintStaticArr start
>
> SL[0].Data = -858993460, SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> SL[6].Data = -858993460, SL[6].Cur = 7
>
> SL[7].Data = -858993460, SL[7].Cur = 8
>
> SL[8].Data = -858993460, SL[8].Cur = 9
>
> SL[9].Data = -858993460, SL[9].Cur = 1
>
> PrintStaticArr end
>
> StaticLinkLenth = 5
>
> PrintStaticLinkList start
>
> SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> PrintStaticLinkList end



# 4 打印静态链表

## (1)**以数组的形式：**

**代码：**

```c
LIST_STATUS PrintStaticArr(const StNode SL[]) {
	int i = 0;

	printf("PrintStaticArr start\n");

	for (i = 0; i < MAXSIZE; ++i) {
		printf("SL[%d].Data = %d, SL[%d].Cur = %d\n", i, SL[i].Data, i, SL[i].Cur);	
	}

	printf("PrintStaticArr end\n");
}
```

**结果：**

> PrintStaticArr start
>
> SL[0].Data = -858993460, SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> SL[6].Data = -858993460, SL[6].Cur = 7
>
> SL[7].Data = -858993460, SL[7].Cur = 8
>
> SL[8].Data = -858993460, SL[8].Cur = 9
>
> SL[9].Data = -858993460, SL[9].Cur = 1
>
> PrintStaticArr end



## （2）以链表的形式

**代码：**

```c
LIST_STATUS PrintStaticLinkList(const StNode SL[]) {
	int i = 0;

	printf("PrintStaticLinkList start\n");

	if (NULL == SL || 0 == SL[0].Cur || 0 == SL[MAXSIZE - 1].Cur) {
		return ERROR;
	}

	if (0 == i) {
		printf("SL[%d].Cur = %d\n", i, SL[i].Cur);
	}

	i = SL[MAXSIZE - 1].Cur;

	while (i < MAXSIZE - 1) {
		if (0 != SL[i].Cur) {
			printf("SL[%d].Data = %d, SL[%d].Cur = %d\n", i, SL[i].Data, i, SL[i].Cur);
		} else {
			printf("SL[%d].Data = %d, SL[%d].Cur = %d\n", i, SL[i].Data, i, SL[i].Cur);
			break;
		}

		i = SL[i].Cur;
	}

	printf("PrintStaticLinkList end\n");
}

```

**结果：**

> PrintStaticLinkList start
>
> SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> PrintStaticLinkList end

# 5 静态链表——获取长度

​	获取静态链表的长度。不包含头结点

```c
int StaticLinkLenth(const StNode SL[]) {
	int i = 0;
	int SLLenth = 0;
	
	if (NULL == SL || 0 == SL[MAXSIZE - 1].Cur) {
		return 0;
	}
	
	i = SL[MAXSIZE - 1].Cur;

	/*The Cur is the judgement standard*/
	/*
	while (SL[i].Cur != 0) {
		SLLenth++;
		i = SL[i].Cur;
	}
	SLLenth++;
	*/

	/*The following is the judgment standard*/
	while (i != 0) {
		SLLenth++;
		i = SL[i].Cur;
	}

	printf("StaticLinkLenth = %d\n", SLLenth);

	return SLLenth;
}

```

**结果：**

> CreateStaticLinkList start
>
> CreateStaticLinkList end
>
> CreateStaticLinkList succeed!
>
> StaticLinkLenth = 5
>
> PrintStaticLinkList start
>
> SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> PrintStaticLinkList end

# 5 静态链表——增加结点

```c
LIST_STATUS AddStaticLinkListNode(const StNode SL[], const int AddIndex, ElemType AddData)
```



​	在静态链表第AddIndex个结点位置（不包含头结点）插入一个元素AddData.

​	在静态链表第三个位置插入元素AddData，如下图，在乙丁之间插入丙。

![增加结点](D:\我的学习\学习笔记\C\Markdown\线性表\线性表静态链表\增加结点.jpg)

**方法：**

①   先判断数组里面有没有备用的链表空间，即判断SL[0].Cur是否为0，若存在则返回备用链表的下标，并将新的备用下标赋值给SL[0].Cur，不存在就返回0。

②   将AddData赋给备用的空间元素中

③   找到AddIndex前一个和后一个元素，对它们的Cur进行改变

**代码：**

```c
int IfSLMalloc(StNode SL[]) {
	int Index = SL[0].Cur;

	if (Index) {
		SL[0].Cur = SL[Index].Cur;
	}

	return Index;
}
```

**代码：**

```c
LIST_STATUS AddStaticLinkListNode(StNode SL[], const int AddIndex, const ElemType AddData) {
	LIST_STATUS SLStatus = SUCCESS;
	int SLMallocIndex;
	int LoopIndex = 0, SLIndex = 0;

	printf("AddStaticLinkListNode start\n");

	if ( NULL == SL || AddIndex < 1 || AddIndex > (StaticLinkLenth(SL) + 1) ) {
		printf("Invalid AddIndex");
		return ERROR;
	}

	/*
	if ( StaticLinkLenth(SL) == (MAXSIZE - 2) ) {
		printf("Space is full");
		return ERROR;
	}
	*/

	SLIndex = MAXSIZE - 1;

	SLMallocIndex = IfSLMalloc(SL);

	if (SLMallocIndex) {		
		SL[SLMallocIndex].Data = AddData;

		/*Move to the previous of the AddIndex*/
		for (LoopIndex = 0; LoopIndex < AddIndex - 1; ++LoopIndex) {
			SLIndex = SL[SLIndex].Cur;
		}
		
		/*Modify Cur*/
		SL[SLMallocIndex].Cur = SL[SLIndex].Cur;
		SL[SLIndex].Cur = SLMallocIndex;

		printf("AddStaticLinkListNode success\n");
		SLStatus = SUCCESS;
	}
	else {
		printf("Space is full");
		SLStatus = ERROR;
	}	

	printf("AddStaticLinkListNode end\n");
	return SLStatus;
}

```

**结果：**

> CreateStaticLinkList start
>
> CreateStaticLinkList end
>
> CreateStaticLinkList succeed!
>
> PrintStaticArr start
>
> SL[0].Data = -858993460, SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> SL[6].Data = -858993460, SL[6].Cur = 7
>
> SL[7].Data = -858993460, SL[7].Cur = 8
>
> SL[8].Data = -858993460, SL[8].Cur = 9
>
> SL[9].Data = -858993460, SL[9].Cur = 1
>
> PrintStaticArr end
>
> StaticLinkLenth = 5
>
> PrintStaticLinkList start
>
> SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> PrintStaticLinkList end



# 6 静态链表——删除结点

```c
LIST_STATUS DeleteStaticLinkListNode(StNode SL[], const int DeleteIndex)
```



​	在静态链表SL中删除第DeleteIndex个的元素。

​	删除第一个结点。如下图，删除甲。

![删除结点](D:\我的学习\学习笔记\C\Markdown\线性表\线性表静态链表\删除结点.jpg)

**方法：**

①   先判断DeleteIndex是否合法，不能小于1，不能大于静态链表的长度。

②   找到DeletIndex的前面一个元素

③   处理Cur, 使前一个元素的Cur值等于DeleteIndex的Cur值

④   处理SL[0].Cur，DeleteIndex的元素被删除后，DeleteIndex作为备用链表的空闲空间的第一个元素。

**代码：**

```c
int FreeSL(StNode SL[], int FreeIndex) {
	SL[FreeIndex].Cur = SL[0].Cur;
	SL[0].Cur = FreeIndex;
}
```

**代码：**

```c
LIST_STATUS DeleteStaticLinkListNode(StNode SL[], const int DeleteIndex) {
	int LoopIndex = 1;
	int SLIndex = MAXSIZE - 1;

	printf("DeleteStaticLinkListNode start\n");

	if (NULL == SL || DeleteIndex < 1 || DeleteIndex > StaticLinkLenth(SL)) {
		printf("Invalid DeleteIndex!\n");
		return ERROR;
	}

	/*Move to the Previous Index of AddIndex*/
	for (LoopIndex = 1; LoopIndex <= DeleteIndex - 1; ++LoopIndex) {
		SLIndex = SL[SLIndex].Cur;	
	}

	/*Modify Cur*/
	SL[SLIndex].Cur = SL[LoopIndex].Cur;

	FreeSL(SL, LoopIndex);

	printf("DeleteStaticLinkListNode end\n");

	return SUCCESS;
}

```

**结果：**

> CreateStaticLinkList start
>
> CreateStaticLinkList end
>
> CreateStaticLinkList succeed!
>
> PrintStaticArr start
>
> SL[0].Data = -858993460, SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> SL[6].Data = -858993460, SL[6].Cur = 7
>
> SL[7].Data = -858993460, SL[7].Cur = 8
>
> SL[8].Data = -858993460, SL[8].Cur = 9
>
> SL[9].Data = -858993460, SL[9].Cur = 1
>
> PrintStaticArr end
>
> StaticLinkLenth = 5
>
> PrintStaticLinkList start
>
> SL[0].Cur = 6
>
> SL[1].Data = 1, SL[1].Cur = 2
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> PrintStaticLinkList end
>
>  
>
> DeleteStaticLinkListNode start
>
> StaticLinkLenth = 5
>
> DeleteStaticLinkListNode end
>
> DeleteStaticLinkListNode succeed!
>
> PrintStaticArr start
>
> SL[0].Data = -858993460, SL[0].Cur = 1
>
> SL[1].Data = 1, SL[1].Cur = 6
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> SL[6].Data = -858993460, SL[6].Cur = 7
>
> SL[7].Data = -858993460, SL[7].Cur = 8
>
> SL[8].Data = -858993460, SL[8].Cur = 9
>
> SL[9].Data = -858993460, SL[9].Cur = 2
>
> PrintStaticArr end
>
> StaticLinkLenth = 4
>
> PrintStaticLinkList start
>
> SL[0].Cur = 1
>
> SL[2].Data = 2, SL[2].Cur = 3
>
> SL[3].Data = 3, SL[3].Cur = 4
>
> SL[4].Data = 4, SL[4].Cur = 5
>
> SL[5].Data = 5, SL[5].Cur = 0
>
> PrintStaticLinkList end
