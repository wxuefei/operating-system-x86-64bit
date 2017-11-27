#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/defs.h>
#include <dirent.h>

void foolcompiler(int* a){
	return;
}

void dummysyscall(){

	unsigned long syscallnumber = 1;
	void *addr = NULL;
	uint64_t length = 12345;
	int prot = 1|2;//PROT_READ;
	int flags = 1|0x20;//MAP_SHARED;
    int fd = -1; int offset = 0;
    int ret=0;
	__asm__(
	"movq %0,%%rax;\n"
	"movq %1,%%rdi;\n"
	"movq %2,%%rsi;\n"
	"movq %3,%%rdx;\n"	
	"movq %4,%%r10;\n"	
	"movq %5,%%r9;;\n"
	"movq %6,%%r8;\n"
	"int $0x80;\n"
	:
	:"m"(syscallnumber),"m"((uint64_t)addr),"m"(length),"m"(prot),"m"(flags),"m"(fd),"m"(offset)
	);
    //printf("returned from syscall\n");

	__asm__(
	"movq %%rax, %0"
	:"=m"(ret)
	:
	);
	// printf("Returned From dummysyscall %d\n", ret);
	return;
}

void testread(){

	uint64_t syscallnumber = 3;
	__asm__(
	"movq %0,%%rax;\n"
	"int $0x80;\n"
	:
	:"m"(syscallnumber)
	);	
}

void TESTMALLOC(){

{
	int* trymalloc = (int*)malloc(2048*sizeof(int));
	// printf("add malloc %p\n", trymalloc);	
	trymalloc[0] = 1;
	puts("Working----------------------------------------");
	printf("malloc success %d\n", trymalloc[0]);
	trymalloc[2047] = 2;
	printf("malloc success %d\n", trymalloc[2047]);


	free(trymalloc);


	int* trymalloc2 = (int*)malloc(1000*sizeof(int));
	trymalloc2[0] = 1;

	int* trymalloc3 = (int*)malloc(1000*sizeof(int));
	trymalloc3[0] = 1;

	int* trymalloc4 = (int*)malloc(1000*sizeof(int));
	trymalloc4[0] = 1;

	free(trymalloc2);
	free(trymalloc3);
	free(trymalloc4);	

}

// {
// 	// 23557 blocks ~ 90+ MB
// 	int kill = 0;
// 	while(1){
// 		int* killme = (int*)malloc(1000*sizeof(int));
// 		killme[0] = 1;
// 		printf("Allocated %d %p %d\n", kill, killme, killme[0]);
// 		kill++;
// 	}

// }

// {
// 	//Allocated 545269 857f8000 545269
// 	int kill = 0;
// 	while(1){
// 		int* killme = (int*)malloc(1000*sizeof(int));
// 		killme[0] = kill;
// 		printf("Allocated %d %p %d\n", kill, killme, killme[0]);
// 		free(killme);
// 		kill++;
// 	}
// }

// {
	
// 	int kill = 0;
// 	while(1){
// 		int* killme = (int*)malloc(1000*sizeof(int));
// 		printf("Allocated %d %p\n", kill, killme);
// 		kill++;
// 	}

// }


// {
// 	//Page table for virtual address take space so not infinite. Need to reuse virtual address to make this work
// 	// Allocated 69093 8752b000
// 	int kill = 0;
// 	while(1){
// 		int* killme = (int*)malloc(8000*sizeof(int));
// 		killme[0] = 1;
// 		killme[1500] = 1;
// 		killme[2500] = 1;
// 		killme[3500] = 1;
// 		killme[4500] = 1;
// 		killme[5500] = 1;
// 		printf("Allocated %d %p\n", kill, killme);
// 		free(killme);
// 		kill++;
// 	}

// }

// {
// 		int kill = 0;
// 		int* killme = (int*)malloc(8000*sizeof(int));
// 		killme[0] = 1;
// 		killme[1500] = 1;		
// 		killme[2500] = 1;
// 		killme[3500] = 1;
// 		killme[4500] = 1;
// 		killme[5500] = 1;
// 		printf("Allocated %d %p\n", kill, killme);
// 		free(killme);
// 		kill++;
		
// }




	// trymalloc[0] = 2;
	// printf("result %d\n", trymalloc[0]);	

	// // trymalloc[1025] = 99;
	// // printf("result %d\n", trymalloc[1025]);	
	// free(trymalloc);

	// int* try2 = (int*)malloc(4096);
	// try2[0] = 1;

	// int* try3 = (int*)malloc(4096);
	// try3[0] = 1;

	// free(try2);	
}

void TESTCONTEXTSWITCH(){

	int a=5;
	 pid_t pid;
	 pid=fork();
	 if(pid > 0)
	 {
		 // printf("I am parent\n");
		 yield();
		 // printf("I am parent 1.0\n");
		 printf("I am parent %d\n",a);
		 yield();
		 //printf("I am parent 1.0\n");
		 //yield();
		 while(1);
		
	 }
	 if(pid==0)
	 {
		 // printf("I am child 1\n");
		 yield();
		 // printf("I am child 1.0\n");
		 yield();
		 // printf("I am child 1.1\n");
		 while(1);
	 }
}

void TESTTERMINAL(){

	puts("Hi how are puts working fine! Enter some text \n");

	char* buff = (char*)malloc(1024*sizeof(char));
	gets(buff);

	puts(buff);

	puts("You entered ");
	puts(buff);
	puts("\n");
	free(buff);


	printf("Hi I am back to the good world\n");	
	// int* try = (int*)malloc(10*sizeof(int));
	// foolcompiler(try);	

	char* num = (char*)malloc(1024*sizeof(char));
	puts("Enter a number\n");
	gets(num);
	puts("You entered");puts(num);
	
}

void TESTVFS(){


	char* queryPath = "/";

    struct dirent *pDirent;
    DIR *pDir;


    pDir = opendir (queryPath);
    if (pDir == NULL) {
        puts ("Cannot open directory \n");
        return ;
    }

    while ((pDirent = readdir(pDir)) != NULL) {
        puts (pDirent->d_name);
        puts("\n");
    }
    // printf("readdir finished\n");
    // closedir (pDir);
}


int main(int argc, char *argv[], char *envp[]) {

	puts("sbush> Hello World!!");

	//int *a=(int *)malloc(10*sizeof(int));

	//a[0]=1;


	TESTVFS();

	//TESTTERMINAL();

	// TESTMALLOC();
	
	// TESTCONTEXTSWITCH();
	 
	while(1);
}
