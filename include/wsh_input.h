#ifndef _WSH_INPUT_H_
#define _WSH_INPUT_H_

struct wsh_input_struct {
    char *text;
    int length;
    int has_newline;
} typedef wsh_input;

void clear_input(wsh_input *input);

#endif
