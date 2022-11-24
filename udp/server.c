// gcc -Wall -o server_udp server.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUFFERSIZE 200
#define PORT 4680

int main ( void ) {

 int socketDescriptor;
 struct sockaddr_in serverAddress, clientAddress;
 socklen_t clientAddressLength;
 char readBuffer [BUFFERSIZE];
 int readBufferLength;

 //create socket
 if ( ( socketDescriptor = socket ( PF_INET, SOCK_DGRAM, 0 ) ) < 0 ) {
    perror ( "socket" ); 
    return -1;
 }

 bzero ( ( char * ) &serverAddress, sizeof ( serverAddress ) );

 //config for socket 
 serverAddress.sin_family = AF_INET;
 serverAddress.sin_port = htons ( PORT );
 serverAddress.sin_addr.s_addr = htonl ( INADDR_ANY );

 //binding address
 if ( bind ( socketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) {
    perror ( "bind" ); 
    return -1;
}

 clientAddressLength = sizeof ( clientAddress );
 //receive data
 readBufferLength = recvfrom ( socketDescriptor, readBuffer, BUFFERSIZE, 0,(struct sockaddr *) &clientAddress, &clientAddressLength );

 if ( readBufferLength < 0 ) {
    perror ( "recvfrom" ); 
    return -1;
 }
 
// send buffer to client
if ( sendto ( socketDescriptor, readBuffer, readBufferLength, 0,(struct sockaddr *) &clientAddress, clientAddressLength) != readBufferLength ) {
    perror ( "sendto" );
    return -1;
}

 //printing readBuffer
 readBuffer[readBufferLength] = 0;
 printf ( "%s\n", readBuffer );

 //close socket
 close ( socketDescriptor );

 return 0;
}
