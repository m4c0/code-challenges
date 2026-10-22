int** mergeHighDefinitionIntervals(int intervals_rows, int intervals_columns, int** intervals, int* result_rows, int* result_columns) {
    if (intervals_rows == 0 || intervals_columns == 0) {
        *result_columns = *result_rows = 0;
        return NULL;
    }
    int ** result = malloc(sizeof(int *) * intervals_rows);
    *result_columns = 2;
    *result_rows = 0;
    assert(intervals_columns == 2);
    
    for (int i = 0; i < intervals_rows; i++) {
        int * last = malloc(2 * sizeof(int));
        last[0] = intervals[i][0];
        last[1] = intervals[i][1];

        for (int j = 0; j < *result_rows; j++) {
            if (result[j][0] < last[0]) continue;
            
            int * tmp = last;
            last = result[j];
            result[j] = tmp;
        }
        result[*result_rows] = last;
        (*result_rows)++;
    }
    
    int deleted = 0;
    int left = 0;
    for (int i = 1; i < *result_rows; i++) {
        if (result[left][1] >= result[i][1]) {
            free(result[i]);
            deleted++;
            continue;
        }
        if (result[left][1] >= result[i][0]) {
            result[left][1] = result[i][1];
            free(result[i]);
            deleted++;
            continue;
        }
        
        left++;
        result[left] = result[i];
    }
    
    *result_rows -= deleted;
    return result;
}

