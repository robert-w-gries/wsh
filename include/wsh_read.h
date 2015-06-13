#ifndef _WSH_READ_H_
#define _WSH_READ_H_

struct wsh_input_struct {
	char *text;
	int length;
} typedef wsh_input;

wsh_input * wsh_readln();

#endif
