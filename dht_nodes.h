// Leon Okida e Pedro Willian
#include <stdio.h>
#include <stdlib.h>

typedef struct dht_node dht_node;
struct dht_node
{
    int id;
    int *table;
    int *finger_table;
    dht_node *next;
};


// inserts dht node in order in the ring
void insert_node(dht_node **dht_table, int id);

// removes node from the ring
void remove_node(dht_node **dht_table, int id);