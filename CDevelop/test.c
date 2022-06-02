#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "test.h"

//Test overflow access in malloc
void test01() {
	char *str = NULL;
	int i = 0;

	str = (char *)malloc(sizeof(char) * 2);

	str[0] = 'w';
	str[1] = 'e';
	str[2] = 'g';

	for (i = 0; i < 3; ++i) {
		printf("str[%d] = %c\n", i, str[i]);
	}

	free(str);
	str = NULL;
}

//Test combine with "++" and "*"
void test02() {
	char str1[6] = "we go";
	char *str = NULL;
	int i = 0;

	str = (char *)malloc(strlen(str1) + 1);
	
	strcpy_s(str, strlen(str1) + 1, str1);

	printf("str = %s\n", str);

	for (i = 0; i < strlen(str) + 1; ++i) {
		printf("before, str[%d] = %c\n", i, str[i]);
	}

	//while (*str != '\0') {
	//	//printf();
	//	printf("*(str++) = %c\n", *(str++));
	//	getchar();
	//}

	free(str);	
	str = NULL;
}

//test malloc
void test03() {
	//char str1[6] = "we go";
	char *str = NULL;
	int i = 0;

	str = (char *)malloc(sizeof(char) * 2);

	str[0] = 'w';
	str[1] = 'e';
	str[2] = 'g';

	//printf("str = %s\n", str);

	for (i = 0; i < 3; ++i) {
		printf("str[%d] = %c\n", i, str[i]);
	}
	
	free(str);
	str = NULL;
}

//test printf with %s
void test04() {
	char str1[3] = "we";
	char str2[2] = {'g', '0'};
	char str3[4] = {'w', 'e'};

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	printf("str3 = %s\n", str3);
}

//test %d, %c
void test05() {
	char ch1 = 'a';
	int a = 65;
	double b = 1.3;
	
	printf("ch1 = %c\n", ch1);
	printf("ch1 = %d\n", ch1);

	printf("a = %d\n", a);
	printf("a = %c\n", a);

	//printf("b = %.2f\n", b);
	//printf("b = %d\n", b);
}

//test %d, %f
void test06() {
	int a = 65;
	double b = 1.3;

	printf("a = %d\n", a);
	printf("a = %.2f\n", a);

	printf("b = %.2f\n", b);
	printf("b = %d\n", b);
}

//test %c, %s
void test07() {
	char ch1 = 'w';
	char str2[3] = "go";

	printf("ch1 = %c\n", ch1);
	printf("str2[0] = %c\n", str2[0]);

	printf("ch1 = %s\n", &ch1);
	printf("str2 = %s\n", str2);
}

//test strcpy_s
void test08() {
	char str1[6] = "we go";
	char *str = NULL;
	int i = 0;

	str = (char *)malloc(sizeof(str1));

	strcpy_s(str, sizeof(str1), str1);

	printf("str = %s\n", str);

	for (i = 0; i < sizeof(str1); ++i) {
		printf("str[%d] = %c\n", i, str[i]);
	}

	free(str);
	str = NULL;
}

//test strcpy_s overflow
void test09() {
	char str1[6] = "we go";
	char str2[2];

	strcpy_s(str2, sizeof(str1), str1);

	printf("str = %s\n", str2);	
}

void PointFunc() {
	int i = 0;
	char str01[4] = "we\n";
	char str02[4] = "go\n";
	int str[2] = { str01, str02 };

	for (i = 0; i < sizeof(str) / sizeof(str[0]); ++i) {
		printf("str[%d] = %s\n", i, str[i]);
	}
}

void testGetchar() {
	char a;
	a = getchar();

	putchar(a);
	printf("\n");
}

void testGets() {
	char str[3];

	gets(str);
	puts(str);

	printf("\n");
}

void TestWriteChar() {
	FILE *fp = NULL;
	int ErrFlag = -1;
	char a = 'a';

	ErrFlag = fopen_s(&fp, "D:\\TestFile\\TestFile03.txt", "w+");
	if (ErrFlag == 0) {
		printf("File open succeed\n");
	}
	else {
		printf("File open filed\n");
	}

	fputc(a, fp);
	fclose(fp);
}

