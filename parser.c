#include "parser.h"

// char to char*
char* ctoa (const char c) {
    char* s = malloc(sizeof(char) * 2);
    s[0] = c;
    s[1] = '\0';

    return s;
}

// int to Symbol
Symbol itoS (int i) {
    Symbol S;

    char* nb = malloc(sizeof(char) * 11); // INT_MAX is 10 digits long (in base 10)
    snprintf(nb, 11, "%d", i);

    S.s = nb;
    S.priority = 0;
    S.type = NUMBER;
    S.assoc = UNDEFINED;

    return S;
}

// expression to output stack
// produces PREfix notation, and not POSTfix
stack exp_tos (const char* exp) {
    stack op = NULL;
    stack out = NULL;
    int nb;
    Symbol ptheses[] = {
        {"(", 4, PARENTHESES, UNDEFINED},
        {")", 4, PARENTHESES, UNDEFINED}
    };
    Symbol op_codes[] = {
        {"-", 1, OPERATOR, LEFT},
        {"+", 1, OPERATOR, ASSOCIATIVE},
        {"*", 2, OPERATOR, ASSOCIATIVE},
        {"/", 2, OPERATOR, LEFT},
        {"^", 3, OPERATOR, LEFT},
    };

    for (int i = 0; i < (int)strlen(exp); i++) {
        nb = 0;
		while(exp[i] == ' ') i++;

        // If a number is read
        if (isdigit(exp[i])) {
            while (isdigit(exp[i])) {
                nb = nb*10 + (int)(exp[i] - '0');
                i++;
            }

            out = push(out, itoS(nb));
            i--;
            goto CONT;
        }

        // If an operator is read
        for (int j = 0; j < (int)(sizeof(op_codes)/sizeof(Symbol)); j++) {
            if (exp[i] == op_codes[j].s[0]) {
                while (
                    head(op).s[0] != '('
                    && (
                        head(op).priority > op_codes[j].priority
                        || (
                            head(op).priority == op_codes[j].priority
							&& op_codes[j].assoc == LEFT
                        )
                    )
                ) {
                    // pop head out of operator stack and into output stack
					out = push(out, head(op));
					op = pop(op);
                }

				// push into output stack
                op = push(op, op_codes[j]);
                goto CONT;
            }
        }

        if (exp[i] == '(') {
            op = push(op, ptheses[0]);
            goto CONT;
        }

        if (exp[i] == ')') {
            
            while (head(op).s[0] != '(') {
                if (op == NULL) {
                    fprintf(stderr, "[Parser][exp_tos]: ERROR: Mismatched parentheses.\n");
                    exit(-1);
                }
                out = push(out, head(op));
                op = pop(op);
            }

            if (head(op).s[0] != '(') {
                fprintf(stderr, "[Parser][exp_tos]: ERROR: Mismatched parentheses.\n");
                exit(-1);
            }
            op = pop(op);
            goto CONT;
        }

        // If it's neither a digit, nor an operator, nor a parentheses, then return an error
        if (exp[i] != '\n') {
            fprintf(stderr, "[Parser][exp_tos]: ERROR: Character `%c` is unsupported.\n", exp[i]);
            exit(-1);
        }
        
        CONT:
        continue; 
    }

    while (op != NULL) {
		out = push(out, head(op));
		op = pop(op);
	}

    return out;
}
