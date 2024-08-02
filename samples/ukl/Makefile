# SPDX-License-Identifier: GPL-2.0

CFLAGS += -I usr/include -fno-PIC -mno-red-zone -mcmodel=kernel

UKL.a: tcp_server.o syscall.o userspace
	riscv64-linux-gnu-ar cr UKL.a tcp_server.o syscall.o
	riscv64-linux-gnu-objcopy --prefix-symbols=ukl_ UKL.a

tcp_server.o: tcp_server.c
	riscv64-linux-gnu-gcc -O2 -mabi=lp64 -fno-stack-protector -march=rv64imac tcp_server.c -c
syscall.o: syscall.S
	riscv64-linux-gnu-gcc -O2 -mabi=lp64 -fno-stack-protector syscall.S -c

userspace:
	riscv64-linux-gnu-gcc -o tcp_server tcp_server.c

clean:
	rm -f UKL.a tcp_server.o syscall.o tcp_server
