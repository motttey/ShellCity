#include<ncurses.h>
#include<string.h>
//#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

int money ;
int population ;
int CheckTandFratioFlag;
int CheckTandSratioFlag;

#define SIZE_ROW 16
#define SIZE_COL 50
#define LOGO_SIZE_ROW 13
#define LOGO_SIZE_COL 90


typedef struct area{
	int type;
	int pop;
	int count;
	int landprice;
	int revenue;
	int cost;
}Area;

typedef struct pub_fac{
	int type;
  int expense;
	char *pict;
	int flag;
}Pub_fac;

typedef struct piece{
	int type;
	int landprice;
	int pop;
}Piece;

	Area Town = {1,  4, 0, 2, 0, 300};
	Area Shop = {2,  6, 0, 4, 0, 500};
	Area Fact = {3,  5, 0, 3, 0, 400}; 
	//if pop >= 500
	Area Town_High = {11, 10, 0, 10 , 0,1000};
	Area Shop_High = {12, 30, 0, 15 , 0,1500};
	Area Fact_High = {13, 25, 0, 12 , 0,1300};

	Pub_fac Police    = {1,20 ,"P",0};
	Pub_fac Firehouse = {2,50 ,"F",0};
	Pub_fac Hospital  = {3,100 ,"H",0};
	Pub_fac Jail      = {4,150 ,"J",0};
	

/*
typedef struct prop{
	int type;
}Prop;
*/
void printLogo(int y, int x,char *AA[]);
void printAA(char *str[], int y,int x);
void printMessage(int y, int x, char *str);
int firstSc(int h, int w);
int gameoverSc(int h, int w);
void addArea(Area *A, Piece *P);
void delArea(Area *A, Piece *P);
void add_public_facility(Pub_fac *P);
void del_public_facility(Pub_fac *P);
void CheckArea(int y,int x,int h, int w,Piece *P);
void PublicFacilityEvent(Pub_fac *P, char *Message,int x,int y, int h,int w,Piece *Piece);
void ResetGlobalVal(void);
void CheckAdjacent(int x, int y, int h, int w, Piece P[][w]);
int CheckRatioEvent(int revenue);
void MakeOcean(int h, int w, Piece P[][w]);
int CheckClear(int h, int w, Piece P[][w]);
int clearSc(int h, int w);
/*
char *LogoAA[] = {
	"      ##### #  # #### #    #                   ",
	"      #     #  # #    #    #                   ",
	"      ##### #### #### #    #	                ",
	"          # #  # #    #    #                   ",
	"      ##### #  # #### #### ####                ",
	"                                               ",
	"        ######## ###### ######## ##     ##     ",
	"        ######## ###### ######## ##     ##     ",
	"        ##         ##      ##     ##   ##      ",
	"        ##         ##      ##      #####       ",
	"        ##         ##      ##       ###        ",
	"        ##         ##      ##       ###        ",
	"        ######## ######    ##       ###        ",
	"        ######## ######   ####      ###        ",
    "                                               ",
	"                        Press 's' To Start     "
};
*/
char *GameOverAA[] = {
    "                                               ",
	"                                               ",
	"     ######   ##   ## ##  #####                ",
	"     ##      ## # ## ## # ##                   ",
	"     ##  ### #### ## ## # #####                ",
	"     ##   # ##  # ## ## # ##                   ",
	"     ###### ##  # ## ## # #####                ",
	"                                               ",
	"        ###### #     # ###### #####            ",
	"        #    # #     # #      #    #           ",
	"        #    #  #   #  ###### #####            ",
	"        #    #   # #   #      #  #             ",
	"        ######    #    ###### #   ##           ",
	"                                               ",
    "                        Press 'r' To Retry     ",
	"                              'q' To  Quit     "
};


