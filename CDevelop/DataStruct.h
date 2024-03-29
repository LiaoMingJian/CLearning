//#pragma once
#ifndef _DATA_STRUCT_H
#define _DATA_STRUCT_H
#include <stdbool.h>


#define SUCCESS					0
#define ERROR					1
#define INVALID_PARAMETER 		1
#define MAXSIZE					7

#define PARENT_TREE_MAXSIZE					100

/*ChildParentTree*/
#define CHILDE_PARENT_TREE_MAXSIZE			100
#define CHILD_TREE_CHILE_INDEX_SIZE			10

/*AVL_TREE_NODE*/
#define EH (0)
#define LH (1)
#define RH (-1)

typedef int ElemType;
typedef int LIST_STATUS;
typedef char ElemCharType;

typedef unsigned int OP_STATUS;

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

typedef struct _SQ_QUEUE {
	int Data[MAXSIZE];
	int Front;
	int Rear;
}SQ_QUEUE;

/*LINK_QUEUE*/
/*
typedef struct _LINK_QUEUE {
	Node *Front;
	Node *Rear;
}LINK_QUEUE;
*/

/*Tree*/
/*PARENT_TREE*/
typedef struct {
	int Data;
	int Parent;
}PT_NODE;

typedef struct {
	PT_NODE Node[PARENT_TREE_MAXSIZE];
	int Root;
	int Num;
}PARENT_TREE;

/*CHILD_PARTENT_TREE*/
typedef struct _CHILD_NODE{
	int ChildIndex;
	struct _CHILD_NODE *Next;
}CHILD_NODE;

typedef struct {
	int Data;
	int Parent;
	CHILD_NODE *FirstChildIndex;
}CT_BOX;

typedef struct {
	CT_BOX Node[CHILDE_PARENT_TREE_MAXSIZE];
	int Root;
	int NodeNum;
}CHILD_PARTENT_TREE;

typedef struct {
	int Data;
	int Parent;
	int ChildNum;
	int ChildIndex[CHILD_TREE_CHILE_INDEX_SIZE];
}CHILD_PARENT_TREE_NODE_DATA;

typedef struct {
	int Root;
	int NodeNum;	
}CHILD_PARENT_TREE_ROOT_NODENUM_DATA;

/*CHILD_SIBLING_PARENT_TREE*/
typedef struct _CHILD_SIBLING_PARENT_TREE {
	int Data;
	int Parent;
	struct _CHILD_SIBLING_PARENT_TREE *FirstChild;
	struct _CHILD_SIBLING_PARENT_TREE *RightSib;
}CHILD_SIBLING_PARENT_TREE_NODE;

typedef struct {
	int Data;
	int Parent;
	int IfExistFirstChild;
	int IfExistRightSib;
}CHILD_SIBLING_PARENT_TREE_NODE_DATA;


/*BINARY_TREE_NODE*/
#pragma pack(1)
typedef struct _BINARY_TREE_NODE {
	int Data;
	struct _BINARY_TREE_NODE *LeftChild;
	struct _BINARY_TREE_NODE *RightChild;
}BINARY_TREE_NODE;

typedef struct _BINARY_TREE_NODE_DATA {
	int BiTreeNodeData;
	int IsExistLeftChildFlag;
	char IsExistRightChildFlag;
}BINARY_TREE_NODE_DATA;

/*BINARY_THREAD_TREE_NODE*/
typedef struct _BINARY_THREAD_TREE_NODE {
	char Data;
	char IfExistDirectLeftNodeFlag;
	char IfExistDirectRightNodeFlag;
	struct _BINARY_THREAD_TREE_NODE *LeftChild;
	struct _BINARY_THREAD_TREE_NODE *RightChild;
}BINARY_THREAD_TREE_NODE;

typedef struct _BINARY_THREAD_TREE_NODE_DATA {
	char BiThrTreeData;
	char IfExistDirectLeftNodeFlag;
	char IfExistDirectRightNodeFlag;
	char IsExistLeftChildFlag;
	char IsExistRightChildFlag;
}BINARY_THREAD_TREE_NODE_DATA;

/*AVL_TREE_NODE*/
typedef struct _AVL_TREE_NODE {
	int Data;
	int BF;
	struct _AVL_TREE_NODE *LeftChild;
	struct _AVL_TREE_NODE *RightChild;
}AVL_TREE_NODE;
#pragma pack()

/*BINARY_TREE_NODE*/
void PreOrderTraversePrintBinaryTree(const BINARY_TREE_NODE *BiTreeNode);
void InOrderTraversePrintBinaryTree(const BINARY_TREE_NODE *BiTreeNode);
void PostOrderTraversePrintBinaryTree(const BINARY_TREE_NODE *BiTreeNode);

