#pragma once
// 중복방지를 위해 쓰는 명령어라고 함.
#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int read_line(FILE *fp, char str[], int n);
char* strdup(const char* s);

#endif