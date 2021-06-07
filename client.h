/*C Chat GUI Copyright (C) 2021 Marcel Walder
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
