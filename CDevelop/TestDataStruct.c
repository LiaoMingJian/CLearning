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



/*BINARY_TREE_NODE*/
static int PreOrderTraverseCompareNum = 0;

void PreOrderTraverseCompare(const int *CmpNode, const BINARY_TREE_NODE *BiTreeNode, unsigned int Index) {	
	if (BiTreeNode == NULL) {
		return;
	} else {
		if (BiTreeNode->Data == CmpNode[Index]) {
			PreOrderTraverseCompareNum++;
		}
	
		Index++;
		PreOrderTraverseCompare(CmpNode, BiTreeNode->LeftChild, Index);
		PreOrderTraverseCompare(CmpNode, BiTreeNode->RightChild, Index);	
	} 
}

void CmpPreOderBuildBinaryTree(const int *CmpNode, const BINARY_TREE_NODE *BiTreeNode, int Num) {
	unsigned int Index = 0;
	
	TestNum++;

	PreOrderTraverseCompare(CmpNode, BiTreeNode, Index);	

	if (PreOrderTraverseCompareNum != PreOrderTraverseCompareNum) {
		FaildNum++;
	} else {
		PassNum++;
	}
}

void TestPreOderBuildBinaryTree(void) {
	/*Test01*/
	BINARY_TREE_NODE *BiTreeNodePtr01 = NULL;
	int Data01[] = {10, 20, 0, 40, 0, 0, 30, 0, 0};
	int Index01 = 0;
	int CmpBiTreeNodeData01[] = { 10, 20, 40, 30 };

	/*Test02*/
	BINARY_TREE_NODE *BiTreeNodePtr02 = NULL;
	BINARY_TREE_NODE_DATA Data02[] = { {10, 1, 1}, {20, 0, 1}, {40, 0, 0}, {30, 0, 0} };
	int Index02 = 0;
	int IfExistNodeFlag02 = 1;
	int CmpBiTreeNodeData02[] = {10, 20, 40, 30};

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	PreOderBuildBinaryTree01(&BiTreeNodePtr01, Data01, Index01);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr01);
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData01, BiTreeNodePtr01, Index01);

	/*Test02*/
	printf("\n-------Test 02----------\n");
	PreOderBuildBinaryTree02(&BiTreeNodePtr02, Data02, Index02, IfExistNodeFlag02);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryTree(BiTreeNodePtr02);
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData02, BiTreeNodePtr02, Index02);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}




/*BINARY_THREAD_TREE_NODE*/
void TestPreOderBuildBinaryThreadTree(void) {
	/*Test01*/
	BINARY_THREAD_TREE_NODE *BiTreeNodePtr01 = NULL;
	char Data01[] = { 'A', 'B', 'D', 'H', '\0', '\0','I', '\0', '\0', 'E', 'J', '\0', '\0', '\0', 'C', 'F', '\0', '\0', 'G', '\0', '\0' };
	int Index01 = 0;
	int CmpBiTreeNodeData01[] = { 'A', 'B', 'D', 'H', 'I', 'E', 'J', 'C', 'F', 'G' };

	printf("-------Test start----------\n");
	InitNum();
	/*Test01*/
	printf("-------Test 01----------\n");
	PreOderBuildBinaryThreadTree01(&BiTreeNodePtr01, Data01, Index01);
	printf("PreOrderTraversePrintBinaryTree\n");
	PreOrderTraversePrintBinaryThreadTree(BiTreeNodePtr01);
	printf("InOrderTraversePrintBinaryTree\n");
	InOrderTraversePrintBinaryThreadTree(BiTreeNodePtr01);
	printf("PostOrderTraversePrintBinaryTree\n");
	PostOrderTraversePrintBinaryThreadTree(BiTreeNodePtr01);
	CmpPreOderBuildBinaryTree(CmpBiTreeNodeData01, BiTreeNodePtr01, Index01);

	/*Test Result*/
	printf("\n-------Test result----------\n");
	TestResult();
}