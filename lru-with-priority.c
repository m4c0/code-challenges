// incomplete - pass 11 of 15, missing eviction and LRU
#define MAP_LEN 193939 // prime

typedef struct prio_s {
    int key;
    int value;
    int prio;
    int usage;
    struct prio_s * next;
} prio_t;

int* simulatePriorityCache(int capacity, int numOperations, int operationTypes_count, char** operationTypes, int keys_count, int* keys, int values_count, int* values, int priorities_count, int* priorities, int* result_count) {
    int * result = malloc(operationTypes_count * sizeof(int));
    *result_count = 0;
    
    prio_t * data = calloc(capacity, sizeof(prio_t));
    int d_size = 0;
    
    prio_t ** map = calloc(MAP_LEN, sizeof(prio_t *));
    
    for (int i = 0; i < operationTypes_count; i++) {
        prio_t * p_prev = NULL;
        prio_t * p = NULL;
        for (p = map[keys[i]]; p; p_prev = p, p = p->next) {
            if (p->key == keys[i]) break;
        }
        
        if (0 == strcmp("get", operationTypes[i])) {
            result[*result_count] = p ? p->value : -1;
            ++*result_count;
        }
        if (0 == strcmp("put", operationTypes[i])) {
            if (p) {
                p->value = values[i];
                p->prio  = priorities[i];
            } else if (d_size < capacity) {
                p = &data[d_size];
                p->key   = keys[i];
                p->value = values[i];
                p->prio  = priorities[i];
                
                int k = keys[i] % MAP_LEN;
                p->next = map[k];
                map[k] = p;
                
                d_size++;
            } else {
                // evict
            }
        }
        if (0 == strcmp("updatePriority", operationTypes[i])) {
            if (p) {
                p->prio = priorities[i];
            } else {
                // TODO: what to do?
            }
        }
        
        if (p) {
            p->usage = i;
            // update lru            
        }
    }
    
    return result;
}

