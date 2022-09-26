#include <stdio.h>
#include "TestDataStruct.h"
#include "DataStruct.h"

static int TestNum = 0;
static int PassNum = 0;
static int FaildNum = 0;

void InitNum(void) {
	TestNum = 0;
	PassNum = 0;
	FaildNum = 0;
}

void TestResult(void) {
	printf("Print test result;\n");
	printf("TestNum = %d, PassNum = %d, FaildNum = %d\n", TestNum, PassNum, FaildNum);
}

LIST_STATUS StatusTest(LIST_STATUS Status1, LIST_STATUS Status2) {
	TestNum++;

	printf("StatusTest:\n");
	if (Status1 == Status2) {
		printf("Test succeed!\n");
		PassNum++;
		return SUCCESS;
	} else {
		printf("%s test faild!\n", __func__);
		FaildNum++;
		return ERROR;
	}
} 

void StringCompareTest(const char *TestStr1, const char *NewStrRep) {
	int Res;
	char *TraTestStr1 = TestStr1;
	char *TraNewStrRep = NewStrRep;

	Res = StrCopmare(TraTestStr1, TraNewStrRep);
	
	if (Res == 0) {
		printf("%s test succeed!\n", __func__);
		PassNum++;
		return SUCCESS;
	}
	else {
		printf("%s test faild!\n", __func__);
		FaildNum++;
		return ERROR;
	}
}

void TestArrCreatList(void) {
	printf("\nTestArrCreatList start!\n");
	SQ_LIST L;
	StatusTest(SUCCESS, CreatList(&L));
	printf("TestArrCreatList end!\n");
	TestResult();
}

void TestGetElem(void) {
	SQ_LIST L;	
	int GetE;

	printf("\nTestGetElem start!\n");

	CreatList(&L);
	StatusTest(ERROR, GetElem(L, 0, &GetE));
	StatusTest(ERROR, GetElem(L, 4, &GetE));
	StatusTest(SUCCESS, GetElem(L, 2, &GetE));
	printf("TestGetElem end!\n");

	TestResult();
}

void TestLocateElem(void) {
	SQ_LIST L;
	
	printf("\nTestLocateElem start!\n");

	CreatList(&L);

	StatusTest(SUCCESS, LocateElem(L, 1));

	ClearList(&L);
	StatusTest(ERROR, LocateElem(L, 1));

	printf("\nTestLocateElem end!\n");
	TestResult();
}

//LIST_STATUS InsertElem01(SQ_LIST * const L, const int InsertIndex, const int InsertElm)

void TestInsertElem01(void) {
	SQ_LIST L;

	printf("\nTestInsertElem start!\n");

	CreatList(&L);
	StatusTest(ERROR, InsertElem01(&L, 0, 15));
	StatusTest(ERROR, InsertElem01(&L, 5, 15));
	
	StatusTest(SUCCESS, InsertElem01(&L, 2, 15));

	ClearList(&L);
	StatusTest(ERROR, InsertElem01(&L, 2, 15));
	StatusTest(ERROR, InsertElem01(&L, 2, 15));

	printf("\nTestInsertElem01 end!\n");
	TestResult();
}

void TestInsertElem02(void) {
	SQ_LIST L;

	printf("\nTestInsertElem start!\n");

	CreatList(&L);
	StatusTest(ERROR, InsertElem01(&L, 0, 15));
	StatusTest(ERROR, InsertElem01(&L, 5, 15));

	StatusTest(SUCCESS, InsertElem01(&L, 2, 15));

	ClearList(&L);
	StatusTest(ERROR, InsertElem01(&L, 2, 15));
	StatusTest(ERROR, InsertElem01(&L, 2, 15));

	printf("TestInsertElem01 end!\n");
	TestResult();
}

//LIST_STATUS DeleteElem01(SQ_LIST * const L, const int DeleteIndex)
void TestDeleteElem01(void) {
	SQ_LIST L;

	printf("\nTestDeleteElem01 start!\n");
	
	CreatList(&L);
	StatusTest(ERROR, DeleteElem01(&L, 0));
	StatusTest(ERROR, DeleteElem01(&L, 4));

	StatusTest(SUCCESS, DeleteElem01(&L, 2));

	ClearList(&L);
	StatusTest(ERROR, DeleteElem01(&L, 2));

	printf("TestDeleteElem01 end!\n");
	TestResult();
}

void TestDeleteElem02(void) {
	SQ_LIST L;

	printf("\nTestDeleteElem02 start!\n");

	CreatList(&L);
	StatusTest(ERROR, DeleteElem02(&L, 0));
	StatusTest(ERROR, DeleteElem02(&L, 4));

	StatusTest(SUCCESS, DeleteElem02(&L, 2));

	ClearList(&L);
	StatusTest(ERROR, DeleteElem02(&L, 2));

	printf("TestDeleteElem02 end!\n");
	TestResult();
}


void TestStrReplace(void) {
	OP_STATUS Status;
	char *Str1 = NULL;
	char Str1cpy[] = "12341236612";
	char Str3[] = "123";
	char StrRep[] = "hello";

	char TestStr1[] = "hello4hello6612";

	Str1 = (char *)malloc(100);
	if (Str1 == NULL) {
		goto EXIT;
	}

	Status = StrCopy(Str1, Str1cpy);
	if (Status == SUCCESS) {
		printf("StrCopy successful!\n");		
	}
	else {
		printf("StrCopy failed!\n");
		goto EXIT;
	}

	InitNum();

	Status = StrReplace(Str1, Str3, StrRep);
	
	/*Test*/
	StatusTest(SUCCESS, Status);
	StringCompareTest(TestStr1, Str1);

EXIT:
	if (Str1 != NULL) {
		free(Str1);
		Str1 = NULL;
	}

	TestResult();
}

void TestMoveBackStr(void) {
	char Str1[20] = "abc";
	unsigned int Pos1 = 1;
	unsigned int MvLen1 = 2;
	char CpmStr1[] = "aeebc";

	char Str2[10] = "abc";
	unsigned int Pos2 = 2;
	unsigned int MvLen2 = 3;
	char CpmStr2[] = "abcbc";

	unsigned int i = 0;
	
	char CpyStr[] = "ee";

	MoveBackStr(Str1, Pos1, MvLen1);
	//MoveBackStr(Str2, Pos2, MvLen2);

	printf("Str1 = %s\n", Str1);

	CopyStrWhithoutTail(Str1, Pos1, CpyStr);
	printf("Str1 = %s\n", Str1);


	InitNum();
	StringCompareTest(Str1, CpmStr1);

	//StringCompareTest(Str2, CpmStr2);
	TestResult();

}