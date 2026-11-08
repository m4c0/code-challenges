#include <stdio.h>
#include <stdlib.h>

static void heapify(int * heap, int n, int i) {
  int l = 2 * i;
  int r = l + 1;

  int s = (l <= n && heap[l] < heap[i]) ? l : i;
  if (r <= n && heap[r] < heap[s]) s = r;

  if (s != i) {
    int tmp = heap[i];
    heap[i] = heap[s];
    heap[s] = tmp;
    heapify(heap, n, s);
  }
}
static void heapify_all(int * heap, int n) {
  for (int i = n / 2; i >= 1; i--) {
    heapify(heap - 1, n, i);
  }
}

int main() {
  int n = 100;

  int * heap = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    heap[i] = rand() % 10000;
  }

  // Sortheap

  heapify_all(heap, n);
  for (int i = n - 1; i >= 0; i--) {
    int tmp = heap[i];
    heap[i] = heap[0];
    heap[0] = tmp;
    heapify(heap - 1, i, 1);
  }
  for (int i = 0; i < n; i++) {
    printf("%d ", heap[i]);
  }
  puts("");
}
