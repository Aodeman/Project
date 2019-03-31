#include "server.h"
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY 1024


int main()
{
    int                     newfd=-1;
    int                     sockfd=-1;
    struct sockaddr_in      cliaddr;
    socklen_t               len;
    char                    buf[MAX_ARRAY];
  
   


    sockfd=sock_server_init(NULL,12335);
    if(sockfd<0)
    {
        printf("socket\n");
        return -1;
    }
    while(1)
    {	    
        newfd=accept(sockfd,(struct sockaddr *)&cliaddr,&len);
        if(newfd<0)
        {
            perror("accep defeat");
            return -1;	
        }
        while(1)
        {

            memset(buf,0,MAX_ARRAY);

     	    int  rv=read(newfd,buf,sizeof(buf));
            if(rv<0)
      	    {
                perror("read");
	        return -1;
            }
	    if(rv==0)
            {
	        return 0;
	    }

	    printf("%x\n",buf[0]);
	    printf("%x\n",buf[1]);
	    printf("%d\n",buf[2]);
	    printf("%s\n",buf+3);

        }
    }
  
    return 0;

}
