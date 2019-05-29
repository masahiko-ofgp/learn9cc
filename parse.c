#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "learn9cc.h"

extern int pos;
extern char *user_input;


/* Reporting Error */
void error(char *fmt, ...) {
    va_list ap;  /* argument pointer */
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

/* Reporting Error place */
void error_at(char *loc, char *msg) {
    pos = loc - user_input;
    fprintf(stderr, "%s\n", user_input);
    fprintf(stderr, "%*s", pos, "");
    fprintf(stderr, "^ %s\n", msg);
    exit(1);
}

Vector *tokenize(char *p) {
    Vector *v = new_vector();
    
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (strncmp(p, "==", 2) == 0) {
            add_token(v, TK_EQ, p);
            p++;
            p++;
            continue;
        }

        if (strncmp(p, "!=", 2) == 0) {
            add_token(v, TK_NE, p);
            p++;
            p++;
            continue;
        }

        if (strncmp(p, "<=", 2) == 0) {
            add_token(v, TK_LE, p);
            p++;
            p++;
            continue;
        }

        if (strncmp(p, ">=", 2) == 0) {
            add_token(v, TK_GE, p);
            p++;
            p++;
            continue;
        }

        if (*p == '<') {
            add_token(v, TK_LE, p);
            p++;
            continue;
        }

        if (*p == '>') {
            add_token(v, TK_GT, p);
            p++;
            continue;
        }

        if (*p == '(' || *p == ')') {
            add_token(v, *p, p);
            p++;
            continue;
        }

        if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            add_token(v, *p, p);
            p++;
            continue;
        }

        if (isdigit(*p)) {
            Token *t = add_token(v, TK_NUM, p);
            t->val = strtol(p, &p, 10);
            continue;
        }

        error_at(p, "Couldn't tokenize");
    }

    add_token(v, TK_EOF, p);
    return v;
}

int expect(int line, int expected, int actual) {
    if (expected == actual)
        return 0;
    fprintf(stderr, "%d: %d expected, but got %d\n",
            line, expected, actual);
    exit(1);
}

Token *add_token(Vector *v, int ty, char *input) {
    Token *t = malloc(sizeof(Token));
    t->ty = ty;
    t->input = input;
    vec_push(v, t);
    return t;
}
