#include "socket_client_init.h"
#include "ds18620.h"

#define serip "127.0.0.1"
#define HEAD  0xFD


typedef enum type{

   init=-1,id=0,time,temp

}type;


typedef struct{

   short  head;
   type tag;
   int  len;
   char buf[];

} send_data;

int main()
{
    int      sockfd=-1;
    char  *  tem;
    int      rv=-1;
//    char     buf[20];


    sockfd=socket_client_init(12335,serip);
    if(sockfd<0)
    {
        return -1;    
    }

    tem=get_tem();
    printf("tem %s\n",tem);
    printf("tem len %d\n",strlen(tem));
    if(tem<0)
    {
        printf("Get temp defeat\n");
    }
  
    send_data * fv;
    fv=(send_data *)malloc(sizeof(fv)+10*sizeof(char));
    fv->head=0xFD;
    fv->tag=temp;
    fv->len=sizeof(fv);
    printf("buf %s\n",fv->buf);
//    memcpy(fv->buf,tem,strlen(tem));
    printf("buf %s\n",fv->buf);
     
    rv=write(sockfd,(char *)&fv,sizeof(fv)+10*sizeof(char));
    if(rv<0)
    {
        perror("Write");
    }
    printf("head %x\n",fv->head);
    printf("tag %d\n",fv->tag);
    printf("len %d\n",fv->len);
    printf("buf %s\n",fv->buf);
    

    free(fv);
    return 0;

}
