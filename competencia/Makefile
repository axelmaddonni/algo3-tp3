CC = g++
CFLAGS = -O2 -Wall -Wextra --std=c++11 -g
TARGETS = local-search.o goloso.o utilidades.o

all: competencia

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

competencia: $(TARGETS) competencia.cpp
	$(CC) $(CFLAGS) $(TARGETS) -o $@ competencia.cpp

clean:
	rm -rf problema2 problema3 testerproblema3 problema4 problema5 problema6
	rm -rf *.o
