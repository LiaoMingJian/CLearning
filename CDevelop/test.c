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

//test printf with %s
void test04() {
	char str1[3] = "we";
	char str2[2] = {'g', '0'};
	char str3[4] = {'w', 'e'};

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	printf("str3 = %s\n", str3);
}

//test %d, %c
void test05() {
	char ch1 = 'a';
	int a = 65;
	double b = 1.3;
	
	printf("ch1 = %c\n", ch1);
	printf("ch1 = %d\n", ch1);

	printf("a = %d\n", a);
	printf("a = %c\n", a);

	//printf("b = %.2f\n", b);
	//printf("b = %d\n", b);
}

//test %d, %f
void test06() {
	int a = 65;
	double b = 1.3;

	printf("a = %d\n", a);
	printf("a = %.2f\n", a);

	printf("b = %.2f\n", b);
	printf("b = %d\n", b);
}

//test %c, %s
void test07() {
	char ch1 = 'w';
	char str2[3] = "go";

	printf("ch1 = %c\n", ch1);
	printf("str2[0] = %c\n", str2[0]);

	printf("ch1 = %s\n", &ch1);
	printf("str2 = %s\n", str2);
}



