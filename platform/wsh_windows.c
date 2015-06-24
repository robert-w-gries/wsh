#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "platform.h"
#include "../include/wsh_status.h"

static char * windows_get_current_directory(char *buffer, int buffer_size);
static int ListDirectoryContents(const char *dir);
static BOOL WINAPI ConsoleHandler(DWORD dwType);

void init_platform(platform *p) {

    p->name = "Windows";

    p->cwd = (char *)malloc(MAX_PATH * sizeof(char));
    if (NULL == p->cwd) {
        fprintf(stderr, "Error: Out of memory\n");
        exit(EXIT_FAILURE);
    }

    get_current_directory(p->cwd, MAX_PATH);

}

enum WSH_STATUS change_directory(wsh_command *cmd) {

    char *path = cmd->args2D[1];

    // if no arguments, go to home directory
    if (1 == cmd->nargs) {
        path = getenv("USERPROFILE");
    }

    if (0 != _chdir(path)) {
        perror("wsh");
        return APPLICATION_FAILURE;
    }

    return OK;

}

enum WSH_STATUS create_process(wsh_command *cmd) {

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    ZeroMemory(&pi, sizeof(pi));

    // Start the child process.
    if (!CreateProcess(NULL, //application name
        cmd->args1D,      // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", (int)GetLastError());
        return APPLICATION_FAILURE;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return OK;

}

char * get_current_directory() {

    windows_get_current_directory(my_platform.cwd, MAX_PATH);
    return my_platform.cwd;

}

static char * windows_get_current_directory(char *buffer, int buffer_size) {

    int size = buffer_size > MAX_PATH ? MAX_PATH : buffer_size;

    if (0 == GetCurrentDirectory(size, buffer)) {
        fprintf(stderr, "Could not retrieve path\n");
        exit(EXIT_FAILURE);
    }

    return buffer;

}

enum WSH_STATUS list_directory_contents(wsh_command *cmd) {

    // TODO: command options

    // list current folder's contents if no arguments passed
    if (cmd->nargs <= 2) {
        
        char *dir = (1 == cmd->nargs) ? "." : cmd->args2D[1];
        windows_list_directory_contents(dir);

        printf("\n");
        return OK;
    }

    // list contents of all directories
    // TODO: recurse through '..'; testcase = 'ls .. test ../..'
    int i = 1;
    for (i = 1; i < cmd->nargs; i++) {
        printf("%s:\n", cmd->args2D[i]);
        windows_list_directory_contents(cmd->args2D[i]);
        printf("\n");
    }

    return OK;

}

static int windows_list_directory_contents(const char *dir) {

    // path specifying all files/directories
    char path[MAX_PATH];
    sprintf(path, "%s\\*.*", dir);

    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;
    if ((hFind = FindFirstFile(path, &fdFile)) == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "ls: %s: No such file or directory\n", dir);
        return 0;
    }

    do {

        if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("%s\n", fdFile.cFileName); // directory
        }
        else {
            printf("%s\n", fdFile.cFileName); // file
        }

    } while (FindNextFile(hFind, &fdFile));

    FindClose(hFind);
    return 1;
}

enum WSH_STATUS signal_handler() {

    if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE)) {
        fprintf(stderr, "Unable to install handler\n");
        return APPLICATION_FAILURE;
    }

    return OK;

}

static BOOL WINAPI ConsoleHandler(DWORD dwType) {

    switch(dwType) {

        case CTRL_C_EVENT: {
            printf("ctrl-c\n");
            exit(EXIT_FAILURE);
            break;
        }

        case CTRL_BREAK_EVENT: {
            printf("break\n");
            exit(EXIT_FAILURE);
            break;
        }

        default: {
            printf("Some other event\n");
            break;
        }

    }

    return TRUE;
}

