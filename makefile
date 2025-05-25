PROG = prog 
CC = g++
CPPFLAGS = -g -Wall -std=c++11 -fopenmp
OBJS = main.o Encrypt.o

$(PROG) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)

main.o : main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp 

Encrypt.o : Encrypt.cpp Encrypt.h
	$(CC) $(CPPFLAGS) -c Encrypt.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make