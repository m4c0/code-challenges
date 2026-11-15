bool isAlphabeticPalindrome(char* code) {
    if (!code) return false;
    if (!*code) return false;
    
    int l = 0;
    int r = strlen(code) - 1;
    while (l < r) {
        char cl = code[l] | 0x20;
        if (cl < 'a' || cl > 'z') {
            l++;
            continue;
        }
        
        char cr = code[r] | 0x20;
        if (cr < 'a' || cr > 'z') {
            r--;
            continue;
        }

        if (cr != cl) return 0;
        
        l++;
        r--;
    }
    return 1;
}

