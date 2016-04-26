#ifndef SHELLCITY_VIEW_H
#define SHELLCITY_VIEW_H

#include<ncurses.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include "shellcity_val.h"

void printLogo(int y, int x,char *AA[]);
void printAA(char *str[], int y,int x);
void printMessage(int y, int x, char *str);
void MakeOcean(int h, int w, Piece P[][w]);
void PrintFrame(int h, int w);
void PrintParam(int h, int w,int money,int population,int revenue);
void PrintExp(int h, int w);
void ViewOption(int h,int w,int x,int y);
void PrintArea(int h, int w, Piece P[][w]);

void printAA(char *str[], int y, int x){
  row = LINES - SIZE_ROW - y;
  col = COLS  - SIZE_COL - x;
  int i;
  for(i = 0; i < SIZE_ROW; i++){
    mvaddstr(row + i, col, str[i]);
  }
}

void printLogo(int y, int x,char *AA[]){
  row = LINES - LOGO_SIZE_ROW - y;
  col = COLS  - LOGO_SIZE_COL - x;
  int i;
  int j;
  char *str;
  timeout(0);
  for(i = 0; i < LOGO_SIZE_ROW- 2 ; i++){
	  str = AA[i];
	  //wait(10000);
	  for(j=0; j < strlen(str); j++){
		 if(str[j] == ':'){
		   attron(COLOR_PAIR(9)| A_BLINK);
		 }else if(str[j] == '#'){
		   attron(COLOR_PAIR(6)| A_BLINK);
		 }else if(str[j] == '$'){
		   attron(COLOR_PAIR(7)| A_BLINK);
		 }else{
		   attron(COLOR_PAIR(8));
		 }
		 mvaddch(row + i, col + j, str[j]);
		 attrset(0);
	  }
	  //sleep(100000);
  }
	  //print message
	  mvaddstr(row + LOGO_SIZE_ROW-2, col, AA[LOGO_SIZE_ROW-2]);
      mvaddstr(row + LOGO_SIZE_ROW-1, col, AA[LOGO_SIZE_ROW-1]);
      //mvaddstr(row + LOGO_SIZE_ROW, col, AA[LOGO_SIZE_ROW]);
	return;

}

void MakeOcean(int h, int w, Piece P[][w]){
	    double tmp1, tmp2;
		int rand1, rand2, moderand;
		int i,j;
		tmp1 = 0,0;
		tmp2 = 1000,0;
		srand((unsigned)time(NULL));
		moderand = rand()% 5 + 1; 
		rand1 = rand() % 100 + 1;
		rand2 = rand() % 3  + 1; 
		//attrset(COLOR_PAIR(10));
		//ocean type(randam)
		switch(moderand){
		//none
		case 1:
			break;
		//common beach
		case 2:
					for(i = 1;i < h - 1; i++){
			tmp2 += 25;
			for(j = 1; j < w - 30; j++){
				//usleep(10);
				srand((tmp1 * rand1) * j/i + (rand2 *  i)/j);
				tmp1 = ((rand() % 10) + i) * 0.05;
				if((tmp1 * tmp2) >= 2000){
					P[i][j].type = 8;
				    //mvprintw(i,j," ");
				}
			}
		}
			break;
		//curb beach
		case 3:
			for(i = 1;i < h - 1; i++){
				tmp2 += 25;
				for(j = 1; j < w - 30; j++){
					//usleep(10);
					srand((tmp1 * rand1) * j/i + (rand2 *  i)/j);
					tmp1 = ((rand() % 10) + j) * 0.05;
					if((tmp1 * tmp2) >= 2000){
						P[i][j].type = 8;
					    //mvprintw(i,j," ");
					}
				}
			}
			break;
		//inverted beach
		case 4:
			for(i = h - 2; i >= 1; i -= 1){
				tmp2 += 25;
				for(j = 1; j < w - 30; j++){
				//usleep(10);
					srand((tmp1 * rand1) * j/i + (rand2 *  i)/j);
					tmp1 = ((rand() % 10) + h-i) * 0.05;
					if((tmp1 * tmp2) >= 2000){
						P[i][j].type = 8;
						//mvprintw(i,j," ");
					}
				}
			}
			break;
		//river
		case 5:
			for(i = 1;i < h - 1; i++){
				//tmp2 += 25;
				for(j = 1; j < w - 30; j++){
					//usleep(10);
					srand((tmp1 * rand1) * j/i + (rand2 *  i)/j);
					if(j <= (w-30)/2) tmp1 = ((rand() % 10) + j) * 0.05;
					if(j > (w-30)/2 ) tmp1 = ((rand() % 10) + w -30  - j) * 0.05;
					if((tmp1 * tmp2) >= 2000){
						P[i][j].type = 8;
						//mvprintw(i,j," ");
					}
				}
			}
			break;
		default:break;

		
		}
		return;
}
void PrintExp(int h, int w){
	
	move(h-2,w-strlen(firstMessage)-1);
	addstr(firstMessage);
	mvwprintw(stdscr,4,w-28,"T: Build Town   ");
	mvwprintw(stdscr,6,w-28,"S: Build Shop   ");
	mvwprintw(stdscr,8,w-28,"F: Build Factory");
	mvwprintw(stdscr,10,w-28,"Shift + P: Build Public");
	mvwprintw(stdscr,12,w-28,"q: Quit from ShellCity");
	mvwprintw(stdscr,14,w-28,"o: View Option");
	refresh();

}

