static int solve(const char * s, int k, char exp) {
    int max = 0;
    int flips = 0;
    int l = 0;
    
    for (int r = 0; s[r]; r++) {
        char c = r % 2 ? (exp ^ 1) : exp;
        if (s[r] != c) flips++;
        
        while (flips > k) {
            char c = l % 2 ? (exp ^ 1) : exp;
            if (s[l] != c) flips--;
            l++;
        }
        
        int len = r - l + 1;
        if (len > max) max = len;
    }

    return max;
}

int longestAlternatingSubstring(char* s, int k) {
    if (!*s) return 0;
    
    int p0 = solve(s, k, '0');
    int p1 = solve(s, k, '1');
    
    return p0 > p1 ? p0 : p1;
}

