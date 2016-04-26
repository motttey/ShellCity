#include "shellcity_scr.h"

int firstSc(int h ,int w)
{
	int k;
	start_color();
	attrset(COLOR_PAIR(5));
	box(stdscr, ' ' , ' ');
	printLogo(10,3,Logo);

	wrefresh(stdscr);
	curs_set(0);
	
	//wait start
	while(1){

		k = getch();
		if(k == 's'){
			return 0;
		}
	}
}
int gameoverSc(int h ,int w){

	int key;
	attrset(COLOR_PAIR(5));
	box(stdscr, ' ' , ' ');
	printLogo(10,3,GameOver);
	wrefresh(stdscr);
	curs_set(0);

	//wait until mode choiced
	while(1){
			key = getch();
		if(key == 'r'){
			clear();
			ResetGlobalVal();
			ReStartflag = 1;
			return 0;
		}else if(key == 'q'){
		   	clear();
			ResetGlobalVal();
			return 0;
		
		}
		
	}
}

int clearSc(int h, int w){
	int key;
	start_color();
	attrset(COLOR_PAIR(5));
	box(stdscr, ' ' , ' ');
	printLogo(10,3,Clear);
	wrefresh(stdscr);
	curs_set(0);
	while(1){
			key = getch();
		if(key == 'r'){
			clear();
			ResetGlobalVal();
			ReStartflag = 1;
			return 0;
		}else if(key == 'q'){
		   	clear();
			ResetGlobalVal();
			return 0;
		
		}
		
	}
}
