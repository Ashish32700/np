#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
void func(int comm_fd)
{
char str[100];


while(1)
{

bzero(str,100);
read(comm_fd,str,100);
printf("From Client- %s",str);
bzero(str,100);
fgets(str,100,stdin);
write(comm_fd,str,100);
if(strncmp("exit",str,4)==0)
{
printf("Server exited...");
break;
}

}
}

int main()
{

int listen_fd;
int comm_fd;
struct sockaddr_in servaddr,caddr;
int len=sizeof(caddr);
listen_fd=socket(AF_INET,1,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(22000);
bind(listen_fd,(struct sockaddr *) &servaddr,sizeof(servaddr));

listen(listen_fd,10);
comm_fd = accept(listen_fd, (struct sockaddr*)&caddr, &len);
func(comm_fd);
close(listen_fd);
}
