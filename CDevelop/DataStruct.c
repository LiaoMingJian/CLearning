#include <stdio.h>
#include "DataStruct.h"
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>


LIST_STATUS OperatorList() {
	SQ_LIST L;
	LIST_STATUS Status;
	int GetIndex = 2;
	int GetE;
	int LoElm = 3;
	int InsertIndex = 2;
	int InsertElm = 15;
	int DeleteIndex = 2;
	

	CreatList(&L);
	PrintList(L);
	
	/*
	ClearList(&L);
	PrintList(L);
	*/

	/*
	GetElem(&L, GetIndex, &GetE);
	printf("The GetIndex = %d, GetE = %d\n", GetIndex, GetE);
	*/

	/*
	Status = LocateElem(L, LoElm);
	printf("Status = %d\n", Status);
	*/

	/*
	Status = InsertElem03(&L, InsertIndex, InsertElm);
	if (ERROR == Status) {
		printf("InsertElem faild!\n");		
	}
	*/

	Status = DeleteElem01(&L, DeleteIndex);
	if (ERROR == Status) {
		printf("DeleteElem01 faild!\n");
	}

	PrintList(L);

	return Status;
}

LIST_STATUS CreatList(SQ_LIST *const L) {
	printf("Creat list start\n");
	L->Data[0] = 1;
	L->Data[1] = 2;
	L->Data[2] = 3;
	L->Len = 3;

	return SUCCESS;
}

LIST_STATUS PrintList(const SQ_LIST L) {
	int i = 0;

	printf("Print List:\n");
	for (i = 0; i < L.Len; ++i) {
		printf("L.Data[%d] = %d\n", i, L.Data[i]);
	}

	printf("L.Len= %d\n", i, L.Len);
	return SUCCESS;
}

LIST_STATUS ClearList(SQ_LIST * const L) {
	printf("Clear list start!\n");
	memset(L, 0, sizeof(SQ_LIST));
	L->Len = 0;

	printf("Clear list end!\n");
	return SUCCESS;
}

LIST_STATUS GetElem(const SQ_LIST L, const int GetIndex, int * const GetE) {
	printf("GetElem start!\n");

	if ( 0==L.Len || GetIndex<1 || GetIndex>L.Len ) {
		return ERROR;	
	}

	*GetE = L.Data[GetIndex -1];

	return SUCCESS;
}

LIST_STATUS LocateElem(const SQ_LIST L, const int LoElm) {
	int Index = 0;
	
	printf("\nLocateElem start\n");

	if (0 == L.Len) {
		return ERROR;	
	}

	for (Index = 0; Index < L.Len; ++Index) {
		if (LoElm == L.Data[Index]) {
			return SUCCESS;
		}	
	}
	
	if (Index == L.Len) {
		return SUCCESS;
	}
}

LIST_STATUS InsertElem01(SQ_LIST * const L, const int InsertIndex, const int InsertElm) {
	int i = 0;
	int Buff;
	int Pre;

	printf("\nInsertElem start:\n");

	if ( MAXSIZE == L->Len || InsertIndex < 1 || InsertIndex > L->Len+1 ) {
		printf("Invaild Len or InserInsex!\n");
		return ERROR;
	}
	
	if (InsertIndex == L->Len + 1) { /*Insert in tail*/
		L->Data[InsertIndex - 1] = InsertElm;
		L->Len++;
	} else {/*Insert in head or middle*/

		Pre = L->Data[InsertIndex - 1];
		for (i = InsertIndex; i <= L->Len; ++i) {
			Buff = L->Data[i];
			L->Data[i] = Pre;
			Pre = Buff;
		}		

		/*
		for (i = L->Len - 1; i >= InsertIndex - 1; --i) {
			L->Data[i + 1] = L->Data[i];		
		} 
		*/

		L->Data[InsertIndex - 1] = InsertElm;
		L->Len++;
	}

	return SUCCESS;
}

LIST_STATUS InsertElem02(SQ_LIST * const L, const int InsertIndex, const int InsertElm) {	
	int Pre;
	int Temp;
	int i;

	printf("\nInsertElem start:\n");

	if (MAXSIZE == L->Len || InsertIndex < 1 || InsertIndex > L->Len + 1) {
		printf("Invaild Len or InserInsex!\n");
		return ERROR;
	}

	//Initialize
	Pre = L->Data[InsertIndex - 1];
	for (i = InsertIndex; i <= L->Len; ++i) {		
		//Loop
		Temp = L->Data[i];		
		L->Data[i] = Pre;

		//Move Pre
		Pre = Temp;		
	}

	L->Data[InsertIndex - 1] = InsertElm;
	L->Len++;	

	printf("InsertElem end:\n");

	return SUCCESS;
}

LIST_STATUS InsertElem03(SQ_LIST * const L, const int InsertIndex, const int InsertElm) {
	int i = 0;

	printf("\nInsertElem start:\n");

	if (MAXSIZE == L->Len || InsertIndex < 1 || InsertIndex > L->Len + 1) {
		printf("\nInvaild Len or InserInsex!\n");
		return ERROR;
	}

	for (i = L->Len; i >= InsertIndex - 1; --i) {
		L->Data[i] = L->Data[i-1];
	}

	L->Data[InsertIndex - 1] = InsertElm;
	L->Len++;

	printf("InsertElem end:\n");

	return SUCCESS;
}

LIST_STATUS DeleteElem01(SQ_LIST * const L, const int DeleteIndex) {
	int i = 0;

	printf("\nDeleteElem start:\n");

	if (0 == L->Len || DeleteIndex < 1 || DeleteIndex > L->Len) {
		printf("\nInvaild Len or DeleteIndex!\n");
		return ERROR;
	}
	
	for (i = DeleteIndex - 1; i < L->Len - 1; ++i) {
		L->Data[i] = L->Data[i + 1];	
	}

	L->Len--;

	printf("DeleteElem end\n");
	return SUCCESS;
}

LIST_STATUS DeleteElem02(SQ_LIST * const L, const int DeleteIndex) {
	int i = 0;
	int Pre;
	int Temp;

	printf("\nDeleteElem start:\n");

	if (0 == L->Len || DeleteIndex < 1 || DeleteIndex > L->Len) {
		printf("\nInvaild Len or DeleteIndex!\n");
		return ERROR;
	}

	Pre = L->Data[L->Len - 1];
	for (i = L->Len - 2; i >= DeleteIndex - 1; --i) {
		Temp = L->Data[i];
		L->Data[i] = Pre;
		Pre = Temp;
	}

	L->Len--;

	printf("DeleteElem end\n");
	return SUCCESS;
}


LinkList ReverseLinkListNode(const LinkList L) {
	LinkList Pre, Cur, Temp, Temp02;

	printf("ReverseLinkListNode start\n");

	if (NULL == L || NULL == L->Next) {
		return NULL;
	}

	Pre = NULL;
	Cur = L;

	while (Cur != NULL) {
		Temp = Cur->Next;

		Cur->Next = Pre;

		Pre = Cur;
		Cur = Temp;
	}

	return Pre;
}

LIST_STATUS OperateLinkList(void) {
	LinkList L = NULL;
	LIST_STATUS Status;
	unsigned int n = 5;
	unsigned int AddIndex = 4;
	int AddNodeData = 25;
	unsigned int DeleteIndex = 4;

	LinkList RevList;

	L = (LinkList)malloc(sizeof(Node));

	/*
	Status = CreatLinkListHead(L, n);
	if (SUCCESS == Status) {
		printf("CreatLinkListHead succeed!\n");
	} else {
		printf("CreatLinkListHead filed!\n");
	}
	*/

	Status = CreatLinkListTail(L, n);
	if (SUCCESS == Status) {
		printf("CreatLinkListTail succeed!\n");
	} else {
		printf("CreatLinkListTail filed!\n");
	}

	PrintLinkList(L);

	/*
	Status = DeleteLinkList(L);
	if (SUCCESS == Status) {
		printf("DeleteLinkList succeed!\n");
	}
	else {
		printf("DeleteLinkList filed!\n");
	}
	*/

	/*
	Status = AddLinkListNode01(L, AddIndex, AddNodeData);
	if (SUCCESS == Status) {
		printf("AddLinkListNode01 succeed!\n");
	} else {
		printf("AddLinkListNode01 filed!\n");
	}
	*/

	/*
	Status = AddLinkListNode02(L, AddIndex, AddNodeData);
	if (SUCCESS == Status) {
		printf("AddLinkListNode02 succeed!\n");
	}
	else {
		printf("AddLinkListNode02 filed!\n");
	}
	*/

	/*
	Status = DeleteLinkListNode(L, DeleteIndex);
	if (SUCCESS == Status) {
		printf("DeleteLinkListNode succeed!\n");
	}
	else {
		printf("DeleteLinkListNode filed!\n");
	}
	*/

	RevList = ReverseLinkListNode(L);

	PrintLinkList(RevList);
}

