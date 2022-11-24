// gcc -Wall -o server_tcp src/server.c [-lsocket –lnsl]
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUFFERSIZE 20
#define PORT 7923

int main ( void ) {

 int socketDescriptor, connectedSocketDescriptor;
 struct sockaddr_in serverAddress, clientAddress;
 socklen_t clientAddressLength;
 char readBuffer [BUFFERSIZE];
 int readBufferLength;

 if ( ( socketDescriptor = socket ( PF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
    perror ( "socket" ); 
    return -1;
 }

 bzero ( ( char * ) &serverAddress, sizeof ( serverAddress ) );

 serverAddress.sin_family = AF_INET;
 serverAddress.sin_port = htons ( PORT );
 serverAddress.sin_addr.s_addr = htonl ( INADDR_ANY );
 
 if ( bind ( socketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) {
    perror ( "bind" ); 
    return -1;
 }

 listen ( socketDescriptor, 5 );

 clientAddressLength = sizeof ( clientAddress );

 if ((connectedSocketDescriptor = accept ( socketDescriptor, (struct sockaddr *) &clientAddress, &clientAddressLength )) < 0) {
    perror ( "accept" ); 
    return -1;
 }
 
 if ( ( readBufferLength = recv ( connectedSocketDescriptor, readBuffer, BUFFERSIZE, 0 ) ) < 0 ) {
    perror ( "recvfrom" ); 
    return -1;
 }

  if ( send ( connectedSocketDescriptor, readBuffer, readBufferLength, 0 ) != readBufferLength ) {
    perror ( "send" ); 
    return -1;
 }

 readBuffer[readBufferLength] = 0;
 printf ( "%s\n", readBuffer );

 close ( connectedSocketDescriptor);
 close ( socketDescriptor );

 return 0;
}