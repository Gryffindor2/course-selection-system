#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include"consts.h"
#define CRYLEN 10
#define DEBUG
#ifdef DEBUG
char key[10] = { 0 };
#else
char key[10] = { 8,3,22,6,25,19,7,23,6,17 };
#endif // DEBUG

//encryption key. If you want to change, please make sure the value is unprintful character and isn't 0.
//better not being space and wrap
//file and encryption functions

//将str加密后写入fp所指向的文件中
void cfwright(const char* str, FILE* fp)
{
	char s2w[50] = { 0 };
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		s2w[i] = str[i] ^ key[i % CRYLEN];
	fputs(s2w, fp);
	fputs("\n", fp);
}
//从fp所指向的文件中读入一行内容并将解密后的字符串并存入buffer中
void cfread(FILE* fp, char* buffer)
{
	char s2r[50] = { 0 };
	fgets(s2r, 50, fp);
	for (int i = 0; s2r[i] != '\0' && s2r[i] != '\n'; i++)
	{
		buffer[i] = s2r[i] ^ key[i % CRYLEN];
	}
	return;
}
//格式化加密写入fp所指向的文件中，返回成功个数
int fprintfc(FILE* fp, const char* Format, ...)
{
	int Result;
	char buffer[50];
	va_list ArgList;
	va_start(ArgList, Format);
	Result = vsprintf_s(buffer, Format, ArgList);
	va_end(ArgList);
	cfwright(buffer, fp);
	return Result;
}
//从fp所指向的文件中格式化加密读取，返回成功个数
int fscanfc(FILE* fp, const char* Format, ...)
{
	char buffer[50] = { 0 };
	cfread(fp, buffer);
	int Result;
	va_list ArgList;
	va_start(ArgList, Format);
	Result = vsscanf(buffer, Format, ArgList);
	va_end(ArgList);
	return Result;
}
//产生name对应的配置文件名，存入destination中
void generateConfigFile(char* destination, const char* name)
{
	strcat(destination, DATAPATH);
	strcat(destination, name);
	strcat(destination, ".txt");
	return;
}
