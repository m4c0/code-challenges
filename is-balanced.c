char* isBalanced(char* s) {
    char * open = malloc(strlen(s));
    int open_i = 0;
    
    for (int i = 0; s[i]; i++) {
        switch (s[i]) {
            case '(':
                open[open_i++] = ')';
                break;
            case '[':
                open[open_i++] = ']';
                break;
            case '{':
                open[open_i++] = '}';
                break;
            case ')':
            case ']':
            case '}':
                if (open_i == 0) return "NO";
                if (open[--open_i] != s[i]) return "NO";
                break;
            default:
                return "NO";
        }
    }
    return open_i == 0 ? "YES" : "NO";
}