void BuildBinaryTree(BINARY_TREE_NODE **BiTreeNodePtr, BINARY_TREE_NODE_DATA *DataPtr, char IfExistNodeFlag);

/*BINARY_THREAD_TREE_NODE*/
void PreOrderTraversePrintBinaryThreadTree(const BINARY_THREAD_TREE_NODE *BiThrTreeNode);
void InOrderTraversePrintBinaryThreadTree(const BINARY_THREAD_TREE_NODE *BiThrTreeNode);
void PostOrderTraversePrintBinaryThreadTree(const BINARY_THREAD_TREE_NODE *BiThrTreeNode);
void PreOrderBuildBiThrTree(BINARY_THREAD_TREE_NODE **BiThrTreeNodePtr, BINARY_THREAD_TREE_NODE_DATA *DataPtr, char IfExistNodeFlag);
void BuildBinaryThreadTree(BINARY_THREAD_TREE_NODE **BiThrTreeNode, BINARY_THREAD_TREE_NODE_DATA *DataPtr);


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
void RPNExpression(void);

void testChar(void);

void test02(void);

void test03(void);

void test04(void);

void test05(void);

//void OpPostfixFunc(void);

int OpPostfixFunc(char *PostfixExpressionInput, int PostfixExpressionInputSize);

void test06(void);

void test07(void);

void OperateQueue(void);

/*LinkQueue*/
void OperateLinkQueue(void);


/*String*/
void OperateString(void);

int StrCopmare(const char *Str1, const char *Str2);

LIST_STATUS SubString(char *Sub, const char *Str, const unsigned int Pos, const unsigned int SubLen);

unsigned int FindStrIndex(char *Str, const char *FindStr, const unsigned int FindStrPos);

OP_STATUS MoveBackStr(char *Str, const unsigned int Pos, const int MvLen);

OP_STATUS CopyStrWhithoutTail(char *Str, const unsigned int Pos, const char *CpyStr);

OP_STATUS StrReplace(const char *Str3, const char *StrRep, char *NewStrRep);

void testPrinta(void);

OP_STATUS StrInsert(char *Str1, const unsigned int FindStr, const char *InsertStr);

unsigned int StrNormalFindIndex(const char *Str, const char *FindStr, const unsigned int FindPos);


/*Tree*/
/*PARENT_TREE*/
OP_STATUS BuildPTree(PARENT_TREE *PTree01, const unsigned int PTNodeNum, const int *PTNodeData, const int *PTNodeParent);

/*CHILD_PARTENT_TREE*/
OP_STATUS BuildChildParentTree(CHILD_PARTENT_TREE *CPTree, const CHILD_PARENT_TREE_ROOT_NODENUM_DATA *CPTreeRootNodeNum, const CHILD_PARENT_TREE_NODE_DATA *CPTreeData);

void PrintChildParentTree(const CHILD_PARTENT_TREE *CPTree);

/*CHILD_SIBLING_PARENT_TREE*/
//OP_STATUS BuildChildSibParentTree(CHILD_SIBLING_PARENT_TREE *CSPTree, const CHILD_SIBLING_PARENT_TREE_DADA *CSPTreeData, const unsigned int NodeNum);
OP_STATUS BuildChildSibParentTree(CHILD_SIBLING_PARENT_TREE_NODE *CSPTreeNode, const CHILD_SIBLING_PARENT_TREE_NODE_DATA *CSPTreeNodeData, unsigned int IfExistFirstChildFlag, unsigned int IfExistRightSibFlag);

void PrintChildSibParentTree(CHILD_SIBLING_PARENT_TREE_NODE *CSPTreeNode);

/*BinarySearch*/
int BinarySearch(int *Arr, int Num, int SearchValue);

/*BubbleRank*/
//{1, 3, 2, 5, 4, 0};
//3, 2, 4, 1, 5
void BubbleRank(int *Arr, int Num);

/*QuickSort*/
void QuickSort(int *Arr, int Low, int High);

/*InterpolationSearch*/
int InterpolationSearch(int *Arr, int Num, int SearchValue);


/*SelectSort*/
void SelectSort(int *Arr, int Num);

/*InsertSort*/
void InsertSort(int *Arr, int Num);

/*ShellSort*/
void ShellSort(int *Arr, int Num);


/*HeapSort*/
void HeapSort(int *Arr, int Num);


/*MergeSort*/
void MergeSort(int *Arr, int Num);

/*MergeSorByCycle*/
void MergeSorByCycle(int *Arr, int Num);

