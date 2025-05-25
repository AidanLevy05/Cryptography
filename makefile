PROG = prog 
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = main.o Encrypt.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp 

Encrypt.o : Encrypt.cpp Encrypt.h
	$(CC) $(CPPFLAGS) -c Encrypt.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make