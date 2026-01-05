CC = g++
CFLAGS = -Wall -std=c++14

wits_and_wagers: wits_and_wagers.o question.o player.o
	$(CC) $(CFLAGS) -o wits_and_wagers wits_and_wagers.o question.o player.o
	
wits_and_wagers.o: wits_and_wagers.cpp question.hpp player.hpp
	$(CC) $(CFLAGS) -c wits_and_wagers.cpp

question.o: question.cpp question.hpp
	$(CC) $(CFLAGS) -c question.cpp

player.o: player.cpp player.hpp
	$(CC) $(CFLAGS) -c player.cpp
	
clean:
	rm *.o wits_and_wagers