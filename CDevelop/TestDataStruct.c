#include <stdio.h>
#include <string.h>
#include <malloc.h>
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
	TestNum++;
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
	TestNum++;
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
	/*Test01*/
	char Str01[] = "abc";
	unsigned int SubPos01 = 1;
	unsigned int SubLen01 = 1;
	char *Sub01 = NULL;
	char Res01[] = "a";

	/*Test02*/
	char Str02[] = "abc";
	unsigned int SubPos02 = 2;
	unsigned int SubLen02 = 2;
	char *Sub02 = NULL;
	char Res02[] = "bc";

	Sub01 = (char *)malloc(SubLen01 + 1);
	if (Sub01 == NULL) {
		goto EXIT;
	}
	Sub02 = (char *)malloc(SubLen02 + 1);
	if (Sub02 == NULL) {
		goto EXIT;
	}

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	SubString(Sub01, Str01, SubPos01, SubLen01);
	printf("Sub01 = %s\n", Sub01);
	StringCompareTest(Res01, Sub01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	SubString(Sub02, Str02, SubPos02, SubLen02);
	printf("Sub02 = %s\n\n", Sub02);
	StringCompareTest(Res02, Sub02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();

EXIT:
	if (Sub01 != NULL) {
		free(Sub01);
		Sub01 = NULL;
	}

	if (Sub02 != NULL) {
		free(Sub02);
		Sub02 = NULL;
	}
}

void TestFindStrIndex(void) {
	/*Test01*/
	char Str01[] = "abcdef";
	char FindStr01[] = "bc";
	unsigned int FindStrPos01 = 1;
	unsigned int FindRes01;
	unsigned int ComPos01 = 2;

	/*Test02*/
	char Str02[] = "abcdef";
	char FindStr02[] = "ef";
	unsigned int FindStrPos02 = 2;
	unsigned int FindRes02;
	unsigned int ComPos02 = 5;

	/*Test03*/
	char Str03[] = "abcdef";
	char FindStr03[] = "ee";
	unsigned int FindStrPos03 = 1;
	unsigned int FindRes03;
	unsigned int ComPos03 = 0;

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	FindRes01 = FindStrIndex(Str01, FindStr01, FindStrPos01);
	ValueTest(ComPos01, FindRes01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	FindRes02 = FindStrIndex(Str02, FindStr02, FindStrPos02);
	ValueTest(ComPos02, FindRes02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	FindRes03 = FindStrIndex(Str03, FindStr03, FindStrPos03);
	ValueTest(ComPos03, FindRes03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

void TestMoveBackStr(void) {
	/*Test01*/
	char Str01[20] = "abc";
	unsigned int Pos01 = 1;
	int MvLen01 = 2;
	char CpmStr01[] = "ababc";

	/*Test02*/
	char Str02[20] = "abcdef";
	unsigned int Pos02 = 2;
	int MvLen02 = -2;
	char CpmStr02[] = "adef";

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	MoveBackStr(Str01, Pos01, MvLen01);
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CpmStr01, Str01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	MoveBackStr(Str02, Pos02, MvLen02);
	printf("Str02 = %s\n", Str02);
	StringCompareTest(CpmStr02, Str02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

void TestCopyStrWhithoutTail(void) {
	char Str01[20] = "ababc";
	unsigned int Pos01 = 1;
	char RepStr01[] = "1234";
	char CpmStr01[] = "1234c";

	printf("-------Test start----------\n");
	InitNum();
	printf("-------Test 01----------\n");
	CopyStrWhithoutTail(Str01, Pos01, RepStr01);	
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CpmStr01, Str01);

	/*Test Result*/
	printf("\n-------Test result----------\n");
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
	printf("-------Test 01----------\n");
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
	printf("-------Test 01----------\n");
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

void TestStrReplace(void) {
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

	/*Test07*/
	char Str07[30] = "abcbcfbc";
	char FindStr07[] = "bc";
	char RepStr07[] = "12";
	char CmpStr07[] = "a1212f12";

	/*Test08*/
	char Str08[30] = "abcbcfbc";
	char FindStr08[] = "bc";
	char RepStr08[] = "1234";
	char CmpStr08[] = "a12341234f1234";

	/*Test09*/
	char Str09[30] = "abcbcfbc";
	char FindStr09[] = "bc";
	char RepStr09[] = "1";
	char CmpStr09[] = "a11f1";

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
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

	/*Test07*/
	printf("\n-------Test 07----------\n");
	StrReplace(Str07, FindStr07, RepStr07);
	printf("Str07 = %s\n", Str07);
	StringCompareTest(CmpStr07, Str07);

	/*Test08*/
	printf("\n-------Test 08----------\n");
	StrReplace(Str08, FindStr08, RepStr08);
	printf("Str08 = %s\n", Str08);
	StringCompareTest(CmpStr08, Str08);

	/*Test09*/
	printf("\n-------Test 09----------\n");
	StrReplace(Str09, FindStr09, RepStr09);
	printf("Str09 = %s\n", Str09);
	StringCompareTest(CmpStr09, Str09);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

void TestStrInsert(void) {
	/*Test01*/
	char Str01[30] = "abcdef";
	unsigned int InSertPos01 = 2;
	char InsertStr01[] = "123";
	char CmpSetr01[] = "a123bcdef";

	/*Test02*/
	char Str02[30] = "abcdef";
	unsigned int InSertPos02 = 6;
	char InsertStr02[] = "123";
	char CmpSetr02[] = "abcde123f";

	/*Test03*/
	char Str03[30] = "abcdef";
	unsigned int InSertPos03 = 7;
	char InsertStr03[] = "123";
	char CmpSetr03[] = "abcdef123";

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	StrInsert(Str01, InSertPos01, InsertStr01);
	printf("Str01 = %s\n", Str01);
	StringCompareTest(CmpSetr01, Str01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	StrInsert(Str02, InSertPos02, InsertStr02);
	printf("Str02 = %s\n", Str02);
	StringCompareTest(CmpSetr02, Str02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	StrInsert(Str03, InSertPos03, InsertStr03);
	printf("Str03 = %s\n", Str03);
	StringCompareTest(CmpSetr03, Str03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

void TestStrNormalFindIndex(void) {
	/*Test01*/
	char Str01[20] = "abcdef";
	char FindStr01[] = "bc";
	unsigned int FindPos01 = 1;
	unsigned int RetPos01;
	unsigned int CmpFindPos01 = 2;

	/*Test02*/
	char Str02[20] = "abcdef";
	char FindStr02[] = "ef";
	unsigned int FindPos02 = 2;
	unsigned int RetPos02;
	unsigned int CmpFindPos02 = 5;

	/*Test03*/
	char Str03[20] = "abcdef";
	char FindStr03[] = "ee";
	unsigned int FindPos03 = 1;
	unsigned int RetPos03;
	unsigned int CmpFindPos03 = 0;

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	RetPos01 = StrNormalFindIndex(Str01, FindStr01, FindPos01);
	printf("RetPos01 = %d\n", RetPos01);
	ValueTest(CmpFindPos01, RetPos01);
	
	/*Test02*/
	printf("\n-------Test 02----------\n");
	RetPos02 = StrNormalFindIndex(Str02, FindStr02, FindPos02);
	printf("RetPos02 = %d\n", RetPos02);
	ValueTest(CmpFindPos02, RetPos02);
	
	/*Test03*/
	printf("\n-------Test 03----------\n");
	RetPos03 = StrNormalFindIndex(Str03, FindStr03, FindPos03);
	printf("RetPos03 = %d\n", RetPos03);
	ValueTest(CmpFindPos03, RetPos03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*Tree*/
/*PARENT_TREE*/
OP_STATUS PTreeCmpTest(const PARENT_TREE *PT01, const PARENT_TREE *PT02, const unsigned int PTNodeNum01) {
	PARENT_TREE *TraPT01 = PT01;
	PARENT_TREE *TraPT02 = PT02;
	unsigned int Index = 0;

	TestNum++;
	
	if (TraPT01->Num != TraPT02->Num || TraPT01->Root != TraPT02->Root) {
		FaildNum++;
		return ERROR;
	}

	for (Index = 0; Index < PTNodeNum01; ++Index) {
		if (TraPT01->Node[Index].Data != TraPT02->Node[Index].Data || TraPT01->Node[Index].Parent != TraPT02->Node[Index].Parent) {
			FaildNum++;
			return ERROR;
		}
	}

	PassNum++;
	return SUCCESS;
}

void TestBuildPTree(void) {
	/*Test01*/
	PARENT_TREE PTree01;
	unsigned int PTNodeNum01 = 7;
	int PTNodeData01[7] = { 0, 
							10, 20, 
							30, 40, 50, 60 };
	int PTNodeParent01[7] = {-1, 
							0, 0, 
							1, 1, 2, 2};
	PARENT_TREE CmpPTree01 = { {{0, -1}, 
								{10, 0}, {20, 0}, 
								{30, 1}, {40, 1}, {50, 2}, {60, 2}}, 0, 7 };

	/*Test02*/
	PARENT_TREE PTree02;
	unsigned int PTNodeNum02 = 10;
	int PTNodeData02[10] = { 0, 
							10, 20, 
							30, 40, 50, 
							60, 70, 80, 90 };

	int PTNodeParent02[10] = { -1, 
								0, 0, 
								1, 2, 2, 
								3, 3, 3, 4 };

	PARENT_TREE CmpPTree02 = { {{0, -1}, 
								{10, 0}, {20, 0}, 
								{30, 1}, {40, 2}, {50, 2}, 
								{60, 3}, {70, 3}, {80, 3}, {90, 4}}, 0, 10 };

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	BuildPTree(&PTree01, PTNodeNum01, PTNodeData01, PTNodeParent01);
	PTreeCmpTest(&CmpPTree01, &PTree01, PTNodeNum01);
	PrintPTree(&PTree01, PTNodeNum01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildPTree(&PTree02, PTNodeNum02, PTNodeData02, PTNodeParent02);
	PTreeCmpTest(&CmpPTree02, &PTree02, PTNodeNum02);
	PrintPTree(&PTree02, PTNodeNum02);


	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

/*CHILD_PARTENT_TREE*/
OP_STATUS CPTreeCmpTest(PARENT_TREE *PTree, CHILD_PARTENT_TREE *CPTree, const unsigned int NodeNum) {
	PARENT_TREE *TraPTree = PTree;
	CHILD_PARTENT_TREE *TraCPTree = CPTree;
	unsigned int Index = 0;

	//printf("CPTreeCmpTest start\n");
	TestNum++;
	if (TraPTree->Num != TraCPTree->NodeNum || TraPTree->Root != TraCPTree->Root) {
		//printf("TraPTree->Num = %d, TraCPTree->NodeNum = %d\n", TraPTree->Num, TraCPTree->NodeNum);
		//printf("TraPTree->Root = %d, TraCPTree->Root = %d\n", TraPTree->Root, TraCPTree->Root);
		FaildNum++;
		return ERROR;
	}

	for (Index = 0; Index < NodeNum; ++Index) {
		/*printf("TraPTree->Node[%d].Parent = %d, TraCPTree->Node[%d].Parent = %d\n", Index, TraPTree->Node[Index].Parent, Index, TraCPTree->Node[Index].Parent);*/
		if (TraPTree->Node[Index].Parent != TraCPTree->Node[Index].Parent || TraPTree->Node[Index].Data != TraCPTree->Node[Index].Data) {
			FaildNum++;
			return ERROR;
		}
	}

	/*printf("CPTreeCmpTest end\n");*/
	PassNum++;
	return SUCCESS;
}

void TestBuildChildParentTree(void) {
	/*Test01*/
	CHILD_PARTENT_TREE CPTree01;
	CHILD_PARENT_TREE_ROOT_NODENUM_DATA CPTreeRootNodeNumData01 = { 0, 7 };
	CHILD_PARENT_TREE_NODE_DATA CPTreeNodeData01[7] = { {0, -1, 2, {1, 2}},
														{10, 0, 2, {3, 4}}, {20, 0, 2, {5, 6}},
														{30, 1, 0}, {40, 1, 0}, {50, 2, 0},{60, 2, 0} };

	PARENT_TREE CmpPTree01 = { {{0, -1},
								{10, 0}, {20, 0},
								{30, 1}, {40, 1}, {50, 2}, {60, 2}}, 0, 7 };
	
	/*Test02*/
	CHILD_PARTENT_TREE CPTree02;
	CHILD_PARENT_TREE_ROOT_NODENUM_DATA CPTreeRootNodeNumData02 = {0, 10};
	CHILD_PARENT_TREE_NODE_DATA CPTreeNodeData02[10] = { {0, -1, 2, {1, 2}},
														{10, 0, 1, {3}}, {20, 0, 2, {4, 5}}, 
														{30, 1, 3, {6, 7, 8}}, {40, 2, 1, {9}}, {50, 2, 0}, 
														{60, 3, 0}, {70, 3, 0}, {80, 3, 0}, {90, 4, 0} };

	PARENT_TREE CmpPTree02 = { {{0, -1},
							{10, 0}, {20, 0},
							{30, 1}, {40, 2}, {50, 2},
							{60, 3}, {70, 3}, {80, 3}, {90, 4}}, 0, 10 };

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	BuildChildParentTree(&CPTree01, &CPTreeRootNodeNumData01, CPTreeNodeData01);
	PrintChildParentTree(&CPTree01);
	CPTreeCmpTest(&CmpPTree01, &CPTree01, CPTreeRootNodeNumData01.NodeNum);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildChildParentTree(&CPTree02, &CPTreeRootNodeNumData02, CPTreeNodeData02);
	PrintChildParentTree(&CPTree02);
	CPTreeCmpTest(&CmpPTree02, &CPTree02, CPTreeRootNodeNumData02.NodeNum);
	
	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

/*CHILD_SIBILING_PARENT_TREE*/
OP_STATUS CSPTreeCmpTest(PARENT_TREE *PTree, CHILD_SIBLING_PARENT_TREE_NODE *CSPTree, const unsigned int NodeNum) {
	PARENT_TREE *TraPTree = PTree;
	CHILD_SIBLING_PARENT_TREE_NODE *TraCSPTree = CSPTree;
	unsigned int Index = 0;

	if (TraPTree->Num != NodeNum) {
		FaildNum++;
		return ERROR;
	}

	//for (Index = 0; Index < NodeNum; ++Index) {
	//	if (TraPTree->Node[Index].Parent != CSPTree->Parent || TraPTree->Node[Index].Data != TraCPTree->Node[Index].Data) {
	//		FaildNum++;
	//		return ERROR;
	//	}
	//	
	//}

	PassNum++;
	return SUCCESS;
}

void TestBuildChildSibParentTree(void) {
	/*Test01*/
	CHILD_SIBLING_PARENT_TREE_NODE *CSPTreeNode01 = NULL;
	unsigned int CSPTreeNodeNum01 = 10;
	/*CHILD_SIBLING_PARENT_TREE_NODE_DATA CSPTreeData01[10] = { {0, -1, 1, 0},
														{10, 0, 1, 1}, {20, 0, 1, 0}, 
														{30, 1, 1, 1}, {40, 2, 1, 1}, {50, 2, 0, 0}, 
														{60, 3, 0, 1}, {70, 3, 0, 1}, {80, 3, 0, 1}, {90, 4, 0, 0} };*/

	CHILD_SIBLING_PARENT_TREE_NODE_DATA CSPTreeData01[9] = {{10, 0, 1, 1}, 
															{30, 1, 1, 0}, 
															{60, 3, 0, 1}, {70, 3, 0, 1}, {80, 3, 0, 0}, 
															{20, 0, 1, 0}, 
															{40, 2, 1, 1}, 
															{90, 4, 0, 0}, 
															{50, 2, 0, 0} };
	
	CSPTreeNode01 = (CHILD_SIBLING_PARENT_TREE_NODE *)malloc(sizeof(CHILD_SIBLING_PARENT_TREE_NODE));
	if (CSPTreeNode01 == NULL) {
		goto EXIT;
	}
	CSPTreeNode01->Data = 0;
	CSPTreeNode01->Parent = -1;
	CSPTreeNode01->FirstChild = NULL;
	CSPTreeNode01->RightSib = NULL;

	unsigned int IfExistFirstChildFlag01 = 1;
	unsigned int IfExistRightSibFlag01 = 0;

	PARENT_TREE CmpPTree01 = { {{0, -1},
								{10, 0}, {20, 0},
								{30, 1}, {40, 2}, {50, 2},
								{60, 3}, {70, 3}, {80, 3}, {90, 4}}, 0, 10 };


	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	BuildChildSibParentTree(CSPTreeNode01, CSPTreeData01, IfExistFirstChildFlag01, IfExistRightSibFlag01);
	//PrintChildSibParentTree(CSPTreeNode01);
	CSPTreeCmpTest(&CmpPTree01, CSPTreeNode01, CSPTreeNodeNum01);



EXIT:
	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*BINARY_TREE*/
static int PreOrderTraverseCompareNum = 0;
static int BiIndex = 0;
void PreOrderTraverseCompare(const int *CmpNode, const BINARY_TREE_NODE *BiTreeNode) {
	if (BiTreeNode == NULL) {
		return;
	} else {
		//printf("BiTreeNode->Data = 0x%lx , CmpNode[%d] = %d, BiTreeNode->LeftChild = 0x%lx, BiTreeNode->RightChild = 0x%lx\n", BiTreeNode->Data, BiIndex, CmpNode[BiIndex], BiTreeNode->LeftChild, BiTreeNode->RightChild);
		printf("BiTreeNode->Data = %d\n", BiTreeNode->Data);
		if (BiTreeNode->Data == CmpNode[BiIndex]) {
			//printf("BiTreeNode->Data = %d , CmpNode[%d] = %d\n", BiTreeNode->Data, Index, CmpNode[Index]);
			PreOrderTraverseCompareNum++;
		}

		BiIndex++;
		PreOrderTraverseCompare(CmpNode, BiTreeNode->LeftChild);
		PreOrderTraverseCompare(CmpNode, BiTreeNode->RightChild);
	}
}

void CmpPreOderBuildBinaryTree(const int *CmpNode, const BINARY_TREE_NODE *BiTreeNode, int NodeNum) {
	BiIndex = 0;
	PreOrderTraverseCompareNum = 0;

	TestNum++;
	PreOrderTraverseCompare(CmpNode, BiTreeNode);
	printf("PreOrderTraverseCompareNum = %d, NodeNum = %d\n", PreOrderTraverseCompareNum, NodeNum);
	if (PreOrderTraverseCompareNum != NodeNum) {
		FaildNum++;
	} else {
		PassNum++;
	}
}


/*AVL_TREE_NODE*/
void PreOrderTraverseAVLCompare(const int *CmpNode, const AVL_TREE_NODE *AVLNode) {
	if (AVLNode == NULL) {
		return;
	} else {
		//printf("CmpNode[%d] = %d, AVLNode->Data = 0x%lx, AVLNode->BF = %d, BiTreeNode->LeftChild = 0x%lx, BiTreeNode->RightChild = 0x%lx\n", CmpNode[BiIndex], AVLNode->Data, AVLNode->BF, AVLNode->LeftChild, AVLNode->RightChild);
		//printf("AVLNode->Data = %d, AVLNode->BF = %d\n", AVLNode->Data, AVLNode->BF);
		if (AVLNode->Data == CmpNode[BiIndex]) {
			PreOrderTraverseCompareNum++;
		}

		BiIndex++;
		PreOrderTraverseAVLCompare(CmpNode, AVLNode->LeftChild);
		PreOrderTraverseAVLCompare(CmpNode, AVLNode->RightChild);
	}
}

void CmpPreOderBuildAVLTree(const int *CmpNode, const AVL_TREE_NODE *AVLNode, int NodeNum) {
	BiIndex = 0;
	PreOrderTraverseCompareNum = 0;

	TestNum++;
	PreOrderTraverseAVLCompare(CmpNode, AVLNode);
	printf("PreOrderTraverseCompareNum = %d, NodeNum = %d\n", PreOrderTraverseCompareNum, NodeNum);
	if (PreOrderTraverseCompareNum != NodeNum) {
		FaildNum++;
	} else {
		PassNum++;
	}
}



/*BINARY_TREE*/
void TestPreOderBuildBinaryTree(void) {
	/*Test01*/
	//    10
	//  20    30
	BINARY_TREE_NODE *BiTreeNodePtr01 = NULL;
	BINARY_TREE_NODE_DATA Data01[] = { {10 , 1, 1}, {20, 0, 0}, {30, 0, 0} };
	int NodeNum01 = 3;
	char IfExistNodeFlag01 = 1;
	int CmpBiTreeNodeData01[] = { 10, 20, 30 };

	/*Test02*/
	//    10
	//  20    30
	//   40  
	BINARY_TREE_NODE *BiTreeNodePtr02 = NULL;
	BINARY_TREE_NODE_DATA Data02[] = { {10, 1, 1}, {20, 0, 1}, {40, 0, 0}, {30, 0, 0} };
	int NodeNum02 = 4;
	char IfExistNodeFlag02 = 1;
	int CmpBiTreeNodeData02[] = { 10, 20, 40, 30 };

	/*Test03*/
	//        10
	//   20        50
	// 30  40   60    70
	BINARY_TREE_NODE *BiTreeNodePtr03 = NULL;
	BINARY_TREE_NODE_DATA Data03[] = { {10, 1, 1}, {20, 1, 1}, {30, 0, 0}, {40, 0, 0}, {50, 1, 1}, {60, 0, 0}, {70, 0, 0} };
	int NodeNum03 = 7;
	char IfExistNodeFlag03 = 1;
	int CmpBiTreeNodeData03[] = { 10, 20, 30, 40, 50, 60, 70 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildBinaryTree(&BiTreeNodePtr01, Data01, IfExistNodeFlag01);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("\nCmpPreOderBuildBinaryTree\n");
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData01, BiTreeNodePtr01, NodeNum01);


	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildBinaryTree(&BiTreeNodePtr02, Data02, IfExistNodeFlag02);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("\nCmpPreOderBuildBinaryTree\n");
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData02, BiTreeNodePtr02, NodeNum02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	BuildBinaryTree(&BiTreeNodePtr03, Data03, IfExistNodeFlag03);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr03);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr03);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr03);
	printf("\nCmpPreOderBuildBinaryTree\n");
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData03, BiTreeNodePtr03, NodeNum03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*BINARY_THREAD_TREE*/
int PreOrderTraverseCmpPreOderBuildBiThrTree(const BINARY_THREAD_TREE_NODE_DATA *CmpNode, int Index, const BINARY_THREAD_TREE_NODE *BiThrTreeNode, int PreOrderTraverseCmpBiThrTreeNum) {
	BINARY_THREAD_TREE_NODE *BiThrTrNodeTemp = BiThrTreeNode->LeftChild;

	printf("\n\nTest PreOrderTraverseCmpPreOderBuildBiThrTree start\n");
	//printf("Root Node, BiThrTrNodeTemp = 0x%lx, BiThrTrNodeTemp->Data = %c, BiThrTrNodeTemp->LeftChild = 0x%lx, BiThrTrNodeTemp->RightChild = 0x%lx\n", (long unsigned int)BiThrTrNodeTemp, BiThrTrNodeTemp->Data, (long unsigned int)BiThrTrNodeTemp->LeftChild, (long unsigned int)BiThrTrNodeTemp->RightChild);
	while (BiThrTrNodeTemp != BiThrTreeNode) {
		//printf("test01\n");
		while (BiThrTrNodeTemp->IfExistDirectLeftNodeFlag != 0) {
			BiThrTrNodeTemp = BiThrTrNodeTemp->LeftChild;
		}

		printf("BiThrTrNodeTemp = 0x%lx, BiThrTrNodeTemp->Data = %c, BiThrTrNodeTemp->LeftChild = 0x%lx, BiThrTrNodeTemp->RightChild = 0x%lx\n", (long unsigned int)BiThrTrNodeTemp, BiThrTrNodeTemp->Data, (long unsigned int)BiThrTrNodeTemp->LeftChild, (long unsigned int)BiThrTrNodeTemp->RightChild);
		printf("CmpNode[Index].BiThrTreeData = %c\n", CmpNode[Index].BiThrTreeData);
		if (CmpNode[Index++].BiThrTreeData == BiThrTrNodeTemp->Data) {
			PreOrderTraverseCmpBiThrTreeNum++;
		}

		while ((BiThrTrNodeTemp->IfExistDirectRightNodeFlag == 0) && (BiThrTrNodeTemp->RightChild != BiThrTreeNode)) {
			BiThrTrNodeTemp = BiThrTrNodeTemp->RightChild;
			printf("BiThrTrNodeTemp = 0x%lx, BiThrTrNodeTemp->Data = %c, BiThrTrNodeTemp->LeftChild = 0x%lx, BiThrTrNodeTemp->RightChild = 0x%lx\n", (long unsigned int)BiThrTrNodeTemp, BiThrTrNodeTemp->Data, (long unsigned int)BiThrTrNodeTemp->LeftChild, (long unsigned int)BiThrTrNodeTemp->RightChild);
			printf("CmpNode[Index].BiThrTreeData = %c\n", CmpNode[Index].BiThrTreeData);
			if (CmpNode[Index++].BiThrTreeData == BiThrTrNodeTemp->Data) {
				PreOrderTraverseCmpBiThrTreeNum++;
			}
		}

		BiThrTrNodeTemp = BiThrTrNodeTemp->RightChild;
		//printf("BiThrTrNodeTemp = 0x%lx, BiThrTrNodeTemp->RightChild = 0x%lx\n", (long unsigned int )BiThrTrNodeTemp, (long unsigned int )BiThrTrNodeTemp->RightChild);
	}

	printf("PreOrderTraverseCompareBinaryThreadTree03 end\n");
	return PreOrderTraverseCmpBiThrTreeNum;
}

void CmpPreOderBuildBiThrTree(const BINARY_THREAD_TREE_NODE_DATA *CmpNode, int Index, const BINARY_THREAD_TREE_NODE *BiThrTreeNode, int NodeNum) {
	//unsigned char Index = 0;
	int PreOrderTraverseCmpBiThrTreeNum = 0;
	//Index = 0;

	TestNum++;

	PreOrderTraverseCmpBiThrTreeNum = PreOrderTraverseCmpPreOderBuildBiThrTree(CmpNode, Index, BiThrTreeNode, PreOrderTraverseCmpBiThrTreeNum);
	printf("PreOrderTraverseCmpBiThrTreeNum = %d, NodeNum = %d\n", PreOrderTraverseCmpBiThrTreeNum, NodeNum);
	if (PreOrderTraverseCmpBiThrTreeNum != NodeNum) {
		FaildNum++;
	}
	else {
		PassNum++;
	}
}

/*BINARY_THREAD_TREE*/
void TestBuildBinaryThreadTree(void) {
	/*Test01*/
	//    A
	//  B    C
	BINARY_THREAD_TREE_NODE  *BiThrTreeNodePtr01 = NULL;
	BINARY_THREAD_TREE_NODE_DATA  BiThrTreeNodeData01[] = { {'A', 1, 1, 1, 1}, {'B', 0, 0, 0, 0}, {'C', 0, 0, 0, 0} };
	int NodeNum01 = 3;
	char IfExistNodeFlag01 = 1;
	BINARY_THREAD_TREE_NODE_DATA  CmpBiThrTreeNodeData01[] = { {'B', 0, 0, 0, 0}, {'A', 1, 1, 1, 1}, {'C', 0, 0, 0, 0} };
	int Index01 = 0;

	//    A
	//  B    E
	// C  D  F  G
	BINARY_THREAD_TREE_NODE  *BiThrTreeNodePtr02 = NULL;
	BINARY_THREAD_TREE_NODE_DATA  BiThrTreeNodeData02[] = { {'A', 1, 1, 1, 1}, {'B', 1, 1, 1, 1}, {'C', 0, 0, 0, 0}, {'D', 0, 0, 0, 0},
				 {'E', 1, 1, 1, 1}, {'F', 0, 0, 0, 0}, {'G', 0, 0, 0, 0} };
	int NodeNum02 = 7;

	BINARY_THREAD_TREE_NODE_DATA  CmpBiThrTreeNodeData02[] = { {'C', 0, 0, 0, 0}, {'B', 0, 0, 0, 0}, {'D', 0, 0, 0, 0}, {'A', 1, 1, 1, 1},
				   {'F', 0, 0, 0, 0}, {'E', 1, 1, 1, 1}, {'G', 0, 0, 0, 0} };
	int Index02 = 0;

	//    A
	//  B    C
	//   D    
	BINARY_THREAD_TREE_NODE  *BiThrTreeNodePtr03 = NULL;
	BINARY_THREAD_TREE_NODE_DATA BiThrTreeNodeData03[] = { {'A', 1, 1, 1, 1}, {'B', 0, 1, 0, 1}, {'D', 0, 0, 0, 0}, {'C', 0, 0, 0, 0} };
	int NodeNum03 = 4;
	BINARY_THREAD_TREE_NODE_DATA  CmpBiThrTreeNodeData03[] = { {'B', 0, 0, 0, 0}, {'D', 0, 0, 0, 0}, {'A', 1, 1, 1, 1}, {'C', 0, 0, 0, 0} };
	int Index03 = 0;


	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildBinaryThreadTree(&BiThrTreeNodePtr01, BiThrTreeNodeData01);
	CmpPreOderBuildBiThrTree(CmpBiThrTreeNodeData01, Index01, BiThrTreeNodePtr01, NodeNum01);


	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildBinaryThreadTree(&BiThrTreeNodePtr02, BiThrTreeNodeData02);
	CmpPreOderBuildBiThrTree(CmpBiThrTreeNodeData02, Index02, BiThrTreeNodePtr02, NodeNum02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	BuildBinaryThreadTree(&BiThrTreeNodePtr03, BiThrTreeNodeData03);
	CmpPreOderBuildBiThrTree(CmpBiThrTreeNodeData03, Index03, BiThrTreeNodePtr03, NodeNum03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}



void TestCmpRes(int CmpRes01, int Res01) {
	TestNum++;

	if (CmpRes01 != Res01) {
		FaildNum++;
	}
	else {		
		PassNum++;
	}
}

/*TestBinarySearch*/
void TestBinarySearch(void) {
	/*Test01: Normal*/
	int Arr01[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue01 = 2;
	int Res01 = 0;
	int CmpRes01 = 2;
	int Num01 = 6;

	/*Test02: Bounary*/
	int Arr02[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue02 = 0;
	int Res02 = 0;
	int CmpRes02 = 0;
	int Num02 = 6;

	/*Test03: Bounary*/
	int Arr03[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue03 = 5;
	int Res03 = 0;
	int CmpRes03 = 5;
	int Num03 = 6;

	/*Test04: Don't exit*/
	int Arr04[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue04 = 7;
	int Res04 = 0;
	int CmpRes04 = -1;
	int Num04 = 6;

	/*Test05: Two Mem*/
	int Arr05[] = { 0, 1 };
	int SearchValue05 = 1;
	int Res05 = 0;
	int CmpRes05 = 1;
	int Num05 = 2;

	/*Test06: Only a Mem and exit*/
	int Arr06[] = { 0 };
	int SearchValue06 = 0;
	int Res06 = 0;
	int CmpRes06 = 0;
	int Num06 = 1;

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	Res01 = BinarySearch(Arr01, Num01, SearchValue01);
	TestCmpRes(CmpRes01, Res01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	Res02 = BinarySearch(Arr02, Num02, SearchValue02);
	TestCmpRes(CmpRes02, Res02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	Res03 = BinarySearch(Arr03, Num03, SearchValue03);
	TestCmpRes(CmpRes03, Res03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	Res04 = BinarySearch(Arr04, Num04, SearchValue04);
	TestCmpRes(CmpRes04, Res04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	Res05 = BinarySearch(Arr05, Num05, SearchValue05);
	TestCmpRes(CmpRes05, Res05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	Res06 = BinarySearch(Arr06, Num06, SearchValue06);
	TestCmpRes(CmpRes06, Res06);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


void TestCmpArr(int *CmpArr, int Num, int *Arr) {
	int Index = 0;
	int CmpNum = 0;

	TestNum++;

	for (Index = 0; Index < Num; ++Index) {
		if (CmpArr[Index] == Arr[Index]) {
			CmpNum++;
		}
	}

	if (CmpNum != Num) {
		printf("Incorrect!\n");
		FaildNum++;
	}
	else {
		printf("Correct!\n");
		PassNum++;
	}
}

void PrintArr(int *Arr, int Num) {
	int i = 0;
	for (i = 0; i < Num; i++) {
		printf("Arr[%d] = %d\n", i, Arr[i]);
	}
}

/*TestBubbleRank*/
void TestBubbleRank(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4 };
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BubbleRank(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BubbleRank(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	BubbleRank(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	BubbleRank(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	BubbleRank(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestQuickSort*/
void TestQuickSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 5, 2, 6, 3, 1, 4 };
	int Num01 = 6;
	int Low01 = 0;
	int High01 = Num01 - 1;
	int CmpArr01[] = { 1, 2, 3, 4, 5, 6 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4 };
	int Num02 = 5;
	int Low02 = 0;
	int High02 = 4;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 8, 7, 6, 5, 4, 3, 2, 1};
	int Num03 = 8;
	int Low03 = 0;
	int High03 = Num03 - 1;
	int CmpArr03[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int Low04 = 0;
	int High04 = Num04 - 1;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Normal*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int Low05 = 0;
	int High05 = Num05 - 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	QuickSort(Arr01, Low01, High01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	QuickSort(Arr02, Low02, High02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	QuickSort(Arr03, Low03, High03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	QuickSort(Arr04, Low04, High04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	QuickSort(Arr05, Low05, High05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*InterpolationSearch*/
void TesInterpolationSearchSearch(void) {
	/*Test01: Normal*/
	int Arr01[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue01 = 2;
	int Res01 = 0;
	int CmpRes01 = 2;
	int Num01 = 6;

	/*Test02: Bounary*/
	int Arr02[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue02 = 0;
	int Res02 = 0;
	int CmpRes02 = 0;
	int Num02 = 6;

	/*Test03: Bounary*/
	int Arr03[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue03 = 5;
	int Res03 = 0;
	int CmpRes03 = 5;
	int Num03 = 6;

	/*Test04: Don't exit*/
	int Arr04[] = { 0, 1, 2, 3, 4, 5 };
	int SearchValue04 = 7;
	int Res04 = 0;
	int CmpRes04 = -1;
	int Num04 = 6;

	/*Test05: Two Mem*/
	int Arr05[] = { 0, 1 };
	int SearchValue05 = 1;
	int Res05 = 0;
	int CmpRes05 = 1;
	int Num05 = 2;

	/*Test06: Only a Mem and exit*/
	int Arr06[] = { 0 };
	int SearchValue06 = 0;
	int Res06 = 0;
	int CmpRes06 = 0;
	int Num06 = 1;

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	Res01 = InterpolationSearch(Arr01, Num01, SearchValue01);
	TestCmpRes(CmpRes01, Res01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	Res02 = InterpolationSearch(Arr02, Num02, SearchValue02);
	TestCmpRes(CmpRes02, Res02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	Res03 = InterpolationSearch(Arr03, Num03, SearchValue03);
	TestCmpRes(CmpRes03, Res03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	Res04 = InterpolationSearch(Arr04, Num04, SearchValue04);
	TestCmpRes(CmpRes04, Res04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	Res05 = InterpolationSearch(Arr05, Num05, SearchValue05);
	TestCmpRes(CmpRes05, Res05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	Res06 = InterpolationSearch(Arr06, Num06, SearchValue06);
	TestCmpRes(CmpRes06, Res06);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}



/*TestSelectSort*/
void TestSelectSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4 };
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	SelectSort(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	SelectSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	SelectSort(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	SelectSort(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	SelectSort(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestInsertSort*/
void TestInsertSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4 };
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	InsertSort(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	InsertSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	InsertSort(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	InsertSort(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	InsertSort(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestShellSort*/
void TestShellSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4 };
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	ShellSort(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	ShellSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	ShellSort(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	ShellSort(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	ShellSort(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}

/*TestHeapSort*/
void TestHeapSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4 };
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	HeapSort(Arr01, Num01);
	PrintArr(Arr01, Num01);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	HeapSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	HeapSort(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	HeapSort(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	HeapSort(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestMergeSort*/
void TestMergeSort(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4};
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	MergeSort(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	MergeSort(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	MergeSort(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	MergeSort(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	MergeSort(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestMergeSorByCycle*/
void TestMergeSorByCycle(void) {
	/*Test01: Normal*/
	int Arr01[] = { 1, 3, 2, 5, 4, 0 };
	int Num01 = 6;
	int CmpArr01[] = { 0, 1, 2, 3, 4, 5 };

	/*Test02: Exist same mem*/
	int Arr02[] = { 5, 3, 0, 3, 4 };
	int Num02 = 5;
	int CmpArr02[] = { 0, 3, 3, 4, 5 };

	/*Test03: Normal*/
	int Arr03[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	int Num03 = 8;
	int CmpArr03[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	/*Test04: Two Mem*/
	int Arr04[] = { 1, 0 };
	int Num04 = 2;
	int CmpArr04[] = { 0, 1 };

	/*Test05: Only 1 Mem*/
	int Arr05[] = { 0 };
	int Num05 = 1;
	int CmpArr05[] = { 0 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	MergeSorByCycle(Arr01, Num01);
	PrintArr(Arr01, Num01);
	TestCmpArr(CmpArr01, Num01, Arr01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	MergeSorByCycle(Arr02, Num02);
	PrintArr(Arr02, Num02);
	TestCmpArr(CmpArr02, Num02, Arr02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	MergeSorByCycle(Arr03, Num03);
	PrintArr(Arr03, Num03);
	TestCmpArr(CmpArr03, Num03, Arr03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	MergeSorByCycle(Arr04, Num04);
	PrintArr(Arr04, Num04);
	TestCmpArr(CmpArr04, Num04, Arr04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	MergeSorByCycle(Arr05, Num05);
	PrintArr(Arr05, Num05);
	TestCmpArr(CmpArr05, Num05, Arr05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}



void CmpBool(bool Mem01, bool Mem02) {
	TestNum++;
	if (Mem01 == Mem02) {
		PassNum++;
	}
	else {
		FaildNum++;
		printf("Incorrect!\n");
	}
}

/*BSTSearch*/
void TestBSTSearch(void) {
	//    50
	//  10    70
	//   30  
	BINARY_TREE_NODE *BiTreeNodePtr = NULL;
	BINARY_TREE_NODE_DATA Data[] = { {50, 1, 1}, {10, 0, 1}, {30, 0, 0}, {70, 0, 0} };
	char IfExistNodeFlag = 1;

	/*Test01*/
	BINARY_TREE_NODE *BSTNode01 = NULL;
	int SearchKey01 = 30;
	bool SearchResult01;
	bool CmpResult01 = true;

	/*Test02*/
	BINARY_TREE_NODE *BSTNode02 = NULL;
	int SearchKey02 = 50;
	bool SearchResult02;
	bool CmpResult02 = true;

	/*Test03*/
	BINARY_TREE_NODE *BSTNode03 = NULL;
	int SearchKey03 = 100;
	bool SearchResult03;
	bool CmpResult03 = false;

	BuildBinaryTree(&BiTreeNodePtr, Data, IfExistNodeFlag);
	// printf("PreOrderTraversePrintBinaryTree\n");
	// PreOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("InOrderTraversePrintBinaryTree\n");
	// InOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("PostOrderTraversePrintBinaryTree\n");
	// PostOrderTraversePrintBinaryTree(BiTreeNodePtr);

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	SearchResult01 = BSTSearch(BiTreeNodePtr, BiTreeNodePtr, SearchKey01, &BSTNode01);
	CmpBool(CmpResult01, SearchResult01);

	/*Test02*/
	printf("-------Test 02----------\n");
	SearchResult02 = BSTSearch(BiTreeNodePtr, BiTreeNodePtr, SearchKey02, &BSTNode02);
	CmpBool(CmpResult02, SearchResult02);

	/*Test03*/
	printf("-------Test 03----------\n");
	SearchResult03 = BSTSearch(BiTreeNodePtr, BiTreeNodePtr, SearchKey03, &BSTNode03);
	CmpBool(CmpResult03, SearchResult03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*AddBSTNode*/
void TestAddBSTNode(void) {
	BINARY_TREE_NODE *BSTNode = NULL;
	BINARY_TREE_NODE *BSTNode11 = NULL;

	/*Test01*/
	//	20
	int Key01 = 20;
	int Num01 = 1;
	int CmpBSTNode01[] = {20};

	/*Test02*/
	//	    20
	//	10
	int Key02 = 10;
	int Num02 = 2;
	int CmpBSTNode02[] = { 20, 10 };

	/*Test03*/
	//	    20
	//	10		50
	int Key03 = 50;
	int Num03 = 3;
	int CmpBSTNode03[] = { 20, 10, 50 };

	/*Test04*/
	//  	    20
	//	  10		 50
	//			 30
	int Key04 = 30;
	int Num04 = 4;
	int CmpBSTNode04[] = { 20, 10, 50, 30 };

	/*Test05*/
	//  	    20
	//	   10		 50
	//	5		 30
	int Key05 = 5;
	int Num05 = 5;
	int CmpBSTNode05[] = { 20, 10, 5, 50, 30 };

	printf("-------Test start----------\n");
	InitNum();
	
	/*Test01*/
	printf("\n-------Test 01----------\n");
	AddBSTNode(&BSTNode, Key01);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode01, BSTNode, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	AddBSTNode(&BSTNode, Key02);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode02, BSTNode, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	AddBSTNode(&BSTNode, Key03);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode03, BSTNode, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	AddBSTNode(&BSTNode, Key04);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode04, BSTNode, Num04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	AddBSTNode(&BSTNode, Key05);
	//printf("PreOrderTraversePrintBinaryTree\n");
	//PreOrderTraversePrintBinaryTree(BSTNode);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode05, BSTNode, Num05);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestBuildBSTree*/
void TestBuildBSTree(void) {
	/*Test01*/
	//		   30
	//	  20	    50
	// 10		 40
	int Arr01[] = { 30, 20, 50, 40, 10 };
	int Num01 = 5;
	BINARY_TREE_NODE *BSTNode01 = NULL;
	int CmpBSTNode01[] = {30, 20, 10, 50, 40};

	/*Test02*/
	//		   20
	//	  10	     50
	//			 30
	//				40	
	int Arr02[] = { 20, 50, 10, 30, 40 };
	int Num02 = 5;
	BINARY_TREE_NODE *BSTNode02 = NULL;
	int CmpBSTNode02[] = { 20, 10, 50, 30, 40 };

	/*Test03*/
	//		   30
	//	  10	    50
	//		20	 40
	//				
	int Arr03[] = { 30, 10, 50, 20, 40 };
	int Num03 = 5;
	BINARY_TREE_NODE *BSTNode03 = NULL;
	int CmpBSTNode03[] = { 30, 10, 20, 50, 40 };

	/*Test04*/
	//	  10
	//	     20
	//	        30
	//	           40
	//                50
	int Arr04[] = { 10, 20, 30, 40, 50 };
	int Num04 = 5;
	BINARY_TREE_NODE *BSTNode04 = NULL;
	int CmpBSTNode04[] = { 10, 20, 30, 40, 50 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildBSTree(&BSTNode01, Arr01, Num01);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BSTNode01);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode01, BSTNode01, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildBSTree(&BSTNode02, Arr02, Num02);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BSTNode02);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode02, BSTNode02, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	BuildBSTree(&BSTNode03, Arr03, Num03);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BSTNode03);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode03, BSTNode03, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	BuildBSTree(&BSTNode04, Arr04, Num04);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BSTNode04);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode04, BSTNode04, Num04);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestDelBSTNode*/
void TestDelBSTNode(void) {
	//          50
	//    20           70
	// 10    30    60	  90
	BINARY_TREE_NODE *BiTreeNodePtr = NULL;
	BINARY_TREE_NODE_DATA Data[] = { {50, 1, 1}, {20, 1, 1}, {10, 0, 0}, {30, 0, 0}, {70, 1, 1}, {60, 0, 0}, {90, 0, 0} };
	char IfExistNodeFlag = 1;

	/*Test01*/
	//          50
	//    20           70
	//        30    60    90
	int Key01 = 10;
	int Num01 = 6;
	int CmpBSTNode01[] = { 50, 20, 30, 70, 60, 90 };

	/*Test02*/
	//          50
	//    30           70
	//              60    90
	int Key02 = 20;
	int Num02 = 5;
	int CmpBSTNode02[] = { 50, 30, 70, 60, 90 };

	/*Test03*/
	//          50
	//    30           60
	//						90
	int Key03 = 70;
	int Num03 = 4;
	int CmpBSTNode03[] = { 50, 30, 60, 90 };

	/*Test04*/
	//          30
	//                60
	//						90
	int Key04 = 50;
	int Num04 = 3;
	int CmpBSTNode04[] = { 30, 60, 90 };

	BuildBinaryTree(&BiTreeNodePtr, Data, IfExistNodeFlag);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("InOrderTraversePrintBinaryTree\n");
	// InOrderTraversePrintBinaryTree(BiTreeNodePtr);
	// printf("PostOrderTraversePrintBinaryTree\n");
	// PostOrderTraversePrintBinaryTree(BiTreeNodePtr);

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	DelBSTNode(&BiTreeNodePtr, Key01);
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode01, BiTreeNodePtr, Num01);


	/*Test02*/
	printf("\n-------Test 02----------\n");
	DelBSTNode(&BiTreeNodePtr, Key02);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode02, BiTreeNodePtr, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	DelBSTNode(&BiTreeNodePtr, Key03);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode03, BiTreeNodePtr, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	DelBSTNode(&BiTreeNodePtr, Key04);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode04, BiTreeNodePtr, Num04);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*AddAVLNode*/
void TestAddAVLNode(void) {
	AVL_TREE_NODE *AVLNode = NULL;

	/*Test01*/
	// 30_EH
	//	30
	int Key01          = 30;
	int Num01          = 1;
	bool Taller01      = false;
	int CmpAVLNode01[] = { 30 };

	/*Test02*/
	// 30_LH
	//	    30
	//	10
	int Key02 = 10;
	int Num02 = 2;
	bool Taller02 = false;
	int CmpAVLNode02[] = { 30, 10 };

	/*Test03*/
	// 30_EH
	//	    30
	//	10      40
	int Key03 = 40;
	int Num03 = 3;
	bool Taller03 = false;
	int CmpAVLNode03[] = { 30, 10, 40 };

	/*Test04*/
	// 10_LH
	//	    30
	//   10    40
	// 9
	int Key04 = 9;
	int Num04 = 4;
	bool Taller04 = false;
	int CmpAVLNode04[] = { 30, 10, 9, 40 };

	/*Test05*/
	// LeftBlance_LH
	//	       30
	//     10       40
	//   9    
	// 5
	// 10_RightRotate
	//	       30
	//     9       40
	//  5    10
	int Key05 = 5;
	int Num05 = 5;
	bool Taller05 = false;
	int CmpAVLNode05[] = { 30, 9, 5, 10, 40 };

	/*Test06*/
	// 30_EH
	//	        30
	//     9        40
	//   5   10        50
	int Key06 = 50;
	int Num06 = 6;
	bool Taller06 = false;
	int CmpAVLNode06[] = { 30, 9, 5, 10, 40, 50 };

	/*Test07*/
	// 5_LH
	//	        30
	//     9        40
	//   5   10        50
	// 1
	int Key07 = 1;
	int Num07 = 7;
	bool Taller07 = false;
	int CmpAVLNode07[] = { 30, 9, 5, 1, 10, 40, 50 };

	/*Test08*/
	// LeftBlance_RH_EH_5_1
	//	        30
	//     9        40
	//   5   10        50
	// 1
	//  3
	// 1_LeftRotate
	//	         30
	//      9        40
	//    5   10        50
	//  3
	// 1
	// 5_RightRotate
	//	         30
	//      9        40
	//   3    10        50
	// 1   5
	int Key08 = 3;
	int Num08 = 8;
	bool Taller08 = false;
	int CmpAVLNode08[] = { 30, 9, 3, 1, 5, 10, 40, 50 };

	/*Test09*/
	// LeftBlance_RH_LH_9_3
	//	         30
	//      9        40
	//   3    10        50
	// 1   5
	//    4
	// 3_LefteRotate
	//	           30
	//        9        40
	//     5    10        50
	//   3
	// 1  4
	// 7_RightRotate
	//	          30
	//       5        40
	//    3    9         50
	//  1  4    10
	int Key09 = 4;
	int Num09 = 9;
	bool Taller09 = false;
	int CmpAVLNode09[] = { 30, 5, 3, 1, 4, 9, 10, 40, 50 };

	/*Test10*/
	// 9_EH
	//	          30
	//       5        40
	//    3    9         50
	//  1  4  6 10
	int Key10 = 6;
	int Num10 = 10;
	bool Taller10 = false;
	int CmpAVLNode10[] = { 30, 5, 3, 1, 4, 9, 6, 10, 40, 50 };

	/*Test11*/
	// LeftBalance_RH_RH_30_5
	//	             30
	//       5               40
	//    3    9                 50
	//  1  4  6 10
	//            15
	// 5_LeftRotate
	//	             30
	//       9               40
	//    5    10                 50
	//  3  6     15
	// 1 4
	// 30_RightRotate
	//	             9
	//       5               30
	//    3    6          10    40
	//   1 4                15    50
	int Key11 = 15;
	int Num11 = 11;
	bool Taller11 = false;
	int CmpAVLNode11[] = { 9, 5, 3, 1, 4, 6, 30, 10, 15, 40, 50 };

	/*Test12*/
	// RightBalance_RH
	//	             9
	//       5               30
	//    3    6          10    40
	//   1 4                15    50
	//                               60
	// 40_LeftRotate
	//	             9
	//       5                30
	//    3    6          10       50
	//   1 4                15  40   60
	int Key12 = 60;
	int Num12 = 12;
	bool Taller12 = false;
	int CmpAVLNode12[] = { 9, 5, 3, 1, 4, 6, 30, 10, 15, 50, 40, 60 };

	/*Test13*/
	// RightBalance_LH_EH
	//	              9
	//       5                 30
	//    3    6          10       50
	//   1 4                 15  40   60
	//                     12
	// 15_RightRotate
	//	              9
	//       5                 30
	//    3    6          10        50
	//   1 4                 12   40   60
	//                         15
	// 12_LeftRotate
	//	              9
	//       5                 30
	//    3    6          12        50
	//   1 4           10    15   40   60
	int Key13 = 12;
	int Num13 = 13;
	bool Taller13 = false;
	int CmpAVLNode13[] = { 9, 5, 3, 1, 4, 6, 30, 12, 10, 15, 50, 40, 60 };

	/*Test14*/
	// 6_RH
	//	              9
	//       5                 30
	//    3    6          12         50
	//   1 4     7      10    15   40    60
	int Key14 = 7;
	int Num14 = 14;
	bool Taller14 = false;
	int CmpAVLNode14[] = { 9, 5, 3, 1, 4, 6, 7, 30, 12, 10, 15, 50, 40, 60 };

	/*Test15*/
	// 60_RH
	//	              9
	//       5                 30
	//    3    6          12          50
	//   1 4     7      10    15   40    60
	//                                     70
	int Key15 = 70;
	int Num15 = 15;
	bool Taller15 = false;
	int CmpAVLNode15[] = { 9, 5, 3, 1, 4, 6, 7, 30, 12, 10, 15, 50, 40, 60, 70 };

	/*Test16*/
	// 60_EH
	//	              9
	//       5                 30
	//    3    6          12           50
	//   1 4     7      10    15   40     60
	//                                  55  70
	int Key16 = 55;
	int Num16 = 16;
	bool Taller16 = false;
	int CmpAVLNode16[] = { 9, 5, 3, 1, 4, 6, 7, 30, 12, 10, 15, 50, 40, 60, 55, 70 };

	/*Test17*/
	// RightBalance_LH_LH
	//	              9
	//       5                 30
	//    3    6          12            50
	//   1 4     7      10    15   40        60
	//                                     55  70
	//                                    53
	// 60_RightRotate
	//	              9
	//       5                 30
	//    3    6          12           50
	//   1 4     7      10    15   40      55
	//                                   53   60
	//                                          70
	// 50_LeftRotate
	//	              9
	//       5                    30
	//    3    6           12           55
	//   1 4     7      10    15     50    60
	//                             40  53    70
	int Key17 = 53;
	int Num17 = 17;
	bool Taller17 = false;
	int CmpAVLNode17[] = { 9, 5, 3, 1, 4, 6, 7, 30, 12, 10, 15, 55, 50, 40, 53, 60, 70 };

	/*Test18*/
	// RightBalance_LH_RH
	//	              9
	//       5                     30
	//    3    6           12                 55
	//   1 4     7      10    15         50      60
	//                                 40  53      70
	//                                      54
	// 55_RightRotate
	//	              9
	//       5                    30
	//    3    6           12              50
	//   1 4     7      10    15       40      55
	//                                      53    60
	//                                       54     70
	// 30_LeffRotate
	//	              9
	//       5                      50
	//    3    6             30            55
	//   1 4     7       12     40      53    60   
	//                 10   15           54     70
	int Key18 = 54;
	int Num18 = 18;
	bool Taller18 = false;
	int CmpAVLNode18[] = { 9, 5, 3, 1, 4, 6, 7, 50, 30, 12, 10, 15, 40, 55, 53, 54, 60, 70 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	AddAVLNode(&AVLNode, Key01, &Taller01);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode01, AVLNode, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	AddAVLNode(&AVLNode, Key02, &Taller02);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode02, AVLNode, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	AddAVLNode(&AVLNode, Key03, &Taller03);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode03, AVLNode, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	AddAVLNode(&AVLNode, Key04, &Taller04);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode04, AVLNode, Num04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	AddAVLNode(&AVLNode, Key05, &Taller05);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode05, AVLNode, Num05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	AddAVLNode(&AVLNode, Key06, &Taller06);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode06, AVLNode, Num06);

	/*Test07*/
	printf("\n-------Test 07----------\n");
	AddAVLNode(&AVLNode, Key07, &Taller07);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode07, AVLNode, Num07);

	/*Test08*/
	printf("\n-------Test 08----------\n");
	AddAVLNode(&AVLNode, Key08, &Taller08);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode08, AVLNode, Num08);

	/*Test09*/
	printf("\n-------Test 09----------\n");
	AddAVLNode(&AVLNode, Key09, &Taller09);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode09, AVLNode, Num09);

	/*Test10*/
	printf("\n-------Test 10----------\n");
	AddAVLNode(&AVLNode, Key10, &Taller10);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode10, AVLNode, Num10);

	/*Test11*/
	printf("\n-------Test 11----------\n");
	AddAVLNode(&AVLNode, Key11, &Taller11);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode11, AVLNode, Num11);

	/*Test12*/
	printf("\n-------Test 12----------\n");
	AddAVLNode(&AVLNode, Key12, &Taller12);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode12, AVLNode, Num12);

	/*Test13*/
	printf("\n-------Test 13----------\n");
	AddAVLNode(&AVLNode, Key13, &Taller13);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode13, AVLNode, Num13);

	/*Test14*/
	printf("\n-------Test 14----------\n");
	AddAVLNode(&AVLNode, Key14, &Taller14);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode14, AVLNode, Num14);

	/*Test15*/
	printf("\n-------Test 15----------\n");
	AddAVLNode(&AVLNode, Key15, &Taller15);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode15, AVLNode, Num15);

	/*Test16*/
	printf("\n-------Test 16----------\n");
	AddAVLNode(&AVLNode, Key16, &Taller16);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode16, AVLNode, Num16);

	/*Test17*/
	printf("\n-------Test 17----------\n");
	AddAVLNode(&AVLNode, Key17, &Taller17);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode17, AVLNode, Num17);

	/*Test18*/
	printf("\n-------Test 18----------\n");
	AddAVLNode(&AVLNode, Key18, &Taller18);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode18, AVLNode, Num18);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestBuildAVLTree*/
void TestBuildAVLTree(void) {
	/*Test01*/
	//         50
	AVL_TREE_NODE *AVLNode01 = NULL;
	int Arr01[] = { 50 };
	int Num01 = 1;
	int CmpAVLNode01[] = { 50 };

	/*Test02*/
	//  LeftBalance_LH
	//         50
	//      30
	//   20
	//  50_RightRotate
	//		   30
	//      20    50
	AVL_TREE_NODE *AVLNode02 = NULL;
	int Arr02[] = { 50, 30, 20 };
	int Num02 = 3;
	int CmpAVLNode02[] = { 30, 20, 50 };

	/*Test03*/
	//  LeftBalance_RH_EH
	//         50
	//     30
	//       40
	//  30_LeftRotate
	//		   50
	//      40
	//   30
	//  50_RightRotate
	//         40
	//      30    50
	AVL_TREE_NODE *AVLNode03 = NULL;
	int Arr03[] = { 50, 30, 40 };
	int Num03 = 3;
	int CmpAVLNode03[] = { 40, 30, 50 };

	/*Test04*/
	//  LeftBalance_RH_LH
	//             50
	//     30            60
	//  20    40
	//      35
	//  30_LeftRotate
	//		      50
	//      40           60
	//   30
	// 20  35
	//  50_RightRotate
	//            40
	//      30         50
	//    20  35         60
	AVL_TREE_NODE *AVLNode04 = NULL;
	int Arr04[] = { 50, 30, 20, 40, 35, 60 };
	int Num04 = 6;
	int CmpAVLNode04[] = { 40, 30, 20, 35, 50, 60 };

	/*Test05*/
	//  LeftBalance_RH_RH
	//             50
	//     30            60
	//  20    40
	//          45
	//  30_LeftRotate
	//		      50
	//      40           60
	//   30   45
	// 20
	//  50_RightRotate
	//            40
	//      30         50
	//    20        45    60
	AVL_TREE_NODE *AVLNode05 = NULL;
	int Arr05[] = { 50, 30, 60, 20, 40, 45 };
	int Num05 = 6;
	int CmpAVLNode05[] = { 40, 30, 20, 50, 45, 60 };

	/*Test06*/
	//  RightBalance_RH
	//         50
	//             60
	//                70
	//  50_LeftRotate
	//		   60
	//      50    70
	AVL_TREE_NODE *AVLNode06 = NULL;
	int Arr06[] = { 50, 60, 70 };
	int Num06 = 3;
	int CmpAVLNode06[] = { 60, 50, 70 };

	/*Test07*/
	//  RightBalance_LH_EH
	//         50
	//             60
	//           55
	//  60_RightRotate
	//		   50
	//             55
	//                60
	//  50_LeftRotate
	//		   55
	//      50    60
	AVL_TREE_NODE *AVLNode07 = NULL;
	int Arr07[] = { 50, 60, 55 };
	int Num07 = 3;
	int CmpAVLNode07[] = { 55, 50, 60 };

	/*Test08*/
	//  RightBalance_LH_LH
	//         50
	//    30         70
	//            60    80
	//           55
	//  70_RightRotate
	//		   50
	//    30         60
	//             55  70
	//                   80
	//  50_LeftRotate
	//		   60
	//    50         70
	//  30  55          80
	AVL_TREE_NODE *AVLNode08 = NULL;
	int Arr08[] = { 50, 30, 70, 60, 55, 80 };
	int Num08 = 6;
	int CmpAVLNode08[] = { 60, 50, 30, 55, 70, 80 };

	/*Test09*/
	//  RightBalance_LH_RH
	//         50
	//    30         70
	//            60    80
	//             65
	//  70_RightRotate
	//		   50
	//    30         60
	//                  70
	//                65  80
	//  50_LeftRotate
	//		   60
	//    50         70
	//  30         65  80
	AVL_TREE_NODE *AVLNode09 = NULL;
	int Arr09[] = { 50, 30, 70, 60, 80, 65 };
	int Num09 = 6;
	int CmpAVLNode09[] = { 60, 50, 30, 70, 65, 80 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildAVLTree(&AVLNode01, Arr01, Num01);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode01);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode01, AVLNode01, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildAVLTree(&AVLNode02, Arr02, Num02);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode02);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode02, AVLNode02, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	BuildAVLTree(&AVLNode03, Arr03, Num03);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode03);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode03, AVLNode03, Num03);

	/*Test04*/
	printf("\n-------Test 04----------\n");
	BuildAVLTree(&AVLNode04, Arr04, Num04);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode04);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode04, AVLNode04, Num04);

	/*Test05*/
	printf("\n-------Test 05----------\n");
	BuildAVLTree(&AVLNode05, Arr05, Num05);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode05);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode05, AVLNode05, Num05);

	/*Test06*/
	printf("\n-------Test 06----------\n");
	BuildAVLTree(&AVLNode06, Arr06, Num06);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode06);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode06, AVLNode06, Num06);

	/*Test07*/
	printf("\n-------Test 07----------\n");
	BuildAVLTree(&AVLNode07, Arr07, Num07);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode07);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode07, AVLNode07, Num07);

	/*Test08*/
	printf("\n-------Test 08----------\n");
	BuildAVLTree(&AVLNode08, Arr08, Num08);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode08);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode08, AVLNode08, Num08);

	/*Test09*/
	printf("\n-------Test 09----------\n");
	BuildAVLTree(&AVLNode09, Arr09, Num09);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode09);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode09, AVLNode09, Num09);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestDeleteAVLNode*/
void TestDeleteAVLNode(void) {
	/*Test01*/
	// Only_Del
	//         50
	//      30     70
	// 30_Del
	//         50
	//             70
	AVL_TREE_NODE *AVLNode01 = NULL;
	int Arr01[] = { 50, 30, 70 };
	int Num01 = 3;
	//int CmpAVLNode01[] = { 50, 30, 70 };
	int Key01 = 30;
	bool Shorter01 = false;
	int CmpNum01 = 2;
	int CmpAVLNode01[] = { 50, 70 };

	/*Test02*/
	// Only_Del
	//         50
	//      30     70
	// 70_Del
	//         50
	//      30
	AVL_TREE_NODE *AVLNode02 = NULL;
	int Arr02[] = { 50, 30, 70 };
	int Num02 = 3;
	//int CmpAVLNode02[] = { 50, 30, 70 };
	int Key02 = 70;
	bool Shorter02 = false;
	int CmpNum02 = 2;
	int CmpAVLNode02[] = { 50, 30 };

	/*Test03*/
	// Only_Del
	//         50
	//      30     70
	// 50_Del
	//         30
	//             70
	AVL_TREE_NODE *AVLNode03 = NULL;
	int Arr03[] = { 50, 30, 70 };
	int Num03 = 3;
	//int CmpAVLNode03[] = { 50, 30, 70 };
	int Key03 = 50;
	bool Shorter03 = false;
	int CmpNum03 = 2;
	int CmpAVLNode03[] = { 30, 70 };

	/*Test04*/
	// Leaf_leftbalance_LH
	//         50
	//      30     70
	//    20
	// 70_Del
	//         50
	//      30
	//    20
	// 50_RightRotate
	//         30
	//      20    50
	AVL_TREE_NODE *AVLNode04 = NULL;
	int Arr04[] = { 50, 30, 70, 20 };
	int Num04 = 4;
	//int CmpAVLNode04[] = { 50, 30, 20, 70};
	int Key04 = 70;
	bool Shorter04 = false;
	int CmpNum04 = 3;
	int CmpAVLNode04[] = { 30, 20, 50 };

	/*Test05*/
	// Leaf_Leftbalance_RH_EH
	//         50
	//      30     70
	//       40
	// 70_Del
	//         50
	//      30
	//       40
	// 30_LeftRotate
	//         50
	//      40
	//    30
	// 50_RightRotate
	//         40
	//      30    50
	AVL_TREE_NODE *AVLNode05 = NULL;
	int Arr05[] = { 50, 30, 70, 40 };
	int Num05 = 4;
	//int CmpAVLNode05[] = { 50, 30, 40, 70};
	int Key05 = 70;
	bool Shorter05 = false;
	int CmpNum05 = 3;
	int CmpAVLNode05[] = { 40, 30, 50 };

	/*Test06*/
	// Leaf_Leftbalance_RH_LH
	//         50
	//      30     70
	//    20  40     80
	//       35
	// 70_Del
	//         50
	//      30     80
	//    20  40
	//       35
	// 30_LeftRotate
	//         50
	//      40   80
	//    30
	//  20 35
	// 50_RightRotate
	//         40
	//      30    50
	//    20 35    80
	AVL_TREE_NODE *AVLNode06 = NULL;
	int Arr06[] = { 50, 30, 70, 20, 40, 80, 35 };
	int Num06 = 7;
	//int CmpAVLNode06[] = { 50, 30, 20, 40, 35, 70, 80};
	int Key06 = 70;
	bool Shorter06 = false;
	int CmpNum06 = 6;
	int CmpAVLNode06[] = { 40, 30, 20, 35, 50, 80 };

	/*Test07*/
	// Leaf_Leftbalance_RH_RH
	//         50
	//      30     70
	//    20  40     80
	//         45
	// 70_Del
	//         50
	//      30     80
	//    20  40
	//         45
	// 30_LeftRotate
	//         50
	//      40   80
	//    30 45
	//  20 
	// 50_RightRotate
	//         40
	//      30    50
	//    20    45  80
	AVL_TREE_NODE *AVLNode07 = NULL;
	int Arr07[] = { 50, 30, 70, 20, 40, 80, 45 };
	int Num07 = 7;
	//int CmpAVLNode07[] = { 50, 30, 20, 40, 45, 70, 80};
	int Key07 = 70;
	bool Shorter07 = false;
	int CmpNum07 = 6;
	int CmpAVLNode07[] = { 40, 30, 20, 50, 45, 80 };


	/*Test08*/
	// Leaf_Rightbalance_RH
	//         50
	//      30     70
	//               80
	// 30_Del
	//         50
	//             70
	//               80
	// 50_LeftRotate
	//         70
	//      50    80
	AVL_TREE_NODE *AVLNode08 = NULL;
	int Arr08[] = { 50, 30, 70, 80 };
	int Num08 = 4;
	//int CmpAVLNode08[] = { 50, 30, 70, 80};
	int Key08 = 30;
	bool Shorter08 = false;
	int CmpNum08 = 3;
	int CmpAVLNode08[] = { 70, 50, 80 };

	/*Test09*/
	// Leaf_Rightbalance_LH_EH
	//         50
	//      30     70
	//            60
	// 30_Del
	//         50
	//             70
	//            60
	// 70_RightRotate
	//         50
	//            60
	 //              70
	// 50_LeftRotate
	//         60
	//      50    70
	AVL_TREE_NODE *AVLNode09 = NULL;
	int Arr09[] = { 50, 30, 70, 60 };
	int Num09 = 4;
	//int CmpAVLNode09[] = { 50, 30, 70, 60};
	//int CmpNum09 = 4;
	int Key09 = 30;
	bool Shorter09 = false;
	int CmpNum09 = 3;
	int CmpAVLNode09[] = { 60, 50, 70 };


	/*Test10*/
	// Leaf_Rightbalance_LH_LH
	//         50
	//      30     70
	//    20     60  80
	//          55
	// 30_Del
	//         50
	//      20     70
	//           60  80
	//          55
	// 70_RightRotate
	//         50
	//      20     60
	//           55  70
	//                80
	// 50_LeftRotate
	//         60
	//      50     70
	//    20  55     80
	AVL_TREE_NODE *AVLNode10 = NULL;
	int Arr10[] = { 50, 30, 70, 20, 60, 80, 55 };
	int Num10 = 7;
	// int CmpAVLNode10[] = { 50, 30, 20, 70, 60, 55, 80};
	// int CmpNum10 = 7;
	int Key10 = 30;
	bool Shorter10 = false;
	int CmpNum10 = 6;
	int CmpAVLNode10[] = { 60, 50, 20, 55, 70, 80 };

	/*Test11*/
	// Leaf_Rightbalance_LH_RH
	//         50
	//      30     70
	//    20     60  80
	//            65
	// 30_Del
	//         50
	//      20     70
	//           60  80
	//            65
	// 70_RightRotate
	//         50
	//      20     60
	//               70
	//              65 80
	// 50_LeftRotate
	//         60
	//      50     70
	//    20     65  80
	AVL_TREE_NODE *AVLNode11 = NULL;
	int Arr11[] = { 50, 30, 70, 20, 60, 80, 65 };
	int Num11 = 7;
	// int CmpAVLNode11[] = { 50, 30, 20, 70, 60, 65, 80};
	// int CmpNum11 = 7;
	int Key11 = 30;
	bool Shorter11 = false;
	int CmpNum11 = 6;
	int CmpAVLNode11[] = { 60, 50, 20, 70, 65, 80 };


	/*Test12*/
	// OnlyDel_NoRotate
	//             50
	//       30          70
	//    20    40     60  80
	//  10     35
	// 50_del
	//             40
	//       30          70
	//    20    35     60  80 
	//  10
	AVL_TREE_NODE *AVLNode12 = NULL;
	int Arr12[] = { 50, 30, 70, 20, 40, 60, 80, 10, 35 };
	int Num12 = 9;
	//int CmpAVLNode12[] = { 50, 30, 20, 10, 40, 35, 70, 60, 80 };
	//int CmpNum12 = 9;
	int Key12 = 50;
	bool Shorter12 = false;
	int CmpNum12 = 8;
	int CmpAVLNode12[] = { 40, 30, 20, 10, 35, 70, 60, 80 };

	/*Test13*/
	// OnlyDel_NoRotate
	//                            50
	//            30                            70
	//     20              40               60       80
	//  10   25         35    45          55  65   75  90
	// 5 15           33 37  43                         100
	//              31
	// 50_del
	//                            45
	//            30                            70
	//     20              40               60       80
	//  10   25         35    43          55  65   75  90
	// 5 15           33 37                           100
	//              31
	// 40_RightRotate
	//                            45
	//            30                            70
	//     20              35               60       80
	//  10   25         33    40          55  65   75  90
	// 5 15           31    37  43                      100
	AVL_TREE_NODE *AVLNode13 = NULL;
	int Arr13[] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 90, 5, 15, 33, 37, 43, 100, 31 };
	int Num13 = 22;
	//int CmpAVLNode13[] = { 50, 30, 20, 10, 5, 15, 25, 40, 35, 33, 31, 37, 45, 43, 70, 60, 55, 65, 80, 75, 90, 100 };
	//int CmpNum13 = 22;
	int Key13 = 50;
	bool Shorter13 = false;
	int CmpNum13 = 21;
	int CmpAVLNode13[] = { 45, 30, 20, 10, 5, 15, 25, 35, 33, 31, 40, 37, 43, 70, 60, 55, 65, 80, 75, 90, 100 };

	/*Test14*/
	// Root_Tmp01_EH_RootRightbalance_RH
	//          50
	//    20          70
	//      30     60   80
	//                   90
	// 50_Del
	//          30
	//    20          70
	//             60   80
	//                   90
	// 30_LeftRotate
	//          70
	//    30          80
	//   20 60         90
	AVL_TREE_NODE *AVLNode14 = NULL;
	int Arr14[] = { 50, 20, 70, 30, 60, 80, 90 };
	int Num14 = 7;
	// int CmpAVLNode14[] = { 50, 20, 30, 70, 60, 80, 90 };
	// int CmpNum14 = 7;
	int Key14 = 50;
	bool Shorter14 = false;
	int CmpNum14 = 6;
	int CmpAVLNode14[] = { 70, 30, 20, 60, 80, 90 };


	/*Test15*/
	// Root_Tmp01Leftbalance_LH_RootRightbalance_RH
	//          50
	//    20          70
	//  10   30     60   80
	// 5           55   75  90
	//                       100
	// 50_Del
	//          30
	//    20          70
	//  10         60   80
	// 5           55  75  90
	//                      100
	// 20_RightRotate
	//          30
	//    10          70
	//  5   20      60   80
	//             55  75  90
	//                      100
	// 30_LeftRotate
	//          70
	//    30          80
	//  10   60     75  90
	// 5 20 55           100
	AVL_TREE_NODE *AVLNode15 = NULL;
	int Arr15[] = { 50, 20, 70, 10, 30, 60, 80, 5, 55, 75, 90, 100 };
	int Num15 = 12;
	// int CmpAVLNode15[] = { 50, 20, 10, 5, 30, 70, 60, 55, 80, 75, 90, 100 };
	// int CmpNum15 = 12;
	int Key15 = 50;
	bool Shorter15 = false;
	int CmpNum15 = 11;
	int CmpAVLNode15[] = { 70, 30, 10, 5, 20, 60, 55, 80, 75, 90, 100 };


	/*Test16*/
	// Root_Tmp01Leftbalance_RH_RootRightbalance_RH
	//          50
	//    20          70
	//  10   30     60   80
	//   15       55   75  90
	//                       100
	// 50_Del
	//          30
	//    20          70
	//  10         60   80
	//   15       55  75  90
	//                      100
	// 10_LeftRotate
	//          30
	//    20          70
	//  15         60   80
	// 10         55  75  90
	//                      100
	// 20_RightRotate
	//          30
	//    15          70
	//  10  20      60   80
	//            55  75  90
	//                      100
	// 30_LeftRotate
	//          70
	//    30          80
	//  15   60     75  90
	//10 20 55           100
	AVL_TREE_NODE *AVLNode16 = NULL;
	int Arr16[] = { 50, 20, 70, 10, 30, 60, 80, 15, 55, 75, 90, 100 };
	int Num16 = 12;
	// int CmpAVLNode16[] = { 50, 20, 10, 15, 30, 70, 60, 55, 80, 75, 90, 100 };
	// int CmpNum16 = 12;
	int Key16 = 50;
	bool Shorter16 = false;
	int CmpNum16 = 11;
	int CmpAVLNode16[] = { 70, 30, 15, 10, 20, 60, 55, 80, 75, 90, 100 };

	/*Test17*/
	// Root_Tmp01Leftbalance_LH_RootRightbalance_RH
	//            50
	//      20            70
	//    10   30     60        80
	//   5 15 25    55 67    75     90
	//  3          53   68  73    85  100
	//                                  110
	// 50_Del
	//            30
	//      20            70
	//    10   25     60        80
	//   5 15       55 67    75     90
	//  3          53   68  73    85  100
	//                                  110
	// 20_RightRotate
	//            30
	//      10            70
	//    5    20     60       80
	//   3   15 25  55 67    75    90
	//             53   68  73    85  100
	//                                  110
	// 30_LeftRotate
	//                     70
	//          30                    80
	//    10         60           75      90
	//  5   20     55  67        73     85  100
	// 3   15 25  53    68                   110
	AVL_TREE_NODE *AVLNode17 = NULL;
	int Arr17[] = { 50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 55, 67, 75, 90, 3, 53, 68, 73, 85, 100, 110 };
	int Num17 = 21;
	// int CmpAVLNode15[] = { 50, 20, 10, 5, 3, 15, 30, 25, 70, 60, 55, 53, 67, 68, 80, 75, 73, 90, 85, 100, 110 };
	// int CmpNum15 = 21;
	int Key17 = 50;
	bool Shorter17 = false;
	int CmpNum17 = 20;
	int CmpAVLNode17[] = { 70, 30, 10, 5, 3, 20, 15, 25, 60, 55, 53, 67, 68, 80, 75, 73, 90, 85, 100, 110 };


	/*Test18*/
	// Leftbalance_RH_RootRightbalance_RH
	//          50
	//    20          70
	//  10   30     60   80
	// 5          55   75  90
	//                       100
	// 30_Del
	//          50
	//    20          70
	//  10          60   80
	// 5          55   75  90
	//                       100
	// 20_RightRotate
	//          50
	//    10          70
	//  5   20      60   80
	//            55   75  90
	//                       100
	// 50_LeftRotate
	//            70
	//      50          80
	//   10    60     75   90
	//  5 20  55             100
	AVL_TREE_NODE *AVLNode18 = NULL;
	int Arr18[] = { 50, 20, 70, 10, 30, 60, 80, 5, 55, 75, 90, 100 };
	int Num18 = 12;
	// int CmpAVLNode18[] = { 50, 20, 10, 5, 30, 70, 60, 55, 80, 75, 90, 100 };
	// int CmpNum18 = 12;
	int Key18 = 30;
	bool Shorter18 = false;
	int CmpNum18 = 11;
	int CmpAVLNode18[] = { 70, 50, 10, 5, 20, 60, 55, 80, 75, 90, 100 };


	/*Test19*/
	// No_Rotate
	//          50
	//    20          70
	//  10   30
	// 30_Del
	//          50
	//    20          70
	//  10
	AVL_TREE_NODE *AVLNode19 = NULL;
	int Arr19[] = { 50, 20, 70, 10, 30 };
	int Num19 = 5;
	// int CmpAVLNode19[] = { 50, 20, 10, 30, 70 };
	// int CmpNum19 = 5;
	int Key19 = 30;
	bool Shorter19 = false;
	int CmpNum19 = 4;
	int CmpAVLNode19[] = { 50, 20, 10, 70 };


	printf("-------Test start----------\n");
	InitNum();

	 /*Test01*/
	 printf("\n-------Test 01----------\n");
	 BuildAVLTree(&AVLNode01, Arr01, Num01);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode01);
	 DeleteAVLNode(&AVLNode01, Key01, &Shorter01);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode01);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode01, AVLNode01, CmpNum01);

	 /*Test02*/
	 printf("\n-------Test 02----------\n");
	 BuildAVLTree(&AVLNode02, Arr02, Num02);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode02);
	 DeleteAVLNode(&AVLNode02, Key02, &Shorter02);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode02);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode02, AVLNode02, CmpNum02);

	 /*Test03*/
	 printf("\n-------Test 03----------\n");
	 BuildAVLTree(&AVLNode03, Arr03, Num03);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode03);
	 DeleteAVLNode(&AVLNode03, Key03, &Shorter03);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode03);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode03, AVLNode03, CmpNum03);

	 /*Test04*/
	 printf("\n-------Test 04----------\n");
	 BuildAVLTree(&AVLNode04, Arr04, Num04);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode04);
	 DeleteAVLNode(&AVLNode04, Key04, &Shorter04);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode04);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode04, AVLNode04, CmpNum04);

	 /*Test05*/
	 printf("\n-------Test 05----------\n");
	 BuildAVLTree(&AVLNode05, Arr05, Num05);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode05);
	 DeleteAVLNode(&AVLNode05, Key05, &Shorter05);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode05);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode05, AVLNode05, CmpNum05);

	 /*Test06*/
	 printf("\n-------Test 06----------\n");
	 BuildAVLTree(&AVLNode06, Arr06, Num06);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode06);
	 DeleteAVLNode(&AVLNode06, Key06, &Shorter06);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode06);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode06, AVLNode06, CmpNum06);

	 /*Test07*/
	 printf("\n-------Test 07----------\n");
	 BuildAVLTree(&AVLNode07, Arr07, Num07);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode07);
	 DeleteAVLNode(&AVLNode07, Key07, &Shorter07);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode07);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode07, AVLNode07, CmpNum07);

	 /*Test08*/
	 printf("\n-------Test 08----------\n");
	 BuildAVLTree(&AVLNode08, Arr08, Num08);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode08);
	 DeleteAVLNode(&AVLNode08, Key08, &Shorter08);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode08);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode08, AVLNode08, CmpNum08);

	 /*Test09*/
	 printf("\n-------Test 09----------\n");
	 BuildAVLTree(&AVLNode09, Arr09, Num09);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode09);
	 DeleteAVLNode(&AVLNode09, Key09, &Shorter09);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode09);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode09, AVLNode09, CmpNum09);

	 /*Test10*/
	 printf("\n-------Test 10----------\n");
	 BuildAVLTree(&AVLNode10, Arr10, Num10);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode10);
	 DeleteAVLNode(&AVLNode10, Key10, &Shorter10);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode10);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode10, AVLNode10, CmpNum10);

	 /*Test11*/
	 printf("\n-------Test 11----------\n");
	 BuildAVLTree(&AVLNode11, Arr11, Num11);
	 printf("PreOrderTraversePrintAVLTree\n");
	 PreOrderTraversePrintAVLTree(AVLNode11);
	 DeleteAVLNode(&AVLNode11, Key11, &Shorter11);
	 printf("After DeleteAVLNode\n");
	 PreOrderTraversePrintAVLTree(AVLNode11);
	 printf("Compare\n");
	 CmpPreOderBuildAVLTree(CmpAVLNode11, AVLNode11, CmpNum11);

	/*Test12*/
	printf("\n-------Test 12----------\n");
	BuildAVLTree(&AVLNode12, Arr12, Num12);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode12);
	DeleteAVLNode(&AVLNode12, Key12, &Shorter12);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode12);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode12, AVLNode12, CmpNum12);

	/*Test13*/
	printf("\n-------Test 13----------\n");
	BuildAVLTree(&AVLNode13, Arr13, Num13);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode13);
	DeleteAVLNode(&AVLNode13, Key13, &Shorter13);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode13);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode13, AVLNode13, CmpNum13);

	/*Test14*/
	printf("\n-------Test 14----------\n");
	BuildAVLTree(&AVLNode14, Arr14, Num14);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode14);
	DeleteAVLNode(&AVLNode14, Key14, &Shorter14);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode14);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode14, AVLNode14, CmpNum14);

	/*Test15*/
	printf("\n-------Test 15----------\n");
	BuildAVLTree(&AVLNode15, Arr15, Num15);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode15);
	DeleteAVLNode(&AVLNode15, Key15, &Shorter15);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode15);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode15, AVLNode15, CmpNum15);

	/*Test16*/
	printf("\n-------Test 16----------\n");
	BuildAVLTree(&AVLNode16, Arr16, Num16);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode16);
	DeleteAVLNode(&AVLNode16, Key16, &Shorter16);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode16);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode16, AVLNode16, CmpNum16);

	/*Test17*/
	printf("\n-------Test 17----------\n");
	BuildAVLTree(&AVLNode17, Arr17, Num17);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode17);
	DeleteAVLNode(&AVLNode17, Key17, &Shorter17);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode17);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode17, AVLNode17, CmpNum17);

	/*Test18*/
	printf("\n-------Test 18----------\n");
	BuildAVLTree(&AVLNode18, Arr18, Num18);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode18);
	DeleteAVLNode(&AVLNode18, Key18, &Shorter18);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode18);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode18, AVLNode18, CmpNum18);

	/*Test19*/
	printf("\n-------Test 19----------\n");
	BuildAVLTree(&AVLNode19, Arr19, Num19);
	printf("PreOrderTraversePrintAVLTree\n");
	PreOrderTraversePrintAVLTree(AVLNode19);
	DeleteAVLNode(&AVLNode19, Key19, &Shorter19);
	printf("After DeleteAVLNode\n");
	PreOrderTraversePrintAVLTree(AVLNode19);
	printf("Compare\n");
	CmpPreOderBuildAVLTree(CmpAVLNode19, AVLNode19, CmpNum19);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}



