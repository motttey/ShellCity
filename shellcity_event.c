#include "shellcity_event.h"

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
	//random val
	srand((unsigned)time(NULL));
	P->pop = rand()%(A->pop + (A->pop - 3)) + A->pop - 2;
	P->landprice = rand()%A->landprice + A->landprice - 2;
	money = money - A->cost;
	//A->revenue += P->landprice;
	//money -= rand()%(A->pop + 2) + 3;
	switch(A->type){
		case 1: attron(COLOR_PAIR(1));
			  P->type = 1;
			  break;
		case 2: attron(COLOR_PAIR(2));
			  P->type = 2;
				break;
		case 3: attron(COLOR_PAIR(3));
			 P->type = 3;
				break;
		case 11: attron(COLOR_PAIR(1)| A_BLINK);
			P->type = 11;
				 break;
		case 12: attron(COLOR_PAIR(2)| A_BLINK);
			P->type = 12;
				 break;
		case 13: attron(COLOR_PAIR(3)| A_BLINK);
			P->type = 13;
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
