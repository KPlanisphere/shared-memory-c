#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM_BUF 4096

int main(){
	int id;
	if((id=shmget(IPC_PRIVATE, TAM_BUF,0666)) < 0){
		perror("shmget");
		exit(-1);
	}
	printf("Identificador del segmento creado: %d\n",id);
	system("ipcs -m");
	exit(0);
}
