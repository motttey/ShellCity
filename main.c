#include<ncurses.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

#include "shellcity_val.h"
#include "shellcity_view.h"
#include "shellcity_check.h"
#include "shellcity_scr.h"
#include "shellcity_event.h"
#include "shellcity_calc.h"

int main(void){

  do{
  	int x,y,w,h;
		int key;
		
		//settings		
		initscr();
		cbreak();

		start_color();

		DefineColors();

		getmaxyx(stdscr,h,w);
		firstSc(h,w);
		
		//map 
		Piece P[h][w];


		struct tm *tst;
		time_t timer;

		//initialize
		ResetGlobalVal();

		//initialize map
		int i,j;
		for(i = 0;i < h; i++){
			for(j = 0; j < w; j++){
				P[i][j].type = 0;
				P[i][j].landprice = 0;
				P[i][j].pop = 0;
			}
		}

		x = (w - 30)/2;
		y = (h - 1)/2;
	
		clear();
		noecho();
		timeout(0);
		
		//print frame
		PrintFrame(h,w);

		PrintExp(h,w);

		//PrintArea(h,w,P);
		//make ocean
		MakeOcean(h,w,P);
		//PrintArea(h,w,P);
		for(i = 1;i < h - 1  ; i++){
		for(j = 1; j < w - 30; j++){
			switch(P[i][j].type){
				case 0:
					attron(COLOR_PAIR(8));
					break;
				case 1:
					attron(COLOR_PAIR(1));
					break;
				case 2:
					attron(COLOR_PAIR(2));
					break;
				case 3:
					attron(COLOR_PAIR(3));
					break;
				case 4:
				case 5:
				case 6:
				case 7:
					attron(COLOR_PAIR(5));
					break;
				case 8:
					attron(COLOR_PAIR(10));
					break;
				case 11:
					attron(COLOR_PAIR(1)| A_BLINK);
					break;
				case 12:
					attron(COLOR_PAIR(2)| A_BLINK);
					break;
				case 13:
					attron(COLOR_PAIR(3)| A_BLINK);
					break;
				default:
					break;

			}
			 char str[1];
			 sprintf(str,"%d", P[i][j].type);
			 
			 //draw area
			 if( P[i][j].type == 4){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Police.pict);	
			 }
			 else if(P[i][j].type == 5){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Firehouse.pict);	
			 }
			 else if(P[i][j].type == 6){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Hospital.pict);	
			 }
			 else if(P[i][j].type == 7){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Jail.pict);					
			 }
			 else{
				 mvprintw(i,j," ");
			 }
			 attron(0);
		}
	}

		while(1){
		  	time(&timer);
		  	tst = localtime(&timer);

		if(ReStartflag == 1){
			MakeOcean(h,w,P);
			ReStartflag = 0;
		}

		//if money < 0, quit from shellcity
		if(money < 0){
			GameOverflag = 1;
			break;
		}
		//check game clear conditions
		if(CheckClear(h,w,P) == 1){
			Clearflag = 1;
			break;
		}

		//set cursol (center)
		move(y,x);
		curs_set(1);
		
		key = getch();
		switch(key){
			case 'u'	: y--; break;	//up
			case 'j'	: y++; break;	//down
			case 'h'	: x--; break;	//left
			case 'k'    : x++; break;	//right
			//town
			case 't'	:         
						  CheckArea(y,x,h,w,&P[y][x]);
						  addArea(&Town,&P[y][x]);
						  CheckAdjacent(x, y, h ,w , P);
						  break;
			//shop
			case 's'    :             
						  CheckArea(y,x,h,w,&P[y][x]);
						  addArea(&Shop,&P[y][x]); 
						  CheckAdjacent(x, y, h ,w , P);
						  break;
			//factory
			case 'f'    :             
						  CheckArea(y,x,h,w,&P[y][x]);
						  addArea(&Fact,&P[y][x]);
						  CheckAdjacent(x, y, h ,w , P);
						  break;
			//option window
			case 'o'    : 
						  attrset(0);
						  ViewOption(h,w,x,y);
						  clear();
						  PrintFrame(h,w);
						  PrintExp(h,w);
						  //wrefresh(stdscr);
						  break;

			//delete area
			case 'd'    :             
						  CheckArea(y,x,h,w,&P[y][x]);
						  mvprintw(y,x," ");
						  break;
			//debug mode
			case 'm'    :
						  money += 10000000;
						  break;
			default:break;
		}
		
		//rich area
		if(population >= 500){
			switch(key){
				//town
				case 'T'	:         
							CheckArea(y,x,h,w,&P[y][x]);
							addArea(&Town_High,&P[y][x]);
							CheckAdjacent(x, y, h ,w , P);
							break;
				//shop
				case 'S'    :             
						    CheckArea(y,x,h,w,&P[y][x]);
							addArea(&Shop_High,&P[y][x]); 
							CheckAdjacent(x, y, h ,w , P);
							break;
				//factory
				case 'F'    :             
							CheckArea(y,x,h,w,&P[y][x]);
							addArea(&Fact_High,&P[y][x]);
							CheckAdjacent(x, y, h ,w , P);
				default:break;
			}
		}

		for(i = 1;i < h - 1  ; i++){
		for(j = 1; j < w - 30; j++){
			switch(P[i][j].type){
				case 0:
					attron(COLOR_PAIR(8));
					break;
				case 1:
					attron(COLOR_PAIR(1));
					break;
				case 2:
					attron(COLOR_PAIR(2));
					break;
				case 3:
					attron(COLOR_PAIR(3));
					break;
				case 4:
				case 5:
				case 6:
				case 7:
					attron(COLOR_PAIR(5));
					break;
				case 8:
					attron(COLOR_PAIR(10));
					break;
				case 11:
					attron(COLOR_PAIR(1)| A_BLINK);
					break;
				case 12:
					attron(COLOR_PAIR(2)| A_BLINK);
					break;
				case 13:
					attron(COLOR_PAIR(3)| A_BLINK);
					break;
				default:
					break;

			}
			 char str[1];
			 sprintf(str,"%d", P[i][j].type);
			 
			 //draw area
			 if( P[i][j].type == 4){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Police.pict);	
			 }
			 else if(P[i][j].type == 5){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Firehouse.pict);	
			 }
			 else if(P[i][j].type == 6){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Hospital.pict);	
			 }
			 else if(P[i][j].type == 7){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Jail.pict);					
			 }
			 else{
				 mvprintw(i,j," ");
			 }
			 attron(0);
		}
	}

		//calc and view param
		//once in every three second
		if((tst->tm_sec % 3) == 0){

			//cursol not set
			curs_set(0);

			//reset color
			attrset(0);

			//initializition of temporal value
			int revenue = 0;
			int tmpopulation = 0 ;

			revenue = CalcTmpRev(h, w, revenue, P);
			tmpopulation = CalcTmpPop(h, w, tmpopulation, P);

			revenue = CheckRatioEvent(revenue);
			
			CalcParam(revenue,tmpopulation);
			
			PrintParam(h, w, money, population, revenue);

			usleep(100000);

		}

		CheckPublicFacility(h, w, y, x, population, P);

		//judgement clear

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

	if(Clearflag == 1){
		clear();
		clearSc(h,w);
    }
	
	}while(ReStartflag != 0);

	endwin();
	return 0;
}

