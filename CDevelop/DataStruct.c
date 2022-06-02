#include <stdio.h>
#include "DataStruct.h"

LIST_STATUS OperatorList() {
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
	printf("Creat list:\n");
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
	printf("Clear list:\n");
	memset(L, 0, sizeof(SQ_LIST));
	return SUCCESS;
}

LIST_STATUS GetElem(const SQ_LIST L, const int GetIndex, int * const GetE) {
	if ( 0==L.Len || GetIndex<1 || GetIndex>L.Len ) {
		return ERROR;	
	}

	*GetE = L.Data[GetIndex -1];

	return SUCCESS;
}

LIST_STATUS LocateElem(const SQ_LIST L, const int LoElm) {
	int Index = 0;
	
	printf("\nLocateElem:\n");

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

	if (0 == L->Len || DeleteIndex < 1 || DeleteIndex > L->Len) {
		printf("\nInvaild Len or DeleteIndex!\n");
		return ERROR;
	}
	
	for (i = DeleteIndex - 1; i < L->Len - 1; ++i) {
		L->Data[i] = L->Data[i + 1];	
	}

	L->Len--;
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