LIST_STATUS PrintLinkList(const LinkList L) {
	LinkList Temp;

	printf("PrintLinkList start\n");
	Temp = L;

	if (NULL == L) {
		return ERROR;
	}

	while (Temp != NULL) {
		printf("L->Data = %d\n", Temp->Data);
		Temp = Temp->Next;
	}

	printf("PrintLinkList end\n");
	return SUCCESS;
}

LIST_STATUS CreatLinkListHead(const LinkList L, const unsigned int n) {
	int i;
	LinkList AddNode;
	LinkList Temp;

	Temp = L;

	printf("CreatLinkListHead start\n");

	if (NULL == Temp) {
		return ERROR;	
	}

	/*Create Head node*/
	Temp->Data = n;
	Temp->Next = NULL;

	/*Create remaining node*/
	for (i = 0; i < n; ++i) {
		AddNode = (LinkList)malloc(sizeof(Node));
		AddNode->Data = i;
		AddNode->Next = Temp->Next;
		Temp->Next = AddNode;
	}

	printf("CreatLinkListHead end\n");
	return SUCCESS;
}

LIST_STATUS CreatLinkListTail(const LinkList L, const unsigned int n) {
	LinkList AddNode;
	LinkList Temp;
	int i = 0;

	printf("CreatLinkListTail start\n");

	if (NULL == L) {
		return ERROR;
	}

	Temp = L;

	/*Create head node*/
	Temp->Data = n;
	Temp->Next = NULL;

	/*Create remaining node*/
	for (i = 0; i < n; ++i) {
		AddNode = (LinkList)malloc(sizeof(Node));
		AddNode->Data = i;
		
		AddNode->Next = NULL;		
		Temp->Next = AddNode;
		
		/*Iteration*/
		Temp = Temp->Next;	
	}
	
	printf("CreatLinkListTail end\n");
}

LIST_STATUS DeleteLinkList(LinkList L) {
	LinkList DeleteNode;
	LinkList DeleteNodeTemp;

	printf("DeleteLinkList start\n");

	if (NULL == L) {
		return ERROR;	
	} 

	DeleteNode = L->Next;

	while (NULL != DeleteNode) {
		DeleteNodeTemp = DeleteNode->Next;

		free(DeleteNode);

		DeleteNode = DeleteNodeTemp;
	}
	
	L->Data = 0;
	L->Next = NULL;

	printf("DeleteLinkList end\n");
	
	return SUCCESS;
}

LIST_STATUS AddLinkListNode01(const LinkList L, const unsigned int AddIndex, const int AddNodeData) {
	unsigned int i = 0;
	LinkList AddNode;
	LinkList Temp;
	int n;

	printf("AddLinkListNode01 start\n");

	Temp = L;
	n = Temp->Data;

	if ((NULL == Temp) || (AddIndex < 1) || (AddIndex > Temp->Data + 1)) {
		return ERROR;	
	}

	for (i = 0; i < n + 1; ++i) {
		if ((i + 1) == AddIndex) {
			AddNode = (LinkList)malloc(sizeof(LinkList));
			AddNode->Data = AddNodeData;

			AddNode->Next = Temp->Next;
			Temp->Next = AddNode;

			L->Data += 1;
		}	

		Temp = Temp->Next;
	}



	printf("AddLinkListNode01 end\n");
	return SUCCESS;
}

LIST_STATUS AddLinkListNode02(const LinkList L, const unsigned int AddIndex, const int AddNodeData) {
	unsigned int i = 1;
	LinkList AddNode;
	LinkList Temp;

	printf("AddLinkListNode02 start\n");

	Temp = L;

	if ((NULL == Temp) || (AddIndex < 1)) {
		return ERROR;
	}

	while (AddIndex != i && NULL != Temp) {
		printf("Temp = 0x%x\n", Temp);
		Temp = Temp->Next;
		++i;
	}

	if (NULL == Temp) {
		printf("AddIndex is invalid\n");
		return ERROR;	
	}

	AddNode = (LinkList)malloc(sizeof(LinkList));
	AddNode->Data = AddNodeData;

	AddNode->Next = Temp->Next;
	Temp->Next = AddNode;

	L->Data += 1;

	printf("AddLinkListNode02 end\n");
	return SUCCESS;
}

LIST_STATUS DeleteLinkListNode(const LinkList L, const unsigned int DeleteIndex) {
	int i = 1;
	LinkList Temp;
	LinkList DeleteNode;

	printf("DeleteLinkListNode start\n");

	if (NULL == L || DeleteIndex < 1) {
		return ERROR;
	}

	Temp = L;

	while ((i < DeleteIndex - 1) && (NULL != Temp)) {
		++i;
		Temp = Temp->Next;
	}

	if (NULL == Temp) {
		printf("DeleteIndex is invalid\n");
		return ERROR;
	}

	DeleteNode = Temp->Next;
	Temp->Next = DeleteNode->Next;
	
	DeleteNode->Next = NULL;
	free(DeleteNode);

	L->Data -= 1;

	printf("DeleteLinkListNode end\n");
	return SUCCESS;
}


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

	printf("PrintStaticLinkList end\n\n");
}

LIST_STATUS PrintStaticArr(const StNode SL[]) {
	int i = 0;

	printf("PrintStaticArr start\n");

	for (i = 0; i < MAXSIZE; ++i) {
		printf("SL[%d].Data = %d, SL[%d].Cur = %d\n", i, SL[i].Data, i, SL[i].Cur);	
	}

	printf("PrintStaticArr end\n");
}

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

int IfSLMalloc(StNode SL[]) {
	int Index = SL[0].Cur;

	if (Index) {
		SL[0].Cur = SL[Index].Cur;
	}

	return Index;
}

int FreeSL(StNode SL[], int FreeIndex) {
	SL[FreeIndex].Cur = SL[0].Cur;
	SL[0].Cur = FreeIndex;
}

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


/*LoopLinkList*/
LIST_STATUS OperatorLoopLinkList(void) {
	Node *LoopHead01;
	Node *LoopHead02;
	Node *MergeLoopHead;
	int CreateNum = 3;
	
	LIST_STATUS Status;

	/*Create empty link list*/
	LoopHead01 = (Node *)malloc(sizeof(Node));
	LoopHead02 = (Node *)malloc(sizeof(Node));


	Status = CreateLoopLinkList01(LoopHead01, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateLoopLinkList01 succeed!\n");
	} else {
		printf("CreateLoopLinkList01 failed!\n");
	}

	PrintLoopLinkList(LoopHead01);

	Status = CreateLoopLinkList02(LoopHead02, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateLoopLinkList02 succeed!\n");
	}
	else {
		printf("CreateLoopLinkList02 failed!\n");
	}

	PrintLoopLinkList(LoopHead02);

	MergeLoopHead = MergeTwoLoopLinkList(LoopHead01, LoopHead02);

	PrintLoopLinkList(MergeLoopHead);
}

LIST_STATUS CreateLoopLinkList01(Node *LoopHead, int CreateNum) {
	int i = 0;
	Node *TraNode;
	Node *CreateNode;

	printf("CreateLoopLinkList start\n");

	if (NULL == LoopHead) {
		return ERROR;
	}

	/*Create TailNode*/
	LoopHead->Data = CreateNum;
	LoopHead->Next = NULL;

	TraNode= LoopHead;

	for (i = 1; i <= CreateNum; ++i) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = i;
		
		/*Insert Node in the tail of link list*/
		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		/*Move TraNode*/
		TraNode = TraNode->Next;
	}

	/*Deal with the last Node*/
	if (NULL == TraNode->Next) {
		TraNode->Next = LoopHead;
	}

	printf("CreateLoopLinkList end\n");
	return SUCCESS;
}