void TestWritStr() {
	FILE *fp = NULL;
	int ErrFlag = -1;
	
	char str01[4] = "we\n";
	char str02[4] = "go\n";

	ErrFlag = fopen_s(&fp, "D:\\TestFile\\TestFile04.txt", "w+");
	if (ErrFlag == 0 ) {
		printf("File open succeed\n");
	} else {
		printf("File open filed\n");
	}

	fputs(str01, fp);
	fprintf(fp, str02);

	fclose(fp);
}

void TestWritStr02() {
	FILE *fp = NULL;
	int ErrFlag = -1;
	int i = 0; 
	char str01[10] = "let's go\n";
	char str02[7] = "we go\n";
	int str[2] = {str01, str02};

	ErrFlag = fopen_s(&fp, "D:\\TestFile\\TestFile07.txt", "w+");
	if (ErrFlag == 0) {
		printf("File open succeed\n");
	}
	else {
		printf("File open filed\n");
	}
	
	fputs(str[0], fp);
	printf("str[0] = %s\n", str[0]);
	fclose(fp);

	ErrFlag = fopen_s(&fp, "D:\\TestFile\\TestFile07.txt", "a");
	if (ErrFlag == 0) {
		printf("File open succeed\n");
	}
	else {
		printf("File open filed\n");
	}

	fputs(str[1], fp);
	printf("str[1] = %s\n", str[1]);
	fclose(fp);

	/*
	for (i = 0; i < sizeof(str) / sizeof(str[0]); ++i) {
		printf("Write str[%d] = %s\n", i, str[i]);
		fputs(str[i], fp);
	}
	*/
	
}

void TestReadFile() {
	FILE *fp;
	int FileOpenFlag = -1;
	char buff[20];
	int a = EOF;
	FileOpenFlag = fopen_s(&fp, "D:\\TestFile\\TestFile04.txt", "r+");
	if (0 == FileOpenFlag) {
		printf("File open succeed\n");
	} else {
		printf("File open filed\n");
	}

	fscanf_s(fp, "%s", buff, 10);
	printf("buff = %s\n", buff);	
	fgets(buff, 10, fp);
	printf("buff = %s\n", buff);	
	fgets(buff, 10, fp);
	printf("buff = %s\n", buff);
	
	fclose(fp);
}

void TestCreateLink01() {
	typedef struct Node{
		int Date;
		struct Node *Next;
	}MyNode;

	//Node N1, N2, N3;		
	MyNode N1;
	MyNode N2;
	MyNode N3;
	MyNode *PN = NULL;

	N1.Date = 1;
	N1.Next = &N2;
	N2.Date = 2;
	N2.Next = &N3;
	N3.Date = 3;
	N3.Next = NULL;	

	PN = &N1;
	while (PN != NULL) {
		printf("Node.Date = %d\n", PN->Date);
		PN = PN->Next;
	}
}

void TestCreateLink02() {
	typedef struct MyNode {
		int Data;
		struct MyNode *Next;
	}Node;

	Node N3 = {3, NULL};
	Node N2 = {2, &N3};
	Node N1 = {1, &N2};
	Node *PN = NULL;

	printf("Link:\n");
	for (PN = &N1; PN != NULL; PN = PN->Next) {		
		printf("Node.Data = %d\n", PN->Data);	
	}
}

