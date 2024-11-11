// Leon Okida e Pedro Willian

#include "dht_nodes.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    dht_node *dht_table;
    int dht_size = 0;
    initialize_dht(&dht_table, &dht_size);
    int timestamp;
    char operation;
    int node_id;
    int key;
    char line[100];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        sscanf(line, "%d %c %d %d", &timestamp, &operation, &node_id, &key);

        printf("Timestamp: %d, Operation: %c, Node ID: %d ", timestamp, operation, node_id);
        // if (operation == 'I' || operation == 'L') {
        //     printf(", Key: %d", key);
        // }

        switch (operation) {
            case 'E':  // Entrada de nó
                insert_node(&dht_table, node_id, &dht_size);
                break;

            case 'S':  // Saída de nó
                remove_node(&dht_table, node_id, &dht_size);
                break;

            case 'I':  // Inclusão de chave
                printf("entrei");
                insert_key(&dht_table, key);
                printf("sai");
                break;

            case 'L': {  // Lookup de chave
                dht_node *found_node = key_lookup(&dht_table, key);

                printf("%d L %d {", timestamp, key);
                dht_node *route = dht_table;
                while (route != found_node) {
                    printf("%d, ", route->id);
                    route = route->next;
                }
                printf("%d}\n", found_node->id);

                route = dht_table;
                while (route != found_node->next) {
                    printf("%d T %d {", timestamp, route->id);
                    for (int i = 0; i < route->finger_table_size; i++) {
                        printf("%d", route->finger_table[i].node->id);
                        if (i < route->finger_table_size - 1)
                            printf(", ");
                    }
                    printf("}\n");
                    route = route->next;
                }
                break;
            }
        }
    }

    free(dht_table);

    return 0;
}
