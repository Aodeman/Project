#include "socket_client_init.h"
#include "ds18620.h"
#include "crc_itu_t.h"


#define MAX_ARRAY 32
#define HEAD_LEN 5  /* head(1B),tag(1B),len(1B),crc(2b) */
#define serip "127.0.0.1"
#define HEAD  0xfd

typedef enum {

    TEMP=1,
    TIME,
    ID
} type;



int pack_data(char *buf,char* data,unsigned short tag)
{
 
    int tem,tem1,tem2,rv=0;

    buf[rv++]=HEAD;
    buf[rv++]=tag;
    buf[rv++]=HEAD_LEN+2;
    
    printf("%s\n",data);
    tem=atoi(data);
    tem1=tem/1000;
    tem2=(tem%1000)/10;
    buf[rv++]=tem1;
    buf[rv++]=tem2;
    printf("tel%d %d  %d\n",tem,tem1,tem2);
    
    for(int i=0;i<10;i++)
    {
        printf("%x ",buf[i]);
    }
    printf("\n");
    printf("***************\n");
    return rv;
}


int main()
{
    int              sockfd=-1;
    char             tem[8];
    int              rv=-1;
    char             buf[MAX_ARRAY];
    unsigned short   tag=TEMP;
    unsigned short   crc16;
    unsigned int     len=0;
    unsigned short   crc;

/*
    sockfd=socket_client_init(12335,serip);
i:wq
f(sockfd<0)
    {
        return -1;    
    }

*/
    
    printf("****************\n");
    memset(tem,0,sizeof(tem));
    memmove(tem,get_tem(),5);
    
    printf("%s %d\n",tem,strlen(tem));
    //printf("***************\n");

    memset(buf,0,sizeof(buf));
    pack_data(buf,tem,tag);
    crc16=crc_itu_t(IoT_MAGIC_CRC,buf,strlen(buf));
    ushort_to_bytes(&buf[strlen(buf)],crc16);
    printf("%x\n",crc16);

    printf("***************\n");
    for(int a=0;a<strlen(buf);a++)
    {
        printf("%02x ",buf[a]);
    }
    printf("\n");

    crc16=crc_itu_t(IoT_MAGIC_CRC,buf,buf[2]);
    printf("%x\n",crc16);
    rv=write(sockfd,buf,strlen(buf));
    

    return 0;

}
