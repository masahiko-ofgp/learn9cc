#ifndef _LEARN9CC_H_
#define _LEARN9CC_H_

/* Token Type */
enum {
    TK_NUM = 256,
    TK_EOF,
    TK_EQ,
    TK_NE,
    TK_LT,
    TK_GT,
    TK_LE,
    TK_GE,
};

typedef struct Token {
    int ty;
    int val;  /* "ty=TK_NUM" only */
    char *input; /* If error, this value is used. */
} Token;

typedef struct Vector {
    void **data;
    int len;
    int capacity;
} Vector;

/* NODE TYPE */
enum {
    ND_NUM = 256,
    ND_EQ,
    ND_NE,
    ND_LT,
    ND_GT,
    ND_LE,
    ND_GE,
};

typedef struct Node {
    int ty;
    struct Node *lhs;
    struct Node *rhs;
    int val;  /* "ty=ND_NUM" only */
} Node;

/****** PROTO TYPE ******/
void error(char *fmt, ...);
void error_at(char *loc, char *msg);
Node *new_node(int ty, Node *lhs, Node *rhs);
Node *new_node_num(int val);
int consume(int ty);
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *term();
void gen(Node *node);
Vector *new_vector();
void vec_push(Vector *vec, void *elem);
int expect(int line, int expected, int actual);
void runtest();
Vector *tokenize(char *p);
Token *add_token(Vector *v, int ty, char *input);

#endif
