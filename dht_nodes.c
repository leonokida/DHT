#include "dht_nodes.h"

dht_node *create_node(int id) {
    dht_node *new_node = (dht_node *)malloc(sizeof(dht_node));
    if (!new_node) {
        printf("Memory allocation for new node failed!");
        exit(1);
    }
    new_node->id = id;
    new_node->next = new_node;
    return new_node;
}

void insert_node(dht_node **dht_table, int id) {
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
}