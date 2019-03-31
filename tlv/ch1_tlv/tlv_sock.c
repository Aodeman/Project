#include "server.h"
#include "tlv.h"
#include <stdlib.h>
#include <string.h>

int main()
{
    int                     newfd=-1;
    int                     sockfd=-1;
    struct sockaddr_in      cliaddr;
    socklen_t               len;
  
  
   


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
        //while(1)
        {
            send_data fv;	
	    memset(&fv,0,sizeof(send_data));
            int  rv=read(newfd,(char *)&fv,sizeof(send_data));
            if(rv<0)
            {
                perror("read");
	        return -1;
            }
	    
            
            if(fv.tag==temp)
            {
	    
                printf(" Temp is %s\n",fv.buf);
	    }   


        }
    }
  
    return 0;

}
