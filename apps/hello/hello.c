#include <stdio.h>
#define _GNU_SOURCE 1
#include <linux/mman.h>

int main() {
	printf("Hello, RISC-V World!\n");
	void *addr;
	addr = mmap(NULL, 64 * 1024, PROT_WRITE | PROT_READ,
			MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGE_64KB, -1, 0);
	printf("back from mmap \n");
	long *ptr = (long *)addr;
	unsigned int i = 0;
	for(; i < 8 * 1024;i += 512) {
		printf("%lp \n", ptr);
		*ptr = 0xdeafabcd12345678;
		ptr += 512;
	}
	ptr = (long *)addr;
	i = 0;
	for(; i < 8 * 1024;i += 512) {
		if (*ptr != 0xdeafabcd12345678) {
			printf("failed! 0x%lx \n", *ptr);
			break;
		}
		ptr += 512;
	}
	if(i == 8 * 1024)
		printf("simple test passed!\n");
	while(1);
}
