#include "socket_client_init.h"
#include "ds18620.h"
#include "crc_itu_t.h"

#define serip "127.0.0.1"
#define HEAD  0xfd
#define ID 0x01
#define TIME 0x02
#define TEMP 0x03




void pack_data(char * p,char *data)
{
    



}


int main()
{
    int              sockfd=-1;
    char *           tem;    
    int              rv=-1;
    char             buf[20];
    unsigned short   tag;
    int              len;



    sockfd=socket_client_init(12335,serip);
    if(sockfd<0)
    {
        return -1;    
    }

    tem=get_tem();
    printf("tem %s\n",tem);
    if(tem<0)
    {
        printf("Get temp defeat\n");
    }
   
    memset(buf,0,20);
    len=3+strlen(tem);
    buf[0]=HEAD;
    buf[1]=TEMP;
    buf[2]=len;
    printf("len %d\n",len);
    memcpy(buf+3,tem,strlen(tem));
    
    printf("%s\n",tem);
    printf("%x\n",buf[0]);
    printf("%x\n",buf[1]);
    printf("%d\n",buf[2]);
    printf("%s\n",buf);
    rv=write(sockfd,buf,strlen(buf));
    

    return 0;

}