void PrintHashTable(HASH_TABLE *HTable) {
	int i = 0;

	for (i = 0; i < HTable->Num; i++) {
		printf("HTable->Table[%d] = %d\n", i, HTable->Table[i]);
	}
}

/*TestSearchHash*/
void TestSearchHash(void) {
	/*Test01*/
	// {5, 1, 2, 3, 4}
	HASH_TABLE *HTable01 = NULL;
	int Arr01[] = { 1, 3, 5, 2, 4 };
	int Num01 = 5;
	int Key01 = 3;
	int Res01;
	int CmpRes01 = 3;

	/*Test02*/
	// {5, 1, 10, 3, 8}
	HASH_TABLE *HTable02 = NULL;
	int Arr02[] = { 1, 3, 5, 10, 8 };
	int Num02 = 5;
	int Key02 = 10;
	int Res02;
	int CmpRes02 = 10;

	/*Test03*/
	// {5, 1, 10, 3, 8}
	HASH_TABLE *HTable03 = NULL;
	int Arr03[] = { 1, 3, 5, 10, 8 };
	int Num03 = 5;
	int Key03 = 4;
	int Res03;
	int CmpRes03 = -1;

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	HashTableInit(&HTable01, Num01);
	InsertHash(HTable01, Arr01, Num01);
	PrintHashTable(HTable01);
	Res01 = SearchHash(HTable01, Key01);
	TestCmpRes(CmpRes01, Res01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	HashTableInit(&HTable02, Num02);
	InsertHash(HTable02, Arr02, Num02);
	PrintHashTable(HTable02);
	Res02 = SearchHash(HTable02, Key02);
	TestCmpRes(CmpRes02, Res02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	HashTableInit(&HTable03, Num03);
	InsertHash(HTable03, Arr03, Num03);
	PrintHashTable(HTable03);
	Res03 = SearchHash(HTable03, Key03);
	TestCmpRes(CmpRes03, Res03);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


void TestMGraph(M_GRAPH *MGraph01, M_GRAPH *MGraph02) {
	int i, j;

	TestNum++;

	if ((MGraph01->VectorNum != MGraph02->VectorNum) || (MGraph01->EadgeNum != MGraph02->EadgeNum)) {
		FaildNum++;
		return;
	}

	for (i = 0; i < MGraph01->VectorNum; i++) {
		if (MGraph01->Vector[i] != MGraph02->Vector[i]) {
			FaildNum++;
			return;
		}
	}

	for (i = 0; i < MGraph01->VectorNum; i++) {
		for (j = 0; j < MGraph01->VectorNum; j++) {
			if (MGraph01->Eadge[i][j] != MGraph02->Eadge[i][j]) {
				FaildNum++;
				return;
			}
		}
	}

	PassNum++;
}

void TestBuildMGraph(void) {
	/*Test01*/
	M_GRAPH  MGraph01;
	int Vector01[] = { 0, 1, 2, 3 };
	int Eadge01[][4] = { {0, 1, 1, 1},
						  {1, 0, 1, 0},
						{1, 1, 0, 1},
						{1, 0, 1, 0} };
	int VectorNum01 = 4;
	int EadgeNum01 = 5;

	M_GRAPH CmpGraph01 = { 4, 5, {0, 1, 2, 3},
			{ {0, 1, 1, 1},
			  {1, 0, 1, 0},
			  {1, 1, 0, 1},
			  {1, 0, 1, 0} } };

	/*Test02*/
	M_GRAPH  MGraph02;
	int Vector02[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	// A  B  C  D  E  F  G  H  I  
	int Eadge02[][9] = { {0, 1, 0, 0, 0, 1, 0, 0, 0},  //A
						 {1, 0, 1, 0, 0, 0, 1, 0, 1},  //B
					   {0, 1, 0, 1, 0, 0, 0, 0, 1},  //C
					   {0, 0, 1, 0, 1, 0, 1, 1, 1},  //D
			  {0, 0, 0, 1, 0, 1, 0, 1, 0},  //E
			  {1, 0, 0, 0, 1, 0, 1, 0, 0},  //F
			  {0, 1, 0, 1, 0, 1, 0, 1, 0},  //G
			  {0, 0, 0, 1, 1, 0, 1, 0, 0},  //H
			  {0, 1, 1, 1, 0, 0, 0, 0, 0},  //I
	};
	int VectorNum02 = 9;
	int EadgeNum02 = 15;
	M_GRAPH CmpGraph02 = { 9, 15, { 0, 1, 2, 3, 4, 5, 6, 7, 8},
								   {{0, 1, 0, 0, 0, 1, 0, 0, 0},  //A
									{1, 0, 1, 0, 0, 0, 1, 0, 1},  //B
								  {0, 1, 0, 1, 0, 0, 0, 0, 1},  //C
								  {0, 0, 1, 0, 1, 0, 1, 1, 1},  //D
						{0, 0, 0, 1, 0, 1, 0, 1, 0},  //E
						{1, 0, 0, 0, 1, 0, 1, 0, 0},  //F
						{0, 1, 0, 1, 0, 1, 0, 1, 0},  //G
						{0, 0, 0, 1, 1, 0, 1, 0, 0},  //H
						{0, 1, 1, 1, 0, 0, 0, 0, 0},  //I
						  }
	};
	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildMGraph(&MGraph01, Vector01, (int *)Eadge01, VectorNum01, EadgeNum01);
	PrintMGraph(&MGraph01);
	TestMGraph(&CmpGraph01, &MGraph01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildMGraph(&MGraph02, Vector02, Eadge02, VectorNum02, EadgeNum02);
	PrintMGraph(&MGraph02);
	TestMGraph(&CmpGraph02, &MGraph02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestBuildAdjustListGraph*/
void TestBuildAdjustListGraph(void) {
	/*Test01*/
	ADJUST_LIST_GRAPH  AdjListGraph01;
	ADJUST_LIST_GRAPH  AdjListGraphData01 = { 4, 5, {{0, NULL}, {10, NULL}, {20, NULL}, {30, NULL}} };
	LIST_NODE_DATA     AdjListNodeData01[] = { {3, {1, 2, 3}}, {2, {0, 2}}, {3, {0, 1, 3}}, {2, {0, 2}} };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");

	BuildAdjustListGraph(&AdjListGraph01, &AdjListGraphData01, AdjListNodeData01);
	PrintAdjLstGraph(&AdjListGraph01);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestMGraphDFS*/
void TestMGraphDFS(void) {
	/*Test01*/
	M_GRAPH  MGraph01;
	int Vector01[] = { 0, 1, 2, 3 };
	// A  B  C  D  
	int Eadge01[][4] = { {0, 1, 1, 1},  //A
						 {1, 0, 1, 0},  //B
					   {1, 1, 0, 1},  //C
					   {1, 0, 1, 0},  //D
	};
	int VectorNum01 = 4;
	int EadgeNum01 = 5;
	M_GRAPH CmpGraph01 = { 4, 5, { 0, 1, 2, 3},
								  {{0, 1, 1, 1},  //A
								   {1, 0, 1, 0},  //B
								 {1, 1, 0, 1},  //C
								 {1, 0, 1, 0},  //D
						 }
	};
	bool Visited01[4] = { 0 };
	int CmpVector01[] = { 0, 1, 2, 3 };

	/*Test02*/
	M_GRAPH  MGraph02;
	int Vector02[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	// A  B  C  D  E  F  G  H  I  
	int Eadge02[][9] = { {0, 1, 0, 0, 0, 1, 0, 0, 0},  //A
						 {1, 0, 1, 0, 0, 0, 1, 0, 1},  //B
					   {0, 1, 0, 1, 0, 0, 0, 0, 1},  //C
					   {0, 0, 1, 0, 1, 0, 1, 1, 1},  //D
			  {0, 0, 0, 1, 0, 1, 0, 1, 0},  //E
			  {1, 0, 0, 0, 1, 0, 1, 0, 0},  //F
			  {0, 1, 0, 1, 0, 1, 0, 1, 0},  //G
			  {0, 0, 0, 1, 1, 0, 1, 0, 0},  //H
			  {0, 1, 1, 1, 0, 0, 0, 0, 0},  //I
	};
	int VectorNum02 = 9;
	int EadgeNum02 = 15;
	M_GRAPH CmpGraph02 = { 9, 15, { 0, 1, 2, 3, 4, 5, 6, 7, 8},
								   {{0, 1, 0, 0, 0, 1, 0, 0, 0},  //A
									{1, 0, 1, 0, 0, 0, 1, 0, 1},  //B
								  {0, 1, 0, 1, 0, 0, 0, 0, 1},  //C
								  {0, 0, 1, 0, 1, 0, 1, 1, 1},  //D
						{0, 0, 0, 1, 0, 1, 0, 1, 0},  //E
						{1, 0, 0, 0, 1, 0, 1, 0, 0},  //F
						{0, 1, 0, 1, 0, 1, 0, 1, 0},  //G
						{0, 0, 0, 1, 1, 0, 1, 0, 0},  //H
						{0, 1, 1, 1, 0, 0, 0, 0, 0},  //I
						  }
	};
	bool Visited02[9] = { 0 };
	int CmpVector02[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	printf("-------Test start----------\n");
	InitNum();

	/*Test01*/
	printf("\n-------Test 01----------\n");
	BuildMGraph(&MGraph01, Vector01, (int *)Eadge01, VectorNum01, EadgeNum01);
	PrintMGraph(&MGraph01);
	//TestMGraph(&CmpGraph01, &MGraph01);
	MGraphDFS(&MGraph01, Visited01);
	TestCmpArr(CmpVector01, VectorNum01, MGraph01.Vector);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	BuildMGraph(&MGraph02, Vector02, (int *)Eadge02, VectorNum02, EadgeNum02);
	PrintMGraph(&MGraph02);
	//TestMGraph(&CmpGraph02, &MGraph02);
	MGraphDFS(&MGraph02, Visited02);
	TestCmpArr(CmpVector02, VectorNum02, MGraph02.Vector);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}


/*TestAdjLstGraphDFS*/
void TestAdjLstGraphDFS(void) {

}

