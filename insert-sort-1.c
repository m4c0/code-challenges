static void print(int n, int *arr) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
}
void insertionSort1(int n, int arr_count, int* arr) {
    if (arr_count < 1) return;
    int arr_n = arr[n - 1];
    int i;
    for (i = n - 2; i >= 0; i--) {
        if (arr[i] > arr_n) {
            arr[i + 1] = arr[i];
            print(n, arr);
        } else {
            break;
        }
    }
    arr[i + 1] = arr_n;
    print(n, arr);
}


