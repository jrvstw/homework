CFLAGS = -O3 -lm -pthread -D_Float32x=float -D_Float64x="long double" -D_Float32=float -D_Float64="long double"

main:
	gcc ${CFLAGS} pi.c -o pi

clean:
	rm -f pi
