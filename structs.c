#include "structs.h"

stack push (stack s, Symbol x) {
    stack ns = malloc(sizeof(struct node_S));
    ns->val = x;
    ns->next = s;

    return ns;
}

stack pop (stack s) {
    if (s == NULL) return NULL;

    stack ns = s->next;
    free(s);
    return ns;
}

Symbol head (stack s) {
    if (s == NULL) {
        Symbol empty = {"", 0, 0, 0};
        return empty;
    }

    return s->val;
}

// stack_d
stack_d push_d (stack_d s, double x) {
    stack_d ns = malloc(sizeof(struct node_d));
    ns->val = x;
    ns->next = s;

    return ns;
}

stack_d pop_d (stack_d s) {
    if (s == NULL) return NULL;

    stack_d ns = s->next;
    free(s);
    return ns;
}

double head_d (stack_d s) {
    if (s == NULL) return 0;
    return s->val;
}

stack invert_stack (stack s) {
    stack ns = NULL;

    while (s != NULL) {
        ns = push(ns, head(s));
        s = pop(s);
    }
    return ns;
}
