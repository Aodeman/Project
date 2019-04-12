/*********************************************************************************
 *      Copyright:  (C) 2019 LingYun<lingyun@email.com>
 *                  All rights reserved.
 *
 *       Filename:  select_sock.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(12/04/19)
 *         Author:  LingYun <lingyun@email.com>
 *      ChangeLog:  1, Release initial version on "12/04/19 21:36:44"
 *                 
 ********************************************************************************/
#include <errno.h>
#include <string.h>
#include "sock_server_init.h"

int main()
{
    int       fd_array[1024];
    int       j,i=0,rv=-1;
    int       maxfd=1;
    int       sockfd=-1;
    int       port=12345;
    char      buf[1024];
    char *    serip=NULL;
    fd_set    readset;
    socklen_t             addrlen;
    struct sockaddr_in    addr;

    sockfd=sock_server_init(serip,port);
    if(sockfd<0)
    {
        printf("Socket error\n");
    }

    memset(fd_array,0,sizeof(fd_array));
    FD_ZERO(&readset);
    FD_SET(sockfd,&readset);
    maxfd=sockfd;
    while(1)
    {
        printf("Warting thing...\n");
        rv=select(maxfd+1,&readset,NULL,NULL,NULL);
        if(rv==-1)
        {
            perror("SELECT ERROR");
            return -1;
        }
        if(rv==0)
        {
            printf("SELECT TIMETOU\n");
        }
        if((FD_ISSET(sockfd,&readset))>0)
        {
            printf("New client connect...\n");
            fd_array[i]=accept(sockfd,(struct sockaddr *)&addr,&addrlen);
            if(fd_array[i]<0)
            {
                perror("Accept error");
                return -2;
            }
            maxfd= (fd_array[i] > maxfd) ? fd_array[i] : maxfd;
            FD_SET(fd_array[i],&readset);
            i++;
            for(j=0;j<i;j++)
            {
                printf(" %d",fd_array[j]);
            }
            printf("\n");
    
        }
        
        {
            printf("Waiting %d\n",rv);
            for(j=0;j<i;j++)
            {
                if((FD_ISSET(fd_array[j],&readset))!=0)
                {
                    printf("Receiving %d data...\n",fd_array[j]);
                    rv=read(fd_array[j],buf,sizeof(buf));
                    if(rv<0)
                    {
                        printf("Read %d error\n",fd_array[j]);
                        continue;
                    }
                    if(rv==0)
                    {
                        printf("client disconnet\n");
                    }
                    printf("%s\n",buf);
            
                }
                else
                {
                    printf("no data\n");
                }
        
            }
            continue;
        }
    }


    return 0;
}

