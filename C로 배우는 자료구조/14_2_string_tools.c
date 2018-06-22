#include "14_2_string_tools.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// 자기자신의 header 파일도 include해줘야 한다.
char* strdup(const char* s){
    char* p = (char*)malloc(strlen(s)+1);
    if (p) strcpy(p, s);
    return p;
}

int read_line(FILE *fp, char str[], int n){
// main.cpp에서 이 함수를 써야 하니까 헤더에도 선언해준다.
    int ch, i = 0;
    while((ch=fgetc(fp))!='\n' && ch != EOF){
        if (i<n-1){
            str[i++]=ch;
        }
    }
    str[i] = '\0';
    return i;
}