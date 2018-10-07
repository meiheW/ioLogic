#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "ioManager.h"

modbus_t *ioctx = NULL;

//open modbus tcp --ip:"192.168.127.254", port:502
int open_modbus_tcp_powermang(const char *ip_address, int port)
{
	//ioctx = modbus_new_tcp("192.168.1.253", 1031);
	ioctx = modbus_new_tcp(ip_address, port);
    modbus_set_debug(ioctx, TRUE);
    int rc = modbus_set_slave(ioctx, 0);
	if(-1 == rc){
        fprintf(stderr, "set slave failed: %s\n",
                modbus_strerror(errno));
		modbus_free(ioctx);
		return -1;
	}

    if (modbus_connect(ioctx) == -1) 
    {
        fprintf(stderr, "Connection failed: %s\n",
                modbus_strerror(errno));
        modbus_free(ioctx);
        return -1;
    }
	return 0;
}

//close modbus tcp
void close_modbus_tcp_powermang()
{
	modbus_close(ioctx);
	modbus_free(ioctx);
}


int read_DO(int index)
{
    int ret = -1;    
    if(index<0||index>7){
        printf("read DO index wrong! index:0 to 7");
        return -1;
    }

    int addr = 0x0000 + index;
    uint8_t tab_rp_bits;
	if(1 != modbus_read_bits(ioctx, addr, 1, &tab_rp_bits))
	{
		printf("Modbus read bits failed.\n");
		return -1;
	}
	
    ret = tab_rp_bits;
    return ret;    
}

int write_DO(int index, int status)
{

    if(index<0||index>7){
        printf("write DO index wrong! index:0 to 7");
        return -1;
    }
    if(status<0||status>1){
        printf("write DO status wrong! status:0 or 1");
        return -1;
    }

    int addr = 0x0000 + index;
	if(1 != modbus_write_bit(ioctx, addr, status))
	{
		printf("modbus write DO status failed");
		return -1;
	}
	
    return 0;
}


int read_DI(int index)
{
    
    int ret = -1;    
    if(index<0||index>11){
        printf("read DI index wrong! index:0 to 11");
        return -1;
    }

    int addr = 0x0000 + index;
    uint8_t tab_rp_bits;
	if(1 != modbus_read_input_bits(ioctx, addr, 1, &tab_rp_bits))
	{
		printf("Modbus read input bits failed.\n");
		return -1;
	}
	
    ret = tab_rp_bits;
    return ret;
    
}



int mytest(){
    for(int i=0; i<=7; i++){
        printf("index %d, status %d\n", i, read_DO(i));
    }
    //usleep(5000000);
    for(int i=0; i<=7; i++){
        if(0==i%2){        
        write_DO(i,0);printf("turn off DO%d ...\n", i);}
        //usleep(1000000);
        //write_DO(i,1);printf("turn on DO%d ...\n", i);
    }
    
    for(int i=0; i<=7; i++){
        printf("read DO%d, %d\n", i, read_DO(i));    
    }        

    for(int i=0; i<=11; i++){
        printf("read DI%d, %d\n", i, read_DI(i));    
    }        
    return 0;

}





//int arg, char** argv
int main()
{
    
	open_modbus_tcp_powermang("192.168.127.254", 502);
    printf("success\n");

    mytest();
	close_modbus_tcp_powermang();
    printf("exit\n");
    return 0;
}










