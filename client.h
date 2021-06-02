
#ifndef CHATGUI_CLIENT_H
#define CHATGUI_CLIENT_H
#define BUFFER_SIZE 1000
#define SERVER_PORT 42069

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <winsock.h>
#include "include/strings.h"
#include <time.h>
#include <conio.h>

static void error_exit(char *errorMessage);
int sen(char buffer[BUFFER_SIZE], SOCKET client, time_t zeit);
int echo(SOCKET client,char echo_buffer[BUFFER_SIZE], time_t zeit);
SOCKET sock(char *text);
#endif //CHATGUI_CLIENT_H
