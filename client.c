#include "client.h"


SOCKET sock(char *text) {
    SOCKET client;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    int retcode;
    time_t zeit;

    WORD wVersionRequested = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        printf("Fehler beim Socket erstellen\n");
        exit(-1);
    }
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    retcode = connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (retcode < 0) {
        sprintf(text,"Verbindung fehlgeschlagen\r\n");
    } else {
        sprintf(text, "Verbindung zu %s:%hu erfolgreich hergestellt.\r\n", inet_ntoa(server_addr.sin_addr),
                ntohs(server_addr.sin_port));
    }
    return client;
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
        printf("Verbindung zum Server verloren\n");
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