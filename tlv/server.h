#include <stdio.h>       
#include <errno.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>



int sock_server_init(char *listen_ip,int port)
{
	int                     on;
	int                     rv=-1;
	int                     serfd=-1;
        struct sockaddr_in       seraddr;

	printf("Start\n");
	serfd=socket(AF_INET,SOCK_STREAM,0);
	if(serfd<0)
	{
		perror("Socket failure:");
		return -1;
	}

        if((setsockopt(serfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))<0)
	{
	        perror("Setsockpt failure");
	}
        
        if(port==0)
	{
	        port=12335;
	}
	if(listen_ip==NULL)
        {
               seraddr.sin_addr.s_addr=htonl(INADDR_ANY); 	        
	}
	else
        {
               if (inet_pton(AF_INET, listen_ip, &seraddr.sin_addr) <= 0)
               {       
                       printf("inet_pton() set listen IP address failure.\n");
                       return -1;
               }
	}


	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(port);
	
	printf("Socket success!\n");
	rv=bind(serfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	if(rv<0)
	{
		perror("Bind failure");
		return -2;
	}
	printf("Bind success!\n");

	rv=listen(serfd,0);
	if(rv<0)
	{
		printf("Listen failure");
		return -3;
	}
	printf("Listen success!\n");
	return serfd;


}
