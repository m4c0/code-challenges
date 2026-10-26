int** findNextGreaterElementsWithDistance(int readings_count, int* readings, int* result_rows, int* result_columns) {
    int ** result = malloc(readings_count * sizeof(int **));
    *result_columns = 2;
    *result_rows = readings_count;
    
    int * stack = malloc(readings_count * sizeof(int));
    int * top = stack;
    
    for (int i = 0; i < readings_count; i++) {
        result[i] = malloc(2 * sizeof(int));
        result[i][0] = result[i][1] = -1;
    }
    
    for (int i = 0; i < readings_count; i++) {
        while (top != stack && readings[top[-1]] < readings[i]) {
            int p = *--top;
            result[p][0] = readings[i];
            result[p][1] = i - p;
        }
        *top++ = i;
    }
    
    return result;
}

