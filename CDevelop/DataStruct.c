#include <stdio.h>
#include "DataStruct.h"

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