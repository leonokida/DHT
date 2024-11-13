// Leon Okida e Pedro Willian
#include <stdio.h>
#include <stdlib.h>

typedef struct finger finger;
typedef struct dht_node dht_node;

struct dht_node {
    int id;
    int *table;
    finger *finger_table;
    int table_size;
    int finger_table_size;
    dht_node *next;
};

struct finger {
    int finger;
    dht_node *node;
};

// Initializes the DHT variables
void initialize_dht(dht_node **dht_table, int *size);

// Inserts the DHT node in order in the ring, increments size of the DHT
void insert_node(dht_node **dht_table, int id, int *size);

// Removes the DHT node from the ring, decrements the size of the DHT
void remove_node(dht_node **dht_table, int id, int *size);

// Lookup routing
dht_node *key_lookup(dht_node **dht_table, int key, dht_node **visited_nodes, int *visited_count);

// Insert key
void insert_key(dht_node **dht_table, int key, dht_node **visited_nodes, int *visited_count);

// Search key in node
int search_key(dht_node *dht_table, int key);

// Prints contents of the DHT
void print_dht(dht_node *dht_table);