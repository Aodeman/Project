#include "socket_client_init.h"
#include "tlv.h"
#include "ds18620.h"

#define serip "127.0.0.1"

int main()
{
    int      sockfd=-1;
    char  *  tem;
    int      rv=-1;

    sockfd=socket_client_init(12335,serip);
    if(sockfd<0)
    {
        return -1;    
    }

    tem=get_tem();
    if(tem<0)
    {
        printf("Get temp defeat\n");
    }
    
    send_data fv;

    fv.tag=temp;
    memcpy(fv.buf, tem, 20);
    fv.len=20;
    rv=write(sockfd,(char *)&fv,sizeof(send_data));
    if(rv<0)
    {
        perror("write dafeat");
	return -1;
    }
    printf("Data type %d\n",fv.tag);
    printf("Send data %s\n",fv.buf);

    return 0;

}
