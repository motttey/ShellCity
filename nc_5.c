#include<ncurses.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include "shellcity.h"

int main(void){

  do{
  	int x,y,w,h;
		int key;
		
		
		initscr();
		cbreak();

		start_color();

		init_pair(1,COLOR_BLACK,COLOR_GREEN);
		init_pair(2,COLOR_BLACK,COLOR_BLUE);
		init_pair(3,COLOR_BLACK,COLOR_YELLOW);
		init_pair(4,COLOR_WHITE,COLOR_BLACK);
		init_pair(5,COLOR_BLACK,COLOR_WHITE);
		init_pair(6,COLOR_RED,COLOR_RED);
		init_pair(7,COLOR_YELLOW,COLOR_YELLOW);
		init_pair(8,COLOR_BLACK,COLOR_BLACK);
		init_pair(9,COLOR_WHITE,COLOR_WHITE);
		init_pair(10,COLOR_BLACK,COLOR_CYAN);

		getmaxyx(stdscr,h,w);
		firstSc(h,w);
		
		Piece P[h][w];

		struct tm *tst;
		time_t timer;

		ReStartflag = 0;

		money = 2000;
		population = 0;

		int TypeArea[h][w];
		int i,j;
		for(i = 0;i < h; i++){
			for(j = 0; j < w; j++){
				TypeArea[i][j] = 0;
				P[i][j].type = 0;
				P[i][j].landprice = 0;
				P[i][j].pop = 0;
			}
		}


		x = w/2;
		y = h/2;
	
		clear();
		noecho();
		timeout(0);
		//WINDOW *frame; 
		//frame = subwin(stdscr,h,w,0,0);
		attron(COLOR_PAIR(5));
		box(stdscr, ' ' , ' ');
		refresh();
		for(i = 0; i < h-1; i++){
		 mvwprintw(stdscr,i,w-30," ");
		}
		attrset(0);
		
		char printPop[30];
		char printRevenue[30];
		char printBudget[30];
		char printTownCount[10];
		char printShopCount[10];
		char printFactCount[10];

		move(h-2,w-strlen(firstMessage)-1);
	  addstr(firstMessage);
	  mvwprintw(stdscr,4,w-28,"Shift + T: Build Town   ");
	  mvwprintw(stdscr,6,w-28,"Shift + S: Build Shop   ");
	  mvwprintw(stdscr,8,w-28,"Shift + F: Build Factory");
	  mvwprintw(stdscr,10,w-28,"Shift + P: Build Public");
	  mvwprintw(stdscr,12,w-28,"q: quit from ShellCity");
	  refresh();

	//maybe use subwin? 

	//WINDOW *subwin_p;
	//subwin_p = subwin(stdscr,h , 30, 0, w-30);
	//draw line	

		MakeOcean(h,w,P);

		while(1){
		  	time(&timer);
		  	tst = localtime(&timer);
		if(ReStartflag == 1){
			MakeOcean(h,w,P);
			ReStartflag = 0;
		}
		usleep(100000);

		if(money < 0){
			GameOverflag = 1;
			break;
		}

		move(y,x);
		curs_set(1);
		
		key = getch();
		switch(key){
			case 'h'	: y--; break;
			case 'j'	: y++; break;
			case 'k'	: x--; break;
			case 'l'	: x++; break;
			case 't'	:         
							CheckArea(y,x,h,w,&P[y][x]);
						  addArea(&Town,&P[y][x]);
						  money = money - Town.cost;
						  P[y][x].type = 1;
						  mvprintw(y,x," ");
						  CheckAdjacent(x, y, h ,w , P);
						  break;
			case 's'    :             
						  CheckArea(y,x,h,w,&P[y][x]);
						  addArea(&Shop,&P[y][x]); 
						  money = money - Shop.cost;
						  P[y][x].type = 2;
						  mvprintw(y,x," ");
						  CheckAdjacent(x, y, h ,w , P);
						  break;
			case 'f'    :             
							CheckArea(y,x,h,w,&P[y][x]);
						  addArea(&Fact,&P[y][x]);
						  money = money - Fact.cost;
						  P[y][x].type = 3;
						  mvprintw(y,x," ");
						  CheckAdjacent(x, y, h ,w , P);
						  break;
			case 'd'    :             
							CheckArea(y,x,h,w,&P[y][x]);
						  mvprintw(y,x," ");

						  break;
			default:break;
		   //public_facility's TypeArea:4
		}
		
		if(population >= 500){
			switch(key){
				case 'T'	:         
							CheckArea(y,x,h,w,&P[y][x]);
							addArea(&Town_High,&P[y][x]);
							money = money - Town_High.cost;
							P[y][x].type = 11;
							mvprintw(y,x," ");
							CheckAdjacent(x, y, h ,w , P);
							break;
				case 'S'    :             
						    CheckArea(y,x,h,w,&P[y][x]);
							addArea(&Shop_High,&P[y][x]); 
							money = money - Shop_High.cost;
							P[y][x].type = 12;
							mvprintw(y,x," ");
							CheckAdjacent(x, y, h ,w , P);
							break;
				case 'F'    :             
							CheckArea(y,x,h,w,&P[y][x]);
							addArea(&Fact_High,&P[y][x]);
							money = money - Fact_High.cost;
							P[y][x].type = 13;
							mvprintw(y,x," ");
							CheckAdjacent(x, y, h ,w , P);
				default:break;
		   //public_facility's TypeArea:4
			}
		}

		if((tst->tm_sec % 3) == 0){
			//clear();
			//char *pT;
		  curs_set(0);
			attron(COLOR_PAIR(4));

			int revenue = 0;
			int tmpopulation = 0 ;

			//money += Town.revenue + Shop.revenue + Fact.revenue ;
			for(i = 1;i < h - 1; i++){
				for(j = 1; j < w - 30; j++){
					if( 1 <=  P[i][j].type <= 3 || 11 <= P[i][j].type <= 13 ){
						revenue += P[i][j].landprice;
						tmpopulation += P[i][j].pop;
					}
				}
			}
			revenue = CheckRatioEvent(revenue);
			money += revenue;
			money += (Police.flag * (-1) * Police.expense + Firehouse.flag * (-1) * Firehouse.expense 
				+ Hospital.flag * (-1) * Hospital.expense + Jail.flag * (-1) * Jail.expense)  ;
			population = tmpopulation;

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
				sprintf(printBudget,"     Budget:%d",money);
			}else if(money <= 100){
			    sprintf(printBudget,"    Budget:%d",money);
			}else if(money <= 1000){
				sprintf(printBudget,"   Budget:%d",money);
			}else if(money <= 10000){
				sprintf(printBudget,"  Budget:%d",money);
			}else if(money <= 100000){
				sprintf(printBudget," Budget:%d",money);
			}
			//sprintf(printRevenue,"Revenue:%d     ",revenue);
			//sprintf(printBudget,"Budget:%d, Revenue:%d",money,revenue);
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

		
		//Police 
		if(population >= 50){
			if(Police.flag == 0){
				PublicFacilityEvent(&Police, PoliceMessage, x, y, h, w, &P[y][x]);
			}
		}

		//firehouse
		if(population >= 100){
			if(Firehouse.flag == 0){
				PublicFacilityEvent(&Firehouse, FirehouseMessage, x, y, h, w, &P[y][x]);
			}
		}
		
		//hospital
		if(population >= 200){
			if(Hospital.flag == 0){
				PublicFacilityEvent(&Hospital, HospitalMessage, x, y, h, w, &P[y][x]);
			}
		}
		//jail
		if(population >= 500){
			if(Jail.flag == 0){
				PublicFacilityEvent(&Jail, JailMessage, x, y, h, w, &P[y][x]);
			}
		}
		//	

		//adjust cursol
		if(x >= w - 30){
			x = 2;
		}else if (x < 1){
			x = w - 30;
		}

		if(y >= h - 1){
			y = 1 ;
		}else if (y < 1){
			y =  h - 2;
		}
		if(key == 'q' ){
			GameOverflag = 0;
			break;
		}
		//usleep(100000);
		//clear();
	}

	if(GameOverflag == 1){
		clear();
		gameoverSc(h,w);
	}

	if(CheckClear(h,w,P) != 0){
		clear();
		clearSc(h,w);
	}
	
	}while(ReStartflag != 0);

	endwin();
	return 0;
}



