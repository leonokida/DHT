# Leon Okida e Pedro Willian

CFLAGS = -lm -Wall -std=c99 # compilation flag

all: mydht

mydht: dht_nodes.o mydht.c
	gcc mydht.c dht_nodes.o -o mydht $(CFLAGS)
dht_nodes.o: dht_nodes.c
	gcc -c dht_nodes.c -o dht_nodes.o
clean:
	-rm -f *.o
purge: clean
	-rm mydht