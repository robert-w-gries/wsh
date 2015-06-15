#include <stdio.h>
#include <stdlib.h>
#include "platform.h"

void init_platform(platform *p) {

	#ifdef _WIN32

		p->name = "Windows32";
        init_windows();

		#ifdef _WIN64
			p->name = "Windows64";
		#endif

	#elif __APPLE__

		#include "TargetConditionals.h"
        init_posix();

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
		init_posix();

	#elif __unix // all unices not caught above

		p->name = "Unix";
		init_posix();

	#elif __posix

		p->name = "Posix";
		init_posix();

    #else

        fprintf(stderr, "Error: Unsupported platform\n");
        exit(EXIT_FAILURE);

	#endif

}