LIST_STATUS CreateLoopLinkList02(Node *LoopHead, int CreateNum) {
	int i = 0;
	Node *TraNode;
	Node *CreateNode;

	printf("CreateLoopLinkList start\n");

	if (NULL == LoopHead) {
		return ERROR;
	}

	/*Create TailNode*/
	LoopHead->Data = CreateNum;
	LoopHead->Next = NULL;

	TraNode = LoopHead;

	for (i = 1; i <= CreateNum; ++i) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = i + 3;

		/*Insert Node in the tail of link list*/
		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		/*Move TraNode*/
		TraNode = TraNode->Next;
	}

	/*Deal with the last Node*/
	if (NULL == TraNode->Next) {
		TraNode->Next = LoopHead;
	}

	printf("CreateLoopLinkList end\n");
	return SUCCESS;
}

LIST_STATUS PrintLoopLinkList(Node *LoopHead) {
	Node *TraNode;

	printf("PrintLoopLinkList start\n");

	TraNode = LoopHead;

	if (NULL == LoopHead) {
		return ERROR;
	}

	while (TraNode->Next != LoopHead) {
		printf("TraNode->Data = %d\n", TraNode->Data);
		TraNode = TraNode->Next;
	}
	
	if (TraNode->Next == LoopHead) {
		printf("TraNode->Data = %d\n", TraNode->Data);	
	}

	printf("PrintLoopLinkList end\n");
}

Node* MergeTwoLoopLinkList(Node *LoopHead01, Node *LoopHead02) {
	Node *TraNode01;
	Node *TraNode02;

	printf("MergeTwoLoopLinkList start\n");

	if (NULL == LoopHead01) {
		return LoopHead02;
	}

	if (NULL == LoopHead02) {
		return LoopHead01;
	}

	LoopHead01->Data += LoopHead02->Data;\

	TraNode01 = LoopHead01;
	TraNode02 = LoopHead02;

	/*Find the tail01*/
	while (TraNode01->Next != LoopHead01) {
		TraNode01 = TraNode01->Next;
	}

	/*Find the tail02*/
	while (TraNode02->Next != LoopHead02) {
		TraNode02 = TraNode02->Next;
	}

	/*Link with tail01 with LoopHead01->Next*/
	if (TraNode01->Next == LoopHead01) {
		TraNode01->Next = LoopHead02->Next;	
	}

	/*Link with tail02 with LoopHead01*/
	if (TraNode02->Next == LoopHead02) {
		TraNode02->Next = LoopHead01;
	}

	/*Free LoopHead02*/
	free(LoopHead02);

	printf("MergeTwoLoopLinkList end\n");

	return LoopHead01;
}


/*DoubleLinkedList*/
void OperateDoubleLinkList(void) {
	Double_Link_Node *DoubleHead;
	LIST_STATUS Status;
	int CreateNum = 5;
	int AddNodeIndex = 2;
	int AddNodeData = 15;
	int DeleteNodeIndex = 3;

	DoubleHead = (Double_Link_Node *)malloc(sizeof(Double_Link_Node));
	
	Status = CreateDoubleLinkList(DoubleHead, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateDoubleLinkList succeed!\n");
	}
	else {
		printf("CreateDoubleLinkList failed!\n");
	}

	GetDoubleLinkListLenth(DoubleHead);
	PrintDoubleLinkList(DoubleHead);	
	
	Status = AddDoubleLinkListNode(DoubleHead, AddNodeIndex, AddNodeData);
	if (SUCCESS == Status) {
		printf("AddDoubleLinkListNode succeed!\n");
	}
	else {
		printf("AddDoubleLinkListNode failed!\n");
	}	

	/*
	Status = DeleteDoubleLinkListNode(DoubleHead, DeleteNodeIndex);
	if (SUCCESS == Status) {
		printf("DeleteDoubleLinkListNode succeed!\n");
	}
	else {
		printf("DeleteDoubleLinkListNode failed!\n");
	}
	*/

	/*
	Status = DeleteWholeDoubleLinkList(DoubleHead);
	if (SUCCESS == Status) {
		printf("DeleteWholeDoubleLinkList succeed!\n");
	}
	else {
		printf("DeleteWholeDoubleLinkList failed!\n");
	}

	GetDoubleLinkListLenth(DoubleHead);
	PrintDoubleLinkList(DoubleHead);
	*/
}

LIST_STATUS CreateDoubleLinkList(Double_Link_Node *DoubleHead, int CreateNum) {
	int i = 0;	
	Double_Link_Node *CreateNode;
	Double_Link_Node *TraNode;

	printf("CreateDoubleLinkList start!\n");

	if (NULL == DoubleHead) {
		return ERROR;
	}

	/*Creat empty double link list*/
	DoubleHead->Data = CreateNum;
	DoubleHead->Next = NULL;
	DoubleHead->Prior = NULL;

	TraNode = DoubleHead;

	for (i = 1; i <= CreateNum; ++i) {
		CreateNode = (Double_Link_Node *)malloc(sizeof(Double_Link_Node));
		CreateNode->Data = i;

		CreateNode->Next = TraNode->Next;
		CreateNode->Prior = TraNode;
		TraNode->Next = CreateNode;

		TraNode = TraNode->Next;
	}

	printf("CreateDoubleLinkList end!\n");
	
	return SUCCESS;
}

LIST_STATUS PrintDoubleLinkList(Double_Link_Node * const DoubleHead) {
	Double_Link_Node *TraNode;
	int TraIndex = 0;

	printf("CreateDoubleLinkList start!\n");

	if (NULL == DoubleHead) {
		return ERROR;	
	}

	TraNode = DoubleHead;

	while (TraNode != NULL) {
		printf("The Index = %d, TraNode = 0x%x, TraNode->Data = %d, TraNode->Prior = 0x%x, TraNode->Next = 0x%x\n", TraIndex, TraNode, TraNode->Data, TraNode->Prior, TraNode->Next);
		++TraIndex;

		TraNode = TraNode->Next;
	}

	printf("CreateDoubleLinkList end!\n\n");
}

int GetDoubleLinkListLenth(Double_Link_Node * const DoubleHead) {
	Double_Link_Node * TraNode;
	
	int DoubleLinkListLenth = 0;

	if (NULL == DoubleHead) {
		return 0;
	}
	
	if (NULL == DoubleHead->Next) {
		return 0;
	}
	
	TraNode = DoubleHead->Next;
	
	/*DoubleLinkListLenth is not incluede of DoubleHead*/
	while (TraNode != NULL) {
		++DoubleLinkListLenth;
		TraNode = TraNode->Next;
	}
	
	printf("DoubleLinkListLenth = %d\n", DoubleLinkListLenth);

	return DoubleLinkListLenth;
}

LIST_STATUS AddDoubleLinkListNode(Double_Link_Node *DoubleHead, int AddNodeIndex, int AddNodeData) {
	Double_Link_Node *AddNode;
	Double_Link_Node *TraNode;
	int TraIndex = 1;

	printf("AddDoubleLinkList start!\n");

	if (NULL == DoubleHead || AddNodeIndex < 1 || AddNodeIndex > GetDoubleLinkListLenth(DoubleHead) + 1) {
		return ERROR;	
	}

	TraNode = DoubleHead;
	
	printf("TraNode = 0x%x\n", TraNode);

	/*Find the previous node of AddNodeIndex*/
	for (TraIndex = 1; TraIndex <= AddNodeIndex - 1 ; ++TraIndex) {
		TraNode = TraNode->Next;
		printf("TraIndex = %d, TraNode = 0x%x\n", TraIndex, TraNode);
	}

	printf("TraIndex = %d, TraNode = 0x%x\n", TraIndex, TraNode);

	AddNode = (Double_Link_Node *)malloc(sizeof(Double_Link_Node));
	
	AddNode->Data = 15;
	AddNode->Next = TraNode->Next;
	AddNode->Prior = TraNode;

	TraNode->Next->Prior = AddNode;
	TraNode->Next = AddNode;

	DoubleHead->Data++;

	printf("AddDoubleLinkList end!\n");
	return SUCCESS;
}

LIST_STATUS DeleteDoubleLinkListNode(Double_Link_Node *DoubleHead, int DeleteNodeIndex) {
	Double_Link_Node *TraNode;
	int TraIndex;

	printf("DeleteDoubleLinkListNode start!\n");

	if (NULL == DoubleHead || DeleteNodeIndex < 1 || DeleteNodeIndex > GetDoubleLinkListLenth(DoubleHead)) {
		return ERROR;	
	}

	TraNode = DoubleHead;

	for (TraIndex = 1; TraIndex <= DeleteNodeIndex; ++TraIndex) {
		TraNode = TraNode->Next;	
	}

	TraNode->Prior->Next = TraNode->Next;
	TraNode->Next->Prior = TraNode->Prior;		

	free(TraNode);
	DoubleHead->Data--;

	printf("DeleteDoubleLinkListNode start!\n");

	return SUCCESS;
}

