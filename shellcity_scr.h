#ifndef SHELLCITY_SCR_H
#define SHELLCITY_SCR_H

#include<ncurses.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

#include "shellcity_val.h"
#include "shellcity_calc.h"
#include "shellcity_view.h"

int firstSc(int h, int w);
int gameoverSc(int h, int w);
int clearSc(int h, int w);

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

#endif

