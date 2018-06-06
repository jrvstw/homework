all: fig3_4_100.c fig3_4_4096.c fig3_4_8192.c fig3_4_16384.c
	gcc fig3_4_100.c error.c -o buffsize100
	gcc fig3_4_4096.c error.c -o buffsize4096
	gcc fig3_4_8192.c error.c -o buffsize8192
	gcc fig3_4_16384.c error.c -o buffsize16384
clean:
	rm -rf buffsize100 buffsize4096 buffsize8192 buffsize16384
