int maxDistinctSubstringLengthInSessions(char * sessionString) {
    char set[256] = {0};
    int maxLen = 0;
    int curLen = 0;
    int start = 0;
    for (int i = 0; sessionString[i]; i++) {
        int c = sessionString[i];
        if (c == '*') {
            start = i;
            curLen = 0;
            memset(set, 0, sizeof(set));
            continue;
        }
        if (!set[c]) {
            set[c] = 1;
            curLen++;
            if (curLen > maxLen) maxLen = curLen;
            continue;
        }
        while (set[c]) {
            set[(int)sessionString[start]] = 0;
            start++;
        }
        set[c] = 1;
    }
    return maxLen;
}

