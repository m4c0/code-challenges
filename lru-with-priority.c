// incomplete - pass 11 of 15, missing eviction
#define MAP_LEN 193939 // prime

typedef struct prio_s {
    int key;
    int value;
    int prio;
    int usage;
    struct prio_s * next;
    struct prio_s * prev;
} prio_t;

static int comp_prio(const prio_t * a, const prio_t * b) {
    if (a->prio < b->prio) return -1;
    if (a->prio > b->prio) return 1;
    if (a->usage < b->usage) return -1;
    if (a->usage > b->usage) return 1;
    return 0;
}
static void heapify(prio_t ** map, prio_t * q, int n, int i) {
    q--;
    i++;
    
    while (1) {
        int l = i * 2;
        int r = i * 2 + 1;
        
        int s = i;
        if (l <= n && comp_prio(&q[l], &q[s]) < 0) s = l;
        if (r <= n && comp_prio(&q[r], &q[s]) < 0) s = r;
        
        if (s == i) break;
        
        if (map[q[i].key] == &q[i]) map[q[i].key] = &q[s];
        if (map[q[s].key] == &q[s]) map[q[s].key] = &q[i];
        if (q[i].next) q[i].next = &q[s];
        if (q[s].next) q[s].next = &q[i];
        if (q[i].prev) q[i].prev = &q[s];
        if (q[s].prev) q[s].prev = &q[i];
        
        prio_t tmp = q[s];
        q[s] = q[i];
        q[i] = tmp;        
    }
}

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
                p->prev  = NULL;
                
                int k = keys[i] % MAP_LEN;
                p->next = map[k];
                if (p->next) p->next->prev = p;
                map[k] = p;
                
                d_size++;
            } else {
                // p = &data[0];
                
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
            heapify(map, data, d_size, p - data);
        }
    }
    
    return result;
}

