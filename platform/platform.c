#include <stdio.h>
#include <stdlib.h>
#include "platform.h"

#ifdef _WIN32
#include "windows/wsh_windows.h"
#elif __linux
#include "wsh_posix.h"
#endif

void init_platform(platform *p) {

	#ifdef _WIN32

		p->name = "Windows32";
		p->create_process = &windows_create_process;
		p->signal_handler = &windows_signal_handler;

		#ifdef _WIN64
			p->name = "Windows64";
		#endif

	#elif __APPLE__

		#include "TargetConditionals.h"
		p->create_process = &posix_create_process;

		#if TARGET_IPHONE_SIMULATOR
			p->name = "Iphone Simulator";
		#elif TARGET_OS_IPHONE
			p->name = "Iphone";
		#elif TARGET_OS_MAC
			p->name = "MacOS";
		#else
            fprintf(stderr, "Error: Unsupported platform\n");
			exit(EXIT_FAILURE);
		#endif

	#elif __linux

		p->name = "Linux";
		p->create_process = &posix_create_process;

	#elif __unix // all unices not caught above

		p->name = "Unix";
		p->create_process = &posix_create_process;

	#elif __posix

		p->name = "Posix";
		p->create_process = &posix_create_process;

    #else

        fprintf(stderr, "Error: Unsupported platform\n");
        exit(EXIT_FAILURE);

	#endif

}
