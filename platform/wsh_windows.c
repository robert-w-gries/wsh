#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "wsh_windows.h"

static BOOL WINAPI ConsoleHandler(DWORD dwType);

int windows_create_process(wsh_command *cmd) {

	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    ZeroMemory(&pi, sizeof(pi));

    // Start the child process.
    if( !CreateProcess( NULL, //application name
        cmd->args1D,      // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    )
    {
        printf( "CreateProcess failed (%d).\n", (int) GetLastError() );
        return -1;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;

}

void windows_signal_handler() {

	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE)) {
		fprintf(stderr, "Unable to install handler\n");
		return;
	}
}

static BOOL WINAPI ConsoleHandler(DWORD dwType) {

    switch(dwType) {
		case CTRL_C_EVENT:
			printf("ctrl-c\n");
			exit(EXIT_FAILURE);
			break;
		case CTRL_BREAK_EVENT:
			printf("break\n");
			exit(EXIT_FAILURE);
			break;
		default:
			printf("Some other event\n");
			break;
	}

    return TRUE;
}
