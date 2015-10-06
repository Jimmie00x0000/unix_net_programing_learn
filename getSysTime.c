#include "./unpv13e/lib/unp.h"
#include "./apueerror.h"
int main( int argc, char ** argv){
	int sockfd,n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;

	if (argc!=2)
		err_quit("usage:a.out <IPaddress>");
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0) //we can use sockfd to get IP of local host
		err_sys("socket error ");

	bzero(&servaddr, sizeof (servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(1311);
	if (inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)//IP string transferred to IP struct
		err_quit("inet_pton error for %s",argv[1]);

	if (connect (sockfd,(SA*) &servaddr, sizeof (servaddr))<0)
		err_sys("connect error");

	while ((n=read(sockfd,recvline,MAXLINE))>0){//read a segment at one time,maybe return many segments
		recvline[n]=0;
		if (fputs(recvline,stdout)==EOF)//put char array into stdout,
			err_sys("fputs error");
		}
	
	if (n<0)
		err_sys("read error ");
	exit(0);

}
//original version of the source code use the well-known port: 13, known as the time server port
//howerver,the unix set the port less than 1024 as reserved ports,which mean user must use sudo to  
//launch the server program, so I choose 1311 to launch the server for convenience,
//
//if you want to use this program,you must luanch the time Server program, the default time service at port 13 is closed in case of DDOS in *nix system
