#include "dht_nodes.h"
#include <math.h>

void initialize_dht(dht_node **dht_table, int *size) {
    *dht_table = NULL;
    *size = 0;
}

// Creates a new node with an id
dht_node *create_node(int id) {
    dht_node *new_node = (dht_node *)malloc(sizeof(dht_node));
    if (!new_node) {
        printf("Memory allocation for new node failed!");
        exit(1);
    }
    new_node->id = id;
    new_node->next = new_node;
    new_node->finger_table = (finger *)malloc(32*sizeof(finger));
    new_node->table = (int *)malloc(32*sizeof(int));
    new_node->finger_table_size = 0;
    new_node->table_size = 0;

    return new_node;
}

// Finds the greatest key in an ordered DHT table (the last element)
int find_greatest_key(dht_node *dht_table) {
    dht_node *itr = dht_table;
    while (itr->next != dht_table)
        itr = itr->next;
    return itr->id;
}

// Finds the node to construct the finger table
dht_node *find_node_by_finger(dht_node *node, int finger_value) {
    dht_node *itr = node;
    do {
        if (itr->id >= finger_value)
            return itr;
        itr = itr->next;
    } while (itr != node);
    return itr;
}

// Updates the finger table of a node in the DHT
void update_finger_table(dht_node **node, dht_node *first_node, int m) {
    //(N+2^(k-1))mod 2^m
    int n = (*node)->id;
    for (int k = 1; k <= m; k++) {
        int finger_value = (n + (int)pow(2, k-1)) % (int)pow(2,m);
        (*node)->finger_table[k-1].finger = finger_value;
        (*node)->finger_table[k-1].node = find_node_by_finger(first_node, finger_value);
    }
    (*node)->finger_table_size = m;
}

void insert_node(dht_node **dht_table, int id, int *size) {
    dht_node *new_node = create_node(id);

    // Empty DHT
    if (*dht_table == NULL) {
        *dht_table = new_node;
        return;
    }

    dht_node *current = *dht_table;
    dht_node *prev = NULL;

    // The new node is smaller than the current first element
    if (id < current->id) {
        while (current->next != *dht_table) {
            current = current->next;
        }
        current->next = new_node;
        new_node->next = *dht_table;
        dht_table = &(new_node);
        return;
    }

    // Inserting at the middle or the end of the ring
    do {
        prev = current;
        current = current->next;
    } while (current != *dht_table && current->id < id);

    prev->next = new_node;
    new_node->next = current;
    *size += 1;

    // Updates the finger table of each node
    dht_node *itr = *dht_table;
    int m = ceil(log2(find_greatest_key(*dht_table)));
    do {
        update_finger_table(&itr, *dht_table, m);
        itr = itr->next;
    } while (itr != *dht_table);
}

dht_node *key_lookup(dht_node *dht_table, int key) {
    // Checks if the key is stored in the current node
    if (key <= dht_table->id)
        return dht_table;

    // The key is greater than the last node, so it's in the first node
    if ((dht_table->id > dht_table->next->id) && (key > dht_table->id)) 
        return dht_table->next;

    // Uses the finger table to find the closest preceding node for the key
    for (int i = dht_table->finger_table_size - 1; i >= 0; i--) {
        int finger_value = dht_table->finger_table[i].finger;
        dht_node *node = dht_table->finger_table[i].node;

        // Found candidate node for routing
        if (finger_value <= key && finger_value > dht_table->id) {
            return key_lookup(node, key);
        }
    }

    // Didn't find a candidate, try the next node
    return dht_table->next;
}

void print_dht(dht_node *dht_table) {
    if (dht_table == NULL) {
        printf("DHT is empty\n");
        return;
    }
    dht_node *itr = dht_table;
    do {
        printf("%d\n", itr->id);
        printf("Finger table:\n");
        for (int i = 0; i < itr->finger_table_size; i++) {
            printf("    finger: %d\n", itr->finger_table[i].finger);
            printf("    node: %d\n", itr->finger_table[i].node->id);
        }
        printf("######\n");
        itr = itr->next;
    } while (itr != dht_table);
}