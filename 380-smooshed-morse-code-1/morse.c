#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_LEN 100
#define CODE_LEN 500

char MORSE[][5] = {
    {".-"}, {"-..."}, {"-.-."}, {"-.."},
    {"."}, {"..-."}, {"--."}, {"...."},
    {".."}, {".---"}, {"-.-"}, {".-.."},
    {"--"}, {"-."}, {"---"}, {".--."},
    {"--.-"}, {".-."}, {"..."}, {"-"},
    {"..-"}, {"...-"}, {".--"}, {"-..-"},
    {"-.--"}, {"--.."}
};

int atom(char *t, char a) {
    int i=0;
    char *m;
    if (a >= 'a' && a <= 'z')
        for (m = MORSE[a - 'a']; m[i] != '\0'; i++)
            t[i] = m[i];
    return i;
}

void morse(char *s, char *t, int len) {
    int i, c;
    i = 0;
    while ((c = *(s++)) != '\0' && i + 5 < len) {
        i += atom(t + i, c);
        *(t + i++) = ' ';
    }
    if (i > 0)
        i--;
    memset(t + i, '\0', len - i);
}

int main(int argc, char *argv[]) {
    char input[LINE_LEN], code[CODE_LEN];
    
    while (fgets(input, LINE_LEN, stdin) != NULL) {
        morse(input, code, CODE_LEN);
        printf("%s\n", code);
    }
    
    return 0;
}
