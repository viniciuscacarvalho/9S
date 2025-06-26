#include "parser.h"

int main (char argc, char*argv)
{

    init_parser();
    char cmd[] = "SAMPLE";
    parser(cmd);
    parser_dinit();
}