#include <stdio.h>
#include <string.h>
#include "learn9cc.h"

/****** GLOBAL VARIABLES ******/
int pos;
char *user_input;
Vector *tokens;


/****** MAIN ******/
int main(int argc, char **argv) {
    if (argc != 2) {
        error("ERROR: The number of arguments is incorrect.");
        return 1;
    }

    if (strncmp(argv[1], "-test", 5) == 0) {
        runtest();
        return 0;
    }

    pos = 0;
    user_input = argv[1];
    tokens = (Vector *)tokenize(user_input);
    Node *node = expr();

    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    gen(node);

    printf("  pop rax\n");
    printf("  ret\n");

    return 0;
}
