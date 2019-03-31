#ifndef _TLV_H_
#define _TLV_H_
；

typedef enum tf enumype{

   nit=-1,id=0,time,temp
	  
}type;




typedef struct{

    int  head;
    type tag;
    int  len;
    char buf[];

} send_data;


#endif
