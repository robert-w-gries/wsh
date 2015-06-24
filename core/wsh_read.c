#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/wsh_read.h"

#define WSH_BUF_SIZE 4096

static char * getinput(char *buffer, size_t size);

wsh_input wsh_readln() {

    int buf_size = WSH_BUF_SIZE;

    char *text = (char *)calloc(buf_size, sizeof(char));
    if (NULL == text) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    char buffer[WSH_BUF_SIZE] = { '\0' };
    while (NULL == getinput(buffer, WSH_BUF_SIZE)) {

        strcat(text, buffer);
        int length = buf_size;
        buf_size += WSH_BUF_SIZE;

        text = (char *)realloc(text, buf_size);
        if (NULL == text) {
            fprintf(stderr, "Error: out of memory\n");
            exit(EXIT_FAILURE);
        }

        text[length] = '\0';

    }

    strcat(text, buffer);

    //remove trailing newline character
    int length = strlen(text) - 1;
    if (length > 0 && text[length] == '\n') {
        text[length] = '\0';
    }

    wsh_input input;
    input.text = text;
    input.length = length;

    return input;
}

static char * getinput(char *buffer, size_t size) {

    size_t i = 0;
    int c = getchar();
    while ('\n' != c && EOF != c) {

        buffer[i++] = c;

        if (i >= size-1) {
            buffer[size-1] = '\0';
            return NULL;
        }

        c = getchar();

    }

    buffer[i] = '\0';
    return buffer;

}
