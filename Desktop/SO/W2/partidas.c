#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_LOCATION_LENGTH 50

// Definición de la estructura Partida
typedef struct {
    char jugador1[MAX_NAME_LENGTH];
    char jugador2[MAX_NAME_LENGTH];
    int puntos1;
    int puntos2;
    char lugar[MAX_LOCATION_LENGTH];
} Partida;

// Procedimiento que imprime los nombres de las personas que perdieron una partida
// contra el jugador cuyo nombre se pasa como parámetro.
void imprimirPerdedoresContra(Partida partidas[], int n, char jugadorGanador[]) {
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        // Si el jugadorGanador es el jugador1 y ganó la partida
        if (strcmp(partidas[i].jugador1, jugadorGanador) == 0 && partidas[i].puntos1 > partidas[i].puntos2) {
            printf("En la partida %d, %s venció a %s\n", i + 1, partidas[i].jugador1, partidas[i].jugador2);
            encontrado = 1;
        }
        // Si el jugadorGanador es el jugador2 y ganó la partida
        else if (strcmp(partidas[i].jugador2, jugadorGanador) == 0 && partidas[i].puntos2 > partidas[i].puntos1) {
            printf("En la partida %d, %s venció a %s\n", i + 1, partidas[i].jugador2, partidas[i].jugador1);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontraron partidas donde %s ganara.\n", jugadorGanador);
    }
}

// Función que retorna los puntos que sacó la primera persona que ganó una partida en Barcelona.
// Retorna -1 si no se encontró ninguna partida en Barcelona con un ganador.
int puntosPrimerGanadorBarcelona(Partida partidas[], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(partidas[i].lugar, "Barcelona") == 0) {
            if (partidas[i].puntos1 > partidas[i].puntos2) {
                return partidas[i].puntos1;
            } else if (partidas[i].puntos2 > partidas[i].puntos1) {
                return partidas[i].puntos2;
            }
        }
    }
    return -1;
}

int main() {
    // Definición de las partidas directamente en main (sin usar un "diccionario")
    Partida partidas[5];
    int n = 5;

    // Definición de la 1ra partida
    strcpy(partidas[0].jugador1, "Alice");
    strcpy(partidas[0].jugador2, "Bob");
    partidas[0].puntos1 = 21;
    partidas[0].puntos2 = 15;
    strcpy(partidas[0].lugar, "Barcelona");

    // Definición de la 2da partida
    strcpy(partidas[1].jugador1, "Charlie");
    strcpy(partidas[1].jugador2, "Dave");
    partidas[1].puntos1 = 18;
    partidas[1].puntos2 = 20;
    strcpy(partidas[1].lugar, "Madrid");

    // Definición de la 3ra partida
    strcpy(partidas[2].jugador1, "Eve");
    strcpy(partidas[2].jugador2, "Alice");
    partidas[2].puntos1 = 22;
    partidas[2].puntos2 = 19;
    strcpy(partidas[2].lugar, "Barcelona");

    // Definición de la 4ta partida
    strcpy(partidas[3].jugador1, "Frank");
    strcpy(partidas[3].jugador2, "Alice");
    partidas[3].puntos1 = 10;
    partidas[3].puntos2 = 20;
    strcpy(partidas[3].lugar, "Sevilla");

    // Definición de la 5ta partida
    strcpy(partidas[4].jugador1, "Bob");
    strcpy(partidas[4].jugador2, "Charlie");
    partidas[4].puntos1 = 16;
    partidas[4].puntos2 = 20;
    strcpy(partidas[4].lugar, "Barcelona");

    // Se define el nombre del jugador para buscar las partidas en las que ganó
    char nombreGanador[MAX_NAME_LENGTH] = "Alice";

    printf("Buscando partidas ganadas por %s:\n", nombreGanador);
    imprimirPerdedoresContra(partidas, n, nombreGanador);

    // Obtener y mostrar los puntos del primer ganador en Barcelona
    int puntos = puntosPrimerGanadorBarcelona(partidas, n);
    if (puntos != -1) {
        printf("\nLos puntos del primer ganador en Barcelona son: %d\n", puntos);
    } else {
        printf("\nNo se encontró ninguna partida en Barcelona con un ganador.\n");
    }

    return 0;
}
