static int compare(const void * a, const void * b) {
    int ai = *(const int *)a;
    int bi = *(const int *)b;
    if (ai > bi) return 1;
    if (ai < bi) return -1;
    return 0;
}
int findLongestArithmeticProgression(int arr_count, int* arr, int k) {
    if (arr_count == 0) return 0;
    if (k == 0) return 0;
    
    qsort(arr, arr_count, sizeof(int), compare);
    
    int * used = calloc(1, sizeof(int) * arr_count);
    
    int64_t kl = k > 0 ? k : -k;

    int max = 0;
    for (int i = 0; i < arr_count; i++) {   
        if (used[i]) continue;
             
        int seq = 1;
        int64_t next = (int64_t)arr[i] + k;
        for (int j = i + 1; j < arr_count; j++) {
            if (used[j]) continue;
            
            if ((int64_t)arr[j] < next) continue;
            if ((int64_t)arr[j] == next) {
                seq++;
                next += kl;
                used[j] = 1;
            } else {
                break;
            }
        }
        if (seq > max) max = seq;
    }
    return max;
}

