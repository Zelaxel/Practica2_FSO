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
	printf("La sala de %s ha cerrado\n\n", ciudad);
	exit(0);
}

int main(){
	char nombresala[100];
	int capacidad;
	
	// Generamos un bucle infinito que no termina hasta que se
	// solicite salir del programa
	printf("1. crea_sucursal <nombre> <capacidad>\n2. salir\n3. limpiar_panel\n");
	char Instruccion[100];
	while(1){
		printf("\n");
		scanf("%s",Instruccion); // Usamos %s para leer cadenas
		if(!strcmp("crear_sucursal",Instruccion)){ // Creamos una sala.
			char nombre[100];
			char capacidad[100];
			scanf("%s",&nombre);
			scanf("%s",capacidad);
			if(fork()==0) crea_sucursal(nombre,capacidad);
		}
		// Si el usuario escribe "salir" le saca del programa
		if(!strcmp("salir",Instruccion)) break;
	}
	printf("\nProceso finalizado\n");
	return 0;
}
