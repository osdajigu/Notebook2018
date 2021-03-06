int minimum_expression (string &s) {
    s = s + s;
    int len = s.size(), i = 0, j = 1, k = 0;
    while (i + k < len && j + k < len) {
        if (s[i+k] == s[j+k]) k++;
        else if (s[i+k] > s[j+k]) {
            i = i+k+1;
            if(i <= j) i = j+1; k = 0;
        }
        else if (s[i+k] < s[j+k]) {
            j = j+k+1;
            if(j <= i) j = i+1; k = 0;
        }
    }
    return min(i, j); //returns the start index of minimum rotation string
}