LIST_STATUS DeleteWholeDoubleLinkList(Double_Link_Node *DoubleHead) {
	Double_Link_Node *TraNode = DoubleHead->Next;
	Double_Link_Node *DeleteNode = TraNode;

	printf("DeleteWholeDoubleLinkList start!\n");

	if (NULL == DoubleHead) {
		return ERROR;
	}
	
	while (TraNode != NULL) {
		DeleteNode = TraNode;		
		TraNode = TraNode->Next;

		free(DeleteNode);
		DoubleHead->Data--;
	}

	if (DoubleHead->Data == 0) {
		DoubleHead->Next = NULL;
	}

	printf("DeleteWholeDoubleLinkList end!\n");

	return SUCCESS;
}


/*SQ_STACK*/
LIST_STATUS CreateSQStack(SQ_STACK *SqStack, int CreateNum) {
	int TraIndex;

	printf("CreateSQStack start\n");

	if (NULL == SqStack || CreateNum > MAXSIZE) {
		return ERROR;
	}

	for (TraIndex = 0; TraIndex < CreateNum; ++TraIndex) {
		SqStack->Data[TraIndex] = TraIndex;
	}

	SqStack->Top = CreateNum - 1;

	printf("CreateSQStack end\n");
	return SUCCESS;
}

void PrintSQStack(SQ_STACK * const SqStack) {
	SQ_STACK *TraStack = SqStack;
	int TraIndex;

	printf("PrintSQStack start\n");

	printf("TraStack->Top = %d\n", TraStack->Top);
	for (TraIndex = 0; TraIndex < MAXSIZE; ++TraIndex) {
		printf("TraStack->Data[TraIndex] = %d\n", TraStack->Data[TraIndex]);
	}

	printf("PrintSQStack end\n\n");
}

LIST_STATUS PushSQStack(SQ_STACK *SqStack, int PushData) {	
	printf("PushSQStack start\n");

	if (NULL == SqStack || SqStack->Top == MAXSIZE - 1) {
		return ERROR;
	}

	SqStack->Top++;
	SqStack->Data[SqStack->Top] = PushData;

	printf("PushSQStack end\n");

	return SUCCESS;
}

LIST_STATUS PopSQStack(SQ_STACK *SqStack, int *PopData) {
	printf("PopSQStack start\n");

	if (NULL == SqStack || SqStack->Top == -1) {
		return ERROR;	
	}

	*PopData = SqStack->Data[SqStack->Top];
	SqStack->Top--;

	printf("PopSQStack end\n");
}

void OperateSqStack(void) {
	LIST_STATUS Status;
	SQ_STACK *SqStack = (SQ_STACK *)malloc(sizeof(SQ_STACK));
	int CreateNum = 3;
	int PushData = 3;
	int *PopData = (int *)malloc(sizeof(int));
	
	Status = CreateSQStack(SqStack, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateSQStack succeed!\n");
	}
	else {
		printf("CreateSQStack failed!\n");
	}

	PrintSQStack(SqStack);

	/*
	Status = PushSQStack(SqStack, PushData);
	if (SUCCESS == Status) {
		printf("PushSQStack succeed!\n");
	}
	else {
		printf("PushSQStack failed!\n");
	}
	*/

	PopSQStack(SqStack, PopData);
	if (SUCCESS == Status) {
		printf("PushSQStack succeed!\n");
	}
	else {
		printf("PushSQStack failed!\n");
	}

	PrintSQStack(SqStack);
}


/*SQ_DOUBLE_STACK*/
LIST_STATUS CreateSQDoubleStack(SQ_DOUBLE_STACK *SqDbStack, int CreateNum) {
	SQ_DOUBLE_STACK *TraDbStack;
	int TraIndex;

	printf("CreateSQDoubleStack start\n");

	if (NULL == SqDbStack || CreateNum > MAXSIZE) {
		return ERROR;	
	}

	for (TraIndex = 0; TraIndex < MAXSIZE; ++TraIndex) {
		if (TraIndex <=1 || TraIndex > 2) {
			SqDbStack->Data[TraIndex] = TraIndex;
		}
	}

	SqDbStack->Top1 = 1;
	SqDbStack->Top2 = 3;

	printf("CreateSQDoubleStack start\n");
	return SUCCESS;
}

void PrintSQDoubleStack(SQ_DOUBLE_STACK * const SqDbStack) {
	SQ_DOUBLE_STACK *TraDbStack = SqDbStack;
	int TraIndex;

	printf("PrintSQDoubleStack start\n");

	printf("TraDbStack->Top1 = %d\n", TraDbStack->Top1);
	printf("TraDbStack->Top2 = %d\n", TraDbStack->Top2);
	for (TraIndex = 0; TraIndex < MAXSIZE; ++TraIndex) {
		printf("PrintSQDoubleStack->Data[TraIndex] = %d\n", TraDbStack->Data[TraIndex]);
	}

	printf("PrintSQDoubleStack end\n\n");
}

LIST_STATUS PushSQDoubleStack(SQ_DOUBLE_STACK *SqDbStack, int PushData, int PushStackNum) {
	printf("PushSQDoubleStack start\n");

	if (NULL == SqDbStack || SqDbStack->Top1 + 1 == SqDbStack->Top2) {
		return ERROR;	
	}

	if (1 == PushStackNum) {
		SqDbStack->Data[++SqDbStack->Top1] = PushData;
	
	} else if (2 == PushStackNum) {
		SqDbStack->Data[--SqDbStack->Top2] = PushData;
	}

	printf("PushSQDoubleStack end\n");
	return SUCCESS;
}

LIST_STATUS PopSQDoubleStack(SQ_DOUBLE_STACK *SqDbStack, int *PopData, int PopStackNum) {
	printf("PopSQDoubleStack start\n");

	if (NULL == SqDbStack) {
		return ERROR;
	}

	if (1 == PopStackNum) {
		if (SqDbStack->Top1 == -1) {
			return ERROR;
		} else {
			*PopData = SqDbStack->Data[SqDbStack->Top1--];
		}
	}
	else if (2 == PopStackNum) {
		if (SqDbStack->Top2 == MAXSIZE) {
			return ERROR;
		} else {
			*PopData = SqDbStack->Data[SqDbStack->Top2++];
		}
	}

	printf("PopSQDoubleStack end\n");
	return SUCCESS;
}

void OperateSQDoubleStack(void) {
	LIST_STATUS Status;
	SQ_DOUBLE_STACK  *SqDbStack = (SQ_DOUBLE_STACK *)malloc(sizeof(SQ_DOUBLE_STACK));
	int CreateNum = 4;
	int PushData = 10;
	int PushStackNum = 1;

	int PopStackNum = 1;
	int *PopData = (int *)malloc(sizeof(int));

	Status = CreateSQDoubleStack(SqDbStack, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateSQDoubleStack succeed!\n");
	}
	else {
		printf("CreateSQDoubleStack failed!\n");
	}

	PrintSQDoubleStack(SqDbStack);

	/*
	Status = PushSQDoubleStack(SqDbStack, PushData, PushStackNum);
	if (SUCCESS == Status) {
		printf("PushSQDoubleStack succeed!\n");
	}
	else {
		printf("PushSQDoubleStack failed!\n");
	}
	*/

	Status = PopSQDoubleStack(SqDbStack, PopData, PopStackNum);
	if (SUCCESS == Status) {
		printf("PopSQDoubleStack succeed!\n");
		printf("*PopData = %d\n", *PopData);
	}
	else {
		printf("PopSQDoubleStack failed!\n");
	}

	PrintSQDoubleStack(SqDbStack);
}


/*LinkStack*/
LIST_STATUS CreateLinkStack(LINK_STACK *LinkStack, Node *LinkHead, int CreateNum) {
	LINK_STACK *TraStack = LinkStack;
	Node *TraNode = LinkHead;
	Node *CreateNode;
	int TraIndex = 0;
	
	printf("CreateLinkStack start\n");

	if (NULL == LinkStack || NULL == LinkHead) {
		return ERROR;
	}

	/*Create empty link*/
	LinkHead->Data = 4;
	LinkHead->Next = NULL;

	LinkStack->Top = LinkHead;
	LinkStack->Count = CreateNum;
	
	for (TraIndex = 1; TraIndex <= CreateNum - 1; ++TraIndex) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = TraIndex;

		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		TraNode = TraNode->Next;
	}

	printf("CreateLinkStack end\n");
	return SUCCESS;
}

