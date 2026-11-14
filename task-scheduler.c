// partial

typedef struct histo_s {
    int id;
    int n;
} histo_t;

static void heapify(histo_t * q, int n, int i) {
    i++;
    q--;
    
    int l = 2 * i;
    int r = 2 * i + 1;
    
    while (1) {
        int s = i;
        if (l <= n && q[l].n > q[s].n) s = l;
        if (r <= n && q[r].n > q[s].n) s = r;
        
        if (s == i) break;
        
        histo_t tmp = q[s];
        q[s] = q[i];
        q[i] = tmp;
    }
}

static void heapup(histo_t * q, int n) {
    int i = n;
    q--; // 1-based
    
    while (i != 1 && q[i].n > q[i / 2].n) {
        histo_t tmp = q[i];
        q[i] = q[i / 2];
        q[i / 2] = tmp;
        i /= 2;
    }
}

int calculateMinimumTimeUnits(int tasks_count, int* tasks, int m, int k) {
    histo_t * histogram = calloc(100000, sizeof(histo_t));
    for (int i = 0; i < tasks_count; i++) {
        histogram[tasks[i]].id = tasks[i];
        histogram[tasks[i]].n++;
    }
    for (int i = 50000; i >= 0; i--) heapify(histogram, 100000, i);
    
    int h_count;
    for (h_count = 0; h_count < 100000 && histogram[h_count].id; h_count++) {}
    
    int * mach_avail = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) mach_avail[i] = m;
    
    histo_t * readd = malloc(k * sizeof(histo_t));
    
    int time = 0;
    while (h_count > 0) {
        time++;
        
        // fetch from queue
        
        histo_t p = histogram[0];
        histogram[0] = histogram[--h_count];
        heapify(histogram, h_count, 0);
        
        int readd_n = 0;
        
        int cm = m;
        while (cm > 0) {
            int to_run = mach_avail[p.id];
            if (p.n < to_run) to_run = p.n;
            if (cm  < to_run) to_run = cm;

            if (k > 0) mach_avail[p.id] -= cm;
            p.n -= cm;
            cm -= to_run;
            
            if (p.n > 0) {
                if (k > 0) {
                    // queue
                }
                if (mach_avail[p.id] > 0) {
                    readd[readd_n++] = p;
                }
            }
        }

        for (int i = 0; i < readd_n; i++) {
            histogram[h_count++] = readd[i];
            heapup(histogram, h_count);
        }
    }
    
    return time;
}

