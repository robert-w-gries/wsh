#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/wsh_read.h"

#define WSH_BUF_SIZE 1024

wsh_input wsh_readln() {

    char *line = (char *) malloc(sizeof(char) * WSH_BUF_SIZE);
    if (NULL == line) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, WSH_BUF_SIZE, stdin);

    //remove trailing newline character
    int length = strlen(line) - 1;
    if (length > 0 && line[length] == '\n') {
        line[length] = '\0';
    }

    wsh_input input;
    input.text = line;
    input.length = length;

    return input;
}

