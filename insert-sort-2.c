static void print(int n, int *arr) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
}
static void insertionSort1(int n, int* arr) {
    if (n < 1) return;
    int arr_n = arr[n - 1];
    int i;
    for (i = n - 2; i >= 0; i--) {
        if (arr[i] > arr_n) {
            arr[i + 1] = arr[i];
        } else {
            break;
        }
    }
    arr[i + 1] = arr_n;
}
void insertionSort2(int n, int arr_count, int* arr) {
    for (int i = 2; i <= n; i++) {
        insertionSort1(i, arr);
        print(n, arr);
    }
}

