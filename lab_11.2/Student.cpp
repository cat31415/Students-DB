#include "student.h"

Student inputStudent()
{
	Student stud;
	printf("Write name: ");
	if (!strlen(gets_s(stud.name, Student::Len)))
		gets_s(stud.name, Student::Len);
	printf("Write age: ");
	scanf_s("%d", &stud.age);
	printf("Write sex: ");
	scanf_s(" %c", &stud.sex, (unsigned int)sizeof(stud.sex));
	printf("Write marks: ");
	for(int i = 0; i < Student::Count; scanf_s("%d", stud.marks + i++));
	stud.mask = 1;
	return stud;
}

void outputStudent(Student* stud)
{
	printf("name: %.*s age: %2d sex: %c marks: ", Student::Len, stud->name, stud->age, stud->sex);
	for (int i = 0; i < Student::Count; printf("%d ", stud->marks[i++]));
	printf(" srMark: %4.2lf min mark %d: \n", srMark(stud), minMark(stud));
}

double srMark(Student* stud)
{
	double s = 0;
	for (int i = 0; i < Student::Count; s += stud->marks[i++]);
	return s / Student::Count;
}

int minMark(Student* st)
{
	int min = st->marks[0];
	for (int i = 0; i < Student::Count; i++)
	{
		if (min > st->marks[i])
			min = st->marks[i];
	}
	return min;
}

int cmpAge(Student* st1, Student* st2)
{
	return st1->age - st2->age;
}

int cmpMinMark(Student* st1, Student* st2)
{
	return minMark(st1) - minMark(st2);
}

int cmpName(Student* st1, Student* st2)
{
	return strcmp(st1->name, st2->name);
}

