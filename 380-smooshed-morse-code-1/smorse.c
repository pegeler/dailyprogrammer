#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_LEN 1000
#define CODE_LEN 4000

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

void smorse(char *s, char *t, int len) {
    int i, c;
    i = 0;
    while ((c = *(s++)) != '\0' && i + 4 < len)
        i += atom(t + i, c);
    memset(t + i, '\0', len - i);
}

void check(char *s, char *t) {
    char code[CODE_LEN];
    smorse(s, code, CODE_LEN);
    assert(strcmp(code, t) == 0);
}

int main(int argc, char *argv[]) {
    char input[LINE_LEN], code[CODE_LEN];
    
    check("sos", "...---...");
    check("daily", "-...-...-..-.--");
    check("programmer", ".--..-.-----..-..-----..-.");
    check("bits", "-.....-...");
    check("three", "-.....-...");
    printf("All checks passed. Enter a string to be encoded...\n");

    while (fgets(input, LINE_LEN, stdin) != NULL) {
        smorse(input, code, CODE_LEN);
        printf("%s\n", code);
    }
    
    return 0;
}
