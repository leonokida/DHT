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

    remove_node(&dht, 16, &size_dht);

    print_dht(dht);

    return 0;
}