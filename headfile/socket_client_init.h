#include <stdio.h>          
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>  /*struct sockaddr_in   inet_aton */
#include <arpa/inet.h>   /*inet_aton*/ 


int socket_client_init (int port , char  *serip)
{

        int             	sockfd=-1;
        int			rv=-1;
        struct sockaddr_in      seraddr;



	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("creat socket failure");
		return -1;
	}
	printf("Socket success!\n");
	
		
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(port);
    inet_aton(serip,&seraddr.sin_addr);
	

	rv=connect(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	if (rv<0)
	{
		perror("Connect failure");
		return -2;
	}
    printf("Connect \n");

        return sockfd;

}
