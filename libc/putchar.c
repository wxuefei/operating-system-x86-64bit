#include <stdio.h>

int putchar(int c)
{
	char *buff=(char*)&c;
	long fd=1;
	long count=1;
	unsigned long syscallnumber = 1;
	long write_count;

	__asm__(
	"movq %1, %%rax;\n"
	"movq %2, %%rdi;\n"
	"movq %3, %%rsi;\n"
	"movq %4, %%rdx;\n"
	"int $0x80;\n"
	"movq %%rax, %0;\n"
	: "=m" (write_count)
	: "m" (syscallnumber), "m" (fd), "m" ((unsigned long)buff), "m" (count)
	: "rax","rdi", "rsi", "rdx"
	);

	if(write_count==1)
		return c;
	else 
		return EOF;
}
