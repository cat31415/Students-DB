#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "student.h"
#include "array.h"
#include "fiodata.h"
#include "menu.h"
#include "tabelstudent.h"


void outNameIndex(IndexElem<char*>* elem)
{
    printf("%d %s \n", elem->index, elem->znach);
}

void outIntIndex(IndexElem<int>* elem)
{
    printf("%d %d \n", elem->index, elem->znach);
}

int main()
{
    const char* items[] = {
        "TABEL",
        "Add",
        "Delete",
        "Search",
        "Sort",
        "Exit",
        0
    };

    enum
    {
        TABEL, ADD, DELETE, SEARCH, SORT, EXIT
    };

    Menu m = initMenu((char**)(items));

    const char* filenames[] = {
        "Students.bin",
            "Mask.bin",
            "IndexName.bin",
            "IndexAge.bin",
            "IndexMinMark.bin"
    };

    FileSystem syst = { 0, 0, 0, 0, 0, filenames };
    
    errno_t err = startSystem(&syst);

    if (!err) {
        
        for (int item; (item = runMenu(&m)) != EXIT; )
            switch (item)
            {
            case TABEL:
            {

                printf("TABEL\n");
                outputTabel(&syst);
            }
            break;
            case ADD:
            {
                printf("ADD\n");
                consoletoTabel(&syst);
            }
            break;
            case DELETE:
            {
                printf("DELETE\n");
                fopen_s(syst.IndexStream, "IndexName.bin", "r+b");
                filetoConsole(syst.IndexStream[0], outNameIndex);
            }
            break;
            case SEARCH:
            {
                printf("SEARCH\n");
            }
            break;
            case SORT:
            {
                printf("SORT\n");
            }
            break;
            }
        
        
    }
    closeSystem(&syst);
}

