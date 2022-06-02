//#pragma once
#ifndef _DATA_STRUCT_H
#define _DATA_STRUCT_H

#define SUCCESS			1
#define ERROR			0
#define MAXSIZE			10

typedef int ElemType;
typedef int LIST_STATUS;

typedef struct SQ_LIST_ {
	ElemType Data[MAXSIZE];
	int Len;
}SQ_LIST;

SQ_LIST L;

LIST_STATUS OperatorList();

#endif