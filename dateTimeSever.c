#include "./common.h"
#include "time.h"
//#include "./unpv13e/lib/unp.h"

int main (int argc, char **argv){
	int 	listenfd,connfd;
	struct sockaddr_in	servaddr;
	char	buff[MAXLINE];
	time_t	ticks;
	time_t  test;
	test = time (NULL);
	printf ("the time now is: %s\n",ctime(&test));
	listenfd=Socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));//clear
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);//
	servaddr.sin_port=htons(1311);
	Bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
	printf ("the IP address in INT form is: %d \n",servaddr.sin_addr.s_addr);
	
	Listen(listenfd,LISTENQ);
	for(;;){
		connfd=Accept(listenfd,(SA*) NULL,NULL);
		ticks=time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
		Write(connfd,buff,strlen(buff));
		Close(connfd);
	}
}
