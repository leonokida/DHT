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
    dht_node **visited_nodes = calloc(30, sizeof(dht_node*));
    int visited_count;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        visited_count = 0;
        sscanf(line, "%d %c %d %d", &timestamp, &operation, &node_id, &key);
        dht_node *itr;

        //printf("Timestamp: %d, Operation: %c, Node ID: %d \n", timestamp, operation, node_id);
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
                // encontra o nó correto para começar a operação
                itr = dht_table;
                do {
                    itr = itr->next;
                } while ((itr->id != node_id));
                insert_key(&itr, key, visited_nodes, &visited_count);
                break;

            case 'L': {  // Lookup de chave
                itr = dht_table;
                do {
                    itr = itr->next;
                } while ((itr->id != node_id));
                //Inicia Lookup
                key_lookup(&itr, key, visited_nodes, &visited_count);

                // Imprime resultados
                printf("%d L %d {", timestamp, key);
                for (int i = 0; i < visited_count; i++) {
                    printf("%d", visited_nodes[i]->id);
                    if (i < visited_count - 1)
                        printf(",");
                }
                printf("}\n");

                for (int i = 0; i < visited_count; i++) {
                    printf("%d T %d {", timestamp, visited_nodes[i]->id);
                    for (int j = 0; j < visited_nodes[i]->finger_table_size; j++) {
                        printf("%d", visited_nodes[i]->finger_table[j].node->id);
                        if (j < visited_nodes[i]->finger_table_size - 1)
                            printf(",");
                    }
                    printf("}\n");
                }
                break;
            }
        }
    }

    free(dht_table);

    return 0;
}
