/*
** client.c for client in /home/samuel/tmp/pong/pong
**
** Made by THOMAS Samuel
** Login   <thomas_s@etna-alternance.net>
**
** Started on  Wed May  9 09:35:25 2018 THOMAS Samuel
** Last update Wed May  9 10:10:51 2018 THOMAS Samuel
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>


int client(int argc, char *argv[])
{
int sockfd = 0, n = 0;
char recvBuff[1024];
struct sockaddr_in serv_addr;

if(argc != 3)
  {
printf("\n Usage: %s <ip of server> \n",argv[0]);
return 1;
}

memset(recvBuff, '0',sizeof(recvBuff));
if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
printf("\n Error : Could not create socket \n");
return 1;
}

memset(&serv_addr, '0', sizeof(serv_addr));

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5000);

if(inet_pton(AF_INET, argv[2], &serv_addr.sin_addr)<=0)
  {
printf("\n inet_pton error occured\n");
return 1;
}

if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
printf("\n Error : Connect Failed \n");
return 1;
}

while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
  {
recvBuff[n] = 0;
if(fputs(recvBuff, stdout) == EOF)
  {
printf("\n Error : Fputs error\n");
}
}

if(n < 0)
  {
printf("\n Read error \n");
}

return 0;
}
