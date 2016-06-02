CC = g++
CFLAGS = -O2 -Wall -Wextra --std=c++11

all: problema2 heuristicas

problema2: problema2-exacto.cpp
	$(CC) $(CFLAGS) $< -o $@

heuristicas: heuristicas.o localSearch.o greedy.o
	$(CC) $^ -o $@

heuristicas.o: heuristicas.cpp
	$(CC) $(CFLAGS) -c heuristicas.cpp 

greedy.o: greedy.h greedy.cpp
	$(CC) $(CFLAGS) -c greedy.cpp

localSearch.o: localSearch.h localSearch.cpp
	$(CC) $(CFLAGS) -c localSearch.cpp

clean:
	rm -rf problema2 heuristicas
	rm -rf *.o
