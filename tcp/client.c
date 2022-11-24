// gcc -Wall -o client_tcp src/client.c [-lsocket –lnsl]
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUFFERSIZE 20
#define PORT 7923
#define SERVER "172.31.73.145"

int main ( void ) {

 int socketDescriptor;
 struct sockaddr_in serverAddress;
 socklen_t serverAddressLength;

 char sendBuffer[BUFFERSIZE];
 int sendBufferLength;

char readBuffer [BUFFERSIZE];
 int readBufferLength;
 
 if ( ( socketDescriptor = socket ( PF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
    perror ( "socket" ); 
    return -1;
 }

 bzero ( ( char * ) &serverAddress, sizeof ( serverAddress ) );

 serverAddress.sin_family = AF_INET;
 serverAddress.sin_port = htons ( PORT );
 serverAddress.sin_addr.s_addr = inet_addr ( SERVER );

 fgets ( sendBuffer, BUFFERSIZE , stdin );
 sendBufferLength = strlen ( sendBuffer );
 serverAddressLength = sizeof ( serverAddress );

 if ( connect ( socketDescriptor, (struct sockaddr *) &serverAddress, serverAddressLength ) < 0 ) {
    perror ( "connect" ); 
    return -1;
 }

 if ( send ( socketDescriptor, sendBuffer, sendBufferLength, 0 ) != sendBufferLength ) {
    perror ( "send" ); 
    return -1;
 }

if ( ( readBufferLength = recv ( socketDescriptor, readBuffer, BUFFERSIZE, 0 ) ) < 0 ) {
    perror ( "recvfrom" ); 
    return -1;
}

 readBuffer[readBufferLength] = 0;
 printf ( "%s\n", readBuffer );

 close ( socketDescriptor );

 return 0;
}