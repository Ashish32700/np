#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define MAX 100
void func(int listen_fd)
{

char str[MAX];
int n;
struct sockaddr_in caddr;
int len=sizeof(caddr);
while(1)
{

bzero(str,MAX);
recvfrom(listen_fd,str,sizeof(str),0,(struct sockaddr *)&caddr,&len);
printf("From Client- %s",str);
bzero(str,MAX);
n=0;
while((str[n++]=getchar())!='\n');
sendto(listen_fd,str,sizeof(str),0,(struct sockaddr *)&caddr,len);
if(strncmp("exit",str,4)==0)
{
printf("Server exit..\n");
break;
}

}


}

int main()
{

int listen_fd;
struct sockaddr_in servaddr;
listen_fd=socket(AF_INET,2,0);
bzero(&servaddr,sizeof(servaddr));

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(22000);
bind(listen_fd,(struct sockaddr *) &servaddr,sizeof(servaddr));
func(listen_fd);
close(listen_fd);

}
