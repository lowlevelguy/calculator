#include "solver.h"
#include "structs.h"

float evaluate (stack postfix) {
    stack_d result_stack = NULL;
    Symbol token;
    double result, ret, op1, op2;
    
    while (postfix != NULL) {
        token = head(postfix);
        postfix = pop(postfix);

        if (token.type == NUMBER) {
            result_stack = push_d(result_stack, atof(token.s));
        } else if (token.type == OPERATOR) {
            op1 = head_d(result_stack);
            result_stack = pop_d(result_stack);
            op2 = head_d(result_stack);
            result_stack = pop_d(result_stack);

            switch(token.s[0]) {
                case '+':
                    result = op2 + op1;
                    break;
                case '-':
                    result = op2 - op1;
                    break;
                case '*':
                    result = op2 * op1;
                    break;
                case '/':
                    if (op1 == 0) {
                        fprintf(stderr, "[Solver][evaluate]: ERROR: Division by 0.\n");
                        exit(-1);
                    }
                    result = op2 / op1;
                    break;
                case '^':
                    if (op1 == 0 && op2 == 0) {
                        fprintf(stderr, "[Solver][evaluate]: ERROR: 0^0.\n");
                        exit(-1);
                    }
                    result = pow(op2, op1);
                    break;
            };
            result_stack = push_d(result_stack, result);

        }
    } 
    ret = head_d(result_stack);
    result_stack = pop_d(result_stack);

    return ret;
}

