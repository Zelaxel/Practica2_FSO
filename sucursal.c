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
		exit(-1);
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
	char instruccion[100];
	char menu[200] = "1. crea_sucursal\n2. salas_cerradas\n3. salir\n4. limpiar_panel\n\n";
	int salas_cerradas[1000];
	
	printf(menu);
	while (1) {
		scanf("%s", &instruccion);
		
		if(!strcmp(instruccion,"crea_sucursal")){ // Crea sucursal.
			char capacidad_total[100];
	        printf("Ingrese el nombre de la ciudad: ");
	        scanf("%s", nombresala);
	        printf("¿Cual sera la capacidad?: ");
	        scanf("%d", &capacidad);
	        sprintf(capacidad_total, "%d", capacidad);
	        switch (fork()) {
	        	case 0:
	            	crea_sucursal(nombresala, capacidad_total);
	            	break;
	            case -1:
	            	printf("Error al crear sala.");
	        }
	    }
	    
		else if(!strcmp(instruccion,"salir")){ // Cerrar la ejecución.
	        printf("\nProceso finalizado\n");
	        return 0;
	    }
	    
	    else if(!strcmp(instruccion,"limpiar_panel")){ // 6. Limpia el terminal.
			int estado;
			switch(fork()){
				case -1: // Error al lanzar proceso.
					printf("  No se pudo limpiar la pantalla. Repitalo ahora o más tarde.\n\n");
					break;
				case 0:	// (hijo) Borra la pantalla.
					execlp("clear","clear",NULL);
					break;
				default: // (Padre) Espera a que el hijo borre.
					wait(&estado);
					printf(menu);
					break;
			}
		}
	    
		else printf("Instruccion no valida '%s'. Intente de nuevo.\n",instruccion); // Opcion invalida.
	}
}
