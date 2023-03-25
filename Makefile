.DEFAULT_GOAL := integrate
CC = g++
FLAGS = -Ofast -Wall -Wextra -pedantic
OBJECTS = integrate.o
EXECUTABLE = integrate
NAME = bestus1

all:    clean integrate

integrate:	compile
	$(CC) $(OBJECTS) -o $(EXECUTABLE) -lpthread

compile:	integrate.cpp
	$(CC) $(FLAGS) -c integrate.cpp

clean:
	rm -f -r *.o *.exe *.cpp~ $(EXECUTABLE) .vscode
	
tar: clean
	cd .. && tar --exclude-vcs -cvzf $(bestus1).tar.gz $(bestus1) && cd -