LIST_STATUS PrintLinkStack(LINK_STACK * const LinkStack) {
	Node *TraStackNode;

	printf("PrintLinkStack start\n");

	if (NULL == LinkStack) {
		return ERROR;
	}

	printf("LinkStack->Top = 0x%x\n", LinkStack->Top);
	printf("LinkStack->Count = %d\n", LinkStack->Count);

	TraStackNode = LinkStack->Top;

	while (TraStackNode != NULL) {
		printf("TraStackNode = 0x%x, TraStackNode->Data = %d\n", TraStackNode, TraStackNode->Data);
		TraStackNode = TraStackNode->Next;
	}

	printf("PrintLinkStack end\n\n");
	return SUCCESS;
}

LIST_STATUS PushLinkStack(LINK_STACK *LinkStack, int PushData) {
	LINK_STACK *TraLinkStack = LinkStack;
	Node *PushNode;

	printf("PushLinkStack start\n");

	if (NULL == LinkStack) {
		return ERROR;
	}

	PushNode = (Node *)malloc(sizeof(Node));
	PushNode->Data = PushData;
	PushNode->Next = TraLinkStack->Top;

	TraLinkStack->Top = PushNode;
	TraLinkStack->Count++;

	printf("PushLinkStack end\n");
	return SUCCESS;
}

LIST_STATUS PopLinkStack(LINK_STACK *LinkStack, int *PopData) {
	LINK_STACK *TraLinkStack = LinkStack;
	LINK_STACK *DeleteNode;

	printf("PopLinkStack start\n");

	if (NULL == LinkStack || NULL == LinkStack->Top) {
		return ERROR;
	}

	*PopData = TraLinkStack->Top->Data;

	DeleteNode = TraLinkStack->Top;
	TraLinkStack->Top = TraLinkStack->Top->Next;
	TraLinkStack->Count--;
	free(DeleteNode);

	printf("PopLinkStack end\n");
	return SUCCESS;
}

void OperateLinkStack(void) {
	LIST_STATUS Status;
	
	Node *LinkHead = (Node *)malloc(sizeof(Node));
	int CreateNum = 4;
	int PushData = 5;
	int *PopData = (int *)malloc(sizeof(int));
	
	LINK_STACK *LinkStack = (LINK_STACK *)malloc(sizeof(LINK_STACK));
	LinkStack->Top = NULL;
	LinkStack->Count = 0;

	Status = CreateLinkStack(LinkStack, LinkHead, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateLinkStack succeed!\n");
	}
	else {
		printf("CreateLinkStack failed!\n");
	}

	PrintLinkStack(LinkStack);

	/*
	Status = PushLinkStack(LinkStack, PushData);
	if (SUCCESS == Status) {
		printf("PushLinkStack succeed!\n");
	}
	else {
		printf("PushLinkStack failed!\n");
	}
	*/

	Status = PopLinkStack(LinkStack, PopData);
	if (SUCCESS == Status) {
		printf("PopLinkStack succeed!\n");
		printf("*PopData = %d\n", *PopData);
	}
	else {
		printf("PopLinkStack failed!\n");
	}

	PrintLinkStack(LinkStack);
}


/*recurrence*/
void FabByArr(void) {
	int i;
	int RecArr[5];

	RecArr[0] = 0;
	RecArr[1] = 1;	

	for (i = 2; i < 5; ++i) {
		RecArr[i] = RecArr[i - 2] + RecArr[i - 1];	
	}

	for (i = 0; i < 5; ++i) {
		printf("RecArr[%d] = %d\n", i, RecArr[i]);
	}
}

int FabRec(int i) {
	if (0 == i) {
		return 0;
	}
	else if (1 == i) {
		return 1; 
	}
	
	return FabRec(i - 2) + FabRec(i - 1);
}

void PrintFabByRec(void) {
	int i = 0;

	for (i = 0; i < 5; ++i) {
		printf("The %d value = %d\n", i, FabRec(i));
	}
}


/*LINK_STACK*/
LIST_STATUS CreateRNPLinkStack(LINK_STACK *LinkStack, Node *LinkHead, int CreateNum) {
	LINK_STACK *TraStack = LinkStack;
	Node *TraNode = LinkHead;
	Node *CreateNode;
	int TraIndex = 0;

	printf("CreateRNPLinkStack start\n");

	if (NULL == LinkStack || NULL == LinkHead) {
		return ERROR;
	}

	/*Create empty link*/
	LinkHead->Data = 'a';
	LinkHead->Next = NULL;

	LinkStack->Top = LinkHead;
	LinkStack->Count = CreateNum;

	for (TraIndex = 1; TraIndex <= CreateNum - 1; ++TraIndex) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = TraNode->Data + 1;

		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		TraNode = TraNode->Next;
	}

	printf("CreateRNPLinkStack end\n");
	return SUCCESS;
}

LIST_STATUS PrintCharLinkStack(LINK_STACK * const LinkStack) {
	Node *TraStackNode;

	printf("PrintCharLinkStack start\n");

	if (NULL == LinkStack || NULL == LinkStack->Top) {
		return ERROR;
	}

	printf("LinkStack->Top = 0x%x\n", LinkStack->Top);
	printf("LinkStack->Count = %d\n", LinkStack->Count);

	TraStackNode = LinkStack->Top;

	while (TraStackNode != NULL) {
		printf("TraStackNode = 0x%x, TraStackNode->Data = %c\n", TraStackNode, TraStackNode->Data);
		TraStackNode = TraStackNode->Next;
	}

	printf("PrintCharLinkStack end\n\n");
	return SUCCESS;
}

void OperateCharLinkStack(void) {
	LIST_STATUS Status;
	LINK_STACK *LinkStack = (LINK_STACK *)malloc(sizeof(LINK_STACK));
	Node *LinkHead = (Node *)malloc(sizeof(Node));
	int CreateNum = 5;
	int PushData = 'i';
	int *PopData = (int *)malloc(sizeof(int));

	Status = CreateRNPLinkStack(LinkStack, LinkHead, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateRNPLinkStack succeed!\n");
	}
	else {
		printf("CreateRNPLinkStack failed!\n");
	}

	PrintCharLinkStack(LinkStack);

	/*
	Status = PushLinkStack(LinkStack, PushData);
	if (SUCCESS == Status) {
		printf("PushLinkStack succeed!\n");
	}
	else {
		printf("PushLinkStack failed!\n");
	}	
	*/
	
	Status = PopLinkStack(LinkStack, PopData);
	if (SUCCESS == Status) {
		printf("PopLinkStack succeed!\n");
		printf("*PopData = %d\n", *PopData);
	}
	else {
		printf("PopLinkStack failed!\n");
	}

	PrintCharLinkStack(LinkStack);
	
}


/*RPN*/
bool IfPopValid(LINK_STACK * const LinkStack, char NewChar) {
	LINK_STACK *TraStackNode = LinkStack;

	printf("IfNewCharPriorityNotHigh start\n");

	/*Empty LinkStack*/
	if (TraStackNode->Top == NULL && TraStackNode->Count == 0) {
		return false;
	}

	if (NewChar == '(') {
		return false;
	} else if (NewChar == ')') {
		return true;
	} else if (NewChar == '+' || NewChar == '-') {
		return true;	
	} else if (NewChar == '*' || NewChar == '/') {
		if (TraStackNode->Top->Data == '+' || TraStackNode->Top->Data == '-') {
			return false;
		} else if (TraStackNode->Top->Data == '*' || TraStackNode->Top->Data == '/') {
			return true;
		}
	}

	printf("IfNewCharPriorityNotHigh end\n\n");
}

LIST_STATUS PushInfixExpression(LINK_STACK *LinkStack, char NewChar) {
	LINK_STACK *TraStackNode = LinkStack;
	Node *AddNode = (Node *)malloc(sizeof(Node));

	LIST_STATUS Status;

	printf("PushInfixExpression start\n");
	printf("In PushInfixExpression, NewChar = %c\n", NewChar);

	Status = PushLinkStack(LinkStack, NewChar);

	printf("PushInfixExpression end\n\n");

	return Status;
}

