#include <stdlib.h>
#include <string.h>
#include "crc_itu_t.h"
#include "server.h"


#define MIN_DATASIZE 6
#define MAX_ARRAY 1024
typedef enum {

        TEMP=1,
        TIME,
        ID
} type;


int main()
{
    int                     i;
    int                     num=0;
    int                     newfd=-1;
    int                     sockfd=-1;
    int                     buf_size;
    struct sockaddr_in      cliaddr;
    socklen_t               len;
    char                    buf[MAX_ARRAY];
    unsigned short          crc16; 
   


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

Start:
            num++;

            if(rv<MIN_DATASIZE)
            {   
                printf("num %d \n  errir:incomplete data\n",num);
                continue;
            }
            for(i=0;i<rv;i++)
            {
                if(buf[i]==0xfd)
                { 
                    memmove(buf,buf+i,rv=rv-i);
                    break; 
                }

            }
            if(rv<6 || i==rv)
            {   
                printf("num %d \n  errir:incomplete data\n",num);
                continue;
            }

            if(buf[1]!=ID && buf[1]!=TIME && buf[1] !=TEMP)
            {
                printf("tag error\n");
                memmove(buf,buf+1,rv=rv-1);
                goto Start;
            }
            if(buf[2] < MIN_DATASIZE)
            {
                printf("lenth errir:lenth %dB   recive %dB \n",buf[2],strlen(buf));
                memmove(buf,buf+2,rv=rv-2);
                goto Start;                
            }

            crc16=crc_itu_t(IoT_MAGIC_CRC,buf,buf[2]);
            if(crc16!=0)
            {
                printf("value error\n");
                memmove(buf,buf+2,rv=rv-2);
                goto Start;
            }
            printf("Correct data:");
            for(int q=0;q<buf[2];q++)
            {
                printf(" %x",buf[q]);
            }
            printf("\n");
            buf[0]=0;
            //memmove(buf,buf+buf[2],strlen(buf+buf[2]));
            sleep(1);
            goto Start;
        }
    }
  
    return 0;

}
