CC = g++
CFLAGS = -O2 -Wall -Wextra --std=c++11
TARGETS = localSearch.o greedy.o utilidades.o

all: problema2 heuristicas

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

problema2: $(TARGETS) problema2-exacto.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ problema2-exacto.cpp

heuristicas: $(TARGETS) heuristicas.cpp
	$(CC) $(FLAGS) $(TARGETS) -o $@ heuristicas.cpp


clean:
	rm -rf problema2 heuristicas
	rm -rf *.o