LIST_STATUS PopInfixExpression(LINK_STACK *LinkStack, char NewChar, char *PostfixExpression, int *PostEIndex) {
	LINK_STACK *TraStackNode = LinkStack;
	int *PopData = (int)malloc(sizeof(int));
	
	printf("PopInfixExpression start\n");

	printf("PopData = 0x%x\n", PopData);
	printf("In PopInfixExpression, NewChar = %c\n", NewChar);
	printf("In PopInfixExpression, PostfixExpression = %s\n", PostfixExpression);

	PrintCharLinkStack(LinkStack);

	if (NewChar == ')') {
		while (TraStackNode->Top != NULL) {
			if (TraStackNode->Top->Data != '(') {
				PopLinkStack(TraStackNode, PopData);
				PostfixExpression[(*PostEIndex)++] = *PopData;
				PostfixExpression[(*PostEIndex)++] = ' ';
			}else if (TraStackNode->Top->Data == '(') {
				PopLinkStack(TraStackNode, PopData);
				break;
			}
			//TraStackNode->Top = TraStackNode->Top->Next;
		}
	} else if (NewChar == '+' || NewChar == '-') {
		while ((TraStackNode->Top != NULL) && (TraStackNode->Top->Data != '(')) {
			PopLinkStack(TraStackNode, PopData);
			PostfixExpression[(*PostEIndex)++] = *PopData;
			PostfixExpression[(*PostEIndex)++] = ' ';

			//TraStackNode->Top = TraStackNode->Top->Next;
		}
		PushLinkStack(LinkStack, NewChar);
	} else if (NewChar == '*' || NewChar == '/') {
		while ( (TraStackNode->Top != NULL) && (TraStackNode->Top->Data != '(') && 
			((TraStackNode->Top->Data == '*') || (TraStackNode->Top->Data == '/')) ) {
			PopLinkStack(TraStackNode, PopData);
			printf("*PopData = %c\n", *PopData);
			PostfixExpression[(*PostEIndex)++] = *PopData;
			PostfixExpression[(*PostEIndex)++] = ' ';

			//TraStackNode->Top = TraStackNode->Top->Next;
		}
		PushLinkStack(LinkStack, NewChar);
	}

	printf("In PopInfixExpression, PostfixExpression = %s\n", PostfixExpression);

	printf("PopData = 0x%x\n", PopData);
	free(PopData);

	PrintCharLinkStack(LinkStack);

	printf("PopInfixExpression end\n\n");
}

int OpPopDataFunc(char Op, int Data1, int Data2) {
	int ResData;

	if (Op == '+') {
		ResData = Data2 + Data1;
		return ResData;
	} else if (Op == '-') {
		ResData = Data2 - Data1;
		return ResData;
	} else if (Op == '*') {
		ResData = Data2 * Data1;
		return ResData;
	} else if (Op == '/') {
		ResData = Data2 / Data1;
		return ResData;
	}
}

int OpPostfixFunc(char *PostfixExpressionInput, int PostfixExpressionInputSize) {
	//char PostfixExpression[] = "1 10 + 234 - 10 *";
	//char PostfixExpression[] = "2 1 +";
	//char PostfixExpression[] = "9 3 1 - 3 * + 10 2 / +";
	char *PostfixExpression = PostfixExpressionInput;

	int Ret;
	int TraIndex = 0;

	LINK_STACK *LinkStack = (LINK_STACK *)malloc(sizeof(LINK_STACK));
	LinkStack->Top = NULL;
	LinkStack->Count = 0;
	
	int PushData = 0;
	int *PopData1 = (int *)malloc(sizeof(int));
	int *PopData2 = (int *)malloc(sizeof(int));	
	int *ResData1 = (int *)malloc(sizeof(int));
	int ResData2 = 0;
	int OpData;	

	printf("\nOpPostfixFunc start\n");
	printf("In OpPostfixFunc, PostfixExpression = %s\n", PostfixExpression);
	printf("PostfixExpressionInputSize = %d\n", PostfixExpressionInputSize);

	for (TraIndex = 0; TraIndex < PostfixExpressionInputSize; ++TraIndex) {
		printf("PostfixExpression[%d] = %c\n", TraIndex, PostfixExpression[TraIndex]);
		if (PostfixExpression[TraIndex] == ' ') {
			continue;
		} else if (PostfixExpression[TraIndex] >= '0' && PostfixExpression[TraIndex] <= '9') {
			PushData = PostfixExpression[TraIndex] - 48;
			printf("PushData 01 = %d\n", PushData);

			/*Judge wheather PostfixExpression[TraIndex] is long number*/
			while ((TraIndex + 1 < PostfixExpressionInputSize) && (PostfixExpression[TraIndex + 1] != ' ')) {
				printf("In while, PostfixExpression[%d] = %c\n", TraIndex + 1, PostfixExpression[TraIndex + 1]);
				PushData = PushData * 10 + (PostfixExpression[TraIndex + 1] - 48);
				++TraIndex;				
				printf("PushData 02 = %d\n", PushData);
			}

			/*Push should make PostfixExpression[TraIndex] int type */
			PushLinkStack(LinkStack, PushData);
			PrintLinkStack(LinkStack);
		} else if (PostfixExpression[TraIndex] == '+' || PostfixExpression[TraIndex] == '-' || PostfixExpression[TraIndex] == '*' || PostfixExpression[TraIndex] == '/') {
			PopLinkStack(LinkStack, PopData1);
			PopLinkStack(LinkStack, PopData2);

			/*
			printf("*PopData1 = %d\n", *PopData1);
			printf("*PopData2 = %d\n", *PopData2);			
			*/
			OpData = OpPopDataFunc(PostfixExpression[TraIndex], *PopData1, *PopData2);
			printf("OpData = %d\n", OpData);

			PushLinkStack(LinkStack, OpData);
		}	
	}

	PrintLinkStack(LinkStack);

	if (LinkStack->Count == 1) {
		PopLinkStack(LinkStack, ResData1);

		printf("*ResData1 = %d\n", *ResData1);

		ResData2 = *ResData1;
	}

	free(LinkStack);
	free(ResData1);
	free(PopData1);
	free(PopData2);

	printf("In OpPostfixFunc, ResData2 = %d\n", ResData2);

	return ResData2;
}

/*RPN*/
void RPNExpression(void) {
	char InfixExpression[] = "9+(3-1)*3+10/2";//9 3 1 - 3 * + 10 2 / +
	//char InfixExpression[] = "9313102";//9313102
	//char InfixExpression[] = "2+1*3+2/1";//2 1 3 * + 2 1 / +
	//char InfixExpression[] = "14*23/32";//14 23 * 32 /
	//char InfixExpression[] = "(2+1)";//2 1 +
	//char InfixExpression[] = "3+(2-1)";//3 2 1 - +
	//char InfixExpression[] = "3+(2-1)*4";//3 2 1 - 4 * +

	char *PostfixExpression = (char *)malloc(sizeof(char) * sizeof(InfixExpression) * 2);
	int PostEIndex = 0;
	int TraIndex = 0;
	int ResData;
	
	LINK_STACK *LinkStack = (LINK_STACK *)malloc(sizeof(LINK_STACK));
	LinkStack->Top = NULL;
	LinkStack->Count = 0;

	LINK_STACK *TraStackNode = LinkStack;

	char *PopData = (char *)malloc(sizeof(char));

	printf("InfixExpression = %s\n", InfixExpression);
	
	for (TraIndex = 0; TraIndex < strlen(InfixExpression); ++TraIndex) {
		printf("In RPNString, InfixExpression[%d] = %c\n", TraIndex, InfixExpression[TraIndex]);
		if (InfixExpression[TraIndex] >= '0' && InfixExpression[TraIndex] <= '9') {
			PostfixExpression[PostEIndex++] = InfixExpression[TraIndex];
			/*long number*/
			while ( (TraIndex + 1 < strlen(InfixExpression)) && ((InfixExpression[TraIndex + 1] >= '0' && InfixExpression[TraIndex + 1] <= '9')) ) {
				PostfixExpression[PostEIndex++] = InfixExpression[++TraIndex];				
			}
			PostfixExpression[PostEIndex++] = ' ';
		} else if (IfPopValid(LinkStack, InfixExpression[TraIndex]) == true) {
			PopInfixExpression(LinkStack, InfixExpression[TraIndex], PostfixExpression, &PostEIndex);
		} else if (IfPopValid(LinkStack, InfixExpression[TraIndex]) == false) {
			PushInfixExpression(LinkStack, InfixExpression[TraIndex]);
		}
	}

	printf("In RPNString, PostfixExpression = %s\n", PostfixExpression);

	/*Pop remain operator*/
	printf("Pop remain operator\n");
	while ((TraStackNode->Top != NULL) && (TraStackNode->Count != 0)) {
		if (TraStackNode->Top->Next == NULL) {
			PopLinkStack(LinkStack, PopData);
			PostfixExpression[PostEIndex++] = *PopData;
		} else {
			PopLinkStack(LinkStack, PopData);
			PostfixExpression[PostEIndex++] = *PopData;
			PostfixExpression[PostEIndex++] = ' ';
		}
	}

	PrintCharLinkStack(LinkStack);

	PostfixExpression[PostEIndex++] = '\0';
	
	printf("In RPNString, PostfixExpression = %s\n\n", PostfixExpression);
	
	/*Operate PostfixExpression*/
	ResData = OpPostfixFunc(PostfixExpression, strlen(PostfixExpression));

	printf("In RPNString, ResData = %d\n", ResData);

	free(PostfixExpression);
	free(LinkStack);
}


