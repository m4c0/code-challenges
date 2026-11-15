// Currently O(n2)

static int comp(const char * s1, const char * s2, int disp, int len) {
    for (int i = 0; s1[i]; i++) {
        if (s1[i] != s2[(i + disp) % len]) return 0;
    }
    return 1;
}

bool isNonTrivialRotation(char* s1, char* s2) {
    if (0 == strcmp(s1, s2)) return false;
    
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    if (l1 != l2) return false;
    
    for (int i = 1; i < l1; i++) {
        if (1 == comp(s1, s2, i, l1)) return true;
    }
    
    return false;
}

