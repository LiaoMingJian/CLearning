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
	char Str01[20] = "abcdef";
	unsigned int Pos01 = 2;
	int MvLen01 = 2;
	char RepStr01[] = "1234";
	char CpmStr01[] = "a1234def";
	
	/*Test02*/
	char Str02[20] = "abcdef";
	unsigned int Pos02= 2;
	int MvLen02 = -2;
	char RepStr02[] = "12";
	char CpmStr02[] = "a12f";

	/*Test03*/
	char Str03[20] = "abcdef";
	unsigned int Pos03 = 2;
	int MvLen03 = 0;
	char RepStr03[] = "12345";
	char CpmStr03[] = "a12345";

	/*Test04*/
	char Str04[20] = "abcdef";
	unsigned int Pos04 = 5;
	int MvLen04 = 2;
	char RepStr04[] = "1234";
	char CpmStr04[] = "abcd1234";

	/*Test05*/
	char Str05[20] = "abcdef";
	unsigned int Pos05 = 5;
	int MvLen05 = -2;
	char RepStr05[] = "1";
	char CpmStr05[] = "abcd1";

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("\n-------Test 01----------\n");
	MoveBackStr(Str01, Pos01, MvLen01);
	printf("Str01 = %s\n", Str01);
	CopyStrWhithoutTail(Str01, Pos01, RepStr01);
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CpmStr01, Str01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	MoveBackStr(Str02, Pos02, MvLen02);
	printf("Str02 = %s\n", Str02);
	CopyStrWhithoutTail(Str02, Pos02, RepStr02);
	printf("Str02 = %s\n", Str02);
	StringCompareTest(CpmStr02, Str02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	MoveBackStr(Str03, Pos03, MvLen03);
	printf("Str03 = %s\n", Str03);
	CopyStrWhithoutTail(Str03, Pos03, RepStr03);
	printf("Str03 = %s\n", Str03);
	StringCompareTest(CpmStr03, Str03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	MoveBackStr(Str04, Pos04, MvLen04);
	printf("Str04 = %s\n", Str04);
	CopyStrWhithoutTail(Str04, Pos04, RepStr04);
	printf("Str04 = %s\n", Str04);
	StringCompareTest(CpmStr04, Str04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	MoveBackStr(Str05, Pos05, MvLen05);
	printf("Str05 = %s\n", Str05);
	CopyStrWhithoutTail(Str05, Pos05, RepStr05);
	printf("Str05 = %s\n", Str05);
	StringCompareTest(CpmStr05, Str05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


void TestFindStrIndexToMoveBackStrToCopyStrWhithoutTail(void) {
	/*Test01*/
	char Str01[20] = "abcdef";
	unsigned int Pos01 = 1;
	unsigned int RetPos01;
	char FindStr01[] = "bc";
	char RepStr01[] = "12";
	int MvLen01 = StringLen(RepStr01) - StringLen(FindStr01);
	char CmpStr01[] = "a12def";

	/*Test02*/
	char Str02[20] = "abcdef";
	unsigned int Pos02 = 1;
	unsigned int RetPos02;
	char FindStr02[] = "bc";
	char RepStr02[] = "1234";
	int MvLen02 = StringLen(RepStr02) - StringLen(FindStr02);
	char CmpStr02[] = "a1234def";

	/*Test03*/
	char Str03[20] = "abcdef";
	unsigned int Pos03 = 1;
	unsigned int RetPos03;
	char FindStr03[] = "bcde";
	char RepStr03[] = "12";
	int MvLen03 = StringLen(RepStr03) - StringLen(FindStr03);
	char CmpStr03[] = "a12f";

	/*Test04*/
	char Str04[20] = "abcdef";
	unsigned int Pos04 = 1;
	unsigned int RetPos04;
	char FindStr04[] = "cdef";
	char RepStr04[] = "1234";
	int MvLen04 = StringLen(RepStr04) - StringLen(FindStr04);
	char CmpStr04[] = "ab1234";

	/*Test05*/
	char Str05[20] = "abcdef";
	unsigned int Pos05 = 1;
	unsigned int RetPos05;
	char FindStr05[] = "cdef";
	char RepStr05[] = "123456";
	int MvLen05 = StringLen(RepStr05) - StringLen(FindStr05);
	char CmpStr05[] = "ab123456";

	/*Test06*/
	char Str06[20] = "abcdef";
	unsigned int Pos06 = 1;
	unsigned int RetPos06;
	char FindStr06[] = "cdef";
	char RepStr06[] = "12";
	int MvLen06 = StringLen(RepStr06) - StringLen(FindStr06);
	char CmpStr06[] = "ab12";

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("\n-------Test 01----------\n");
	RetPos01 = FindStrIndex(Str01, FindStr01, Pos01);
	printf("RetPos01 = %d\n", RetPos01);
	MoveBackStr(Str01, RetPos01, MvLen01);
	printf("Str01 = %s\n", Str01);
	CopyStrWhithoutTail(Str01, RetPos01, RepStr01);
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CmpStr01, Str01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	RetPos02 = FindStrIndex(Str02, FindStr02, Pos02);
	printf("RetPos02 = %d\n", RetPos02);
	MoveBackStr(Str02, RetPos02, MvLen02);
	printf("Str02 = %s\n", Str02);
	CopyStrWhithoutTail(Str02, RetPos02, RepStr02);
	printf("Str02 = %s\n", Str02);
	StringCompareTest(CmpStr02, Str02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	RetPos03 = FindStrIndex(Str03, FindStr03, Pos03);
	printf("RetPos03 = %d\n", RetPos03);
	MoveBackStr(Str03, RetPos03, MvLen03);
	printf("Str03 = %s\n", Str03);
	CopyStrWhithoutTail(Str03, RetPos03, RepStr03);
	printf("Str03 = %s\n", Str03);
	StringCompareTest(CmpStr03, Str03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	RetPos04 = FindStrIndex(Str04, FindStr04, Pos04);
	printf("RetPos04 = %d\n", RetPos04);
	MoveBackStr(Str04, RetPos04, MvLen04);
	printf("Str04 = %s\n", Str04);
	CopyStrWhithoutTail(Str04, RetPos04, RepStr04);
	printf("Str04 = %s\n", Str04);
	StringCompareTest(CmpStr04, Str04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	RetPos05 = FindStrIndex(Str05, FindStr05, Pos05);
	printf("RetPos05 = %d\n", RetPos05);
	MoveBackStr(Str05, RetPos05, MvLen05);
	printf("Str05 = %s\n", Str05);
	CopyStrWhithoutTail(Str05, RetPos05, RepStr05);
	printf("Str05 = %s\n", Str05);
	StringCompareTest(CmpStr05, Str05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	RetPos06 = FindStrIndex(Str06, FindStr06, Pos06);
	printf("RetPos06 = %d\n", RetPos06);
	MoveBackStr(Str06, RetPos06, MvLen06);
	printf("Str06 = %s\n", Str06);
	CopyStrWhithoutTail(Str06, RetPos06, RepStr06);
	printf("Str06 = %s\n", Str06);
	StringCompareTest(CmpStr06, Str06);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}



//TODO
void TestStrReplace(void) {
	//char Str1cpy[] = "12341236612";
	//char Str3[] = "123";
	//char StrRep[] = "hello";
	//char TestStr1[] = "hello4hello6612";
	OP_STATUS Status;
	/*Test01*/
	char Str01[30] = "abcdef";
	char FindStr01[] = "bc";	
	char RepStr01[] = "12";
	char CmpStr01[] = "a12def";

	/*Test02*/
	char Str02[30] = "abcdef";
	char FindStr02[] = "bc";
	char RepStr02[] = "1234";
	char CmpStr02[] = "a1234def";

	/*Test03*/
	char Str03[30] = "abcdef";
	char FindStr03[] = "bcde";
	char RepStr03[] = "12";
	char CmpStr03[] = "a12f";

	/*Test04*/
	char Str04[30] = "abcdef";
	char FindStr04[] = "cdef";
	char RepStr04[] = "1234";
	char CmpStr04[] = "ab1234";

	/*Test05*/
	char Str05[30] = "abcdef";
	char FindStr05[] = "cdef";
	char RepStr05[] = "123456";
	char CmpStr05[] = "ab123456";

	/*Test06*/
	char Str06[30] = "abcdef";
	char FindStr06[] = "cdef";
	char RepStr06[] = "12";
	char CmpStr06[] = "ab12";

	///*Test07*/
	//char str07[30] = "abcdefbc";
	//char findstr07[] = "bc";
	//char repstr07[] = "12";
	//char cmpstr07[] = "a12def12";


	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("\n-------Test 01----------\n");
	StrReplace(Str01, FindStr01, RepStr01);
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CmpStr01, Str01);
	
	/*Test02*/
	printf("\n-------Test 02----------\n");
	StrReplace(Str02, FindStr02, RepStr02);
	printf("Str02 = %s\n", Str02);
	StringCompareTest(CmpStr02, Str02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	StrReplace(Str03, FindStr03, RepStr03);
	printf("Str03 = %s\n", Str03);
	StringCompareTest(CmpStr03, Str03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	StrReplace(Str04, FindStr04, RepStr04);
	printf("Str04 = %s\n", Str04);
	StringCompareTest(CmpStr04, Str04);
	
	/*Test05*/
	printf("\n-------Test 05----------\n");
	StrReplace(Str05, FindStr05, RepStr05);
	printf("Str05 = %s\n", Str05);
	StringCompareTest(CmpStr05, Str05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	StrReplace(Str06, FindStr06, RepStr06);
	printf("Str06 = %s\n", Str06);
	StringCompareTest(CmpStr06, Str06);





	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

