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



void pack_data(char *buf,char* data,unsigned short tag)
{
 
    buf[0]=HEAD;
    buf[1]=tag;
    buf[2]=HEAD_LEN+strlen(data);
    memcpy(buf+3,data,5);
    for(int i=0;i<10;i++)
    {
        printf("%x ",buf[i]);
    }
    printf("\n");
    printf("%s\n",buf);
    printf("***************\n");
}


int main()
{
    int              sockfd=-1;
    char *           tem;
    int              rv=-1;
    char             buf[MAX_ARRAY];
    unsigned short   tag=TEMP;
    unsigned short   crc16;
    unsigned int     len=0;
    unsigned short   crc;
/*

    sockfd=socket_client_init(12335,serip);
    if(sockfd<0)
    {
        return -1;    
    }

*/
    
    printf("****************\n");
    tem=get_tem();
    
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
    //   rv=write(sockfd,buf,strlen(buf));
    

    return 0;

}