void testChar(void) {
	char ch1[5];
	ch1[0] = 'a';
	int i = 0;
	//printf("a = %c\n", ++ch1[0]);

	printf("\n");
	for (i = 1; i < 5; ++i) {
		ch1[i] = ch1[i - 1] + 1;
		printf("ch1[%d] = %c\n", i, ch1[i]);
	}	
}

void test01(int ch1) {
	printf("ch1 = %c\n", ch1);
}

void test02(void) {
	int ch1 = 'd';
	test01(ch1);
}

void test03(void) {
	char ch1 = 100;
	printf("ch1 = %d", ch1);
}

void test04(void) {
	char Ch1[] = "hello";
	printf("strlen(Ch1) = %d\n", strlen(Ch1));
}

void test05(void) {
	int Ch1 = '5';
	int Data1;
	Data1 = Ch1 - '1';
	printf("Data1 = %d\n", Data1);
}

void test06(void) {
	int Ch1 = ' ';
	printf("Ch1 = %c\n", Ch1);
	printf("Ch1 = %d\n", Ch1);
}

void test07(void) {
	char Ch1 = '��';
	printf("Ch1 = %c\n", Ch1);
}


/*SqQueue*/
LIST_STATUS CreateSqQueue(SQ_QUEUE *SqQueue) {
	SQ_QUEUE *TraSqQueue = SqQueue;
	int TraIndex = 0;

	printf("CreateSqQueue start\n");

	if (NULL == TraSqQueue) {
		return ERROR;
	}

	/*Empty queue*/
	TraSqQueue->Front = 0;
	TraSqQueue->Rear = 0;

	/*Assignment*/
	for (TraIndex = 0; TraIndex < 3; ++TraIndex) {
		TraSqQueue->Data[TraIndex] = TraIndex;
		TraSqQueue->Rear++;
	}

	printf("CreateSqQueue end\n");

	return SUCCESS;
}

LIST_STATUS PrintSqQueue(SQ_QUEUE *SqQueue) {
	SQ_QUEUE *TraSqQueue = SqQueue;
	int TraIndex = 0;

	printf("PrintSqQueue start\n");

	if (NULL == TraSqQueue) {
		return ERROR;
	}

	printf("TraSqQueue->front = %d\n", TraSqQueue->Front);
	printf("TraSqQueue->Rear = %d\n", TraSqQueue->Rear);

	for (TraIndex = 0; TraIndex < MAXSIZE; ++TraIndex) {
		printf("TraSqQueue->Data[%d] = %d\n", TraIndex, TraSqQueue->Data[TraIndex]);
	}

	printf("PrintSqueue end\n\n");

	return SUCCESS;
}

int SqQueueLength(SQ_QUEUE *SqQueue) {
	printf("SqQueueLength = %d\n", (SqQueue->Rear - SqQueue->Front + MAXSIZE) % MAXSIZE);
	return (SqQueue->Rear - SqQueue->Front + MAXSIZE) % MAXSIZE;
}

LIST_STATUS EnterSqQueue(SQ_QUEUE *SqQueue, int EnterData) {
	SQ_QUEUE *TraSqQueue = SqQueue;

	printf("EnterSqQueue start\n");

	if (NULL == TraSqQueue) {
		return ERROR;
	}

	if ((TraSqQueue->Rear + 1 + MAXSIZE) % MAXSIZE == TraSqQueue->Front) {
		return ERROR;	
	}

	TraSqQueue->Data[TraSqQueue->Rear] = EnterData;
	TraSqQueue->Rear = (TraSqQueue->Rear + 1) % MAXSIZE;

	printf("EnterSqQueue end\n");

	return SUCCESS;
}

LIST_STATUS ExitSqQueue(SQ_QUEUE *SqQueue, int *ExitData) {
	SQ_QUEUE *TraSqQueue = SqQueue;

	printf("ExitSqQueue start\n");

	if (NULL == TraSqQueue) {
		return ERROR;
	}

	if (TraSqQueue->Rear == TraSqQueue->Front) {
		return ERROR;
	}

	*ExitData = TraSqQueue->Data[TraSqQueue->Front];
	TraSqQueue->Front = (TraSqQueue->Front + 1) % MAXSIZE;

	printf("ExitSqQueue end\n");

	return SUCCESS;
}


void OperateQueue(void) {
	LIST_STATUS Status;
	
	SQ_QUEUE *SqQueue = (SQ_QUEUE *)malloc(sizeof(SQ_QUEUE));
	int *ExitData = (int *)malloc(sizeof(int));
	int EnterData = 3;


	Status = CreateSqQueue(SqQueue);
	if (SUCCESS == Status) {
		printf("CreateSqQueue succeed!\n");
	} else {
		printf("CreateSqQueue failed!\n");
	}

	SqQueueLength(SqQueue);
	PrintSqQueue(SqQueue);
	
	Status  = EnterSqQueue(SqQueue, EnterData);
	if (SUCCESS == Status) {
		printf("EnterSqQueue succeed!\n");
	} else {
		printf("EnterSqQueue failed!\n");
	}	

	/*
	Status = ExitSqQueue(SqQueue, ExitData);
	if (SUCCESS == Status) {
		printf("ExitSqQueue succeed!\n");
	}
	else {
		printf("ExitSqQueue failed!\n");
	}
	*/

	SqQueueLength(SqQueue);
	PrintSqQueue(SqQueue);
	

	free(SqQueue);
	free(ExitData);

	SqQueue = NULL;
	ExitData = NULL;
}


/*LinkQueue*/
LIST_STATUS CreateLinkQueue(LINK_QUEUE *LinkQueue, Node *HeadNode, int CreateNum) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *TraNode = HeadNode;
	Node *CreateNode;
	int TraIndex = 0;	

	printf("CreateLinkQueue start!\n");

	if (NULL == LinkQueue || NULL == HeadNode) {
		return ERROR;
	}

	for (TraIndex = 0; TraIndex < CreateNum - 1; ++TraIndex) {
		CreateNode = (Node *)malloc(sizeof(Node));
		CreateNode->Data = TraIndex;

		CreateNode->Next = TraNode->Next;
		TraNode->Next = CreateNode;

		TraLinkQueue->Rear = CreateNode;		
		TraNode = TraNode->Next;
	}

	printf("CreateLinkQueue end!\n");
	return SUCCESS;
}

LIST_STATUS DelLinkQueue(LINK_QUEUE * LinkQueue, Node *HeadNode) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *TraNode = HeadNode;
	Node *DelNode;

	printf("DelLinkQueue start!\n");

	if (NULL == LinkQueue || NULL == HeadNode) {
		return ERROR;
	}

	TraNode = TraNode->Next;

	TraLinkQueue->Rear = TraLinkQueue->Front;

	while (TraNode != NULL) {
		DelNode = TraNode;
		TraNode = TraNode->Next;
		
		free(DelNode);
		DelNode = NULL;
	}

	HeadNode->Next = NULL;

	printf("DelLinkQueue end!\n");
	return SUCCESS;
}

LIST_STATUS PrintLinkQueue(LINK_QUEUE * LinkQueue) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *NodeHead = LinkQueue->Front;

	printf("PrintLinkQueue start!\n");

	if (NULL == TraLinkQueue) {
		printf("LinkQueue = NULL\n");
		return ERROR;
	}

	printf("TraLinkQueue->Front = %x\n",TraLinkQueue->Front);
	printf("TraLinkQueue->Rear = %x\n", TraLinkQueue->Rear);

	while (NodeHead != NULL) {
		printf("NodeHead = 0x%lx, NodeHead->Data = %d, NodeHead->Next = 0x%lx\n", NodeHead, NodeHead->Data, NodeHead->Next);
		NodeHead = NodeHead->Next;
	}

	printf("PrintLinkQueue end!\n\n");
	return SUCCESS;
}

