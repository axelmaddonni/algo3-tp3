CC = g++
CFLAGS = -O2 -Wall -Wextra --std=c++11

all: problema2 problema4

problema2: problema2-exacto.cpp
	$(CC) $(CFLAGS) $< -o $@

problema4: problema4-heuristico.cpp
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -rf problema2 problema4

