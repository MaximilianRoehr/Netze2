// gcc -Wall -o client_udp client.c [-lsocket –lnsl]
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUFFERSIZE 200
#define PORT 4680
#define SERVER "172.31.73.145"

int main ( void ) {

int socketDescriptor;
struct sockaddr_in serverAddress;

socklen_t serverAddressLength;
char sendBuffer[BUFFERSIZE];
int sendBufferLength;

 
 //create socket
 if ( ( socketDescriptor = socket ( PF_INET, SOCK_DGRAM, 0 ) ) < 0 ) {
    perror ( "socket" ); 
    return -1;
 }
 
 bzero ( ( char * ) &serverAddress, sizeof ( serverAddress ) );

 //config for destination
 serverAddress.sin_family = AF_INET;
 serverAddress.sin_port = htons ( PORT );
 serverAddress.sin_addr.s_addr = inet_addr ( SERVER );

 //write into buffer
 fgets( sendBuffer, BUFFERSIZE , stdin );
 sendBufferLength = strlen ( sendBuffer );
 serverAddressLength = sizeof ( serverAddress );

 // send buffer to server 
 if ( sendto ( socketDescriptor, sendBuffer, sendBufferLength, 0,(struct sockaddr *) &serverAddress, serverAddressLength) != sendBufferLength ) {
    perror ( "sendto" );
    return -1;
 }


 char readBuffer [BUFFERSIZE];
 int readBufferLength;


 readBufferLength = recvfrom ( socketDescriptor, readBuffer, BUFFERSIZE, 0,(struct sockaddr *) &serverAddress, &serverAddressLength );

 if ( readBufferLength < 0 ) {
    perror ( "recvfrom" ); 
    return -1;
 }

 //printing readBuffer
 readBuffer[readBufferLength] = 0;
 printf ( "message from server: %s\n", readBuffer );

 //close socket
 close ( socketDescriptor );

 return 0;
}