LIST_STATUS EnterLinkQueue(LINK_QUEUE * LinkQueue, int AddData) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *AddNode = (Node *)malloc(sizeof(Node));

	printf("EnterLinkQueue start!\n");

	if (NULL == TraLinkQueue) {
		return ERROR;
	}

	AddNode->Data = AddData;
	AddNode->Next = NULL;

	TraLinkQueue->Rear->Next = AddNode;
	TraLinkQueue->Rear = AddNode;

	printf("EnterLinkQueue end!\n");
	return SUCCESS;
}

LIST_STATUS ExitLinkQueue(LINK_QUEUE * LinkQueue, int *DelData) {
	LINK_QUEUE *TraLinkQueue = LinkQueue;
	Node *DelNode;

	printf("ExitLinkQueue start!\n");

	if (NULL == TraLinkQueue) {
		return ERROR;
	}
	
	if (TraLinkQueue->Front == TraLinkQueue->Rear) {
		printf("LinkQueue is empty!\n");
		return ERROR;	
	}

	*DelData = TraLinkQueue->Front->Data;
	DelNode = TraLinkQueue->Front;

	TraLinkQueue->Front = TraLinkQueue->Front->Next;
	free(DelNode);
	DelNode = NULL;

	printf("ExitLinkQueue end!\n");
	return SUCCESS;
}

void OperateLinkQueue(void) {
	LINK_QUEUE *LinkQueue = (LINK_QUEUE *)malloc(sizeof(LINK_QUEUE));
	LIST_STATUS Status;

	int CreateNum = 3;
	int AddData = 4;
	int *DelData = (int *)malloc(sizeof(int));

	/*Create empty linkQueue*/
	Node *HeadNode = (Node *)malloc(sizeof(Node));
	HeadNode->Data = CreateNum;
	HeadNode->Next = NULL;
	LinkQueue->Front = HeadNode;
	LinkQueue->Rear = HeadNode;

	Status = CreateLinkQueue(LinkQueue, HeadNode, CreateNum);
	if (SUCCESS == Status) {
		printf("CreateLinkQueue succeed!\n");
	}
	else {
		printf("CreateLinkQueue failed!\n");
	}
	
	PrintLinkQueue(LinkQueue);

	
	Status = EnterLinkQueue(LinkQueue, AddData);
	if (SUCCESS == Status) {
		printf("EnterLinkQueue succeed!\n");
	}
	else {
		printf("EnterLinkQueue failed!\n");
	}
	
	PrintLinkQueue(LinkQueue);
	

	/*
	Status = ExitLinkQueue(LinkQueue, DelData);
	if (SUCCESS == Status) {
		printf("ExitLinkQueue succeed!\n");
	}
	else {
		printf("ExitLinkQueue failed!\n");
	}

	PrintLinkQueue(LinkQueue);
	*/

	/*
	Status = DelLinkQueue(LinkQueue, HeadNode);
	if (SUCCESS == Status) {
		printf("DelLinkQueue succeed!\n");
	}
	else {
		printf("DelLinkQueue failed!\n");
	}

	PrintLinkQueue(LinkQueue);
	*/
	
	free(DelData);

	LinkQueue = NULL;
	DelData = NULL;
	HeadNode = NULL;
}




/*String*/
int StringLen(const char * const Str) {
	char *TraStr = Str;
	int StrLen = 0;

	printf("StringLen start\n");
	if (NULL == Str) {
		return 0;	
	}

	while (*TraStr != '\0') {
		StrLen++;
		TraStr++;
	}	

	printf("StringLen end\n");	
	return StrLen;
}

LIST_STATUS StrCopy(char *T, char *S) {
	char *TraS = S;
	char *TraT = T;

	printf("StrCopy start\n");

	if (T == NULL || S == NULL ) {
		return ERROR;	
	}

	while (*TraS != '\0') {
		*TraT = *TraS;
		TraT++;
		TraS++;
	}

	*TraT = '\0';

	printf("StrCopy end\n");

	return SUCCESS;
}

int StrCopmare(const char *Str1, const char *Str2) {
	char *TraStr1 = Str1;
	char *TraStr2 = Str2;
	int ret;
	int Str1Len = StringLen(Str1);
	int Str2Len = StringLen(Str2);

	printf("StrCopmare start\n");

	printf("Str1 = %s\n", Str1);
	printf("Str2 = %s\n", Str2);

	while (*TraStr1 != '\0' || *TraStr2 != '\0') {
		if (*TraStr1 == *TraStr2) {
			TraStr1++;
			TraStr2++;
		}
		else {
			break;
		}

	}

	if (*TraStr1 == '\0' && *TraStr2 == '\0' && Str1Len == Str2Len) {
		ret = 0;
		goto EXIT;
	}	

	if (*TraStr1 == '\0' && Str1Len < Str2Len) {
		ret = -1;
		goto EXIT;
	}

	if (*TraStr1 != '\0' && *TraStr2 != '\0' && *TraStr1 < *TraStr2) {
		ret = -1;
		goto EXIT;
	}

	ret = 1;

EXIT:
	printf("StrCopmare end\n");
	return ret;

}

LIST_STATUS StrConcat(char *NewStr, const char *Str1, const char *Str2) {
	char *TraNewStr = NewStr;
	char *TraStr1 = Str1;
	char *TraStr2 = Str2;
	
	printf("StrConcat start\n");
	if (TraNewStr == NULL || Str1 == NULL || Str2 == NULL) {
		return ERROR;
	}

	while (*TraStr1 != '\0') {
		*TraNewStr = *TraStr1;

		TraNewStr++;
		TraStr1++;
	}
	
	while (*TraStr2 != '\0') {
		*TraNewStr = *TraStr2;

		TraNewStr++;
		TraStr2++;
	}

	*TraNewStr = '\0';
	
	printf("StrConcat end\n");
	return SUCCESS;
}

LIST_STATUS SubString(char *Sub, const char *Str, const unsigned int Pos, const unsigned int SubLen) {
	char *TraSub = Sub;
	char *TraStr = Str;
	unsigned int Index = 0;

	printf("SubString start\n");
	if (NULL == Str || NULL == Sub) {
		return ERROR;
	}

	if (Pos < 1 || Pos > StringLen(Str)) {
		return ERROR;
	}

	if (SubLen > StringLen(Str) - Pos + 1) {
		return ERROR;
	}

	/*TraStr move to Pos*/
	for (Index = 0; Index < Pos; ++Index) {
		TraStr++;
	}

	/*Copy Str into Sub, lenth is SubLen*/
	for (Index = 0; Index < SubLen; ++Index) {
		*TraSub = *TraStr;
		TraStr++;
		TraSub++;
	}

	*TraSub = '\0';
	
	printf("SubString end\n");
	return SUCCESS;
}


void OperateString(void) {
	LIST_STATUS Status;
	char Str1[] = "hello199";
	char Str2[] = "hello200";
	int Str1Len;
	char *CpyStr = (char *)malloc(sizeof(Str1));
	int CmpResult;

	char *ConcatStr = (char *)malloc(sizeof(Str1) + sizeof(Str2) + 1);

	char *SubStr = (char *)malloc(sizeof(Str1));
	unsigned int Pos = 2;
	unsigned int SubLen = 3;
	
/*
	Str1Len = StringLen(Str1);
	printf("Str1Len = 0x%x\n", Str1Len);

	Status = StrCopy(CpyStr, Str1);
	if (Status == SUCCESS) {
		printf("StrCopy successful!\n");
	}else {
		printf("StrCopy failed!\n");
	}	
	printf("CpyStr = %s\n\n", CpyStr);

	if (CpyStr != NULL) {
		free(CpyStr);
		CpyStr = NULL;
	}

	CmpResult = StrCopmare(Str1, Str2);
	printf("CmpResult = %d\n", CmpResult);

	Status = StrConcat(ConcatStr, Str1, Str2);
	if (Status == SUCCESS) {
		printf("StrConcat successful!\n");
	}
	else {
		printf("StrConcat failed!\n");
	}
	printf("ConcatStr = %s\n", ConcatStr);	

	if (ConcatStr != NULL) {
		free(ConcatStr);
		ConcatStr = NULL;
	}
*/

	Status = SubString(SubStr, Str1, Pos, SubLen);
	if (Status == SUCCESS) {
		printf("SubString successful!\n");
	}
	else {
		printf("SubString failed!\n");
	}
	printf("SubStr = %s\n", SubStr);
}