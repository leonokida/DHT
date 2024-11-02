// Leon Okida e Pedro Willian
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct dht_node dht_node;
struct dht_node
{
    int id;
    int *table;
    int table_size;
    int *finger_table;
    int finger_table_size;
};

// inserts dht node in order in the ring
void insert_node(dht_node **dht_table, int *size, int id);

// removes node from the ring
void remove_node(dht_node **dht_table, int *size, int id);