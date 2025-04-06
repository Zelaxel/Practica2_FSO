#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int max_salas = 1000;
int salas_actuales[1000];
int n_salas = 0;

void crea_sucursal (const char* ciudad, char* capacidad){
	// Generamos un duplicado del proceso actual
	if(n_salas == max_salas){
		printf("Número de salas máximo alcanzado. Revisa si hay salas cerradas para liverarlas.\n");
		return;
	}
	pid_t proceso = fork();
	
	// Se comprueba si no se ha podido crear un nuevo proceso
	if(proceso == -1){
		printf("Se ha producido un error al crear la sala. Intentelo de nuevo.\n");
		exit(-1);
	}
	// En caso contrario, se ejecuta "gnome-terminal" y se abre la aplicacion ./sala"
	if(proceso == 0) {
		execlp("gnome-terminal","gnome-terminal", "--", "./sala", ciudad, capacidad, NULL);
		printf("Se ha producido un error al crear la sala. Intentelo de nuevo.\n");
		exit(-1);
	}
	else{ // Padre.
		salas_actuales[n_salas] = proceso;
		n_salas++;
	}
}

int main(){
	char nombre_sala[100];
	char capacidad[100];
	char instruccion[100];
	char menu[200] = "1. crea_sucursal\n2. salas_cerradas\n3. salir\n4. limpiar_panel\n\n";
	
	printf(menu);
	while (1) {
		scanf("%s", &instruccion);
		
		if(!strcmp(instruccion,"crea_sucursal")){ // 1. Crea sucursal.
	        printf("Ingrese el nombre de la ciudad: ");
	        scanf("%s", nombre_sala);
	        printf("¿Cual sera la capacidad?: ");
	        scanf("%s", &capacidad);
	        crea_sucursal(nombre_sala, capacidad);
	        printf("\n");
	    }
	    
		else if(!strcmp(instruccion,"salas_cerradas")){ // 2. Devuelve las salas cerradas.
			if(n_salas == 0) printf("No hay salas cerradas.\n\n");
			else {
				printf("Se han cerrado las salas:\n");
				for(int i = 0; i < n_salas; i++){
					printf("  Sala %d\n",salas_actuales[i]);
				}
				printf("\n");
			}
		}
	    
		else if(!strcmp(instruccion,"salir")){ // 3. Cerrar la ejecución.
	        printf("\nProceso finalizado\n\n");
	        return 0;
	    }
	    
	    else if(!strcmp(instruccion,"limpiar_panel")){ // 4. Limpia el terminal.
			int estado;
			pid_t proceso = fork();
			switch(proceso){
				case -1: // Error al lanzar proceso.
					printf("No se pudo limpiar la pantalla. Intentelo de nuevo.\n\n");
					break;
				case 0:	// (hijo) Borra la pantalla.
					execlp("clear","clear",NULL);
					printf("No se pudo limpiar la pantalla. Intentelo de nuevo.\n\n");
					break;
				default: // (Padre) Espera a que el hijo borre.
					waitpid(proceso, &estado, 0);
					printf("%s",menu);
					break;
			}
		}
	    
		else printf("Instruccion invalida '%s'. Intente de nuevo.\n\n",instruccion); // Opcion invalida.
	}
}
