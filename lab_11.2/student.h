#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>

struct Student
{
	
	const static int Len = 30;
	char name[Len];
	char sex;
	int age;
	const static int Count = 3;
	int marks[Count];
	int mask;
};

Student inputStudent();
void outputStudent(Student* stud);
double srMark(Student* stud);
int minMark(Student* st);
int cmpName(Student* st1, Student* st2);
int cmpAge(Student* st1, Student* st2);
int cmpMinMark(Student* st1, Student* st2);

#endif
