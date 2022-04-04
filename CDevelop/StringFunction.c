#include "StringFunction.h"
#include <string.h>

void NorStrcpy(char *str1, const char *str2) {
	//char str1[3];
	//char str2[3] = "we";
	//char *str = NULL;
	//char str3[3];

	//int i = 0;

	//str = (char *)malloc(sizeof(char) * 5);
	//printf("before cpy, sizeof(str) = %d\n", sizeof(str));
	//strcpy_s(str, sizeof(str2), str2);
	//printf("after cpy, sizeof(str) = %d\n", sizeof(str));

	//printf("str = %s\n", str);

	//for (i = 0; i < sizeof(char) * 5; ++i) {
	//	printf("str[%d] = %c\n", i, str[i]);
	//}
	//printf("str2 = %s\n", str2);

	//free(str);

	//printf("hello\n");
	//getchar();
}


 char* MyStrcpy(char *str1, const char *str2) {
	int i = 0;
	
	if (str1 == NULL) {
		return NULL;
	}

	for (i = 0; i < strlen(str2) + 1; ++i) {
		str1[i] = str2[i];
	}
	
	return str1;
}



