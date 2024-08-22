#include "menu.h"
#include <stdio.h>
Menu initMenu(char** st)
{
    int count;
    for (count = 0; st[count]; count++);

    Menu m = { new char* [count], count };
    for (int i = 0; i < count; m.items[i] = st[i++]);
    return m;
}

int runMenu(Menu* mn)
{
    for (int i = 0; i < mn->count; i++)
        printf("%2d. %s\n", i + 1, mn->items[i]);
    int item;
    printf("> ");
    scanf_s("%d", &item);
    return item - 1;
}

void freeMenu(Menu* menu)
{
    delete[] menu->items;
    menu->count = 0;
}