/*BSTSearch*/
bool BSTSearch(BINARY_TREE_NODE *BSTNode, BINARY_TREE_NODE *PreBSTNode, int Key, BINARY_TREE_NODE **RtNode);

/*AddBSTNode*/
void AddBSTNode(BINARY_TREE_NODE **BSTNode, int Key);

/*DelBSTNode*/
void DelBSTNode(BINARY_TREE_NODE **BSTNode, int Key);

/*BuildBSTree*/
void BuildBSTree(BINARY_TREE_NODE **BSTNode, int *Arr, int Num);

/*AddAVLNode*/
bool AddAVLNode(AVL_TREE_NODE **AVLNode, int Key, bool *Taller);

/*AVL_TREE_NODE*/
void PreOrderTraversePrintAVLTree(const AVL_TREE_NODE *AVLNode);

void InOrderTraversePrintAVLTree(const AVL_TREE_NODE *AVLNode);

void PostOrderTraversePrintAVLTree(const AVL_TREE_NODE *AVLNode);

/*BuildAVLTree*/
void BuildAVLTree(AVL_TREE_NODE **AVLNode, int *Arr, int Num);


/*DelAVLNode*/
bool DeleteAVLNode(AVL_TREE_NODE **AVLNode, int Key, bool *Shorter);

//Hash
#define EMPTY_FLAG           (-1)
#pragma pack(1)
typedef struct _HASH_TABLE {
	int *Table;
	int Num;
}HASH_TABLE;
#pragma pack()

void HashTableInit(HASH_TABLE **HTable, int Num);

void InsertHash(HASH_TABLE *HTable, int *Arr, int Num);

int SearchHash(HASH_TABLE *HTable, int Key);

//MGraph
/*M_GRAPH*/
#define MAX_VEXS_SIZE    (100)
#define MAX_VALUE        (65535)
#pragma pack(1)
typedef struct _M_GRAPH {
	int VectorNum;
	int EadgeNum;
	int Vector[MAX_VEXS_SIZE];
	int Eadge[MAX_VEXS_SIZE][MAX_VEXS_SIZE];
}M_GRAPH;
#pragma pack()

void PrintMGraph(M_GRAPH *MGraph);
void BuildMGraph(M_GRAPH *MGraph, int *Vector, int *Eadge, int VectorNum, int EadgeNum);

/*ADJUST_LIST_GRAPH*/
typedef struct _LIST_NODE_DATA {
	int  Num;
	int  Vector[MAX_VEXS_SIZE];
}LIST_NODE_DATA;

typedef struct _LIST_NODE {
	int               VectorIndex;
	struct _LIST_NODE *Next;
}LIST_NODE;

typedef struct _ADJUST_LIST {
	int       Data;
	LIST_NODE *FirstEadge;
}ADJUST_LIST;

typedef struct _ADJUST_LIST_GRAPH {
	int          VectorNum;
	int          EadgeNum;
	ADJUST_LIST  AdjustGraph[MAX_VEXS_SIZE];
}ADJUST_LIST_GRAPH;

void BuildAdjustListGraph(ADJUST_LIST_GRAPH *AdjListGraph, ADJUST_LIST_GRAPH *AdjListGraphData, LIST_NODE_DATA *LstNodeData);

void PrintAdjLstGraph(const ADJUST_LIST_GRAPH *AdjListGraph01);

/*MGraphDFS*/
void MGraphDFS(M_GRAPH *MGraph, bool *Visited, int *ResultArr);

/*AdjLstGraphDFS*/
void AdjLstGraphDFS(ADJUST_LIST_GRAPH *AdjLstGraph, bool *Visited, int *ResultArr);


/*LINK_QUEUE*/
typedef struct _LINK_NODE {
	int Data;
	struct _LINK_NODE *Next;
}LINK_NODE;

typedef struct _LINK_QUEUE {
	LINK_NODE *Front;
	LINK_NODE *Rear;
}LINK_QUEUE;

void InitLinkQueue(LINK_QUEUE **LinkQueue);
void BuildLinkQueue(LINK_QUEUE *LinkQueue, int Num, int *DataArr);
void PrintLinkQueue(LINK_QUEUE *LinkQueue);
void DestoryLinkQueue(LINK_QUEUE *LinkQueue);
void EnterLinkQueue(LINK_QUEUE *LinkQueue, int AddData);
void ExitLinkQueue(LINK_QUEUE *LinkQueue, int *ExitData);

/*MGraghBFS*/
void MGraghBFS(M_GRAPH *MGraph, bool *Visited, int *ResultArr);

/*AdjLstGraphBFS*/
void AdjLstGraphBFS(ADJUST_LIST_GRAPH *AdjLstGraph, bool *Visited, int *ResultArr);
#endif