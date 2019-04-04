crc=crc_itu_t
cc=gcc

target:
	 ${cc} -shared -fPIC -o libtem.so ${crc}.c -I /home/iot/yangbiao/headfile/
	 ${cc} -shared -fPIC -o libtem.so taxt.c -I /home/iot/yangbiao/headfile/
client:
	${cc}  tlvcli.c -o cli -I /home/iot/yangbiao/headfile/ -lcec_t -L/home/iot/yangbiao/lib
server:
	${cc}  sertlv.c -o ser  -I /home/iot/yangbiao/headfile/ -lcec_t -L/home/iot/yangbiao/lib
clear:
	rm *.o

