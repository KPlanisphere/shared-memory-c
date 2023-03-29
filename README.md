# Shared Memory in C

## Description
This project contains a series of C programs that demonstrate various aspects of shared memory usage in Unix-like operating systems. These programs illustrate how to create, attach, manipulate, and remove shared memory segments using system calls. Each file showcases different aspects of shared memory management, providing a comprehensive overview of how to implement these mechanisms in C.

### Key Features
- **Shared Memory Creation**: Examples of creating shared memory segments using `shmget`.
- **Shared Memory Attachment**: Demonstrations of attaching shared memory segments to the process's address space using `shmat`.
- **Shared Memory Manipulation**: Usage of shared memory for storing and retrieving data.
- **Shared Memory Detachment and Removal**: Examples of detaching and removing shared memory segments using `shmdt` and `shmctl`.

### Files
1. **A1P9.c**
    - Demonstrates the creation of a shared memory segment.
    - **Key Code Snippet**:
        ```c
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/shm.h>
        #include <stdio.h>
        #include <stdlib.h>

        #define TAM_BUF 4096

        int main() {
            int id;
            if ((id = shmget(IPC_PRIVATE, TAM_BUF, 0666)) < 0) {
                perror("shmget");
                exit(-1);
            }
            printf("Identificador del segmento creado: %d\n", id);
            system("ipcs -m");
            exit(0);
        }
        ```
        This code creates a shared memory segment and prints its identifier.

2. **A2P9.c**
    - Illustrates attaching a shared memory segment to the process's address space.
    - **Key Code Snippet**:
        ```c
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/shm.h>
        #include <stdio.h>
        #include <stdlib.h>

        int main(int argc, char *argv[]) {
            int id;
            char *buf_sgtmemc;
            if (argc != 2) {
                puts("MODO DE EMPLEO: shmat A1P9");
                exit(-1);
            }
            id = atoi(argv[1]);
            if ((buf_sgtmemc = shmat(id, 0, 0)) < (char *)0) {
                perror("shmat");
                exit(-1);
            }
            printf("El segmento ha sido adosado en %p\n", buf_sgtmemc);
            system("ipcs -m");
            exit(0);
        }
        ```
        This code attaches a shared memory segment to the process's address space and prints its address.

3. **A3P9.c**
    - Demonstrates attaching, manipulating, and removing a shared memory segment.
    - **Key Code Snippet**:
        ```c
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/shm.h>
        #include <stdio.h>
        #include <stdlib.h>
        #include <fcntl.h>

        #define TAM_BUF 4096

        int main(int argc, char *argv[]) {
            int id;
            char *buf_sgtmemc;
            int salida, i;

            if (argc != 2) {
                puts("MODO DE EMPLEO: abrir_sgtmemc <identificador>");
                exit(-1);
            }
            id = atoi(argv[1]);
            if ((buf_sgtmemc = shmat(id, 0, 0)) < (char *)0) {
                perror("shmat");
                exit(-1);
            }
            if ((buf_sgtmemc = malloc(sizeof(char) * TAM_BUF)) == NULL) {
                perror("malloc");
                exit(-1);
            }
            for (i = 0; i < TAM_BUF; i++)
                buf_sgtmemc[i] = 0x7F;
            salida = open("text.c", O_CREAT | O_WRONLY, 0600);
            write(salida, buf_sgtmemc, TAM_BUF);
            close(salida);
            printf("Eliminando memoria compartida\n");
            shmctl(id, IPC_RMID, 0);
            exit(0);
        }
        ```
        This code attaches a shared memory segment, manipulates it by writing data, and then removes the segment.

4. **A4P9.c**
    - Illustrates creating, attaching, manipulating, detaching, and removing a shared memory segment.
    - **Key Code Snippet**:
        ```c
        #include <sys/types.h>
        #include <sys/ipc.h>
        #include <sys/shm.h>
        #include <stdio.h>
        #include <stdlib.h>

        #define LLAVE 234
        #define MAX 10

        int main() {
            int shmid, i;
            key_t key = LLAVE;
            char *vector;
            shmid = shmget(key, (MAX * sizeof(char)), IPC_CREAT | 0600);
            if (shmid == -1) {
                printf("No se ha podido crear el segmento.\n");
                exit(-1);
            } else {
                vector = shmat(shmid, 0, 0);
                if (vector == (char *)0) {
                    printf("Error en la conexión.\n");
                    exit(-1);
                }
                printf("Segmento mapeado (asociado)\n");
                for (i = 0; i < MAX; i++)
                    vector[i] = 'a';
                for (i = 0; i < MAX; i++)
                    printf("Valor almacenado: %c\n", vector[i]);
                if (shmdt(vector) == -1) {
                    printf("Error en la desconexión.\n");
                    exit(-1);
                } else {
                    printf("Éxito en la desconexión\n");
                }
                if (shmctl(shmid, IPC_RMID, 0) == -1) {
                    printf("Error en el borrado del segmento.\n");
                    exit(-1);
                } else {
                    printf("Borrada memoria compartida\n");
                }
            }
        }
        ```
        This code demonstrates the complete lifecycle of a shared memory segment, including creation, attachment, manipulation, detachment, and removal.

## How to Use
1. **Compilation**: Each C file can be compiled using a C compiler such as `gcc`.
    ```bash
    gcc A1P9.c -o A1P9
    gcc A2P9.c -o A2P9
    gcc A3P9.c -o A3P9
    gcc A4P9.c -o A4P9
    ```

2. **Execution**: Run the compiled programs to see the output of shared memory operations.
    ```bash
    ./A1P9
    ./A2P9 <identifier>
    ./A3P9 <identifier>
    ./A4P9
    ```