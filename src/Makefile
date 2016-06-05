CC = g++
CFLAGS = -O2 -Wall -Wextra --std=c++11 -g
TARGETS = localSearch.o goloso.o utilidades.o

all: problema2 testerproblema3 heuristicas 

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

problema2: $(TARGETS) problema2-exacto.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ problema2-exacto.cpp problema2-exacto.hpp 

testerproblema3: $(TARGETS) tester_problema3.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ tester_problema3.cpp problema3-cografos.hpp

heuristicas: $(TARGETS) heuristicas.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ heuristicas.cpp

clean:
	rm -rf problema2 testerproblema3 heuristicas
	rm -rf *.o
