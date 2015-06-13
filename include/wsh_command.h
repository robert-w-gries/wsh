#ifndef _WSH_COMMAND_H_
#define _WSH_COMMAND_H_

enum OUTPUT_TYPE {
	text,
	unicode,
	image,
	audio,
	video
};

struct wsh_command_struct {
	char *name;
	int nargs;
	char *args1D;
	char **args2D;
	enum OUTPUT_TYPE cmd_type;
} typedef wsh_command;

#endif
