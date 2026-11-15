int findSmallestMissingPositive(int orderNumbers_count, int* orderNumbers) {
    int i = 0;
    while (i < orderNumbers_count) {
        int n = orderNumbers[i];
        
        if (n - 1 == i) {
            i++;
            continue;
        }
        
        if (n >= orderNumbers_count || n <= 0) {
            orderNumbers[i] = orderNumbers[--orderNumbers_count];
            continue;
        }
        if (n - 1 < i) {
            orderNumbers[i] = orderNumbers[--orderNumbers_count];
            continue;
        }
        
        int last = orderNumbers[n - 1];
        if (last == n) {
            orderNumbers[i] = orderNumbers[--orderNumbers_count];
            continue;            
        }
        
        orderNumbers[i] = orderNumbers[n - 1];
        orderNumbers[n - 1] = n;
    }

    for (int i = 0; i < orderNumbers_count; i++) {
        int n = orderNumbers[i];
        if (n != i + 1) return i + 1;
    }
    return orderNumbers_count + 1;
}

