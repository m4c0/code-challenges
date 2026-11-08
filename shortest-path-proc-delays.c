typedef struct edge_s {
    int to;
    int cost;
    struct edge_s * next;
} edge_t;

typedef struct q_s {
    int id;
    int64_t prio;
} q_t;

static void decrease_prio(q_t * q, int n, int id) {
    id++; q--; // operate on base 1
    while (id != 1 && q[id].prio < q[id / 2].prio) {
        q_t tmp = q[id];
        q[id] = q[id / 2];
        q[id / 2] = tmp;
        
        id /= 2;
    }
}

static void heapify(q_t * q, int n, int i) {
    // Only works for i starting from 1
    int l = 2 * i;
    int r = 2 * i + 1;
    int s = l <= n && q[l].prio < q[i].prio ? l : i;
    if (r <= n && q[r].prio < q[i].prio) s = r;
    
    if (s != i) {
        q_t tmp = q[s];
        q[s] = q[i];
        q[i] = tmp;
        heapify(q, n, s);
    }
}
static void pop(q_t * q, int * n) {
    q[0] = q[--*n];
    heapify(q - 1, *n, 1);
}

int* computeShortestDeliveryTimes(int n, int handlingTimes_count, int* handlingTimes, int m, int routes_rows, int routes_columns, int** routes, int source, int* result_count) {
    if (n == 0) {
        *result_count = 0;
        return NULL;
    }
    
    edge_t ** edges = calloc(n, sizeof(edge_t *));
    for (int i = 0; i < m; i++) {
        int * route = routes[i];
        edge_t * e = malloc(sizeof(edge_t));
        e->to   = route[1];
        e->cost = route[2];
        e->next = edges[route[0]];
        edges[route[0]] = e;
    }
    
    int64_t * dist = malloc(n * sizeof(int64_t));
    for (int i = 0; i < n; i++) {
        dist[i] = (1UL << 63) - 1;
    }
    dist[source] = 0;

    q_t * q = malloc(2 * n * sizeof(q_t));
    q[0] = (q_t) {
        .id   = source,
        .prio = 0,
    };
    int qn = 1;
    
    while (qn > 0) {
        int u = q->id;
        int p = q->prio;
        // fprintf(stderr, "%d (%p %p)\n", u, q, q->next);
        pop(q, &qn);
        
        if (p > dist[u]) continue;
        
        for (edge_t * e = edges[u]; e; e = e->next) {
            // TODO: this might require int64
            int64_t d = dist[u] + e->cost;
            if (u != source) d += handlingTimes[u];
            if (d < dist[e->to]) {
                dist[e->to] = d;
                
                q[qn++] = (q_t) {
                    .id   = e->to,
                    .prio = dist[e->to],
                };
                decrease_prio(q, qn, qn - 1);
            }
        }
    }
    
    int * res = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        res[i] = (dist[i] < 0xFFFFFFFF) ? dist[i] : -1;
    }
    
    *result_count = n;
    return res;
}

