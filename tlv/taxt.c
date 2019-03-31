/*********************************************************************************
 *      Copyright:  (C) 2019 LingYun<lingyun@email.com>
 *                  All rights reserved.
 *
 *       Filename:  taxt.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(30/03/19)
 *         Author:  LingYun <lingyun@email.com>
 *      ChangeLog:  1, Release initial version on "30/03/19 21:37:19"
 *                 
 ********************************************************************************/
#include "crc_itu_t.h"
#include <stdio.h>


int main()
{

    unsigned char buf[6];
    buf[0]=0xdf;
    buf[1]=0x01;
    buf[2]=4;

    unsigned short a;
    unsigned short crc16;

    crc16=crc_itu_i(a,buf,3);
    printf("%x\n",crc16);

    return 0;

}

