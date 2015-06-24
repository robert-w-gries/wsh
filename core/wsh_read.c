#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/wsh_read.h"

#define WSH_BUF_SIZE 4096

static char * getinput(char *buffer, size_t size);

/*
Read a line of input from terminal
@return struct containing text and length
*/
wsh_input wsh_readln() {

    int buf_size = WSH_BUF_SIZE;

    char *text = (char *)calloc(buf_size, sizeof(char));
    if (NULL == text) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // grab all input from stdin
    char buffer[WSH_BUF_SIZE] = { '\0' };
    while (NULL == getinput(buffer, WSH_BUF_SIZE)) {

        strcat(text, buffer);

        // increase buffer size and reallocate memory
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

    wsh_input input;
    input.text = text;
    input.length = strlen(text)+1;

    return input;
}

/* 
Grab input until EOF, newline char, or buffer full
@buffer stores the read characters from stdin
@size the buffer's size
@return On success, function returns buffer.
        If buffer is filled before EOF or newline, returns NULL
*/
static char * getinput(char *buffer, size_t size) {

    size_t i = 0;
    int c = getchar();
    while ('\n' != c && EOF != c) {

        buffer[i++] = c;

        // buffer is filled so we null-terminate it
        if (i >= size-1) {
            buffer[size-1] = '\0';
            return NULL;
        }

        c = getchar();

    }

    buffer[i] = '\0';
    return buffer;

}
