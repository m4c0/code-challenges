#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char * a = "kitten";
  const char * b = "sitting";

  if (!*a) return strlen(b);
  if (!*b) return strlen(a);

  int d0[100];
  int d1[100];

  int * r0 = d0;
  int * r1 = d1;

  // Make them 1-based
  a--;
  b--;

  for (int i = 0; a[i]; i++) {
    r0[i] = i;
  }

  int dist = 0;
  for (int j = 1; b[j]; j++) {
    r1[0] = j;
    for (int i = 1; a[i]; i++) {
      int d = a[i] == b[j] ? 0 : 1;
      d += r0[i - 1];
      if (d > 1 + r1[i - 1]) d = 1 + r1[i - 1];
      if (d > 1 + r0[i])     d = 1 + r0[i];
      dist = r1[i] = d;
    }
    int * tmp = r1;
    r1 = r0;
    r0 = tmp;
  }

  printf("%d\n", dist);
  return 0;
}
