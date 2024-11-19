#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*===   SYMBOL  ===*/

enum S_ASSOC {
	LEFT,
	RIGHT,
	ASSOCIATIVE,
	UNDEFINED
};

enum S_TYPE {
    NUMBER,
    OPERATOR,
    PARENTHESES
};

struct Symbol {
    char* s;
    unsigned int priority;
    enum S_TYPE type;
    enum S_ASSOC assoc;
};
typedef struct Symbol Symbol;

/*===   STACKS  ===*/
/****   Symbol Stack    ****/

struct node_S {
	Symbol val;
	struct node_S* next;
};
typedef struct node_S* stack;

/****   Double Stack    ****/

struct node_d {
    double val;
    struct node_d* next;
};
typedef struct node_d* stack_d;


/*=== 	METHODS	===*/
/****   Symbol Stack    ****/
stack push (stack s, Symbol x);
stack pop (stack s);
stack invert_stack (stack s);
Symbol head (stack s);

/****   Double Stack    ****/
stack_d push_d(stack_d s, double x);
stack_d pop_d(stack_d s);
double head_d(stack_d s);
