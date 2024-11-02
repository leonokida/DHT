#include "dht_nodes.h"

// Creates a new dht node
dht_node *create_node(int id) {
    // Allocates memory for the dht_node structure itself
    dht_node *new_node = (dht_node *)malloc(sizeof(dht_node));
    if (!new_node) {
        exit(1);
    }

    // Initializes the fields
    new_node->id = id;
    new_node->table_size = 0;
    new_node->finger_table_size = 0;

    // Allocates memory for the table and the finger_table
    new_node->table = (int *)malloc(32 * sizeof(int));
    if (!new_node->table) {
        free(new_node);
        exit(1);
    }

    new_node->finger_table = (int *)malloc(30 * sizeof(int));
    if (!new_node->finger_table) {
        free(new_node->table);
        free(new_node);
        exit(1);
    }

    return new_node;
}

// Function to sort the ring
int compare_dht_nodes(const void *a, const void *b) {
    dht_node *nodeA = *(dht_node **)a;
    dht_node *nodeB = *(dht_node **)b;
    return (nodeA->id - nodeB->id);
}

// Finds the address of the node with the smallest N bigger than the finger
int find_node(int finger, dht_node **dht_table, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (dht_table[i]->id >= finger)
            return i;
    }
    return 0;
}

// Updates the finger table of a node
void update_finger_table(int node, dht_node **dht_table, int size) {
    int m = ceil(log2(dht_table[size-1]->id));
    int n = dht_table[node]->id;
    int k;
    for (k=1;k<=m;k++) {
        // Adds the address of the node related to the finger calculated with k
        // (N+2^(k-1))mod 2^m
        int finger = (n + (int)pow(2, k-1)) % (int)pow(2,m);
        dht_table[node]->finger_table[k-1] = find_node(finger, dht_table, size);
    }
    dht_table[node]->finger_table_size = m;
}

void insert_node(dht_node **dht_table, int *size, int id) {
    dht_node *new_node = create_node(id);
    dht_table[*size] = new_node;
    *size++;
    // Sorts the ring
    qsort(dht_table, *size, sizeof(dht_node *), compare_dht_nodes);

    // Updates the finger table of each node
    for (int node = 0; node < *size; node++) {
        update_finger_table(node, dht_table, *size);
    }
}