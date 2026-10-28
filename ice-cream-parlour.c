typedef struct node_s {
    int flavour;
    int cost;
} node_t;
static int node_comp(const void * a, const void * b) {
    const node_t * aa = a;
    const node_t * bb = b;
    if (aa->cost == bb->cost) {
        if (aa->flavour == bb->flavour) return 0;
        return aa->flavour > bb->flavour ? 1 : -1;
    }
    return aa->cost > bb->cost ? 1 : -1;
}

static node_t * find(node_t * in_ord, int l, int r, int who) {
    while (l <= r) {
        int mid = (l + r) / 2;
        
        int mc = in_ord[mid].cost;        
        if (mc == who) return in_ord + mid;
        if (mc > who) r = mid - 1;
        else l = mid + 1;
    }
    return NULL;
}

int* icecreamParlor(int m, int arr_count, int* arr, int* result_count) {
    node_t * in_ord = malloc(arr_count * sizeof(node_t));
    for (int i = 0; i < arr_count; i++) {
        in_ord[i] = (node_t) {
            .flavour = i + 1,
            .cost = arr[i],
        };
    }
    qsort(in_ord, arr_count, sizeof(node_t), node_comp);

    for (int i = 0 ; i < arr_count; i++) {
        node_t * a = in_ord + i;
        node_t * b;
        
        if (a->cost < m / 2) b = find(in_ord, i + 1, arr_count - 1, m - a->cost);
        else b = find(in_ord, 0, i - 1, m - a->cost);
        
        if (b != NULL) {
            *result_count = 2;
            
            static int res[2];
            res[0] = a->flavour < b->flavour ? a->flavour : b->flavour;
            res[1] = a->flavour < b->flavour ? b->flavour : a->flavour;
            return res; 
        }
    }

    *result_count = 0;
    return NULL;
}

