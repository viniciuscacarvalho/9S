
#ifndef __PARSER_H__
#define  __PARSER_H__

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_codes.h"
#include "command_callbacks.h"

typedef void* (*callback_pointer) (void*);

typedef struct command_s
{
    char* command_name;
    callback_pointer command_callback;
    char parameter_number;
}command_t;

int init_parser();
int parser(char * cmd);
int parser_dinit();
#endif