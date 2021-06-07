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

#include "server.h"
int close=0;

SOCKET sock(char *text) {

    SOCKET sock, fd;
    unsigned int len;
    char echo_buffer[BUFFER_SIZE] = {0};
    time_t zeit;
    struct sockaddr_in server_addr, client;
    int retcode;

    WORD wVersionRequested = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        sprintf(text,"Fehler beim Socket erstellen\n");
        return 1;
    }
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);
    retcode = bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));


    if (retcode < 0) {
        sprintf(text,"Socket konnte nicht gebunden werden!\n");
        return 0;
    } else {
        sprintf(text,"Socket erfolgreich erstellt und gebunden!\r\n");
        listen(sock, 2);
        len = sizeof(client);
        fd = accept(sock, (struct sockaddr *) &client, &len);
        if(INVALID_SOCKET == fd){
            sprintf(text,"Fehler bei accept");
        }else{
            sprintf(text,"Client verbunden: %s\r\n", inet_ntoa(client.sin_addr));
        }
        closesocket(sock);
        return fd;
    }
}
int echo(SOCKET client, char echo_buffer[BUFFER_SIZE], time_t zeit) {
    int recv_size = -1;
    int close = 0;
    u_long len;
    char buffer2[100];

    bzero(echo_buffer, sizeof *(echo_buffer));
    ioctlsocket(client, FIONREAD, &len);
    if (len) {
        recv_size = recv(client, buffer2, BUFFER_SIZE, 0);
        if (strcmp(buffer2, "exit") == 0) {
            sprintf(echo_buffer,"\r\nServer hat die Verbindung getrennt\r\n");
            closesocket(client);
            return close=1;
        } else {
            echo_buffer[recv_size] = '\0';
            time(&zeit);
            sprintf(echo_buffer,"Nachrichten vom Server: %s \t%s\r\n", buffer2, ctime(&zeit));
        }
    } else {
        return close;
    }
}
int sen(char buffer[BUFFER_SIZE], SOCKET client, time_t zeit) {
    int echo_len = 0;
    int close = 0;
    char buffer2[100];
    strcpy(buffer2,buffer);
    echo_len = strlen(buffer);
    if (send(client, buffer, echo_len, 0) != echo_len) {
        sprintf(buffer,"Verbindung zum Server verloren\n");
        return close=1;
    } else {
        time(&zeit);
        sprintf(buffer,"An Server gesendet: %s \t%s\r\n", buffer2, ctime(&zeit));
    }
    if (strcmp(buffer2, "exit") == 0) {
        closesocket(client);
        sprintf(buffer,"\r\nDie Verbindung wurde getrennt\r\n");
        return close=1;
    }else{
        Sleep(100);
        return close;
    }

}
void error_exit(char *errorMessage) {
    fprintf(stderr, "%s: %d\n", errorMessage, WSAGetLastError());
    exit(EXIT_FAILURE);
}