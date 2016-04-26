#ifndef SHELLCITY_CALC_H
#define SHELLCITY_CALC_H

#include<ncurses.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

#include "shellcity_val.h"

void ResetGlobalVal(void);
void CalcParam(int revenue,int tmpopulation);
int CalcTmpRev(int h, int w, int revenue, Piece P[][w]);
int CalcTmpPop(int h, int w, int tmpopulation, Piece P[][w]);

void ResetGlobalVal(){
	//initialization
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
	Police.count = 0;
	Firehouse.count = 0;
	Hospital.count = 0;
	Jail.count = 0;
	GameOverflag = 0;
	Clearflag = 0;
	ReStartflag = 0;
	return;
}

//calculate money and population
void CalcParam(int revenue,int tmpopulation){
	money += revenue;
	money += Police.count * (-1) * Police.expense; 
	money += Firehouse.count * (-1) * Firehouse.expense;
	money += Hospital.count * (-1) * Hospital.expense;
	money += Jail.count * (-1) * Jail.expense ;
	population = tmpopulation;
	return;
}

//calculate temporary revenue
int CalcTmpRev(int h, int w, int revenue, Piece P[][w]){
	
	int i,j;
	for(i = 1;i < h - 1; i++){
		for(j = 1; j < w - 30; j++){
			switch(P[i][j].type){
				case 1:
				case 2:
				case 3:
				case 11:
				case 12:
				case 13:
					revenue += P[i][j].landprice;
					break;
				default:
					break;
			}
		}
	}
	return revenue;
}

//calculate temporary population
int CalcTmpPop(int h, int w, int tmpopulation, Piece P[][w]){
	
	int i,j;
	for(i = 1;i < h - 1; i++){
		for(j = 1; j < w - 30; j++){
			switch(P[i][j].type){
				case 1:
				case 2:
				case 3:
				case 11:
				case 12:
				case 13:
					tmpopulation += P[i][j].pop;
					break;
				default:
					break;
			}
		}
	}
	return tmpopulation;
}

#endif