char *Logo[] = {

  "     #:::::$#:::$ #:::$#::::::$$#:::#   #:::$#    ##:::::::$##$:::#$::::::::#::::#$::::#   ", 
  "    #::::::$#:::$ #:::$#::::::$$#:::$#  #:::$#   #$::::::::$##$:::#$::::::::#$:::#$:::#    ",  
  "    #:::$$$ #:::$##:::$#:::$#####:::$#  #:::$#  #$$:::::$$$###$:::###$$:::###$$::::::#     ",  
  "    #::::$# #:::$##:::$#:::$## ##:::$#  #:::$#  $$:::::$## ###$:::####$:::# #$$:::::#      ",  
  "    #:::::$##:::$##:::$#:::$$####:::$#  #:::$#  $$::::$     ##$:::# ##$:::#  #$$:::#       ",  
  "     #:::::$#:::::::::$#:::::::$#:::$#  #:::$#  #$::::#   ####$:::# ##$:::#  ##$:::#       ",  
  "   ####:::::#:::::::::$#:::::::$#:::$#  #:::$#  #$::::#   #::#$:::# ##$:::#  ##$:::#       ",  
  "   #::###:::#:::$##:::$#:::$$$$$#:::$#  #:::$#  #$::::$###:::##:::# ##$:::#  ##$:::#       ",  
  "   #::::::::#:::$##:::$#:::$$  ##:::$####:::$#####$::::::::::##:::# ##$:::#  ##$:::#       ",  
  "   #:::::::$#:::$##:::$#:::$$####::::::##::::::$##$:::::::::###:::# ###:::#  ###:::#       ",  
  "    #$::::$##:::$##:::$#:::::::##::::::##::::::$# #$$:::::#####:::# ###:::#  ###:::#       ", 
  "                                                                                           ",
  "                                                              Press 's' To Start           "                                                                                         
};

char *GameOver[] = {
  "   #::::::#  #:::#   #:::       :::#::::::#$ ##::::::::##$:::#$  #:::#::::::##:::::::::#   ", 
  "  #:::::::# #::#::#  #:::#     #:::#::::::#$#$::::::::::#$:::#$  #:::#::::::##:::::::::::# ",  
  "  #:::###$$ #:#$#:#  #::::#   #::::#:::#####$$::::###::::#:::#$ #:::#:::######:::######::# ",  
  " #:::#$$$  #::#$#::# #::::#   #::::#:::#$  #$::::#$$##:::#:::#$ #:::#:::#$   #:::#$$  #::# ",  
  " #:::#######::###::# #:::::###:::::#:::#####$::::#$$ #:::#:::#$#:::##:::######:::#####::#  ",  
  " #:::#::::#:::::::::$#:::::::::::::#:::::::#$::::#$  #:::#:::#$#:::##:::::::##:::::::::#   ",  
  " #:::#::::#:::::::::$#:::::::::::::#:::::::#$::::#$  #:::#:::##:::#$#:::::::##:::###:::#   ",  
  " #:::###::#:::###:::$#::::#:::#::::#:::#####$::::$###:::##:::#:::#$ #:::######:::#$$#:::#  ",  
  " #::::::::#:::#$#:::$#:::#$#:#$#:::#:::#$$$##$::::::::::##:::::::#$ #:::#$$$##:::#$ $#:::# ",  
  " #:::::::$#:::#$#:::$#:::#$$#$ #:::#:::::::$#$:::::::::#$#:::::##$  #:::::::##:::#$  #:::# ",  
  "  #$::::$##:::# #:::$#:::#$    #:::#:::::::$##$$:::::##$  #:::#$$   #:::::::##:::#$   #:::#",     
  "                                                                    Press 'r' To Retry     ",
  "                                                                          'q' To  Quit     "
};

int row;
int col;
int GameOverflag;
int ReStartflag;
		
	char *firstMessage     = "This is Shell City  ";
	char *PoliceMessage    = "Locate The Police   ";
	char *FirehouseMessage = "Locate the Firehouse";
  char *HospitalMessage  = "Locate tha Hospital ";
	char *JailMessage      = "Locate the Jail     ";

void CheckArea(int y,int x,int h,int w, Piece *P){
  switch(P->type){
  case 1:
        P->type = 0;
        delArea(&Town, P);
		break;
  case 2:
        P->type = 0;
        delArea(&Shop, P);
		break;
  case 3:
        P->type = 0;
        delArea(&Fact, P);
		break;
  case 4:
        P->type = 0;
        del_public_facility(&Police);
		break;
  case 5:
        P->type = 0;
        del_public_facility(&Firehouse);
		break;
  case 6:
        P->type = 0;
        del_public_facility(&Hospital);
		break;
  case 7:
        P->type = 0;
        del_public_facility(&Jail);
		break;
  case 11:
	    P->type = 0;
		delArea(&Town_High, P);
	    break;
  case 12:
	  	P->type = 0;
		delArea(&Shop_High, P);
	    break;
  case 13:
	  	P->type = 0;
		delArea(&Fact_High, P);
	    break;
  case 8:
  default:break;
  }
}
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
  		mvaddstr(row + LOGO_SIZE_ROW-1, col, AA[LOGO_SIZE_ROW-2]);
  		mvaddstr(row + LOGO_SIZE_ROW, col, AA[LOGO_SIZE_ROW-1]);
  /*
  for(i = 0; i < LOGO_SIZE_ROW; i++){
    mvaddch(row + i, col,LogoWhite[i]);
  }
  */
}

