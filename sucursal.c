#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void crea_sucursal (const char* ciudad, char* capacidad){
	// Generamos un duplicado del proceso actual
	pid_t proceso = fork();
	
	// Se comprueba si no se ha podido crear un nuevo proceso
	if(proceso == -1){
		printf("\nSe ha producido un error en el proceso");
		exit(-11);
	}
	// En caso contrario, se ejecuta "gnome-terminal" y se abre la aplicacion ./sala"
	if(proceso == 0) {
		execlp("gnome-terminal","gnome-terminal","--wait", "--", "./sala", ciudad, capacidad, NULL);
		printf("\nError al ejecutar gnome-terminal");
		exit(-1);
	}
	int estado;
	waitpid(proceso, &estado, 0);
	printf("\n\nLa sala de %s ha cerrado\n", ciudad);
	printf("Debido al cierre, introduzca nuevamente: ");
	exit(0);
}

int main(){
	char nombresala[100];
	int capacidad;
	int opcion = 0;
	
	while (1) {
		printf("\n1 - Crear nueva sucursal\n2 - Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);

		switch(opcion) {
		    case 1: {
		        char capacidad_total[100];
		        printf("Ingrese el nombre de la ciudad: ");
		        scanf("%s", nombresala);
		        printf("¿Cual sera la capacidad?: ");
		        scanf("%d", &capacidad);
		        sprintf(capacidad_total, "%d", capacidad);
		        if (fork() == 0) {
		            crea_sucursal(nombresala, capacidad_total);
		        }
		        break;
		    }
		    case 2:
		        printf("\nProceso finalizado\n");
		        return 0;
		    default:
		        printf("Opcion no valida. Intente de nuevo.\n");
		}
	    }
	return 0;
}
