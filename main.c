#include "sucursal.h"
#include <stdio.h>
#include <string.h>

int main() {
	char nombresala[...];
	int capacidad;
	while (1) {
		// Pedir nombre de nueva sala y capacidad
		printf("Introduzca el nombre de la sala: ");
		scanf("%d",&nombresala);
		printf("Introduzca la cantidad de la sala: ");
		scanf("%d",&capacidad);
		if (!strcmp("salir",nombresala)) break;
		crea_sucursal(nombresala, capacidad);
	} 
	// termina el bucle principal
}