void PrintParam(int h, int w,int money,int population,int revenue){

	char printPop[30];
	char printRevenue[30];
	char printBudget[30];
	char printTownCount[10];
	char printShopCount[10];
	char printFactCount[10];
	
	if(population <= 10  ){
		sprintf(printPop,"     Population:%d",population); 
	}else if(population <= 100){
		sprintf(printPop,"    Population:%d",population); 
	}else if(population <= 1000){
		sprintf(printPop,"   Population:%d",population); 
	}else if(population <= 10000){
		sprintf(printPop,"  Population:%d",population); 
	}
	
	if(revenue <= 10  ){
		sprintf(printRevenue,"     Revenue:%d",revenue); 
	}else if(revenue <= 100){
		sprintf(printRevenue,"    Revenue:%d",revenue);
	}else if(revenue <= 1000){
		sprintf(printRevenue,"   Revenue:%d",revenue);
	}else if(revenue <= 10000){
		sprintf(printRevenue,"  Revenue:%d",revenue);
	}
	
	if(money <= 10  ){
		sprintf(printBudget,"       Budget:%d",money);
	}else if(money <= 100){
	    sprintf(printBudget,"      Budget:%d",money);
	}else if(money <= 1000){
		sprintf(printBudget,"     Budget:%d",money);
	}else if(money <= 10000){
		sprintf(printBudget,"    Budget:%d",money);
	}else if(money <= 100000){
		sprintf(printBudget,"   Budget:%d",money);
	}else if(money <= 1000000){
		sprintf(printBudget,"  Budget:%d",money);
	}else if(money <= 10000000){
		sprintf(printBudget," Budget:%d",money);
	}else if(money <= 100000000){
		sprintf(printBudget,"Budget:%d",money);
	}

	sprintf(printTownCount,"Town:%d",Town.count);
	sprintf(printShopCount,"Shop:%d",Shop.count);
	sprintf(printFactCount,"Fact:%d",Fact.count);
	mvwprintw(stdscr,h-6,w-strlen(printPop)-1,printPop);
	mvwprintw(stdscr,h-5,w-strlen(printRevenue)-1,printRevenue);
    mvwprintw(stdscr,h-4,w-strlen(printBudget)-1,printBudget);
	move(h-2,w-strlen(firstMessage)-1);
	addstr(firstMessage);
	mvwprintw(stdscr,h-12,w-strlen(printTownCount)-1,printTownCount);
	mvwprintw(stdscr,h-11,w-strlen(printShopCount)-1,printShopCount);	
	mvwprintw(stdscr,h-10,w-strlen(printFactCount)-1,printFactCount);		
	       	       
	refresh();

}

void PrintFrame(int h, int w){
		int i;
		attron(COLOR_PAIR(5));
		box(stdscr, ' ' , ' ');
		refresh();
		for(i = 0; i < h-1; i++){
		 mvwprintw(stdscr,i,w-30," ");
		}
		attrset(0);
}

void ViewOption(int h,int w,int x,int y){
	int key;
	int i,j;

	WINDOW *optionwin = subwin(stdscr,h-2,w-2,1,1);

	i = 2;
	j = 2;

	clear();

	//start_color();
	//DefineColors();
	
	//attrset(0);

	FILE *fp;
	char str[256];
	fp = fopen("option.txt","r");
	if(fp == NULL){
		mvwprintw(optionwin, i ,j ,"option.txt not found");
	}

	while(fgets(str, 256, fp) != NULL ){
		mvwprintw(optionwin, i, j, str);
		i++;

	}

	fclose(fp);

	attron(COLOR_PAIR(10));
	box(optionwin, '|' , '-');
	//printLogo(10,3,Logo);

	wrefresh(optionwin);
	curs_set(0);
	
	//wait start
	while(1){

		key = getch();
		if(key == 'q'){
			//werase(optionwin);
			wrefresh(optionwin);
			delwin(optionwin);
			return ;
		}
	}

 }



#endif

