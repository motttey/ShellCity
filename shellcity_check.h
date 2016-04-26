#ifndef SHELLCITY_CHECK_H
#define SHELLCITY_CHECK_H

#include<ncurses.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

#include "shellcity_val.h"
#include "shellcity_event.h"

void CheckArea(int y,int x,int h, int w,Piece *P);
void CheckAdjacent(int x, int y, int h, int w, Piece P[][w]);
void CheckPublicFacility(int h, int w, int y, int x, int population, Piece P[][w]);
int CheckRatioEvent(int revenue);
int CheckClear(int h, int w, Piece P[][w]);


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
					//jail
					if(P[i][j - 1].type == 7 && P[i][j + 1].type == 7 && P[i - 1][j].type == 7 && P[i + 1][j].type  == 7 ){
						P[i][j].landprice = 0;
					}
					//sea
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

void CheckPublicFacility(int h, int w, int y, int x, int population, Piece P[][w]){
		
	//Police 
		if(population - Police.count * Police.pop >= Police.pop){
				PublicFacilityEvent(&Police, PoliceMessage, x, y, h, w, P);
				//P[y][x].type = Police.type;
		}

		//firehouse
		if(population - Firehouse.count * Firehouse.pop >= Firehouse.pop){
				PublicFacilityEvent(&Firehouse, FirehouseMessage, x, y, h, w, P);
				//P[y][x].type = Firehouse.type;
		}
		
		//hospital
		if(population - Hospital.count * Hospital.pop >= Hospital.pop){
				PublicFacilityEvent(&Hospital, HospitalMessage, x, y, h, w, P);
				//P[y][x].type = Hospital.type;
		}
		//jail
		if(population - Jail.count * Jail.pop >= Jail.pop){
				PublicFacilityEvent(&Jail, JailMessage, x, y, h, w, P);
				//P[y][x].type = Jail.type;
		}

}
	

int CheckRatioEvent(int revenue){

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

int CheckClear(int h, int w, Piece P[][w]){
	int i,j;
	int val = (h - 2) * (w - 32);
	for(i = 1;i <= h ; i++){
		for(j = 0; j <= w - 30; j++){
			if(val <= 0 ){
				return 1;
			}
			if(P[i][j].type != 0 ){
				val--;
			}
		}
	}
	if(money >= 10000000){
		return 1;
	}
	return 0;
}

#endif
