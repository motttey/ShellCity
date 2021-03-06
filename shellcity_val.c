#include "shellcity_val.h";

	Town = {1,  4, 0, 2, 0, 300};
	Shop = {2,  6, 0, 4, 0, 500};
	Fact = {3,  5, 0, 3, 0, 400}; 
	//if pop >= 500
	Town_High = {11, 10, 0, 10 , 0,1000};
	Shop_High = {12, 30, 0, 15 , 0,1500};
	Fact_High = {13, 25, 0, 12 , 0,1300};

	PuPolice    = {1,20 ,"P",0};
	Pub_fac Firehouse = {2,50 ,"F",0};
	Pub_fac Hospital  = {3,100 ,"H",0};
	Pub_fac Jail      = {4,150 ,"J",0};
	
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
*GameOverAA[] = {
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


*Logo[] = {
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


*GameOver[] = {
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

*Clear[] = {
	"                 #:::::::##:::#$    #::::::::#   #:::::#   #:::::::::#                     "
	"                #::::::::##:::#$    #::::::::#  #:::#:::#  #:::::::::::#                   ",  
	"                #::::$##$$#:::#$    #:::######  #::#$#::#  #:::######::#                   ",
	"               #::::#$$$  #:::#$    #:::#$     #:::#$#:::# #:::#$$  #::#                   ",    
	"               #::::#$    #:::#$    #:::#####  #::#$ ##::# #:::#####::#                    ",    
	"               #::::#$#####:::#$    #::::::::###::#####::# #:::::::::#                     ",  
	"               #::::#$#:::#:::#$    #::::::::##:::::::::::##:::::::::#                     ",  
	"               #::::$##:::#:::#$    #:::#######::::###::::##:::#$$#:::#                    ", 
	"               #::::::::::#:::#######:::#$$$  #::::#$#::::##:::#$$$#:::#                   ",  
	"               #:::::::::$#:::::::::#::::::::##:::#$$ #:::##:::#$ $#:::#                   ", 
	"                #$:::::$###:::::::::#::::::::##:::#$  #:::##:::#$  $#:::#                  ",     
	"                                                                    Press 'r' To Retry     ",
	"                                                                        'q' To  Quit     " 
};
		
 *firstMessage     = "This is Shell City  ";
 *PoliceMessage    = "Locate The Police   ";
 *FirehouseMessage = "Locate the Firehouse";
 *HospitalMessage  = "Locate tha Hospital ";
 *JailMessage      = "Locate the Jail     ";
	