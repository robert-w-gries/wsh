#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../platform/platform.h"
#include "../include/wsh_parse.h"

#define WSH_TOK_BUFSIZE 8
#define WSH_TOK_DELIM " \t\r\n\a"

wsh_command wsh_parseln(wsh_input *input) {

    int position = 0, bufsize = WSH_TOK_BUFSIZE;

    char **tokens = (char **)malloc(sizeof(char *) * bufsize);
    if (tokens == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // copy input->text so that strtok doesn't destroy it
    char *input_copy = (char *)malloc(sizeof(char) * (input->length+1));
    if (NULL == input_copy) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    strncpy(input_copy, input->text, input->length);
    input_copy[input->length] = '\0';

    char *token = strtok(input->text, WSH_TOK_DELIM);
    while (token != NULL) {

        int token_length = strlen(token);
		tokens[position] = (char *)malloc(sizeof(char) * (token_length+1));
        if (NULL == tokens[position]) {
            fprintf(stderr, "Error: out of memory\n");
            exit(EXIT_FAILURE);
        }

        strcpy(tokens[position], token);
        tokens[position][token_length] = '\0';
        position++;

        if (position >= bufsize) {

            bufsize += WSH_TOK_BUFSIZE;

            tokens = (char **)realloc(tokens, sizeof(char *) * bufsize);
            if (tokens == NULL) {
                fprintf(stderr, "Error: out of memory\n");
                exit(EXIT_FAILURE);
            }

        }

        token = (char *) strtok(NULL, WSH_TOK_DELIM);

    }

    tokens[position] = NULL;

    wsh_command cmd;
    cmd.name = *tokens;
    cmd.nargs = position;
    cmd.args1D = input_copy;
    cmd.args2D = tokens;
    cmd.cmd_type = text;

    return cmd;
}
