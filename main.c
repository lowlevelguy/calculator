#include "parser.h"
#include "solver.h"
#include "structs.h"

int main() {

    char input[100];

    while (1) {
        printf(">>> ");
        fgets(input, 100, stdin);

        if (strncmp(input, "exit", 4) == 0) {
            return 0;
        }

        stack s = exp_tos(input);
        float res = evaluate(invert_stack(s));
        printf("%f\n", res);
    }
}
