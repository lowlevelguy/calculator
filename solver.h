#pragma once

#include "structs.h"
#include "parser.h"
#include <limits.h>

float evaluate(stack out);
char* dtoa(double num);
Symbol ftoS (double f);
