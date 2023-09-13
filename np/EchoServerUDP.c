#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main()
{
char str[100];
int listen_fd;
struct sockaddr_in servaddr,caddr;
listen_fd=socket(AF_INET,2,0);
bzero(&servaddr,sizeof(servaddr));
int len=sizeof(caddr);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(22000);
bind(listen_fd,(struct sockaddr *) &servaddr,sizeof(servaddr));


while(1)
{

bzero(str,100);
recvfrom(listen_fd,str,100,0,(struct sockaddr *)&caddr,&len);
printf("Echoing Back- %s",str);
sendto(listen_fd,str,100,0,(struct sockaddr *)&caddr,len);
if(strncmp("exit",str,4)==0)
{
printf("Client exited..\n");
break;
}
}
close(listen_fd);
}
