#pragma once

#include "structs.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* ctoa (const char c);
Symbol itoS (int i);
stack exp_tos (const char* exp);