void OperateLink() {
	MyNode N3 = { 3, NULL };
	MyNode N2 = { 2, &N3 };
	MyNode N1 = { 1, &N2 };
	MyNode *PN = NULL;	
	MyNode *PNReturnHeadNode = NULL;
	MyNode HeadNode = {0, NULL};
	MyNode TailNode = { 4, NULL };
	MyNode MiddleNode = {23, NULL};
	int DeleteDate = 2;
	
	//Print link
	printf("Print the created link:\n");
	for (PN = &N1; PN != NULL; PN = PN->Next) {
		printf("Node.Data = %d\n", PN->Data);
	}
	
	//Add head node
	//PNReturnHeadNode = AddHeadNode(&N1, &HeadNode);

	//Add tail node
	//PNReturnHeadNode = AddTailNode(&N1, &TailNode);

	//Add middle node
	PNReturnHeadNode = TestAddMiddleNode(&N1, &N2, &MiddleNode);

	//Delete head node
	//PNReturnHeadNode = DeleteHeadNode(&N1);
	
	//Delete tail node
	//PNReturnHeadNode = DeleteTailNode(&N1);
	
	//Delete middle node
	//PNReturnHeadNode = DeletMiddleNode(&N1, DeleteDate);

	//Reverse link
	//PNReturnHeadNode = ReverseLink(&N1);

	//Printf link
	if (NULL != PNReturnHeadNode) {
		printf("Operate succeed!\n");
		printf("Print operated link:\n");
		for (PN = PNReturnHeadNode; PN != NULL; PN = PN->Next) {
			printf("Node.Data = %d\n", PN->Data);
		}
	} else {
		printf("Operate filed!\n");
	}
}

MyNode* AddHeadNode(MyNode *LNode, MyNode *HeadNode) {
	//Judge node
	if (NULL == LNode) {
		if (NULL == HeadNode) {
			return NULL;
		} else {		
			return HeadNode;
		}
	}
	
	//Add head node
	HeadNode->Next = HeadNode;

	return HeadNode;
}

MyNode* AddTailNode(MyNode *LNode, MyNode *TailNode) {
	MyNode *PN = NULL;

	//Judge node
	if (NULL == LNode) {
		if (NULL == TailNode) {
			return NULL;
		} else {
			return TailNode;
		}
	}

	//Move PN to N3
	for (PN = LNode; PN->Next != NULL; PN = PN->Next) {
	}

	//Add N4
	if (PN->Next == NULL) {
		PN->Next = TailNode;
		PN->Next->Next = NULL;
	}

	return LNode;
}

MyNode* TestAddMiddleNode(MyNode *LNode, MyNode *PreNode, MyNode *MiddleNode) {
	MyNode *PN = NULL;
	MyNode *PNTemp = NULL;

	//Judge
	if (NULL == LNode) {
		return MiddleNode;
	}

	//Move PN to PreNode
	for (PN = LNode; PN->Next != PreNode; PN = PN->Next) {
	}

	//Add MiddleNode
	if (PN->Next == PreNode) {
		PNTemp = PN->Next;
		PN->Next = MiddleNode;
		PN->Next->Next = PNTemp;
	}
}

MyNode* DeleteHeadNode(MyNode *LNode) {
	MyNode *PNRt = NULL;	
	
	//Judge LNode
	if (LNode == NULL) {
		return NULL;	
	} else if(LNode->Next == NULL) {
		return LNode;
	} 	

	//Delete head node
	PNRt = LNode->Next;
	LNode->Next = NULL;
	
	return PNRt;
}

MyNode* DeleteTailNode(MyNode *LNode) {
	MyNode *PNtemp = LNode;	

	//Judge LNode
	if (NULL == LNode ) {
		return NULL;
	} else if(NULL == LNode->Next) {
		return LNode;
	}
	
	//Move PNRt to N2
	for (PNtemp = LNode; PNtemp->Next->Next != NULL; PNtemp = PNtemp->Next) {
	}
	
	//Delete tail node
	PNtemp->Next = NULL;
	
	return LNode;
}

MyNode* DeletMiddleNode(MyNode *LNode, int DeleteDate) {
	MyNode *PN = LNode;
	MyNode *PNTemp = NULL;

	//Judge node
	if (NULL == LNode) {
		return NULL;
	}else if (NULL == LNode->Next) {
		return LNode;
	}
	
	//Move PN to N1
	for (PN = LNode; PN->Next->Data != DeleteDate; PN = PN->Next) {	
	}
	
	//Delete N2
	PNTemp = PN->Next;
	PN->Next = PN->Next->Next;
	PNTemp->Next = NULL;
	
	return LNode;
}

