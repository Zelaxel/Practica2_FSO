#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void crea_sucursal (const char* ciudad, int capacidad){
	capacidad_actual = capacidad;
	// Generamos un duplicado del proceso actual
	pid_t proceso = fork();
	
	// Se comprueba si no se ha podido crear un nuevo proceso
	if(proceso == -1){
		printf("Se ha producido un error en el proceso");
		exit(1);
	}
	// En caso contrario, se ejecuta "gnome-terminal" y se abre la aplicacion ./sala"
	if(proceso == 0) {
		execlp("gnome-terminal","gnome-terminal","--wait", "--", "./sala", ciudad, capacidad_str, NULL);
		printf("Error al ejecutar gnome-terminal");
		exit(1);
	}
	int estado;
	wait(&estado);
	prinf("La sala de %s ha cerrado", ciudad);
}

void main(){
	char nombresala[100];
	int capacidad;
	
	// Generamos un bucle infinito que no termina hasta que se
	// solicite salir del programa
	while(1){
		printf("¿Cual va a ser el nombre de la nueva sala?");
		scanf("%s",nombresala); // Usamos %s para leer cadenas
		
		// Si el usuario escribe "salir" le saca del programa
		if(!strcmp("salir",nombresala) break;
		
		printf("¿Que capacidad va a tener la sala?");
		scanf("%d",&capacidad); // Usamos %d para leer enteros
		
		crea_sucursal (nombresala, capacidad);
	}
	printf("Proceso finalizado");
	return 0;
}
