crc=crc_itu_t
cc=gcc
headfile_path=/home/iot/yangbiao/headfile/
lib_path=/home/iot/yangbiao/lib/

target:
	 ${cc} -shared -fPIC -o libtem.so ${crc}.c -I ${headfile_path}
	 ${cc} -shared -fPIC -o libtem.so taxt.c -I ${headfile_path}
client:
	${cc}  tlvcli.c -o cli -I ${headfile_path}  -lcec_t  -L${lib_path}
server:
	${cc}  sertlv.c -o ser  -I ${headfile_path}  -lcec_t -L${lib_path}
clear:
	rm *.o

