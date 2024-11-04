// Leon Okida e Pedro Willian
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dht_nodes.h"

int main() {
    dht_node *dht;
    int size_dht;

    initialize_dht(&dht, &size_dht);

    insert_node(&dht, 8, &size_dht);
    insert_node(&dht, 24, &size_dht);
    insert_node(&dht, 16, &size_dht);
    insert_node(&dht, 36, &size_dht);
    insert_node(&dht, 52, &size_dht);

    print_dht(dht);

    int result_lookup1 = key_lookup(dht, 15)->id; // 16
    int result_lookup2 = key_lookup(dht, 23)->id; // 24
    int result_lookup3 = key_lookup(dht, 53)->id; // 8

    printf("Results from Lookups: %d, %d, %d\n", result_lookup1, result_lookup2, result_lookup3);

    return 0;
}