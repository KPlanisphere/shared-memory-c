#include <sys/types.h>
#include <sys/tpc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define LLAVE 234
#define MAX 10
int main() {
	int shmid, i;
	key_t key=LLAVE;
	char *vector;
	/*Creacion de un segmento de memoria compartida*/
	shmid = shmget(key, (MAX*sizeof(char)), IPC_CREAT | 0600);
	if(shmid == -1){
		printf("No se ha podido crear el segmento.");
		exit(-1);
	}
	else{
		/*Conexion del segmento al espacio de direcciones virtuales*/
		vector = shmat (shmid,0,0);
		if(vector == (char*)0){
			printf("Error en la concexion.");
			exit(-1);
		}
		/*Manipulaxion del segmento de memoria compartida*/
		printf("Segmento mapeado (asociado)\n");
		for(i=0; i < MAX; i++)
			vector[i] = 'a';
		for(i=0; i < MAX; i++)
			printf("Valor almacenado %c\n", vector[i]);
		/*Desconexion del segmento al espacio de direcciones virtuales*/
		if(shmdt (vector) == -1){
			printf("Error en la desconexion.");
			exit(-1);
		}
		else
			printf("Exito en la desconexion\n");
		/*Borrado del segmento de memoria compartida*/
		if(shmctl(shmid,IPC_RMID,0) == -1){
			printf("Error en el borrado del segmento.");
			exit(-1);
		}
		else
			printf("Borrada memoria compartida\n");
	}
}