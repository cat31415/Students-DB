#ifndef MENU_H
#define MENU_H

struct Menu
{
	char** items;
	int count;
};

Menu initMenu(char** sr);
int runMenu(Menu* menu);
void freeMenu(Menu* menu);

#endif 
