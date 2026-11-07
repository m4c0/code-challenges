static void print(uint64_t * res) {
    int last;
    for (last = 100-1; last >= 0; last--) {
        if (res[last] != 0) break;
    }
    printf("%ld", res[last]);
    for (int i = last - 1; i >= 0; i--) {
        printf("%09ld", res[i]);
    }
    puts("");
}

void extraLongFactorials(int n) {
    uint64_t res[100] = {0};
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
        unsigned rem = 0;
        for (int j = 0; j < 100; j++) {
            uint64_t v = res[j] * i + rem;
            rem = v / 1000000000;
            res[j] = v % 1000000000;
        }
    }
    print(res);
}


