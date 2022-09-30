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

void ValueTest(const unsigned int Value01, const unsigned int Value02) {
	if (Value01 == Value02) {
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



/*Test String*/
void TestSubString(void) {
	char Str1[] = "abc";
	unsigned int SubPos1_01 = 1;
	unsigned int SubLen1_01 = 1;
	char *Sub1_01 = NULL;
	char Res1_01[] = "a";

	unsigned int SubPos1_02 = 2;
	unsigned int SubLen1_02 = 2;
	char *Sub1_02 = NULL;
	char Res1_02[] = "bc";

	Sub1_01 = (char *)malloc(SubLen1_01 + 1);
	if (Sub1_01 == NULL) {
		goto EXIT;
	}
	Sub1_02 = (char *)malloc(SubLen1_02 + 1);
	if (Sub1_02 == NULL) {
		goto EXIT;
	}

	SubString(Sub1_01, Str1, SubPos1_01, SubLen1_01);
	printf("Sub1_01 = %s\n\n", Sub1_01);

	SubString(Sub1_02, Str1, SubPos1_02, SubLen1_02);
	printf("Sub1_02 = %s\n\n", Sub1_02);

	InitNum();
	StringCompareTest(Res1_01, Sub1_01);
	StringCompareTest(Res1_02, Sub1_02);
	TestResult();

EXIT:
	if (Sub1_01 != NULL) {
		free(Sub1_01);
		Sub1_01 = NULL;
	}

	if (Sub1_02 != NULL) {
		free(Sub1_02);
		Sub1_02 = NULL;
	}
}

void TestFindStrIndex(void) {
	char Str1[] = "abc";
	char FindStr1_01[] = "a";
	unsigned int FindStrPos1_01 = 1;
	unsigned int FindRes1_01;
	unsigned int ComPos1_01 = 1;

	char FindStr1_02[] = "bc";
	unsigned int FindRes1_02;
	unsigned int ComPos1_02 = 2;

	FindRes1_01 = FindStrIndex(Str1, FindStr1_01, FindStrPos1_01);
	printf("\n\n");
	FindRes1_02 = FindStrIndex(Str1, FindStr1_02, FindStrPos1_01);

	printf("\n\n");
	InitNum();
	ValueTest(ComPos1_01, FindRes1_01);
	ValueTest(ComPos1_02, FindRes1_02);
	TestResult();
}

//TODO
void TestMoveBackStr(void) {
	char Str1[20] = "abc";
	unsigned int Pos1_01 = 1;
	int MvLen1_01 = 2;
	char CpmStr1_01[] = "ababc";

	char Str2[20] = "abcdef";
	unsigned int Pos2_01 = 2;
	int MvLen2_01 = -2;
	char CpmStr2_01[] = "adef";

	MoveBackStr(Str1, Pos1_01, MvLen1_01);
	printf("Str1 = %s\n", Str1);

	MoveBackStr(Str2, Pos2_01, MvLen2_01);
	printf("Str2 = %s\n", Str2);
	
	printf("\n\n");
	InitNum();
	StringCompareTest(CpmStr1_01, Str1);
	StringCompareTest(CpmStr2_01, Str2);
	TestResult();
}

void TestCopyStrWhithoutTail(void) {
	char Str1[20] = "ababc";
	unsigned int Pos1_01 = 1;
	char RepStr1_01[] = "1234";
	char CpmStr1_01[] = "1234c";

	CopyStrWhithoutTail(Str1, Pos1_01, RepStr1_01);
	
	printf("Str1 = %s\n", Str1);
	
	InitNum();
	StringCompareTest(CpmStr1_01, Str1);
	TestResult();
}

void TestMoveBackStrAndCopyStrWhithoutTail(void) {
	/*Test01*/
	char Str1[20] = "abc";
	unsigned int Pos1_01 = 1;
	int MvLen1_01 = 2;
	char RepStr1_01[] = "1234";
	char CpmStr1_01[] = "1234c";
	
	/*Test02*/
	char Str2[20] = "abcdef";
	unsigned int Pos2_01= 2;
	int MvLen2_01 = -2;
	char RepStr2_01[] = "12";
	char CpmStr2_01[] = "a12f";

	/*Test01*/
	MoveBackStr(Str1, Pos1_01, MvLen1_01);
	printf("Str1 = %s\n", Str1);
	CopyStrWhithoutTail(Str1, Pos1_01, RepStr1_01);
	printf("Str1 = %s\n", Str1);

	/*Test02*/
	MoveBackStr(Str2, Pos2_01, MvLen2_01);
	printf("Str2 = %s\n", Str2);
	CopyStrWhithoutTail(Str2, Pos2_01, RepStr2_01);
	printf("Str2 = %s\n", Str2);

	/*Test Result*/
	printf("\n\n");
	InitNum();
	StringCompareTest(CpmStr1_01, Str1);
	StringCompareTest(CpmStr2_01, Str2);
	TestResult();
}

//TODO
void TestStrReplace(void) {
	OP_STATUS Status;
	char *Str1 = NULL;
	//char Str1cpy[] = "12341236612";
	//char Str3[] = "123";
	//char StrRep[] = "hello";
	//char TestStr1[] = "hello4hello6612";

	char Str1cpy[] = "1234";
	char Str3[] = "123";
	char StrRep[] = "hello";
	char TestStr1[] = "hello4";

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

	Status = StrReplace(Str1, Str3, StrRep);
	
	InitNum();
	/*Test*/
	//StatusTest(SUCCESS, Status);
	StringCompareTest(TestStr1, Str1);

EXIT:
	if (Str1 != NULL) {
		free(Str1);
		Str1 = NULL;
	}

	TestResult();
}