void PrintArea(int h, int w, Piece P[][w]){
	
	int i,j;
	for(i = 1;i < h - 1  ; i++){
		for(j = 1; j < w - 30; j++){
			switch(P[i][j].type){
				case 0:
					attron(COLOR_PAIR(8));
					break;
				case 1:
					attron(COLOR_PAIR(1));
					break;
				case 2:
					attron(COLOR_PAIR(2));
					break;
				case 3:
					attron(COLOR_PAIR(3));
					break;
				case 4:
				case 5:
				case 6:
				case 7:
					attron(COLOR_PAIR(5));
					break;
				case 8:
					attron(COLOR_PAIR(10));
					break;
				case 11:
					attron(COLOR_PAIR(1)| A_BLINK);
					break;
				case 12:
					attron(COLOR_PAIR(2)| A_BLINK);
					break;
				case 13:
					attron(COLOR_PAIR(3)| A_BLINK);
					break;
				default:
					break;

			}
			 char str[1];
			 sprintf(str,"%d", P[i][j].type);
			 
			 //draw area
			 if( P[i][j].type == 4){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Police.pict);	
			 }
			 else if(P[i][j].type == 5){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Firehouse.pict);	
			 }
			 else if(P[i][j].type == 6){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Hospital.pict);	
			 }
			 else if(P[i][j].type == 7){
				 attron(COLOR_PAIR(5));
				 mvprintw(i,j,Jail.pict);					
			 }
			 else{
				 mvprintw(i,j," ");
			 }
			 attron(0);
		}
	}
	return;
}

