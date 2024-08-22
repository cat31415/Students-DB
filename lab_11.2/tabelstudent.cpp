#include "tabelstudent.h"

errno_t startSystem(FileSystem* syst)
{
    errno_t err = fopen_s(&syst->mainStream, syst->names[0], "r+b");
    err *= fopen_s(&syst->maskStream, syst->names[1], "r+b");
    if (err)
    {
        err = fopen_s(&syst->mainStream, syst->names[0], "w+b");
        err += fopen_s(&syst->maskStream, syst->names[1], "w+b");
        printf("Welcome! Start data base: ");
        consoletoTabel(syst);
    }
    startIndexes(syst);
    return errno_t();
}


long consoletoTabel(FileSystem* syst, int orign)
{
    printf("Write number of students: \n");
    int n = 0;
    scanf_s("%d", &n);
    Student st;

    for (int i = 0; i < n; i++)
    {
        st = inputStudent();
        addStud(syst, &st);
    }
    fflush(syst->mainStream);
    fflush(syst->maskStream);
    return flengthData<Student>(syst->mainStream);
}

errno_t startMaskArr(FileSystem* syst)
{
    errno_t err = fopen_s(&syst->maskStream, syst->names[1], "r+b");
    if (err)
    {
        err = fopen_s(&syst->maskStream, syst->names[1], "w+b");
        if (!err) {
            Student st = { 0, 0, 0, 0 };
            fseek(syst->mainStream, 0, SEEK_SET);
            for (; freadData(&st, 0, syst->mainStream, SEEK_CUR); fwriteData(&st.mask, 0, syst->maskStream, SEEK_CUR));
        }
    }
    fflush(syst->maskStream);
    return err;
}

errno_t startIndexes(FileSystem* syst)
{
    errno_t err = 0;
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        err += fopen_s(syst->IndexStream + i, syst->names[2 + (i)], "r+b");
        if (err)
        {
            err = fopen_s(syst->IndexStream + i, syst->names[2 + (i)], "w+b");
            flag = 1;
        }
    }
    if (flag) {
        int mask = 0;
        Student st = { 0, 0, 0, 0 };
        char* name = st.name;
        int min_mark = minMark(&st);
        for (int i = 0; freadData(&mask, i, syst->maskStream); i++)
        {
            if (mask)
            {
                freadData(&st, i, syst->mainStream);
                int min_mark = minMark(&st);
                IndexElem<char[30]> name;
                name.index = i;
                strcpy(name.znach, st.name);
                addElemInIndexArr(&name, syst->IndexStream[0], strcmpmy);
                addInIndex(syst->IndexStream[1], st.age, i, intcmp);
                addInIndex(syst->IndexStream[2], min_mark, i, intcmp);
            }
        }
    }
    for (int i = 0; i < 3; fclose(syst->IndexStream[i++]));
    return err;
}

void closeSystem(FileSystem* syst)
{
    fclose(syst->mainStream);
    fclose(syst->maskStream);
    for (int i = 0; i < 3; fclose(syst->IndexStream[i++]));    
}

void addStud(FileSystem* syst, Student* st)
{
    int n = flengthData<Student>(syst->mainStream);
    fwriteData(st, 0, syst->mainStream, SEEK_END);
    fwriteData(&st->mask, 0, syst->maskStream, SEEK_END);
    errno_t err;
    for (int i = 0; i < 3; i++)
    {
        err = fopen_s(syst->IndexStream + i, syst->names[2 + (i)], "r+b");
        if (err)
            err = fopen_s(syst->IndexStream + i, syst->names[2 + (i)], "w+b");
    }
    if (st->mask) {
        int min_mark = minMark(st);
        addInIndex(syst->IndexStream[0], st->name, n, strcmpmy);
        addInIndex(syst->IndexStream[1], st->age, n, intcmp);
        addInIndex(syst->IndexStream[2], min_mark, n, intcmp);
    }
    for (int i = 0; i < 3; fclose(syst->IndexStream[i++]));
}

void dellStudent(FileSystem* syst)
{

}

void outputTabel(FileSystem* syst)
{
    int mask = 0;
    Student st = { 0, 0, 0, 0 };
    for (int i = 0; freadData(&mask, i, syst->maskStream); i++)
    {
        if (mask)
        {
            freadData(&st, i, syst->mainStream);
            outputStudent(&st);
        }
    }
}

int strcmpmy(char** s1, char** s2)
{
    return strcmp(*s1, *s2);
}

int intcmp(int* a, int* b)
{
    return *a - *b;
}

void strcpymy(char* s, const char* s2, int n)
{
    s = new char[n];
    strcpy(s, s2);
}