#include <sys/types.h>
#include <sys/tpc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int id;
	char *buf_sgtmemc;
	if(argc != 2){
		puts("MODO DE EMPLEO: shmat A1P9");
		exit(-1);
	}
	id = atoi (argv[1]);
	if((buf_sgtmemc = shmat(id,0,0)) < (char *)0){
		perror("shmat");
		exit(-1);
	}
	printf("El segmento a sido adosado en %p\n", buf_sgtmemc);
	system("ipcs -m");
	exit(0);
}
