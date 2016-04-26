# Makefile for main.c
SRCS= main.c
HEADS= shellcity_val.h shellcity_view.h shellcity_check.h shellcity_scr.h shellcity_event.h shellcity_calc.h
OBJS= $(SRCS:.c=.o)
TARGET= nc

CC= gcc
CFLAGS= -Wall
LDFLAGS= -lncurses

all:	$(TARGET)
nc:	$(OBJS)
	$(CC) -o $@ $(OBJS) $(HEADS) $(LDFLAGS)
.c.o:
	$(CC) -c $< $(CFLAGS)
clean:
	rm -f $(OBJS) $(TARGET)
run:	all
	./$(TARGET) 
