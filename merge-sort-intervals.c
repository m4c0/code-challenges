int int_comp(const void * a, const void * b) {
    const int * aa = *(const int * const *)a;
    const int * bb = *(const int * const *)b;
    
    return aa[0] != bb[0]
        ? aa[0] - bb[0]
        : aa[1] - bb[1];
}
 
int** mergeHighDefinitionIntervals(int intervals_rows, int intervals_columns, int** intervals, int* result_rows, int* result_columns) {
    if (intervals_rows == 0 || intervals_columns == 0) {
        *result_columns = *result_rows = 0;
        return NULL;
    }

    qsort(intervals, intervals_rows, sizeof(int *), int_comp);

    int ** result = malloc(sizeof(int *) * intervals_rows);
    int n = 0;
    for (int i = 0; i < intervals_rows; i++) {
        int * interval = intervals[i];
        if (n == 0) {
            result[n++] = interval;
            continue;
        }
        int * last = result[n - 1];
        if (last[1] >= interval[0]) {
            if (interval[1] > last[1]) last[1] = interval[1];
            continue;
        }
        result[n++] = interval;
    }

    *result_columns = 2;
    *result_rows = n;
    return result;
}