MyNode* ReverseLink(MyNode *LNode) {
	MyNode *PCur = NULL;
	MyNode *PNext = NULL;
	MyNode *PTemp = NULL;

	if (NULL == LNode) {
		return NULL;
	} else if (NULL == LNode->Next) {
		return LNode;
	}

	PCur = NULL;
	PNext = LNode;	
	while (PNext != NULL) {
		PTemp = PNext->Next;		
		//Reverse
		PNext->Next = PCur;
		//Iterate
		PCur = PNext;
		PNext = PTemp;		
	}

	return PCur;
}

void Rec() {
	int a[3] = {1, 2, 3};
	//Add 3 numbers a[0], a[1], a[2]
	int p;
	int q;
	int i;
	int sum;

	//origin 
	p = a[0];
	q = a[1];
	
	//cycle
	sum = p + q;

	//iterte
	p = sum;	
	q = a[2];//q must be next element 

	for (i = 0, p = 0; i < 3; ++i) {
		q = a[i];//iterate

		sum = p + q;

		p = sum;		
	}

	for (i = 0, p = 0; i < 3; ++i) {
		q = a[i];//iterate

		p += q;//大鱼吃小鱼的意向，迭代与循环体结合
	}

	for (i = 0, p = 0; i < 3; ++i) {
		q = a[i];//iterate

		p += q;//大鱼吃小鱼的意向，迭代与循环体结合
	}

	//数组的最后简化版本
	for (i = 0, p = 0; i < 3; ++i) {
		p += a[i];//大鱼吃小鱼的意向，迭代与循环体结合
	}
}

void FabByLoop01() {
	int i = 0;
	int a[5];
	int p = 0;
	a[0] = 1;
	a[1] = 1;
	
	//1,1,2,3,5
	for (i = 2; i < 5; ++i) {		
		a[i] = a[i - 2]+ a[i - 1];
		printf("a[%d] = %d\n", i, a[i]);
	}
}

void FabByLoop02() {
	int i = 0;
	int a[5];
	
	//1,1,2,3,5
	for (i = 0; i < 5; ++i) {		
		if (0 == i) {
			a[i] = 1;		
		} else if (1 == i) {
			a[i] = 1;
		} else {
			a[i] = a[i - 2] + a[i - 1];
		}

		printf("a[%d] = %d\n", i, a[i]);
	}
}

int RecFab(int i) {
	if (1 == i) {
		return 1;
	} else if (2 == i) {
		return 1;
	} 
		
	return RecFab(i - 2) + RecFab(i - 1);		
}

void FabByRec() {
	int i = 0;
	int n = 5;
	for (i = 1; i <= 5; ++i) {
		printf("RecFab(%d) = %d\n", i, RecFab(i));
	}
}

int RecFab02(int * const a, const int i) {
	//1, 1, 2, 3, 5
	//Exit condition
	if (1 == i) {
		a[i - 1] = 1;
		return 1;
	} else if (2 == i) {
		a[i - 1] = 1;
		return 1;
	}
	
	//Finish operation in this level
	a[i - 1] = RecFab02(a, i - 2) + RecFab02(a, i - 1);

	//Next level
	return RecFab02(a, i - 2) + RecFab02(a, i - 1);
}

void FabByRec02() {
	int i = 5;
	int a[5];

	RecFab02(a, i);

	for (i = 0; i < 5; ++i) {
		printf("a[%d] = %d\n", i, a[i]);
	}
}

int  RecAdd01(int i) {	
	if (1 == i) {
		return 1;
	}

	return i + RecAdd01(i - 1);
}

void AddValByRec01() {
	int i = 3;

	//1, 2, 3
	printf("sum = %d\n", RecAdd01(i));
}

//Finsh once add
int RecAdd02(int sum, const int i) {
	//Exit condition
	if (1 == i) {
		return 1;	
	}

	//Finish add in this level
	sum += i;

	return sum + RecAdd02(sum, i - 1);//Next level
}

void AddValByRec02() {
	int i = 3;
	int sum = 0;

	//1, 2, 3
	sum = RecAdd02(sum, i);
	printf("sum = %d\n", sum);
}


//void 