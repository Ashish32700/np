#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
int main(int argc,char **argv)
{
char send1[100];
char recv1[100];
int sockfd;
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,2,0);
bzero(&servaddr,sizeof(servaddr));
int len=sizeof(servaddr);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(22000);


while(1)
{
bzero( send1, 100);
bzero( recv1, 100);
fgets(send1,100,stdin); 
if(strncmp("exit",send1,4)==0)
{
printf("client exit..\n");
break;
}
sendto(sockfd,send1,strlen(send1),0,(struct sockaddr *)&servaddr,len);
recvfrom(sockfd,recv1,100,0,(struct sockaddr *)&servaddr,&len);

if(strncmp("exit",recv1,4)==0)
{
printf("client exit..\n");
break;
}
printf("From Server - %s",recv1);

}
close(sockfd);
}
