typedef struct node_s {
    int value;
    struct node_s * next;
} node_t;

int* processRequestQueueOperations(int operations_count, char** operations, int values_count, int* values, int* result_count) {
    int * result = malloc(sizeof(int) * operations_count);
    int res_i = 0;
    
    node_t * ins = NULL;
    node_t * outs = NULL;

    int size = 0;
    
    for (int i = 0; i < operations_count; i++) {
        const char * cmd = operations[i];
        if (0 == strcmp(cmd, "enqueue")) {
            while (outs) {
                node_t * next = outs->next;
                outs->next = ins;
                ins = outs;
                outs = next;
            }
            
            node_t * n = malloc(sizeof(node_t));
            n->value = values[i];
            n->next = ins;
            ins = n;
            size++;
        }
        if (0 == strcmp(cmd, "dequeue")) {
            while (ins) {
                node_t * next = ins->next;
                ins->next = outs;
                outs = ins;
                ins = next;
            }
            if (outs) {
                result[res_i++] = outs->value;
                
                node_t * next = outs->next;
                free(outs);
                outs = next;
            }
        }
        if (0 == strcmp(cmd, "peek")) {
            while (ins) {
                node_t * next = ins->next;
                ins->next = outs;
                outs = ins;
                ins = next;
            }
            if (outs) {
                result[res_i++] = outs->value;
            }
        }
        if (0 == strcmp(cmd, "size")) {
            result[res_i++] = size;
        }
    }
    
    *result_count = res_i;
    return result;
}

