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
	}
	else {
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
	//unsigned char Index = 0;
	BiIndex = 0;
	PreOrderTraverseCompareNum = 0;

	TestNum++;

	PreOrderTraverseCompare(CmpNode, BiTreeNode);
	printf("PreOrderTraverseCompareNum = %d, NodeNum = %d\n", PreOrderTraverseCompareNum, NodeNum);
	if (PreOrderTraverseCompareNum != NodeNum) {
		FaildNum++;
	}
	else {
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
	//     50
	//  10     70
	//    30  
	BINARY_TREE_NODE *BiTreeNodePtr = NULL;
	BINARY_TREE_NODE_DATA Data[] = { {50, 1, 1}, {10, 0, 1}, {30, 0, 0}, {70, 0, 0} };
	char IfExistNodeFlag = 1;

	/*Test01*/
	//      50
	//  10      70
	//    30  
	//   20
	BINARY_TREE_NODE AddNode01 = { 20, NULL, NULL };
	int Num01 = 5;
	int CmpBSTNode01[] = { 50, 10, 30, 20, 70 };

	/*Test02*/
	//          50
	//    10         70
	// 5     30  
	//	  20
	BINARY_TREE_NODE AddNode02 = { 5, NULL, NULL };
	int Num02 = 6;
	int CmpBSTNode02[] = { 50, 10, 5, 30, 20, 70 };

	/*Test03*/
	//          50
	//    10          70
	// 5     30    60
	//	  20
	BINARY_TREE_NODE AddNode03 = { 60, NULL, NULL };
	int Num03 = 7;
	int CmpBSTNode03[] = { 50, 10, 5, 30, 20, 70, 60 };

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
	AddBSTNode(BiTreeNodePtr, &AddNode01);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode01, BiTreeNodePtr, Num01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	AddBSTNode(BiTreeNodePtr, &AddNode02);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode02, BiTreeNodePtr, Num02);

	/*Test03*/
	printf("\n-------Test 03----------\n");
	AddBSTNode(BiTreeNodePtr, &AddNode03);
	printf("Compare\n");
	CmpPreOderBuildBinaryTree(CmpBSTNode03, BiTreeNodePtr, Num03);

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