void PublicFacilityEvent(Pub_fac *P, char *Message,int x,int y, int h,int w,Piece *Piece){
		move(h-2,w-strlen(Message)-1);
		addstr(Message);
		while(P->flag == 0){
			move(y,x);
		        curs_set(1);
			int key;
			key = getch();
			switch(key){
				case 'u'	: y--; break;	//up
				case 'j'	: y++; break;	//down
				case 'h'	: x--; break;	//left
				case 'k'  : x++; break;	//right
				case  'P':
					CheckArea(y,x,h,w,Piece);
					add_public_facility(P);
					Piece->type = 5;
				//flag = 1;
					mvprintw(y,x,P->pict);
 					break;
			//refresh();
				default:break;
			}
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
		}
}

void addArea(Area *A, Piece *P){
	A->count++;
	srand((unsigned)time(NULL));
	P->pop = rand()%(A->pop + (A->pop - 3)) + A->pop - 2;
	P->landprice = rand()%A->landprice + A->landprice - 3;
	//A->revenue += P->landprice;
	//money -= rand()%(A->pop + 2) + 3;
	switch(A->type){
		case 1: attron(COLOR_PAIR(1));
			    //money -= 300;
			  break;
		case 2: attron(COLOR_PAIR(2));
			    //money -= 500;
				break;
		case 3: attron(COLOR_PAIR(3));
			    //money -= 400;
				break;
		case 11: attron(COLOR_PAIR(1)| A_BLINK);
				 break;
		case 12: attron(COLOR_PAIR(2)| A_BLINK);
				 break;
		case 13: attron(COLOR_PAIR(3)| A_BLINK);
				 break;
	}
}

void add_public_facility(Pub_fac *P){
	//P->count++;
	attron(COLOR_PAIR(5));
	P->flag = 1;
}

void delArea(Area *A, Piece *P){
  	A->count--;
  	A->revenue -= P->landprice;
	switch(A->type){
		case 1: //delch();
					P->pop = 0;
					P->landprice = 0;
			    break;
		case 2: //delch();
					P->pop = 0;
					P->landprice = 0;
				break;
		case 3: //delch();
					P->pop = 0;
					P->landprice = 0;
				break;
	}
	//refresh();
}

void del_public_facility(Pub_fac *P){
	//P->count++;
	P->flag = 0;
}

