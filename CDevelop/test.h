#ifndef _TEST_H
#define _TEST_H

//Create link
typedef struct Node {
	int Data;
	struct Node *Next;
}MyNode;

//SqList
#define MAXSIZE 20
typedef int ElemType;

typedef struct {
	ElemType Data[MAXSIZE];
	int Len;
}SqList;


//Test overflow access 
void test01();

//Test combine "++" and "*"
void test02();

void test02();

//test malloc
void test03();

//test printf with %s
void test04();

//test %d, %c
void test05();

//test %d, %f
void test06();

//test %c, %s
void test07();

//test strcpy_s
void test08();

//test strcpy_s overflow
void test09();

void PointFunc();

void testGetchar();

void testGets();

void TestWriteChar();

void TestWritStr();

void TestWritStr02();

void TestReadFile();

void TestCreateLink01();

void TestCreateLink02();

void OperateLink();

MyNode* DeleteHeadNode(MyNode *);

MyNode* DeleteTailNode(MyNode *);

MyNode* DeletMiddleNode(MyNode *, int );

MyNode* AddHeadNode(MyNode *, MyNode *);

MyNode* AddTailNode(MyNode *, MyNode *);

MyNode* TestAddMiddleNode(MyNode *, MyNode *, MyNode *);

void Rec();

void FabByLoop01();

void FabByLoop02();

void FabByRec();

void FabByRec02();

void AddValByRec01();

void AddValByRec02();

#endif
