CC = g++
CFLAGS = -O2 -Wall -Wextra --std=c++11 -g
TARGETS = local-search.o goloso.o utilidades.o

all: problema2 testerproblema3 problema4 problema5

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

problema2: $(TARGETS) problema2-exacto.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ problema2-exacto.cpp

testerproblema3: $(TARGETS) tester_problema3.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ tester_problema3.cpp

problema4: $(TARGETS) problema4-goloso.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ problema4-goloso.cpp

problema5: $(TARGETS) problema5-heuristicas.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ problema5-heuristicas.cpp

clean:
	rm -rf problema2 testerproblema3 problema4 problema5
	rm -rf *.o