int firstSc(int h ,int w)
{
	int k;
	attrset(COLOR_PAIR(5));
	box(stdscr, ' ' , ' ');
	//move(h/2,w/2);
	printLogo(10,3,Logo);
	wrefresh(stdscr);
	curs_set(0);
	//refresh(stdscr);
	while(1){
	k = getch();
	if(k == 's'){
		//endwin();
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
	//printMessage(h,w,gameoverMessage);
	///while(1){
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

void ResetGlobalVal(){
	money = 2000;
	population = 0;
	Town.revenue = 0;
	Shop.revenue = 0;
	Fact.revenue = 0;
	Town.count = 0;
	Shop.count = 0;
 	Fact.count = 0;
	Town_High.count = 0;
	Shop_High.count = 0;
 	Fact_High.count = 0;
	Police.flag = 0;
	Firehouse.flag = 0;
	Hospital.flag = 0;
	Jail.flag = 0;
	return;
}

void CheckAdjacent(int x, int y, int h, int w, Piece P[][w]){
	int i,j;
		for(i = 1;i < h - 1; i++){
			for(j = 1; j < w - 30; j++){
				if(P[i][j].type == 1){
					if(P[i][j - 1].type == 2 || P[i][j + 1].type == 2 || P[i - 1][j].type == 2 || P[i + 1][j].type  == 2 ){
						//mvprintw(y,x,"a");
						P[i][j].landprice++;
					}
					if(P[1][j - 1].type == 8 || P[i][j + 1].type == 8 || P[i - 1][j].type == 8 || P[i + 1][j].type  == 9 ){
						P[i][j].landprice++;
					}
					if(P[i][j - 1].type == 3 || P[i][j + 1].type == 3 || P[i - 1][j].type == 3 || P[i + 1][j].type  == 3){
						P[i][j].landprice--;					
					}
					if(P[i][j - 1].type == 8 && P[i][j + 1].type == 8 && P[i - 1][j].type == 8 && P[i + 1][j].type  == 8 ){
						P[i][j].landprice = 0;
					}
				}
				if(P[i][j].type == 2){
					//if(P[y][x - 1].type == 1 || P[y][x + 1].type == 1 || P[y - 1][x].type == 1 || P[y + 1][x].type  == 1 ){
					//	P[y][x].landprice++;
					//}
					if(P[i][j - 1].type == 8 || P[i][j + 1].type == 8 || P[i - 1][j].type == 8 || P[i + 1][j].type  == 8 ){
						P[i][j].landprice += 2;
					}
					if(P[i][j - 1].type == 3 || P[i][j + 1].type == 3 || P[i - 1][j].type == 3 || P[i+ 1][j].type  == 3){
						P[i][j].landprice++;					
					}
				}
				if(P[i][j].type == 3){
				//	if(P[y][x - 1].type == 2 || P[y][x + 1].type == 2 || P[y - 1][x].type == 2 || P[y + 1][x].type  == 2 ){
					//	P[y][x].landprice++;
				//	}
					if(P[i][j - 1].type == 2 || P[i][j + 1].type == 2 || P[i - 1][j].type == 2 || P[i + 1][j].type  == 2 ){
						P[i][j].landprice ++;
					}
					if(P[i][j - 1].type == 8 || P[i][j + 1].type == 8 || P[i - 1][j].type == 8 || P[i + 1][j].type  == 8 ){
						P[i][j].landprice = 0;
					}

				}
				
			}
		}
}
	

int CheckRatioEvent(int revenue){
	//char blank = "                                         ";
	if(Town.count >= 10 &&(Town.count - Fact.count) >= 10){
	  		 //mvaddstr(30, 3, "There is a few Factory, Please Build Factory");
	  		 revenue = revenue / 4 ;
	}else if(Town.count >= 5 &&(Town.count - Fact.count) >= 5){
				 revenue = revenue / 2 ;
	}else{
			   //mvaddstr(30, 3, "                                            ");
	}
	if(Town.count >= 10 &&(Town.count - Shop.count) >= 10){
	  		// mvaddstr(30, 3, "There is a few Shop, Please Build Shop");
	  		 revenue = revenue / 4 ;
	}else if(Town.count >= 5 &&(Town.count - Shop.count) >= 5){
				 revenue = revenue / 2 ;
	}else{
			   //mvaddstr(30, 3, "                                            ");
	}
	return revenue;
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
		attrset(COLOR_PAIR(10));
		switch(moderand){
		case 1:
			break;
		case 2:
					for(i = 1;i < h - 1; i++){
			tmp2 += 25;
			for(j = 1; j < w - 30; j++){
				//usleep(10);
				srand((tmp1 * rand1) * j/i + (rand2 *  i)/j);
				tmp1 = ((rand() % 10) + i) * 0.05;
				if((tmp1 * tmp2) >= 2000){
					P[i][j].type = 8;
				    mvprintw(i,j," ");
				}
			}
		}
			break;
		case 3:
			for(i = 1;i < h - 1; i++){
				tmp2 += 25;
				for(j = 1; j < w - 30; j++){
					//usleep(10);
					srand((tmp1 * rand1) * j/i + (rand2 *  i)/j);
					tmp1 = ((rand() % 10) + j) * 0.05;
					if((tmp1 * tmp2) >= 2000){
						P[i][j].type = 8;
					    mvprintw(i,j," ");
					}
				}
			}
			break;
		case 4:
			for(i = h - 2; i >= 1; i -= 1){
				tmp2 += 25;
				for(j = 1; j < w - 30; j++){
				//usleep(10);
					srand((tmp1 * rand1) * j/i + (rand2 *  i)/j);
					tmp1 = ((rand() % 10) + h-i) * 0.05;
					if((tmp1 * tmp2) >= 700){
						P[i][j].type = 8;
						mvprintw(i,j," ");
					}
				}
			}
			break;
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
						mvprintw(i,j," ");
					}
				}
			}
			break;
		default:break;

		
		}
}


int CheckClear(int h, int w, Piece P[][w]){
	int i,j;
	for(i = 1;i < h - 1; i++){
		for(j = 1; j < w - 30; j++){
			if(P[i][j].type == 0 ){
				return 0;
			}
		}
	}
	if(money >= 100000000){
		return 1;
	}
	return 1;
}
int clearSc(int h, int w){
	int key;
	attrset(COLOR_PAIR(5));
	box(stdscr, ' ' , ' ');
	//printLogo(10,3,Clear);
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

