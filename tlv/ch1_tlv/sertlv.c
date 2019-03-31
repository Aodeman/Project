#include "server.h"
#include <stdlib.h>
#include <string.h>

typedef enum  type{

	   nit=-1,id=0,time,temp
		       
}type;




typedef struct{

    int  head;
    type tag;
    int  len;
    char buf[];

} send_data;



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
        while(1)
        {
            send_data * fv;	
	  //  memset(&fv,0,sizeof(send_data)+20);
            fv=(send_data *)malloc(sizeof(fv)+10*sizeof(char));


	    printf("head %d\n",fv->head);
	    printf("tag %d\n",fv->tag);

	    int  rv=read(newfd,(char *)&fv,sizeof(send_data)+10*sizeof(char));
            if(rv<0)
            {
                perror("read");
	        return -1;
            }
	    printf("receive\n");
	    printf("head %d\n",fv->head);
	    printf("tag %d\n",fv->tag);

            
            if(fv->tag==temp)
            {
	    
                printf(" Temp is %s\n",fv->buf);
	    }   
	    free(fv);


        }
    }
  
    return 0;

}
