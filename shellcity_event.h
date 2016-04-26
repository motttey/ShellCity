
#ifndef SHELLCITY_EVENT_H
#define SHELLCITY_EVENT_H

#include<ncurses.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

#include "shellcity_val.h"
//#include "shellcity_check.h"


void addArea(Area *A, Piece *P);
void delArea(Area *A, Piece *P);
void add_public_facility(Pub_fac *P);
void del_public_facility(Pub_fac *P);
void PublicFacilityEvent(Pub_fac *P, char *Message,int x,int y, int h,int w,Piece Piece[][w]);

//prevent  "conflicting types for 'CheckArea'"
void CheckArea(int y,int x,int h, int w,Piece *P);



void PublicFacilityEvent(Pub_fac *P, char *Message,int x,int y, int h,int w, Piece Piece[][w]){
		
		//flag(check whether publicfaciity is built)
		int flag;
		flag = 0;
		
		curs_set(0);
		attrset(0);
		move(h-2,w-strlen(Message)-1);
		addstr(Message);
		

		//until publicfaclity build
		while(flag == 0){
			move(y,x);
		    curs_set(1);
			int key;
			key = getch();
			switch(key){
				case 'u'	: y--; break;	//up
				case 'j'	: y++; break;	//down
				case 'h'	: x--; break;	//left
				case 'k'  : x++; break;	//right
				//build public facility
				case  'P':
					CheckArea(y,x,h,w,&Piece[y][x]);
					add_public_facility(P);
					flag = 1;
					Piece[y][x].type = P->type; 
 					break;
				case 'd'    :             
				    CheckArea(y,x,h,w,&Piece[y][x]);
					break;
				default:break;
			}
			
			//
			if(population <= P->pop){
				flag = 1;
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
	return;
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
		case 1: 
			  P->type = 1;
			  break;
		case 2: 
			  P->type = 2;
				break;
		case 3: 
			 P->type = 3;
				break;
		case 11: 
			P->type = 11;
				 break;
		case 12: 
			P->type = 12;
				 break;
		case 13: 
			P->type = 13;
				 break;
	}
	return;
}

void add_public_facility(Pub_fac *P){
	P->count++;
	return;
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
	return;
}

void del_public_facility(Pub_fac *P){
	P->count--;
	return;
}


#endif


