int* rotLeft(int a_count, int* a, int d, int* result_count) {
    int * res = malloc(a_count * sizeof(int));
    *result_count = a_count;
    
    for (int i = 0; i < a_count; i++) {
        int j = (i + a_count - d) % a_count;
        res[j] = a[i];
    }
    
    return res;
}

