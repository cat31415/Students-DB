#ifndef TABLESTUDENT_H
#define TABLESTUDENT_H

#include "student.h"
#include "array.h"
#include "fiodata.h"
#include "indexarr.h"
#pragma warning(disable:4996)

struct FileSystem
{
	FILE* mainStream;
	FILE* maskStream;
	FILE* IndexStream[3];
	const char** names;
};

errno_t startSystem(FileSystem* syst);
long consoletoTabel(FileSystem* syst, int orign = SEEK_END);
void outputTabel(FileSystem* file);
errno_t startMaskArr(FileSystem* syst);
errno_t startIndexes(FileSystem* syst);
void closeSystem(FileSystem* syst);
void addStud(FileSystem* syst, Student* st);
void dellStudent(FileSystem* syst);
int intcmp(int* a, int* b);
int strcmpmy(char** s1, char** s2);
void strcpymy(char* s, const char* s2, int n);

#endif

