#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "platform.h"
#include "../include/wsh_status.h"

static enum WSH_STATUS windows_change_directory(wsh_command *cmd);
static enum WSH_STATUS windows_create_process(wsh_command *cmd);
static enum WSH_STATUS windows_signal_handler();

static BOOL WINAPI ConsoleHandler(DWORD dwType);

void init_platform(platform *p) {

    p->name = "Windows";
    p->change_directory = &windows_change_directory;
    p->create_process = &windows_create_process;
    p->signal_handler = &windows_signal_handler;

}

static enum WSH_STATUS windows_change_directory(wsh_command *cmd) {

	char *path = cmd->args2D[1];

    // if no arguments, go to home directory
    if (1 >= cmd->nargs) {
        path = getenv("HOME");
	}

	if (0 != chdir(path)) {
        perror("wsh");
        return APPLICATION_FAILURE;
    }

	return OK;

}

static enum WSH_STATUS windows_create_process(wsh_command *cmd) {

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
        return APPLICATION_FAILURE;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return OK;

}

static enum WSH_STATUS windows_signal_handler() {

    if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE)) {
        fprintf(stderr, "Unable to install handler\n");
        return APPLICATION_FAILURE;
    }

    return OK;

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

