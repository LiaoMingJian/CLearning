//#pragma once
#ifndef _DATA_STRUCT_H
#define _DATA_STRUCT_H

#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			10

typedef int ElemType;
typedef int LIST_STATUS;

typedef struct SQ_LIST_ {
	ElemType Data[MAXSIZE];
	int Len;
}SQ_LIST;

typedef struct _Node {
	ElemType Data;
	struct _Node *Next;
}Node;

typedef struct _Node *LinkList;

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

#endif