//#pragma once
#ifndef _DATA_STRUCT_H
#define _DATA_STRUCT_H

#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			5

typedef int ElemType;
typedef int LIST_STATUS;
typedef char ElemCharType;

typedef struct SQ_LIST_ {
	ElemType Data[MAXSIZE];
	int Len;
}SQ_LIST;

typedef struct _Node {
	ElemType Data;
	struct _Node *Next;
}Node;

typedef struct _CHAR_NODE {
	ElemCharType Data;
	struct _CHAR_NODE *Next;
}CHAR_NODE;

typedef struct _Node *LinkList;

typedef struct {
	ElemType Data;
	int Cur;
}StNode;

typedef struct _Double_link_Node {
	ElemType Data;
	struct _Double_link_Node *Next;
	struct _Double_link_Node *Prior;
}Double_Link_Node;


typedef struct _SQ_STACK {
	ElemType Data[MAXSIZE];
	int Top;
}SQ_STACK;

typedef struct _SQ_DOUBLE_STACK {
	ElemType Data[MAXSIZE];
	int Top1;
	int Top2;
}SQ_DOUBLE_STACK;

typedef struct _LINK_STACK {
	Node * Top;
	int Count;
}LINK_STACK;

typedef struct _CHAR_LINK_STACK {
	CHAR_NODE * Top;
	int Count;
}CHAR_LINK_STACK;



LIST_STATUS OperatorList();

LIST_STATUS CreatList(SQ_LIST *const L);

LIST_STATUS PrintList(const SQ_LIST L);

LIST_STATUS ClearList(SQ_LIST * const L);

LIST_STATUS GetElem(const SQ_LIST L, const int GetIndex, int * const GetE);

LIST_STATUS LocateElem(const SQ_LIST L, const int LoElm);

LIST_STATUS InsertElem01(SQ_LIST * const L, const int InsertIndex, const int InsertElm);

LIST_STATUS InsertElem02(SQ_LIST * const L, const int InsertIndex, const int InsertElm);

LIST_STATUS InsertElem03(SQ_LIST * const L, const int InsertIndex, const int InsertElm);

LIST_STATUS DeleteElem01(SQ_LIST * const L, const int DeleteIndex);

LIST_STATUS DeleteElem02(SQ_LIST * const L, const int DeleteIndex);

LIST_STATUS OperateLinkList(void);

LIST_STATUS CreatLinkListHead(const LinkList L, const unsigned int n);

LIST_STATUS PrintLinkList(const LinkList L);

LIST_STATUS CreatLinkListTail(const LinkList L, const unsigned int n);

LIST_STATUS DeleteLinkList(LinkList L);

LIST_STATUS AddLinkListNode01(const LinkList L, const unsigned int AddIndex, const int AddNodeData);

LIST_STATUS DeleteLinkListNode(const LinkList L, const unsigned int DeleteIndex);

LinkList ReverseLinkListNode(const LinkList L);

LIST_STATUS OperatorStaticLinkList(void);

LIST_STATUS CreateStaticLinkList(StNode SL[], int CreateStNodeNum);

LIST_STATUS PrintStaticLinkList(const StNode SL[]);

LIST_STATUS AddStaticLinkListNode(StNode SL[], const int AddIndex, const ElemType AddData);

LIST_STATUS DeleteStaticLinkListNode(StNode SL[], const int DeleteIndex);

/*Loop Link list*/
LIST_STATUS OperatorLoopLinkList(void);

Node* MergeTwoLoopLinkList(Node *LoopHead01, Node *LoopHead02);

/*Double Link list*/
void OperateDoubleLinkList(void);


/*SqStack*/
void OperateSqStack(void);


/*SQDoubleStack*/
void OperateSQDoubleStack(void);


/*LinkStack*/
void OperateLinkStack(void);

/*recurrence*/
void FabByArr(void);


void PrintFabByRec(void);

/*CHAR_LINK_STACK*/
void OperateCharLinkStack(void);

/*RPN*/
void RPNString();

void testChar(void);

void test02(void);

void test03(void);

void test04(void);

void test05(void);

void OpPostfixFunc(void);

void test06(void);

#endif