#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "test.h"


//Test overflow access in malloc
void test01() {
	char *str = NULL;
	int i = 0;

	str = (char *)malloc(sizeof(char) * 2);

	str[0] = 'w';
	str[1] = 'e';
	str[2] = 'g';

	for (i = 0; i < 3; ++i) {
		printf("str[%d] = %c\n", i, str[i]);
	}

	free(str);
	str = NULL;
}

//Test combine with "++" and "*"
void test02() {
	char str1[6] = "we go";
	char *str = NULL;
	int i = 0;

	str = (char *)malloc(strlen(str1) + 1);
	
	strcpy_s(str, strlen(str1) + 1, str1);

	printf("str = %s\n", str);

	for (i = 0; i < strlen(str) + 1; ++i) {
		printf("before, str[%d] = %c\n", i, str[i]);
	}

	//while (*str != '\0') {
	//	//printf();
	//	printf("*(str++) = %c\n", *(str++));
	//	getchar();
	//}

	free(str);	
	str = NULL;
}

//test strcpy_s, the size of des is lesser than src
//test malloc
void test03() {
	//char str1[6] = "we go";
	char *str = NULL;
	int i = 0;

	str = (char *)malloc(sizeof(char) * 2);

	str[0] = 'w';
	str[1] = 'e';
	str[2] = 'g';

	//printf("str = %s\n", str);

	for (i = 0; i < 3; ++i) {
		printf("str[%d] = %c\n", i, str[i]);
	}
	
	free(str);
	str = NULL;
}


void test04() {
	


}